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

int DatabaseManager::addCustomer(const QString& surname, const QString& name, const QString& middlename,
                                  const QDate& birthDate, int series, int number, const QString& citizenship) {
    QSqlQuery query;
    query.prepare("INSERT INTO customers (surname, name, middlename, date, series, number, сitizenship) "
                  "VALUES (:surname, :name, :middlename, :birthDate, :series, :number, :citizenship)");
    query.addBindValue(surname);
    query.addBindValue(name);
    query.addBindValue(middlename);
    query.addBindValue(birthDate);
    query.addBindValue(series);
    query.addBindValue(number);
    query.addBindValue(citizenship);

    if (!query.exec()) {
        qDebug() << "Failed to add customer:" << query.lastError();
        return -1;  // Возвращаем -1 при ошибке
    }

    qint64 lastId = query.lastInsertId().toInt();
    qDebug() << "Last inserted ID:" << lastId;
    return lastId;
}

bool DatabaseManager::addUserCredentials(int customerId, const QString& username, const QString& passwordHash) {
    QSqlQuery query;
    query.prepare("INSERT INTO user_credentials (id_customers, username, password_hash) "
                  "VALUES (:customerId, :username, :passwordHash)");
    query.addBindValue(customerId);
    query.addBindValue(username);
    query.addBindValue(passwordHash);

    if (!query.exec()) {
        qDebug() << customerId << " " << "Failed to add user credentials:" << query.lastError();
        return false;
    }
    return true;
}
bool DatabaseManager::verifyCredentials(const QString &username, const QString &passwordHash) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM user_credentials WHERE username = :username AND password_hash = :passwordHash");
    query.bindValue(":username", username);
    query.bindValue(":passwordHash", passwordHash);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;  // Если найдено совпадение, возвращаем true
    } else {
        qDebug() << "Ошибка при проверке учетных данных:" << query.lastError().text();
        return false;
    }
}
