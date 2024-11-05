#ifndef REQUESTFORM_H
#define REQUESTFORM_H

#include <QDialog>
#include "databasemanager.h"
#include <QLineEdit>
#include <QDateEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QLabel>

class RequestForm : public QDialog
{
    Q_OBJECT

public:
    explicit RequestForm(DatabaseManager* dbManager, QWidget *parent = nullptr);

private slots:
    void saveRequest();
    void togglePhysicalMedicalDetailsField(int index);
    void toggleMentalMedicalDetailsField(int index);

private:
    DatabaseManager* dbManager;
    QComboBox* homeComboBox;
    QComboBox* citizenComboBox;
    QComboBox* f_healthComboBox;
    QComboBox* m_healthComboBox;

    QLineEdit* nameEdit;
    QLineEdit* patronymicEdit;
    QDateEdit* birthDateEdit;
    QLineEdit* passportEdit;
    QTextEdit* problemDescriptionEdit;

    QLabel* f_medicalDetailsLabel;
    QTextEdit* f_medicalDetailsEdit;
    QLabel* m_medicalDetailsLabel;
    QTextEdit* m_medicalDetailsEdit;
};

#endif // REQUESTFORM_H
