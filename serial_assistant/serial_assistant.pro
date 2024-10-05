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


# 编译输出目录设置-----------------------------

#输出源程序目录和构建目录
#message("Source Directory: $$_PRO_FILE_PWD_")
#message("Output Directory: $$OUT_PWD")
# 检查是否使用影子构建
# 但是有时候没有生效，不输出错误，不阻止构建
equals(_PRO_FILE_PWD_, OUT_PWD) {
    error("You must use shadow build. Please select a build directory outside the source directory.")
}

# 设置构建目录
BUILD_DIR = $$OUT_PWD

# 根据构建类型设置子目录
CONFIG(debug, debug|release) {
    BUILD_SUBDIR = debug
} else {
    BUILD_SUBDIR = release
}

## 设置输出目录，子文件夹更细分
#DESTDIR = $$BUILD_DIR/$$BUILD_SUBDIR/bin
#OBJECTS_DIR = $$BUILD_DIR/$$BUILD_SUBDIR/obj
#MOC_DIR = $$BUILD_DIR/$$BUILD_SUBDIR/moc
#RCC_DIR = $$BUILD_DIR/$$BUILD_SUBDIR/rcc
#UI_DIR = $$BUILD_DIR/$$BUILD_SUBDIR/ui

# 设置输出目录
DESTDIR = $$BUILD_DIR/$$BUILD_SUBDIR/bin        # 可执行文件输出目录
OBJECTS_DIR = $$BUILD_DIR/$$BUILD_SUBDIR  # 中间对象文件目录
MOC_DIR = $$BUILD_DIR/$$BUILD_SUBDIR      # moc文件目录
RCC_DIR = $$BUILD_DIR/$$BUILD_SUBDIR      # 资源文件编译目录
UI_DIR = $$BUILD_DIR/$$BUILD_SUBDIR       # UI文件编译目录

# 可选：为 debug 版本添加后缀
CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,_d)
}

# ------------------------------------------------
