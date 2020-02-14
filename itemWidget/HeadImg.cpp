#include "HeadImg.h"
#include <QPainter>
#include <QPainterPath>
#include <QFont>
#include <QFontMetrics>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>
#include <QRect>
#include "defines.h"

HeadImg::HeadImg(QWidget*parent) : QWidget(parent)
{
    m_pix.load(PPRE("skin/General/interact_native/roleplay/boyLeft.png"));
    m_catchDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/xes_imgCache/";

    QDir d(m_catchDir);
    if(!d.exists()) {
        d.mkdir(m_catchDir);
    }

    m_timeLine = new QTimeLine;
    m_timeLine->setParent(this);
    m_timeLine->setDirection(QTimeLine::Backward);
    m_timeLine->setFrameRange(1, 360);
    connect(m_timeLine, SIGNAL(frameChanged(int)), this, SLOT(onFrameChanged(int)));
    connect(m_timeLine,&QTimeLine::finished,this,[=](){
        if (!m_timeLine) {
            return;
        }
        m_timeLine->stop();
        emit sigTimeOut();
    });

    m_font.setPixelSize(20);
}

void HeadImg::setImgUrl(QString img_url)
{
    qDebug()<< Q_FUNC_INFO << img_url;
    if(img_url.isEmpty())
        return;
    m_imgName = img_url.mid(img_url.lastIndexOf("/") + 1);

    QFileInfo file(m_catchDir + m_imgName);
    bool isExist = file.exists();

    qDebug()<< Q_FUNC_INFO <<m_catchDir<<m_imgName << isExist;
    if(isExist) {
        m_pix.load(m_catchDir+m_imgName);
        qDebug() << m_pix.size();
        update();
    } else {
        setRemoteImg(img_url);
    }
}

void HeadImg::setRemoteImg(const QString &img_url)
{
    qDebug() << Q_FUNC_INFO;
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(QNetworkRequest(img_url));
    connect(reply, &QNetworkReply::finished, [this, reply, manager](){
        manager->deleteLater();
        if (nullptr == reply) {
            return;
        }
        qDebug() << Q_FUNC_INFO;
        qDebug()<<reply->error();
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray bytes = reply->readAll();
            m_pix.loadFromData(bytes);
            qDebug() << m_catchDir+m_imgName;
            bool is = m_pix.save(m_catchDir+m_imgName);
            qDebug() << is;
            update();
        }
        reply->deleteLater();
    });
}


void HeadImg::startAniTimer(int second)
{
    m_second = second;
    if (!m_timeLine) {
        return;
    }

    m_timeLine->setDuration(second * 1000);
    m_timeLine->start();

    QPoint pt = rect().center();
    QFontMetrics metrics(m_font);
//    QRect rect_text = metrics.boundingRect(QString::number(second));
    QRect rect_text = metrics.boundingRect(QString::number(9));
    m_textPos = pt+QPoint(-1*(rect_text.width()/2),rect_text.height()/2);
}

void HeadImg::endAniTimer()
{
    if (!m_timeLine) {
        return;
    }
    m_timeLine->stop();
}

void HeadImg::onFrameChanged(int frame)
{
    m_angle = frame*16;
    update();
}

void HeadImg::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing,true);

    painter.save();
    QPainterPath path;
    int offset = m_ringWidth/2;
    QRect r = rect().adjusted(offset,offset,-1*offset,-1*offset);
    path.addEllipse(r);
    painter.setClipPath(path);
    painter.drawPixmap(r,m_pix);
    painter.restore();

    if (m_timeLine->state() == QTimeLine::Running) {

        float ratio =  float(m_angle/360.0/16.0);
        int num = int(m_second * ratio) + 1;

        QColor colorRing("#F2658D") , colorText("#FFFFFF");
        if(num < 4) {
            colorRing.setNamedColor("#FF5E50");
            colorText.setNamedColor("#FF5E50");

            //mask
            painter.save();
            painter.setPen(Qt::NoPen);
            painter.setBrush(QBrush(QColor(33,40,49,150)));
            painter.drawEllipse(r);
            painter.restore();

            //ring
            int angle = m_angle * m_second /3;
            painter.save();
            QPen pen(colorRing, m_ringWidth);
            painter.setPen(pen);
            painter.drawArc(r,90*16, -angle);
            painter.restore();

            //text
            painter.save();
            QPen pen2(colorText);
            painter.setPen(pen2);
            painter.setFont(m_font);
            painter.drawText(m_textPos,QString::number(num));
            painter.restore();
        }

//        //mask
//        painter.save();
//        painter.setPen(Qt::NoPen);
//        painter.setBrush(QBrush(QColor(33,40,49,150)));
//        painter.drawEllipse(r);
//        painter.restore();

//        //ring
//        painter.save();
//        QPen pen(colorRing, m_ringWidth);
//        painter.setPen(pen);
//        painter.drawArc(r,90*16, -m_angle);
//        painter.restore();

//        //text
//        painter.save();
//        QPen pen2(colorText);
//        painter.setPen(pen2);
//        painter.setFont(m_font);
//        painter.drawText(m_textPos,QString::number(num));
//        painter.restore();
    }
}
