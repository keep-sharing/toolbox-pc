#ifndef UCXX52DEALTHREAD_H
#define UCXX52DEALTHREAD_H

#include <QObject>
#include <QThread>
#include <QVariant>
#include "ucxx52/unp/qunpucxx52.h"

class UCXX52DealThread : public QObject
{
    Q_OBJECT
public:


    enum IfCbx{IC_Empty,IC_Time,IC_PSQ,IC_Input1,IC_Input2,IC_In1OrIn2,IC_In1AndIn2,IC_MsgRecv,IC_DevRestars,IC_Analog1,IC_Analog2,IC_CHANNEL,IC_Counter1,IC_Counter2};
    enum InputCbx{INC_GoseActive,INC_GoseInactive,INC_ChangeState,INC_IsActive,INC_IsInactive};
    enum AnalogStatus{AS_Above,AS_Below,AS_Within};
    enum IfStackedWidget{ISW_Empty,ISW_Time,ISW_Input,ISW_MsgRecv,ISW_Analog,ISW_Channel,ISW_Counter};
    enum ThenCbx{TC_Empty,TC_StatusMessage,TC_CustomMessage,TC_ALARM,TC_Output1,TC_Output2,TC_DevRestart};
    enum ThenStackedWidget{TSW_Empty,TSW_CustomMessage,TSW_Output};

    enum OutputCbx{
        OP_GoseHigh,
        OP_GoseLow,
        OP_ChangeState,
    #if OUTPUT_WAVEFORM
        OP_Waveform,
    #endif
        OP_FollowInput};
    enum ReadMudbusSpecial{
        RMS_AI1 = 0,
        RMS_AI2,
        RMS_Serial
    };
    enum MudbusGengernal{
        MG_ALL=-1 ,
        MG_BASIC=0 ,
    #ifdef ODM_LHR_AZURE
        MG_RS485=99,
        MG_RS232=1
    #else
        MG_RS485=1,
        MG_RS232=2
    #endif

    };
    enum EnumPage{
        PAGE_STATUS=0,
        PAGE_GENERAL,
        PAGE_LORAWAN,
        PAGE_CHANNEL,
        PAGE_SETTING,
        PAGE_SETTING_EDIT,
        PAGE_UPGRADE,
        CONFIG_WRITE_GENERAL,
        CONFIG_READ_GENERAL_SPECIAL,
        CONFIG_WRITE_LORAWAN,
        CONFIG_WRITE_SETTING,
        CONFIG_WRITE_CHANNEL,
        CONFIG_WRITE_CHANNEL_SPECIAL,
        CONFIG_IMPORT_AWS_FILE,
        CONFIG_READ_DTU_STATUS,
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
        int ioNum = 4;
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

        //
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
        ///basic
        int network_type;
        QString msgCenterNum;
        int smsCodeType;
        QString pinCode;
        int application_mode;
        QString keepAliveInterval;
        int dataCollectInterval;
        QString reportingInterval;
        QString apn;
        QString apnUser;
        QString apnPwd;
        QString serAddr;

        int rs485Enabel;
        int rs485Baudrate;
        int rs485Databit;
        int rs485Stopbit;
        int rs485Parity;
        int rs485BridgeLoraWanEnable;
        QString rs485BridgeLoraWanPort;

        int rs232Enabel;
        int rs232Baudrate;
        int rs232Databit;
        int rs232Stopbit;
        int rs232Parity;
        int rs232Protocol;
        int rs232KeepAliveInterval;
        int rs232KeepAliveRetryTimes;
        int rs232PacketLength;
        int rs232FrameInterval;
        int rs232ReconnectInterval;
        QString rs232RegsterString;

        QString serverAddr1;
        QString serverPort1;
        QString status1;
        QString serverAddr2;
        QString serverPort2;
        QString status2;

        QString dtuStatus1;
        QString dtuStatus2;
        bool onlyDTUStatus;

        //tcp udp mqtt
        QString description;
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
        QString tcpServerAddr1;
        QString tcpServerPort1;
        QString tcpStatus1;
        QString tcpServerAddr2;
        QString tcpServerPort2;
        QString tcpStatus2;
        QString userCreUsername;
        QString userCrePwd;
        QString userCreEnable;
        QString tlsEnable;

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

        //onenet
        QString oneNetKeepAlive;
        QString oneNetProductID;
        QString oneNetKey;
    };

    struct StructPageChannel{
        int readSpecial;
        int readSpecialType;

        //Fetch Serial
        QString serialType;
        QString serialSign;
        QString serialValue;
        QString serialQuantity;
        QString serialDp;
        int serialIndex;
        int fetchPkgLen;

        int executionInterval;
        int maxRespTime;
        int maxRetrytime;

        QVariantList dataList;
        QString name;
        int slaveid;
        int address;
        int quantity;
        int type;
        int sign;
        int decimaiPlace;
        int curVal;
    };

    struct StructPageSetting{

    };

    explicit UCXX52DealThread(QObject *parent = nullptr);
    ~UCXX52DealThread();

    StructSupportModel structSupportModel;

public slots:
    void run();
    void imageProgress(uint32_t pktsize);
    void onGetProductName(QString proName, QString swver, QString hwver, bool isNFC);
    void onConnectingDevice(SerialInfo s);
    void onRequestToDevice(int type, QVariantList list);

signals:

    void getDeviceStatus(UCXX52DealThread::StructPageStatus info);
    void getGeneral(UCXX52DealThread::StructPageGeneral info);
    void getSetting(QVariantList info);
    void getLorawan(StructPageLorawan info);
    void getChannel(UCXX52DealThread::StructPageChannel info);
    void sendMsgWnd(QString msg);
    void waitingVisible(bool vis);
    void upgradeProgress(int progress);
    void sendProductName(QString productName);
    void sendSmsTxt(QString txt);
private:
    QunpUCXX52 *m_qunp;

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
    StructPageChannel m_structPageChannel;

    void waitTime(int mesc);
    QString hexToString(uint8_t *in,int len);
    void stringToHex(QString dataStr, uint8_t* out);
    int  stringToHex2(QString dataStr, uint8_t* out);
    bool openSerialPort();
    void closeSerialPort();
    void getStatusPage(QVariantList list);
    void getGeneralPage(QVariantList list);
    void getGeneralGPIO(QVariantList list);
    void setGeneralPage(QVariantList list);
    void setChannelPage(QVariantList list);
    void getChannelPage(QVariantList list);
    void getChannelSpecial(QVariantList list);
    void getSettingPage(QVariantList list);
    void setSettingPage(QVariantList list);
    void getGeneralDTU(QVariantList list);
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

#endif // UCXX52DEALTHREAD_H
