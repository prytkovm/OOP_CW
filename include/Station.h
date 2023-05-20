#ifndef CW_STATION_H
#define CW_STATION_H

#include <QObject>
#include <vector>
#include "User.h"


const int connectionsLimit = 4;


class Station : private QObject {
    Q_OBJECT

    public:
    explicit Station(std::vector<User> &usersList, QObject *parent=nullptr);
    ~Station() override = default;

    private:
    std::vector<User> &users;
    std::vector<User> talkingUsers;

    private slots:



};


#endif