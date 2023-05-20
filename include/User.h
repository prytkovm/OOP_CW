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
    static int objectsCount;
    int state;
    std::string number;

    static std::string numberFromInt(int number);

};


#endif
