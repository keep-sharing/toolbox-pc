#ifndef CONNECTTING_H
#define CONNECTTING_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include "unp/qunp.h"

struct statusPageData{
    QString productName;

};

class Connectting : public QObject
{
    Q_OBJECT
public:
    explicit Connectting(QObject *parent = nullptr);
    ~Connectting();

public slots:
    void run();
    void onConnectingDevice(SerialInfo s);


signals:
    void sendMsgWnd(QString msg);
    void upgradeProgress(int progress);
    void sendProductName(QString productName, QString swver, QString hwver);

private:
    Qunp *m_qunp;
    uint32_t imageDataSize;
};

#endif //CONNECTTING_HL
