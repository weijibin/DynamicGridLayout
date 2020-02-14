#ifndef SELFSECTIONWIDGET_H
#define SELFSECTIONWIDGET_H

#include <QWidget>

namespace Ui {
class SelfSectionWidget;
}

class SelfSectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelfSectionWidget(QWidget *parent = nullptr);
    ~SelfSectionWidget();

    void setStatus(int status);
    void setCurText(const QString &str,const QString& originText);

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
    Ui::SelfSectionWidget *ui;
    int                    m_status = 2;  // 1: normal  2: inReading
    QString                m_originText;
};

#endif // SELFSECTIONWIDGET_H
