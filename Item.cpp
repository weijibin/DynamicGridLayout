#include "Item.h"
#include "ui_Item.h"
#include <QPainter>
#include <QStyleOption>
#include <QPaintEvent>
#include <QDebug>

Item::Item(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Item)
{
    ui->setupUi(this);
    this->setFixedSize(300,300);

    this->setObjectName("itemObj");
    QString str;
    str = "QWidget#itemObj{background-color:#fff000;}\
           QWidget#itemObj[status=\"1\"]{background-color:#ff0000;}\
           QWidget#itemObj[status=\"2\"]{background-color:#00ff00;}";
    this->setStyleSheet(str);
}

Item::~Item()
{
    delete ui;
}

void Item::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Item::enterEvent(QEvent *event)
{
    qDebug() << Q_FUNC_INFO;
    setStatus(2);
}

void Item::leaveEvent(QEvent *event)
{
    qDebug() << Q_FUNC_INFO;
    setStatus(1);
}

void Item::setStatus(int status)
{
    QString str = QString::number(status);
    qDebug() << Q_FUNC_INFO << QString::number(status);
    this->setProperty("status",status);
    this->style()->unpolish(this);
    this->style()->polish(this);
}
