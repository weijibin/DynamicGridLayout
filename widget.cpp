#include "widget.h"
#include "ui_widget.h"
#include <QGridLayout>
#include "Item.h"
#include <QDebug>
#include <QSpacerItem>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    initUi();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initUi()
{
    qDebug() << Q_FUNC_INFO;
    ui->gridLayout->setRowStretch(0,1);
    int count = 4;
    for(int i =0; i< count ; i++) {
        Item *item = new Item;
        ui->gridLayout->addWidget(item,i/3,i%3);
    }
    if(count < 3) {
        ui->gridLayout->addItem(new QSpacerItem(100,100,QSizePolicy::Expanding),0,2);
    }

    // 是否顶部对齐
    ui->verticalLayout->addStretch();
}
