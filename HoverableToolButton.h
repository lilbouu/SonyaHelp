#ifndef HOVERABLETOOLBUTTON_H
#define HOVERABLETOOLBUTTON_H

#include <QToolButton>
#include <QEnterEvent> // Измените с QEvent на QEnterEvent

class HoverableToolButton : public QToolButton {
    Q_OBJECT
public:
    using QToolButton::QToolButton; // Используем конструктор базового класса

signals:
    void hovered(); // Определяем сигнал hovered

protected:
    void enterEvent(QEnterEvent *event) override { // Измените QEvent на QEnterEvent
        emit hovered(); // Генерируем сигнал hovered
        QToolButton::enterEvent(event); // Вызываем базовую реализацию
    }
};

#endif // HOVERABLETOOLBUTTON_H
