#ifndef PROCESSINFOFORM_H
#define PROCESSINFOFORM_H

#include <QWidget>
#include <QStandardItemModel>
#include <QPoint>
#include <QModelIndex>

#include "process.h"

namespace Ui {
class ProcessInfoForm;
}

class ProcessInfo;

typedef struct
{
    quint32 pid;
    quint32 wndHandle;
    QPixmap icon;
    QString name;
    QString wndText;
    QString fullPathName;
}TASK_ITEM;

class ProcessInfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessInfoForm(QWidget *parent = 0);
    ~ProcessInfoForm();

public slots:

private:
    void initTableView();  
    void refreshTableItems();
    void initConnection();
    void getProcesses();

private slots:

private:
    Ui::ProcessInfoForm *ui;
    QStandardItemModel mItemModel;    
};

#endif // PROCESSINFOFORM_H
