#ifndef UCXX22MODEL_H
#define UCXX22MODEL_H

#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QDialog>
#include <QFileDialog>
#include "ucxx22dealthread.h"
#include "upgradewnd.h"
#include "passwordverify.h"
#include "myControl/mywindowstytle.h"
namespace Ui {
class UCXX22Model;
}

class UCXX22Model : public MyWindowStytle
{
    Q_OBJECT


public:
    enum EnumLoraGengernal{LG_ALL=-1 ,LG_BASIC=0 ,LG_CHANNEL=1, LG_ADVANCED=2};

    explicit UCXX22Model(QWidget *parent = nullptr);
    ~UCXX22Model();

signals:
    void requestToDevice(int type, QVariantList list);
    void getProductName(QString proName,QString swver, QString hwver, bool isNFC);
    void waitingVisible(bool vis);

public slots:
    void onGetProductName(QString proName, QString swver, QString hwver, bool isNFC, QString loginPwd);
    void onPageChanged(QString name, QString title);
    void onRecvDeviceStatus(UCXX22DealThread::StructPageStatus);
    void onRecvGeneral(UCXX22DealThread::StructPageGeneral info);
    void onRecvLorawan(StructPageLorawan);
    void changeEvent(QEvent *e);
private slots:
    void on_brows_btn_clicked();
    void on_browsUboot_btn_clicked();
    void on_upgradeFirmware_btn_clicked();
    void onUpgradePregressChanged(int progress);
    void on_reset_btn_clicked();
    void on_changePwd_cb_clicked(bool checked);
    void on_cloudApplicationMode_cbx_currentIndexChanged(int index);
    void on_customHeartbeat_cb_clicked(bool checked);
    void on_requireResponse_cb_clicked(bool checked);
    void on_mqttUserCreEnable_cb_clicked(bool checked);
    void on_mqttTlsEnable_cb_clicked(bool checked);
    void on_awsCASelectFile_btn_clicked();
    void on_awsCAImportFile_btn_clicked();
    void on_awsCADelFile_btn_clicked();
    void on_awsCliCerSelectFile_btn_clicked();
    void on_awsCliCerImportFile_btn_clicked();
    void on_awsCliCerDelFile_btn_clicked();
    void on_awsCliKeySelectFile_btn_clicked();
    void on_awsCliKeyImportFile_btn_clicked();
    void on_awsCliKeyDelFile_btn_clicked();
    void on_azureMode_cbx_currentIndexChanged(int index);
    void on_generalSave_btn_clicked();
    void on_joinType_cbx_currentIndexChanged(int index);
    bool on_generalBasicSave_btn_clicked();
    bool on_fixedFreSave_btn_clicked();
    bool on_generalChannelSave_btn_clicked();
    void on_supportFre_cbx_currentIndexChanged(const QString &arg1);
    void on_supportFre2_cbx_currentIndexChanged(const QString &arg1);
    void on_tabWidget_2_tabBarClicked(int index);
    bool on_generalJTNSave_btn_clicked();
    void on_gpioType_cbx_currentIndexChanged(int index);
    void on_gpioCounterStart_btn_clicked();
    void on_gpioCounterRefresh_btn_clicked();
    void on_gpioCounterClear_btn_clicked();
    void on_channelAll_cb_clicked(bool checked);
    void onCheckChannelAllClicked();

private:
    Ui::UCXX22Model *ui;

    PasswordVerify *m_nfcPwdWnd;
    UpgradeWnd *m_upgradeWnd;
    UCXX22DealThread *m_dealThread;
    QThread *m_thread;

    UCXX22DealThread::StructPageStatus m_statusPageInfo;
    UCXX22DealThread::StructPageGeneral m_generalPageInfo;
    UCXX22DealThread::StructPageSetting m_settingPageInfo;
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

    int m_loraReadIndex;
    float m_freMax;
    float m_freMin;
    float m_rxFreMax;
    float m_rxFreMin;

    void setLoraChannelData(StructPageLorawan info);
    void setLoraChannelFixFre(QVariantMap map, bool lastVis);
    bool thresholdOverBelow(QString over, QString below, QString high, QString less);
    QString hexTobin4bit(QString strHex);
    QString hexTobin16bit(QString strHex);
    QStringList hexTolist(QString hex, int extNum=0);
};

#endif // UCXX22MODEL_H
