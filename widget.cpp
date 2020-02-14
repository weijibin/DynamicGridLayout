#include "widget.h"
#include "ui_widget.h"
#include <QGridLayout>
#include "Item.h"
#include <QDebug>
#include <QSpacerItem>
#include <iostream>
#include <memory>
#include <QEventLoop>
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <QScrollBar>
#include <QPainter>
#include "itemWidget/SeniorConversationItem.h"
#include "dlg/dialog.h"

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
//    fun();

//    connect(ui->pushButton,&QPushButton::clicked,[=](){
//        qDebug() << "lambda";
//        ui->label->setText("lambda");
//        ui->label->update();    // 阻塞后 ，前面label 设置text 不会刷新

////        ui->pushButton->disconnect(this);
//    });

//    ui->pushButton->disconnect(this);

      //模态对话框的 层级测试

}

Widget::~Widget()
{
    delete ui;
}

void Widget::initUi()
{
    qDebug() << Q_FUNC_INFO;
    QVBoxLayout * vLayout = new QVBoxLayout;
    int count = 20;
    for(int i =0; i< count ; i++) {
        SeniorConversationItem *item = new SeniorConversationItem;
        vLayout->addWidget(item);
    }

    ui->scrollWidget->setLayout(vLayout);

    QTimer * time = new QTimer(this);
    time->start(1000);
    connect(time,&QTimer::timeout,this,[=](){
        qDebug() << "======set Effect====";
        QRect r = ui->scrollArea->contentsRect();
        qDebug() << r;
        int pt = ui->scrollArea->verticalScrollBar()->value();
        QSize  s = r.size();
        r.setTopLeft(QPoint(0,pt));
        r.setSize(s);

        qDebug() << r << pt;

        QLinearGradient alphaGradient(r.topLeft(), r.bottomLeft());
        alphaGradient.setColorAt(0.0, Qt::transparent);
        alphaGradient.setColorAt(0.2, Qt::black);
        alphaGradient.setColorAt(0.8, Qt::black);
        alphaGradient.setColorAt(1.0, Qt::transparent);
        QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect;
        effect->setOpacityMask(alphaGradient);
        ui->scrollWidget->setGraphicsEffect(effect);
    });


//    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Widget::on_pushButton_clicked()
{
    qDebug() << Q_FUNC_INFO << "start";
//    ui->label->setText("32323232323");
////    ui->label->repaint();   // 阻塞后 ，前面label 设置text 会强制刷新
//    ui->label->update();    // 阻塞后 ，前面label 设置text 不会刷新

//    while(1){}   // 会阻塞界面

//    if(m_loop == nullptr)
//    {
//        m_loop = new QEventLoop;
//    }
//    m_loop->exec(QEventLoop::ExcludeUserInputEvents);  // 不会阻塞界面


    // 测试对话框层级

    m_dlg1 = new Dialog(this);
    m_dlg1->setText("1111111111111111");

    m_dlg2 = new Dialog(this);
    m_dlg2->setText("2222222222222222");

    QTimer::singleShot(2000,this,[=](){
        m_dlg1->setFixedSize(400,400);
        m_dlg1->exec();
    });

    QTimer::singleShot(4000,this,[=](){
        m_dlg1->raise();
    });

    m_dlg2->setFixedSize(200,200);
//    m_dlg1->setWindowFlag(Qt::WindowStaysOnTopHint);
    // dlg 的显示层级 与创建顺序无关， 与调用显示的顺序有关，如果设置ontop 属性 则会打乱这个顺序。
//    m_dlg2->setWindowFlag(Qt::WindowStaysOnTopHint);
    m_dlg2->exec();


    qDebug() << Q_FUNC_INFO << "end";
}

void Widget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
