
//#include "serialassistant_ui.h"
#include "serial_mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    myWidget w;
//    w.show();

//    SerialAssistant serialAssistant;
//    serialAssistant.show();
    SerialAssistant w;  // 创建主窗口对象
        w.show();  // 显示主窗口
    return a.exec();


}



/*用来验证qtxlsx的使用
 * 可以生成一个文件QtXLSX.xlsx
 * Hello Qt!
 * 内容是Qt Xlsx!
*/
