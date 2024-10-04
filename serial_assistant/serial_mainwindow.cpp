#pragma execution_character_set("utf-8")


//#include "serialassistant_ui.h"
//#include "ui_serialassistant_ui.h"  // 包含自动生成的 UI 文件头

#include "ui_serial_mainwindow.h"
#include "serial_mainwindow.h"

//#include "customdialog.h"

SerialAssistant::SerialAssistant(QWidget  *parent)
    : QMainWindow(parent),
      ui(new Ui::SerialAssistant),
      secondWindow(nullptr), // 初始化第二个窗口指针为空
      helpWindow_1(nullptr) // 初始化帮助窗口1指针为空
{
    qDebug() << "SerialAssistant constructor called"; // 调试信息
    ui->setupUi(this);  // 设置 UI

    initSerialParameters();
    setupConnections();
    updatePortList();
    loadSavedConfigureParameters();

}

SerialAssistant::~SerialAssistant()
{
    saveParameters();
    delete ui;  // 清理 UI 指针
}

void SerialAssistant::setupConnections()
{
    connect(ui->openCloseButton, &QPushButton::clicked, this, &SerialAssistant::openClosePort);
    connect(ui->sendButton, &QPushButton::clicked, this, &SerialAssistant::sendData);
    connect(&serialPort, &QSerialPort::readyRead, this, &SerialAssistant::readData);
    connect(ui->clearReceiveButton, &QPushButton::clicked, this, &SerialAssistant::clearReceive);
    connect(ui->clearSendButton, &QPushButton::clicked, this, &SerialAssistant::clearSend);
    connect(ui->timestampCheckBox, &QCheckBox::stateChanged, this, &SerialAssistant::toggleTimestamp);

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

    connect(ui->link_1, &QMenu::aboutToShow, this, &SerialAssistant::onMenuActionTriggered);

    connect(ui->sendMutiParameters, &QAction::triggered, this, &SerialAssistant::OpenSecondWindowButton);

    connect(ui->descriptioMenuAction, &QAction::triggered, this, &SerialAssistant::onMenuActionTriggered);



}





void SerialAssistant::updatePortList()
{
//    ui->portComboBox->clear();
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

//void SerialAssistant::openClosePort()
//{
//    if (serialPort.isOpen()) {
//        serialPort.close();
//        ui->openCloseButton->setText("打开串口");
//        ui->openCloseButton->setIcon(QIcon(":/asset/gray.png")); //
////        ui->rDataDisplayLabel->append("串口关闭. ");

//    } else {
////        serialPort.setPortName(ui->portComboBox->currentText());
////        serialPort.setBaudRate(QSerialPort::Baud115200);
////        serialPort.setDataBits(QSerialPort::Data8);
////        serialPort.setParity(QSerialPort::NoParity);
////        serialPort.setStopBits(QSerialPort::OneStop);
////        serialPort.setFlowControl(QSerialPort::NoFlowControl);
//        updateSerialPortConfig();

//        if (serialPort.isOpen()) {
//                    qDebug() << "Double-check: Port is indeed open.";
//                }

//        if (serialPort.open(QIODevice::ReadWrite) == true) {
//            ui->openCloseButton->setText("关闭串口");
//            ui->openCloseButton->setIcon(QIcon(":/asset/green.png")); //
////            ui->rDataDisplayLabel->append("串口开启... ");
//        } else {
////            ui->portComboBox->clear();
//            QString newText = ui->rDataDisplayLabel->text() + "无法打开串口: " + serialPort.errorString();
//    //          ui->rDataDisplayLabel->append("无法打开串口: " + serialPort.errorString());
//            ui->rDataDisplayLabel->setText(newText);

////            qDebug() << "Error code:" << serialPort.error();
//        }
//    }
//}


void SerialAssistant::openClosePort()
{
    if (serialPort.isOpen()) {
        serialPort.close();
        ui->openCloseButton->setText("打开串口");
        ui->openCloseButton->setIcon(QIcon(":/asset/gray.png")); //
//        ui->rDataDisplayTextEdit->append("串口关闭. ");

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
//            ui->rDataDisplayTextEdit->append("串口开启... ");
        } else {
//            ui->portComboBox->clear();
            ui->rDataDisplayTextEdit->append("无法打开串口: " + serialPort.errorString());
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

//void SerialAssistant::sendData()
//{
//    if (serialPort.isOpen()) {
//        QByteArray data = ui->sDataTextEdit->toPlainText().toUtf8();
//        serialPort.write(data);

//        // 根据 addTimestamp 的值选择是否添加时间戳
//        if (addTimestamp) {

//            QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
//            QString newText = ui->rDataDisplayLabel->text() + timestamp + " >>send: " + QString::fromUtf8(data);
////            ui->rDataDisplayLabel->append(timestamp + " >>send: " + QString::fromUtf8(data));
//            ui->rDataDisplayLabel->setText(newText);
//        } else {
//            QString newText = ui->rDataDisplayLabel->text() + QString::fromUtf8(data);
////            ui->rDataDisplayLabel->append(QString::fromUtf8(data));
//            ui->rDataDisplayLabel->setText(newText);
//        }
//    } else {
//        QString newText = ui->rDataDisplayLabel->text() + "无法打开串口: " + serialPort.errorString();
//        ui->rDataDisplayLabel->setText(newText);
////        ui->sDataTextEdit->append("串口未打开");
//    }
//}




//void SerialAssistant::readData()
//{
//    QByteArray data = serialPort.readAll();
//    if (addTimestamp) {
//        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
//        QString newText = ui->rDataDisplayLabel->text() + timestamp + " >>send: " + QString::fromUtf8(data);
////          ui->rDataDisplayLabel->append(timestamp + "receive<<:" + QString::fromUtf8(data));
//        ui->rDataDisplayLabel->setText(newText);
//    } else {
//        QString newText = ui->rDataDisplayLabel->text() + QString::fromUtf8(data);
////          ui->rDataDisplayLabel->append(QString::fromUtf8(data));
//        ui->rDataDisplayLabel->setText(newText);

//    }
//}


void SerialAssistant::sendData()
{
    if (serialPort.isOpen()) {
        QByteArray data = ui->sDataTextEdit->toPlainText().toUtf8();
        serialPort.write(data);

        // 根据 addTimestamp 的值选择是否添加时间戳
        if (addTimestamp) {
            QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
            ui->rDataDisplayTextEdit->append(timestamp + " >>send: " + QString::fromUtf8(data));
        } else {
            ui->rDataDisplayTextEdit->append(QString::fromUtf8(data));
        }
    } else {
        ui->rDataDisplayTextEdit->append("串口未打开");
    }
}




void SerialAssistant::readData()
{
    QByteArray data = serialPort.readAll();
    if (addTimestamp) {
        QString timestamp = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss] ");
        ui->rDataDisplayTextEdit->append(timestamp + "receive<<:" + QString::fromUtf8(data));
    } else {
        ui->rDataDisplayTextEdit->append(QString::fromUtf8(data));
    }
}

void SerialAssistant::clearReceive() {
    ui->rDataDisplayTextEdit->clear();
}

void SerialAssistant::clearSend() {
    ui->sDataTextEdit->clear();
}



void SerialAssistant::initSerialParameters()
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
    ui->dataBitsComboBox->addItem("5", QSerialPort::Data5);
    ui->dataBitsComboBox->addItem("6", QSerialPort::Data6);
    ui->dataBitsComboBox->addItem("7", QSerialPort::Data7);
    ui->dataBitsComboBox->addItem("8", QSerialPort::Data8);


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
    ui->baudRateComboBox->setCurrentIndex(8); // 115200 在列表中的索引为 8
    ui->dataBitsComboBox->setCurrentIndex(3);
    ui->stopBitsComboBox->setCurrentIndex(0);
    ui->parityComboBox->setCurrentIndex(0);


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



void SerialAssistant::saveParameters()
{
//    QSettings settings("MySoftwareShop", "MySerialAssistant");
    QSettings settings("SerialAssistant.ini", QSettings::IniFormat);

    settings.setValue("param1", ui->portComboBox ->currentIndex());
    settings.setValue("param2", ui->baudRateComboBox ->currentIndex());
    settings.setValue("param3", ui->dataBitsComboBox ->currentIndex());
    settings.setValue("param4", ui->stopBitsComboBox ->currentIndex());
    settings.setValue("param5", ui->parityComboBox ->currentIndex());
//    settings.setValue("param6", );//flowcontrol
    settings.setValue("param7", ui->rDataHEXDisplayCheckBox ->isChecked());
    settings.setValue("param8", ui->DTRCheckBox ->isChecked());
    settings.setValue("param9", ui->RTSCheckBox ->isChecked());
    settings.setValue("param10", ui->timestampCheckBox ->isChecked());
    settings.setValue("param11", ui->autoSaveReceiveCheckBox ->isChecked());
    settings.setValue("param12", ui->autoSaveReceiveTimeText ->text());
    settings.setValue("param13", ui->addReturnAndFeedLineCheckBox ->isChecked());
    settings.setValue("param14", ui->sDataHEXDisplayCheckBox ->isChecked());
    settings.setValue("param15", ui->timeSendDataCheckBox ->isChecked());
    settings.setValue("param16", ui->timeSendDataText ->text());
//    settings.setValue("param17", ui->autoSaveReceiveTimeText ->text());



//           settings.setValue("param1", ui->autoSaveReceiveTimeText ->text());
//           settings.setValue("param2", ui->timeSendDataText->text());
//           settings.setValue("param3", ui->baudRateComboBox->currentIndex());
////           settings.setValue("param4", ui->portComboBox->currentIndex());
//           settings.setValue("param4", 1);
//           settings.setValue("param", 1);



}

//显示上次关闭窗口时的参数
void SerialAssistant::loadSavedConfigureParameters()
{
    // 读取之前保存的参数
//    QSettings settings("MySoftwareShop", "MySerialAssistant");
    QSettings settings("SerialAssistant.ini", QSettings::IniFormat);

    // 检查是否是第一次运行 (假设用 param1 作为是否初始化的标志)
        if (!settings.contains("isFirstRun")) {
            // 设置第一次运行的标志
            settings.setValue("isFirstRun", false);

            // 设置默认值
            settings.setValue("param1", 0);  // 默认串口索引
            settings.setValue("param2", 8);  // 默认波特率索引
            settings.setValue("param3", 3);  // 默认数据位索引
            settings.setValue("param4", 0);  // 默认停止位索引
            settings.setValue("param5", 0);  // 默认奇偶校验索引
            settings.setValue("param7", false);  // 默认 HEX 显示关闭
            settings.setValue("param8", false);  // 默认 DTR 关闭
            settings.setValue("param9", false);  // 默认 RTS 关闭
            settings.setValue("param10", false);  // 默认 时间戳 关闭
            settings.setValue("param11", false);  // 默认 自动保存 关闭
            settings.setValue("param12", "1000");  // 自动保存接收时间默认值
            settings.setValue("param13", false);  // 默认 回车换行 关闭
            settings.setValue("param14", false);  // 默认 HEX发送 关闭
            settings.setValue("param15", false);  // 默认 自动发送 关闭
            settings.setValue("param16", "1000");  // 默认发送间隔时间

            // 其他默认值也可以按照此方式设置
        }
    // 恢复下拉框的当前索引
        ui->portComboBox->setCurrentIndex(settings.value("param1", 0).toInt());
        ui->baudRateComboBox->setCurrentIndex(settings.value("param2", 0).toInt());
        ui->dataBitsComboBox->setCurrentIndex(settings.value("param3", 0).toInt());
        ui->stopBitsComboBox->setCurrentIndex(settings.value("param4", 0).toInt());
        ui->parityComboBox->setCurrentIndex(settings.value("param5", 0).toInt());
        // Flow Control ComboBox （你还需要添加 flow control 的保存逻辑）
        // ui->flowControlComboBox->setCurrentIndex(settings.value("param6", 0).toInt());

        // 恢复复选框的状态
        ui->rDataHEXDisplayCheckBox->setChecked(settings.value("param7", false).toBool());
        ui->DTRCheckBox->setChecked(settings.value("param8", false).toBool());
        ui->RTSCheckBox->setChecked(settings.value("param9", false).toBool());
        ui->timestampCheckBox->setChecked(settings.value("param10", false).toBool());
        ui->autoSaveReceiveCheckBox->setChecked(settings.value("param11", false).toBool());

        // 恢复文本框的内容
        ui->autoSaveReceiveTimeText->setText(settings.value("param12", "defaultValue").toString());

        // 恢复其他复选框的状态
        ui->addReturnAndFeedLineCheckBox->setChecked(settings.value("param13", false).toBool());
        ui->sDataHEXDisplayCheckBox->setChecked(settings.value("param14", false).toBool());
        ui->timeSendDataCheckBox->setChecked(settings.value("param15", false).toBool());

        // 恢复时间发送的文本框内容
        ui->timeSendDataText->setText(settings.value("param16", "defaultValue").toString());


}


//点击菜单按钮，执行动作
void SerialAssistant::onMenuActionTriggered()
{
//    qDebug()<<"点击菜单";
    QAction *action = qobject_cast<QAction*>(sender());
//    qDebug()<<"点击菜单"<< *action;
    if (action) {
//        qDebug()<<"点击菜单" << action->text();
        if (action->text() == "") {
            // 执行 Open 操作
        } else if (action->text() == "说明") {
//            qDebug()<<"点击菜单1111" << action->text();
            if (!helpWindow_1) { // 如果第二个窗口尚未创建
                helpWindow_1 = new HelpWindow_1(this); // 创建第二个窗口
            }else{
                helpWindow_1->raise(); // 提升窗口到最前面
                helpWindow_1->activateWindow(); // 激活窗口
            }
            helpWindow_1->setParent(nullptr);//独立窗口
            helpWindow_1->show(); // 显示
        }
        else if (action->text() == "") {
//            qDebug()<<"点击菜单link2";
        }
    }

    QMenu *menu = qobject_cast<QMenu*>(sender());
        if (menu) {
            qDebug() << "菜单即将显示，内容如下：";
//            foreach (QAction *action, menu->actions()) {
//                qDebug() << "菜单项文本: " << action->text();
//            }
            if (menu->title() == "link_1") {
                // 执行 Open 操作
                // 使用 QDesktopServices 打开网页链接
//                qDebug()<<"点击菜单link1";
//                    QDesktopServices::openUrl(QUrl("https://www.example.com"));
            } else if (menu->title() == "百度") {
                qDebug()<<"点击菜单link1";
                QDesktopServices::openUrl(QUrl("https://www.baidu.com"));
            }
        }

}

//void SerialAssistant::onBaudRateChanged(int index)
//{
//    qDebug() << "BonBaudRateChanged---------" ;
//}


/*
 * 第二个界面窗口
*/
void SerialAssistant::OpenSecondWindowButton()
{
//    qDebug() << "2222菜单即将显示，内容如下：";
    if (!secondWindow) { // 如果第二个窗口尚未创建
        secondWindow = new SecondWindow(this); // 创建第二个窗口
//        qDebug() << "Second window created.";
    }else{
        secondWindow->raise(); // 提升窗口到最前面
        secondWindow->activateWindow(); // 激活窗口
    }
    secondWindow->setParent(nullptr);//独立第二个窗口
    secondWindow->show(); // 显示第二个窗口

//    //检查第二个窗口不显示的原因，最后没有用到
//    qDebug() << "Is SecondWindow visible:" << secondWindow->isVisible(); // 检查窗口是否可见
//    secondWindow->setFixedSize(400, 300); // 设置固定大小
//    secondWindow->show(); // 显示第二个窗口
//    secondWindow->raise();
//    secondWindow->activateWindow();
//    qDebug() << "Second window position:" << secondWindow->pos();
//    qDebug() << "Second window size:" << secondWindow->size();
//    qDebug() << "Second window opacity:" << secondWindow->windowOpacity();

}













