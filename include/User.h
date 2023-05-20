#ifndef CW_USER_H
#define CW_USER_H

#include <QObject>
#include <string>


const int numberLength = 4;

enum AllowedStates {
    INACTIVE,
    READY,
    CALL,
    TALK
};

class User : public QObject {
    Q_OBJECT

    public:
    explicit User(QObject *parent=nullptr);
    ~User() override = default;
    std::string getNumber() const;
    void setNumber(const std::string &newNumber);

    private:
    int state;
    std::string number;
    static int objectsCount;
    static std::string generateNumber();

    public slots:
    void onCall_received(const std::string &s);

    signals:
    void call(const std::string &subscriberNumber);
    void acceptCall();
    void dropCall();
    void sendMessage(const std::string &message);
    void receivedMessage(const std::string &message);

};

#endif
