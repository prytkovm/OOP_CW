#include <QApplication>
#include "MainWindow.h"
#include "User.h"
#include <iostream>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto w = new MainWindow();
    w->show();
    for (auto i = 0; i < 10; i++) {
        auto user = new User();
        std::cout << user->getNumber() << std::endl;
        delete user;
    }
    return QApplication::exec();
}
