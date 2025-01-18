#ifndef UCXX52MODEL_H
#define UCXX52MODEL_H

#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QDialog>
#include <QFileDialog>
#include <QComboBox>
#include <QParallelAnimationGroup>
#include <QMutex>
#include <QStandardItemModel>
#include "../myControl/tableviewdelegate.h"
#include "myControl/mywindowstytle.h"
#include "ucxx52dealthread.h"
#include "upgradewnd.h"
#include "passwordverify.h"

namespace Ui {
class UCXX52Model;
}

class UCXX52Model : public MyWindowStytle
{
    Q_OBJECT


public:
    enum EnumLoraGengernal{LG_ALL=-1 ,LG_BASIC=0 ,LG_CHANNEL=1, LG_ADVANCED=2};
    enum SettingTB{ID,CONFIGURATION,EDIT,TDELETE};
enum IfCbx1{IC_Empty,IC_Time,IC_PSQ,IC_Input1,IC_Input2,IC_In1OrIn2,IC_In1AndIn2,IC_MsgRecv,IC_DevRestars,IC_Analog1,IC_Analog2,IC_CHANNEL,IC_Counter1,IC_Counter2};
enum InputCbx1{INC_GoseActive,INC_GoseInactive,INC_ChangeState,INC_IsActive,INC_IsInactive};
enum AnalogStatus1{AS_Above,AS_Below,AS_Within};
enum IfStackedWidget1{ISW_Empty,ISW_Time,ISW_Input,ISW_MsgRecv,ISW_Analog,ISW_Channel,ISW_Counter};
enum ThenCbx1{TC_Empty,TC_StatusMessage,TC_CustomMessage,TC_ALARM,TC_Output1,TC_Output2,TC_DevRestart};
enum ThenStackedWidget1{TSW_Empty,TSW_CustomMessage,TSW_Output};
enum OutputCbx{
    OP_GoseHigh,
    OP_GoseLow,
    OP_ChangeState,
#if OUTPUT_WAVEFORM
    OP_Waveform,
#endif
    OP_FollowInput};

    explicit UCXX52Model(QWidget *parent = nullptr);
    ~UCXX52Model();

signals:
    void requestToDevice(int type, QVariantList list);
    void getProductName(QString proName,QString swver, QString hwver, bool isNFC);
    void waitingVisible(bool vis);

public slots:
    void onGetProductName(QString proName, QString swver, QString hwver, bool isNFC, QString loginPwd);
    void onPageChanged(QString name, QString title);
    void onRecvDeviceStatus(UCXX52DealThread::StructPageStatus);
    void onRecvGeneral(UCXX52DealThread::StructPageGeneral info);
    void onRecvLorawan(StructPageLorawan);
    void onRecvChannelStatus(UCXX52DealThread::StructPageChannel info);
    void changeEvent(QEvent *e);
private slots:
    void on_brows_btn_clicked();
    void on_browsUboot_btn_clicked();
    void on_upgradeFirmware_btn_clicked();
    void onUpgradePregressChanged(int progress);
    void on_reset_btn_clicked();
    void on_joinType_cbx_currentIndexChanged(int index);
    bool on_generalBasicSave_btn_clicked();
    bool on_fixedFreSave_btn_clicked();
    bool on_generalChannelSave_btn_clicked();
    void on_supportFre_cbx_currentIndexChanged(const QString &arg1);
    void on_supportFre2_cbx_currentIndexChanged(const QString &arg1);
    void on_tabWidget_2_tabBarClicked(int index);
    bool on_generalJTNSave_btn_clicked();
    void on_tabWidget_3_tabBarClicked(int index);
    void on_modbusChangePwd_cb_clicked(bool checked);
    void on_modbusCustomHeartbeat_cb_clicked(bool checked);
    void on_modbusRequireResponse_cb_clicked(bool checked);
    void on_modbusApplicationMode_cbx_currentIndexChanged(int index);
    void on_modbusMqttUserCreEnable_cb_clicked(bool checked);
    void on_modbusMqttTlsEnable_cb_clicked(bool checked);
    void on_modbusAwsCASelectFile_btn_clicked();
    void on_modbusAwsCAImportFile_btn_clicked();
    void on_modbusAwsCADelFile_btn_clicked();
    void on_modbusAwsCliCerSelectFile_btn_clicked();
    void on_modbusAwsCliCerImportFile_btn_clicked();
    void on_modbusAwsCliCerDelFile_btn_clicked();
    void on_modbusAwsCliKeySelectFile_btn_clicked();
    void on_modbusAwsCliKeyImportFile_btn_clicked();
    void on_modbusAwsCliKeyDelFile_btn_clicked();
    void onRs232DTUExitSlot();
    void on_rs485Enabel_cb_clicked(bool checked);
    void on_rs232Enable_cb_clicked(bool checked);
    void on_rs232Protocol_cbx_currentIndexChanged(int index);
    void on_modbusBasicSave_btn_clicked();
    void on_rs485Save_btn_clicked()  ;
    void on_rs232Save_btn_clicked()  ;
    void on_modbusGpioType_cbx_currentIndexChanged(int index);
    void on_modbusGpioCounterStart_btn_clicked();
    void on_modbusGpioCounterRefresh_btn_clicked();
    void on_modbusGpioCounterClear_btn_clicked();
    void on_modbusAzureMode_cbx_currentIndexChanged(int index);
    void on_modbusChannelSave_btn_clicked();
    void onModbusChannelTypeCbxChange();
    void onModbusChannelAddBtnClicked();
    void onModBusChannelDelBtnClicked();
    void onModbusChannelFetchClicked();
    void on_channelAll_cb_clicked(bool checked);
    void onCheckChannelAllClicked();
    void modbusChannelAddDelChange();
    void modbusChannelDataChange();
    void modbusChannelGetData();

    void on_tableView_clicked(const QModelIndex &index);
    void onRecvDeviceCommand(QVariantList dev_device_info);
    void onGetSmsTxt(QString txt);
    void on_timeisDay_cbx_currentIndexChanged(const QString &arg1);
    void on_timeisTime_tde_timeChanged(const QTime &time);
    void onTextEditTextChanged();
    void on_saveToDevice_btn_clicked();
    void on_saveToFile_btn_clicked();
    void on_readFromDevice_btn_clicked();
    void on_openFromFile_btn_clicked();
    void saveSettingCommand(QString filename);
    void on_settingEditCancel_btn_clicked();
    void on_inputLevel_cbx_currentIndexChanged(int index);
    void on_if_cbx_currentIndexChanged(int index);
    void on_thenAdd1_btn_clicked();
    void on_thenAdd2_btn_clicked();
    void on_then1_cbx_currentIndexChanged(int index);
    void on_then2_cbx_currentIndexChanged(int index);
    void on_then3_cbx_currentIndexChanged(int index);
    void on_thenDel3_btn_clicked();
    void on_thenDel2_btn_clicked();
    void on_level1_cbx_currentIndexChanged(int index);
    void on_level2_cbx_currentIndexChanged(int index);
    void on_level3_cbx_currentIndexChanged(int index);
    void on_analogStatus_cbx_currentIndexChanged(int index);
    void on_modbusStatus_cbx_currentIndexChanged(int index);
    void on_modbusChannelStatus_cbx_currentIndexChanged(int index);
    void on_settingEditSave_btn_clicked();

private:
    Ui::UCXX52Model *ui;

    PasswordVerify *m_nfcPwdWnd;
    UpgradeWnd *m_upgradeWnd;
    UCXX52DealThread *m_dealThread;
    QThread *m_thread;

    UCXX52DealThread::StructPageStatus m_statusPageInfo;
    UCXX52DealThread::StructPageGeneral m_generalPageInfo;
    UCXX52DealThread::StructPageSetting m_settingPageInfo;
    StructPageLorawan m_lorawanPageInfo;

    QVariantMap m_cacheDataMap; //接口中需要读什么接什么的缓存数据
    QVariantMap backupMap;    //全系列备份还原Map
    QStringList defaultFre;

    QString m_iniPath;
    QString m_loginPwd;
    QString m_proName;
    QString m_swver;
    QString m_hwver;
    QString m_caFilePath;
    QString m_cliCerFilePath;
    QString m_cliKeyFilePath;

    int m_oemver;

    bool m_bcaFileBrowse = false;
    bool m_bclientFileBrowse = false;
    bool m_bclientKeyBrowse = false;
    bool m_bNFC;
    bool m_bLoraBasicSave = false;
    bool m_bLoraChannelSave = false;
    bool m_bLoraAdvancedSave = false;

    int m_modbusReadIndex;
    int m_loraReadIndex;
    float m_freMax;
    float m_freMin;
    float m_rxFreMax;
    float m_rxFreMin;

    //channel
    int m_channelMudbusNum ;
    int m_modbusChannelDelRow;
    QMutex m_modbusChannelGetDataMutex;
    QVariantList m_modbusChannelData;
    QList<QComboBox *>modbusChannelIdList;
    QList<QLineEdit *>modbusChannelNameList;
    QList<QLineEdit *>modbusChannelSlaveidList;
    QList<QLineEdit *>modbusChannelAddrList;
    QList<QLineEdit *>modbusChannelQuantityList;
    QList<QComboBox *>modbusChannelTypeList;
    QList<QCheckBox *>modbusChannelSignList;
    QList<QLineEdit *>modbusChannelDecimalList;
    QList<QLineEdit *>modbusChannelCurValList;
    QList<QToolButton *>modbusChannelReList;
    QList<QParallelAnimationGroup *>modbusChannelAnimationList;
    QList<QPushButton *>modbusChannelFetchList;
    QList<QToolButton *>modbusChannelDelList;
    QList<QToolButton *>modbusChannelAddList;
    QList<QFrame *> modbusChannelFrameList;

    //规则引擎
    QStandardItemModel *model;
    QVariantList commandList;
    QString smsTxt;
    int settingRow;

    void configCommandTableview(QVariantList command_list);
    void recoverySettingEdit();
    void onTimeCbxChanged(int row);
    void removeThenCbxMsg(int index);
    void insertThenCbxMsg(int index);
    void initThenCbx();
    QString thresholdToMa(QString value, int ic_analogIndex);
    QString mAtoThreshold(QString value, int ic_analogIndex);
    QString ascMsToSec(QString ms, int unit=0);
    char * base64_encode( const unsigned char * bindata, char * base64, int binlength );
    int base64_decode( const char * base64, unsigned char * bindata );

    void initCmdSetting();
    void initSettingTableview();
    void initLorawanSetting();
    void modbusChannelInit();

    void setLoraChannelData(StructPageLorawan info);
    void setLoraChannelFixFre(QVariantMap map, bool lastVis);
    bool thresholdOverBelow(QString over, QString below, QString high, QString less);
    QString hexTobin4bit(QString strHex);
    QString hexTobin16bit(QString strHex);
    QStringList hexTolist(QString hex, int extNum=0);
};

#endif // UCXX52MODEL_H
