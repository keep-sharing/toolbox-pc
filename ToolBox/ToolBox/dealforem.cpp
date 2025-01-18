#include "dealforem.h"

DealForEm::DealForEm(QObject *parent) : QObject(parent)
{

}

DealForEm::~DealForEm()
{
//    m_qunp->auto_close_serialport();
    delete m_qunp;
}

void DealForEm::run()
{
    m_qunp = new qunp();
    connect(m_qunp,SIGNAL(getImageSize(uint32_t)),this,SLOT(imageProgress(uint32_t)));
}

void DealForEm::imageProgress(uint32_t pktsize)
{
    p_mutex.lock();
    if(((pktsize *100 / imageDataSize) >3 ) && ((pktsize *100 / imageDataSize) < 99) ){
        emit upgradeProgress(static_cast<int>(pktsize *100 / imageDataSize));
    }
    p_mutex.unlock();
}

void DealForEm::onConnectingDevice(SerialInfo s)
{
    if(m_qunp->initSerialPort(s)){

        if(m_qunp->unp_send_passwd(reinterpret_cast<uint8_t *>(s.loginPwd.toLatin1().data()),static_cast<uint16_t>(s.loginPwd.length())) == UNP_SUCCESS){
            qDebug("Device Connect Success");

            QString name;
            uint8_t productName[UNP_PRODUCT_NAME_LEN + 1]={0};
            uint8_t pn[UNP_PN_TOTAL_LEN]={0};

            m_qunp->unp_get_product_name(productName);
            m_qunp->unp_get_product_pn(pn);

            name = QString::asprintf("%s-%s",productName,pn);

            emit sendProductName(name);
        }else{
            qDebug("Connect Password Error");

        }
    }else{
        qDebug();
    }
    m_qunp->close_serialport();
}
