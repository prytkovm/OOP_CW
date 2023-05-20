#ifndef CW_STATION_H
#define CW_STATION_H

#include <QObject>
#include <vector>
#include "User.h"


class Station : private QObject {
    Q_OBJECT

    public:
    explicit Station(std::vector<User> &usersList, QObject *parent=nullptr);

    private:
    std::vector<User> &users;

};


#endif