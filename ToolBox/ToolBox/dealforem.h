#ifndef DEALFOREM_H
#define DEALFOREM_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include "unp/qunp.h"

struct statusPageData{
    QString productName;

};

class DealForEm : public QObject
{
    Q_OBJECT
public:
    explicit DealForEm(QObject *parent = nullptr);
    ~DealForEm();

public slots:
    void run();
    void imageProgress(uint32_t pktsize);
    void onConnectingDevice(SerialInfo s);


signals:
    void upgradeProgress(int progress);
    void sendProductName(QString productName);

private:
    qunp *m_qunp;
    QMutex p_mutex;

    uint32_t imageDataSize;

};

#endif // DEALFOREM_H
