#include "Station.h"
#include "User.h"
#include <QObject>
#include <vector>

Station::Station(std::vector<User> &usersList, QObject *parent) : QObject(parent), users(usersList) {

}

void Station::setConnection(User caller1, std::string number) {
    size_t i;
    auto usersListSize = users.size();
    for(i = 0;i<usersListSize;i++)
    {
        if (number.compare(users[i].getNumber()) == 0)
        {
            break;
        }
        else if (i == (usersListSize - 1))
        {
            throw std::runtime_error("Invalid number");
        }
    }
    connect(caller1,SIGNAL(),users[i],SLOT());
    connect(users[i],SIGNAL(),users[i],SLOT());
    if (caller1.getState() == AllowedStates::READY)
    {
        if (users[i].getState() == AllowedStates::INACTIVE)
        {

        }
        if (users[i].getState() == AllowedStates::READY)
        {

        }
        if (users[i].getState() == AllowedStates::TALK)
        {

        }
    }
    else{

    }
}