#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);

private slots:
    void closeDialog();
};

#endif // ABOUTDIALOG_H
