#ifndef REQUESTFORM_H
#define REQUESTFORM_H

#include <QDialog>
#include "databasemanager.h"
#include <QLineEdit>
#include <QDateEdit>
#include <QTextEdit>

class RequestForm : public QDialog // Меняем QWidget на QDialog
{
    Q_OBJECT

public:
    explicit RequestForm(DatabaseManager* dbManager, QWidget *parent = nullptr);

private slots:
    void saveRequest();

private:
    DatabaseManager* dbManager;
    QLineEdit* surnameEdit;
    QLineEdit* nameEdit;
    QLineEdit* patronymicEdit;
    QDateEdit* birthDateEdit;
    QLineEdit* passportEdit;
    QTextEdit* problemDescriptionEdit;
};

#endif // REQUESTFORM_H
