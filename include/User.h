#ifndef CW_USER_H
#define CW_USER_H

#include <QObject>
#include <string>


const int numberLength = 4;


class User : private QObject {
    Q_OBJECT

    public:
    explicit User(QObject *parent=nullptr);
    ~User() override = default;
    std::string getNumber() const;
    void setNumber(const std::string &newNumber);

    private:
    enum AllowedStates {
        READY,
        CALL,
        TALK
    };
    int state;
    std::string number;
    static int objectsCount;
    static std::string generateNumber();

//    signals:
//    void call(const std::string &numberTo);
//
//    public slots:
//    void acceptCall(const std::string &numberFrom);

};

#endif
