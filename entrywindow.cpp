// entrywindow.cpp
#include "entrywindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "registrationwindow.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

EntryWindow::EntryWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Вход в систему");
    setFixedSize(400, 300);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");     // Адрес сервера базы данных
    db.setPort(3306);                // Порт
    db.setDatabaseName("sonyahelp_db"); // Имя базы данных
    db.setUserName("root");          // Имя пользователя
    db.setPassword("tobishka12");
    if (!db.open()) {
        qDebug() << "Не удалось подключиться к базе данных:" << db.lastError().text();
        ;
    }
    qDebug() << "Подключение к базе данных успешно";

    // Поле для ввода логина
    QLabel *usernameLabel = new QLabel("Логин:  ", this);
    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setPlaceholderText("Введите логин");
    usernameLineEdit->setMinimumHeight(50);

    // Поле для ввода пароля
    QLabel *passwordLabel = new QLabel("Пароль:", this);
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setPlaceholderText("Введите пароль");
    passwordLineEdit->setMinimumHeight(50);
    passwordLineEdit->setEchoMode(QLineEdit::Password); // Скрывает текст пароля

    // Кнопка входа
    loginButton = new QPushButton("Войти", this);

    // Кнопка регистрации
    QLabel *registerLabel = new QLabel("Если у вас нет аккаунта:", this);
    registerButton = new QPushButton("Регистрация", this);
    registerButton->setMinimumHeight(50);

    // Создаем компоновку
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Компоновка для логина
    QHBoxLayout *usernameLayout = new QHBoxLayout;
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameLineEdit);
    mainLayout->addLayout(usernameLayout);

    // Компоновка для пароля
    QHBoxLayout *passwordLayout = new QHBoxLayout;
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordLineEdit);
    mainLayout->addLayout(passwordLayout);

    // Добавляем кнопку входа и кнопку регистрации
    mainLayout->addWidget(loginButton);
    QHBoxLayout *registerLayout = new QHBoxLayout;
    registerLayout->addWidget(registerLabel);
    registerLayout->addWidget(registerButton);
    mainLayout->addLayout(registerLayout);

    connect(registerButton, &QPushButton::clicked, this, &EntryWindow::openRegistrationWindow);

    setLayout(mainLayout);
}
void EntryWindow::openRegistrationWindow()
{
    registrationWindow = new RegistrationWindow(dbManager, this);
    registrationWindow->show();
}
