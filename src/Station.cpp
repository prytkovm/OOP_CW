#include "Station.h"
#include "User.h"
#include <QObject>
#include <vector>
#include <algorithm>


Station::Station(std::vector<User*> &usersList, QObject *parent) : QObject(parent), users(usersList) {
    for (auto &user: users) {
        QObject::connect(user,
                &User::call,
                [&user, this](const std::string &receiverNumber) { connect(user, receiverNumber); });
        QObject::connect(user,
                         &User::dropCall,
                         [&user, this]() { disconnect(user); });
        QObject::connect(user,
                         &User::acceptCall,
                         this,
                         &Station::checkLimit);
        QObject::connect(this,
                         &Station::limitExceeded,
                         user,
                         &User::limitExceeded);
        QObject::connect(this,
                        &Station::callAllowed,
                        user,
                        &User::callAllowed);
    }
}

User *Station::getUserByNumber(const std::string &number) {
    for (auto &user: users) {
        if (user->getNumber() == number) {
            return user;
        }
    }
    throw std::runtime_error("Invalid number.");
}

void Station::connect(User *caller, const std::string &receiverNumber) {
    auto receiver = getUserByNumber(receiverNumber);
    if (receiver == nullptr) return;
    auto receiverState = receiver->getState();
    if (receiverState == AllowedStates::TALK) return;

    QObject::connect(caller,
            &User::sendMessage,
            receiver,
            &User::receivedMessage);
    QObject::connect(receiver,
                     &User::sendMessage,
                     caller,
                     &User::receivedMessage);
    caller->setState(AllowedStates::TALK);
    receiver->setState(AllowedStates::CALL);
    auto usersPair = std::make_pair(caller, receiver);
    connectedUsers.push_back(usersPair);
}

void Station::disconnect(User *caller) {
    for (auto &usersPair: connectedUsers) {
        auto firstUser = usersPair.first;
        auto secondUser = usersPair.second;
        if (firstUser->getNumber() == caller->getNumber() || secondUser->getNumber() == caller->getNumber()) {
            QObject::disconnect(firstUser,
                             &User::sendMessage,
                             secondUser,
                             &User::receivedMessage);
            QObject::disconnect(secondUser,
                             &User::sendMessage,
                             firstUser,
                             &User::receivedMessage);
            firstUser->setState(AllowedStates::INACTIVE);
            secondUser->setState(AllowedStates::INACTIVE);
            auto id = std::find(connectedUsers.begin(), connectedUsers.end(), usersPair);
            if (id != connectedUsers.end()) {
                connectedUsers.erase(id);
            }
        }
    }
}

void Station::checkLimit() {
    if (connectedUsers.size() == connectionsLimit) {
        emit limitExceeded();
    } else {
        emit callAllowed();
    }
}
