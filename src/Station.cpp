#include "Station.h"


Station::Station(std::vector<User> &usersList, QObject *parent) : QObject(parent), users(usersList) {
    for (auto &user: usersList) {
        ;
    }
}
