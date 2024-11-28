#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("О нас");
    setMinimumSize(400, 300);

    // Текст "рыба"
    QLabel *aboutText = new QLabel(
        "SonyaHelp — это система, которая помогает решать проблемы пользователей. "
        "Мы стремимся к совершенству, создавая удобные решения для всех наших клиентов.\n\n"
        "Версия: 1.0.0\nАвторы:\n Куксова Софья\n Матвеев Владислав",
        this
        );
    aboutText->setWordWrap(true);
    aboutText->setAlignment(Qt::AlignCenter);

    // Кнопка закрытия
    QPushButton *closeButton = new QPushButton("Закрыть", this);
    connect(closeButton, &QPushButton::clicked, this, &AboutDialog::closeDialog);

    // Компоновка
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(aboutText);
    layout->addWidget(closeButton);
    layout->setAlignment(closeButton, Qt::AlignCenter);

    setLayout(layout);
}

void AboutDialog::closeDialog()
{
    this->accept(); // Закрывает диалог
}
