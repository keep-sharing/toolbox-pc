#include "ucxx22dealthread.h"
#include <QDateTime>
#include <QTimer>
#include <QTimeZone>

UCXX22DealThread::UCXX22DealThread(QObject *parent) : QObject(parent)
{
    m_loginPwd = "";
}

UCXX22DealThread::~UCXX22DealThread()
{
    delete m_qunp;
}

void UCXX22DealThread::run()
{
    m_qunp = new QunpUCXX22();
    qDebug()<<"Thread id:"<<QThread::currentThreadId();
    connect(m_qunp,SIGNAL(getImageSize(uint32_t)),this,SLOT(imageProgress(uint32_t)),Qt::UniqueConnection);
}

void UCXX22DealThread::imageProgress(uint32_t pktsize)
{
    if(((pktsize *100 / imageDataSize) >3 ) && ((pktsize *100 / imageDataSize) < 99) ){
        emit upgradeProgress(static_cast<int>(pktsize *100 / imageDataSize));
    }
}

void UCXX22DealThread::onConnectingDevice(SerialInfo s)
{
    m_loginPwd = s.loginPwd;
    if(m_qunp->initSerialPort(s)){

        if(m_qunp->unp_send_passwd(reinterpret_cast<uint8_t *>(s.loginPwd.toLatin1().data()),static_cast<uint16_t>(s.loginPwd.length())) == UNP_SUCCESS){

        }else{
            qDebug("Connect Password Error");
        }
    }else{
        qDebug("SerialPort Open Error");
    }
    m_qunp->close_serialport();
}

void UCXX22DealThread::onGetProductName(QString proName,QString swver, QString hwver, bool isNFC)
{
    m_proName = proName;
    m_swver = swver;
    m_hwver = hwver;
    m_bNFC = isNFC;

    structSupportModel.nb = m_proName.contains("UC35");
    structSupportModel.cloud = m_proName.at(2) == '3';
    structSupportModel.lora = m_proName.at(2) == '1';

}
bool UCXX22DealThread::openSerialPort()
{
    QSettings settings( QApplication::applicationDirPath()+"/config.ini", QSettings::IniFormat);
    settings.beginGroup("SerialPortInfo");

    SerialInfo s;
    s.portName=settings.value("portName").toString().trimmed();
    s.baudrate = static_cast<QSerialPort::BaudRate>(settings.value("baudrate").toInt());
    s.databit = static_cast<QSerialPort::DataBits>(settings.value("databits").toInt());
    s.paritybit = static_cast<QSerialPort::Parity>(settings.value("parity").toInt());
    s.stopbit = static_cast<QSerialPort::StopBits>(settings.value("stopbits").toInt());
    settings.endGroup();

    return m_qunp->initSerialPort(s);
}

void UCXX22DealThread::closeSerialPort()
{
    m_qunp->close_serialport();
}

void UCXX22DealThread::onRequestToDevice(int type, QVariantList list)
{
    qDebug("request type:%d",type);
    if(!openSerialPort()){
        emit sendMsgWnd(tr("serial port open error"));
        return;
    }

    m_qunp->set_comnct_type(m_bNFC ? QunpUCXX22::COMNCT_NFC : QunpUCXX22::COMNCT_UART);

    if(!m_bNFC && m_qunp->unp_send_passwd(reinterpret_cast<uint8_t *>(m_loginPwd.toLatin1().data()),static_cast<uint16_t>(m_loginPwd.length())) != UNP_SUCCESS){
        emit sendMsgWnd(tr("password error"));
        goto CMD_END;
    }
    emit waitingVisible(true);

    switch (type) {
    case PAGE_STATUS:{
        getStatusPage(list);
        break;
    }
    case PAGE_GENERAL:{
        getGeneralPage(list);
        break;
    }
    case CONFIG_READ_GENERAL_SPECIAL:{
        getGeneralGPIO(list);
        break;
    }
    case PAGE_LORAWAN:{
        getLorawanPage(list);
        break;
    }
    case CONFIG_WRITE_LORAWAN:{
        setLorawanPage(list);
        break;
    }
    case CONFIG_WRITE_GENERAL:{
        setGeneralPage(list);
        break;
    }
    case PAGE_SETTING:{
        getSettingPage(list);
        break;
    }
    case CONFIG_WRITE_SETTING:{
        setSettingPage(list);
        break;
    }
    case CONFIG_IMPORT_AWS_FILE:{
        setImportAwdFile(list);
        break;
    }
    case PAGE_UPGRADE:{
        toUpgrade(list);
        break;
    }
    case CONFIG_RESET:{
        resetDevice(list);
        break;
    }
    }

CMD_END:
    closeSerialPort();
}

/**
 * 读状态页
 * @brief UCXX22DealThread::getStatusPage
 * @param list
 */
void UCXX22DealThread::getStatusPage(QVariantList list)
{
    Q_UNUSED(list)

    StructPageStatus info;
    int ret = 0;
    uint8_t sn[UNP_MAX_PKTSIZE]={0};
    uint8_t oem[UNP_PN_LEN]={0};
    uint8_t pn11[UNP_PN_TOTAL_LEN]={0};
    uint8_t ucpVer[1]={0};
    uint8_t name[UNP_PRODUCT_NAME_LEN + 1]={0};
    uint8_t swver[UNP_SWVER_LEN]={0};
    uint8_t hwver[UNP_HWVER_LEN]={0};

    ret |= m_qunp->unp_get_product_name(name);
    m_proName = QString::asprintf("%s",name);
    info.proName = m_proName;

    ret |= m_qunp->unp_get_product_swver(swver);
    m_swver = QString::asprintf("%c%c.%c%c",swver[0],swver[1],swver[2],swver[3]);
    info.swVer = m_swver;

    ret |= m_qunp->unp_get_product_hwver(hwver);
    m_hwver = QString::asprintf("%c%c.%c%c",hwver[0],hwver[1],hwver[2],hwver[3]);
    info.hwVer = m_hwver;

    m_qunp->unp_get_version(ucpVer);
    info.ucpVer = *ucpVer;

    ret |= m_qunp->unp_get_product_sn(sn);
    info.sn = QString(QLatin1String((char*)sn));
    qDebug()<<info.sn;

    ret |= m_qunp->unp_get_oem(oem);
    info.oem=QString(QLatin1String((char*)oem));

    ret = m_qunp->unp_get_product_pn(pn11);
    info.pn = QString::asprintf("%s",pn11);
    if(info.pn.split("-").size()>1){
        setSupportModel(info.pn.split("-").at(1));
    }

    QDateTime localTime;
    QunpUCXX22::unxxtime_t cur;
    ret = m_qunp->unp_get_current_time(&cur);

    QString month,date,hour,min,sec;
    QString utcTimeStr = QString("%1-%2-%3 %4:%5:%6")
            .arg(cur.year)
            .arg(month = QString::asprintf("%02d",cur.month))
            .arg(date = QString::asprintf("%02d",cur.date))
            .arg(hour = QString::asprintf("%02d",cur.hour))
            .arg(min = QString::asprintf("%02d",cur.min))
            .arg(sec = QString::asprintf("%02d",cur.sec));

    QDateTime utcTime = QDateTime::fromString(utcTimeStr,"yyyy-MM-dd hh:mm:ss");

    localTime = QDateTime(utcTime.date(),utcTime.time(),Qt::UTC).toTimeSpec(Qt::LocalTime);
    qDebug()<<localTime<<utcTimeStr;

    QString weekday;
    switch (localTime.date().dayOfWeek()) {
    case 1:
        weekday = "Monday";
        break;
    case 2:
        weekday = "Tuesday";
        break;
    case 3:
        weekday = "Wednesday";
        break;
    case 4:
        weekday = "Thursday";
        break;
    case 5:
        weekday = "Friday";
        break;
    case 6:
        weekday = "Saturday";
        break;
    case 7:
        weekday = "Sunday";
        break;
    default:
        break;
    }

    info.time = QString("%1 %2").arg(localTime.toString("yyyy-MM-dd hh:mm:ss")).arg(weekday);

    QunpUCXX22::unp_mobile_state_t state;
    ret = m_qunp->unp_get_mobile_state(&state);
    info.mobileState = QString::number(state);

    uint8_t signal[4] = {0};
    ret = m_qunp->unp_get_mobile_signal(signal);
    qsnprintf(reinterpret_cast<char*>(signal),sizeof(signal),"%d",*signal);
    QString aus = QString::asprintf("%s",signal);

    int dbm = -113 + 2 * aus.trimmed().toInt();
    info.mobileSignal=QString("%1asu(%2dbm)").arg(aus.trimmed()).arg(QString::number(dbm));

    QunpUCXX22::app_mode_t am;
    ret = m_qunp->unp_get_app_mode(&am);
    info.application_mode = am;

    uint8_t value[UNP_MAX_PKTSIZE] = {0};
    QString io_status;
    for(int m=1; m<=1; m++){
        ret = m_qunp->unp_get_inputio_status(uint8_t(m),value);
        io_status = io_status + QString::asprintf("%d",*value)+" /";
    }
    io_status.remove(io_status.length()-1,1);
    info.inputioStatus = io_status.replace("0",tr("Low")).replace("1",tr("High"));

    io_status.clear();
    for(int m=1; m<=1; m++){
        ret = m_qunp->unp_get_outputio_status(uint8_t(m),value);
        io_status = io_status + QString::asprintf("%d",*value)+" /";
    }
    io_status.remove(io_status.length()-1,1);
    info.outputioStatus = io_status.replace("0",tr("Low")).replace("1",tr("High"));

    QSettings settings(QApplication::applicationDirPath()+"/config.ini",QSettings::IniFormat);
    settings.beginGroup("AiUnit");
    QString unit  = settings.value("A"+info.sn).toString();
    QString unit2 = settings.value("B"+info.sn).toString();
    settings.endGroup();

    float current1=0;
    float usrdata1=0;
    ret = m_qunp->unp_get_ai_value(1,&current1,&usrdata1);
    info.analog1Status = unit.isEmpty() ? QString("%2mA").arg(QString::asprintf("%.2f",static_cast<double>(current1))) : QString("%1%3(%2mA)").arg(QString::asprintf("%.2f",static_cast<double>(usrdata1))).arg(QString::asprintf("%.2f",static_cast<double>(current1))).arg(unit);

    float current2=0;
    float usrdata2=0;
    ret = m_qunp->unp_get_ai_value(2,&current2,&usrdata2);
    info.analog2Status = unit2.isEmpty() ? QString("%1mA").arg(QString::asprintf("%.2f",static_cast<double>(current2))) : QString("%1%3(%2mA)").arg(QString::asprintf("%.2f",static_cast<double>(usrdata2))).arg(QString::asprintf("%.2f",static_cast<double>(current2))).arg(unit2);

    float osl1 = 0;
    ret = m_qunp->unp_get_osl(1,&osl1);
    info.osl1 = QString::asprintf("%.2f",static_cast<double>(osl1));

    float osl2 = 0;
    ret = m_qunp->unp_get_osl(2,&osl2);
    info.osl2 = QString::asprintf("%.2f",static_cast<double>(osl2));

    float osh1 = 0;
    ret = m_qunp->unp_get_osh(1,&osh1);
    info.osh1 = QString::asprintf("%.2f",static_cast<double>(osh1));

    float osh2 = 0;
    ret = m_qunp->unp_get_osh(2,&osh2);
    info.osh2 = QString::asprintf("%.2f",static_cast<double>(osh2));

    if(structSupportModel.lora){
        uint8_t value[UNP_MAX_PKTSIZE]={0};
        uint8_t out[UNP_MAX_PKTSIZE]={0};

        ret = m_qunp->unp_get_lora(LORA_DEV_EUI,LORA_APP_EUI-LORA_DEV_EUI,value);
        memcpy(out, value, 8);
        info.devEui = hexToString(out,8);
        ret = m_qunp->unp_get_lora_status(LORA_SNR,LORA_CUR_DOWN_LINK_COUNTER-LORA_SNR+4, value );
        info.snr = QString::asprintf("%d",*reinterpret_cast<int8_t *>(value + LORA_SNR));
        info.rssi = QString::asprintf("%d",*reinterpret_cast <int16_t *>(value + LORA_RSSI));
        info.join_status = QString::asprintf("%d",*static_cast<uint8_t *>(value + LORA_JOIN_STATUS));
        info.chan = QString::asprintf("%d",*static_cast<uint8_t *>(value + LORA_CHAN));
        info.datarate = QString::asprintf("%d",*static_cast<uint8_t *>(value + LORA_DATARATE));
        info.rx2dr = QString::asprintf("%d",*static_cast<uint8_t *>(value + LORA_RX2DR));
        info.rx2freq = QString::asprintf("%d",*reinterpret_cast <uint32_t *>(value + LORA_RX2FREQ));
        info.maxEIRP = QString::asprintf("%d",*reinterpret_cast<int8_t *>(value + LORA_MAX_EIRP));
        info.receive_delay1 = QString::asprintf("%d",*reinterpret_cast <uint32_t *>(value + LORA_RECEIVE_DELAY1));
        info.receive_delay2 = QString::asprintf("%d",*reinterpret_cast <uint32_t *>(value + LORA_RECEIVE_DELAY2));
        info.cur_retry_counts = QString::asprintf("%d",*static_cast<uint8_t *>(value + LORA_CUR_RETRY_COUNTS));
        info.state = QString::asprintf("%d",*static_cast<uint8_t *>(value + LORA_STATE));
        info.cur_up_link_counter = QString::asprintf("%u",*reinterpret_cast<uint32_t *>(value + LORA_CUR_UP_LINK_COUNTER));
        info.cur_down_link_counter = QString::asprintf("%u",*reinterpret_cast<uint32_t *>(value + LORA_CUR_DOWN_LINK_COUNTER));
    }
    m_structPageStatus = info;
    emit getDeviceStatus(info);
}

/**
 * 读General
 * @brief UCXX22DealThread::getGeneralPage
 * @param list
 */
void UCXX22DealThread::getGeneralPage(QVariantList list)
{
    Q_UNUSED(list)

    unp_state_t ret;
    m_structPageGeneral.onlyTcpUdpMqttStatus = false;

    QunpUCXX22::app_mode_t am;
    ret = m_qunp->unp_get_app_mode(&am);
    m_structPageGeneral.application_mode = am;
//    curDevApplicationmode = am;

    uint32_t keepalive=0;
    ret = m_qunp->unp_get_mqtt_keepalive(&keepalive);
    QString tmp;
    tmp = QString::asprintf("%d",keepalive);
    m_structPageGeneral.keepAliveInterval = tmp;

    uint32_t reportingInterval=0;
    ret = m_qunp->unp_get_cloud_cycle(&reportingInterval);
    m_structPageGeneral.reportingInterval = QString::asprintf("%d",reportingInterval);

    uint8_t apn[UNP_APN_MAX_LENGTH]={0};
    uint8_t apn1[UNP_APN_USERNAME_LEN]={0};
    uint8_t apn2[UNP_APN_PASSWORD_LEN]={0};
    ret = m_qunp->unp_get_mobile_apn(apn,apn1,apn2);

    m_structPageGeneral.apn = QString::asprintf("%s",apn);
    m_structPageGeneral.apnUser = QString::asprintf("%s",apn1);
    m_structPageGeneral.apnPwd = QString::asprintf("%s",apn2);
#ifdef ODM_LHR_AZURE
    uint8_t authMode[1]={0};
    m_qunp->unp_get_azure_auth(authMode);
    m_structPageGeneral.authMode = QString::asprintf("%c",*authMode);
    curAzureAuthMode = m_structPageGeneral.authMode.toInt();

    uint8_t serAddr[256]={0};
    ret = m_qunp->unp_get_endpoint_addr(serAddr);
    if(ret){emit commandError(-1,ERROR_READ_GENGERAL,tr("Server Address")); return;}
    m_structPageGeneral.serverAddr = QString::asprintf("%s",serAddr);
#endif

    if(structSupportModel.aws || structSupportModel.data){
        uint8_t data[256]={0};
        uint8_t data1[256]={0};
        uint8_t data2[256]={0};
        uint16_t size = 256;
        QString da ;

        m_qunp->unp_get_rootcrt(data1,size);
        da = QString::asprintf("%s",data1);
        m_structPageGeneral.caFile = da.isEmpty()?"":"ca";

        m_qunp->unp_get_devcrt(data2,size);
        da = QString::asprintf("%s",data2);
        m_structPageGeneral.clientFile = da.isEmpty()?"":"client";

        m_qunp->unp_get_prikey(data,size);
        da = QString::asprintf("%s",data);
        m_structPageGeneral.clientKeyFile = da.isEmpty()?"":"key";

    }
    if(structSupportModel.aws){
        uint8_t serAddr[256]={0};
        ret = m_qunp->unp_get_endpoint_addr(serAddr);
        m_structPageGeneral.serverAddr = QString::asprintf("%s",serAddr);
    }

    if(structSupportModel.data){
        QunpUCXX22::app_tcpudp_t tcp_read;
        m_qunp->unp_get_tcpudp_config(&tcp_read);
        m_structPageGeneral.tcpkeepAlive = QString::asprintf("%d",tcp_read.keepalive_interval);
        m_structPageGeneral.customHeartbeat = QString::asprintf("%d",tcp_read.enable_custom_heartbeat);
        m_structPageGeneral.customContent = QString::asprintf("%s",tcp_read.custom_heartbeat);
        m_structPageGeneral.heartbeatInterval = QString::asprintf("%d",tcp_read.custom_heartbeat_interval);
        m_structPageGeneral.requireResponse = QString::asprintf("%d",tcp_read.custom_heartbeat_need_ack);
        m_structPageGeneral.responseContent = QString::asprintf("%s",tcp_read.server_ack);

        if(m_structPageStatus.ucpVer>=0x13){
            m_structPageGeneral.serverAddr1 = QString::asprintf("%s",tcp_read.server_name[0]);
            m_structPageGeneral.serverPort1 = QString::asprintf("%d",tcp_read.server_port[0]);

            m_structPageGeneral.serverAddr2 = QString::asprintf("%s",tcp_read.server_name[1]);
            m_structPageGeneral.serverPort2 = QString::asprintf("%d",tcp_read.server_port[1]);
        }else{
            m_structPageGeneral.serverAddr1 = QString::asprintf("%d.%d.%d.%d",tcp_read.server_ip[0][0],
                                                              tcp_read.server_ip[0][1],
                                                              tcp_read.server_ip[0][2],
                                                              tcp_read.server_ip[0][3]);
            m_structPageGeneral.serverPort1 = QString::asprintf("%d",tcp_read.server_port[0]);

            m_structPageGeneral.serverAddr2 = QString::asprintf("%d.%d.%d.%d",tcp_read.server_ip[1][0],
                                                              tcp_read.server_ip[1][1],
                                                              tcp_read.server_ip[1][2],
                                                              tcp_read.server_ip[1][3]);
            m_structPageGeneral.serverPort2 = QString::asprintf("%d",tcp_read.server_port[1]);
        }

        uint8_t tcpstatus[1] = {0};
        m_qunp->unp_get_tcpudp_status(tcpstatus);
        QString tmp ;
        tmp = QString::asprintf("%d",*tcpstatus);
        if(tmp.toInt() == 0){
            m_structPageGeneral.status1 = "Disconnected";
            m_structPageGeneral.status2 = "Disconnected";
        }else if(tmp.toInt() == 1){
            m_structPageGeneral.status2 = "Disconnected";
            m_structPageGeneral.status1 = "Connected";
        }else if(tmp.toInt() == 2){
            m_structPageGeneral.status2 = "Connected";
            m_structPageGeneral.status1 = "Disconnected";
        }else if(tmp.toInt() == 3){
            m_structPageGeneral.status1 = "Connected";
            m_structPageGeneral.status2 = "Connected";
        }

        QunpUCXX22::app_mqtt_t mqtt_read;
        m_qunp->unp_get_mqtt_config(&mqtt_read);

        m_structPageGeneral.userCreUsername = QString::asprintf("%s",mqtt_read.username);
        m_structPageGeneral.userCrePwd = QString::asprintf("%s",mqtt_read.password);
        m_structPageGeneral.userCreEnable = QString::asprintf("%d",mqtt_read.mqtt_enable_auth);
        m_structPageGeneral.tlsEnable = QString::asprintf("%d",mqtt_read.mqtt_enable_tls);
        m_structPageGeneral.brokerAddr = QString::asprintf("%s",mqtt_read.broker_addr);
        m_structPageGeneral.brokerPort = QString::asprintf("%d",mqtt_read.broker_port);
        m_structPageGeneral.clientID = QString::asprintf("%s",mqtt_read.clientid);
        m_structPageGeneral.connectTimeout = QString::asprintf("%d",mqtt_read.connect_timeout);
        m_structPageGeneral.mqttKeepAliveInterval = QString::asprintf("%d",mqtt_read.keepalive);
        qDebug()<<m_structPageGeneral.tcpkeepAlive<<m_structPageGeneral.userCreEnable;

        QunpUCXX22::unxx_onenet_setting_t onenet_read;
        m_qunp->unp_get_onenet_config(&onenet_read);
        m_structPageGeneral.oneNetKeepAlive = QString::asprintf("%d",onenet_read.keepalive);
        m_structPageGeneral.oneNetKey = QString::asprintf("%s",onenet_read.key);
        m_structPageGeneral.oneNetProductID = QString::asprintf("%s",onenet_read.productID);
    }

    if(structSupportModel.nb){
        QunpUCXX22::unxx_ali_setting_t ali;
        m_qunp->unp_get_ali_cfg(&ali);

        m_structPageGeneral.aliClientID = QString::asprintf("%s",ali.ali_clientID);
        m_structPageGeneral.aliProductKey = QString::asprintf("%s",ali.ali_ProductKey);
        m_structPageGeneral.aliDevSecret = QString::asprintf("%s",ali.ali_DeviceSecret);
        m_structPageGeneral.aliKeepAilve = QString::asprintf("%d",ali.keepalive);
        m_structPageGeneral.aliQos = QString::asprintf("%d",ali.qos);
    }

    float osl1 = 0;
    ret = m_qunp->unp_get_osl(1,&osl1);
    m_structPageGeneral.osl1 = QString::asprintf("%.2f",static_cast<double>(osl1));

    float osl2 = 0;
    ret = m_qunp->unp_get_osl(2,&osl2);
    m_structPageGeneral.osl2 = QString::asprintf("%.2f",static_cast<double>(osl2));

    float osh1 = 0;
    ret = m_qunp->unp_get_osh(1,&osh1);
    m_structPageGeneral.osh1 = QString::asprintf("%.2f",static_cast<double>(osh1));

    float osh2 = 0;
    ret = m_qunp->unp_get_osh(2,&osh2);
    m_structPageGeneral.osh2 = QString::asprintf("%.2f",static_cast<double>(osh2));


    //onenet
    QunpUCXX22::unxx_onenet_setting_t onenet;
    m_qunp->unp_get_onenet_config(&onenet);
    m_structPageGeneral.oneNetKeepAlive = QString::asprintf("%d",onenet.keepalive);
    m_structPageGeneral.oneNetKey = QString::asprintf("%s",onenet.key);
    m_structPageGeneral.oneNetProductID = QString::asprintf("%s",onenet.productID);

    uint8_t pin[UNP_PIN_MAX_LENGTH] = {0};
    ret = m_qunp->unp_get_cellular_pin(pin);
    m_structPageGeneral.pinCode = QString::asprintf("%s",pin);

    QunpUCXX22::cellular_network_t cn;
    ret = m_qunp->unp_get_cellular_net_type(&cn);
    m_structPageGeneral.network_type = cn;

    uint32_t collect = 0;
    ret = m_qunp->unp_get_collect_cycle(&collect);
    m_structPageGeneral.dataCollectInterval = QString::asprintf("%d",collect);

    emit getGeneral(m_structPageGeneral);
}

void UCXX22DealThread::getGeneralGPIO(QVariantList list)
{
    QVariantMap mapRead = list.at(0).toMap();
    StructPageGeneral m_structPageGeneral;
    switch (mapRead.value("readType").toInt()) {
    case RNS_GPIO2_COUNTER_REFRESH:{

        uint32_t value=0;
        uint8_t start=0;
        uint8_t mode=0;
        m_qunp->unp_get_11xx_gpio_counter(mapRead.value("counterNum").toInt(),&mode,&start,&value);
        m_structPageGeneral.gpioType = QString::asprintf("%d",mode);
        m_structPageGeneral.gpioCounterStart = QString::asprintf("%d",start);
        m_structPageGeneral.gpioCounter = QString::asprintf("%d",value);
    }
        break;
    case RNS_GPIO2_COUNTER_CLEAR:{
        m_qunp->unp_set_gpio_counter(mapRead.value("counterNum").toInt(),0);

        uint32_t value=0;
        uint8_t start=0;
        uint8_t mode=0;
        m_qunp->unp_get_11xx_gpio_counter(mapRead.value("counterNum").toInt(),&mode,&start,&value);
        m_structPageGeneral.gpioType = QString::asprintf("%d",mode);
        m_structPageGeneral.gpioCounterStart = QString::asprintf("%d",start);
        m_structPageGeneral.gpioCounter = QString::asprintf("%d",value);
    }
        break;
    case RNS_GPIO2_COUNTER_START:{
        qDebug()<<mapRead.value("start").toInt();
        m_qunp->unp_set_gpio_counter(mapRead.value("counterNum").toInt(),(uint32_t)mapRead.value("start").toInt());
    }
        break;
    default:
        break;
    }
    m_structPageGeneral.counterNum = mapRead.value("counterNum").toInt();
    m_structPageGeneral.readSpecial = 9999;
    m_structPageGeneral.readSpecialType = mapRead.value("readType").toInt();

    emit getGeneral(m_structPageGeneral);
}
/**
 * 设置Genneral
 * @brief UCXX22DealThread::setGeneralPage
 * @param list
 */
void UCXX22DealThread::setGeneralPage(QVariantList list)
{
    QVariantMap map = list.at(0).toMap();
    unp_state_t ret;

    if(!map.value("oldPwd").toString().isEmpty()){
        ret = m_qunp->unp_set_passwd(reinterpret_cast<uint8_t*>(map.value("oldPwd").toString().toLatin1().data()),reinterpret_cast<uint8_t*>(map.value("newPwd").toString().toLatin1().data()));
        if(ret == UNP_SUCCESS)m_loginPwd = map.value("newPwd").toString();
    }

    if(static_cast<uint32_t>(map.value("dataCollectInterval").toInt()) != 0){
        ret = m_qunp->unp_set_collect_cycle(static_cast<uint32_t>(map.value("dataCollectInterval").toInt()));
    }

    if(!map.value("pinCode").toString().isEmpty()){
        ret = m_qunp->unp_set_cellular_pin(reinterpret_cast<uint8_t*>(map.value("pinCode").toString().toLatin1().data()));
    }else{
        QString pincode="";
        ret = m_qunp->unp_set_cellular_pin(reinterpret_cast<uint8_t*>(pincode.toLatin1().data()));
    }
    ret = m_qunp->unp_set_cellular_net_type(static_cast<QunpUCXX22::cellular_network_t>(map.value("networkType").toInt()));

    if(structSupportModel.cloud){
        ret = m_qunp->unp_set_cloud_cycle(static_cast<uint32_t>(map.value("reportingInterval").toInt()));

        if(static_cast<QunpUCXX22::app_mode_t>(map.value("applicationMode").toInt()) == QunpUCXX22::APP_AWS
    #ifdef ODM_LHR_AZURE
            || static_cast<app_mode_t>(map.value("applicationMode").toInt()) == QunpUCXX22::APP_AZURE
    #endif
                ){
            ret = m_qunp->unp_set_mqtt_keepalive(static_cast<uint32_t>(map.value("keepAliveInterval").toInt()));

            if(!map.value("awsServerAddr").toString().isEmpty()){
                ret = m_qunp->unp_set_endpoint_addr(reinterpret_cast<uint8_t*>(map.value("awsServerAddr").toString().toLatin1().data()));
            }

        }else if(static_cast<QunpUCXX22::app_mode_t>(map.value("applicationMode").toInt()) == QunpUCXX22::APP_TCP){
            QunpUCXX22::app_tcpudp_t tcp_set;
            qDebug()<<map.value("customHeartbeatMode").toInt()<<map.value("serverAddr1").toString();
            tcp_set.keepalive_interval = static_cast<uint8_t>(map.value("tcpKeepAlive").toInt());
            tcp_set.enable_custom_heartbeat =static_cast<uint8_t>(map.value("customHeartbeatMode").toInt());
            snprintf(reinterpret_cast<char *>(tcp_set.custom_heartbeat) , 64 , "%s", map.value("customContent").toString().toLocal8Bit().data());
            snprintf(reinterpret_cast<char *>(tcp_set.server_ack) , 64 , "%s", map.value("responseContent").toString().toLocal8Bit().data());
            tcp_set.custom_heartbeat_interval = static_cast<uint16_t>(map.value("heartbeatInterval").toInt());
            tcp_set.custom_heartbeat_need_ack = static_cast<uint8_t>(map.value("requireResponse").toInt());

            if(m_structPageStatus.ucpVer>=0x13){
                snprintf(reinterpret_cast<char *>(tcp_set.server_name[0]) ,64 , "%s", map.value("serverAddr1").toString().toLocal8Bit().data());
                tcp_set.server_port[0] = static_cast<uint16_t>(map.value("serverPort1").toInt());

                snprintf(reinterpret_cast<char *>(tcp_set.server_name[1]) ,64 , "%s", map.value("serverAddr2").toString().toLocal8Bit().data());
                tcp_set.server_port[1] = static_cast<uint16_t>(map.value("serverPort2").toInt());
            }else{
                if(strIsIp(map.value("serverAddr1").toString())){
                    tcp_set.server_ip[0][0] = static_cast<uint8_t>(map.value("serverAddr1").toString().split(".").at(0).toInt());
                    tcp_set.server_ip[0][1] = static_cast<uint8_t>(map.value("serverAddr1").toString().split(".").at(1).toInt());
                    tcp_set.server_ip[0][2] = static_cast<uint8_t>(map.value("serverAddr1").toString().split(".").at(2).toInt());
                    tcp_set.server_ip[0][3] = static_cast<uint8_t>(map.value("serverAddr1").toString().split(".").at(3).toInt());
                    tcp_set.server_port[0]  = static_cast<uint16_t>(map.value("serverPort1").toInt());
                }

                if(strIsIp(map.value("serverAddr2").toString())){
                    tcp_set.server_ip[1][0] = static_cast<uint8_t>(map.value("serverAddr2").toString().split(".").at(0).toInt());
                    tcp_set.server_ip[1][1] = static_cast<uint8_t>(map.value("serverAddr2").toString().split(".").at(1).toInt());
                    tcp_set.server_ip[1][2] = static_cast<uint8_t>(map.value("serverAddr2").toString().split(".").at(2).toInt());
                    tcp_set.server_ip[1][3] = static_cast<uint8_t>(map.value("serverAddr2").toString().split(".").at(3).toInt());
                    tcp_set.server_port[1] = static_cast<uint16_t>(map.value("serverPort2").toInt());
                }
            }

            m_qunp->unp_set_tcpudp_config(&tcp_set);

        }else if(static_cast<QunpUCXX22::app_mode_t>(map.value("applicationMode").toInt()) == QunpUCXX22::APP_UDP){
            QunpUCXX22::app_tcpudp_t udp_set;
            udp_set.keepalive_interval =static_cast<uint8_t>(map.value("tcpKeepAlive").toInt());
            udp_set.enable_custom_heartbeat = static_cast<uint8_t>(map.value("customHeartbeatMode").toInt());
            snprintf(reinterpret_cast<char *>(udp_set.custom_heartbeat), 64 , "%s", map.value("customContent").toString().toLocal8Bit().data());
            snprintf(reinterpret_cast<char *>(udp_set.server_ack) , 64 , "%s", map.value("responseContent").toString().toLocal8Bit().data());
            udp_set.custom_heartbeat_interval = static_cast<uint16_t>(map.value("heartbeatInterval").toInt());
            udp_set.custom_heartbeat_need_ack = static_cast<uint8_t>(map.value("requireResponse").toInt());

            if(m_structPageStatus.ucpVer>=0x13){
                snprintf(reinterpret_cast<char *>(udp_set.server_name[0]), 64 , "%s", map.value("serverAddr1").toString().toLocal8Bit().data());
                udp_set.server_port[0] = static_cast<uint16_t>(map.value("serverPort1").toInt());

                snprintf(reinterpret_cast<char *>(udp_set.server_name[1]), 64 , "%s", map.value("serverAddr2").toString().toLocal8Bit().data());
                udp_set.server_port[1] = static_cast<uint16_t>(map.value("serverPort2").toInt());
            }else{
                if(strIsIp(map.value("serverAddr1").toString())){
                    udp_set.server_ip[0][0] = static_cast<uint8_t>(map.value("serverAddr1").toString().split(".").at(0).toInt());
                    udp_set.server_ip[0][1] = static_cast<uint8_t>(map.value("serverAddr1").toString().split(".").at(1).toInt());
                    udp_set.server_ip[0][2] = static_cast<uint8_t>(map.value("serverAddr1").toString().split(".").at(2).toInt());
                    udp_set.server_ip[0][3] = static_cast<uint8_t>(map.value("serverAddr1").toString().split(".").at(3).toInt());
                    udp_set.server_port[0]  = static_cast<uint16_t>(map.value("serverPort1").toInt());
                }

                if(strIsIp(map.value("serverAddr2").toString())){
                    udp_set.server_ip[1][0] = static_cast<uint8_t>(map.value("serverAddr2").toString().split(".").at(0).toInt());
                    udp_set.server_ip[1][1] = static_cast<uint8_t>(map.value("serverAddr2").toString().split(".").at(1).toInt());
                    udp_set.server_ip[1][2] = static_cast<uint8_t>(map.value("serverAddr2").toString().split(".").at(2).toInt());
                    udp_set.server_ip[1][3] = static_cast<uint8_t>(map.value("serverAddr2").toString().split(".").at(3).toInt());
                    udp_set.server_port[1 ] = static_cast<uint16_t>(map.value("serverPort2").toInt());
                }
            }

            m_qunp->unp_set_tcpudp_config(&udp_set);

        }else if(static_cast<QunpUCXX22::app_mode_t>(map.value("applicationMode").toInt()) == QunpUCXX22::APP_MQTT){
            QunpUCXX22::app_mqtt_t mqtt_set;
            snprintf(reinterpret_cast<char *>(mqtt_set.broker_addr) , 64 , "%s", map.value("brokerAddr").toString().toLocal8Bit().data());
            snprintf(reinterpret_cast<char *>(mqtt_set.clientid ), UNP_MQTT_CLIENTID_LEN + 1 , "%s", map.value("clientID").toString().toLocal8Bit().data());
            snprintf(reinterpret_cast<char *>(mqtt_set.username) , UNP_MQTT_USERNAME_LEN + 1 , "%s", map.value("mqttUsername").toString().toLocal8Bit().data());
            snprintf(reinterpret_cast<char *>(mqtt_set.password) , UNP_MQTT_PASSWORD_LEN + 1 , "%s", map.value("mqttPwd").toString().toLocal8Bit().data());

            mqtt_set.broker_port = static_cast<uint16_t>(map.value("brokerPort").toInt());
            mqtt_set.keepalive = static_cast<uint32_t>(map.value("mqttKeepAliveInterval").toInt());
            mqtt_set.connect_timeout = static_cast<uint32_t>(map.value("connectTimeout").toInt());
            mqtt_set.mqtt_enable_auth = static_cast<uint8_t>(map.value("mqttUserCre").toInt());
            mqtt_set.mqtt_enable_tls = static_cast<uint8_t>(map.value("mqttTlsEnable").toInt());

            m_qunp->unp_set_mqtt_config(&mqtt_set);
        }else if(static_cast<QunpUCXX22::app_mode_t>(map.value("applicationMode").toInt()) == QunpUCXX22::APP_URSALINK_CLOUD){
            ret = m_qunp->unp_set_mqtt_keepalive(static_cast<uint32_t>(map.value("keepAliveInterval").toInt()));

        }else if(static_cast<QunpUCXX22::app_mode_t>(map.value("applicationMode").toInt()) == QunpUCXX22::APP_ALI){
            QunpUCXX22::unxx_ali_setting_t ali;
            snprintf(reinterpret_cast<char *>(ali.ali_clientID) , UNP_MQTT_CLIENTID_LEN + 1 , "%s", map.value("aliyunClientID").toString().toLocal8Bit().data());
            snprintf(reinterpret_cast<char *>(ali.ali_ProductKey) , 16 + 1 , "%s", map.value("aliyunProductKey").toString().toLocal8Bit().data());
            snprintf(reinterpret_cast<char *>(ali.ali_DeviceSecret) , 64 + 1 , "%s", map.value("aliyunDeviceSecret").toString().toLocal8Bit().data());
            ali.keepalive = static_cast<uint32_t>(map.value("aliyunKeepAliveInterval").toInt());
            ali.qos = static_cast<QunpUCXX22::Qos>(map.value("aliyunQoS").toInt());
            m_qunp->unp_set_ali_cfg(&ali);
        }else if(static_cast<QunpUCXX22::app_mode_t>(map.value("applicationMode").toInt()) == QunpUCXX22::APP_ONENET){
            QunpUCXX22::unxx_onenet_setting_t onenet;
            onenet.qos=0;
            onenet.keepalive = static_cast<uint32_t>(map.value("oneNetKeepAlive").toInt());
            snprintf(reinterpret_cast<char *>(onenet.key) , 64 + 1 , "%s", map.value("oneNetKey").toString().toLocal8Bit().data());
            snprintf(reinterpret_cast<char *>(onenet.productID) , 32 + 1 , "%s", map.value("oneNetProductID").toString().toLocal8Bit().data());
            m_qunp->unp_set_onenet_config(&onenet);
        }

        if(!map.value("apn").toString().isEmpty()){
            qDebug()<<map.value("apn").toString()<<map.value("apnUser").toString()<<map.value("apnPwd").toString();
            ret = m_qunp->unp_set_mobile_apn(reinterpret_cast<uint8_t*>(map.value("apn").toString().toLatin1().data()),
                                             reinterpret_cast<uint8_t*>(map.value("apnUser").toString().toLatin1().data()),
                                             reinterpret_cast<uint8_t*>(map.value("apnPwd").toString().toLatin1().data()));
        }else{
            uint8_t z[1]={0};
            ret = m_qunp->unp_set_mobile_apn(z,reinterpret_cast<uint8_t*>(map.value("apnUser").toString().toLatin1().data()),
                                             reinterpret_cast<uint8_t*>(map.value("apnPwd").toString().toLatin1().data()));
        }
    }

    ret = m_qunp->unp_set_osh(1, map.value("osh").toFloat());

    ret = m_qunp->unp_set_osl(1, map.value("osl").toFloat());

    ret = m_qunp->unp_set_osh(2, map.value("osh2").toFloat());

    ret = m_qunp->unp_set_osl(2, map.value("osl2").toFloat());

    if(structSupportModel.lora){
        if(m_proName.contains("1114")){
            m_qunp->unp_set_gpio_counter(1,map.value("gpioCounter1Enable").toInt());
            m_qunp->unp_set_gpio_counter(2,map.value("gpioCounter2Enable").toInt());
        }else if(m_proName.contains("1152") || m_proName.contains("1122")){
            m_qunp->unp_set_gpio_counter(1,map.value("gpioCounter1Enable").toInt());
        }
    }


    if(structSupportModel.cloud){
        if(m_structPageGeneral.application_mode != map.value("applicationMode").toInt()){
            ret = m_qunp->unp_set_app_mode(static_cast<QunpUCXX22::app_mode_t>(map.value("applicationMode").toInt()));
            waitTime(8000);
        }
    #ifdef ODM_LHR_AZURE
        if(curAzureAuthMode != map.value("authMode").toInt()){
            m_qunp->unp_set_azure_auth((uint8_t*)map.value("authMode").toString().toLatin1().data());
            waitTime(8000);
        }
    #endif
    }


    emit waitingVisible(false);
}

/**
 * 导入认证文件
 * @brief UCXX22DealThread::setImportAwdFile
 * @param list
 */
void UCXX22DealThread::setImportAwdFile(QVariantList list)
{
    unp_state_t ret= UNP_SUCCESS;
    QVariantMap map = list.at(0).toMap();
    uint8_t *pdata;
    uint16_t size ;

    if(map.value("delete").toBool()){
        size = 128;
        pdata = reinterpret_cast<uint8_t*>(malloc(size));
        memset(pdata,0,128);
    }else{
        QString path;
        if(map.value("fileType").toString() == "CA"){
            path = map.value("caFilePath").toString();
        }else if(map.value("fileType").toString() == "Client Certificate"){
            path = map.value("cliCerFilePath").toString();
        }else if(map.value("fileType").toString() == "Client Key"){
            path = map.value("cliKeyFilePath").toString();
        }

        FILE *fp;
        uint8_t imagepath[512]={0};
        snprintf(reinterpret_cast<char *>(imagepath),sizeof(imagepath),"%s",path.toLocal8Bit().data());

        fp = fopen(reinterpret_cast<char *>(imagepath),"rb");
        if(!fp){
            if(map.value("fileType").toString() == "CA"){
                path = map.value("caFilePath").toString();
            }else if(map.value("fileType").toString() == "Client Certificate"){
                path = map.value("cliCerFilePath").toString();
            }else if(map.value("fileType").toString() == "Client Key"){
                path = map.value("cliKeyFilePath").toString();
            }
            emit sendMsgWnd(tr("%1 File Open").arg(map.value("fileType").toString()));
            return;
        }
        fseek(fp,0,SEEK_END);
        size = static_cast<uint16_t>(ftell(fp));
        pdata =reinterpret_cast<uint8_t*>(malloc(size));
        if(!pdata){
            emit sendMsgWnd(tr("%1 File Open").arg(map.value("fileType").toString()));
            return;
        }
        fseek(fp,0,SEEK_SET);
        fread(pdata, 1, size, fp);
        fclose(fp);
    }
    if(map.value("fileType").toString() == "CA"){
        ret = m_qunp->unp_set_update_rootcrt(pdata,(size));
    }else if(map.value("fileType").toString() == "Client Certificate"){
        ret = m_qunp->unp_set_update_devcrt(pdata,(size));
    }else if(map.value("fileType").toString() == "Client Key"){
        ret = m_qunp->unp_set_update_prikey(pdata,(size));
    }
    emit waitingVisible(false);
}

/**
 * 读lorawan
 * @brief UC11T1DealThread::getLorawanPage
 * @param list
 */
void UCXX22DealThread::getLorawanPage(QVariantList list)
{
    Q_UNUSED(list)

    uint8_t value[UNP_MAX_PKTSIZE]={0};
    uint8_t out[UNP_MAX_PKTSIZE]={0};
    int ret = 0;

    StructPageLorawan info;

    uint32_t report_interval=0;
    ret |= m_qunp->unp_get_cloud_cycle(&report_interval);
    info.regularReport = QString::asprintf("%d",report_interval);

    ret |= m_qunp->unp_get_lora(LORA_MODE,LORA_FREQ-LORA_MODE,value);

    memcpy(out, value+LORA_MODE,2 );
    info.mode = QString::asprintf("%d",out[0]);

    memcpy(out, value+LORA_OTA, 2);
    info.ota = QString::asprintf("%d",out[0]);
    m_otaType = info.ota;
    info.ota = QString::number(1-info.ota.toInt());

    memcpy(out, value+LORA_ADR, 2);
    info.adr = QString::asprintf("%d",out[0]);
    info.netId = QString::asprintf("%06x",*reinterpret_cast<uint32_t *>(value + LORA_NET_ID));

    memcpy(out, value+LORA_DEV_ADDR, 2);
    info.devAddr = QString::asprintf("%08x",*reinterpret_cast<uint32_t *>(value + LORA_DEV_ADDR));

    memcpy(out, value+LORA_DEV_EUI, 16);
    info.devEui = hexToString(out,16);

    memcpy(out, value+LORA_APP_EUI, 16);
    info.appEui = hexToString(out,16);

    memcpy(out, value+LORA_NWKS_KEY, 32);
    info.nwksKey = hexToString(out,32);

    memcpy(out, value+LORA_APPS_KEY, 32);
    info.appsKey = hexToString(out,32);

    memcpy(out, value+LORA_APP_KEY, 32);
    info.appKey = hexToString(out,32);

    info.rxWinDelay1 = QString::asprintf("%d",*reinterpret_cast<uint32_t *>(value + LORA_RX_WIN_DELAY1));

    info.rxWinDelay2 = QString::asprintf("%d",*reinterpret_cast<uint32_t *>(value + LORA_RX_WIN_DELAY2));

    info.joinDelay1 = QString::asprintf("%d",*reinterpret_cast<uint32_t *>(value + LORA_JOIN_DELAY1));

    info.joinDelay2 = QString::asprintf("%d",*reinterpret_cast<uint32_t *>(value + LORA_JOIN_DELAY2));

    memcpy(out, value+LORA_TX_POWER, 2);
    info.txPower = QString::asprintf("%d",out[0]);

    memcpy(out, value+LORA_APP_PORT, 2);
    info.appPort = QString::asprintf("%d",out[0]);

    memcpy(out, value+LORA_CONFIRM, 2);
    info.confirm = QString::asprintf("%d",out[0]);

    info.chanMask = QString::asprintf("%04x",*reinterpret_cast<uint16_t *>(value + LORA_CHAN_MASK));

    qDebug()<<info.chanMask<<info.confirm<<info.appPort;

    memset(value,0,UNP_MAX_PKTSIZE);
    ret |= m_qunp->unp_get_lora(LORA_FREQ,LORA_REGION-LORA_FREQ+1,value);

    int freOffset = 0;
    memcpy(out, value+freOffset, 4);
    freOffset += 5;
    info.fre0 = QString::asprintf("%d",*reinterpret_cast<uint32_t *>(out));

    memcpy(out, value+freOffset, 4);
    freOffset += 5;
    info.fre1 = QString::asprintf("%d",*reinterpret_cast<uint32_t *>(out));

    memcpy(out, value+freOffset, 4);
    freOffset += 5;
    info.fre2 = QString::asprintf("%d",*reinterpret_cast<uint32_t *>(out));

    memcpy(out, value+freOffset, 4);
    freOffset += 5;
    info.fre3 = QString::asprintf("%d",*reinterpret_cast<uint32_t *>(out));

    memcpy(out, value+freOffset, 4);
    freOffset += 5;
    info.fre4 = QString::asprintf("%d",*reinterpret_cast<uint32_t *>(out));

    memcpy(out, value+freOffset, 4);
    freOffset += 5;
    info.fre5 = QString::asprintf("%d",*reinterpret_cast<uint32_t *>(out));

    memcpy(out, value+freOffset, 4);
    freOffset += 5;
    info.fre6 = QString::asprintf("%d",*reinterpret_cast<uint32_t *>(out));

    memcpy(out, value+freOffset, 4);
    freOffset += 5;
    info.fre7 = QString::asprintf("%d",*reinterpret_cast<uint32_t *>(out));

    memset(out,0,UNP_MAX_PKTSIZE);
    memcpy(out, value+LORA_DEFDR-LORA_FREQ, 2);

    info.defDr = QString::asprintf("%d",out[0]);

    ret |= m_qunp->unp_get_lora(LORA_LINKWAN_FREQ_MODE,1,value);
    memcpy(out, value, 2);
    info.linkwanFreqMode = QString::asprintf("%d",out[0]);
    m_linkwanFreMode=info.linkwanFreqMode;

    ret |= m_qunp->unp_get_lora(LORA_VERSION,1,value);
    memcpy(out, value, 2);
    info.loraVersion = QString::asprintf("%d",out[0]);

    info.win2Feq = QString::asprintf("%d",*reinterpret_cast<uint32_t *>(value + LORA_WIN2_FEQ-LORA_FREQ));
    memcpy(out, value+LORA_WIN2_FEQ-LORA_FREQ, 2);

    info.win2Dr = QString::asprintf("%d",out[0]);
    info.globalDutyRate = QString::asprintf("%d",*reinterpret_cast<uint32_t *>(value + LORA_DUTY_CYCLE_VALUE-LORA_FREQ));
    info.dutyCycleOn = QString::asprintf("%d",*static_cast<uint8_t *>(value + LORA_DUTY_CYCLE_SWITCH-LORA_FREQ));
    info.joinRetries = QString::asprintf("%d",*static_cast<uint8_t *>(value + LORA_JOIN_RETRIES-LORA_FREQ));
    info.retriesTx = QString::asprintf("%d",*static_cast<uint8_t *>(value + LORA_RETRIES_TX-LORA_FREQ));
    info.ackTimeout = QString::asprintf("%d",*reinterpret_cast<uint32_t *>(value + LORA_ACK_TIMEOUT-LORA_FREQ));
    info.linkCheck = QString::asprintf("%d",*static_cast<uint8_t *>(value + LORA_LINK_CHECK-LORA_FREQ));
    info.syncWord = QString::asprintf("%d",*static_cast<uint8_t *>(value + LORA_SYNC_WORD-LORA_FREQ));
    info.region = QString::asprintf("%d",*static_cast<uint8_t *>(value + LORA_REGION-LORA_FREQ));

    ret |= m_qunp->unp_get_lora(LORA_UP_LINK_COUNTER ,LORA_DOWN_LINK_COUNTER - LORA_UP_LINK_COUNTER+4,value);
    info.upLinkCounter  = QString::asprintf("%u",*reinterpret_cast<uint32_t *>(value + LORA_UP_LINK_COUNTER-LORA_UP_LINK_COUNTER));
    info.downLinkCounter = QString::asprintf("%u",*reinterpret_cast<uint32_t *>(value + LORA_DOWN_LINK_COUNTER-LORA_UP_LINK_COUNTER));

    ret |= m_qunp->unp_get_lora(LORA_RS232_PORT,1,value);
    memcpy(out, value, 2);
    info.rs232Port = QString::asprintf("%d",out[0]);

    ret |= m_qunp->unp_get_lora(LORA_MAX_CONFIRM_ENABLE,1,value);
    memcpy(out, value, 2);
    info.rejoin = QString::asprintf("%d",out[0]);

    ret |= m_qunp->unp_get_lora(LORA_MAX_CONFIRM_NUM,1,value);
    memcpy(out, value, 2);
    info.rejoinCount = QString::asprintf("%d",out[0]);

    ret |= m_qunp->unp_get_lora(LORA_CHANNELMASK15_95,10,value);
    info.chanMask16_31 = QString::asprintf("%04x",*reinterpret_cast<uint16_t *>(value+0));
    info.chanMask32_47 = QString::asprintf("%04x",*reinterpret_cast<uint16_t *>(value+2));
    info.chanMask48_63 = QString::asprintf("%04x",*reinterpret_cast<uint16_t *>(value+4));
    info.chanMask64_79 = QString::asprintf("%04x",*reinterpret_cast<uint16_t *>(value+6));
    info.chanMask80_95 = QString::asprintf("%04x",*reinterpret_cast<uint16_t *>(value+8));

    emit getLorawan(info);
}

/**
 * 设置lorawan
 * @brief UC11T1DealThread::setLorawanPage
 * @param list
 */
void UCXX22DealThread::setLorawanPage(QVariantList list)
{
    QVariantMap map = list.at(0).toMap();
    QString otaTmp;
    uint8_t dataHex[256] = {0};
    int ret=0;
    int afterWrite=0; //0:不操作 1：reboot 2:reset 3:lora reload

    qDebug()<<map.value("basicModify").toBool()<<map.value("advancedModify").toBool()<<map.value("channelModify").toBool();
    if(map.value("basicModify").toBool()){
        QVariantMap basicMap = map.value("loraBasic").toMap();

        if(!basicMap.value("devEui").toString().contains("***")){
            stringToHex(basicMap.value("devEui").toString(),dataHex);
            ret |= m_qunp->unp_set_lora(dataHex, LORA_DEV_EUI, 8);
            memset(dataHex,0,256);
        }


        stringToHex(basicMap.value("appEui").toString(),dataHex);
        m_qunp->unp_set_lora(dataHex, LORA_APP_EUI, 8);
        memset(dataHex,0,256);

        ret |= m_qunp->unp_set_lora(static_cast<uint8_t>(basicMap.value("rs232Port").toInt()),LORA_RS232_PORT);

        stringToHex(basicMap.value("workingMode").toString(),dataHex);
        ret |= m_qunp->unp_set_lora(dataHex, LORA_MODE, 1);
        memset(dataHex,0,256);


        if(!basicMap.value("appKey").toString().contains("***")){
            qDebug()<<basicMap.value("appKey").toString();
            stringToHex(basicMap.value("appKey").toString(),dataHex);
            ret |= m_qunp->unp_set_lora(dataHex, LORA_APP_KEY, 16);
            memset(dataHex,0,256);
        }

        stringToHex2(basicMap.value("networkId").toString(),dataHex);
        ret |= m_qunp->unp_set_lora(dataHex,LORA_NET_ID,4);
        memset(dataHex,0,256);


        if(!basicMap.value("devAddr").toString().contains("***")){
            stringToHex2(basicMap.value("devAddr").toString(),dataHex);
            ret |= m_qunp->unp_set_lora(dataHex,LORA_DEV_ADDR,4);
            memset(dataHex,0,256);
        }

        if(!basicMap.value("networkSessionkey").toString().contains("***")){
            stringToHex(basicMap.value("networkSessionkey").toString(),dataHex);
            ret |= m_qunp->unp_set_lora(dataHex, LORA_NWKS_KEY, 16);
            memset(dataHex,0,256);
        }

        if(!basicMap.value("appSessionKey").toString().contains("***")){
            stringToHex(basicMap.value("appSessionKey").toString(),dataHex);
            ret |= m_qunp->unp_set_lora(dataHex, LORA_APPS_KEY, 16);
            memset(dataHex,0,256);
        }

        ret |= m_qunp->unp_set_lora(static_cast<uint8_t>(basicMap.value("adrMode").toInt()),LORA_ADR);
        ret |= m_qunp->unp_set_lora(static_cast<uint8_t>(basicMap.value("comfirmMode").toInt()),LORA_CONFIRM);


        ret |= m_qunp->unp_set_lora(static_cast<uint8_t>(basicMap.value("datarate").toInt()),LORA_DEFDR);
        stringToHex(basicMap.value("loraVersion").toString(),dataHex);
        ret |= m_qunp->unp_set_lora(dataHex, LORA_VERSION, 1);
        memset(dataHex,0,256);

        if(m_linkwanFreMode != basicMap.value("linkwanFreMode").toString()){
            m_qunp->unp_set_lora(static_cast<uint8_t>(basicMap.value("linkwanFreMode").toInt()),LORA_LINKWAN_FREQ_MODE);
            m_linkwanFreMode = basicMap.value("linkwanFreMode").toString();
            afterWrite=3;
        }
        otaTmp = QString::number(1-basicMap.value("joinType").toInt());
        ret |= m_qunp->unp_set_lora(static_cast<uint8_t>(1-basicMap.value("joinType").toInt()),LORA_OTA);

        stringToHex(basicMap.value("loraVersion").toString(),dataHex);
        ret |= m_qunp->unp_set_lora(dataHex, LORA_VERSION, 1);
        memset(dataHex,0,256);

        map.insert("deviceCmd",0);
        if(m_otaType != otaTmp){
            m_otaType = otaTmp;
            map.insert("deviceCmd",2);
            if(!m_bNFC){
                afterWrite=1;
            }
        }else{
            qDebug()<<map.value("deviceCmd").toInt();
            map.insert("deviceCmd",1);
            if(!m_bNFC){
                afterWrite=3;
            }
        }
    }

    if(map.value("advancedModify").toBool()){
        QVariantMap advanceMap = map.value("loraAdvanced").toMap();

        ret = m_qunp->unp_set_lora(static_cast<uint32_t>(advanceMap.value("joinDelay1").toInt()),LORA_JOIN_DELAY1,4);
        ret = m_qunp->unp_set_lora(static_cast<uint32_t>(advanceMap.value("receiveDelay1").toInt()),LORA_RX_WIN_DELAY1,4);
        ret = m_qunp->unp_set_lora(static_cast<uint32_t>(advanceMap.value("receiveDelay2").toInt()),LORA_RX_WIN_DELAY2,4);
        ret = m_qunp->unp_set_lora(static_cast<uint8_t>(advanceMap.value("txPower").toInt()),LORA_TX_POWER);

        QString rx2Fre =  advanceMap.value("rx2Fre").toString()+"00";
        memset(dataHex,0,256);
        stringToHex2(QString::number(rx2Fre.toInt(),16),dataHex);

        ret = m_qunp->unp_set_lora(dataHex,LORA_WIN2_FEQ,4);
        ret = m_qunp->unp_set_lora(static_cast<uint8_t>(advanceMap.value("rx2Datarate").toInt()),LORA_WIN2_DR);
        ret = m_qunp->unp_set_lora(static_cast<uint32_t>(advanceMap.value("dutyCycle").toInt()),LORA_DUTY_CYCLE_VALUE,4);
        ret = m_qunp->unp_set_lora(static_cast<uint8_t>(advanceMap.value("dutyCycleSwitch").toInt()),LORA_DUTY_CYCLE_SWITCH);
        ret = m_qunp->unp_set_lora(static_cast<uint8_t>(advanceMap.value("joinTrials").toInt()),LORA_JOIN_RETRIES);
        ret = m_qunp->unp_set_lora(static_cast<uint8_t>(advanceMap.value("retx").toInt()),LORA_RETRIES_TX);
        ret = m_qunp->unp_set_lora(static_cast<uint32_t>(advanceMap.value("actTimeout").toInt()),LORA_ACK_TIMEOUT,4);
        ret = m_qunp->unp_set_lora(static_cast<uint32_t>(advanceMap.value("uplinkFrameCounter").toInt()),LORA_UP_LINK_COUNTER,4);
        ret = m_qunp->unp_set_lora(static_cast<uint32_t>(advanceMap.value("downlinkFrameCounter").toInt()),LORA_DOWN_LINK_COUNTER,4);
        afterWrite = 3;
    }

//    bool freChangeFlag=false;
    if(map.value("channelModify").toBool()){
        map.insert("deviceCmd",1);
        if(map.value("loraChannel").toMap().value("fixedFre").toBool()){
            setLoraChannel2(list);
        }else{
            setLoraChannel(list);
        }

        qDebug()<<"loraChannel change "<<map.value("isBackup").toString()
                     <<map.value("loraChannel").toMap().value("frequenceIndex").toInt()
                    <<map.value("loraChannel").toMap().value("frequenceName").toString();
        //改变频段pn
        if(!m_proName.contains(map.value("loraChannel").toMap().value("frequenceName").toString().mid(2,3))){
            qDebug()<<map.value("loraChannel").toMap().value("frequenceName").toString();
            m_qunp->unp_set_product_pn(reinterpret_cast<uint8_t*>(map.value("loraChannel").toMap().value("frequenceName").toString().toLatin1().data()));
            waitTime(100);
//            freChangeFlag = true;

            if(!m_bNFC){
                afterWrite=1;
            }

        }else{
            afterWrite=3;
        }
    }

    qDebug()<<map.value("deviceCmd").toInt()<<map.value("writeToFlash").toBool()<<afterWrite;
    if(m_bNFC && map.value("writeToFlash").toBool()){
        list.clear();
        list.append(map);
//        nfcWriteFlash(list,freChangeFlag);
    }
    if(afterWrite == 2){
        resetDevice(list,false);
    }else if(afterWrite == 1){
        if(!m_bNFC){
            m_qunp->unp_send_reboot_request();
            waitTime(8000);
        }
    }else if(afterWrite == 3){
        m_qunp->unp_set_lora_reload_config();
        waitTime(4000);
    }

    emit waitingVisible(false);
}

/**
 * 读设置
 * @brief UCXX22DealThread::getSettingPage
 * @param list
 */
void UCXX22DealThread::getSettingPage(QVariantList list)
{
    Q_UNUSED(list)
    emit getSetting(m_structPageSetting);
}

/**
 * 写入设置界面
 * @brief UCXX22DealThread::setSettingPage
 * @param list
 */
void UCXX22DealThread::setSettingPage(QVariantList list)
{

    emit waitingVisible(false);
}

/**
 * 升级
 * @brief UCXX22DealThread::toUpgrade
 * @param list
 */
void UCXX22DealThread::toUpgrade(QVariantList list)
{
    QVariantMap map = list.at(0).toMap();
    uint8_t *pdata;
    uint64_t imageflag1=0x1111222233334444;
    uint32_t pos = 16;
    uint32_t image1Offset = 0;
    uint32_t size ;
    uint32_t imageVer = 0;
    QString pathName = map.value("imageName").toString();
    FILE *fp;
    uint64_t imf;
    uint8_t imagepath[512];
    snprintf(reinterpret_cast<char*>(imagepath),sizeof(imagepath),"%s",pathName.toLocal8Bit().data());

    fp = fopen(reinterpret_cast<char*>(pathName.toLocal8Bit().data()),"rb");
    if(!fp){
        emit upgradeProgress(FileOpenFail1);
        goto END_FLAG;
    }
    fseek(fp,0,SEEK_END);
    size  = static_cast<uint32_t>(ftell(fp));
    pdata = static_cast<uint8_t*>(malloc(size));


    if(!pdata){
        emit upgradeProgress(SpaceError);
        goto END_FLAG;
    }

    fseek(fp, 0, SEEK_SET);
//    fread(pdata, 1, size, fp);
    fclose(fp);

    imf = *reinterpret_cast <uint64_t *>(pdata);
//    printf("====##====== %016x  %016x\n ",aa, aa);
//    for(int i=0; i<8; i++){
//        printf("%x",pdata[i]);
//    }
//    printf("\n");

    if(imf == imageflag1){
        pos = 64;
        image1Offset = 8;
        imageVer = 1;
    }else{
        pos = 32;
    }

    qDebug()<< "offset pos: "<<pos << image1Offset<<imageVer;

    emit upgradeProgress(0);

    emit waitingVisible(false);
    if(m_bNFC){

    }else{

        if(m_qunp->unp_send_upgrade_request() == UNP_SUCCESS){
            emit upgradeProgress(2);

            m_qunp->close_serialport();
//            m_qunp->auto_close_serialport();
            waitTime(7000);
//            m_qunp->auto_reopen_serialport();

            m_qunp->reopen_serialport();

            uint8_t hwver_offset = 0, swver_offset = 0;

            hwver_offset = 12;
            swver_offset = 16;

            qDebug()<<hwver_offset<<swver_offset;
            if(m_qunp->unp_upgrade_check(*reinterpret_cast <uint32_t *>(pdata+image1Offset), pdata +4 +image1Offset, pdata + hwver_offset + image1Offset, pdata + swver_offset + image1Offset,
                                         pdata + swver_offset +4 + image1Offset,imageVer ) == UNP_SUCCESS){
                emit upgradeProgress(3);
                size -= pos;
                imageDataSize = size;
                if(m_qunp->unp_send_upgrade_image(pdata + pos, size) == UNP_SUCCESS){
                    emit upgradeProgress(99);
                    waitTime(1000);
                    if(m_qunp->unp_upgrade_complete() == UNP_SUCCESS){
                        waitTime(9000);
                        emit upgradeProgress(UpgradeOK);
                    }else{
                        emit upgradeProgress(FileOpenFail);
                    }
                }else{
                    emit upgradeProgress(FileOpenFail);
                }
            }else{
                emit upgradeProgress(FileOpenFail);
            }
        }else{
            emit upgradeProgress(RequestError);
        }
    }

END_FLAG:
    emit waitingVisible(false);
}

/**
 * 重置设备
 * @brief unpThread::resetDevice
 * @param showTip
 */
void UCXX22DealThread::resetDevice(QVariantList list, bool showTip)
{
    Q_UNUSED(showTip)
    Q_UNUSED(list)
    if(m_qunp->unp_reset_device() != UNP_SUCCESS){
        emit upgradeProgress(ResetFail);
        return;
    }

    waitTime(2000);

    emit waitingVisible(false);
}

bool UCXX22DealThread::strIsIp(QString str)
{
    if(str.split(".").size() == 4){
        int a = str.split(".").at(0).toInt();
        int b = str.split(".").at(1).toInt();
        int c = str.split(".").at(2).toInt();
        int d = str.split(".").at(3).toInt();
        if((a <= 255 && a >= 0)&&(b <= 255 && b >= 0)&&(c <= 255 && c >= 0)&&(d <= 255 && d >= 0)){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}


void UCXX22DealThread::setSupportModel(QString customBin)
{
    bool ok=0;
    QString aa = customBin.setNum(customBin.toInt(&ok,16),2);
    QString bb;
    for(int i=0;i<16-aa.length();i++){
        bb.append("0");
    }
    customBin = bb+aa;

//    if(customBin.length() <16)
//        return;
    for(int i=15; i>=0; i--){
        bool use=false;

        if(customBin.at(i) == '1'){
            use = true;
        }
        switch (i) {
        case PN_USSD:
            structSupportModel.ussd = use;
            break;
        case PN_SMS:
            structSupportModel.sms  = use;
            break;
        case PN_DATA:
            structSupportModel.data = use;
            break;
        case PN_AWS:
            structSupportModel.aws = use;
            break;
        case PN_AZURE:
            structSupportModel.azure = use;
            break;
        case PN_URUSSD:
            structSupportModel.urussd = use;
            break;
        case PN_URAWS:
            structSupportModel.uraws = use;
            break;
//        case PN_LORA:
//            supportDeviceModel.lora = use;
//            break;
        default:
            break;
        }
    }
    qDebug()<<"ussd:"<<structSupportModel.ussd;
    qDebug()<<"sms:"<<structSupportModel.sms;
    qDebug()<<"data:"<<structSupportModel.data;
    qDebug()<<"aws:"<<structSupportModel.aws;
    qDebug()<<"urussd:"<<structSupportModel.urussd;
    qDebug()<<"uraws:"<<structSupportModel.uraws;
}

/**
 * 设置lora通道
 * @brief UC11T1DealThread::setLoraChannel
 * @param list
 * @return
 */
int UCXX22DealThread::setLoraChannel(QVariantList list)
{

    QVariantMap map = list.at(0).toMap().value("loraChannel").toMap();
    unp_state_t ret;

#ifdef OEM_LHR_MILESIGHT
        m_qunp->unp_set_lora(static_cast<uint8_t>(map.value("datarate").toInt()),LORA_DEFDR);

#endif

    uint8_t dataHex[256] = {0};
    int offset = 0;

    stringToHex2(map.value("channemMask").toString(),dataHex);

    offset += 12;
    qInfo()<<"Freq value: "<<map.value("fre0").toInt()<<map.value("fre1").toInt()<<map.value("fre2").toInt()<<
                 map.value("fre3").toInt()<<map.value("fre4").toInt()<<map.value("fre5").toInt()
              <<map.value("fre6").toInt()<<map.value("fre7").toInt()<<map.value("channemMask").toString();
//    for(int i=0; i<20; i++){
//        printf("%02x",dataHex[i]);
//    }
//    printf("\n");

    if(map.value("fre0").toInt() != 0){
        int m_offset=0;
        m_offset = stringToHex2(QString::number(map.value("fre0").toInt(),16),dataHex+offset);
        offset = m_offset+offset;
        dataHex[offset] = 0x50;
        offset++;
    }else{
        offset += 5;
    }

    if(map.value("fre1").toInt() != 0){
        int m_offset=0;
        m_offset = stringToHex2(QString::number(map.value("fre1").toInt(),16),dataHex+offset);
        offset = m_offset+offset;
        dataHex[offset] = 0x50;
        offset++;
    }else{
        offset += 5;
    }

    if(map.value("fre2").toInt() != 0){
        int m_offset=0;
        m_offset = stringToHex2(QString::number(map.value("fre2").toInt(),16),dataHex+offset);
        offset = m_offset+offset;
        dataHex[offset] = 0x50;
        offset++;
    }else{
        offset += 5;
    }

    if(map.value("fre3").toInt() != 0){
        int m_offset=0;
        m_offset = stringToHex2(QString::number(map.value("fre3").toInt(),16),dataHex+offset);
        offset = m_offset+offset;
        dataHex[offset] = 0x50;
        offset++;
    }else{
        offset += 5;
    }

    if(map.value("fre4").toInt() != 0){
        int m_offset=0;
        m_offset = stringToHex2(QString::number(map.value("fre4").toInt(),16),dataHex+offset);
        offset = m_offset+offset;
        dataHex[offset] = 0x50;
        offset++;
    }else{
        offset += 5;
    }

    if(map.value("fre5").toInt() != 0){
        int m_offset=0;
        m_offset = stringToHex2(QString::number(map.value("fre5").toInt(),16),dataHex+offset);
        offset = m_offset+offset;
        dataHex[offset] = 0x50;
        offset++;
    }else{
        offset += 5;
    }

    if(map.value("fre6").toInt() != 0){
        int m_offset=0;
        m_offset = stringToHex2(QString::number(map.value("fre6").toInt(),16),dataHex+offset);
        offset = m_offset+offset;
        dataHex[offset] = 0x50;
        offset++;
    }else{
        offset += 5;
    }

    if(map.value("fre7").toInt() != 0){
        int m_offset=0;
        m_offset = stringToHex2(QString::number(map.value("fre7").toInt(),16),dataHex+offset);
        offset = m_offset+offset;
        dataHex[offset] = 0x50;
        offset++;
    }else{
        offset += 5;
    }
//qDebug();
//for(int i=0; i<100; i++){
//    printf("%02x",dataHex[i]);
//}
//printf("\n");

    ret = m_qunp->unp_set_lora(dataHex,LORA_CHAN_MASK,LORA_DEFDR-LORA_CHAN_MASK);

    return ret;
}

int UCXX22DealThread::setLoraChannel2(QVariantList list)
{
    QVariantMap map = list.at(0).toMap().value("loraChannel").toMap();

    #ifdef OEM_LHR_MILESIGHT
        if(productName.contains("11T1") || productName.contains("11N1")
                 || productName.contains(UC501) || productName.contains(UC502)
                 || productName.contains(UC511) || productName.contains(UC512)){
            m_qunp->unp_set_lora(static_cast<uint8_t>(map.value("datarate").toInt()),LORA_DEFDR);
        }else{
            m_qunp->unp_set_lora(static_cast<uint8_t>(map.value("datarate").toInt()),LORA_DEFDR);
        }
    #endif

    uint8_t dataHex1[4] = {0};

    stringToHex2(map.value("cm1").toString(),dataHex1);
    m_qunp->unp_set_lora(dataHex1,LORA_CHAN_MASK,2);
//    qDebug()<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
//    for(int i=0; i<20; i++){
//        printf("%02x",dataHex1[i]);
//    }
//    printf("\n");

    uint8_t dataHex[64] = {0};
    int offset = 0;

    stringToHex2(map.value("cm2").toString(),dataHex+offset);
    offset += 2;

    stringToHex2(map.value("cm3").toString(),dataHex+offset);
    offset += 2;

    stringToHex2(map.value("cm4").toString(),dataHex+offset);
    offset += 2;

    stringToHex2(map.value("cm5").toString(),dataHex+offset);
    offset += 2;

    stringToHex2(map.value("cm6").toString(),dataHex+offset);
    offset += 2;

    for(int i=0; i<64; i++){
        printf("%02x",dataHex[i]);
    }
    printf("\n");

    m_qunp->unp_set_lora(dataHex,LORA_CHANNELMASK15_95,10);

    return 1;
}

void UCXX22DealThread::waitTime(int mesc)
{
    QEventLoop loop;//定义一个新的事件循环
    QTimer::singleShot(mesc, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
    loop.exec();
}

QString UCXX22DealThread::hexToString(uint8_t *in, int len)
{
    QString tmp,a;
    for(int kk = 0; kk<len; kk++){
        tmp.append(a.asprintf("%02x",in[kk]));
    }
    return tmp;
}
void UCXX22DealThread::stringToHex(QString dataStr, uint8_t *out)
{
    uint8_t dataHex[256] = {0};
    size_t offset=0;
    bool ok=0;
    for(int j=0; j<dataStr.length(); j++ ){
        dataHex[offset++] = static_cast<uint8_t>(dataStr.mid(j,2).toInt(&ok,16));
        j+=1;
    }

    memcpy(out,dataHex,offset);
}
int UCXX22DealThread::stringToHex2(QString dataStr, uint8_t *out)
{
    uint8_t dataHex[256] = {0};
    int offset=0;
    bool ok=0;
    for(int j=0; j<dataStr.length(); j++ ){
        dataHex[offset++] = static_cast<uint8_t>(dataStr.mid(j,2).toInt(&ok,16));
        j=j+1;
    }
    offset--;

    uint8_t dataHex2[offset];

    for(int i=0; i<offset+1; i++){
        dataHex2[i] = dataHex[offset-i];
//        printf("%02x",dataHex2[i]);
    }
//    printf("\n");

    memcpy(out,dataHex2,size_t(offset+1));
    return offset+1;
}

