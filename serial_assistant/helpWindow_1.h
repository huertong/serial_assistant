#pragma execution_character_set("utf-8")

#ifndef HELP_WINDOW_1_H
#define HELP_WINDOW_1_H
// helpWindow_1.h
//版本说明


#include <QWidget>
#include <QDebug>

// 引入生成的 UI 头文件
namespace Ui {
    class HelpWindow_1;
}

class HelpWindow_1 : public QWidget
{
    Q_OBJECT

public:
    explicit HelpWindow_1(QWidget *parent = nullptr);
    ~HelpWindow_1();

private:
    Ui::HelpWindow_1 *help_1_Ui; // UI 指针

};



#endif // HELP_1_H
