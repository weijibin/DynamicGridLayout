#ifndef ITEM_H
#define ITEM_H

#include <QWidget>

namespace Ui {
class Item;
}

class Item : public QWidget
{
    Q_OBJECT

public:
    explicit Item(QWidget *parent = 0);
    ~Item();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
private:
    void setStatus(int status);
private:
    Ui::Item *ui;
    int  m_status;
};

#endif // ITEM_H
