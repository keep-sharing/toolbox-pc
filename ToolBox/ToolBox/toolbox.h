#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QWidget>
#include <windows.h>
#include <windowsx.h>
#include <QMouseEvent>
#include <QThread>
#include "version.h"

#include "serialportsetting.h"
#include "ucxx14model.h"
#include "ucxx22model.h"
#include "ucxx52model.h"
#include "connectting.h"
#include "waitingwnd.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ToolBox; }
QT_END_NAMESPACE

class ToolBox : public QWidget
{
    Q_OBJECT

public:
    ToolBox(QWidget *parent = nullptr);
    ~ToolBox();

    struct filePathCache{
        QString imageFilePath;
        QString ubootFilePath;
        QString caFilePath;
        QString cliCerFilePath;
        QString cliKeyFilePath;
        QString iniPath;
    };

signals:
    void getProductName(QString proName,QString swver, QString hwver, bool isNFC,QString loginPwd);
    void pageChanged(QString pageName, QString title);
    void connectingDevice(SerialInfo type);


protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    virtual void mousePressEvent(QMouseEvent *event);       // 鼠标按下
    virtual void mouseMoveEvent(QMouseEvent *event);        // 移动
    virtual void mouseReleaseEvent(QMouseEvent *event);     // 鼠标释放
    bool b_pressed;                                         // 判断鼠标左键是否按下
    QPoint m_windowPos;
    QPoint m_movePoint;

private slots:
    void onWaitingVisible(bool visible);
    void onWaitingPosChanged(QPoint pos);
    void onSerialInfoSaveClicked(SerialInfo s);
    void onSelectProductType(QString productName, QString swver, QString hwver);
    void on_close_btn_clicked();
    void on_min_btn_clicked();
    void on_relogin_btn_clicked();
    void on_upgrade_btn_clicked();
    void on_status_btn_clicked();
    void on_general_btn_clicked();
    void on_lorawan_btn_clicked();
    void on_deviceSetting_btn_clicked();
    void on_channel_btn_clicked();
    void on_setting_btn_clicked();
    void on_application_btn_clicked();
    void on_serialInfobtn_clicked();


    void on_translations_btn_clicked();

    void on_translations_btn_released();

private:
    Ui::ToolBox *ui;
    SerialPortSetting *m_serialPortSetting;
    UCXX14Model *m_ucxx14Model;
    UCXX22Model *m_ucxx22Model;
    UCXX52Model *m_ucxx52Model;

    QWidget *m_modelWidget;
    WaitingWnd *m_waitingWnd;
    Connectting *m_connect;
    QThread *m_threadConnect;

    filePathCache m_filePathCache;
    QString m_loginPwd;
    QString m_preProName;
    bool isNFC;
    bool m_bEnglish=false;
    bool connectToSerial();

};
#endif // TOOLBOX_H
