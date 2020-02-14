#include "StarsWidget.h"
#include <QDebug>
#include <QLabel>
#include <QPainter>

#define STAR_PIX    (":/res/item/star.png")

StarsWidget::StarsWidget(QWidget *parent) : QWidget(parent)
{
    initUi();
}

void StarsWidget::initUi()
{
    m_layout = new QHBoxLayout;
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSizeConstraint(QLayout::SetFixedSize);
    setFixedHeight(20);
    this->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout);
//    this->setStyleSheet(QString("#starLabel{border-image:url(%1);}").arg(STAR_PIX));
    setStarNum(4);
}

void StarsWidget::clearLayout(QLayout *layout)
{
    qDebug() << Q_FUNC_INFO;
    QLayoutItem *item;
    while((item = layout->takeAt(0)) != 0)
    {
        //删除widget
        if(item->widget())
        {
            delete item->widget();
        }
        //删除子布局
        QLayout *childLayout = item->layout();
        if(childLayout)
        {
            clearLayout(childLayout);
        }
        delete item;
    }
}

void StarsWidget::setStarNum(int num)
{
    qDebug() << Q_FUNC_INFO << num;
    if(num < 1) {
        this->setVisible(false);
        return;
    }
    clearLayout(m_layout);
    m_starNum = num;

    for(int i =0; i< num; i++) {
        QLabel * label = new QLabel(this);
        label->setObjectName("starLabel");
        label->setFixedSize(20,20);
        label->setStyleSheet(QString("border-image:url(%1);").arg(STAR_PIX));
        m_layout->addWidget(label);
    }
    this->setVisible(true);
}
