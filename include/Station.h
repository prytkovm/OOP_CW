#ifndef CW_STATION_H
#define CW_STATION_H

#include <QObject>
#include <vector>
#include "User.h"


const int connectionsLimit = 4;


class Station : public QObject {
    Q_OBJECT

    public:
    explicit Station(std::vector<User*> &usersList, QObject *parent=nullptr);
    ~Station() override = default;

    private:
    std::vector<User*> &users;
    std::vector<std::pair<User*, User*>> connectedUsers;
    User *getUserByNumber(const std::string &number);

    private slots:
    void connect(User *caller, const std::string &receiverNumber);
    void disconnect(User *caller);
    void checkLimit();

    signals:
    void limitExceeded();
    void callAllowed();

};


#endif