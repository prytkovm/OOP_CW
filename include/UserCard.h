#ifndef CW_USERCARD_H
#define CW_USERCARD_H

#include "ui_UserCard.h"
#include "User.h"
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {
    class UserCard;
}
QT_END_NAMESPACE


class UserCard : public QWidget {
    Q_OBJECT

    public:
    explicit UserCard(User *userModel, QWidget *parent=nullptr);
    ~UserCard() override;
    void setStatus(const std::string &newStatus);

    private:
    int currentState;
    Ui::UserCard *ui;

    private slots:
    void onCallButton_clicked();
    void onAcceptCallButton_clicked();
    void onDropCallButton_clicked();
    void onCallText_changed();
    void onState_changed(int newState);
    void onMessageReceived(const std::string &message);
    void onLimitExceeded();
    void onCallNotAllowed();

    signals:
    void call(const std::string &subscriberNumber);
    void sendMessage(const std::string &newText);
    void acceptCall();
    void dropCall();

};


#endif
