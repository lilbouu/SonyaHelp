// #include "userrequestswindow.h"
// #include <QVBoxLayout>
// #include <QSqlDatabase>
// #include <QSqlError>
// #include <QDebug>

// UserRequestsWindow::UserRequestsWindow(QWidget *parent)
//     : QWidget(parent)
// {
//     setWindowTitle("Заявки пользователей");
//     setMinimumSize(800, 600);

//     // Настройка модели данных
//     setupModel();

//     // Создание представления таблицы и добавление модели
//     tableView = new QTableView(this);
//     tableView->setModel(model);
//     tableView->setSelectionMode(QAbstractItemView::SingleSelection);
//     tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//     tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // Запрет редактирования

//     // Компоновка окна
//     QVBoxLayout *layout = new QVBoxLayout;
//     layout->addWidget(tableView);
//     setLayout(layout);
// }

// void UserRequestsWindow::setupModel()
// {
//     // Создаем модель, привязанную к таблице "requests" в базе данных
//     model = new QSqlTableModel(this);
//     model->setTable("requests");
//     model->setEditStrategy(QSqlTableModel::OnManualSubmit);

//     // Загружаем данные из таблицы
//     if (!model->select()) {
//         qDebug() << "Ошибка загрузки данных:" << model->lastError().text();
//     }

//     // Устанавливаем заголовки колонок
//     model->setHeaderData(0, Qt::Horizontal, "ID");
//     model->setHeaderData(1, Qt::Horizontal, "Имя пользователя");
//     model->setHeaderData(2, Qt::Horizontal, "Дата создания");
//     model->setHeaderData(3, Qt::Horizontal, "Описание");
// }
