// registrationwindow.cpp
#include "registrationwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QSpacerItem>
#include <QCryptographicHash>
#include <QSqlDatabase>
RegistrationWindow::RegistrationWindow(DatabaseManager* dbManager, QWidget *parent)
    : QDialog(parent), dbManager(dbManager)
{
    setWindowTitle("Регистрация");
    setFixedSize(400, 600);

    // Инициализация полей ввода
    surnameEdit = new QLineEdit(this);
    nameEdit = new QLineEdit(this);
    patronymicEdit = new QLineEdit(this);
    birthDateEdit = new QDateEdit(this);
    birthDateEdit->setCalendarPopup(true);
    birthDateEdit->setDisplayFormat("dd.MM.yyyy");

    citizenshipComboBox = new QComboBox(this);
    citizenshipComboBox->addItems({"Россия", "Казахстан", "Беларусь", "Украина"});

    seriesEdit = new QLineEdit(this);
    numberEdit = new QLineEdit(this);

    // Дополнительные поля
    extraField1 = new QLineEdit(this);
    extraField2 = new QLineEdit(this);
    extraField2->setEchoMode(QLineEdit::Password);
    extraField22 = new QLineEdit(this);
    extraField22->setEchoMode(QLineEdit::Password);

    registerButton = new QPushButton("Зарегистрироваться", this);

    // Создаем форму и добавляем поля
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Фамилия:", surnameEdit);
    formLayout->addRow("Имя:", nameEdit);
    formLayout->addRow("Отчество (при наличии):", patronymicEdit);
    formLayout->addRow("Дата рождения:", birthDateEdit);
    formLayout->addRow("Гражданство:", citizenshipComboBox);
    formLayout->addRow("Серия:", seriesEdit);
    formLayout->addRow("Номер:", numberEdit);
    QSpacerItem *verticalSpacer = new QSpacerItem(0, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);
    formLayout->addItem(verticalSpacer);
    formLayout->addRow("Придумайте Логин:", extraField1);
    formLayout->addRow("Придумайте Пароль:", extraField2);
    formLayout->addRow("Повторите пароль:", extraField22);

    // Основной компоновщик
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(registerButton);
    connect(registerButton, &QPushButton::clicked, this, &RegistrationWindow::registerUser);


    setLayout(mainLayout);
}
void RegistrationWindow::registerUser() {
    QString surname = surnameEdit->text();
    QString name = nameEdit->text();
    QString patronymic = patronymicEdit->text();
    QDate birthDate = birthDateEdit->date();
    QString citizenship = citizenshipComboBox->currentText();
    int series = seriesEdit->text().toInt();
    int number = numberEdit->text().toInt();
    QString username = extraField1->text();
    QString password = extraField2->text();

    // Хеширование пароля
    QString passwordHash = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());

    // Добавляем пользователя в таблицу customers и получаем ID
    int customerId = dbManager->addCustomer(surname, name, patronymic, birthDate, series, number, citizenship);
    if (customerId == -1) {
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить пользователя в базу данных.");
        return;
    }

    // Добавляем учетные данные в таблицу user_credentials
    if (!dbManager->addUserCredentials(customerId, username, passwordHash)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить учетные данные.");
    } else {
        QMessageBox::information(this, "Успех", "Регистрация прошла успешно!");
        accept();
    }
}

