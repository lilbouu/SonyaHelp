#include "mainwindow.h"
#include "aboutdialog.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QMenu>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

MainWindow::MainWindow(int id_customers, QWidget *parent) : QWidget(parent),id_customers(id_customers), profileWindow(nullptr) {
    setMinimumSize(1080, 720);
    setWindowTitle("SonyaHelp");
    // QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    // db.setHostName("localhost");     // Адрес сервера базы данных
    // db.setPort(3306);                // Порт
    // db.setDatabaseName("sonyahelp_db"); // Имя базы данных
    // db.setUserName("root");          // Имя пользователя
    // db.setPassword("tobishka12");    // Пароль

    // if (!db.open()) {
    //     qDebug() << "Не удалось подключиться к базе данных:" << db.lastError().text();
    //     ;
    // }
    // qDebug() << "Подключение к базе данных успешно";
    // Верхняя панель

    QWidget *titleBar = new QWidget(this);
    titleBar->setFixedHeight(100);
    QHBoxLayout *titleLayout = new QHBoxLayout(titleBar);

    // Логотип
    QLabel *imageLabel = new QLabel(titleBar);
    QPixmap leftImage(":/images/logotip.svg");
    imageLabel->setPixmap(leftImage.scaled(60, 60, Qt::KeepAspectRatio));
    imageLabel->setFixedSize(60, 60);
    titleLayout->addWidget(imageLabel);
    titleLayout->addStretch();

    // Заголовок
    QLabel *titleLabel = new QLabel("SonyaHelp", titleBar);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("Arial", 16, QFont::Bold));
    titleLayout->addWidget(titleLabel);
    titleLayout->addStretch();

    // Кнопка профиля
    HoverableToolButton *iconButton = new HoverableToolButton(titleBar);
    iconButton->setIcon(QIcon(":/images/person.svg"));
    iconButton->setToolTip("Click me");
    iconButton->setFixedSize(70, 70);
    titleLayout->addWidget(iconButton);

    QMenu *menu = new QMenu(iconButton);
    QAction *profileAction = new QAction("Мой Профиль", menu);
    QAction *helpAction = new QAction("О нас", menu);
    QAction *exitAction = new QAction("Выход", menu);

    menu->addAction(profileAction);
    menu->addAction(helpAction);
    menu->addAction(exitAction);

    // Обработчики для действий в меню
    QObject::connect(profileAction, &QAction::triggered, this, &MainWindow::openProfile); // Исправлено
    QObject::connect(helpAction, &QAction::triggered, []() {
        qDebug() << "Открыть помощь!";
        // Здесь можно добавить логику для открытия окна помощи
    });
    QObject::connect(exitAction, &QAction::triggered, [&]() {
        qDebug() << "Выход из приложения!";
        QApplication::quit(); // Закрываем приложение
    });

    // Показываем меню при наведении курсора на иконку
    QObject::connect(iconButton, &HoverableToolButton::hovered, [menu]() {

        menu->exec(QCursor::pos());
    });
    QObject::connect(menu, &QMenu::aboutToHide, [menu]() {
        menu->hide();
    });
    QObject::connect(helpAction, &QAction::triggered, this, [this]() {
        AboutDialog aboutDialog(this); // Создаем диалог
        aboutDialog.exec();            // Показываем как модальное окно
    });


    // Кнопки
    QPushButton *createRequestBtn = new QPushButton("Создать обращение", this);
    QPushButton *myRequestsBtn = new QPushButton("Мои заявки", this);
    QFont buttonFont("Arial", 16, QFont::Bold);
    createRequestBtn->setFont(buttonFont);
    myRequestsBtn->setFont(buttonFont);
    createRequestBtn->setMinimumSize(350, 120);
    createRequestBtn->setMaximumSize(400, 150);
    myRequestsBtn->setMinimumSize(350, 120);
    myRequestsBtn->setMaximumSize(400, 150);

    QVBoxLayout *buttonsLayout = new QVBoxLayout;
    buttonsLayout->addWidget(createRequestBtn);
    buttonsLayout->addWidget(myRequestsBtn);
    buttonsLayout->setAlignment(Qt::AlignCenter);

    // Главный компоновщик
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleBar);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addStretch();
    QSqlQuery query;
    query.prepare(R"(
        SELECT surname, name, middlename, date, series, number, сitizenship
        FROM customers
        WHERE id_customers = :id_customers
    )");
    query.bindValue(":id_customers", id_customers);

    QString surname, name, middlename, birthDate, сitizenship, series, number;

    if (query.exec() && query.next()) {
        surname = query.value("surname").toString();
        name = query.value("name").toString();
        middlename = query.value("middlename").toString();
        birthDate = query.value("date").toDate().toString("dd.MM.yyyy");
        series = query.value("series").toString();
        number = query.value("number").toString();
        сitizenship = query.value("сitizenship").toString();
    } else {
        qDebug() << "Ошибка при загрузке данных пользователя:" << query.lastError().text();
    }

    setLayout(mainLayout);

    // Подключаем сигналы
    connect(createRequestBtn, &QPushButton::clicked, this, &MainWindow::openRequestForm);
}

void MainWindow::openRequestForm() {
    RequestForm *form = new RequestForm(dbManager, this);
    form->show();  // Открываем форму как модальное окно
}

void MainWindow::openProfile() {
    if (!profileWindow) {
        profileWindow = new ProfileWindow(id_customers, this);  // Передаем id_customers
    }
    profileWindow->show();
}


