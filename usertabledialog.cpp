#include "usertabledialog.h"
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QHeaderView>

UserTableDialog::UserTableDialog(QWidget *parent) : QDialog(parent), tableWidget(new QTableWidget(this)) {
    setWindowTitle("Список пользователей");
    setMinimumSize(800, 600);

    tableWidget->setColumnCount(8);
    tableWidget->setHorizontalHeaderLabels(
        {"ID", "Фамилия", "Имя", "Отчество", "Дата рождения", "Серия", "Номер", "Гражданство"});
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tableWidget);
    setLayout(layout);

    // Запрос к базе данных
    QSqlQuery query("SELECT id_customers, surname, name, middlename, date, series, number, сitizenship FROM customers");

    if (!query.exec()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить данные пользователей:\n" + query.lastError().text());
        return;
    }

    // Заполнение таблицы
    int row = 0;
    while (query.next()) {
        tableWidget->insertRow(row);
        for (int col = 0; col < 8; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            tableWidget->setItem(row, col, item);
        }
        row++;
    }

    // Подключение двойного клика для отображения деталей
    connect(tableWidget, &QTableWidget::cellDoubleClicked, this, &UserTableDialog::showCustomerDetails);
}

void UserTableDialog::showCustomerDetails(int row, int column) {
    Q_UNUSED(column);
    int customerId = tableWidget->item(row, 0)->text().toInt(); // ID клиента в первой колонке

    QSqlQuery query;
    query.prepare("SELECT * FROM customers WHERE id_customers = :id");
    query.bindValue(":id", customerId);

    if (query.exec() && query.next()) {
        QString details = QString(
                              "ID: %1\nФамилия: %2\nИмя: %3\nОтчество: %4\nДата рождения: %5\nСерия: %6\nНомер: %7\nГражданство: %8")
                              .arg(query.value("id_customers").toString())
                              .arg(query.value("surname").toString())
                              .arg(query.value("name").toString())
                              .arg(query.value("middlename").toString())
                              .arg(query.value("date").toString())
                              .arg(query.value("series").toString())
                              .arg(query.value("number").toString())
                              .arg(query.value("сitizenship").toString());

        QMessageBox::information(this, "Информация о клиенте", details);
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить данные клиента:\n" + query.lastError().text());
    }
}
