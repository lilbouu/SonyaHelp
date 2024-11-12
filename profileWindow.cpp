#include "profilewindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>

ProfileWindow::ProfileWindow(int id_customers, QWidget *parent)
    : QDialog(parent), id_customers(id_customers) {
    setWindowTitle("Профиль пользователя");
    setMinimumSize(500, 600);

    QVBoxLayout *layout = new QVBoxLayout;

    // Функция для добавления строки с меткой и данными
    auto addRow = [layout](const QString &labelText, const QString &valueText) {
        QHBoxLayout *rowLayout = new QHBoxLayout;

        QLabel *label = new QLabel(labelText);
        QLabel *value = new QLabel(valueText);

        label->setFixedWidth(150);
        value->setStyleSheet("color: #FFFFFF;");

        rowLayout->addWidget(label);
        rowLayout->addWidget(value);
        rowLayout->addStretch();

        layout->addLayout(rowLayout);
    };

    // Загружаем данные пользователя и добавляем строки с данными в интерфейс
    loadUserData(layout, addRow);

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
