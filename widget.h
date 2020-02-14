#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QEventLoop>

namespace Ui {
class Widget;
}

class Dialog;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void initUi();

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QEventLoop *m_loop=nullptr;

    Dialog * m_dlg1 = nullptr;
    Dialog * m_dlg2 = nullptr;
};

#endif // WIDGET_H
