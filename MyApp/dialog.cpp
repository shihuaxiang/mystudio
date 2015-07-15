#include <QDebug>
#include <QMessageBox>

#include "dialog.h"
#include "ui_dialog.h"
#include "MyCoo.h"
#include "MyUtil.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButtonUtil_clicked()
{
    qDebug() << MyUtil::getName();

    QMessageBox::warning(this, tr("MyApp"),
                         MyUtil::getName(),
                         QMessageBox::Ok | QMessageBox::Cancel,
                         QMessageBox::Ok);
}

void Dialog::on_pushButtonCoo_clicked()
{
    qDebug() << MyCoo::getName();

    QMessageBox::warning(this, tr("MyApp"),
                         MyCoo::getName(),
                         QMessageBox::Ok | QMessageBox::Cancel,
                         QMessageBox::Ok);
}
