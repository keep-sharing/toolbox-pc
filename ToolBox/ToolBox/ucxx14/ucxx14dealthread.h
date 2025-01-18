#ifndef UCXX14DEALTHREAD_H
#define UCXX14DEALTHREAD_H

#include <QObject>
#include <QThread>
#include <QVariant>
#include "ucxx14/unp/qunpucxx14.h"

class UCXX14DealThread : public QObject
{
    Q_OBJECT
public:

    enum SettingTB{ID,CONFIGURATION,EDIT,TDELETE};
    enum IfCbx{IC_Empty,IC_Time,IC_PSQ,IC_Input1,IC_Input2,IC_In1OrIn2,IC_In1AndIn2,IC_MsgRecv,IC_DevRestars,IC_Analog1,IC_Analog2,IC_CHANNEL,IC_Counter1,IC_Counter2};
    enum InputCbx{INC_GoseActive,INC_GoseInactive,INC_ChangeState,INC_IsActive,INC_IsInactive};
    enum IfStackedWidget{ISW_Empty,ISW_Time,ISW_Input,ISW_MsgRecv,ISW_Analog,ISW_Channel,ISW_Counter};
    enum ThenCbx{TC_Empty,TC_StatusMessage,TC_CustomMessage,TC_ALARM,TC_Output1,TC_Output2,TC_DevRestart};
    enum ThenStackedWidget{TSW_Empty,TSW_CustomMessage,TSW_Output};

    enum EnumPage{
        PAGE_STATUS=0,
        PAGE_GENERAL,
        PAGE_LORAWAN,
        PAGE_SETTING,
        PAGE_SETTING_EDIT,
        PAGE_UPGRADE,
        POWER_SWITCH,
        CONFIG_WRITE_GENERAL,
        CONFIG_READ_GENERAL_SPECIAL,
        CONFIG_WRITE_LORAWAN,
        CONFIG_WRITE_SETTING,
        CONFIG_IMPORT_AWS_FILE,
        CONFIG_RESET,
    };

    enum ReadSpecial{
        RNS_GPIO1 = 0,
        RNS_GPIO2,
        RNS_AI1,
        RNS_AI2,
        RNS_Serial,
        RNS_GPIO2_COUNTER_REFRESH,
        RNS_GPIO2_COUNTER_START,
        RNS_GPIO2_COUNTER_CLEAR,
        RNS_FETCH_ALL,
        RNS_GPIO1_SWITCH,
        RNS_GPIO2_SWITCH,

    };

    enum CUSTOM_PN{
        PN_USSD,
        PN_SMS,
        PN_DATA,
        PN_AWS,
        PN_URUSSD,
        PN_URAWS,
        PN_AZURE,
        PN_LORA = 8
    };

    struct StructSupportModel{
        bool ussd;
        bool sms;
        bool data;
        bool urussd;
        bool uraws;
        bool lora;
        bool aws;
        bool azure;
        bool DC;
        bool nb;
        bool cloud;
    };

    struct StructPageStatus{
        int     ucpVer;
        QString proName;
        QString sn;
        QString pn;
        QString oem;
        QString swVer;
        QString hwVer;
        QString power;
        QString time;
        QString mobileSignal;
        QString inputioStatus;
        QString outputioStatus;
        QString mobileState;

        int application_mode;
        //ai
        QString analog1Status;
        QString analog2Status;
        QString osh1;
        QString osl1;
        QString osh2;
        QString osl2;

        //lora
        QString snr;
        QString rssi;
        QString join_status;
        QString chan;
        QString datarate;
        QString rx2dr;
        QString rx2freq;
        QString maxEIRP;
        QString receive_delay1;
        QString receive_delay2;
        QString cur_retry_counts;
        QString state;
        QString cur_up_link_counter;
        QString cur_down_link_counter;
        QString input;
        QString output;
        QString battery;
        QString devEui;
    };

    struct StructPageGeneral{
        //gengeral
        QString device_name;
        int network_type;
        QString msgCenterNum;
        int smsCodeType;
        QString pinCode;
        int application_mode;
        QString keepAliveInterval;
        QString reportingInterval;
        QString apn;
        QString apnUser;
        QString apnPwd;
        QString serverAddr;
        QString dataCollectInterval;

        //tcp udp mqtt
        QString tcpkeepAlive;
        QString brokerAddr;
        QString brokerPort;
        QString clientID;
        QString connectTimeout;
        QString mqttKeepAliveInterval;
        QString customHeartbeat;
        QString customContent;
        QString heartbeatInterval;
        QString requireResponse;
        QString responseContent;
        QString serverAddr1;
        QString serverPort1;
        QString status1;
        QString serverAddr2;
        QString serverPort2;
        QString status2;
        QString userCreUsername;
        QString userCrePwd;
        QString userCreEnable;
        QString tlsEnable;
        bool onlyTcpUdpMqttStatus;

        //zhengshu
        QString caFile;
        QString clientFile;
        QString clientKeyFile;

        //NB for Aliyum
        QString aliClientID;
        QString aliProductKey;
        QString aliDevSecret;
        QString aliKeepAilve;
        QString aliQos;

        //Azure
        QString authMode;

        //gpio
        int counterNum;
        int readSpecial;
        int readSpecialType;
        QString gpioStatus;
        QString gpioCounter;
        QString gpioCounterStart;
        QString gpioType;

        QString gpio2Type;
        QString gpio2Status;
        QString gpio2Counter;
        QString gpio2CounterStart;
        //onenet
        QString oneNetKeepAlive;
        QString oneNetProductID;
        QString oneNetKey;
    };

    struct StructPageSetting{

    };

    explicit UCXX14DealThread(QObject *parent = nullptr);
    ~UCXX14DealThread();

    StructSupportModel structSupportModel;

public slots:
    void run();
    void imageProgress(uint32_t pktsize);
    void onGetProductName(QString proName, QString swver, QString hwver, bool isNFC);
    void onConnectingDevice(SerialInfo s);
    void onRequestToDevice(int type, QVariantList list);

signals:

    void getDeviceStatus(UCXX14DealThread::StructPageStatus info);
    void getGeneral(UCXX14DealThread::StructPageGeneral info);
    void getSetting(UCXX14DealThread::StructPageSetting info);
    void getLorawan(StructPageLorawan info);
    void sendMsgWnd(QString msg);
    void waitingVisible(bool vis);
    void upgradeProgress(int progress);
    void sendProductName(QString productName);

private:
    QunpUCXX14 *m_qunp;

    QString m_loginPwd;
    QString m_proName;
    QString m_swver;
    QString m_hwver;
    QString m_otaType;
    QString m_linkwanFreMode;

    bool m_bNFC = false;

    uint32_t imageDataSize;


    StructPageStatus m_structPageStatus;
    StructPageGeneral m_structPageGeneral;
    StructPageSetting m_structPageSetting;

    void waitTime(int mesc);
    QString hexToString(uint8_t *in,int len);
    void stringToHex(QString dataStr, uint8_t* out);
    int  stringToHex2(QString dataStr, uint8_t* out);
    bool openSerialPort();
    void closeSerialPort();
    void getStatusPage(QVariantList list);
    void getGeneralPage(QVariantList list);
    void getGeneralGPIO(QVariantList list);
    void getSettingPage(QVariantList list);
    void setGeneralPage(QVariantList list);
    void setSettingPage(QVariantList list);
    void setImportAwdFile(QVariantList list);
    void getLorawanPage(QVariantList list);
    void setLorawanPage(QVariantList list);
    void setDeviceTime(QVariantList list);
    void toUpgrade(QVariantList list);
    void resetDevice(QVariantList list, bool showTip=true);
    void setSupportModel(QString customBin);
    bool strIsIp(QString str);
    int setLoraChannel(QVariantList list);
    int setLoraChannel2(QVariantList list);

};

#endif // UCXX14DEALTHREAD_H
