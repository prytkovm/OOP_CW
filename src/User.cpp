#include "User.h"
#include <iostream>

int User::objectsCount = 0;

User::User(QObject *parent) : QObject(parent) {
    state = AllowedStates::READY;
    number = generateNumber();
    User::objectsCount++;
}

void User::setNumber(const std::string &newNumber) {
    number = newNumber;
}

std::string User::getNumber() const {
    return number;
}

std::string User::generateNumber() {
    using std::string, std::to_string;

    auto strNumber = to_string(User::objectsCount);
    auto result = std::string((numberLength - strNumber.length()), '0') + strNumber;

    return result;
}
