#ifndef USERTABLEDIALOG_H
#define USERTABLEDIALOG_H

#include <QDialog>
#include <QTableWidget>

class UserTableDialog : public QDialog {
    Q_OBJECT

public:
    explicit UserTableDialog(QWidget *parent = nullptr);

private slots:
    void showCustomerDetails(int row, int column);

private:
    QTableWidget *tableWidget;
};

#endif // USERTABLEDIALOG_H
