#include "SeniorConversationItem.h"
#include "ui_SeniorConversationItem.h"
#include <QDebug>

#define  OTHER_STYLESHEET ("QWidget{\
                            border: none; \
                            border-top-left-radius:24px;\
                            border-bottom-left-radius:0px;\
                            border-top-right-radius:24px;\
                            border-bottom-right-radius:24px;\
                            }\
                            QWidget%1{\
                                background-color:rgba(255,255,255,153);\
                            }\
                            QWidget%2{\
                                background-color:#6B67FF;\
                            }\
                            QWidget%3{\
                                background-color:rgba(255,255,255,204);\
                            }")

#define SELF_STYLESHEET ("QWidget{\
                            border: none; \
                            border-top-left-radius:24px;\
                            border-bottom-left-radius:24px;\
                            border-top-right-radius:24px;\
                            border-bottom-right-radius:0px;\
                         }\
                         QWidget%1{\
                             background-color:rgba(255,255,255,153);\
                         }\
                         QWidget%2{\
                            background-color:#F2658D;\
                         }\
                         QWidget%3{\
                             background-color:rgba(255,255,255,204);\
                         }")

#define PRAISE_PIX          (":/res/item/senior_praise_nor.png")
#define PRAISE_PIX_HOVER    (":/res/item/senior_praise_hover.png")
#define PRAISE_PIX_PRESS    (":/res/item/senior_praise_pressed.png")

#define PRI_PRAISE_PIX          (":/res/item/primary_praise_nor.png")
#define PRI_PRAISE_PIX_HOVER    (":/res/item/primary_praise_hover.png")
#define PRI_PRAISE_PIX_PRESS    (":/res/item/primary_praise_pressed.png")

#define PRAISE_BTN_CSS ( "QPushButton{" \
    "border-image:url(%1);"\
    "}" \
    "QPushButton:disabled{" \
    "border-image:url(%3);"\
    "}" \
    "QPushButton:hover{" \
    "border-image:url(%2);"\
    "}" \
    "QPushButton:pressed{" \
    "border-image:url(%3);"\
    "}" )

SeniorConversationItem::SeniorConversationItem(bool isPrimary,QWidget *parent) :
    m_isPrimary(isPrimary),
    QWidget(parent),
    ui(new Ui::SeniorConversationItem)
{
    ui->setupUi(this);
    initUi();
    initConnections();
}

SeniorConversationItem::~SeniorConversationItem()
{
    delete ui;
}

void SeniorConversationItem::initUi()
{
    qDebug() << Q_FUNC_INFO;

    // other ui
    QString styleStr;
    if(m_isPrimary) {
        styleStr = QString(PRAISE_BTN_CSS).arg(PRI_PRAISE_PIX).arg(PRI_PRAISE_PIX_HOVER).arg(PRI_PRAISE_PIX_PRESS);
    } else {
        styleStr = QString(PRAISE_BTN_CSS).arg(PRAISE_PIX).arg(PRAISE_PIX_HOVER).arg(PRAISE_PIX_PRESS);
    }

    ui->praise_btn->setStyleSheet(styleStr);

    ui->other_dlg->setStyleSheet(QString(OTHER_STYLESHEET).arg("[status=\"1\"]")
                                 .arg("[status=\"2\"]").arg("[status=\"3\"]"));
    // self ui
    ui->self_dlg->setStyleSheet(QString(SELF_STYLESHEET).arg("[status=\"1\"]")
                                .arg("[status=\"2\"]").arg("[status=\"3\"]"));
}

void SeniorConversationItem::initConnections()
{
    qDebug() << Q_FUNC_INFO;
    connect(ui->self_dlg,&SelfSectionWidget::sigClicked,this,[=]{
        qDebug() << Q_FUNC_INFO << "SelfSectionWidget::sigClicked";
        if(m_info.isAnswered) {
            int index = property("index").toInt();
            emit sigItemClicked(index);
        }
    });

    connect(ui->other_dlg,&OtherSectionWidget::sigClicked,this,[=]{
        qDebug() << Q_FUNC_INFO << "OtherSectionWidget::sigClicked";
        if(m_info.isAnswered) {
            int index = property("index").toInt();
            emit sigItemClicked(index);
        }
    });

    connect(ui->img_self,&HeadImg::sigTimeOut,this,[=](){
        qDebug() << Q_FUNC_INFO << "HeadImg::sigTimeOut";
        if(!(m_info.isAnswered)) {
            int index = property("index").toInt();
            emit sigInReadingTimeOut(index);
        }
    });

    connect(ui->praise_btn,&QPushButton::clicked,this,[=](){
        qDebug() << Q_FUNC_INFO << "PraiseBtn  clicked";
        {
            int index = property("index").toInt();
            emit sigPraiseClicked(index);
            ui->praise_btn->setEnabled(false);
        }
    });
}

void SeniorConversationItem::setStatus(int status)
{
    qDebug() << Q_FUNC_INFO << status;
    if(m_info.isMyRole) {
        ui->self_dlg->setStatus(status);
    } else {
        ui->other_dlg->setStatus(status);
    }
}

void SeniorConversationItem::startSelfReadTimer(int time)
{
    qDebug() << Q_FUNC_INFO ;
    if(m_info.isMyRole) {
        ui->img_self->startAniTimer(time);
    }
}

void SeniorConversationItem::endSelfReadTimer()
{
    qDebug() << Q_FUNC_INFO ;
    if(m_info.isMyRole) {
        ui->img_self->endAniTimer();
    }
}

void SeniorConversationItem::setInfo(const SpeechInfo& info)
{
    qDebug() << Q_FUNC_INFO ;
    m_info = info;
    updateUiByInfo();
}

void SeniorConversationItem::updateUiByInfo()
{
    qDebug() << Q_FUNC_INFO << m_info.isMyRole << m_info.isNeedPraise ;
    if(m_info.isMyRole) {
        ui->stackedWidget->setCurrentIndex(1);
        //init self ui
        ui->self_dlg->setCurText(m_info.displayText,m_info.text);
        ui->img_self->setImgUrl(m_info.headInfo.img_url);
        ui->name_self->setText(m_info.headInfo.name);
        ui->star_self->setStarNum(m_info.starNum);
    } else {
        ui->stackedWidget->setCurrentIndex(0);
        //init other ui
        ui->other_dlg->setCurText(m_info.displayText);
        ui->img_other->setImgUrl(m_info.headInfo.img_url);
        ui->name_other->setText(m_info.headInfo.name);
        ui->star_other->setStarNum(m_info.starNum);
        ui->praise_btn->setVisible(m_info.isNeedPraise);
    }
}
