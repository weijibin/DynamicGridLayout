#include "widget.h"
#include "ui_widget.h"
#include <QGridLayout>
#include "Item.h"
#include <QDebug>
#include <QSpacerItem>
#include <iostream>
#include <memory>

using namespace std;

class B;    //声明
class A
{
public:
    shared_ptr<B> pb_;
    A()
    {
        cout << "A contruct\n";
    }

    ~A()
    {
        cout << "A delete\n";
    }
};

class B
{
public:
    shared_ptr<A> pa_;
    B()
    {
        cout << "B contruct\n";
    }

    ~B()
    {
        cout << "B delete\n";
    }
};

void fun()
{
    shared_ptr<B> pb(new B());
    shared_ptr<A> pa(new A());
    cout << pb.use_count() << endl; //1
    cout << pa.use_count() << endl; //1
    pb->pa_ = pa;
    pa->pb_ = pb;
    cout << pb.use_count() << endl; //2
    cout << pa.use_count() << endl; //2
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
//    initUi();

//    char buffer[256] = "p123oo 34";
//    int i = atoi (buffer);
//    qDebug() << "testAtoi==" << i;
    fun();
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
