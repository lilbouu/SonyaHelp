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
    QString surname = surnameEdit->text().trimmed();
    QString name = nameEdit->text().trimmed();
    QString patronymic = patronymicEdit->text().trimmed();
    QDate birthDate = birthDateEdit->date();
    QString citizenship = citizenshipComboBox->currentText();
    QString series = seriesEdit->text().trimmed();
    QString number = numberEdit->text().trimmed();
    QString username = extraField1->text().trimmed();
    QString password = extraField2->text();
    QString passwordRepeat = extraField22->text();

    // Проверка на пустые обязательные поля
    if (surname.isEmpty() || name.isEmpty() || series.isEmpty() || number.isEmpty() || username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все обязательные поля.");
        return;
    }

    // Проверка на заглавную букву в Фамилии, Имени и Отчестве
    if (!surname[0].isUpper() || !name[0].isUpper() || (!patronymic.isEmpty() && !patronymic[0].isUpper())) {
        QMessageBox::warning(this, "Ошибка", "Фамилия, Имя и Отчество (если указано) должны начинаться с заглавной буквы.");
        return;
    }

    // Проверка на числовые значения в Серии и Номере
    bool seriesIsNumeric, numberIsNumeric;
    int seriesInt = series.toInt(&seriesIsNumeric);
    int numberInt = number.toInt(&numberIsNumeric);
    if (!seriesIsNumeric || !numberIsNumeric) {
        QMessageBox::warning(this, "Ошибка", "Поля \"Серия\" и \"Номер\" должны содержать только цифры.");
        return;
    }

    // Проверка совпадения паролей
    if (password != passwordRepeat) {
        QMessageBox::warning(this, "Ошибка", "Пароли не совпадают. Пожалуйста, введите пароль еще раз.");
        return;
    }

    // Проверка уникальности логина
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM user_credentials WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Ошибка при проверке уникальности логина: " + query.lastError().text());
        return;
    }

    if (query.next() && query.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Ошибка", "Пользователь с таким логином уже существует. Пожалуйста, выберите другой логин.");
        return;
    }

    // Хеширование пароля
    QString passwordHash = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());

    // Добавляем пользователя в таблицу customers и получаем ID
    int customerId = dbManager->addCustomer(surname, name, patronymic, birthDate, seriesInt, numberInt, citizenship);
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


