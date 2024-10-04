#pragma execution_character_set("utf-8")

#include "serial_mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SerialAssistant w;  // 创建主窗口对象
    w.show();  // 显示主窗口
    return a.exec();


}



/*串口助手
*/
