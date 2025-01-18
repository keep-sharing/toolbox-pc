#include "toolbox.h"
#include "ui_toolbox.h"
#include "maskWidget.h"
#include <QTranslator>

ToolBox::ToolBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ToolBox)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setMinimumSize(900,700);//设置最小尺寸

    ui->label_15->setText(QString(UC_VERSION));
    //自定义类声明
    m_waitingWnd = new WaitingWnd(this);
    m_serialPortSetting = new SerialPortSetting();

    m_ucxx14Model = new UCXX14Model();
    m_ucxx22Model = new UCXX22Model();
    m_ucxx52Model = new UCXX52Model();

    m_connect = new Connectting();
    m_threadConnect = new QThread();

    //模块移入线程
    m_connect->moveToThread(m_threadConnect);
    connect(m_connect, &Connectting::sendMsgWnd, this, [=](QString msg){
        emit onWaitingVisible(false);
        showWarning(this,tr("Attention"),msg);
    });

    //参数初始化
    b_pressed = false;

    //界面初始化
    ui->status_frame->setVisible(false);
    ui->general_frame->setVisible(false);
    ui->lorawan_frame->setVisible(false);
    ui->deviceSettings_frame->setVisible(false);
    ui->channel_frame->setVisible(false);
    ui->setting_frame->setVisible(false);
    ui->application_frame->setVisible(false);
    ui->upgrade_frame->setVisible(false);

    //信号槽初始化
    connect(m_serialPortSetting,SIGNAL(sendSerialInfo(SerialInfo)),this,SLOT(onSerialInfoSaveClicked(SerialInfo)));
    connect(m_waitingWnd,&WaitingWnd::mouseClickChanged,this,[=](QPoint pos) {
        move(pos);
        m_windowPos = this->pos();
    });

    //注册结构体
    qRegisterMetaType<SerialInfo>("SerialInfo");
    qRegisterMetaType<QVariantList>("QVariantList");


    connectToSerial();

    QTimer::singleShot(100,this,[=]{m_windowPos = this->pos();});
}

ToolBox::~ToolBox()
{
    delete ui;
}

/**
 * 关闭窗口处理
 * @brief uboxTool::on_close_btn_clicked
 */
void ToolBox::on_close_btn_clicked()
{
    QSettings settings(m_filePathCache.iniPath, QSettings::IniFormat);
    settings.beginGroup("CloseTipAgain");
    if(settings.value("again").toBool()){
        if(showQuestion(this,tr("Attention"),MyMessageBox::TYPE_CLOSE_WND,tr("Closing the toolbox will disconnect you from device.Are you sure you want to disconnect ?")) == QMessageBox::Ok){
            close();
        }
    }else{
        close();
    }
    settings.endGroup();
}

/**
 * 处理无边框但可以拉伸窗口
 * @brief ToolBox::nativeEvent
 * @param eventType
 * @param message
 * @param result
 * @return
 */
bool ToolBox::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    MSG* msg = (MSG*)message;
    int boundaryWidth = 5;
    switch(msg->message)
    {
    case WM_NCHITTEST:
        int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
        int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
        if(xPos < boundaryWidth && yPos<boundaryWidth)                    //左上角
            *result = HTTOPLEFT;
        else if(xPos>=width()-boundaryWidth&&yPos<boundaryWidth)          //右上角
            *result = HTTOPRIGHT;
        else if(xPos<boundaryWidth&&yPos>=height()-boundaryWidth)         //左下角
            *result = HTBOTTOMLEFT;
        else if(xPos>=width()-boundaryWidth&&yPos>=height()-boundaryWidth)//右下角
            *result = HTBOTTOMRIGHT;
        else if(xPos < boundaryWidth)                                     //左边
            *result =  HTLEFT;
        else if(xPos>=width()-boundaryWidth)                              //右边
            *result = HTRIGHT;
        else if(yPos<boundaryWidth)                                       //上边
            *result = HTTOP;
        else if(yPos>=height()-boundaryWidth)                             //下边
            *result = HTBOTTOM;
        else
           return false;
        return true;
    }
    return false;
}

void ToolBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if((event->pos().y() > ui->label_15->y()) && event->pos().y() < ui->label_15->y()+ui->label_15->height()){
            b_pressed = true;
        }
    }
    m_movePoint = event->globalPos() - pos();
}

void ToolBox::mouseMoveEvent(QMouseEvent *event)
{
    if(b_pressed)
    {
        QPoint movePos = event->globalPos();
        move(movePos - m_movePoint);
        m_windowPos = this->pos();
    }
}

void ToolBox::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    b_pressed = false;
}

/**
 * 控制等待mask显示
 * @brief uboxTool::onWaitingVisible
 * @param visible
 */
void ToolBox::onWaitingVisible(bool visible)
{
    if(!visible){
        m_waitingWnd->hide();
    }else{
        this->show();
        m_waitingWnd->show();

        if(m_windowPos != QPoint(0,0)){
            m_waitingWnd->setPoint(m_windowPos);
        }
    }
}

/**
 * 等待页面改变位子,主界面跟随变动
 * @brief uboxTool::onWaitingPosChanged
 * @param pos
 */
void ToolBox::onWaitingPosChanged(QPoint pos)
{
    move(pos);
    m_windowPos = this->pos();

}

void ToolBox::on_min_btn_clicked()
{
    this->showMinimized();
}

void ToolBox::on_relogin_btn_clicked()
{
    connectToSerial();
}

/**
 * 打开串口，连接设备
 * @brief uboxTool::connectToSerial
 */
bool ToolBox::connectToSerial()
{
    QList<QSerialPortInfo>  portlist;
    QSerialPortInfo spinfo;
    for(int i=0; i<spinfo.availablePorts().size(); i++){
        if(spinfo.availablePorts().at(i).manufacturer().isEmpty())
            continue;
        portlist.append(spinfo.availablePorts().at(i));
    }
    for(int i=0; i<portlist.size(); i++){
        for(int j=i+1; j<portlist.size(); j++){
            if(portlist.at(i).portName().mid(3, portlist.at(i).portName().length()-3).toInt() >
                portlist.at(j).portName().mid(3, portlist.at(j).portName().length()-3).toInt()){
                portlist.swapItemsAt(i,j);
            }
        }
    }

    m_filePathCache.iniPath = QApplication::applicationDirPath()+"/config.ini";
    SerialInfo s;
    QSettings settings(m_filePathCache.iniPath, QSettings::IniFormat);

    if(QFile(m_filePathCache.iniPath).exists()){
        settings.beginGroup("SerialPortInfo");
        s.portName=settings.value("portName").toString().trimmed();
        s.baudrate = static_cast<QSerialPort::BaudRate>(settings.value("baudrate").toInt());
        s.databit = static_cast<QSerialPort::DataBits>(settings.value("databits").toInt());
        s.paritybit = static_cast<QSerialPort::Parity>(settings.value("parity").toInt());
        s.stopbit = static_cast<QSerialPort::StopBits>(settings.value("stopbits").toInt());
        s.connectionTimeout = settings.value("connectTimeout").toInt();
        settings.endGroup();

        settings.beginGroup("ImageFilePath");
        m_filePathCache.imageFilePath  = settings.value("imageFilePath").toString();
        m_filePathCache.ubootFilePath  = settings.value("ubootFilePath").toString();
        m_filePathCache.caFilePath     = settings.value("caFilePath").toString();
        m_filePathCache.cliCerFilePath = settings.value("cliCerFilePath").toString();
        m_filePathCache.cliKeyFilePath = settings.value("cliKeyFilePath").toString();
        settings.endGroup();
        m_serialPortSetting->show();

    }else{
        settings.beginGroup("CloseTipAgain");
        settings.setValue("again",true);
        settings.setValue("deleteCommand",true);
        settings.setValue("reset",true);
        settings.endGroup();
    }

    m_serialPortSetting->setPortName(portlist,s.portName);
    return true;
}

void ToolBox::on_serialInfobtn_clicked()
{
    on_relogin_btn_clicked();
}

/**
 * 串口连接槽
 * @brief ToolBox::onSerialInfoSaveClicked
 * @param s
 */
void ToolBox::onSerialInfoSaveClicked(SerialInfo s)
{
    if(s.type == E_NFC){
        isNFC = true;
        m_loginPwd = "";
    }else{
        isNFC = false;
        m_loginPwd = s.loginPwd;
    }

    connect(this, SIGNAL(connectingDevice(SerialInfo)), m_connect, SLOT(onConnectingDevice(SerialInfo)),Qt::UniqueConnection);
    connect(m_connect,&Connectting::sendProductName,this,&ToolBox::onSelectProductType,Qt::UniqueConnection);
    connect(m_threadConnect,SIGNAL(started()),m_connect,SLOT(run()),Qt::UniqueConnection);
    if(!m_threadConnect->isRunning()){
        m_threadConnect->start();
    }
    emit connectingDevice(s);
    onWaitingVisible(true);
}

/**
 * @brief ToolBox::onSelectProductType
 * @param productName
 */
void ToolBox::onSelectProductType(QString productName,QString swver,QString hwver)
{

    ui->hwverBottom_label->setText(hwver);
    ui->swverBottom_label->setText(swver);

    ui->stackedWidget->setCurrentIndex(1);
    qDebug()<<"product name:"<<productName;

    if(m_modelWidget){//Q_NULLPTR(m_modelWidget)

        ui->model_page->layout()->removeWidget(m_modelWidget);
    }
    m_preProName = productName;

    if(productName.startsWith("UC1114") || productName.startsWith("UC3214") || productName.startsWith("UC3314") || productName.startsWith("UC3414") || productName.startsWith("UC3514")){
        ui->model_page->layout()->addWidget(m_ucxx14Model);
        m_modelWidget = m_ucxx14Model;

        ui->status_frame->setVisible(true);
        ui->general_frame->setVisible(true);
        ui->lorawan_frame->setVisible(productName.startsWith("UC1114"));
        ui->deviceSettings_frame->setVisible(false);
        ui->channel_frame->setVisible(false);
        ui->setting_frame->setVisible(true);
        ui->application_frame->setVisible(false);
        ui->upgrade_frame->setVisible(true);

        connect(this,&ToolBox::getProductName,m_ucxx14Model, &UCXX14Model::onGetProductName, Qt::UniqueConnection);
        connect(this,&ToolBox::pageChanged,   m_ucxx14Model, &UCXX14Model::onPageChanged,    Qt::UniqueConnection);
        connect(m_ucxx14Model,&UCXX14Model::waitingVisible, this, &ToolBox::onWaitingVisible,Qt::UniqueConnection);

        emit getProductName(productName,swver,hwver,isNFC,m_loginPwd);
        ui->status_btn->click();
    }else if(productName.startsWith("UC1122") || productName.startsWith("UC3222") || productName.startsWith("UC3322") || productName.startsWith("UC3422") || productName.startsWith("UC3522")){
        ui->model_page->layout()->addWidget(m_ucxx22Model);
        m_modelWidget = m_ucxx22Model;

        ui->status_frame->setVisible(true);
        ui->general_frame->setVisible(true);
        ui->lorawan_frame->setVisible(productName.startsWith("UC1122"));
        ui->deviceSettings_frame->setVisible(false);
        ui->channel_frame->setVisible(false);
        ui->setting_frame->setVisible(true);
        ui->application_frame->setVisible(false);
        ui->upgrade_frame->setVisible(true);

        connect(this,&ToolBox::getProductName,m_ucxx22Model, &UCXX22Model::onGetProductName, Qt::UniqueConnection);
        connect(this,&ToolBox::pageChanged,   m_ucxx22Model, &UCXX22Model::onPageChanged,    Qt::UniqueConnection);
        connect(m_ucxx22Model,&UCXX22Model::waitingVisible, this, &ToolBox::onWaitingVisible,Qt::UniqueConnection);

        emit getProductName(productName,swver,hwver,isNFC,m_loginPwd);
        ui->status_btn->click();

    }else if(productName.startsWith("UC1152") || productName.startsWith("UC3252") || productName.startsWith("UC3352") || productName.startsWith("UC3452") || productName.startsWith("UC3552")){
        ui->model_page->layout()->addWidget(m_ucxx52Model);
        m_modelWidget = m_ucxx52Model;

        ui->status_frame->setVisible(true);
        ui->general_frame->setVisible(true);
        ui->lorawan_frame->setVisible(productName.startsWith("UC1152"));
        ui->deviceSettings_frame->setVisible(false);
        ui->channel_frame->setVisible(true);
        ui->setting_frame->setVisible(true);
        ui->application_frame->setVisible(false);
        ui->upgrade_frame->setVisible(true);

        connect(this,&ToolBox::getProductName,m_ucxx52Model, &UCXX52Model::onGetProductName, Qt::UniqueConnection);
        connect(this,&ToolBox::pageChanged,   m_ucxx52Model, &UCXX52Model::onPageChanged,    Qt::UniqueConnection);
        connect(m_ucxx52Model,&UCXX52Model::waitingVisible, this, &ToolBox::onWaitingVisible,Qt::UniqueConnection);

        emit getProductName(productName,swver,hwver,isNFC,m_loginPwd);
        ui->status_btn->click();

    }else{
        onWaitingVisible(false);
    }
}

void ToolBox::on_status_btn_clicked()
{
    emit pageChanged(ui->status_btn->objectName(),tr("Status >"));
}

void ToolBox::on_general_btn_clicked()
{
    emit pageChanged(ui->general_btn->objectName(),tr("General >"));
}

void ToolBox::on_lorawan_btn_clicked()
{
    emit pageChanged(ui->lorawan_btn->objectName(),tr("LoRaWAN >"));
}

void ToolBox::on_deviceSetting_btn_clicked()
{
    emit pageChanged(ui->deviceSetting_btn->objectName(),tr("Settings >"));
}

void ToolBox::on_channel_btn_clicked()
{
    emit pageChanged(ui->channel_btn->objectName(),tr("Channel >"));
}

void ToolBox::on_setting_btn_clicked()
{
    emit pageChanged(ui->setting_btn->objectName(),tr("Settings >"));
}

void ToolBox::on_application_btn_clicked()
{
    emit pageChanged(ui->application_btn->objectName(),tr("Application >"));
}

void ToolBox::on_upgrade_btn_clicked()
{
    emit pageChanged(ui->upgrade_btn->objectName(),tr("Upgrade >"));
}


void ToolBox::on_translations_btn_clicked()
{
    QString qmFilename;
    static QTranslator* translator;
    if (translator != nullptr){
        qApp->removeTranslator(translator);
        delete translator;
        translator = nullptr;
    }
    translator = new QTranslator;

    QString runPath = QApplication::applicationDirPath();

    if(m_bEnglish){
        m_bEnglish = false;

        qmFilename = runPath + "/translations/ToolBox_zh_CN.qm";

        qDebug()<<qmFilename;
        if (translator->load(qmFilename)){
            qApp->installTranslator(translator);

        }
    }
    else{
        m_bEnglish = true;
        qApp->removeTranslator(translator);
    }

    ui->retranslateUi(this);
}

void ToolBox::on_translations_btn_released()
{
    ui->translations_btn->setStyleSheet("QToolButton {border: 1px solid #e9e9e9;border-top:none;border-bottom:none;border-right:none;background-color: rgb(255, 255, 255);}");
    if(m_bEnglish){
        ui->translations_btn->setIcon(QIcon(":/new/image/23.png"));//中白
    }else{
        ui->translations_btn->setIcon(QIcon(":/new/image/24.png"));//英白
    }
}
