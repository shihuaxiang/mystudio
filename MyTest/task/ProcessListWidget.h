#ifndef PROCESSLISTWIDGET_H
#define PROCESSLISTWIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QPoint>
#include <QModelIndex>

class ProcessInfo;
class QTableView;

typedef struct
{
    quint32 pid;
    quint32 wndHandle;
    QPixmap icon;
    QString name;
    QString wndText;
    QString fullPathName;
}TASK_ITEM;

namespace Ui {
    class ProcessListWidget;
}

class ProcessListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessListWidget(QWidget *parent = 0);
    ~ProcessListWidget();

    private slots:
    void on_tbvProcesses_doubleClicked(const QModelIndex &index);

private:
    void initTableView();
    void refreshTableItems();
    void initConnection();
    void getProcesses();

    void setTableViewStyle(QTableView *tbv);
    void setTableHeader(QTableView *tbv, QStandardItemModel &itemModel,
        const QStringList &strList);
    void setTableItem(QStandardItemModel &itemModel, const QStringList &strList,
        int row, int col = 0);

private:
    Ui::ProcessListWidget *ui;
    QStandardItemModel itemModel;
};

#endif // PROCESSLISTWIDGET_H
