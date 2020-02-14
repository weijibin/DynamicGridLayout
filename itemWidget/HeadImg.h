#ifndef HEADIMG_H
#define HEADIMG_H

#include <QWidget>
#include <QPixmap>
#include <QPen>
#include <QTimeLine>
#include <QFont>


class HeadImg : public QWidget
{
    Q_OBJECT
public:
    HeadImg(QWidget*parent = nullptr);
    void setImgUrl(QString url);
    void startAniTimer(int second);
    void endAniTimer();
signals:
    void sigTimeOut();
protected slots:
    void onFrameChanged(int frame);
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    void setRemoteImg(const QString & url);
private:
    QPixmap m_pix;

    QString m_imgName;
    QString m_catchDir;

    QTimeLine*  m_timeLine  = nullptr;
    int         m_ringWidth = 4;     // 使用动画功能时需要调整大小
    int         m_angle     = 90;

    int         m_second    = 0;
    QFont       m_font;
    QPoint      m_textPos;
};

#endif // TEACHERHEADIMG_H
