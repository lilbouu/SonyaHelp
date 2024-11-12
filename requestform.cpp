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
#include <QCheckBox> // Добавьте это

RequestForm::RequestForm(DatabaseManager* dbManager, QWidget *parent)
    : QDialog(parent), dbManager(dbManager) {
    setWindowTitle("Создать обращение");
    setMinimumSize(400, 600);

    // Поля формы
    QLabel *homeLabel = new QLabel("Жилищные условия");
    homeComboBox = new QComboBox;
    homeComboBox->setPlaceholderText("Выберите вариант:");
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

    f_medicalDetailsLabel = new QLabel("Подробности необходимого вмешательства:");
    f_medicalDetailsEdit = new QTextEdit;
    f_medicalDetailsLabel->setVisible(false);
    f_medicalDetailsEdit->setVisible(false);

    QLabel *m_healthLabel = new QLabel("Ментальное состояние");
    m_healthComboBox = new QComboBox;
    m_healthComboBox->setPlaceholderText("Выберите вариант:");
    m_healthComboBox->addItem("Мне необходимо медицинское вмешательство");
    m_healthComboBox->addItem("Не нуждаюсь в медицинском вмешательстве");

    m_medicalDetailsLabel = new QLabel("Подробности необходимого вмешательства:");
    m_medicalDetailsEdit = new QTextEdit;
    m_medicalDetailsLabel->setVisible(false);
    m_medicalDetailsEdit->setVisible(false);

    QLabel *legal_helpLabel = new QLabel("Юридическая помощь");
    legal_helpComboBox = new QComboBox;
    legal_helpComboBox->setPlaceholderText("Выберите вариант:");
    legal_helpComboBox->addItem("Мне необходима юридическая помощь");
    legal_helpComboBox->addItem("Не нуждаюсь в юридической помощи");

    lh_medicalDetailsLabel = new QLabel("Подробности вашей ситуации:");
    lh_medicalDetailsEdit = new QTextEdit;
    lh_medicalDetailsLabel->setVisible(false);
    lh_medicalDetailsEdit->setVisible(false);


    QLabel *workPlaceLabel = new QLabel("Место работы");
    workPlaceComboBox = new QComboBox;
    workPlaceComboBox->setPlaceholderText("Выберите вариант:");
    workPlaceComboBox->addItem("Не имею работы");
    workPlaceComboBox->addItem("Временно трудоустроен");
    workPlaceComboBox->addItem("Работаю неофициально");
    workPlaceComboBox->addItem("Имею стабильную работу");

    // Поле "Проблема с зависимостью"
    QLabel *dependencyLabel = new QLabel("Проблема с зависимостью");
    dependencyComboBox = new QComboBox;
    // Устанавливаем placeholder-текст
    dependencyComboBox->setPlaceholderText("Выберите вариант:"); // Текст по умолчанию
    dependencyComboBox->addItem("-");
    dependencyComboBox->addItem("У меня зависимость от");

    dependencyDialog = new QDialog(this);
    dependencyDialog->setWindowTitle("Выберите зависимости");
    dependencyDialog->setModal(true);
    QVBoxLayout *dialogLayout = new QVBoxLayout(dependencyDialog);
    QCheckBox *alcoholCheckBox = new QCheckBox("Алкоголь");
    QCheckBox *drugsCheckBox = new QCheckBox("Наркотики");
    QCheckBox *gamblingCheckBox = new QCheckBox("Азартные игры");
    QCheckBox *smokingCheckBox = new QCheckBox("Курение");
    dialogLayout->addWidget(alcoholCheckBox);
    dialogLayout->addWidget(drugsCheckBox);
    dialogLayout->addWidget(gamblingCheckBox);
    dialogLayout->addWidget(smokingCheckBox);
    QPushButton *confirmButton = new QPushButton("Подтвердить");
    dialogLayout->addWidget(confirmButton);
    connect(confirmButton, &QPushButton::clicked, [=]() {
        selectedDependencies.clear();
        if (alcoholCheckBox->isChecked()) selectedDependencies << "Алкоголь";
        if (drugsCheckBox->isChecked()) selectedDependencies << "Наркотики";
        if (gamblingCheckBox->isChecked()) selectedDependencies << "Азартные игры";
        if (smokingCheckBox->isChecked()) selectedDependencies << "Курение";
        dependencyComboBox->setCurrentText("У меня зависимость от: " + selectedDependencies.join(", "));
        dependencyDialog->accept();
    });

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

    QPushButton *saveBtn = new QPushButton("Сохранить");

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
    formLayout->addWidget(legal_helpLabel);
    formLayout->addWidget(legal_helpComboBox);
    formLayout->addWidget(lh_medicalDetailsLabel);
    formLayout->addWidget(lh_medicalDetailsEdit);
    formLayout->addWidget(workPlaceLabel);
    formLayout->addWidget(workPlaceComboBox);

    formLayout->addWidget(dependencyLabel);
    formLayout->addWidget(dependencyComboBox);

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

    connect(f_healthComboBox, &QComboBox::currentIndexChanged, this, [this](int index) {
        toggleMedicalDetailsField(index, f_healthComboBox, f_medicalDetailsLabel, f_medicalDetailsEdit);
    });

    connect(m_healthComboBox, &QComboBox::currentIndexChanged, this, [this](int index) {
        toggleMedicalDetailsField(index, m_healthComboBox, m_medicalDetailsLabel, m_medicalDetailsEdit);
    });

    connect(legal_helpComboBox, &QComboBox::currentIndexChanged, this, [this](int index) {
        toggleMedicalDetailsField(index, legal_helpComboBox, lh_medicalDetailsLabel, lh_medicalDetailsEdit);
    });

    connect(dependencyComboBox, &QComboBox::currentIndexChanged, this, &RequestForm::showDependencySelection);

    connect(saveBtn, &QPushButton::clicked, this, &RequestForm::saveRequest);
}


void RequestForm::toggleMedicalDetailsField(int index, QComboBox* comboBox, QLabel* label, QTextEdit* edit) {
    QString selectedText = comboBox->itemText(index);
    if (selectedText == "Мне необходимо медицинское вмешательство" || selectedText == "Мне необходима юридическая помощь") {
        label->setVisible(true);
        edit->setVisible(true);
    } else {
        label->setVisible(false);
        edit->setVisible(false);
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

void RequestForm::showDependencySelection() {
    if (dependencyComboBox->currentIndex() == 0) {
        return; // Игнорируем, если выбрано значение по умолчанию
    }
    if (dependencyComboBox->currentText() == "У меня зависимость от") {
        // Показываем диалоговое окно для множественного выбора
        dependencyDialog->exec();
    }
}


