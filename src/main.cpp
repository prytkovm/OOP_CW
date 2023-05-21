#include <QApplication>
#include "MainWindow.h"
#include "User.h"
#include "UserCard.h"
#include "Station.h"
#include <vector>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto w = new MainWindow();
    w->show();
    std::vector<User*> users;
    for (auto i = 0; i < 10; i++) {
        auto user = new User(&a);
        auto card = new UserCard(user, w);
        w->addUserCard(card);
        users.push_back(user);
    }
    auto s = new Station(users);
    return QApplication::exec();
}
