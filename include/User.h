#ifndef CW_USER_H
#define CW_USER_H

#include <QObject>
#include <string>


const int numberLength = 11;


class User : private QObject {
    Q_OBJECT

    public:
    User(QObject *parent=nullptr);
    ~User() override;
    std::string getNumber() const;
    void setNumber(std::string newNumber);

    private:
    static int objectsCount;
    std::string number;


};


#endif
