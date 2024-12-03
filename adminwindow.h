#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QSqlQuery>

class AdminWindow : public QWidget {
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
private slots:
    void openUserTableDialog();
    void logout();

private:
    QTableWidget *tableWidget;

    void loadCustomerData();
};

#endif // ADMINWINDOW_H
