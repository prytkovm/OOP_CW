#include "UserCard.h"
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QRegularExpression>


UserCard::UserCard(User &userModel, QWidget *parent) : QWidget(parent), ui(new Ui::UserCard) {
    ui->setupUi(this);
    ui->selfNumber->setText(QString::fromStdString(userModel.getNumber()));
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
    connect(this,
            &UserCard::call,
            &userModel,
            &User::call);
    connect(this,
            &UserCard::acceptCall,
            &userModel,
            &User::acceptCall);
    connect(this,
            &UserCard::dropCall,
            &userModel,
            &User::dropCall);
    auto validator = new QRegularExpressionValidator(QRegularExpression("^[0-9]{4}$"), this);
    ui->subscriberNumber->setValidator(validator);
}

UserCard::~UserCard() {
    delete ui;
}

void UserCard::onCallButton_clicked() {
    auto number = ui->subscriberNumber->text().toStdString();
    if (number.length() != numberLength || number == ui->selfNumber->text().toStdString()) {
        auto msgBox = new QMessageBox(this);
        msgBox->setText("Неправильно набран номер.");
        msgBox->show();
        return;
    }
    emit call(number);
    ui->callButton->setEnabled(false);
    ui->talkText->setEnabled(true);
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
    ui->callButton->setEnabled(true);
    ui->subscriberNumber->setEnabled(true);
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
    ui->subscriberNumber->setEnabled(false);
    ui->talkText->setEnabled(false);
}

void UserCard::onCallText_changed() {
    auto newText = ui->talkText->toPlainText().toStdString();
    emit textChanged(newText);
}

void UserCard::setStatus(const std::string &newStatus) {
    ui->currentStatus->setText(QString::fromStdString(newStatus));
}
