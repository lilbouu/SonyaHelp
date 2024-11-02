#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>

class DatabaseManager {
public:
    DatabaseManager();
    bool connect();
    bool insertRequest(const QString &surname, const QString &name, const QString &middlename,
                       const QDate &date, int series, int number);
private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
