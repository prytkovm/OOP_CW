#ifndef CW_MAINWINDOW_H
#define CW_MAINWINDOW_H

#include "ui_MainWindow.h"
#include "UserCard.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
    explicit MainWindow(QWidget *parent=nullptr);
    ~MainWindow() override;
    void addUserCard(UserCard *newCard);

    private:
    Ui::MainWindow *ui;

};


#endif
