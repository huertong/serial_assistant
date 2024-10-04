#pragma execution_character_set("utf-8")

#ifndef SERIAL_MAINWINDOW_H
#define SERIAL_MAINWINDOW_H



#include <QMainWindow>
#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMenuBar>
#include <QDateTime>
#include <QDebug>
#include <QDesktopServices>
#include <QSettings>

#include "SecondWindow.h" // 引入第二个窗口
#include "helpWindow_1.h"

//#include "qserialport.h"


QT_BEGIN_NAMESPACE
namespace Ui { class SerialAssistant; }
QT_END_NAMESPACE

class SerialAssistant : public QMainWindow
{
    Q_OBJECT

public:
    SerialAssistant(QWidget *parent = nullptr);
    ~SerialAssistant();

private slots:


    void openClosePort();
    void sendData();
    void readData();
    void clearReceive();
    void clearSend();
    void toggleTimestamp();
    void updateSerialPortConfig();
    void onMenuActionTriggered();
//    void SerialAssistant::onBaudRateChanged(int index);
    void saveParameters();
    void OpenSecondWindowButton();





private:
    Ui::SerialAssistant *ui;  // UI指针
    QSerialPort serialPort;
    SecondWindow *secondWindow; // 第二个窗口指针
    HelpWindow_1 *helpWindow_1;//帮助--说明窗口


    bool addTimestamp = false;//是否添加时间戳
    bool port_state = false;//是否打开串口


//    void updateControlsVisibility();
    void setupConnections();
    void updatePortList();
    void initSerialParameters();
    void loadSavedConfigureParameters();


};

#endif // SERIAL_MAINWINDOW_H
