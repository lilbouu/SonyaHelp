QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql
RC_FILE = myapp.rc
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databasemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    profileWindow.cpp \
    requestform.cpp

HEADERS += \
    HoverableToolButton.h \
    databasemanager.h \
    mainwindow.h \
    profileWindow.h \
    requestform.h

FORMS += \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
RESOURCES += \
    images.qrc