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
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void openRequestForm();
    void openProfile();

private:
    DatabaseManager *dbManager;
ProfileWindow *profileWindow;    // Указатель на объект DatabaseManager
};

#endif // MAINWINDOW_H
