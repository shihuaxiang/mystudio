#include <QStandardItem>
#include "processinfoform.h"
#include "ui_processinfoform.h"
#include "tableviewhelper.h"

#include <windows.h>
#include <psapi.h>
#include <stdio.h>
#include <tchar.h>
Q_GUI_EXPORT QPixmap qt_pixmapFromWinHICON(HICON icon);
Q_GUI_EXPORT HICON qt_pixmapToWinHICON(const QPixmap &p);

QVector<TASK_ITEM*> g_vec;

ProcessInfoForm::ProcessInfoForm(QWidget *parent) :
QWidget(parent),
ui(new Ui::ProcessInfoForm),
mItemModel()
{
    ui->setupUi(this);
    this->resize(1280,720);

    ui->rdoAllProcess->setChecked(true);
    initTableView();
    initConnection();
    refreshTableItems();
}

ProcessInfoForm::~ProcessInfoForm()
{
    delete ui;
}

void ProcessInfoForm::initTableView()
{
    QStringList headerList;
    headerList.append(tr("PID"));
    headerList.append(tr("Name"));
    headerList.append(tr("WndHandle"));
    headerList.append(tr("WndText"));

    TableViewHelper::setTableHeader(ui->tbvProcesses, mItemModel, headerList);

    TableViewHelper::setTableViewStyle(ui->tbvProcesses);
    ui->tbvProcesses->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tbvProcesses->setContextMenuPolicy(Qt::CustomContextMenu);
}

void ProcessInfoForm::initConnection()
{
    //    connect(ui->rdoAllProcess, SIGNAL(clicked(bool)),
    //            this, SLOT(showAllProcess(bool)));
    //    connect(ui->rdoMyProcess, SIGNAL(clicked(bool)),
    //            this, SLOT(showMyProcess(bool)));
    //    connect(ui->tbvProcesses->horizontalHeader(), SIGNAL(sectionClicked(int)),
    //            this, SLOT(sortProcess(int)));
}

void ProcessInfoForm::refreshTableItems()
{
    getProcesses();

    int processCount = g_vec.size();
    ui->labProcessCount->setText(QString::number(processCount));

    int index = 0;
    for (index = 0; index < processCount; index++)
    {
        TASK_ITEM* taskItem = g_vec.at(index);

        QStringList cellList;
        cellList << QString::number(taskItem->pid)
            << taskItem->name
            << QString::number(taskItem->wndHandle, 16).toUpper()
            << taskItem->wndText;

        TableViewHelper::setTableItem(mItemModel, cellList, index);
    }

    if (mItemModel.rowCount() > processCount)
    {
        mItemModel.removeRows(processCount, mItemModel.rowCount() - processCount);
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

QString getModuleName(HANDLE hProcess)
{
    char szModuleName[MAX_PATH] = ("");
    QString moduleName;

    HMODULE hModules[1024] = { NULL };
    DWORD cbNeeded;

    if (EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded))
    {
        DWORD retVal = GetModuleBaseNameA(hProcess, hModules[0], szModuleName,
            sizeof(szModuleName) / sizeof(char));

        if (retVal != 0)
        {
            moduleName = QString::fromLocal8Bit(szModuleName);
        }
    }

    return moduleName;
}

bool getModuleName(quint32 processID, TASK_ITEM* taskItem)
{
    // Get a handle to the process.
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
        PROCESS_VM_READ,
        FALSE, processID);

    if (NULL == hProcess)
        return false;

    taskItem->fullPathName = getFullPathName(hProcess);
    taskItem->name = getModuleName(hProcess);

    // Release the handle to the process.
    CloseHandle(hProcess);

    return true;
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

        char szWndText[MAX_PATH] = ("");
        GetWindowTextA(hWnd, szWndText, sizeof(szWndText));

        TASK_ITEM* taskItem = new TASK_ITEM;
        getModuleName(processID, taskItem);
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

void ProcessInfoForm::getProcesses()
{
    g_vec.clear();

    EnumWindows(EnumWindowsProc, (LPARAM)0);
}
