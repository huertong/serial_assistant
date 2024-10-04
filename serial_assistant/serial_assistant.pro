QT += widgets serialport
CONFIG += c++11

# 警告设置
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # 取消注释以禁用 Qt 6.0.0 之前的过时 API

SOURCES += \
    helpWindow_1.cpp \
    main.cpp \
    secondWindow.cpp \
    serial_mainwindow.cpp

HEADERS += \
    helpWindow_1.h \
    secondWindow.h \
    serial_mainwindow.h

FORMS += \
    helpWindow_1.ui \
    secondWindow.ui \
    serial_mainwindow.ui

# 资源文件
RESOURCES += \
    resource.qrc

# Windows 资源文件
RC_FILE += \
    resource_1.rc

DISTFILES += \
    resource_1.rc




