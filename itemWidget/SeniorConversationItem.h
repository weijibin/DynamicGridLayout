#ifndef SENIORCONVERSATIONITEM_H
#define SENIORCONVERSATIONITEM_H

#include <QWidget>
#include "RolePlayDefine.h"

namespace Ui {
class SeniorConversationItem;
}

class SeniorConversationItem : public QWidget
{
    Q_OBJECT

public:
    explicit SeniorConversationItem(bool isPrimary = false,QWidget *parent = nullptr);
    ~SeniorConversationItem();

    void setInfo(const SpeechInfo& info);
    void setStatus(int status);
    void updateUiByInfo();

    void startSelfReadTimer(int time);
    void endSelfReadTimer();
signals:
    void sigItemClicked(int index);
    void sigInReadingTimeOut(int index);
    void sigPraiseClicked(int index);
private:
    void initUi();
    void initConnections();
private:
    Ui::SeniorConversationItem *ui;
    SpeechInfo  m_info;
    bool        m_isPrimary = false;
};

#endif // SENIORCONVERSATIONITEM_H
