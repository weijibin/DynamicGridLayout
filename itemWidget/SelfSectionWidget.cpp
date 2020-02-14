#include "SelfSectionWidget.h"
#include "ui_SelfSectionWidget.h"
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include "defines.h"
#include <QTimer>
#include <QPoint>
#include <QMouseEvent>

#define HORN_PIX_NORMAL            PPRE("skin/General/interact_native/roleplay/self_horn.png")
#define HORN_PIX_READING           PPRE("skin/General/interact_native/roleplay/self_horn_reading.png")
#define HORN_PIX_READINGANI_DIR    PPRE("skin/General/interact_native/roleplay/senior/rightAni")

static const int textMaxWidth = 480;

SelfSectionWidget::SelfSectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelfSectionWidget)
{
    ui->setupUi(this);
    initUi();
}

SelfSectionWidget::~SelfSectionWidget()
{
    delete ui;
}

void SelfSectionWidget::setStatus(int status)
{
    m_status = status;
    this->setProperty("status",QString::number(status));
    if(status == 1) {
        ui->label_horn->setStyleSheet(QString("border-image:url(%1);border-radius:0px;").arg(HORN_PIX_NORMAL));
        ui->label->setStyleSheet(QString("font-size:20px; color:#212831;"));
        ui->aniWidget->setVisible(false);
        ui->aniWidget->stop();
        ui->label_horn->setVisible(true);
    } else if(status == 2) {
        ui->label_horn->setStyleSheet(QString("border-image:url(%1);border-radius:0px;").arg(HORN_PIX_READING));
        ui->label->setStyleSheet(QString("font-size:20px; color:#FFFFFF;"));
        ui->aniWidget->setVisible(true);
        ui->aniWidget->start(SequenceFrame::KeepStart);
        ui->label_horn->setVisible(false);
    } else if(status == 3) {
        ui->label_horn->setStyleSheet(QString("border-image:url(%1);border-radius:0px;").arg(HORN_PIX_NORMAL));
        ui->label->setStyleSheet(QString("font-size:20px; color:#212831;"));
        ui->aniWidget->setVisible(false);
        ui->aniWidget->stop();
        ui->label_horn->setVisible(true);
    }
    style()->unpolish(this);
    style()->polish(this);
}

void SelfSectionWidget::setCurText(const QString &str,const QString& originText)
{
    m_originText = originText;
    ui->label->setText(str);
    updateSizeByContent();
}

void SelfSectionWidget::initUi()
{
   qDebug() << Q_FUNC_INFO;
   QFont font;
   font.setPixelSize(20);
   ui->label->setFont(font);
   setStatus(1);
   updateSizeByContent();
   this->installEventFilter(this);
   ui->label->installEventFilter(this);
   ui->label_horn->installEventFilter(this);
   ui->aniWidget->setFramePath(HORN_PIX_READINGANI_DIR,QString("speaker_right"));
}

void SelfSectionWidget::updateSizeByContent()
{
    qDebug() << Q_FUNC_INFO;
    QString text = m_originText;
    qDebug() << text;
    QFontMetrics fmt(ui->label->font());
    qDebug() << ui->label->font();
    int textWidth = fmt.width(text);
    qDebug() << "textWidth: " <<textWidth;
    if (textWidth >= textMaxWidth) {
        ui->label->setFixedWidth(textMaxWidth);
        ui->label->setWordWrap(true);
    } else {
        ui->label->setWordWrap(false);
    }
    ui->label->adjustSize();
    ui->label->update();
    qDebug() << ui->label->size();
}

void SelfSectionWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}

bool SelfSectionWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->label || obj == ui->label_horn || obj == this) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast <QMouseEvent*> (event);
            if(mouseEvent->button() == Qt::LeftButton) {
                qDebug()<< Q_FUNC_INFO << "Mouse Clicked";
                emit sigClicked();
                return true;
            }
        }
    }
    return false;
}

void SelfSectionWidget::enterEvent(QEvent *event)
{
    qDebug() << Q_FUNC_INFO;
    if(m_status != 2)
        setStatus(3);
}

void SelfSectionWidget::leaveEvent(QEvent *event)
{
    qDebug() << Q_FUNC_INFO;
    if(m_status != 2)
        setStatus(1);
}
