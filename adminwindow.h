#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>

class AdminWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);

private slots:
    void openUserRequests();  // Слот для открытия списка заявок пользователей
    void exitApplication();   // Слот для выхода из приложения
};

#endif // ADMINWINDOW_H
