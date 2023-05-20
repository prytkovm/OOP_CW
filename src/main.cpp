#include <QApplication>
#include "MainWindow.h"
#include "User.h"
#include "UserCard.h"
#include <iostream>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto w = new MainWindow();
    w->show();
    for (auto i = 0; i < 10; i++) {
        auto user = new User();
        auto card = new UserCard(user->getNumber());
        w->addUserCard(card);
//        delete card;
        delete user;
    }
    return QApplication::exec();
}
