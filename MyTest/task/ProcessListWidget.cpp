#include <QStandardItem>
#include <QDebug>
#include "ProcessListWidget.h"
#include "ui_ProcessListWidget.h"

#include <windows.h>
#include <psapi.h>
#include <stdio.h>
#include <tchar.h>

Q_GUI_EXPORT QPixmap qt_pixmapFromWinHICON(HICON icon);
Q_GUI_EXPORT HICON qt_pixmapToWinHICON(const QPixmap &p);

QVector<TASK_ITEM*> g_vec;

ProcessListWidget::ProcessListWidget(QWidget *parent)
: QWidget(parent)
, ui(new Ui::ProcessListWidget)
, itemModel()
{
    ui->setupUi(this);
    this->resize(540, 360);

    initTableView();
    initConnection();
    refreshTableItems();
}


ProcessListWidget::~ProcessListWidget()
{
    delete ui;
}

void ProcessListWidget::on_tbvProcesses_doubleClicked(const QModelIndex &index)
{
    QAbstractItemModel* abstractModel = (QAbstractItemModel*)index.model();
    QStandardItemModel* standardModel = dynamic_cast<QStandardItemModel*>(abstractModel);
    QStandardItem* item = standardModel->itemFromIndex(index);
    QStandardItem* pidItem = standardModel->item(item->row());
    
    QString pidString = pidItem->text();
    int pid = pidString.toInt();

    qDebug() << "pid is: " << pid;
    emit processClicked(pid);
}

bool ProcessListWidget::terminateProcess(int pid)
{
    DWORD dwDesiredAccess = PROCESS_TERMINATE;
    BOOL  bInheritHandle = FALSE;
    HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, pid);
    if (hProcess == NULL)
        return FALSE;

    BOOL result = TerminateProcess(hProcess, 1);

    CloseHandle(hProcess);

    return result;
}

void ProcessListWidget::setTableViewStyle(QTableView *tbv)
{
    if (tbv == NULL)
    {
        return;
    }
    tbv->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tbv->setSelectionBehavior(QAbstractItemView::SelectRows);
    tbv->verticalHeader()->hide();
    tbv->setShowGrid(false);
    tbv->setColumnWidth(0, 80);
    tbv->setColumnWidth(1, 100);
    tbv->setColumnWidth(2, 300);
}

void ProcessListWidget::setTableHeader(QTableView *tbv, QStandardItemModel &itemModel,
    const QStringList &strList)
{
    if (tbv == NULL)
    {
        return;
    }

    int col = 0;
    for (QStringList::const_iterator it = strList.begin();
        it != strList.end(); ++it)
    {
        itemModel.setHorizontalHeaderItem(col++, new QStandardItem(*it));
    }
    tbv->setModel(&itemModel);
}

void ProcessListWidget::setTableItem(QStandardItemModel &itemModel, const QStringList &strList,
    int row, int col)
{
    if (row < 0)
    {
        return;
    }
    for (QStringList::const_iterator it = strList.begin();
        it != strList.end(); ++it)
    {
        itemModel.setItem(row, col++, new QStandardItem(*it));
    }
}

void ProcessListWidget::initTableView()
{
    QStringList headerList;
    headerList.append(tr("PID"));
    headerList.append(tr("Name"));
    headerList.append(tr("Caption"));

    setTableHeader(ui->tbvProcesses, itemModel, headerList);

    setTableViewStyle(ui->tbvProcesses);
    ui->tbvProcesses->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tbvProcesses->setContextMenuPolicy(Qt::CustomContextMenu);
}

void ProcessListWidget::initConnection()
{
    connect(ui->tbvProcesses->horizontalHeader(), SIGNAL(sectionClicked(int)),
        this, SLOT(sortProcess(int)));
}

void ProcessListWidget::refreshTableItems()
{
    getProcesses();

    int processCount = g_vec.size();

    int index = 0;
    for (index = 0; index < processCount; index++)
    {
        TASK_ITEM* taskItem = g_vec.at(index);

        QStringList cellList;
        cellList << QString::number(taskItem->pid)
            << taskItem->name
            << taskItem->wndText;

        setTableItem(itemModel, cellList, index);
    }

    if (itemModel.rowCount() > processCount)
    {
        itemModel.removeRows(processCount, itemModel.rowCount() - processCount);
    }
}

//************************************************************************************
//
BOOL IsAppMainWindow(HWND hWnd)
{
    BOOL b1 = ::IsWindowVisible(hWnd);
    BOOL b2 = (::GetWindow(hWnd, GW_OWNER) == NULL);

    char szWndText[MAX_PATH] = ("");
    GetWindowTextA(hWnd, szWndText, sizeof(szWndText));

    return (strlen(szWndText) > 0 && b1 && b2);
}

QString getFullPathName(HANDLE hProcess)
{
    char szFullPathName[MAX_PATH] = ("");
    QString fullPathName;

    DWORD retVal = 0;
    retVal = GetModuleFileNameExA(hProcess, NULL, szFullPathName, sizeof(szFullPathName) / sizeof(char));
    if (retVal != 0)
    {
        fullPathName = QString::fromLocal8Bit(szFullPathName);
    }

    return fullPathName;
}

bool getModuleName(HANDLE hProcess, QString& moduleName)
{
    char szModuleName[MAX_PATH] = ("");
    //QString moduleName;

    HMODULE hModules[1024] = { NULL };
    DWORD cbNeeded;

    if (EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded))
    {
        qDebug() << "------------------------------------------";

        bool isFound = false;
        unsigned int i;
        for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
        {
            if (GetModuleFileNameExA(hProcess, hModules[i], szModuleName,
                sizeof(szModuleName) / sizeof(char)))
            {
                moduleName = QString::fromLocal8Bit(szModuleName);
                isFound = moduleName.endsWith("AudioSes.dll", Qt::CaseInsensitive);
                if (isFound)
                {
                    qDebug() << "moduleName ..." << i << "   " << moduleName << "isFound: " << isFound;
                    break;
                }
            }
        }

        if (!isFound)
            return false;

        DWORD retVal = GetModuleBaseNameA(hProcess, hModules[0], szModuleName,
            sizeof(szModuleName) / sizeof(char));

        if (retVal != 0)
        {
            moduleName = QString::fromLocal8Bit(szModuleName);
            qDebug() << "moduleName ..." << moduleName;

            return true;
        }
    }

    return false;
}

bool getModuleName(quint32 processID, TASK_ITEM* taskItem)
{
    // Get a handle to the process.
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
        PROCESS_VM_READ,
        FALSE, processID);

    if (NULL == hProcess)
        return false;

    QString moduleName;
    bool ret = getModuleName(hProcess, moduleName);
    if (ret)
    {
        taskItem->fullPathName = getFullPathName(hProcess);
        taskItem->name = moduleName;
    }

    // Release the handle to the process.
    CloseHandle(hProcess);

    return ret;
}

QPixmap extractIcon(QString fileName)
{
    DWORD dwFileAttributes = 0;
    UINT uFlags = SHGFI_ICON | SHGFI_LARGEICON;

    SHFILEINFOA sfi;
    ZeroMemory(&sfi, sizeof(sfi));

    DWORD dwRC = SHGetFileInfoA(fileName.toStdString().c_str(), dwFileAttributes, &sfi, sizeof(sfi), SHGFI_ICON | SHGFI_LARGEICON);

    QPixmap pixmap = qt_pixmapFromWinHICON(sfi.hIcon);

    DestroyIcon(sfi.hIcon);

    return pixmap;
}

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
    Q_ASSERT(hWnd);

    static int wndIndex = 0;

    if (IsAppMainWindow(hWnd))
    {
        DWORD processID = 0;
        DWORD dwThreadId = GetWindowThreadProcessId(hWnd, &processID);

        TASK_ITEM* taskItem = new TASK_ITEM;
        if (!getModuleName(processID, taskItem))
            return TRUE;

        char szWndText[MAX_PATH] = ("");
        GetWindowTextA(hWnd, szWndText, sizeof(szWndText));

        taskItem->pid = processID;

        //icon
        if (!taskItem->fullPathName.isEmpty())
            taskItem->icon = extractIcon(taskItem->fullPathName);
        taskItem->wndHandle = (quint32)(hWnd);
        taskItem->wndText = QString::fromLocal8Bit(szWndText);

        g_vec.push_back(taskItem);

        //SaveWndPixmap(hWnd);
    }

    wndIndex++;

    return TRUE;
}

void ProcessListWidget::getProcesses()
{
    g_vec.clear();

    EnumWindows(EnumWindowsProc, (LPARAM)0);
}
