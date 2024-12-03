#include "adminwindow.h"
#include "usertabledialog.h" // Новый диалог для таблицы
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

AdminWindow::AdminWindow(QWidget *parent) : QWidget(parent) {
    setMinimumSize(1080, 720);
    setWindowTitle("Admin Panel - SonyaHelp");

    // Верхняя панель
    QWidget *titleBar = new QWidget(this);
    titleBar->setFixedHeight(100);
    QHBoxLayout *titleLayout = new QHBoxLayout(titleBar);
    QLabel *imageLabel = new QLabel(titleBar);
    QPixmap logo(":/images/logotip.svg");
    imageLabel->setPixmap(logo.scaled(60, 60, Qt::KeepAspectRatio));
    imageLabel->setFixedSize(60, 60);
    titleLayout->addWidget(imageLabel);
    titleLayout->addStretch();

    QLabel *titleLabel = new QLabel("Admin Panel - SonyaHelp", titleBar);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("Arial", 16, QFont::Bold));
    titleLayout->addWidget(titleLabel);
    titleLayout->addStretch();

    // Кнопки
    QPushButton *viewUsersBtn = new QPushButton("Показать всех пользователей", this);
    QPushButton *manageRequestsBtn = new QPushButton("Управление заявками", this);
    QPushButton *logoutBtn = new QPushButton("Выйти", this);

    QFont buttonFont("Arial", 14, QFont::Bold);
    viewUsersBtn->setFont(buttonFont);
    manageRequestsBtn->setFont(buttonFont);
    logoutBtn->setFont(buttonFont);

    viewUsersBtn->setMinimumSize(350, 100);
    manageRequestsBtn->setMinimumSize(350, 100);
    logoutBtn->setMinimumSize(350, 100);


    QVBoxLayout *buttonsLayout = new QVBoxLayout;
    buttonsLayout->addWidget(viewUsersBtn);
    buttonsLayout->addWidget(manageRequestsBtn);
    buttonsLayout->addWidget(logoutBtn);
    buttonsLayout->setAlignment(Qt::AlignCenter);

    // Главный компоновщик
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleBar);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);

    // Подключение сигналов
    connect(viewUsersBtn, &QPushButton::clicked, this, &AdminWindow::openUserTableDialog);
    connect(logoutBtn, &QPushButton::clicked, this, &AdminWindow::logout);
}

void AdminWindow::openUserTableDialog() {
    UserTableDialog *dialog = new UserTableDialog(this); // Создаем диалог
    dialog->exec();                                      // Открываем как модальное окно
}

void AdminWindow::logout() {
    close(); // Закрыть окно
}
