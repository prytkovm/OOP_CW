#include "Station.h"
#include "User.h"


Station::Station(std::vector<User*> &usersList, QObject *parent) : QObject(parent), users(usersList) {
    for (auto &user: users) {
        QObject::connect(user,
                         &User::call,
                         [&user, this](const std::string &receiverNumber) { processCall(user, receiverNumber); });
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
                        &Station::callNotAllowed,
                        user,
                        &User::callNotAllowed);
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


void Station::processCall(User *caller, const std::string &receiverNumber) {
    auto receiver = getUserByNumber(receiverNumber);
    auto receiverState = receiver->getState();
    if (receiverState != AllowedStates::INACTIVE) {
        emit callNotAllowed();
        return;
    }
    connect(caller, receiver);
}

void Station::disconnect(User *caller) {
    for (auto &usersPair: connectedUsers) {
        auto firstUser = usersPair.first;
        auto secondUser = usersPair.second;
        bool firstFound = (firstUser->getNumber() == caller->getNumber());
        bool secondFound = (secondUser->getNumber() == caller->getNumber());
        if (firstFound || secondFound) {
            QObject::disconnect(firstUser,
                             &User::sendMessage,
                             secondUser,
                             &User::receivedMessage);
            QObject::disconnect(secondUser,
                             &User::sendMessage,
                             firstUser,
                             &User::receivedMessage);

            QObject::disconnect(secondUser,
                             &User::acceptCall,
                             firstUser,
                             &User::callAccepted);
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
    }
}

void Station::connect(User *caller, User *receiver) {
    QObject::connect(caller,
                     &User::sendMessage,
                     receiver,
                     &User::receivedMessage);
    QObject::connect(receiver,
                     &User::sendMessage,
                     caller,
                     &User::receivedMessage);
    QObject::connect(receiver,
                     &User::acceptCall,
                     caller,
                     &User::callAccepted);
    caller->setState(AllowedStates::CALL);
    receiver->setState(AllowedStates::CALL);
    auto usersPair = std::make_pair(caller, receiver);
    connectedUsers.push_back(usersPair);
}
