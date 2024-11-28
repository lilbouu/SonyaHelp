#include "profilewindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>
#include <QPushButton>

ProfileWindow::ProfileWindow(int id_customers, QWidget *parent)
    : QDialog(parent), id_customers(id_customers) {
    setWindowTitle("Профиль пользователя");
    setMinimumSize(600, 700);

    QVBoxLayout *layout = new QVBoxLayout;

    // Устанавливаем стиль окна
    setStyleSheet("background-color: #282c34; color: #FFFFFF; font-family: 'Arial'; font-size: 16px;");

    // Заголовок
    QLabel *title = new QLabel("Профиль пользователя");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 24px; font-weight: bold; margin-bottom: 20px;");
    layout->addWidget(title);

    // Функция для добавления строки с меткой и данными
    auto addRow = [layout](const QString &labelText, const QString &valueText) {
        QHBoxLayout *rowLayout = new QHBoxLayout;

        QLabel *label = new QLabel(labelText);
        label->setStyleSheet("font-weight: bold; font-size: 18px; margin-right: 10px;");

        QLabel *value = new QLabel(valueText);
        value->setStyleSheet("color: #FFFFFF; font-size: 16px;");

        rowLayout->addWidget(label);
        rowLayout->addWidget(value);
        rowLayout->addStretch();

        layout->addLayout(rowLayout);
    };

    // Загружаем данные пользователя и добавляем строки с данными в интерфейс
    loadUserData(layout, addRow);

    // Кнопка закрытия
    QPushButton *closeButton = new QPushButton("Закрыть");
    closeButton->setStyleSheet(
        "background-color: #61afef; color: #FFFFFF; border: none; padding: 10px 20px; font-size: 16px; font-weight: bold; border-radius: 5px;"
        );
    connect(closeButton, &QPushButton::clicked, this, &ProfileWindow::accept);
    layout->addWidget(closeButton);
    layout->setAlignment(closeButton, Qt::AlignCenter);

    setLayout(layout);
}

void ProfileWindow::loadUserData(QVBoxLayout *layout, std::function<void(const QString&, const QString&)> addRow) {
    // Выполняем запрос к базе данных для получения данных пользователя
    QSqlQuery query;
    query.prepare(R"(
        SELECT surname, name, middlename, date, series, number, сitizenship
        FROM customers
        WHERE id_customers = :id_customers
    )");
    query.bindValue(":id_customers", id_customers);

    if (query.exec() && query.next()) {
        // Извлекаем данные из запроса
        QString surname = query.value("surname").toString();
        QString name = query.value("name").toString();
        QString middlename = query.value("middlename").toString();
        QString birthDate = query.value("date").toDate().toString("dd.MM.yyyy");
        QString сitizenship = query.value("сitizenship").toString();
        QString series = query.value("series").toString();
        QString number = query.value("number").toString();

        // Заполняем интерфейс данными из базы
        addRow("Фамилия:", surname);
        addRow("Имя:", name);
        addRow("Отчество:", middlename);
        addRow("Дата рождения:", birthDate);
        addRow("Гражданство:", сitizenship);
        addRow("Серия:", series);
        addRow("Номер:", number);
    } else {
        qDebug() << "Ошибка при загрузке данных пользователя:" << query.lastError().text();
    }
}
