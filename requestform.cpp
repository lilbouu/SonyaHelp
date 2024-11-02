#include "requestform.h"
#include <QMessageBox>
#include <QSqlError>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QMessageBox>
#include <QIcon>
#include <QMenu>
#include <QToolButton>
#include <QDebug>
#include <QtSvg/QSvgWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QMessageBox>
#include <QIcon>
#include <QMenu>
#include <QToolButton>
#include <QDebug>
#include <QWidget>

RequestForm::RequestForm(DatabaseManager* dbManager, QWidget *parent)
    : QDialog(parent), dbManager(dbManager)  // Изменяем QWidget на QDialog
{
    setWindowTitle("Создание заявки");
    setMinimumSize(400, 600);

    // Поля формы
    QLabel *surnameLabel = new QLabel("Фамилия:");
    surnameEdit = new QLineEdit;

    QLabel *nameLabel = new QLabel("Имя:");
    nameEdit = new QLineEdit;

    QLabel *patronymicLabel = new QLabel("Отчество (при наличии):");
    patronymicEdit = new QLineEdit;

    QLabel *birthDateLabel = new QLabel("Дата рождения:");
    birthDateEdit = new QDateEdit;
    birthDateEdit->setCalendarPopup(true);
    birthDateEdit->setDisplayFormat("dd.MM.yyyy");

    QLabel *passportLabel = new QLabel("Серия и номер паспорта:");
    passportEdit = new QLineEdit;

    QLabel *problemDescriptionLabel = new QLabel("Описание проблемы:");
    problemDescriptionEdit = new QTextEdit;

    // Кнопка "Сохранить"
    QPushButton *saveBtn = new QPushButton("Сохранить");

    QVBoxLayout *formLayout = new QVBoxLayout;
    formLayout->addWidget(surnameLabel);
    formLayout->addWidget(surnameEdit);
    formLayout->addWidget(nameLabel);
    formLayout->addWidget(nameEdit);
    formLayout->addWidget(patronymicLabel);
    formLayout->addWidget(patronymicEdit);
    formLayout->addWidget(birthDateLabel);
    formLayout->addWidget(birthDateEdit);
    formLayout->addWidget(passportLabel);
    formLayout->addWidget(passportEdit);
    formLayout->addWidget(problemDescriptionLabel);
    formLayout->addWidget(problemDescriptionEdit);
    formLayout->addWidget(saveBtn);
    setLayout(formLayout);

    connect(saveBtn, &QPushButton::clicked, this, &RequestForm::saveRequest);
}

void RequestForm::saveRequest() {
    QString surname = surnameEdit->text();
    QString name = nameEdit->text();
    QString patronymic = patronymicEdit->text();
    QDate birthDate = birthDateEdit->date();
    QString passportData = passportEdit->text();
    QStringList passportParts = passportData.split(" ");
    int series = passportParts.size() > 0 ? passportParts[0].toInt() : 0;
    int number = passportParts.size() > 1 ? passportParts[1].toInt() : 0;

    // Вызов метода из DatabaseManager для сохранения данных
    if (dbManager->insertRequest(surname, name, patronymic, birthDate, series, number)) {
        QMessageBox::information(this, "Успех", "Заявка успешно сохранена!");
        accept();
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить заявку.");

    }

}
