#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "databasemanager.h"
#include "requestform.h"
#include "hoverabletoolbutton.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void openRequestForm();

private:
    DatabaseManager *dbManager;  // Указатель на объект DatabaseManager
};

#endif // MAINWINDOW_H
