#include <QApplication>
#include "entrywindow.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    EntryWindow EntryWindow;
    EntryWindow.show();
    return app.exec();
}

