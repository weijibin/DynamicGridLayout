#ifndef SEQUENCEFRAME_H
#define SEQUENCEFRAME_H

#include <QWidget>
#include <QPaintEvent>

class SequenceFrame : public QWidget
{
    Q_OBJECT

public:
    enum StartAttribute
    {
        StopOnFinished = 1,
        KeepStart = 2,
    };
public:
    explicit SequenceFrame(QWidget *parent = nullptr);
    ~SequenceFrame() Q_DECL_OVERRIDE;

    void setFramePath(const QString &path, const QString &baseName);

    void clear();
    void start(const StartAttribute &attribute);
    void stop();

public slots:
    void onTimeOut();

protected :
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    QVector<QPixmap>    m_pixGroup;
    QTimer             *m_timer;
    int                 m_pixIdx;
    QPixmap             m_currentPix;
    StartAttribute      m_startAttribute;
};

#endif // SEQUENCEFRAME_H
