#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
//    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::setText(const QString &str)
{
   qDebug() << Q_FUNC_INFO << str;
   ui->label->setText(str);
}
