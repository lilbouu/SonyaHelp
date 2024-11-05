#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QDate>

class DatabaseManager {
public:
    DatabaseManager();
    bool connect();
    bool insertRequest(const QString &surname, const QString &name, const QString &middlename,
                       const QDate &date, int series, int number);
    int addCustomer(const QString& surname, const QString& name, const QString& middlename,
                     const QDate& birthDate, int series, int number, const QString& citizenship);
    bool addUserCredentials(int customerId, const QString& username, const QString& passwordHash);
private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
