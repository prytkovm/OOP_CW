#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::addUserCard(UserCard *newCard) {
    ui->scrollAreaWidgetContents->layout()->addWidget(newCard);
}
