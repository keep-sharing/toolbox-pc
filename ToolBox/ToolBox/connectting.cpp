#include "connectting.h"
Connectting::Connectting(QObject *parent) : QObject(parent)
{

}

Connectting::~Connectting()
{
    delete m_qunp;
}

void Connectting::run()
{
    m_qunp = new Qunp();
}



void Connectting::onConnectingDevice(SerialInfo s)
{
    if(m_qunp->initSerialPort(s)){

        m_qunp->set_comnct_type(s.type == 1 ? Qunp::COMNCT_NFC : Qunp::COMNCT_UART);

        if(m_qunp->unp_send_passwd(reinterpret_cast<uint8_t *>(s.loginPwd.toLatin1().data()),static_cast<uint16_t>(s.loginPwd.length())) != UNP_SUCCESS){
            emit sendMsgWnd(tr("Password Error!"));
        }else{
            qDebug("Device Connect Success");
            int ret = 0;
            QString s_name;
            uint8_t name[UNP_PRODUCT_NAME_LEN + 1]={0};
            uint8_t pn[UNP_PN_TOTAL_LEN]={0};
            uint8_t swver[UNP_SWVER_LEN]={0};
            uint8_t hwver[UNP_HWVER_LEN]={0};

            ret |= m_qunp->unp_get_product_name(name);

            ret |= m_qunp->unp_get_product_pn(pn);
            s_name = QString::asprintf("%s-%s",name,pn);

            ret |= m_qunp->unp_get_product_swver(swver);

            ret |= m_qunp->unp_get_product_hwver(hwver);

            printf("---- %s ",name);
            qDebug()<<QString::asprintf("%s-%s",name,pn);
            emit sendProductName(s_name,
                                 QString::asprintf("%c%c.%c%c",swver[0],swver[1],swver[2],swver[3]) ,
                                 QString::asprintf("%c%c.%c%c",hwver[0],hwver[1],hwver[2],hwver[3]));
        }
    }else{
        emit sendMsgWnd(tr("SerialPort Open Error"));
    }

    m_qunp->close_serialport();
}
