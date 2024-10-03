QT       += core gui

QT += xlsx
QT += serialport
QT += widgets serialport
CONFIG += c++11


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
#    customdialog.c \
    main.cpp \
    serial_mainwindow.cpp

HEADERS += \
#    customdialog.h \
    serial_mainwindow.h

FORMS += \
#    customdialog.ui \
    serial_mainwindow.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    ../include/QtXlsxWriter-master/qtxlsx.pro \
    ../include/qtxlsx.pro \
    ../include/qtxlsx.pro

DISTFILES += \
    ../include/QtXlsxWriter-master/.gitignore \
    ../include/QtXlsxWriter-master/.qmake.conf \
    ../include/QtXlsxWriter-master/LICENSE \
    ../include/QtXlsxWriter-master/README.md \
    ../include/QtXlsxWriter-master/_clang-format \
    ../include/QtXlsxWriter-master/qtxlsx.pro.user \
    ../include/QtXlsxWriter-master/sync.profile \
    resource_1.rc

RESOURCES += \
    resource.qrc

RC_FILE += \
    resource_1.rc
