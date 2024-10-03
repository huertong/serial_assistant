

//#include "serialassistant_ui.h"
//#include "ui_serialassistant_ui.h"  // 包含自动生成的 UI 文件头

#include "ui_serial_mainwindow.h"
#include "serial_mainwindow.h"

//#include "customdialog.h"

SerialAssistant::SerialAssistant(QWidget  *parent)
    : QMainWindow(parent), ui(new Ui::SerialAssistant)
{
    ui->setupUi(this);  // 设置 UI

    initializeUI();
    setupConnections();
    updatePortList();
}

SerialAssistant::~SerialAssistant()
{
    delete ui;  // 清理 UI 指针
}

void SerialAssistant::setupConnections()
{
    connect(ui->openCloseButton, &QPushButton::clicked, this, &SerialAssistant::openClosePort);
//    connect(ui->sendButton, &QPushButton::clicked, this, &SerialAssistant::sendData);
//    connect(&serialPort, &QSerialPort::readyRead, this, &SerialAssistant::readData);
    connect(ui->sendButton, &QPushButton::clicked, this, &SerialAssistant::sendData);
    connect(&serialPort, &QSerialPort::readyRead, this, &SerialAssistant::readData);
    connect(ui->clearReceiveButton, &QPushButton::clicked, this, &SerialAssistant::clearReceive);
    connect(ui->clearSendButton, &QPushButton::clicked, this, &SerialAssistant::clearSend);
    connect(ui->toggleTimestampBox, &QCheckBox::stateChanged, this, &SerialAssistant::toggleTimestamp);

    // 连接波特率、数据位、停止位、校验位、端口名字下拉框
    connect(ui->baudRateComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SerialAssistant::updateSerialPortConfig);
    connect(ui->dataBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SerialAssistant::updateSerialPortConfig);
    connect(ui->stopBitsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SerialAssistant::updateSerialPortConfig);
    connect(ui->parityComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SerialAssistant::updateSerialPortConfig);
    connect(ui->portComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SerialAssistant::updateSerialPortConfig);

}




void SerialAssistant::updatePortList()
{
    ui->portComboBox->clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        ui->portComboBox->addItem(info.portName());
        QString portDetails = QString("%1 -%2 ")
            .arg(info.portName())
            .arg(info.description());
//            .arg(info.manufacturer());
//        ui->portComboBox->addItem(portDetails);
    }
}


//// 实现 openClosePort、sendData 和 readData 函数

void SerialAssistant::openClosePort()
{
    if (serialPort.isOpen()) {
        serialPort.close();
        ui->openCloseButton->setText("打开串口");
        ui->openCloseButton->setIcon(QIcon(":/asset/gray.png")); //
//        ui->outputTextEdit->append("串口关闭. ");

    } else {
//        serialPort.setPortName(ui->portComboBox->currentText());
//        serialPort.setBaudRate(QSerialPort::Baud115200);
//        serialPort.setDataBits(QSerialPort::Data8);
//        serialPort.setParity(QSerialPort::NoParity);
//        serialPort.setStopBits(QSerialPort::OneStop);
//        serialPort.setFlowControl(QSerialPort::NoFlowControl);
        updateSerialPortConfig();

        if (serialPort.isOpen()) {
                    qDebug() << "Double-check: Port is indeed open.";
                }

        if (serialPort.open(QIODevice::ReadWrite) == true) {
            ui->openCloseButton->setText("关闭串口");
            ui->openCloseButton->setIcon(QIcon(":/asset/green.png")); //
//            ui->outputTextEdit->append("串口开启... ");
        } else {
//            ui->portComboBox->clear();
            ui->outputTextEdit->append("无法打开串口: " + serialPort.errorString());
//            qDebug() << "Error code:" << serialPort.error();
        }
    }
}


void SerialAssistant::toggleTimestamp()
{
    if(addTimestamp==false){
        addTimestamp=true;
    }else{
        addTimestamp=false;
    }
}

void SerialAssistant::sendData()
{
    if (serialPort.isOpen()) {
        QByteArray data = ui->inputTextEdit->toPlainText().toUtf8();
        serialPort.write(data);

        // 根据 addTimestamp 的值选择是否添加时间戳
        if (addTimestamp) {
            QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
            ui->outputTextEdit->append(timestamp + " >>send: " + QString::fromUtf8(data));
        } else {
            ui->outputTextEdit->append(QString::fromUtf8(data));
        }
    } else {
        ui->outputTextEdit->append("串口未打开");
    }
}




void SerialAssistant::readData()
{
    QByteArray data = serialPort.readAll();
    if (addTimestamp) {
        QString timestamp = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss] ");
        ui->outputTextEdit->append(timestamp + "receive<<:" + QString::fromUtf8(data));
    } else {
        ui->outputTextEdit->append(QString::fromUtf8(data));
    }
}

void SerialAssistant::clearReceive() {
    ui->outputTextEdit->clear();
}

void SerialAssistant::clearSend() {
    ui->inputTextEdit->clear();
}


//void SerialAssistant::updateSerialPortConfig()
//{
//    int baudRate = ui->comboBox->currentData().toInt();

//    serialPortConfig.portName = ui->;
//    serialPortConfig.baudRate = ui->baudRateComboBox->currentText();
//    serialPortConfig.dataBits = ui->dataBitsComboBox->currentText();
//    serialPortConfig.stopBits = ui->stopBitsComboBox->currentText();
//    serialPortConfig.parity = ui->parity->currentText();
//    serialPortConfig.flowControl = "None";



//}


void SerialAssistant::initializeUI()
{
    // 初始化波特率下拉框
    ui->baudRateComboBox->addItem("1200", QSerialPort::Baud1200);
    ui->baudRateComboBox->addItem("2400", QSerialPort::Baud2400);
    ui->baudRateComboBox->addItem("4800", QSerialPort::Baud4800);
    ui->baudRateComboBox->addItem("9600", QSerialPort::Baud9600);
    ui->baudRateComboBox->addItem("19200", QSerialPort::Baud19200);
    ui->baudRateComboBox->addItem("38400", QSerialPort::Baud38400);
    ui->baudRateComboBox->addItem("57600", QSerialPort::Baud57600);
    ui->baudRateComboBox->addItem("115200", QSerialPort::Baud115200);

    // 初始化数据位下拉框
    ui->dataBitsComboBox->addItem("8", QSerialPort::Data8);
    ui->dataBitsComboBox->addItem("5", QSerialPort::Data5);
    ui->dataBitsComboBox->addItem("6", QSerialPort::Data6);
    ui->dataBitsComboBox->addItem("7", QSerialPort::Data7);


    // 初始化停止位下拉框
    ui->stopBitsComboBox->addItem("1", QSerialPort::OneStop);
    ui->stopBitsComboBox->addItem("1.5", QSerialPort::OneAndHalfStop);
    ui->stopBitsComboBox->addItem("2", QSerialPort::TwoStop);

    // 初始化校验位下拉框
    ui->parityComboBox->addItem("None", QSerialPort::NoParity);
    ui->parityComboBox->addItem("Even", QSerialPort::EvenParity);
    ui->parityComboBox->addItem("Odd", QSerialPort::OddParity);
    ui->parityComboBox->addItem("Space", QSerialPort::SpaceParity);
    ui->parityComboBox->addItem("Mark", QSerialPort::MarkParity);

//    // 初始化流控下拉框
//    ui->flowControlComboBox->addItem("None", QSerialPort::NoFlowControl);
//    ui->flowControlComboBox->addItem("Hardware", QSerialPort::HardwareControl);
//    ui->flowControlComboBox->addItem("Software", QSerialPort::SoftwareControl);

    //默认值设置
    // 设置默认值为115200
    ui->baudRateComboBox->setCurrentIndex(8); // 115200 在列表中的索引为 7

}



void SerialAssistant::updateSerialPortConfig()
{
    // 获取选择的端口名字
    QString portName = ui->portComboBox->currentText();


    // 获取选择的波特率
    QSerialPort::BaudRate baudRate = static_cast<QSerialPort::BaudRate>(
        ui->baudRateComboBox->currentData().toInt());

    // 获取选择的数据位
    QSerialPort::DataBits dataBits = static_cast<QSerialPort::DataBits>(
        ui->dataBitsComboBox->currentData().toInt());

    // 获取选择的停止位
    QSerialPort::StopBits stopBits = static_cast<QSerialPort::StopBits>(
        ui->stopBitsComboBox->currentData().toInt());

    // 获取选择的校验位
    QSerialPort::Parity parity = static_cast<QSerialPort::Parity>(
        ui->parityComboBox->currentData().toInt());

    // 设置串口参数
    serialPort.setPortName(portName);
    serialPort.setBaudRate(baudRate);
    serialPort.setDataBits(dataBits);
    serialPort.setStopBits(stopBits);
    serialPort.setParity(parity);

//    // 尝试打开串口（这里假设串口名称已经设置）
//    if (serialPort.open(QIODevice::ReadWrite)) {
//        qDebug() << "这里假设串口名称已经设置Serial port opened successfully";
//        qDebug() << "Baud Rate:" << baudRate;
//        qDebug() << "Data Bits:" << dataBits;
//        qDebug() << "Stop Bits:" << stopBits;
//        qDebug() << "Parity:" << parity;
//    } else {
//        qDebug() << "00Failed to open serial port:" << serialPort.errorString();
//    }

    qDebug() << "Baud Rate:" << baudRate;
    qDebug() << "Data Bits:" << dataBits;
    qDebug() << "Stop Bits:" << stopBits;
    qDebug() << "Parity:" << parity;
}

//void SerialAssistant::onBaudRateChanged(int index)
//{
//    qDebug() << "BonBaudRateChanged---------" ;
//}




























//void SerialAssistant::openClosePort()
//{
//    if (port_state) {
//        // 关闭串口
//        serialPort.close();
//        ui->openCloseButton->setText("打开串口"); // 设置按钮文本为"打开串口"
//        port_state = false; // 更新状态
//    } else {
//        // 打开串口
//        serialPort.open(QIODevice::ReadWrite);
//        ui->openCloseButton->setText("关闭串口"); // 设置按钮文本为"关闭串口"
//        port_state = true; // 更新状态
//    }
//}


