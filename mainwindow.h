#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "databasemanager.h"
#include "requestform.h"
#include "hoverabletoolbutton.h"
#include "profilewindow.h"
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(int id_customers, QWidget *parent = nullptr);
    void setCustomerId(int id);
private slots:
    void openRequestForm();
    void openProfile();

private:
    DatabaseManager *dbManager;
    int id_customers;
ProfileWindow *profileWindow;    // Указатель на объект DatabaseManager
};

#endif // MAINWINDOW_H
