#include "SequenceFrame.h"

#include <QDir>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QFileInfoList>

SequenceFrame::SequenceFrame(QWidget *parent)
    : QWidget(parent)
    , m_timer(nullptr)
    , m_pixIdx(0)
    , m_startAttribute(KeepStart)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAutoFillBackground(false);
    m_pixGroup.clear();
}

SequenceFrame::~SequenceFrame()
{
    stop();
}

void SequenceFrame::setFramePath(const QString &path, const QString &baseName)
{
    stop();

    m_pixGroup.clear();
    QStringList nameFilters;
    nameFilters << "*.png";

    QDir d(path);
    QFileInfoList files = d.entryInfoList(nameFilters, QDir::NoFilter, QDir::Name);
    int count = files.size();

    for (int i = 0; i < count; ++i) {
        QString facePath = path + "/" + baseName + QString("%1.png").arg(i+1);
        QPixmap pix = QPixmap(facePath);
        m_pixGroup.push_back(pix);
    }
}

void SequenceFrame::clear()
{
    m_pixGroup.clear();
}

void SequenceFrame::start(const SequenceFrame::StartAttribute &attribute)
{
    m_startAttribute = attribute;

    if (m_timer == nullptr) {
        m_timer = new QTimer(this);
        connect(m_timer, &QTimer::timeout, this, &SequenceFrame::onTimeOut);
        m_timer->setInterval(100);
    }

    if (!m_timer->isActive()) {
        m_timer->start();
    }

    setVisible(true);
}

void SequenceFrame::stop()
{
    if (m_timer != nullptr && m_timer->isActive()) {
        m_timer->stop();
    }

    setVisible(false);
}

void SequenceFrame::onTimeOut()
{
    if (m_pixGroup.isEmpty()) {
        return;
    }

    int idx = m_pixIdx;
    bool isFinished = false;
    if ((++m_pixIdx) >= m_pixGroup.size()) {
        m_pixIdx = 0;
        isFinished = true;
    }

    if (isFinished && m_startAttribute == StopOnFinished) {
        stop();
        return;
    }

    m_currentPix = m_pixGroup.value(idx);
    update();
}

void SequenceFrame::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter p(this);
    p.drawPixmap(rect(), m_currentPix);
}
