// registrationwindow.h
#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDialog>
#include "databasemanager.h"

class RegistrationWindow :public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationWindow(DatabaseManager* dbManager, QWidget *parent = nullptr);

private slots:
    void registerUser();
private:
    DatabaseManager* dbManager;
    QLineEdit *surnameEdit;
    QLineEdit *nameEdit;
    QLineEdit *patronymicEdit;
    QDateEdit *birthDateEdit;
    QComboBox *citizenshipComboBox;
    QLineEdit *seriesEdit;
    QLineEdit *numberEdit;
    QLineEdit *extraField1;
    QLineEdit *extraField2;
    QLineEdit *extraField22;
    QPushButton *registerButton;
};

#endif // REGISTRATIONWINDOW_H
