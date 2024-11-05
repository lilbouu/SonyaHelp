// main.cpp
#include <QApplication>
#include "entrywindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    EntryWindow window;
    window.show();

    return app.exec();
}



// #include <QApplication>
// #include "mainwindow.h"

// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);
//     MainWindow mainWindow;
//     mainWindow.show();
//     return app.exec();
// }


// #include "adminwindow.h"
// #include <QApplication>

// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);

//     AdminWindow window;
//     window.show();

//     return app.exec();
// }
