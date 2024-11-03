#include "profilewindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

ProfileWindow::ProfileWindow(QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Профиль пользователя");
    setMinimumSize(500, 600);  // Размер окна такой же, как у mainwindow

    // Создаем и настраиваем поля для профиля
    QLabel *surnameLabel = new QLabel("Фамилия:");
    surnameEdit = new QLineEdit;

    QLabel *nameLabel = new QLabel("Имя:");
    nameEdit = new QLineEdit;

    QLabel *patronymicLabel = new QLabel("Отчество:");
    patronymicEdit = new QLineEdit;

    QLabel *birthDateLabel = new QLabel("Дата рождения:");
    birthDateEdit = new QDateEdit;
    birthDateEdit->setCalendarPopup(true);
    birthDateEdit->setDisplayFormat("dd.MM.yyyy");

    QLabel *citizenshipLabel = new QLabel("Гражданство:");
    citizenshipEdit = new QLineEdit;

    QLabel *documentTypeLabel = new QLabel("Тип документа:");
    documentTypeEdit = new QLineEdit;

    QLabel *seriesLabel = new QLabel("Серия:");
    seriesEdit = new QLineEdit;

    QLabel *numberLabel = new QLabel("Номер:");
    numberEdit = new QLineEdit;

    // Кнопка "Сохранить"
    QPushButton *saveBtn = new QPushButton("Сохранить");

    // Компоновка элементов
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(surnameLabel);
    layout->addWidget(surnameEdit);
    layout->addWidget(nameLabel);
    layout->addWidget(nameEdit);
    layout->addWidget(patronymicLabel);
    layout->addWidget(patronymicEdit);
    layout->addWidget(birthDateLabel);
    layout->addWidget(birthDateEdit);
    layout->addWidget(citizenshipLabel);
    layout->addWidget(citizenshipEdit);
    layout->addWidget(documentTypeLabel);
    layout->addWidget(documentTypeEdit);
    layout->addWidget(seriesLabel);
    layout->addWidget(seriesEdit);
    layout->addWidget(numberLabel);
    layout->addWidget(numberEdit);
    layout->addWidget(saveBtn);

    setLayout(layout);

    // Подключение действия кнопки "Сохранить"
    connect(saveBtn, &QPushButton::clicked, this, [this]() {
        // Здесь можно добавить логику сохранения профиля
        qDebug() << "Профиль сохранен!";
    });
}
