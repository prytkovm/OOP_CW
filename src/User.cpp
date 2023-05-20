#include "User.h"

int User::objectsCount;

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
    auto result = std::string("0", (numberLength - strNumber.length()));

    return result + strNumber;
}
