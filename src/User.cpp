#include "User.h"
#include <iostream>

int User::objectsCount = 0;

User::User(QObject *parent) : QObject(parent) {
    state = AllowedStates::READY;
    number = generateNumber();
    User::objectsCount++;
//    connect(,
//            &User::call,
//            this,
//            &User::onCall_received);
}

void User::setNumber(const std::string &newNumber) {
    number = newNumber;
}

std::string User::getNumber() const {
    return number;
}

int User::getState() const{
    return state;
}

void User::setState(int newState){
    state = newState;
}


std::string User::generateNumber() {
    using std::string, std::to_string;

    auto strNumber = to_string(User::objectsCount);
    auto result = std::string((numberLength - strNumber.length()), '0') + strNumber;

    return result;
}

void User::onCall_received(const std::string &s) {
    std::cerr << "Call from: " << getNumber() << " to: " << s << std::endl;
}
