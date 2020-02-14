#ifndef STARSWIDGET_H
#define STARSWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>

class StarsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StarsWidget(QWidget *parent = nullptr);
    void setStarNum(int num);
private:
    void initUi();
    void clearLayout(QLayout *layout);
private:
    QHBoxLayout * m_layout = nullptr;
    int           m_starNum = -1;
};

#endif // STARSWIDGET_H
