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
    connect(this,
            &User::callDropped,
            this,
            &User::onCallDropped);
}

void User::setNumber(const std::string &newNumber) {
    number = newNumber;
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
    auto result = std::string((numberLength - strNumber.length()), '0') + strNumber;

    return result;
}

void User::onAcceptCall_received() {
    if(getState() == AllowedStates::CALL) {
        setState(AllowedStates::TALK);
    }
    else {
        setState(AllowedStates::READY);
    }
}

void User::onDropCall_received() {
    setState(AllowedStates::INACTIVE);
    std::cerr << "I dropped call" << std::endl;
}

void User::onCallAccepted() {
    setState(AllowedStates::TALK);
    std::cerr << "Call accepted by another her" << std::endl;
}

void User::onCallDropped() {
    setState(AllowedStates::INACTIVE);
    std::cerr << "Call dropped by another her" << std::endl;
}

