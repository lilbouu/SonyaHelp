#include "profilewindow.h"
#include <QVBoxLayout>
#include <QLabel>


ProfileWindow::ProfileWindow(QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Профиль пользователя");
    setMinimumSize(500, 600);  // Размер окна

    // Предопределенные значения для полей профиля
    QString surnameText = "Иванов";
    QString nameText = "Иван";
    QString patronymicText = "Иванович";
    QString birthDateText = "01.01.1990"; // Значение даты рождения
    QString citizenshipText = "Россия";
    QString seriesText = "1234";
    QString numberText = "567890";

    // Создаем и настраиваем поля для профиля, устанавливаем их как "только для чтения"
    QLabel *surnameLabel = new QLabel("Фамилия:");
    surnameEdit = new QLineEdit(surnameText);
    surnameEdit->setReadOnly(true);

    QLabel *nameLabel = new QLabel("Имя:");
    nameEdit = new QLineEdit(nameText);
    nameEdit->setReadOnly(true);

    QLabel *patronymicLabel = new QLabel("Отчество:");
    patronymicEdit = new QLineEdit(patronymicText);
    patronymicEdit->setReadOnly(true);

    QLabel *birthDateLabel = new QLabel("Дата рождения:");
    birthDateEdit = new QLineEdit(birthDateText); // Создаем QLineEdit вместо QDateEdit
    birthDateEdit->setReadOnly(true); // Установка поля как "только для чтения"

    QLabel *citizenshipLabel = new QLabel("Гражданство:");
    citizenshipEdit = new QLineEdit(citizenshipText);
    citizenshipEdit->setReadOnly(true);

    QLabel *seriesLabel = new QLabel("Серия:");
    seriesEdit = new QLineEdit(seriesText);
    seriesEdit->setReadOnly(true);

    QLabel *numberLabel = new QLabel("Номер:");
    numberEdit = new QLineEdit(numberText);
    numberEdit->setReadOnly(true);

    // Компоновка элементов
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(surnameLabel);
    layout->addWidget(surnameEdit);
    layout->addWidget(nameLabel);
    layout->addWidget(nameEdit);
    layout->addWidget(patronymicLabel);
    layout->addWidget(patronymicEdit);
    layout->addWidget(birthDateLabel);
    layout->addWidget(birthDateEdit); // Добавление нового текстового поля
    layout->addWidget(citizenshipLabel);
    layout->addWidget(citizenshipEdit);
    layout->addWidget(seriesLabel);
    layout->addWidget(seriesEdit);
    layout->addWidget(numberLabel);
    layout->addWidget(numberEdit);

    setLayout(layout);
}
