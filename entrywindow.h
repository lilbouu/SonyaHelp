// entrywindow.h
#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H

#include <QWidget>
#include "registrationwindow.h"

class QLineEdit;
class QPushButton;

class EntryWindow : public QWidget
{
    Q_OBJECT
private slots:
    void openRegistrationWindow();
public:
    explicit EntryWindow(QWidget *parent = nullptr);

private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QPushButton *registerButton;
    DatabaseManager *dbManager;
    RegistrationWindow *registrationWindow;
};

#endif // ENTRYWINDOW_H
