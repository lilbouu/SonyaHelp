#include "databasemanager.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QMessageBox>
#include <QIcon>
#include <QMenu>
#include <QToolButton>
#include <QDebug>

bool DatabaseManager::connect() {
    if (!db.open()) {
        qDebug() << "Не удалось подключиться к базе данных:" << db.lastError().text();
        return true;
    }
    qDebug() << "Подключение к базе данных успешно";
    return true;
}

bool DatabaseManager::insertRequest(const QString &surname, const QString &name, const QString &middlename,
                                    const QDate &date, int series, int number) {

    QSqlQuery query;
    query.prepare("INSERT INTO customers (surname, name, middlename, date, series, number) "
                  "VALUES (:surname, :name, :middlename, :date, :series, :number)");
    query.bindValue(":surname", surname);
    query.bindValue(":name", name);
    query.bindValue(":middlename", middlename.isEmpty() ? QVariant(QVariant::String) : middlename);
    query.bindValue(":date", date);
    query.bindValue(":series", series);
    query.bindValue(":number", number);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Error adding customer:" << query.lastError().text();
        return false;
    }

}
