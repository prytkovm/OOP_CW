#include "User.h"
#include <iostream>

int User::objectsCount = 0;

User::User(QObject *parent) : QObject(parent) {
    setState(AllowedStates::INACTIVE);
    number = generateNumber();
    User::objectsCount++;
    connect(this,
            &User::acceptCall,
            this,
            &User::onAcceptCall_received);
    connect(this,
            &User::dropCall,
            this,
            &User::onDropCall_received);
    connect(this,
            &User::callAccepted,
            this,
            &User::onCallAccepted);
}

std::string User::getNumber() const {
    return number;
}

int User::getState() const {
    return state;
}

void User::setState(int newState){
    state = newState;
    emit stateChanged(state);
}


std::string User::generateNumber() {
    using std::string, std::to_string;

    auto strNumber = to_string(User::objectsCount);
    auto result = string((numberLength - strNumber.length()), '0') + strNumber;

    return result;
}

void User::onAcceptCall_received() {
    if (getState() == AllowedStates::CALL) {
        setState(AllowedStates::TALK);
    }
    else {
        setState(AllowedStates::READY);
    }
}

void User::onDropCall_received() {
    setState(AllowedStates::INACTIVE);
}

void User::onCallAccepted() {
    setState(AllowedStates::TALK);
}

