// SecondWindow.cpp
#include "SecondWindow.h"
#include "ui_secondWindow.h"

//SecondWindow::SecondWindow(QWidget *parent) :
//    QWidget(parent)
//{
//    // 设置窗口标题和其他属性
//    setWindowTitle("Second ");
//        setFixedSize(400, 300); // 设置固定大小，避免窗口太小看不见
//        qDebug() << "SecondWindow constructor called"; // 调试信息

//}

SecondWindow::SecondWindow(QWidget *parent) :
    QWidget(parent),
    secondUi(new Ui::SecondWindow) // 分配内存给 UI 指针
{
    secondUi->setupUi(this); // 初始化 UI，关联到当前窗口
    qDebug() << "SecondWindow constructor called"; // 调试信息
}

SecondWindow::~SecondWindow()
{
}
