#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H

#include <QDialog>
#include <functional>
#include <QVBoxLayout>// Необходимо для std::function

class ProfileWindow : public QDialog {
    Q_OBJECT

public:
    explicit ProfileWindow(int id_customers, QWidget *parent = nullptr);

private:
    int id_customers;

    // Обновляем объявление loadUserData
    void loadUserData(QVBoxLayout *layout, std::function<void(const QString&, const QString&)> addRow);
};

#endif // PROFILEWINDOW_H
