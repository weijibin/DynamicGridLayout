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
private:
    Ui::Item *ui;
};

#endif // ITEM_H
