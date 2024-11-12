// entrywindow.h
#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H

#include <QWidget>
#include "registrationwindow.h"
#include <mainwindow.h>

class QLineEdit;
class QPushButton;

class EntryWindow : public QWidget
{
    Q_OBJECT
private slots:
    void openRegistrationWindow();
    void onLoginButtonClicked();
public:
    explicit EntryWindow(QWidget *parent = nullptr);

private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QPushButton *registerButton;
    DatabaseManager *dbManager;
    RegistrationWindow *registrationWindow;
    MainWindow *mainWindow;
};

#endif // ENTRYWINDOW_H
