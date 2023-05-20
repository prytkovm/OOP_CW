#include "UserCard.h"
#include "User.h"
#include <QMessageBox>


UserCard::UserCard(const std::string &number, QWidget *parent) : QWidget(parent), ui(new Ui::UserCard) {
    ui->setupUi(this);
    ui->selfNumber->setText(QString::fromStdString(number));
    setStatus("");
    connect(ui->acceptCall,
            &QPushButton::clicked,
            this,
            &UserCard::onAcceptCallButton_clicked);
    connect(ui->dropCall,
            &QPushButton::clicked,
            this,
            &UserCard::onDropCallButton_clicked);
    connect(ui->callButton,
            &QPushButton::clicked,
            this,
            &UserCard::onCallButton_clicked);
}

UserCard::~UserCard() {
    delete ui;
}

void UserCard::onCallButton_clicked() {
    if (ui->subscriberNumber->text().length() != numberLength) {
        auto msgBox = new QMessageBox();
        msgBox->setText("Неправильно набран номер.");
        msgBox->show();
        delete msgBox;
        return;
    }
    auto number = ui->subscriberNumber->text().toStdString();
    emit call(number);
    ui->callButton->setEnabled(false);
}

void UserCard::onAcceptCallButton_clicked() {
    ui->talkText->clear();
    connect(ui->talkText,
            &QTextEdit::textChanged,
            this,
            &UserCard::onCallText_changed);
    emit acceptCall();
    ui->acceptCall->setEnabled(false);
    ui->dropCall->setEnabled(true);
}

void UserCard::onDropCallButton_clicked() {
    ui->talkText->clear();
    disconnect(ui->talkText,
               &QTextEdit::textChanged,
               this,
               &UserCard::onCallText_changed);
    emit dropCall();
    ui->acceptCall->setEnabled(true);
    ui->dropCall->setEnabled(false);
    ui->callButton->setEnabled(true);
}

void UserCard::onCallText_changed() {
    auto newText = ui->talkText->toPlainText().toStdString();
    emit textChanged(newText);
}

void UserCard::setStatus(const std::string &newStatus) {
    ui->currentStatus->setText(QString::fromStdString(newStatus));
}
