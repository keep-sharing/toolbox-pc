#include "serialportsetting.h"
#include "ui_serialportsetting.h"

SerialPortSetting::SerialPortSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialPortSetting)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint| Qt::Tool|Qt::SubWindow|Qt::Popup);

    //鼠标点击拖动标志位
    m_pressed = false;

    ui->loginPwd_lineedit->setContextMenuPolicy(Qt::NoContextMenu);
    ui->loginPwd_lineedit->setValidator(new QRegExpValidator(QRegExp("^[^\u4e00-\u9fa5-\u0020]*$")));

    ui->parityBit_cbx->addItem(tr("None"),QSerialPort::NoParity);
    ui->parityBit_cbx->addItem(tr("Even"),QSerialPort::EvenParity);
    ui->parityBit_cbx->addItem(tr("Odd"),QSerialPort::OddParity);

    ui->baudRate_cbx->addItem(tr("115200"),QSerialPort::Baud115200);
    ui->baudRate_cbx->addItem(tr("57600"),QSerialPort::Baud57600);
    ui->baudRate_cbx->addItem(tr("9600"),QSerialPort::Baud9600);

    ui->dataBit_cbx->addItem(tr("8"),QSerialPort::Data8);
    ui->dataBit_cbx->addItem(tr("7"),QSerialPort::Data7);
    ui->dataBit_cbx->addItem(tr("5"),QSerialPort::Data5);

    ui->stopBit_cbx->addItem(tr("1"),QSerialPort::OneStop);
    ui->stopBit_cbx->addItem(tr("2"),QSerialPort::TwoStop);
    ui->loginPwd_lineedit->setFocus();
}

SerialPortSetting::~SerialPortSetting()
{
    delete ui;
}


void SerialPortSetting::setPortName(QList<QSerialPortInfo> portName,QString p)
{
    ui->serialPort_cbx->clear();
    m_spis = portName;
    foreach (QSerialPortInfo spi, portName) {
        ui->loginPwd_lineedit->setText("");
        ui->serialPort_cbx->addItem(spi.portName());
        if(p == spi.portName() && spi.description().contains("USB-SERIAL")){
            ui->type_cbx->setCurrentIndex(1);
        }
    }
    ui->serialPort_cbx->setCurrentIndex(ui->serialPort_cbx->findText(p));

}

void SerialPortSetting::on_save_btn_clicked()
{
    currentPortName = ui->serialPort_cbx->currentText().trimmed();
    SerialInfo s;
    s.type = ui->type_cbx->currentIndex();
    s.portName = ui->serialPort_cbx->currentText().trimmed();
    if(ui->type_cbx->currentText().toUpper().contains("NFC")){
        s.baudrate = QSerialPort::Baud115200;
        s.databit = QSerialPort::Data8;
        s.paritybit = QSerialPort::NoParity;
        s.stopbit = QSerialPort::OneStop;
        s.loginPwd = "";
    }else{
        s.baudrate = static_cast<QSerialPort::BaudRate>(ui->baudRate_cbx->currentData().toInt());
        s.databit = static_cast<QSerialPort::DataBits>(ui->dataBit_cbx->currentData().toInt());
        s.paritybit = static_cast<QSerialPort::Parity>(ui->parityBit_cbx->currentData().toInt());
        s.stopbit = static_cast<QSerialPort::StopBits>(ui->stopBit_cbx->currentData().toInt());
        s.loginPwd = ui->loginPwd_lineedit->text();
    }

    QString iniPath = QApplication::applicationDirPath()+"/config.ini";
    QSettings settings(iniPath, QSettings::IniFormat);
    if(!QFile(iniPath).exists()){
    }

    settings.beginGroup("SerialPortInfo");
    settings.setValue("baudrate",ui->baudRate_cbx->currentData().toInt());
    settings.setValue("parity",ui->parityBit_cbx->currentData().toInt());
    settings.setValue("databits",ui->dataBit_cbx->currentData().toInt());
    settings.setValue("stopbits",ui->stopBit_cbx->currentData().toInt());
    settings.setValue("portName",ui->serialPort_cbx->currentText());
    settings.setValue("type",ui->type_cbx->currentIndex());
    settings.endGroup();

    emit sendSerialInfo(s);
}

void SerialPortSetting::on_type_cbx_currentIndexChanged(int index)
{
    if(index == 0){
        ui->serial_frame->setVisible(true);

    }else if(index ==  1){
        ui->serialPort_cbx->clear();
        foreach (QSerialPortInfo spi, m_spis) {
            ui->serialPort_cbx->addItem(spi.portName());
            if(spi.description().contains("USB-SERIAL")){
                ui->serialPort_cbx->setCurrentIndex(ui->serialPort_cbx->findText(spi.portName()));
                break;
            }
        }
        ui->serial_frame->setVisible(false);
    }
}

void SerialPortSetting::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if((event->pos().y() > ui->label_8->y()) && event->pos().y() < ui->label_8->y()+ui->label_8->height()){
            m_pressed = true;
//            m_pos = event->pos();
        }
    }
    movePoint = event->globalPos() - pos();
}

void SerialPortSetting::mouseMoveEvent(QMouseEvent *event)
{
    if(m_pressed)
    {
//        move(event->pos() - m_pos + this->pos());
        QPoint movePos = event->globalPos();
        move(movePos - movePoint);
    }
}

void SerialPortSetting::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)// avoid the warnning that 'event' is unused while building the project
    m_pressed = false;
}

void SerialPortSetting::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
