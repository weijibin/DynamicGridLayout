#include "OtherSectionWidget.h"
#include "ui_OtherSectionWidget.h"
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include <QMouseEvent>

#define HORN_PIX_NORMAL            (":/res/item/other_horn.png")
#define HORN_PIX_READING           (":/res/item/other_horn_reading.png")
#define HORN_PIX_READINGANI_DIR    (":/res/item/leftAni")

static const int textMaxWidth = 480;

OtherSectionWidget::OtherSectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OtherSectionWidget)
{
    ui->setupUi(this);
    initUi();
}

OtherSectionWidget::~OtherSectionWidget()
{
    delete ui;
}

void OtherSectionWidget::setStatus(int status)
{
    m_status = status;
    qDebug() << Q_FUNC_INFO << status;
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

void OtherSectionWidget::setCurText(const QString &str)
{
    ui->label->setText(str);
    updateSizeByContent();
}

void OtherSectionWidget::initUi()
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
   ui->aniWidget->setFramePath(HORN_PIX_READINGANI_DIR,QString("speaker_left"));
}

void OtherSectionWidget::updateSizeByContent()
{
    qDebug() << Q_FUNC_INFO;
    QString text = ui->label->text();
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
}

void OtherSectionWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}

bool OtherSectionWidget::eventFilter(QObject *obj, QEvent *event)
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


void OtherSectionWidget::enterEvent(QEvent *event)
{
    qDebug() << Q_FUNC_INFO;
    if(m_status != 2)
        setStatus(3);
}

void OtherSectionWidget::leaveEvent(QEvent *event)
{
    qDebug() << Q_FUNC_INFO;
    if(m_status != 2)
        setStatus(1);
}
