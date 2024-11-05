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
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QComboBox>

RequestForm::RequestForm(DatabaseManager* dbManager, QWidget *parent)
    : QDialog(parent), dbManager(dbManager) {
    setWindowTitle("Создать обращение");
    setMinimumSize(400, 600);

    // Поля формы
    QLabel *homeLabel = new QLabel("Жилищные условия");
    homeComboBox = new QComboBox;
    homeComboBox->setPlaceholderText("Выберите вариант");
    homeComboBox->addItem("Временно проживаю у родственников");
    homeComboBox->addItem("Проживаю в социальном центре или приюте");
    homeComboBox->addItem("Не имею места жительства");
    homeComboBox->addItem("Имею стабильное жильё");

    QLabel *citizenLabel = new QLabel("Гражданство и статус проживания");
    citizenComboBox = new QComboBox;
    citizenComboBox->setPlaceholderText("Мне необходимо получить:");
    citizenComboBox->addItem("Гражданство");
    citizenComboBox->addItem("Вид на жительство");
    citizenComboBox->addItem("Рабочую визу");
    citizenComboBox->addItem("Учебную визу");
    citizenComboBox->addItem("-");

    QLabel *f_healthLabel = new QLabel("Физическое состояние");
    f_healthComboBox = new QComboBox;
    f_healthComboBox->setPlaceholderText("Выберите вариант:");
    f_healthComboBox->addItem("Мне необходимо медицинское вмешательство");
    f_healthComboBox->addItem("Не нуждаюсь в медицинском вмешательстве");

    // Поле для дополнительных сведений по физическому состоянию
    f_medicalDetailsLabel = new QLabel("Подробности необходимого вмешательства:");
    f_medicalDetailsEdit = new QTextEdit;
    f_medicalDetailsLabel->setVisible(false);
    f_medicalDetailsEdit->setVisible(false);

    QLabel *m_healthLabel = new QLabel("Ментальное состояние");
    m_healthComboBox = new QComboBox;
    m_healthComboBox->setPlaceholderText("Выберите вариант:");
    m_healthComboBox->addItem("Мне необходимо медицинское вмешательство");
    m_healthComboBox->addItem("Не нуждаюсь в медицинском вмешательстве");

    // Поле для дополнительных сведений по ментальному состоянию
    m_medicalDetailsLabel = new QLabel("Подробности необходимого вмешательства:");
    m_medicalDetailsEdit = new QTextEdit;
    m_medicalDetailsLabel->setVisible(false);
    m_medicalDetailsEdit->setVisible(false);

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

    // Компоновка элементов
    QVBoxLayout *formLayout = new QVBoxLayout;
    formLayout->addWidget(homeLabel);
    formLayout->addWidget(homeComboBox);
    formLayout->addWidget(citizenLabel);
    formLayout->addWidget(citizenComboBox);
    formLayout->addWidget(f_healthLabel);
    formLayout->addWidget(f_healthComboBox);
    formLayout->addWidget(f_medicalDetailsLabel);
    formLayout->addWidget(f_medicalDetailsEdit);
    formLayout->addWidget(m_healthLabel);
    formLayout->addWidget(m_healthComboBox);
    formLayout->addWidget(m_medicalDetailsLabel);
    formLayout->addWidget(m_medicalDetailsEdit);
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

    // Подключение сигналов для отображения/скрытия поля медицинских сведений
    connect(f_healthComboBox, &QComboBox::currentIndexChanged, this, &RequestForm::togglePhysicalMedicalDetailsField);
    connect(m_healthComboBox, &QComboBox::currentIndexChanged, this, &RequestForm::toggleMentalMedicalDetailsField);
    connect(saveBtn, &QPushButton::clicked, this, &RequestForm::saveRequest);
}

void RequestForm::togglePhysicalMedicalDetailsField(int index) {
    if (f_healthComboBox->itemText(index) == "Мне необходимо медицинское вмешательство") {
        f_medicalDetailsLabel->setVisible(true);
        f_medicalDetailsEdit->setVisible(true);
    } else {
        f_medicalDetailsLabel->setVisible(false);
        f_medicalDetailsEdit->setVisible(false);
    }
}

void RequestForm::toggleMentalMedicalDetailsField(int index) {
    if (m_healthComboBox->itemText(index) == "Мне необходимо медицинское вмешательство") {
        m_medicalDetailsLabel->setVisible(true);
        m_medicalDetailsEdit->setVisible(true);
    } else {
        m_medicalDetailsLabel->setVisible(false);
        m_medicalDetailsEdit->setVisible(false);
    }
}

void RequestForm::saveRequest() {
    QString home = homeComboBox->currentText();
    QString name = nameEdit->text();
    QString patronymic = patronymicEdit->text();
    QDate birthDate = birthDateEdit->date();
    QString passportData = passportEdit->text();
    QStringList passportParts = passportData.split(" ");
    int series = passportParts.size() > 0 ? passportParts[0].toInt() : 0;
    int number = passportParts.size() > 1 ? passportParts[1].toInt() : 0;

    // Вызов метода из DatabaseManager для сохранения данных
    if (dbManager->insertRequest(home, name, patronymic, birthDate, series, number)) {
        QMessageBox::information(this, "Успех", "Заявка успешно сохранена!");
        accept();
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить заявку.");
    }
}
