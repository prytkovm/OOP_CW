#include "User.h"


User::User(QObject *parent) : QObject(parent) {
    state = AllowedStates::READY;
    objectsCount++;
}

void User::setNumber(const std::string &newNumber) {
    number = newNumber;
}

std::string User::getNumber() const {
    return number;
}

std::string User::numberFromInt(int number) {
    auto result = std::string("0", numberLength);

}
