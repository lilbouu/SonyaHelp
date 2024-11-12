#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>

class ProfileWindow : public QDialog {  // Замените QWidget на QDialog
    Q_OBJECT

public:
    explicit ProfileWindow(QWidget *parent = nullptr);

private:
    QLineEdit *surnameEdit;
    QLineEdit *nameEdit;
    QLineEdit *patronymicEdit;
    QLineEdit *birthDateEdit;
    QLineEdit *citizenshipEdit;
    QLineEdit *documentTypeEdit;
    QLineEdit *seriesEdit;
    QLineEdit *numberEdit;
};
