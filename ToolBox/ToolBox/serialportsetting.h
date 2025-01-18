#ifndef SERIALPORTSETTING_H
#define SERIALPORTSETTING_H

#include <QDialog>
#include <QSerialPort>
#include <QSettings>
#include <QFile>
#include <QMouseEvent>
#include <QThread>
#include <QTimer>
#include <QSerialPortInfo>
#include <QDebug>
#include "version.h"

namespace Ui {
class SerialPortSetting;
}

enum Connect_Type{
    E_SerialPort=0,
    E_NFC
};

class SerialPortSetting : public QDialog
{
    Q_OBJECT

public:

    struct SerialInfo{
        QString portName;
        int connectionTimeout;
        QSerialPort::BaudRate baudrate;
        QSerialPort::DataBits databit;
        QSerialPort::Parity paritybit;
        QSerialPort::StopBits stopbit;
        QString loginPwd;
        int type;
    };

    explicit SerialPortSetting(QWidget *parent = nullptr);
    ~SerialPortSetting();
    void setPortName(QList<QSerialPortInfo> portName, QString p);
    QString currentPortName;

signals:
    void sendSerialInfo(SerialInfo s);

private slots:
    void on_save_btn_clicked();
    void on_type_cbx_currentIndexChanged(int index);
    void changeEvent(QEvent *e);

protected:
    virtual void mousePressEvent(QMouseEvent *event);       // 鼠标按下
    virtual void mouseMoveEvent(QMouseEvent *event);        // 移动
    virtual void mouseReleaseEvent(QMouseEvent *event);     // 鼠标释放
    bool m_pressed;       // 判断鼠标左键是否按下
    QPoint m_pos;         // 鼠标相对于窗口的位置，不是相对屏幕的位置
    QPoint movePoint;

private:
    Ui::SerialPortSetting *ui;
    QList<QSerialPortInfo> m_spis;


};

#endif // SERIALPORTSETTING_H
