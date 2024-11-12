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
    void toggleMedicalDetailsField(int index, QComboBox* comboBox, QLabel* label, QTextEdit* edit);
    void showDependencySelection(); // Слот для показа окна выбора зависимости

private:
    DatabaseManager* dbManager;
    QComboBox* homeComboBox;
    QComboBox* citizenComboBox;
    QComboBox* f_healthComboBox;
    QComboBox* m_healthComboBox;
    QComboBox *workPlaceComboBox;  // Поле для информации о месте работы
    QComboBox *dependencyComboBox;  // Поле для выбора зависимости
    QDialog *dependencyDialog;      // Диалог для множественного выбора зависимости
    QStringList selectedDependencies; // Список выбранных зависимостей
    QComboBox* legal_helpComboBox;

    QLineEdit* nameEdit;
    QLineEdit* patronymicEdit;
    QDateEdit* birthDateEdit;
    QLineEdit* passportEdit;
    QTextEdit* problemDescriptionEdit;

    QLabel* f_medicalDetailsLabel;
    QTextEdit* f_medicalDetailsEdit;
    QLabel* m_medicalDetailsLabel;
    QTextEdit* m_medicalDetailsEdit;
    QLabel* lh_medicalDetailsLabel;
    QTextEdit* lh_medicalDetailsEdit;
};

#endif // REQUESTFORM_H
