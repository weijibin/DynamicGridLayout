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
