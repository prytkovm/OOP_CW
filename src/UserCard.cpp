#include "UserCard.h"
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QRegularExpression>


UserCard::UserCard(User *userModel, QWidget *parent) : QWidget(parent), ui(new Ui::UserCard) {
    ui->setupUi(this);
    ui->selfNumber->setText(QString::fromStdString(userModel->getNumber()));
    currentStatus = AllowedStates::INACTIVE;
    setStatus("Трубка повешена");
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
            userModel,
            &User::call);
    connect(this,
            &UserCard::acceptCall,
            userModel,
            &User::acceptCall);
    connect(this,
            &UserCard::dropCall,
            userModel,
            &User::dropCall);
    connect(userModel,
            &User::stateChanged,
            this,
            &UserCard::onState_changed);
    connect(userModel,
            &User::receivedMessage,
            this,
            &UserCard::onMessageReceived);
    connect(this,
            &UserCard::sendMessage,
            userModel,
            &User::sendMessage);
    connect(userModel,
            &User::limitExceeded,
            this,
            &UserCard::onLimitExceeded);
//    connect(userModel,
//            &User::callAllowed,
//            this,
//            &UserCard::onCallAllowed);

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
    emit sendMessage(newText);
}

void UserCard::setStatus(const std::string &newStatus) {
    ui->currentStatus->setText(QString::fromStdString(newStatus));
}

void UserCard::onState_changed(int newState) {
    switch (newState) {
        case AllowedStates::INACTIVE:
            currentStatus = newState;
            setStatus("Трубка повешена");
        case AllowedStates::READY:
            currentStatus = newState;
            setStatus("Готов");
            break;
        case AllowedStates::CALL:
            currentStatus = newState;
            setStatus("Вызов");
            break;
        case AllowedStates::TALK:
            currentStatus = newState;
            setStatus("Разговор");
            break;
        default:
            break;
    }
}

void UserCard::onMessageReceived(const std::string &message) {
    blockSignals(true);
    ui->talkText->setText(QString::fromStdString(message));
    blockSignals(false);
}

void UserCard::onLimitExceeded() {
    setStatus("Занято");
}


//void UserCard::onCallAllowed() {
//    setStatus()
//}
