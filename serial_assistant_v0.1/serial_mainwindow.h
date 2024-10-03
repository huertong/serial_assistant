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
    void SerialAssistant::clearReceive();
    void SerialAssistant::clearSend();
    void SerialAssistant::toggleTimestamp();
    void SerialAssistant::updateSerialPortConfig();
//    void SerialAssistant::onBaudRateChanged(int index);





private:
    Ui::SerialAssistant *ui;  // UI指针
    QSerialPort serialPort;

    struct SerialPortConfig {
        QString portName;   // 端口名字
        qint32 baudRate;       // 波特率
        qint32 dataBits;       // 数据位
        qint32 stopBits;       // 停止位
        QString parity;     // 校验位 (可以是 "None", "Even", "Odd" 等)
        QString flowControl; // 流控制 (如 "None", "RTS/CTS", "XON/XOFF" 等)
    };

    SerialPortConfig serialPortConfig;



    bool addTimestamp = false;//是否添加时间戳
    bool port_state = false;//是否打开串口


    void setupConnections();
    void updatePortList();
    void SerialAssistant::initializeUI();


};

#endif // SERIAL_MAINWINDOW_H
