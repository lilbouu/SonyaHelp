#include "adminwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenu>
#include <QApplication>
#include <QDebug>

AdminWindow::AdminWindow(QWidget *parent)
    : QWidget(parent)
{
    // Устанавливаем размер и заголовок окна
    setMinimumSize(1080, 720);
    setWindowTitle("SonyaHelp: admin access");

    // Верхняя панель
    QWidget *titleBar = new QWidget(this);
    titleBar->setFixedHeight(100);
    QHBoxLayout *titleLayout = new QHBoxLayout(titleBar);

    // Логотип
    QLabel *imageLabel = new QLabel(titleBar);
    QPixmap leftImage(":/images/friends.svg");
    imageLabel->setPixmap(leftImage.scaled(60, 60, Qt::KeepAspectRatio));
    imageLabel->setFixedSize(60, 60);
    titleLayout->addWidget(imageLabel);
    titleLayout->addStretch();

    // Заголовок
    QLabel *titleLabel = new QLabel("SonyaHelp: admin access", titleBar);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("Arial", 16, QFont::Bold));
    titleLayout->addWidget(titleLabel);
    titleLayout->addStretch();

    // Кнопка профиля (с меню)
    QMenu *menu = new QMenu(this);
    QAction *exitAction = new QAction("Выход", menu);
    menu->addAction(exitAction);

    // Подключение к слоту выхода из приложения
    connect(exitAction, &QAction::triggered, this, &AdminWindow::exitApplication);

    // Кнопка меню
    QPushButton *menuButton = new QPushButton(titleBar);
    menuButton->setIcon(QIcon(":/images/person.svg"));
    menuButton->setToolTip("Menu");
    menuButton->setFixedSize(70, 70);
    titleLayout->addWidget(menuButton);

    // Показываем меню при клике на кнопку
    connect(menuButton, &QPushButton::clicked, [menu, menuButton]() {
        menu->exec(menuButton->mapToGlobal(menuButton->rect().bottomRight()));
    });

    // Кнопка "Заявки пользователей"
    QPushButton *userRequestsButton = new QPushButton("Заявки пользователей", this);
    QFont buttonFont("Arial", 16, QFont::Bold);
    userRequestsButton->setFont(buttonFont);
    userRequestsButton->setMinimumSize(350, 120);
    userRequestsButton->setMaximumSize(400, 150);

    // Подключаем кнопку "Заявки пользователей" к слоту
    connect(userRequestsButton, &QPushButton::clicked, this, &AdminWindow::openUserRequests);

    // Главный компоновщик
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleBar);
    mainLayout->addStretch();
    mainLayout->addWidget(userRequestsButton, 0, Qt::AlignCenter);
    mainLayout->addStretch();

    setLayout(mainLayout);
}

// Слот для открытия заявок пользователей
void AdminWindow::openUserRequests()
{
    qDebug() << "Открыть заявки пользователей";
    // Здесь можно добавить логику открытия окна с заявками пользователей
}

// Слот для выхода из приложения
void AdminWindow::exitApplication()
{
    qDebug() << "Выход из приложения!";
    QApplication::quit();
}
