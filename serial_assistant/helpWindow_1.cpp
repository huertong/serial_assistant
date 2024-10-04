// helpWindow_1.cpp
#include "helpWindow_1.h"
#include "ui_helpWindow_1.h"


HelpWindow_1::HelpWindow_1(QWidget *parent) :
    QWidget(parent),
    help_1_Ui(new Ui::HelpWindow_1) // 分配内存给 UI 指针
{
    help_1_Ui->setupUi(this); // 初始化 UI，关联到当前窗口
}

HelpWindow_1::~HelpWindow_1()
{
}
