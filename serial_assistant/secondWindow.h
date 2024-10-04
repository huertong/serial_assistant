#pragma execution_character_set("utf-8")

// SecondWindow.h
#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QWidget>
#include <QDebug>

// 引入生成的 UI 头文件
namespace Ui {
    class SecondWindow;
}

class SecondWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

private:
    Ui::SecondWindow *secondUi; // UI 指针

};

#endif // SECONDWINDOW_H
