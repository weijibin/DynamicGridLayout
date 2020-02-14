#ifndef OTHERSECTIONWIDGET_H
#define OTHERSECTIONWIDGET_H

#include <QWidget>
#include <QFrame>

namespace Ui {
class OtherSectionWidget;
}

class OtherSectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OtherSectionWidget(QWidget *parent = nullptr);
    ~OtherSectionWidget();

    void setStatus(int status);
    void setCurText(const QString& str);

signals:
    void sigClicked();

protected:
    virtual void paintEvent(QPaintEvent* event) override;
    virtual bool eventFilter(QObject *obj, QEvent *ev) override;
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

private:
    void initUi();
    void updateSizeByContent();

private:
    Ui::OtherSectionWidget *ui;
    int                     m_status = 2;  // 1: normal  2: inReading
};

#endif // OTHERSECTIONWIDGET_H
