#include "qunpucxx22.h"

QunpUCXX22::QunpUCXX22(QObject *parent) : QObject(parent)
{

    m_port = new QSerialPort();
//    m_pollingSerialEnable = true;
//    m_threadMonitorSerial = new QThread();
//    m_monitorSerialPort = new MonitorSerialPort();
//    connect(this, SIGNAL(sendDataToMonitorSerial(QVariantList)), m_monitorSerialPort, SLOT(receiveDataFromMain(QVariantList)));
//    connect(m_monitorSerialPort, SIGNAL(notifySerialChange(bool)), this ,SLOT(onSerialStatusChangeFromMonitor(bool)));
//    connect(m_threadMonitorSerial,SIGNAL(started()),m_monitorSerialPort,SLOT(monitorSerialStart()));
//    m_monitorSerialPort->moveToThread(m_threadMonitorSerial);


    serialMaxTimeout = UNP_MAX_TIMEOUT;
    passwd_verify_success = 0;
    g_comnct_type = COMNCT_UART;
    save_sms_command =false;
    onlyUcp = false;
//    m_todo = -1;
//    write_enable = 0;
//    read_enable = 0;
//    nfc_upgreade_flag = false;
}

#ifdef SUPPORT_UPGRADE_UBOOT
void QunpUCXX22::deal_upgrade_uboot(uint8_t *data, uint16_t datasize)
{
    static uint8_t stage = 0;
    static uint32_t offset = 0;
    uint8_t pktlen;
    uint8_t pkt[32] = {0};

    switch(stage) {
        case 0:
            if(datasize == strlen(UNP_UPGRADE_UBOOT_REQ) && strstr((const char *)data, UNP_UPGRADE_UBOOT_REQ)) {
                stage  = 1;
                offset = 0;
                pktlen = generate_pkt(nullptr, 0, pkt, UPGRADE_UBOOT_ACK_PKT);
                unp_send_pkt(pkt, pktlen);
            }
            break;
        case 1:
            if(datasize == strlen(UNP_UBOOT_COMPLETE) && strstr((const char *)data, UNP_UBOOT_COMPLETE)) {
                stage = 0;
                pktlen = generate_pkt(nullptr, 0, pkt, UPGRADE_UBOOT_ACK_PKT);
                unp_send_pkt(pkt, pktlen);
                unxx_restart_device();
            } else {
                if(FLASH_UBL_BASE_ADDR + offset + datasize < FLASH_APP_BASE_ADDR) {
                    write_data_to_flash((uint32_t *)data, datasize, FLASH_UBL_BASE_ADDR + offset);
                    offset += datasize;
                }
            }
            break;
        default:
            break;
    }
}

void QunpUCXX22::deal_upgrade_uboot_ack(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(data)
    Q_UNUSED(datasize)
    g_unp_ack.type = UPGRADE_UBOOT_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.state = UNP_SUCCESS;
}
#endif

void QunpUCXX22::deal_reset_dev(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(data)
    Q_UNUSED(datasize)
    uint8_t pkt[32] = {0};
    uint16_t pktlen;

    if(!unp_verify()) {
        return;
    }

    pktlen = generate_pkt(nullptr, 0, pkt, RESET_DEVICE_ACK_PKT);
    unp_send_pkt(pkt, pktlen);
    unxx_reset_device();
}

void QunpUCXX22::deal_reset_dev_ack(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(data)
    Q_UNUSED(datasize)
    g_unp_ack.type = RESET_DEVICE_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.state = UNP_SUCCESS;
}

void QunpUCXX22::deal_dtu_status(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(data)
    Q_UNUSED(datasize)
}

void QunpUCXX22::deal_lorawan_reload_ack(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(data)
    Q_UNUSED(datasize)
    g_unp_ack.type = DEVICE_RELOAD_CONFIG_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.state = UNP_SUCCESS;
}

void QunpUCXX22::deal_connect_dev(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(datasize)
    Q_UNUSED(data)
    uint8_t pkt[32] = {0};
    uint16_t pktlen;

    //passwd_verify_success = 1;
    pktlen = generate_pkt(nullptr, 0, pkt, CONNECT_DEVICE_ACK_PKT);
    unp_send_pkt(pkt, pktlen);
}

void QunpUCXX22::deal_connect_dev_ack(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(data)
    Q_UNUSED(datasize)
    g_unp_ack.type = CONNECT_DEVICE_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.state = UNP_SUCCESS;
}

void QunpUCXX22::deal_reload_config_dev_ack(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(datasize)
    Q_UNUSED(data)
    g_unp_ack.type = DEVICE_RELOAD_CONFIG_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.state = UNP_SUCCESS;
}

void QunpUCXX22::deal_reload_config_dev(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(data)
    Q_UNUSED(datasize)
    g_unp_ack.type = DEVICE_RELOAD_CONFIG_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.state = UNP_SUCCESS;
}

void QunpUCXX22::deal_passwd_input(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(data)
    Q_UNUSED(datasize)
    uint8_t pkt[32] = {0};
    uint8_t status[1] = {0};
    uint8_t passwd[UNP_PASSWD_LEN] = {0};
    uint16_t pktlen;

    get_device_passwd(passwd);
    if(strncmp((const char *)data, (const char *)passwd, UNP_PASSWD_LEN) == 0) {
        status[0] = UNP_SUCCESS;
        passwd_verify_success = 1;
    } else {
        status[0] = UNP_FAIL;
    }
#ifdef SUPPORT_UPGRADE_UBOOT
    passwd_verify_success = 1;
    status[0] = UNP_SUCCESS;
#endif
    pktlen = generate_pkt(status, sizeof(status), pkt, INPUT_PASSWD_ACK_PKT);
    unp_send_pkt(pkt, pktlen);
}

void QunpUCXX22::deal_passwd_input_ack(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(datasize)
    g_unp_ack.type = INPUT_PASSWD_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.state = (unp_state_t)data[0];
}

void QunpUCXX22::deal_reboot(void)
{
    uint8_t pkt[32] = {0};
    uint16_t pktlen;

    if(!unp_verify()) {
        return;
    }

    pktlen = generate_pkt(nullptr, 0, pkt, REBOOT_DEVICE_ACK_PKT);
    unp_send_pkt(pkt, pktlen);

#ifdef USE_IN_STM32
    unxx_restart_device();
#endif
}

void QunpUCXX22::deal_reboot_ack(void)
{
    g_unp_ack.type = REBOOT_DEVICE_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.state = UNP_SUCCESS;
}

static uint8_t unxx_compare(uint8_t *s1, uint8_t *s2, uint16_t len)
{
    uint16_t i;

    for(i = 0; i < len; i++) {
        if(s1[i] != s2[i]) {
            return 0;
        }
    }

    return 1;
}

void QunpUCXX22::deal_upgrade(uint8_t *buffer, uint16_t datasize)
{
    static uint8_t stage = 1;
    static uint8_t recv_swver[UNP_HWVER_LEN + 1] = {0};
    static uint32_t image_crc, calulate_crc, offset = 0;
    uint8_t recv_productid[UNP_PRODUCT_ID_LEN] = {0};
    uint8_t recv_hwver[UNP_HWVER_LEN + 1] = {0};
    uint8_t local_productid[UNP_PRODUCT_ID_LEN] = {0};
    uint8_t local_hwver[UNP_HWVER_LEN + 1] = {0};
    uint8_t pkt[32] = {0}, status[1] = {0};
    uint8_t data[UNP_MAX_PKTSIZE] = {0};
    uint16_t pktlen;
    //if(!passwd_verify_success) {
    //	return;
    //}

    memcpy(data, buffer, datasize);

    switch(stage) {
        case 1 :
            if(strncmp((const char *)buffer, UNP_UPGRADE_REQUEST, strlen(UNP_UPGRADE_REQUEST)) == 0) {
                set_upgrade_info(UPGRADE_FLAGS_VALUE, 0, 0);
                get_upgrade_info(&data[0], (uint32_t *)&data[1], (uint32_t *)&data[5]);
                if(data[0] == UPGRADE_FLAGS_VALUE) {
                    status[0] = UNP_SUCCESS;
                    pktlen = generate_pkt(status, sizeof(status), pkt, UPGRADE_DEVICE_ACK_PKT);
                    unp_send_pkt(pkt, pktlen);
                    unp_delay(500);
                    unxx_restart_device();
                }
            } else {
                image_crc = *(uint32_t *)data;
                memset(&recv_productid, 0, sizeof(recv_productid));
                memset(recv_hwver     , 0, sizeof(recv_hwver));
                memset(recv_swver     , 0, sizeof(recv_swver));
                memcpy(&recv_productid, data + 4                                     , UNP_PRODUCT_ID_LEN);
                memcpy(recv_hwver     , data + 4 + UNP_PRODUCT_ID_LEN                , UNP_HWVER_LEN);
                memcpy(recv_swver     , data + 4 + UNP_PRODUCT_ID_LEN + UNP_HWVER_LEN, UNP_SWVER_LEN);

                get_productid(local_productid);
                get_device_hwver(local_hwver);

                //HAL_Delay(500);
                //qDebug("@@@@@: local_productid = %s, recv_productid = %s, local_hwver = %s, recv_hwver = %s\n", local_productid, recv_productid, local_hwver, recv_hwver);
                //HAL_Delay(500);

                if(unxx_compare(local_productid, recv_productid, UNP_PRODUCT_ID_LEN) && unxx_compare(local_hwver, recv_hwver, UNP_HWVER_LEN)) {
                        status[0]    = UNP_SUCCESS;
                        stage        = 2;
                        offset       = 0;
                        calulate_crc = 0;
                } else {
                        status[0] = UNP_FAIL;
                }
                pktlen = generate_pkt(status, sizeof(status), pkt, UPGRADE_DEVICE_ACK_PKT);
                unp_send_pkt(pkt, pktlen);
                if (status[0] == UNP_FAIL) {
                     unp_delay(1000);
                     unxx_restart_device();
                }
            }
            break;
        case 2 :
            if(datasize == strlen(UNP_UPGRADE_COMPLETE) && strncmp((const char *)data, UNP_UPGRADE_COMPLETE, strlen(UNP_UPGRADE_COMPLETE)) == 0) {
                //HAL_Delay(500);
                //qDebug("@@@@@: calulate_crc = 0x%x, image_crc = 0x%x, offset = %d\n", calulate_crc, image_crc, offset);
                //HAL_Delay(500);
                if(calulate_crc == image_crc) {
                    set_device_swver(recv_swver);
                    set_upgrade_info(UPGRADE_FLAGS_VALUE, image_crc, offset);
                    status[0] = UNP_SUCCESS;
                } else {
                    status[0] = UNP_FAIL;
                }
                pktlen = generate_pkt(status, sizeof(status), pkt, UPGRADE_DEVICE_ACK_PKT);
                unp_send_pkt(pkt, pktlen);

//                uint8_t flag;
//                uint32_t crc32, size;
//                get_upgrade_info(&flag, &crc32, &size);
//                unp_delay(500);
//                qDebug("flag = 0x%x, crc32 = 0x%x, size = %d\r\n", flag, crc32, size);

#ifdef USE_IN_STM32
                unp_delay(1000);
                unxx_restart_device();
#endif
            } else {
#ifdef USE_IN_STM32
                if(UPGRADE_IMAGE_ADDR + offset + datasize < UPGRADE_IMAGE_SIZE) {
                    write_data_to_flash((uint32_t *)data, datasize, UPGRADE_IMAGE_ADDR + offset);
                    calulate_crc = my_ether_crc32(calulate_crc, data, datasize);
                    offset += datasize;
                }
#endif
            }
            break;
        default :
            break;
    }
}

void QunpUCXX22::deal_upgrade_ack(uint8_t *buffer, uint16_t datasize)
{
    Q_UNUSED(datasize)
    g_unp_ack.type = UPGRADE_DEVICE_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.state = (unp_state_t)buffer[0];
}

void QunpUCXX22::deal_read_param(uint8_t *data, uint16_t len)
{
    Q_UNUSED(len)
    uint8_t pkt[UNP_MAX_PKTSIZE] = {0};
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint16_t pktsize = 0, bufsize = 0;

    if(!unp_verify()) {
        return;
    }

    bufsize = read_device_params(data, buf);
    pktsize = generate_pkt(buf, bufsize, pkt, READ_PARAM_ACK_PKT);
    unp_send_pkt(pkt, pktsize);
}

void QunpUCXX22::deal_read_param_ack(uint8_t *data, uint16_t len)
{
    g_unp_ack.type = READ_PARAM_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.params_len = len;
//    qDebug("===========deal_read_param_ack============\n");
//    for(int i=0; i<len; i++){
//        qDebug("%02x",data[i]);
//    }
//    qDebug("   len=%d \n",len);
    memcpy(g_unp_ack.params, data, len);
//    QString ret ;
//    qDebug()<<ret.sprintf("%02x",*data);
//    ret.clear();
//    qDebug()<<ret.sprintf("%02x",*g_unp_ack.params);
}

void QunpUCXX22::deal_write_param(uint8_t *data, uint16_t len)
{
    uint8_t pkt[64] = {0}, status[1] = {0};
    uint16_t pktsize = 0;

    if(!unp_verify()) {
        return;
    }

    status[0] = write_device_params(data, len);
    unp_param_t type;
    type = (unp_param_t)data[0];
    if (type != PARAM_OUTPUT_IO_STATUS) {
        pktsize = generate_pkt(status, sizeof(status), pkt, WRITE_PARAM_ACK_PKT);
        unp_send_pkt(pkt, pktsize);
    }else{
//        unxx_change_report_process(1);
    }
}

void QunpUCXX22::deal_write_param_ack(uint8_t *data, uint16_t len)
{
    Q_UNUSED(len)
    g_unp_ack.type = WRITE_PARAM_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.state = (unp_state_t)data[0];
}

void QunpUCXX22::unp_delay(uint32_t ms)
{
#ifdef USE_IN_STM32
    HAL_Delay(ms);
#else
    QThread::msleep(ms);
#endif
}


unp_state_t QunpUCXX22::wait_for_ack(void)
{
    if(g_comnct_type == COMNCT_NFC){
        return UNP_SUCCESS;
    }
    if(onlyUcp){
        return UNP_SUCCESS;
    }

    read_serialport_data();

    uint32_t timeout = 0;

    while(timeout < UNP_MAX_TIMEOUT && m_ackFlag) {
        unp_delay(10);
        if(g_unp_ack.received) {
            return g_unp_ack.state;
        }
        timeout += 10;
    }
    m_ackFlag = false;
    return UNP_TIMEOUT_ERROR;
}

uint8_t QunpUCXX22::unp_verify(void)
{
    uint8_t ret = 1;

    if(g_comnct_type == COMNCT_UART) {
        if(!passwd_verify_success) {
            ret = 0;
        }
    }

    return ret;
}

uint16_t QunpUCXX22::generate_pkt(uint8_t *data, uint16_t datasize, uint8_t *pkt, unp_pack_t type)
{
    uint16_t offset = 4;
    uint8_t devname[UNP_DEVNAME_LEN + 1] = {0};

    pkt[0] = UNP_FRAME_FLAG;
    pkt[1] = type;

    if(UNP_DEVNAME_LEN) {
        get_device_name(devname);
        if(strlen((const char *)devname) == 0) {
            get_device_sn(devname);
        }
        memcpy(pkt + offset, devname, UNP_DEVNAME_LEN);
        offset += UNP_DEVNAME_LEN;
    }

    if(data && datasize) {
        memcpy(pkt + offset, data, datasize);
        offset += datasize;
    }

    pkt[offset++] = UNP_FRAME_FLAG;
    *(uint16_t *)(pkt + 2) = offset;

    return offset;
}

uint8_t QunpUCXX22::unp_frame_split(uint8_t *data, uint16_t datasize, uint16_t *pos, uint16_t *len)
{
    uint8_t num = 0;
    uint8_t cnt = 0;
    uint16_t i;

    for(i = 0; i < datasize; i++) {
        if(data[i] == UNP_FRAME_FLAG) {
            cnt++;
            if(cnt % 2) {
                pos[num] = i;
            } else {
                len[num] = i - pos[num] + 1;
                num++;
            }
        }
    }

    return num;
}

void QunpUCXX22::unp_send_pkt(uint8_t *data, uint16_t pktsize)
{
    if(g_comnct_type == COMNCT_NFC)
    {
        deal_with_unp(data,pktsize,COMNCT_NFC);
        return;
    }
    QString tmp;
    if(save_sms_command){
        tmp.clear();

        for(uint32_t i=0; i<pktsize; i++){
//            qDebug("%02x",data[i]);
            QString aa;
            aa.asprintf("%02x",data[i]);
            tmp.append(aa);
        }
//        qDebug("\n");
        int sms_count = sms_command.split("\n").size();
        QString sms_s = sms_command.split("\n").at(sms_count - 1);
        if(sms_s.length()+tmp.length() > 126){
            sms_command.append("\n");
            sms_command.append(tmp);
        }else{
            sms_command.append(tmp);
        }

    }

    if(!onlyUcp){

        if(m_port->isOpen() && m_ackFlag){
            printf("===========Write============\n");
            for(int i=0; i<pktsize; i++){
                printf("%02x",data[i]);
            }
            printf("   len=%d \n",pktsize);
            m_port->write(reinterpret_cast<const char *>(data), pktsize);
            m_port->waitForBytesWritten(3000);

        }else{
            qDebug()<<"SerialPort CLOSED";
        }
    }
}


uint16_t QunpUCXX22::read_device_params(uint8_t *params, uint8_t *data)
{
    uint16_t datasize = 0;
#ifndef USE_IN_BOOTLOADER
    uint8_t type;
    uint8_t id;
    uint8_t pn[UNP_PN_TOTAL_LEN] = {0};
    uint8_t edata[16] = {0};
    uint8_t *pdata;
#if defined(LORAWAN_DEVICE)
    uint16_t start_pos;
    uint16_t params_len;
#endif

    type = params[0];
    switch(type) {
        case PARAM_UNP_VERSION :
        {
            data[datasize++] = UNP_VERSION;
            break;
        }
        case PARAM_UNXX_PRODUCTID :
        {
            read_data_from_flash((uint32_t *)data, UNP_PRODUCT_ID_LEN, (uint32_t)pProductInfo->productid, 0);
            if(strstr((const char*)data,"0000"))
            {
                read_data_from_flash((uint32_t *)data, UNP_PRODUCT_ID_LEN_EM, (uint32_t)pProductInfo->productid_em, 0);
                datasize += UNP_PRODUCT_ID_LEN_EM;
            }
            else{
                datasize += UNP_PRODUCT_ID_LEN;
            }
            break;
        }
        case PARAM_UNXX_SN :
        {
            read_data_from_flash((uint32_t *)data, UNP_PRODUCT_SN_LEN2, (uint32_t)pProductInfo->productsn, 0);
            datasize += UNP_PRODUCT_SN_LEN2;
            break;
        }
        case PARAM_UNXX_HWVER :
        {
            read_data_from_flash((uint32_t *)data, UNP_HWVER_LEN, (uint32_t)pProductInfo->hwver, 0);
            datasize += UNP_HWVER_LEN;
            break;
        }
        case PARAM_UNXX_SWVER :
        {
            read_data_from_flash((uint32_t *)data, UNP_SWVER_LEN, (uint32_t)pProductInfo->swver, 0);
            datasize += UNP_SWVER_LEN;
            break;
        }
        case PARAM_UNXX_PN :
        {
            if(m_product.contains("EM") || m_product.startsWith("UC5")){
                get_device_pn_em(pn);
            }else{
                get_device_pn(pn);
            }

            memcpy(data, pn, UNP_PN_TOTAL_LEN);
            datasize += strlen((const char *)pn);
            break;
        }
        case PARAM_UNXX_OEM :
        {
            uint8_t oem[UNP_PN_LEN + 1] = {0};

            get_device_oem(oem);
            qDebug("===device oem:%s\r\n", oem);
            memcpy(data, oem, UNP_PN_LEN+1);
            datasize += strlen((const char *)oem);
            break;
        }
        case PARAM_UNXX_REAL_PN:
        {

            get_device_real_pn(pn);

            memcpy(data, pn, UNP_REAL_PN_TOTAL_LEN);
            datasize += strlen((const char *)pn);
            break;
        }

        case PARAM_DEVICE_STATUS:
        {
            memcpy(data, (void*)&pStatus->uc11t1_status, sizeof(device_status_t));
            datasize += sizeof(device_status_t);

            break;
        }
        case PARAM_POWER_CTRL:
        {
            uint8_t data2[32];
            memcpy(data2, (void*)&pStatus->uc11t1_status, sizeof(device_status_t));
            data[datasize++] = data2[2];

            break;
        }
#ifdef USE_IN_STM32
        case PARAM_OUTPUT_IO_STATUS:
        case PARAM_INPUT_IO_STATUS:
        {
            uint8_t num;

            num = params[1];
            data[datasize++] = unxx_gpio_get_value(num);
            break;
        }
        case PARAM_AI_VALUE:
        {
            uint8_t num;
            float val;

            num = params[1];
            if(num > 0 && num <= UNXX_MAX_AI_NUM) {
                val = unxx_adc_get_value(num);
                *(float *)data = val;
                datasize += sizeof(float);
            }
            break;
        }
#endif
        case PARAM_USER_CONFIG :
        {
//            read_data_from_flash((uint32_t *)data, sizeof(user_config_t), (uint32_t)pUserConfig, 0);

            memcpy(data, pUserConfig, sizeof(user_config_t));
            datasize += sizeof(user_config_t);
            break;
        }
        case PARAM_DEVICE_TIME:
        {
            uint32_t timestamp;
            timestamp = pStatus->timpstamp;

            memcpy(data, &timestamp, sizeof(uint32_t));
            datasize += sizeof(uint32_t);
            break;
        }
        case PARAM_HT_VALUE:
        {
            sensor_status_em sensor_data;
            sensor_data.opt1  = pStatus->data[0];
            sensor_data.opt2  = pStatus->data[1];
            sensor_data.opt3  = pStatus->data[2];
            sensor_data.opt4  = pStatus->data[3];

            memcpy(data, &sensor_data, sizeof(sensor_status_em));
            datasize += sizeof(sensor_status_em);

            break;
        }

        case PARAM_HT_ALARM:
        {
            //alarm_rules_t rules;
            //uint8_t *pdata;
            id = params[1];
            if(id > 0 && id <= UNP_MAX_RULES_NUM) {
                    //read_data_from_flash((uint32_t *)&rules, sizeof(rules), (uint32_t)&pAlarmParams->rules[id-1], 0);
                    //qDebug("===mode = %d, min = %d, max = %d, lock = %d, continue = %d\r\n", rules.mode, rules.min_value, rules.max_value, rules.lock_time, rules.continue_time);
                    //data[datasize++] = rules.mode;

                    //pdata = (uint8_t *)&rules.min_value;
                    //data[datasize++] = pdata[0];
                    //data[datasize++] = pdata[1];

                    //pdata = (uint8_t *)&rules.max_value;
                    //data[datasize++] = pdata[0];
                    //data[datasize++] = pdata[1];

                    //pdata = (uint8_t *)&rules.lock_time;
                    //data[datasize++] = pdata[0];
                    //data[datasize++] = pdata[1];

                    //pdata = (uint8_t *)&rules.continue_time;
                    //data[datasize++] = pdata[0];
                    //data[datasize++] = pdata[1];
                    if(id == 1) {
                            memcpy(data, &pAlarmParams->rules[id-1], 14);
                    } else if(id == 2) {
                            memcpy(data, ((uint8_t *)&pAlarmParams->rules[0] + 14), 14);
                    }
                    datasize += 14;
            }
            break;
        }
        case PARAM_ABNORMAL_SET:
        {
            abnormal_check_set_t abnormal_check_set;
            uint8_t *pdata;

            read_data_from_flash((uint32_t *)&abnormal_check_set, sizeof(abnormal_check_set), (uint32_t)&pApplication_am->abnormal_check_set, 0);
            data[datasize++] = abnormal_check_set.enable;

            pdata = (uint8_t *)&abnormal_check_set.range;
            data[datasize++] = pdata[0];
            data[datasize++] = pdata[1];

            pdata = (uint8_t *)&abnormal_check_set.percentage;
            data[datasize++] = pdata[0];


            abnormal_check_patch_set_t abnormal_check_patch_set;
            read_data_from_flash((uint32_t *)&abnormal_check_patch_set, sizeof(abnormal_check_patch_set), (uint32_t)&pApplication_am->abnormal_check_patch_set, 0);

            pdata = (uint8_t *)&abnormal_check_patch_set.percentage;
            data[datasize++] = pdata[0];

            pdata = (uint8_t *)&abnormal_check_patch_set.retry_count;
            data[datasize++] = pdata[0];

            pdata = (uint8_t *)&abnormal_check_patch_set.retry_interval;
            data[datasize++] = pdata[0];

            break;
        }
        case PARAM_LORA:
        {
            start_pos  = params[1];
            params_len = params[2];
//            printf_info("read lorawan param:%d pos %d len %d\r\n", type, start_pos, params_len);
            if (((start_pos+params_len) > LORA_INFO_LEN) || params_len > 256) {
                datasize = 0;
            } else {
                if (start_pos == 196) {
                    start_pos = 2048;
                } else if (start_pos == 200) {
                    start_pos = 2052;
                }
                memcpy(data, (uint8_t *)pLoRaWANParams+start_pos, params_len);
                datasize = params_len;
            }

            break;
        }
        case PARAM_CONSOLE_CTRL :
        {
            read_data_from_flash((uint32_t *)data, sizeof(pDeviceParam->debug), (uint32_t)&pDeviceParam->debug, 0);
            datasize += sizeof(pDeviceParam->debug);
            break;
        }
        case PARAM_CLOUD_REPORT_PERIOD:
        {
            read_data_from_flash((uint32_t *)edata, sizeof(pApplication_am->report_cycle), (uint32_t)&pApplication_am->report_cycle, 0);
            data[datasize++] = edata[0];
            data[datasize++] = edata[1];
            break;
        }
        case PARAM_COLLECT_PERIOD:
        {
            read_data_from_flash((uint32_t *)edata, sizeof(pApplication->collect_cycle), (uint32_t)&pApplication->collect_cycle, 0);
            data[datasize++] = edata[0];
            data[datasize++] = edata[1];
            break;
        }
        case PARAM_CONSOLE_CFG :
        {
            uint8_t num;
            struct console_param uartcfg;

            num = params[1];
            if(num < UART_MAX_ID) {
                if(num == 0){
                    read_data_from_flash((uint32_t *)&uartcfg, sizeof(uartcfg), (uint32_t)&pDeviceParam->con_param[num], 0);
                }else{
                    read_data_from_flash((uint32_t *)&uartcfg, sizeof(uartcfg), (uint32_t)pDeviceParam+100, 0);//因结构体偏差此处特殊处理
                }
                qDebug("uartcfg.app.enable = %d  \n",uartcfg.app.enable);
                pdata            = (uint8_t *)&uartcfg.baud;
                data[datasize++] = pdata[0];
                data[datasize++] = pdata[1];
                data[datasize++] = pdata[2];
                data[datasize++] = pdata[3];
                data[datasize++] = uartcfg.databits;
                data[datasize++] = uartcfg.stopbits;
                data[datasize++] = uartcfg.parity;
                data[datasize++] = uartcfg.flow;

                data[datasize++] = uartcfg.app.mode;
                data[datasize++] = uartcfg.app.enable;
                data[datasize++] = uartcfg.app.protocol;

                pdata            = (uint8_t *)&uartcfg.app.idle_time;
                data[datasize++] = pdata[0];
                data[datasize++] = pdata[1];

                pdata            = (uint8_t *)&uartcfg.app.interval_time;
                data[datasize++] = pdata[0];
                data[datasize++] = pdata[1];

                pdata            = (uint8_t *)&uartcfg.app.probe_cnt;
                data[datasize++] = pdata[0];
                data[datasize++] = pdata[1];

                pdata            = (uint8_t *)&uartcfg.app.bytes_per_frame;
                data[datasize++] = pdata[0];
                data[datasize++] = pdata[1];

                pdata            = (uint8_t *)&uartcfg.app.interval_per_frame;
                data[datasize++] = pdata[0];
                data[datasize++] = pdata[1];

                memcpy(data + datasize, uartcfg.app.register_packet, sizeof(uartcfg.app.register_packet));
                datasize += sizeof(uartcfg.app.register_packet);

                for(id = 0; id < UNP_DTU_SERVER_NUM; id++) {
                    data[datasize++] = uartcfg.app.destination.ip[id][0];
                    data[datasize++] = uartcfg.app.destination.ip[id][1];
                    data[datasize++] = uartcfg.app.destination.ip[id][2];
                    data[datasize++] = uartcfg.app.destination.ip[id][3];

                    pdata            = (uint8_t *)&uartcfg.app.destination.port[id];
                    data[datasize++] = pdata[0];
                    data[datasize++] = pdata[1];
                }

                if((datasize + 5)%64 == 0) {
                    data[datasize++] = 0;
                }
            }
            break;
        }
        case PARAM_INTELLIGENT_DISPLAY:
        {
           read_data_from_flash((uint32_t *)data, sizeof(pApplication_am->intelligent_display), (uint32_t)&pApplication_am->intelligent_display, 0);
           datasize += sizeof(pApplication_am->intelligent_display);
           break;
        }
        case PARAM_DISPLAY_MODE:
        {
            read_data_from_flash((uint32_t *)data, sizeof(pApplication_am->display_mode), (uint32_t)&pApplication_am->display_mode, 0);
            datasize += sizeof(pApplication_am->display_mode);
            break;
        }
        case PARAM_3V3_SET:
        {
            read_data_from_flash((uint32_t *)&data[datasize++], sizeof(uint8_t), (uint32_t)&pApplication->enable_3v3_out1, 0);
            read_data_from_flash((uint32_t *)&data[datasize++], sizeof(uint8_t), (uint32_t)&pApplication->enable_3v3_out2, 0);
            break;
        }
        case PARAM_KEEP_PWR_STATE:
        {
            read_data_from_flash((uint32_t *)&data[datasize++], sizeof(pApplication->keep_pwr_state), (uint32_t)&pApplication->keep_pwr_state, 0);
            break;
        }
        case PARAM_DEVICE_STATE :
        {
//                uint8_t state = 0;
//                read_data_from_flash((uint32_t *)&state,1,(uint32_t )&pDeviceParam->device_state,0);
//                memcpy(data, &state, 1);
//                datasize ++;
            read_data_from_flash((uint32_t *)&data[datasize++], sizeof(pApplication->connect_pwr), (uint32_t)&pApplication->connect_pwr, 0);
            break;
        }
        case PARAM_CLASSA_RESPONSE_TIME:
        {
            read_data_from_flash((uint32_t *)edata, sizeof(pApplication->classa_response_time), (uint32_t)&pApplication->classa_response_time, 0);
            data[datasize++] = edata[0];
            data[datasize++] = edata[1];

            break;
        }
        case PARAM_REPORT_ENABLE_TYPE:
        {
            read_data_from_flash((uint32_t *)&data[datasize++], sizeof(pApplication->report_enable_type), (uint32_t)&pApplication->report_enable_type, 0);
            break;
        }
        default :
        {
            break;
        }
    }
#endif

    return datasize;
}

unp_state_t QunpUCXX22::send_read_param_request(uint8_t *out, uint8_t *in, uint16_t insize)
{
    uint8_t pkt[UNP_MAX_PKTSIZE] = {0};
    uint16_t pktsize = 0;
    pktsize = generate_pkt(in, insize, pkt, READ_PARAM_PKT);

    memset(&g_unp_ack, 0, sizeof(g_unp_ack));

    unp_send_pkt(pkt, pktsize);

    if(wait_for_ack() == UNP_SUCCESS) {
        memcpy(out, g_unp_ack.params, g_unp_ack.params_len);
        return UNP_SUCCESS;
    } else {
        return UNP_FAIL;
    }
}

unp_state_t QunpUCXX22::send_write_param_request(uint8_t *data, uint16_t datasize)
{
    uint8_t pkt[UNP_MAX_PKTSIZE] = {0};
    uint16_t pktsize = 0;

    pktsize = generate_pkt(data, datasize, pkt, WRITE_PARAM_PKT);

    memset(&g_unp_ack, 0, sizeof(g_unp_ack));

    unp_send_pkt(pkt, pktsize);

    if(wait_for_ack() == UNP_SUCCESS) {
        return UNP_SUCCESS;
    } else {
        return UNP_FAIL;
    }
}

unp_state_t QunpUCXX22::write_device_params(uint8_t *data, uint16_t datasize)
{
    unp_state_t ret = UNP_SUCCESS;
#ifndef USE_IN_BOOTLOADER
    unp_param_t type;
    uint8_t id;
    uint8_t offset = 0;
    uint8_t temp[8] = {0};
    uint8_t *params = data + 1;
    uint16_t real_datasize = datasize - 1;
#if defined(LORAWAN_DEVICE)
    uint16_t start_pos;
    uint16_t params_len;
#endif

    type = (unp_param_t)data[0];
//    qDebug("type = %02x\n",type);
    switch(type) {
        case PARAM_UNXX_PN:
        {
            if(strstr((const char*)params,"CN470") != nullptr)
                pLoRaWANParams->region =CN470;
            else if(strstr((const char*)params,"EU433") != nullptr)
                pLoRaWANParams->region =EU433;
            else if(strstr((const char*)params,"AS923") != nullptr)
                pLoRaWANParams->region =AS923;
            else if(strstr((const char*)params,"AU915") != nullptr)
                pLoRaWANParams->region =AU915;
            else if(strstr((const char*)params,"EU868") != nullptr)
                pLoRaWANParams->region =EU868;
            else if(strstr((const char*)params,"KR920") != nullptr)
                pLoRaWANParams->region =KR920;
            else if(strstr((const char*)params,"IN865") != nullptr)
                pLoRaWANParams->region =IN865;
            else if(strstr((const char*)params,"US915") != nullptr)
                pLoRaWANParams->region =US915;
            else if(strstr((const char*)params,"US915_HYBRID") != nullptr)
                pLoRaWANParams->region =US915_HYBRID;
            else if(strstr((const char*)params,"CN779") != nullptr)
                pLoRaWANParams->region =CN779;
            else if(strstr((const char*)params,"RU864") != nullptr)
                pLoRaWANParams->region =RU864;

            offset = 0;

            memcpy(pPNInfo->region, params, 2);
            offset += 2;

            memcpy(pPNInfo->pn[0], params + offset, 3);
            offset += 3;
            break;
        }
        case PARAM_LORA:
        {
            start_pos  = data[1];
            params_len = data[2];

            if (params_len > 256 || ((start_pos+params_len) > LORA_INFO_LEN)) {
                ret = UNP_FAIL;
            } else {
                LoRaWANParams_t lorawanparams_setting;

                if (start_pos == 196) {
                    start_pos = 1024;
                } else if (start_pos == 200) {
                    start_pos = 1028;
                }

                read_data_from_flash((uint32_t *)&lorawanparams_setting, sizeof(LoRaWANParams_t), (uint32_t)pLoRaWANParams, 0);
                memcpy((uint8_t *)&lorawanparams_setting+start_pos, (uint8_t *)data+3, params_len);
                write_data_to_flash((uint32_t *)&lorawanparams_setting, sizeof(lorawanparams_setting), (uint32_t)pLoRaWANParams);
#ifdef USE_IN_STM32
                SetDownLinkCounter(lorawanparams_setting.DownLinkCounter);
                SetUpLinkCounter(lorawanparams_setting.UpLinkCounter);
#endif
#if 0
                int i;
                for (i=0; i<datasize; i++)
                    qDebug("%x", data[i]); qDebug("\r\n");
#endif
            }
            break;
        }
        case PARAM_CONSOLE_CTRL :
        {
            write_data_to_flash((uint32_t *)params, 1, (uint32_t)pDeviceParam->debug);
            break;
        }
        case PARAM_DEVICE_PASSWD :
        {
            read_data_from_flash((uint32_t *)temp, sizeof(pDeviceParam->password), (uint32_t)pDeviceParam->password, 0);
            write_data_to_flash((uint32_t *)(params + UNP_PASSWD_LEN), UNP_PASSWD_LEN, (uint32_t)pDeviceParam->password);

            break;
        }
        case PARAM_CLOUD_REPORT_PERIOD:
        {
            uint16_t value;

            memset(temp, 0, sizeof(temp));
            memcpy(temp, params + offset, 2);
            value  = *(uint16_t *)temp;
            write_data_to_flash((uint32_t *)&value, sizeof(value), (uint32_t)&pApplication_am->report_cycle);
#ifdef USE_IN_STM32
            unxx_lorawan_report_cycle_update(value);
#endif
            break;
        }
        case PARAM_COLLECT_PERIOD:
        {
            uint16_t value;
            uint16_t old_value;

            memset(temp, 0, sizeof(temp));
            memcpy(temp, params + offset, 2);
            value  = *(uint16_t *)temp;

            if(value >= 60) {
                read_data_from_flash((uint32_t *)&old_value, sizeof(old_value), (uint32_t)&pApplication->collect_cycle, 0);
                write_data_to_flash((uint32_t *)&value, sizeof(value), (uint32_t)&pApplication->collect_cycle);
            } else {
                ret = UNP_FAIL;
            }
            break;
        }
        case PARAM_USER_CONFIG :
        {
            user_config_t sensor_cfg;

            memcpy(&sensor_cfg, params, real_datasize);
            write_data_to_flash((uint32_t *)&sensor_cfg, sizeof(user_config_t), (uint32_t)pUserConfig);
            qDebug("=$$$$$$$$$$$$$$$$$$$$ %d %d %d\n",pUserConfig->sensor1.enable,pUserConfig->sensor2.enable,pUserConfig->sensor3.enable);
            qDebug("=$$$$$$$$$$$$$$$$$$$$ %d %d %d\n",pUserConfig->sensor1.calibration_enable,pUserConfig->sensor2.calibration_enable,pUserConfig->sensor3.calibration_enable);
            break;
        }
        case PARAM_HT_ALARM:
        {
            id = data[1];
            if(id > 0 && id <= UNP_MAX_RULES_NUM) {
                //memcpy((uint32_t *)&rules, &data[2], sizeof(rules));
                //offset = 2;
                //rules.mode = (alarm_mode_t)data[offset++];

                //rules.min_value = *(uint16_t *)(data + offset);
                //offset += sizeof(uint16_t);

                //rules.max_value = *(uint16_t *)(data + offset);
                //offset += sizeof(uint16_t);

                //rules.lock_time = *(uint16_t *)(data + offset);
                //offset += sizeof(uint16_t);

                //rules.continue_time = *(uint16_t *)(data + offset);
                //offset += sizeof(uint16_t);
                if(id == 1) {
                    write_data_to_flash((uint32_t *)&data[2], 14, (uint32_t)&pAlarmParams->rules[id-1]);
                } else if(id == 2) {
                    write_data_to_flash((uint32_t *)&data[2], 14, (uint32_t)((uint8_t *)&pAlarmParams->rules[0] + 14));
                }
                //unxx_alarm_reload();
            }
            break;
        }
        case PARAM_CONSOLE_CFG :
        {
            uint8_t num;
            struct console_param uartcfg;

            num   = params[offset++];
            if(num < UART_MAX_ID) {
                if(num == 0){
                    read_data_from_flash((uint32_t *)&uartcfg, sizeof(uartcfg), (uint32_t)&pDeviceParam->con_param[num], 0);
                }else{
                    read_data_from_flash((uint32_t *)&uartcfg, sizeof(uartcfg), (uint32_t)pDeviceParam+100, 0);
                }

                memset(temp, 0              , sizeof(temp));
                memcpy(temp, params + offset, 4);
                offset += 4;
                uartcfg.baud          = *(uint32_t *)temp;
                uartcfg.databits      = params[offset++];
                uartcfg.stopbits      = params[offset++];
                uartcfg.parity        = params[offset++];
                uartcfg.flow          = params[offset++];
                qDebug("uartcfg.app.enable11 = %d\n",uartcfg.app.enable);
                uartcfg.app.mode      = params[offset++];
                uartcfg.app.enable    = params[offset++];
                qDebug("uartcfg.app.enable22 = %d\n",uartcfg.app.enable);
                uartcfg.app.protocol  = (serial_protocol_t)params[offset++];

                memset(temp, 0              , sizeof(temp));
                memcpy(temp, params + offset, sizeof(uartcfg.app.idle_time));
                offset += 2;
                uartcfg.app.idle_time = *(uint16_t *)temp;

                memset(temp, 0              , sizeof(temp));
                memcpy(temp, params + offset, sizeof(uartcfg.app.interval_time));
                offset += 2;
                uartcfg.app.interval_time = *(uint16_t *)temp;

                memset(temp, 0              , sizeof(temp));
                memcpy(temp, params + offset, sizeof(uartcfg.app.probe_cnt));
                offset += 2;
                uartcfg.app.probe_cnt = *(uint16_t *)temp;

                memset(temp, 0              , sizeof(temp));
                memcpy(temp, params + offset, sizeof(uartcfg.app.bytes_per_frame));
                offset += 2;
                uartcfg.app.bytes_per_frame = *(uint16_t *)temp;

                memset(temp, 0              , sizeof(temp));
                memcpy(temp, params + offset, sizeof(uartcfg.app.interval_per_frame));
                offset += 2;
                uartcfg.app.interval_per_frame = *(uint16_t *)temp;

                memcpy(uartcfg.app.register_packet, params + offset, sizeof(uartcfg.app.register_packet));
                offset += sizeof(uartcfg.app.register_packet);

                for(id = 0; id < UNP_DTU_SERVER_NUM && offset <= real_datasize; id++) {
                    memcpy(uartcfg.app.destination.ip[id], params + offset, 4);
                    offset += 4;

                    memset(temp, 0              , sizeof(temp));
                    memcpy(temp, params + offset, sizeof(uartcfg.app.destination.port[id]));
                    offset += 2;
                    uartcfg.app.destination.port[id] = *(uint16_t *)temp;
                }
                if(num == 0){
                    write_data_to_flash((uint32_t *)&uartcfg, sizeof(struct console_param), (uint32_t)&pDeviceParam->con_param[num]);
                }else{
                    write_data_to_flash((uint32_t *)&uartcfg, sizeof(struct console_param), (uint32_t)pDeviceParam+100);
                }

            }
            break;
        }
        case PARAM_ABNORMAL_SET:
        {

            abnormal_check_set_t abnormal_check_set;
            abnormal_check_patch_set_t abnormal_check_patch_set;

            offset = 1;
            abnormal_check_set.enable = *(uint8_t *)(data + offset);
            offset += sizeof(uint8_t);

            abnormal_check_set.range = *(int16_t *)(data + offset);
            offset += sizeof(int16_t);

            abnormal_check_set.percentage = *(uint8_t *)(data + offset);
            offset += sizeof(int8_t);

            if(offset < real_datasize) {
                abnormal_check_patch_set.percentage = *(uint8_t *)(data + offset);
                offset += sizeof(int8_t);

                abnormal_check_patch_set.retry_count = *(uint8_t *)(data + offset);
                offset += sizeof(int8_t);

                abnormal_check_patch_set.retry_interval = *(uint8_t *)(data + offset);
                offset += sizeof(int8_t);

                write_data_to_flash((uint32_t *)&abnormal_check_patch_set, sizeof(abnormal_check_patch_set), (uint32_t)&pApplication_am->abnormal_check_patch_set);
            }

            write_data_to_flash((uint32_t *)&abnormal_check_set, sizeof(abnormal_check_set), (uint32_t)&pApplication_am->abnormal_check_set);

            break;
        }
        case PARAM_INTELLIGENT_DISPLAY:
        {
            write_data_to_flash((uint32_t *)&params[offset++], sizeof(uint8_t), (uint32_t)&pApplication_am->intelligent_display);
            break;
        }
        case PARAM_DISPLAY_MODE:
        {
            write_data_to_flash((uint32_t *)params, 1, (uint32_t)&pApplication_am->display_mode);
            break;
        }
        case PARAM_3V3_SET:
        {
            write_data_to_flash((uint32_t *)&params[offset++], sizeof(uint8_t), (uint32_t)&pApplication->enable_3v3_out1);
            write_data_to_flash((uint32_t *)&params[offset++], sizeof(uint8_t), (uint32_t)&pApplication->enable_3v3_out2);
#ifdef USE_IN_STM32
            unxx_3v3_out_control();
#endif
            break;
        }
        case PARAM_KEEP_PWR_STATE:
        {
            write_data_to_flash((uint32_t *)&params[offset++], sizeof(pApplication->keep_pwr_state), (uint32_t)&pApplication->keep_pwr_state);
            break;
        }
        case PARAM_DEVICE_STATE:
        {
            write_data_to_flash((uint32_t *)&params[offset++], sizeof(pApplication->connect_pwr), (uint32_t)&pApplication->connect_pwr);
            break;
        }
        case PARAM_CLASSA_RESPONSE_TIME:
        {
            write_data_to_flash((uint32_t *)&params[offset++], sizeof(pApplication->classa_response_time), (uint32_t)&pApplication->classa_response_time);
            break;
        }
        case PARAM_REPORT_ENABLE_TYPE:
        {
            write_data_to_flash((uint32_t *)&params[offset++], sizeof(pApplication->report_enable_type), (uint32_t)&pApplication->report_enable_type);
            break;
        }
#ifdef USE_IN_STM32
        case PARAM_POWER_ON:
        {
            unxx_set_power_state(POWER_ON);
            break;
        }
        case PARAM_POWER_OFF:
        {
            unxx_set_power_state(POWER_OFF);
            break;
        }
#endif
        default :
        {
            ret = UNP_FAIL;
            break;
        }
    }
#endif
    return ret;
}

void QunpUCXX22::get_device_passwd(uint8_t *data)
{
    Q_UNUSED(data)
    read_data_from_flash((uint32_t *)data, UNP_PASSWD_LEN, (uint32_t)pDeviceParam->password, 0);
}

void QunpUCXX22::get_device_appkey(uint8_t *data)
{
    read_data_from_flash((uint32_t *)data, 16, (uint32_t)pLoRaWANParams->AppKey, 0);
}

void QunpUCXX22::get_productid(uint8_t *data)
{
    read_data_from_flash((uint32_t *)data, UNP_PRODUCT_ID_LEN, (uint32_t)pProductInfo->productid, 0);
}

void QunpUCXX22::get_device_hwver(uint8_t *data)
{
    read_data_from_flash((uint32_t *)data, UNP_HWVER_LEN, (uint32_t)pProductInfo->hwver, 0);
}
void QunpUCXX22::set_device_swver(uint8_t *data)
{
    write_data_to_flash((uint32_t *)data, strlen((const char *)data), (uint32_t)pProductInfo->swver);
}

void QunpUCXX22::set_upgrade_enable_flag(uint8_t upgrade_enable)
{
    write_data_to_flash((uint32_t *)&upgrade_enable, 1, (uint32_t)&pFlash_flag->upgrade_enable);
}

void QunpUCXX22::set_upgrade_flag(uint8_t *buf)
{
    if(strlen((const char *)buf) < UPGRADE_INFO_LEN) {
        write_data_to_flash((uint32_t *)buf, strlen((const char *)buf), FLASH_UPGRADE_INFO_ADDR);
    }
}

void QunpUCXX22::get_upgrade_flag(uint8_t *buf)
{
    memcpy(buf, (void *)FLASH_UPGRADE_INFO_ADDR, UPGRADE_INFO_LEN);
}

void QunpUCXX22::get_device_name(uint8_t *data)
{
    read_data_from_flash((uint32_t *)data, UNP_DEVNAME_LEN, (uint32_t)pDeviceParam->name, 0);
}

void QunpUCXX22::get_device_pn_em(uint8_t *data)
{
    uint8_t offset = 0;
    uint8_t len = 0;
    uint8_t tmp[UNP_PN_TOTAL_LEN];
    memset(tmp, 0, sizeof(tmp));
    /*read_data_from_flash((uint32_t *)tmp, sizeof(pPNInfo->region), (uint32_t)pPNInfo->region, 0);
    len = snprintf((char *)data + offset, UNP_PN_TOTAL_LEN - offset, "%s", tmp);
    offset += len;*/
    memset(tmp, 0, sizeof(tmp));

    read_data_from_flash((uint32_t *)tmp, sizeof(pPNInfo->pn_em[0]), (uint32_t)pPNInfo->pn_em[0], 0);
    if(strlen((const char *)tmp)) {
        len = snprintf((char *)data + offset, UNP_PN_TOTAL_LEN - offset, "%s", tmp);
         offset += len;
    }


    read_data_from_flash((uint32_t *)tmp, sizeof(pPNInfo->pn_em[1]), (uint32_t)pPNInfo->pn_em[1], 0);
    if(strlen((const char *)tmp)) {
        len = snprintf((char *)data + offset, UNP_PN_TOTAL_LEN - offset, "-%s", tmp);
         offset += len;
    }

    read_data_from_flash((uint32_t *)tmp, sizeof(pPNInfo->pn_em[1]), (uint32_t)pPNInfo->pn_em[2], 0);
    if(strlen((const char *)tmp)) {
        len = snprintf((char *)data + offset, UNP_PN_TOTAL_LEN - offset, "-%s", tmp);
         offset += len;
    }

    read_data_from_flash((uint32_t *)tmp, sizeof(pPNInfo->pn_em[1]), (uint32_t)pPNInfo->pn_em[3], 0);
    if(strlen((const char *)tmp)) {
        len = snprintf((char *)data + offset, UNP_PN_TOTAL_LEN - offset, "-%s", tmp);
         offset += len;
    }

#ifdef LORAWAN_DEVICE
    memset(tmp, 0, sizeof(tmp));
    read_data_from_flash((uint32_t *)tmp, sizeof(pPNInfo->pn[0]), (uint32_t)pPNInfo->pn[0], 0);
    if(strlen((const char *)tmp)) {
        if(offset >0)
            len = snprintf((char *)data + offset, UNP_PN_TOTAL_LEN - offset, "-%sM", tmp);
        else
            len = snprintf((char *)data + offset, UNP_PN_TOTAL_LEN - offset, "-%sM", tmp);
        offset += len;
    }
#endif
}

void QunpUCXX22::get_device_real_pn(uint8_t *data)
{
    uint8_t offset = 0;
    uint8_t len = 0;
    uint8_t tmp[UNP_PN_TOTAL_LEN];
    memset(tmp, 0, sizeof(tmp));

    read_data_from_flash((uint32_t *)tmp, sizeof(pPNInfo->pn_em[1]), (uint32_t)pPNInfo->pn_em[1], 0);
    if(strlen((const char *)tmp)) {
        len = snprintf((char *)data + offset, UNP_PN_TOTAL_LEN - offset, "%s", tmp);
         offset += len;
    }

    read_data_from_flash((uint32_t *)tmp, sizeof(pPNInfo->pn_em[1]), (uint32_t)pPNInfo->pn_em[2], 0);
    if(strlen((const char *)tmp)) {
        len = snprintf((char *)data + offset, UNP_PN_TOTAL_LEN - offset, "-%s", tmp);
         offset += len;
    }

    read_data_from_flash((uint32_t *)tmp, sizeof(pPNInfo->pn_em[1]), (uint32_t)pPNInfo->pn_em[3], 0);
    if(strlen((const char *)tmp)) {
        len = snprintf((char *)data + offset, UNP_PN_TOTAL_LEN - offset, "-%s", tmp);
         offset += len;
    }
}

void QunpUCXX22::get_device_pn(uint8_t *data)
{
    uint8_t offset = 0;
    uint8_t len = 0;
    uint8_t i;
    uint8_t tmp[UNP_PN_TOTAL_LEN];

    memset(tmp, 0, sizeof(tmp));
    read_data_from_flash((uint32_t *)tmp, sizeof(pPNInfo->region), (uint32_t)pPNInfo->region, 0);
    len = snprintf((char *)data + offset, UNP_PN_TOTAL_LEN - offset, "%s", tmp);
    offset += len;

#ifdef LORAWAN_DEVICE
    memset(tmp, 0, sizeof(tmp));
    read_data_from_flash((uint32_t *)tmp, sizeof(pPNInfo->pn[0]), (uint32_t)pPNInfo->pn[0], 0);
    if(strlen((const char *)tmp)) {
                    len = snprintf((char *)data + offset, UNP_PN_TOTAL_LEN - offset, "%s", tmp);
    }
    offset += len;
#endif

    if(offset) {
            memset(tmp, 0, sizeof(tmp));
            read_data_from_flash((uint32_t *)tmp, sizeof(pPNInfo->custom), (uint32_t)pPNInfo->custom, 0);
            len = snprintf((char *)data + offset, UNP_PN_TOTAL_LEN - offset, "-%s", tmp);
    } else {
            memset(tmp, 0, sizeof(tmp));
            read_data_from_flash((uint32_t *)tmp, sizeof(pPNInfo->custom), (uint32_t)pPNInfo->custom, 0);
            len = snprintf((char *)data + offset, UNP_PN_TOTAL_LEN - offset, "%s", tmp);
    }
    offset += len;

    for(i = 1; i < UNP_PN_NUM; i++) {
            memset(tmp, 0, sizeof(tmp));
            read_data_from_flash((uint32_t *)tmp, sizeof(pPNInfo->pn[i]), (uint32_t)pPNInfo->pn[i], 0);
            if(strlen((const char *)tmp)) {
                    if(offset) {
                            len = snprintf((char *)data + offset, UNP_PN_TOTAL_LEN - offset, "-%s", tmp);
                    } else {
                            len = snprintf((char *)data + offset, UNP_PN_TOTAL_LEN - offset, "%s", tmp);
                    }
            }
            offset += len;
    }

}

void QunpUCXX22::get_device_oem(uint8_t *data)
{
    uint8_t offset = 0;
    uint8_t len = 0;
    uint8_t tmp[UNP_PN_LEN + 1];

    memset(tmp, 0, sizeof(tmp));
    read_data_from_flash((uint32_t *)tmp, sizeof(pPNInfo->pn[3]), (uint32_t)pPNInfo->pn[3], 0);
    if(strlen((const char *)tmp)) {
        len = snprintf((char *)data + offset, UNP_PN_LEN+1 - offset, "%s", tmp);
        offset += len;
    }
}

void QunpUCXX22::get_device_custom(uint16_t *value)
{
    uint8_t temp[UNP_CUSTOM_LEN + 1];
    uint32_t data;

    read_data_from_flash((uint32_t *)temp, sizeof(pPNInfo->custom), (uint32_t)pPNInfo->custom, 0);
    sscanf((const char *)temp, "%x", &data);

    *value = data;
}

void QunpUCXX22::get_device_sn(uint8_t *data)
{
    read_data_from_flash((uint32_t *)data, UNP_PRODUCT_SN_LEN, (uint32_t)pProductInfo->productsn, 0);
}

void QunpUCXX22::write_data_to_flash(uint32_t *data, uint16_t len_bytes, uint32_t addr)
{
    memcpy((void *)addr, data, len_bytes);
}

void QunpUCXX22::read_data_from_flash(uint32_t *data, uint16_t len_bytes, uint32_t addr, uint8_t fromisr)
{
    Q_UNUSED(fromisr)
    memcpy(data, (void *)addr, len_bytes);
}

void QunpUCXX22::unxx_reset_device(void)
{

}
void QunpUCXX22::unxx_restart_device(void)
{

}

void QunpUCXX22::unp_set_ussd_ack(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(data)
    Q_UNUSED(datasize)
}

void QunpUCXX22::get_upgrade_info(uint8_t *flag, uint32_t *crc32, uint32_t *size)
{
    Q_UNUSED(flag)
    Q_UNUSED(size)
    Q_UNUSED(crc32)
}

void QunpUCXX22::set_upgrade_info(uint8_t flag, uint32_t crc32, uint32_t size)
{
    Q_UNUSED(flag)
    Q_UNUSED(size)
    Q_UNUSED(crc32)
}

int QunpUCXX22::deal_with_unp(uint8_t *data, uint32_t len, unp_comnct_t type)
{
    Q_UNUSED(type)
    unp_state_t ret = UNP_SUCCESS;
    uint8_t pkt_type;
    uint8_t pkt_begin_octet;
    uint8_t pkt_end_octet;
    uint8_t identification[UNP_DEVNAME_LEN + 1] = {0};
    uint8_t clen[2];
    uint8_t *pdata = nullptr;
    uint16_t datasize = 0;
    uint16_t pkt_size = 0;

    memcpy(clen, data + 2, 2);

//    g_comnct_type   = type;
    pkt_begin_octet = data[0];
    pkt_end_octet   = data[len - 1];
    pkt_type        = data[1];
    pkt_size        = *(uint16_t *)clen;
    memcpy(identification, data + 4, UNP_DEVNAME_LEN);

    //pro

    //else
    if(pkt_begin_octet == UNP_FRAME_FLAG && pkt_end_octet == UNP_FRAME_FLAG) {
        if(len == pkt_size && len < UNP_MAX_PKTSIZE) {
            pdata    = data + 4 + UNP_DEVNAME_LEN;
            datasize = pkt_size - UNP_DEVNAME_LEN - 5;

            switch(pkt_type) {
                case INPUT_PASSWD_PKT:
                    deal_passwd_input(pdata, datasize);
                    break;
                case REBOOT_DEVICE_PKT:
                    deal_reboot();
                    break;
                case UPGRADE_DEVICE_PKT:
                    deal_upgrade(pdata, datasize);
                    break;
                case READ_PARAM_PKT:
                    deal_read_param(pdata, datasize);
                    break;
                case WRITE_PARAM_PKT:
                    deal_write_param(pdata, datasize);
                    break;
                case CONNECT_DEVICE_PKT :
                    deal_connect_dev(pdata, datasize);
                    break;
                case RESET_DEVICE_PKT :
                    deal_reset_dev(pdata, datasize);
                    break;
                case INPUT_PASSWD_ACK_PKT :
                    deal_passwd_input_ack(pdata, datasize);
                    break;
                case REBOOT_DEVICE_ACK_PKT :
                    deal_reboot_ack();
                    break;
                case UPGRADE_DEVICE_ACK_PKT :
                    deal_upgrade_ack(pdata, datasize);
                    break;
                case READ_PARAM_ACK_PKT :
                    deal_read_param_ack(pdata, datasize);
                    break;
                case WRITE_PARAM_ACK_PKT :
                    deal_write_param_ack(pdata, datasize);
                    break;
                case CONNECT_DEVICE_ACK_PKT :
                    deal_connect_dev_ack(pdata, datasize);
                    break;
                case RESET_DEVICE_ACK_PKT :
                    deal_reset_dev_ack(pdata, datasize);
                    break;
                case DEVICE_DTU_REPORT_PKT :
                    deal_dtu_status(pdata,datasize);
                    break;
#ifdef SUPPORT_UPGRADE_UBOOT
                case UPGRADE_UBOOT_PKT :
                    deal_upgrade_uboot(pdata, datasize);
                    break;
                case UPGRADE_UBOOT_ACK_PKT :
                    deal_upgrade_uboot_ack(pdata, datasize);
                    break;
#endif
                case DEVICE_RELOAD_CONFIG_ACK_PKT:
                    deal_lorawan_reload_ack(pdata, datasize);
                    break;
                default:
                    ret = UNP_TYPE_ERROR;
                    break;
            }
        } else {
            ret = UNP_LEN_ERROR;
        }
    } else {
        ret = UNP_FLAG_ERROR;
    }
    return ret;
}

/**
 * 串口初始化
 * @brief QunpUCXX22::initSerialPort
 * @param s
 * @return
 */
bool QunpUCXX22::initSerialPort(SerialInfo s)
{

    m_port->setPortName(s.portName);
    m_port->setBaudRate(s.baudrate);
    m_port->setDataBits(s.databit);
    m_port->setParity(s.paritybit);
    m_port->setStopBits(s.stopbit);

    qDebug()<<m_port->isOpen()<<s.portName<<m_port->portName();
    if(m_port->isOpen()){
        m_port->close();
    }
    if(m_port->open(QIODevice::ReadWrite)){
        return true;
    }else{
        qDebug()<<m_port->errorString()<<m_port->error();
    }
    return false;
}
void QunpUCXX22::read_serialport_data()
{
    if(m_port->isOpen() && m_ackFlag){
        m_port->waitForReadyRead(serialMaxTimeout);
        QByteArray array = m_port->readAll();

        unsigned char *data1 ;
        data1 = (unsigned char*)array.data();
        for(int i=0; i<array.size(); i++){
            printf("%02x",data1[i]);
        }
        printf("  reLen=%d \n",array.size());

        deal_with_unp(reinterpret_cast<uint8_t *>(array.data()),static_cast<uint32_t>(array.size()),COMNCT_UART);

    }
}
/**
 * 主动关闭串口
 * @brief QunpUCXX22::close_serialport
 */
void QunpUCXX22::close_serialport()
{
    if(m_port->isOpen()){
        m_port->close();
    }
}

bool QunpUCXX22::reopen_serialport()
{
    if(m_port->isOpen()){
        return true;
    }
    qDebug()<<"reopen serial port";
    return m_port->open(QIODevice::ReadWrite);
}

void QunpUCXX22::set_comnct_type(unp_comnct_t g_comnct_type_tmp)
{
    g_comnct_type = g_comnct_type_tmp;
}

int QunpUCXX22::unp_send_passwd(uint8_t *passwd, uint16_t len)
{
    uint8_t pkt[64] = {0};
    uint16_t pktsize = 0;
    m_ackFlag = true;

    pktsize = generate_pkt(passwd, len, pkt, INPUT_PASSWD_PKT);

    memset(&g_unp_ack, 0, sizeof(g_unp_ack));
    unp_send_pkt(pkt, pktsize);

    return (wait_for_ack());
}

unp_state_t QunpUCXX22::unp_get_version(uint8_t *version)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[32] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_UNP_VERSION;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        *version = out[0];
    }

    return ret;
}


int QunpUCXX22::unp_get_product_name(uint8_t *name)
{
    unp_state_t ret;
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t out[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_UNXX_PRODUCTID;

    ret = send_read_param_request(out, buf, offset);

#if 01
    if(ret == UNP_SUCCESS) {
        snprintf((char *)name, UNP_PRODUCT_NAME_LEN, "UC%s", out);
    }
    m_product = QString::asprintf("UC%s",out);

#else
    if(ret == UNP_SUCCESS) {
        snprintf((char *)name, UNP_PRODUCT_NAME_LEN, "UC511", out);
    }
    m_product.asprintf("UC511",out);
#endif
    return ret;
}

int QunpUCXX22::unp_get_product_pn(uint8_t *pn)
{
    unp_state_t ret;
    uint8_t buf[32] = {0};
    uint8_t out[32] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_UNXX_PN;

    ret = send_read_param_request(out, buf, offset);
#if 01
    if(ret == UNP_SUCCESS) {
        snprintf((char *)pn, UNP_PN_TOTAL_LEN, "%s", out);
    }
#else
    if(ret == UNP_SUCCESS) {
        snprintf((char *)pn, UNP_PN_TOTAL_LEN, "", out);
    }
#endif
    m_pn = QString::asprintf("%s",pn);
    qDebug("pn--- %s\n",pn);
    return ret;
}

unp_state_t QunpUCXX22::unp_set_passwd(uint8_t *old_passwd, uint8_t *new_passwd)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_DEVICE_PASSWD;

    memcpy(buf + offset, old_passwd, UNP_PASSWD_LEN);
    offset += UNP_PASSWD_LEN;

    memcpy(buf + offset, new_passwd, UNP_PASSWD_LEN);
    offset += UNP_PASSWD_LEN;

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_product_hwver(uint8_t *hwver)
{
    unp_state_t ret;
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_UNXX_HWVER;

    ret = send_read_param_request(hwver, buf, offset);

    return ret;
}

unp_state_t QunpUCXX22::unp_get_product_swver(uint8_t *swver)
{
    unp_state_t ret;
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_UNXX_SWVER;

    ret = send_read_param_request(swver, buf, offset);

//    m_swver.sprintf("%c%c.%c%c",swver[0],swver[1],swver[2],swver[3]);

//    qDebug()<<"000000000 "<<m_swver;
    return ret;
}
unp_state_t QunpUCXX22::unp_get_product_sn(uint8_t *sn)
{
    unp_state_t ret;

    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_UNXX_SN;

    ret = send_read_param_request(sn, buf, offset);

    return ret;
}

unp_state_t QunpUCXX22::unp_get_oem(uint8_t *oem)
{
    unp_state_t ret;

    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_UNXX_OEM;

    ret = send_read_param_request(oem, buf, offset);

    return ret;
}

unp_state_t QunpUCXX22::unp_get_product_real_pn(uint8_t *pn)
{
    unp_state_t ret;
    uint8_t buf[32] = {0};
    uint8_t out[32] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_UNXX_REAL_PN;

    ret = send_read_param_request(out, buf, offset);
#if 01
    if(ret == UNP_SUCCESS) {
        snprintf((char *)pn, UNP_PN_TOTAL_LEN, "%s", out);
    }
#else
    if(ret == UNP_SUCCESS) {
        snprintf((char *)pn, UNP_PN_TOTAL_LEN, "TWL-868", out);
    }
#endif

    qDebug("pn3--- %s\n",pn);
    return ret;
}

unp_state_t QunpUCXX22::unp_get_lora_status(uint32_t dataoffset, uint32_t datasize, uint8_t *out)
{
    unp_state_t ret;

//    uint8_t out[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 8;

    uint8_t pkt[UNP_MAX_PKTSIZE] = {0};
    uint16_t pktsize = 8;

    pkt[0] = UNP_FRAME_FLAG;
    pkt[1] = READ_PARAM_PKT;
    pkt[4] = 0x21;
    pkt[5] = dataoffset;
    pkt[6] = datasize;
    pkt[7] = UNP_FRAME_FLAG;
    *(uint16_t *)(pkt + 2) = offset;

    memset(&g_unp_ack, 0, sizeof(g_unp_ack));

    unp_send_pkt(pkt, pktsize);

    if(wait_for_ack() == UNP_SUCCESS) {
        memcpy(out, g_unp_ack.params,g_unp_ack.params_len );
        return UNP_SUCCESS;
    } else {
        return UNP_FAIL;
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_get_lora(uint32_t dataoffset, uint32_t datasize, uint8_t *out)
{
    uint8_t offset = 8;
    uint8_t pkt[UNP_MAX_PKTSIZE] = {0};
    uint16_t pktsize = 8;

    pkt[0] = UNP_FRAME_FLAG;
    pkt[1] = READ_PARAM_PKT;
    pkt[4] = PARAM_LORA;
    pkt[5] = dataoffset;
    pkt[6] = datasize;
    pkt[7] = UNP_FRAME_FLAG;
    *(uint16_t *)(pkt + 2) = offset;

    memset(&g_unp_ack, 0, sizeof(g_unp_ack));

    unp_send_pkt(pkt, pktsize);

    if(wait_for_ack() == UNP_SUCCESS) {
        memcpy(out, g_unp_ack.params,g_unp_ack.params_len );
        return UNP_SUCCESS;
    }else{
        return UNP_FAIL;
    }
}

unp_state_t QunpUCXX22::unp_set_lora(uint8_t value, uint8_t valueoffset)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint32_t offset = 0;

    buf[offset++] = PARAM_LORA;
    buf[offset++] = valueoffset;
    buf[offset++] = 1;
    buf[offset++] = value;
//    memcpy(buf + offset, value, datasize);


    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_set_lora(uint8_t *value, uint8_t valueoffset, uint16_t datasize)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint32_t offset = 0;

    buf[offset++] = PARAM_LORA;
    buf[offset++] = valueoffset;
    buf[offset++] = datasize;
    memcpy(buf + offset, value, datasize);
    offset += datasize;

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_set_lora(uint32_t value, uint8_t valueoffset, uint16_t datasize)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint32_t offset = 0;

    buf[offset++] = PARAM_LORA;
    buf[offset++] = valueoffset;
    buf[offset++] = datasize;
    *(uint32_t *)(buf + offset) = value;
    offset += 4;

    return (send_write_param_request(buf, offset));

}


unp_state_t QunpUCXX22::unp_get_device_status(device_status_t *status)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[256] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_DEVICE_STATUS;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        memcpy(status, out, sizeof(device_status_t));
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_get_device_time(uint32_t *timestamp, int16_t *timezone)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[32] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_DEVICE_TIME;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        offset       = 0;

        *timestamp   = *(uint32_t *)(out + offset);
        offset += 4;

        *timezone    = *(int16_t *)(out + offset);
        offset += 2;
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_get_sensor_data(sensor_status_em *temphumi)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[256] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_HT_VALUE;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        memcpy(temphumi, out, sizeof(sensor_status_em));
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_collect_cycle(uint32_t cycle)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_COLLECT_PERIOD;

    *(uint32_t *)(buf + offset) = cycle;
    offset += sizeof(uint32_t);

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_collect_cycle(uint32_t *cycle)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[32] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_COLLECT_PERIOD;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        memcpy(cycle, out, sizeof(uint32_t));
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_get_cloud_cycle(uint32_t *cycle)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[32] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_CLOUD_REPORT_PERIOD;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        memcpy(cycle, out, sizeof(uint32_t));
    }
    return ret;
}

unp_state_t QunpUCXX22::unp_set_cloud_cycle(uint32_t cycle)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_CLOUD_REPORT_PERIOD;
    *(uint32_t *)(buf + offset) = cycle;
    offset += sizeof(uint32_t);

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_sensor_cfg(user_config_t *sensors_cfg)
{
    unp_state_t ret;
    uint8_t buf[256] = {0}, out[256] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_USER_CONFIG;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        memcpy(sensors_cfg, out, sizeof(user_config_t));
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_sensor_cfg(user_config_t *sensors_cfg)
{
    uint8_t buf[256] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_USER_CONFIG;

    memcpy(buf + offset, sensors_cfg, sizeof(user_config_t));
    offset += sizeof(user_config_t);

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_abnormal_set(abnormal_check_set_t * abnormal, abnormal_check_patch_set_t *abnormal_patch)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[256] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_ABNORMAL_SET;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        offset = 0;

        abnormal->enable = out[offset++];

        abnormal->range = *(uint16_t *)(out + offset);
        offset += sizeof(uint16_t);

        abnormal->percentage = *(uint8_t *)(out + offset);
        offset += sizeof(uint8_t);

        abnormal_patch->percentage = *(uint8_t *)(out + offset);
        offset += sizeof(uint8_t);

        abnormal_patch->retry_count = *(uint8_t *)(out + offset);
        offset += sizeof(uint8_t);

        abnormal_patch->retry_interval = *(uint8_t *)(out + offset);
        offset += sizeof(uint8_t);

        qDebug("%d %d %d  %d",abnormal->percentage,abnormal_patch->percentage, abnormal_patch->percentage <<8, abnormal->percentage | (abnormal_patch->percentage <<8));
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_abnormal_set(abnormal_check_set_t * abnormal, abnormal_check_patch_set_t *abnormal_patch)
{
    uint8_t buf[256] = {0};
    uint8_t offset = 0;
    uint8_t *pdata;

    buf[offset++] = PARAM_ABNORMAL_SET;

    buf[offset++] = abnormal->enable;

    pdata = (uint8_t *)&abnormal->range;
    buf[offset++] = pdata[0];
    buf[offset++] = pdata[1];

    buf[offset++] = abnormal->percentage;
    buf[offset++] = abnormal_patch->percentage;
    buf[offset++] = abnormal_patch->retry_count;
    buf[offset++] = abnormal_patch->retry_interval;

    qDebug("%d %d %d",abnormal->percentage,abnormal_patch->percentage,1<<2);

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_alarm(uint8_t num, alarm_rules_t *alarmconfig)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[256] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_HT_ALARM;
    buf[offset++] = num;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        offset = 0;

        alarmconfig->mode = (alarm_mode_t)out[offset++];

        alarmconfig->max_value= *(uint16_t *)(out + offset);
        offset += sizeof(uint16_t);

        alarmconfig->min_value = *(uint16_t *)(out + offset);
        offset += sizeof(uint16_t);

        alarmconfig->continue_time = *(uint16_t *)(out + offset);
        offset += sizeof(uint16_t);

        alarmconfig->lock_time = *(uint16_t *)(out + offset);
        offset += sizeof(uint16_t);

        alarmconfig->enable = (alarm_mode_t)out[offset++];

        alarmconfig->max_value2 = *(uint16_t *)(out + offset);
        offset += sizeof(uint16_t);

        alarmconfig->min_value2 = *(uint16_t *)(out + offset);
        offset += sizeof(uint16_t);

    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_alarm(uint8_t num, alarm_rules_t *alarmconfig)
{
    uint8_t buf[256] = {0};
    uint8_t offset = 0;
    uint8_t *pdata;
    printf("set uc11t1 alarm :::::: %d\n",alarmconfig->enable);
    buf[offset++] = PARAM_HT_ALARM;
    buf[offset++] = num;

    buf[offset++] = alarmconfig->mode;

    pdata = (uint8_t *)&alarmconfig->max_value;
    buf[offset++] = pdata[0];
    buf[offset++] = pdata[1];

    pdata = (uint8_t *)&alarmconfig->min_value;
    buf[offset++] = pdata[0];
    buf[offset++] = pdata[1];

    pdata = (uint8_t *)&alarmconfig->continue_time;
    buf[offset++] = pdata[0];
    buf[offset++] = pdata[1];

    pdata = (uint8_t *)&alarmconfig->lock_time;
    buf[offset++] = pdata[0];
    buf[offset++] = pdata[1];

    buf[offset++] = alarmconfig->enable;

    pdata = (uint8_t *)&alarmconfig->max_value2;
    buf[offset++] = pdata[0];
    buf[offset++] = pdata[1];

    pdata = (uint8_t *)&alarmconfig->min_value2;
    buf[offset++] = pdata[0];
    buf[offset++] = pdata[1];


    return (send_write_param_request(buf, offset));
}


unp_state_t QunpUCXX22::unp_send_upgrade_request(void)
{
    unp_state_t ret;
    uint8_t pkt[64] = {0};
    uint16_t pktsize = 0;

    pktsize = generate_pkt((uint8_t *)UNP_UPGRADE_REQUEST, strlen((const char *)UNP_UPGRADE_REQUEST), pkt, UPGRADE_DEVICE_PKT);
    memset(&g_unp_ack, 0, sizeof(g_unp_ack));
    unp_send_pkt(pkt, pktsize);

    ret = wait_for_ack();
//    unp_delay(5000);
    return ret;
}

unp_state_t QunpUCXX22::unp_connect_device(void)
{
    uint8_t pkt[UNP_MAX_PKTSIZE] = {0};
    uint16_t pktsize = 0;

    onlyUcp = false;
    pktsize = generate_pkt(nullptr, 0, pkt, CONNECT_DEVICE_PKT );

    memset(&g_unp_ack, 0, sizeof(g_unp_ack));

    unp_send_pkt(pkt, pktsize);

    if(wait_for_ack() == UNP_SUCCESS) {
        return UNP_SUCCESS;
    } else {
        return UNP_FAIL;
    }
}

/**
 * @brief QunpUCXX22::unp_upgrade_check
 * @param crc32
 * @param productid
 * @param hwver
 * @param swver
 * @param pn
 * @param imageVer  镜像打包方式的版本，0：原始方式； 1：带PN
 * @return
 */
unp_state_t QunpUCXX22::unp_upgrade_check(uint32_t crc32, uint8_t *productid, uint8_t *hwver, uint8_t *swver, uint8_t *pn,int imageVer)
{
//    QThread::msleep(3000);
//    qDebug("***************crc32=0x%x productid=%s  hwver=%s swver=%s  pn=%s  imagever=%d\n",&crc32,productid,hwver,swver, pn,imageVer);

    uint8_t pkt[64] = {0};
    uint8_t buf[64] = {0};
    uint16_t pktsize = 0, offset = 0;

    memcpy(buf + offset, &crc32, sizeof(crc32));
    offset += sizeof(crc32);


    memcpy(buf + offset, productid, UNP_PRODUCT_ID_LEN_EM);
    offset += UNP_PRODUCT_ID_LEN_EM;


    memcpy(buf + offset, hwver, UNP_HWVER_LEN);
    offset += UNP_HWVER_LEN;

    memcpy(buf + offset, swver, UNP_SWVER_LEN);
    offset += UNP_SWVER_LEN;

    if(imageVer){
        memcpy(buf + offset, pn, UNP_PN_LEN_EM *4);
        offset += UNP_PN_LEN_EM *4;
    }

    pktsize = generate_pkt(buf, offset, pkt, UPGRADE_DEVICE_PKT);

    memset(&g_unp_ack, 0, sizeof(g_unp_ack));

    unp_send_pkt(pkt, pktsize);

    return (wait_for_ack());
}

unp_state_t QunpUCXX22::unp_send_upgrade_image(uint8_t *data, uint32_t datasize)
{
    QString iniPath = QApplication::applicationDirPath()+"/config.ini";
    QSettings settings(iniPath, QSettings::IniFormat);
    settings.beginGroup("SerialPortInfo");
    int m_delay = settings.value("upgradeWait").toInt();
    settings.endGroup();
    unp_state_t ret = UNP_SUCCESS;
    uint32_t upgrade_per_pkt = UNP_UPGRADE_CHUNKSIZE;
    uint32_t delay;
    if(m_delay == 0){
#ifdef ODM_LHR_AZURE
        delay = 500;
#else
        delay = 400;
#endif

    }else{
        delay = m_delay;
    }

    uint8_t pkt[UNP_UPGRADE_CHUNKSIZE + 32] = {0};
    uint32_t pos = 0;
    uint16_t pktsize = 0;
    uint16_t realsize;
    uint32_t allPkt;
    uint8_t count=0;
    allPkt = 0;
    qDebug()<<"upgrade chunksize:"<<upgrade_per_pkt<<delay<<"product:"<<m_product;
    printf( "datasize : %d\n",datasize);
    while(datasize) {
        realsize = ((datasize > upgrade_per_pkt) ? upgrade_per_pkt : datasize);
        pktsize  = generate_pkt(data + pos, realsize, pkt, UPGRADE_DEVICE_PKT);
        unp_send_pkt(pkt, pktsize);

//        crc32= my_ether_crc32(0, pkt, pktsize);
//        printf("crc32=%x  pktsize=%d\n",crc32,pktsize);

        pos += realsize;
        datasize -= realsize;
        allPkt += realsize;
        emit getImageSize(allPkt);
        unp_delay(delay);

        count++;
        if(count >= 30) {
            count = 0;
            ret = unp_connect_device();
            if(ret != UNP_SUCCESS) {
                ret = unp_connect_device();
                if(ret != UNP_SUCCESS) {
                    ret = unp_connect_device();
                    if(ret != UNP_SUCCESS) {
                        return ret;
                    }
                }
            }
        }
    }
    return ret;
}

unp_state_t QunpUCXX22::unp_upgrade_complete(void)
{
    uint8_t pkt[UNP_MAX_PKTSIZE] = {0};
    uint16_t pktsize = 0;
//    printf("====== %d\n",strlen(UNP_UPGRADE_COMPLETE));
    pktsize = generate_pkt((uint8_t *)UNP_UPGRADE_COMPLETE, strlen(UNP_UPGRADE_COMPLETE), pkt, UPGRADE_DEVICE_PKT);

    memset(&g_unp_ack, 0, sizeof(g_unp_ack));

    unp_send_pkt(pkt, pktsize);

    return (wait_for_ack());
}

unp_state_t QunpUCXX22::unp_reset_device()
{
    uint8_t pkt[UNP_MAX_PKTSIZE] = {0};
    uint16_t pktsize = 0;

    pktsize = generate_pkt(nullptr, 0, pkt,RESET_DEVICE_PKT );

    memset(&g_unp_ack, 0, sizeof(g_unp_ack));

    unp_send_pkt(pkt, pktsize);

    if(wait_for_ack() == UNP_SUCCESS) {
        return UNP_SUCCESS;
    } else {
        return UNP_FAIL;
    }
}

unp_state_t QunpUCXX22::unp_send_reboot_request(void)
{
    qInfo()<<"#################"<<"reboot ing";
    uint8_t pkt[64] = {0};
    uint16_t pktsize = 0;

    pktsize = generate_pkt(nullptr, 0, pkt, REBOOT_DEVICE_PKT);
    memset(&g_unp_ack, 0, sizeof(g_unp_ack));
    unp_send_pkt(pkt, pktsize);

//    return (wait_for_ack()); //重启时设备有时不会回包就重启，自动检测串口的线程可能会因为wait_for_ack的循环来不及关闭串口,接口外要强行非阻塞等待
    return UNP_SUCCESS;
}

unp_state_t QunpUCXX22::unp_set_lora_reload_config()
{
    qInfo()<<"#################"<<"reload lora";
    uint8_t pkt[64] = {0};
    uint16_t pktsize = 0;

    pktsize = generate_pkt(nullptr, 0, pkt, DEVICE_RELOAD_CONFIG);

    memset(&g_unp_ack, 0, sizeof(g_unp_ack));

    unp_send_pkt(pkt, pktsize);

//    return (wait_for_ack()); //重启时设备有时不会回包就重启，自动检测串口的线程可能会因为wait_for_ack的循环来不及关闭串口,接口外要强行非阻塞等待
    return UNP_SUCCESS;
}

unp_state_t QunpUCXX22::unp_set_product_pn(uint8_t *pn)
{
     uint8_t buf[32] = {0};
     uint8_t offset = 0;
     uint8_t len;

     buf[offset++] = PARAM_UNXX_PN;
     len = snprintf((char *)buf + offset, sizeof(buf) - offset, "%s", pn);
     offset += len;

     return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_uc11t1_data(uc11t1_temphumi_t *temphumi)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[256] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_HT_VALUE;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        memcpy(temphumi, out, sizeof(uc11t1_temphumi_t));
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_enable_auto_report(uint8_t state)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;
    uint16_t threshold;

    if(state) {
        threshold = 2;
    } else {
        threshold = 0;
    }

    buf[offset++] = PARAM_AUTO_REPORT;
    *(uint16_t *)(buf + offset) = threshold;
    offset += sizeof(uint16_t);

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_enable_auto_report(uint8_t *state)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[32] = {0};
    uint8_t offset = 0;
    uint16_t threshold = 0;

    buf[offset++] = PARAM_AUTO_REPORT;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        threshold = *(uint16_t *)out;
    }

    if(threshold) {
        *state = 1;
    } else {
        *state = 0;
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_get_uc11t1_alarm(uint8_t num, alarm_rules_t *alarmconfig)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[256] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_HT_ALARM;
    buf[offset++] = num;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        offset = 0;

        alarmconfig->mode = (alarm_mode_t)out[offset++];

        alarmconfig->min_value = *(uint16_t *)(out + offset);
        offset += sizeof(uint16_t);

        alarmconfig->max_value = *(uint16_t *)(out + offset);
        offset += sizeof(uint16_t);

        alarmconfig->lock_time= *(uint16_t *)(out + offset);
        offset += sizeof(uint16_t);

        alarmconfig->continue_time = *(uint16_t *)(out + offset);
        offset += sizeof(uint16_t);

        alarmconfig->enable = (alarm_mode_t)out[offset++];

        alarmconfig->max_value2 = *(uint16_t *)(out + offset);
        offset += sizeof(uint16_t);

        alarmconfig->min_value2 = *(uint16_t *)(out + offset);
        offset += sizeof(uint16_t);

    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_uc11t1_alarm(uint8_t num, alarm_rules_t *alarmconfig)
{
    uint8_t buf[256] = {0};
    uint8_t offset = 0;
    uint8_t *pdata;
    printf("set uc11t1 alarm :::::: %d\n",alarmconfig->enable);
    buf[offset++] = PARAM_HT_ALARM;
    buf[offset++] = num;

    buf[offset++] = alarmconfig->mode;

    pdata = (uint8_t *)&alarmconfig->min_value;
    buf[offset++] = pdata[0];
    buf[offset++] = pdata[1];

    pdata = (uint8_t *)&alarmconfig->max_value;
    buf[offset++] = pdata[0];
    buf[offset++] = pdata[1];

    pdata = (uint8_t *)&alarmconfig->lock_time;
    buf[offset++] = pdata[0];
    buf[offset++] = pdata[1];

    pdata = (uint8_t *)&alarmconfig->continue_time;
    buf[offset++] = pdata[0];
    buf[offset++] = pdata[1];



    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_set_temp_humi_compensate(uint8_t temp_enable, int16_t temp_value, uint8_t humi_enable, int16_t humi_value)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_TEMP_COMPENSATE;

    buf[offset++] = temp_enable;
    *(int16_t *)(buf + offset) = temp_value;
    offset += 2;

    buf[offset++] = humi_enable;
    *(int16_t *)(buf + offset) = humi_value;
    offset += 2;

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_temp_humi_compensate(uint8_t *temp_enable, int16_t *temp_value, uint8_t *humi_enable, int16_t *humi_value)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[64] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_TEMP_COMPENSATE;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        *temp_enable = out[0];
        *temp_value  = *(int16_t *)&out[1];

        *humi_enable = out[3];
        *humi_value  = *(int16_t *)&out[4];
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_get_mobile_state(unp_mobile_state_t *state)
{
    unp_state_t ret;
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t out[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_GSM_STATUS;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        *state = (unp_mobile_state_t)out[0];
    }
    return ret;
}

unp_state_t QunpUCXX22::unp_get_mobile_signal(uint8_t *signal)
{
    unp_state_t ret;
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t out[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_GSM_SIGNAL;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        *signal = (unp_mobile_state_t)out[0];
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_get_inputio_status(uint8_t gpionum, uint8_t *value)
{
    unp_state_t ret;
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t out[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_INPUT_IO_STATUS;
    buf[offset++] = gpionum;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        *value = out[0];
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_get_outputio_status(uint8_t gpionum, uint8_t *value)
{
    unp_state_t ret;
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t out[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_OUTPUT_IO_STATUS;
    buf[offset++] = gpionum;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        *value = out[0];
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_current_time(unxxtime_t *cur)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_DEVICE_TIME;
    buf[offset++] = cur->sec;
    buf[offset++] = cur->min;
    buf[offset++] = cur->hour;
    buf[offset++] = cur->date;
    buf[offset++] = cur->month;
    *(uint16_t *)(buf + offset) = cur->year;
    offset += 2;
    buf[offset++] = cur->weekday;

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_current_time(unxxtime_t *cur)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[32] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_DEVICE_TIME;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        offset       = 0;
        cur->sec     = out[offset++];
        cur->min     = out[offset++];
        cur->hour    = out[offset++];
        cur->date    = out[offset++];
        cur->month   = out[offset++];
        cur->year    = *(uint16_t *)(out + offset);
        offset      += 2;
        cur->weekday = out[offset++];
    }

    return ret;
}


unp_state_t QunpUCXX22::unp_set_app_mode(app_mode_t mode)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_APP_MODE;
    buf[offset++] = mode;

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_app_mode(app_mode_t *mode)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[64] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_APP_MODE;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        *mode = (app_mode_t)out[0];
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_mqtt_keepalive(uint32_t keepalive)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_MQTT_KEEPALIVE;


    *(uint32_t *)(buf + offset) = keepalive;
    offset += sizeof(keepalive);

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_mqtt_keepalive(uint32_t *keepalive)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[32] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_MQTT_KEEPALIVE;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        offset   = 0;
        *keepalive = *(uint32_t *)(out + offset);
        offset += sizeof(uint32_t);
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_get_mobile_apn(uint8_t *apn)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[32] = {0};
    uint8_t offset = 0;
    buf[offset++] = PARAM_APN_SET;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        memcpy(apn, out, UNP_APN_MAX_LENGTH);
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_get_mobile_apn(uint8_t *apn, uint8_t *username, uint8_t *password)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[128] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_APN_SET;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        memcpy(apn     , out, UNP_APN_MAX_LENGTH);
        memcpy(username, out + UNP_APN_MAX_LENGTH, UNP_APN_USERNAME_LEN);
        memcpy(password, out + UNP_APN_MAX_LENGTH + UNP_APN_USERNAME_LEN, UNP_APN_PASSWORD_LEN);
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_mobile_apn(uint8_t *apn, uint8_t *username, uint8_t *password)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_APN_SET;


    memcpy(buf + offset, apn, UNP_APN_MAX_LENGTH);
    offset += UNP_APN_MAX_LENGTH;

    memcpy(buf + offset, username, UNP_APN_USERNAME_LEN);
    offset += UNP_APN_USERNAME_LEN;

    memcpy(buf + offset, password, UNP_APN_PASSWORD_LEN);
    offset += UNP_APN_PASSWORD_LEN;

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_set_update_rootcrt(uint8_t *data, uint16_t datasize)
{
    uint8_t num;
    uint8_t loop;
    uint16_t pos;
    uint16_t left;
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;
    unp_state_t ret;

    loop = datasize/UNP_ONE_TIME_SIZE;
    left = datasize%UNP_ONE_TIME_SIZE;

    buf[offset++] = PARAM_ROOT_CRT;
    pos = offset;

    for(num = 0; num < loop; num++, offset = pos) {
        buf[offset++] = num;
        memcpy(buf + offset, data + num*UNP_ONE_TIME_SIZE, UNP_ONE_TIME_SIZE);
        offset += UNP_ONE_TIME_SIZE;
        ret = send_write_param_request(buf, offset);
        if(ret != UNP_SUCCESS) {
            return ret;
        }
    }

    offset = pos;
    if(left) {
        buf[offset++] = num;
        memcpy(buf + offset, data + num*UNP_ONE_TIME_SIZE, left);
        offset += left;
        ret = send_write_param_request(buf, offset);
        if(ret != UNP_SUCCESS) {
            return ret;
        }
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_get_rootcrt(uint8_t *data, uint16_t datasize)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[256] = {0};
    uint8_t num = 0;
    uint16_t offset = 0;

    buf[0] = PARAM_ROOT_CRT;

    for(num = 0; num*UNP_ONE_TIME_SIZE < datasize; num++) {
        buf[1] = num;
        ret = send_read_param_request(out, buf, 2);
        if(ret == UNP_SUCCESS) {
            memcpy(data + offset, out, g_unp_ack.params_len);
            offset += g_unp_ack.params_len;
            if(strlen((const char *)out) != g_unp_ack.params_len) {
                break;
            }
        }	else {
            break;
        }
    }

    if(offset) {
        ret = UNP_SUCCESS;
    }
    return ret;
}

unp_state_t QunpUCXX22::unp_set_update_devcrt(uint8_t *data, uint16_t datasize)
{
    uint8_t num;
    uint8_t loop;
    uint16_t pos;
    uint16_t left;
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;
    unp_state_t ret;

    loop = datasize/UNP_ONE_TIME_SIZE;
    left = datasize%UNP_ONE_TIME_SIZE;

    buf[offset++] = PARAM_DEV_CRT;
    pos = offset;

    for(num = 0; num < loop; num++, offset = pos) {
        buf[offset++] = num;
        memcpy(buf + offset, data + num*UNP_ONE_TIME_SIZE, UNP_ONE_TIME_SIZE);
        offset += UNP_ONE_TIME_SIZE;
        ret = send_write_param_request(buf, offset);
        if(ret != UNP_SUCCESS) {
            return ret;
        }
    }

    offset = pos;
    if(left) {
        buf[offset++] = num;
        memcpy(buf + offset, data + num*UNP_ONE_TIME_SIZE, left);
        offset += left;
        ret = send_write_param_request(buf, offset);
        if(ret != UNP_SUCCESS) {
            return ret;
        }
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_get_devcrt(uint8_t *data, uint16_t datasize)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[256] = {0};
    uint8_t num = 0;
    uint16_t offset = 0;

    buf[0] = PARAM_DEV_CRT;

    for(num = 0; num*UNP_ONE_TIME_SIZE < datasize; num++) {
        buf[1] = num;
        ret = send_read_param_request(out, buf, 2);
        if(ret == UNP_SUCCESS) {
            memcpy(data + offset, out, g_unp_ack.params_len);
            offset += g_unp_ack.params_len;
            if(strlen((const char *)out) != g_unp_ack.params_len) {
                break;
            }
        }	else {
            break;
        }
    }
    return ret;
}

unp_state_t QunpUCXX22::unp_set_update_prikey(uint8_t *data, uint16_t datasize)
{
    uint8_t num;
    uint8_t loop;
    uint16_t pos;
    uint16_t left;
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;
    unp_state_t ret;

    loop = datasize/UNP_ONE_TIME_SIZE;
    left = datasize%UNP_ONE_TIME_SIZE;

    buf[offset++] = PARAM_PRI_KEY;
    pos = offset;

    for(num = 0; num < loop; num++, offset = pos) {
        buf[offset++] = num;
        memcpy(buf + offset, data + num*UNP_ONE_TIME_SIZE, UNP_ONE_TIME_SIZE);
        offset += UNP_ONE_TIME_SIZE;
        ret = send_write_param_request(buf, offset);
        if(ret != UNP_SUCCESS) {
            return ret;
        }
    }

    offset = pos;
    if(left) {
        buf[offset++] = num;
        memcpy(buf + offset, data + num*UNP_ONE_TIME_SIZE, left);
        offset += left;
        ret = send_write_param_request(buf, offset);
        if(ret != UNP_SUCCESS) {
            return ret;
        }
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_get_prikey(uint8_t *data, uint16_t datasize)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[256] = {0};
    uint8_t num = 0;
    uint16_t offset = 0;

    buf[0] = PARAM_PRI_KEY;

    for(num = 0; num*UNP_ONE_TIME_SIZE < datasize; num++) {
        buf[1] = num;
        ret = send_read_param_request(out, buf, 2);
        if(ret == UNP_SUCCESS) {
            memcpy(data + offset, out, g_unp_ack.params_len);
            offset += g_unp_ack.params_len;
            if(strlen((const char *)out) != g_unp_ack.params_len) {
                break;
            }
        }	else {
            break;
        }
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_endpoint_name(uint8_t *name)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_AWS_NAME;
    memcpy(buf + offset, name, strlen((const char *)name));
    offset += strlen((const char *)name);

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_endpoint_name(uint8_t *name)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[256] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_AWS_NAME;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        memcpy(name, out, g_unp_ack.params_len);
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_endpoint_addr(uint8_t *addr)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_AWS_ADDR;
    memcpy(buf + offset, addr, strlen((const char *)addr));
    offset += strlen((const char *)addr);

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_endpoint_addr(uint8_t *addr)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_AWS_ADDR;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
//        printf("unp_get_endpoint_addr == %s \n",out);
        memcpy(addr, out, g_unp_ack.params_len);
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_get_device_desc(uint8_t *desc)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_DEV_DESC;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        memcpy(desc, out, UNP_DEVDESC_LEN);
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_device_desc(uint8_t *desc)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;
    uint8_t datasize = 0;

    buf[offset++] = PARAM_DEV_DESC;

    datasize = UNP_DEVDESC_LEN > strlen((char *)desc) ? strlen((char *)desc) : UNP_DEVDESC_LEN;
    memcpy(buf + offset, desc, datasize);

    offset += datasize;

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_set_tcpudp_config(app_tcpudp_t *tcpudp_set)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint16_t offset = 0;

    buf[offset++] = PARAM_TCPUDP_SET;

    memcpy(buf + offset, tcpudp_set, sizeof(app_tcpudp_t));

    offset += sizeof(app_tcpudp_t);

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_tcpudp_config(app_tcpudp_t *tcpudp_set)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[UNP_MAX_PKTSIZE] = {0};
    uint16_t offset = 0;

    buf[offset++] = PARAM_TCPUDP_SET;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        memcpy(tcpudp_set, out, sizeof(app_tcpudp_t));
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_mqtt_config(app_mqtt_t *mqtt_set)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint32_t offset = 0;

    buf[offset++] = PARAM_MQTT_SET;

    memcpy(buf + offset, mqtt_set, sizeof(app_mqtt_t));

    offset += sizeof(app_mqtt_t);
    qDebug()<<offset<<sizeof(app_mqtt_t);

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_mqtt_config(app_mqtt_t *mqtt_set)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_MQTT_SET;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        memcpy(mqtt_set, out, sizeof(app_mqtt_t));
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_onenet_config(unxx_onenet_setting_t *onenet_set)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_ONENET_CFG;

    memcpy(buf + offset, onenet_set, sizeof(unxx_onenet_setting_t));

    offset += sizeof(unxx_onenet_setting_t);

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_onenet_config(unxx_onenet_setting_t *onenet_get)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_ONENET_CFG;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        memcpy(onenet_get, out, sizeof(unxx_onenet_setting_t));
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_ali_cfg(unxx_ali_setting_t *ali_cfg)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] =  PARAM_ALI_CFG ;

    memcpy(buf + offset, ali_cfg, sizeof(unxx_ali_setting_t));

    offset += sizeof(unxx_ali_setting_t);

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_ali_cfg(unxx_ali_setting_t *ali_cfg)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] =  PARAM_ALI_CFG ;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        offset = 0;
//        memcpy(ali_cfg, out, sizeof(unxx_ali_setting_t));

        ali_cfg->qos =  *(Qos *)(out + offset);
        offset += sizeof(Qos);

        ali_cfg->keepalive =  *(uint16_t *)(out + offset);
        offset += sizeof(uint16_t);

        memcpy(ali_cfg->ali_clientID, out + offset, 32);
        offset += 32;

        memcpy(ali_cfg->ali_ProductKey, out + offset, 32);
        offset += 32;

        memcpy(ali_cfg->ali_DeviceSecret, out + offset, 64);
        offset += 64;
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_cellular_net_type(cellular_network_t value)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_MOBILE_NET;
    buf[offset++] = value;

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_cellular_net_type(cellular_network_t *value)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[64] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_MOBILE_NET;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        *value = (cellular_network_t)out[0];
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_cellular_sca(uint8_t *sca)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_MOBILE_SCA;

    memcpy(buf + offset, sca, strlen((const char *)sca));
    offset += strlen((const char *)sca);

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_cellular_sca(uint8_t *sca)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[64] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_MOBILE_SCA;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        memcpy(sca, out, UNP_SCA_MAX_LENGTH);
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_cellular_pin(uint8_t *pin)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_MOBILE_PIN;

    memcpy(buf + offset, pin, strlen((const char *)pin));
    offset += strlen((const char *)pin);

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_cellular_pin(uint8_t *pin)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[64] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_MOBILE_PIN;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        memcpy(pin, out, UNP_PIN_MAX_LENGTH);
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_sms_dcs(sms_dcs_t code)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_SMS_DCS;
    buf[offset++] = code;

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_sms_dcs(sms_dcs_t *code)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[64] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_SMS_DCS;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        *code = (sms_dcs_t)out[0];
    }

    return ret;
}
unp_state_t QunpUCXX22::unp_get_tcpudp_status(uint8_t *state)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[32] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_TCPUDP_STATUS;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        *state = out[0];
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_osh(uint8_t num, float osh)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_OSH;
    buf[offset++] = num;
    *(float *)(buf + offset) = osh;
    offset += sizeof(float);

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_osh(uint8_t num, float *osh)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[32] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_OSH;
    buf[offset++] = num;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        memcpy(osh, out, sizeof(float));
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_osl(uint8_t num, float osl)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_OSL;
    buf[offset++] = num;
    *(float *)(buf + offset) = osl;
    offset += sizeof(float);

    return (send_write_param_request(buf, offset));
}

unp_state_t QunpUCXX22::unp_get_osl(uint8_t num, float *osl)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[32] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_OSL;
    buf[offset++] = num;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        memcpy(osl, out, sizeof(float));
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_get_ai_value(uint8_t num, float *current, float *usrdata)
{
    unp_state_t ret;
    uint8_t buf[8] = {0}, out[32] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_AI_VALUE;
    buf[offset++] = num;

    ret = send_read_param_request(out, buf, offset);

    if(ret == UNP_SUCCESS) {
        offset   = 0;

        *current = *(float *)(out + offset);
        offset  += sizeof(float);

        *usrdata = *(float *)(out + offset);
        offset += sizeof(float);
    }

    return ret;
}
unp_state_t QunpUCXX22::unp_get_11xx_gpio_counter(uint8_t gpionum, uint8_t *mode, uint8_t *start, uint32_t *value)
{
    unp_state_t ret;
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t out[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_GPIO_COUNTER;
    buf[offset++] = gpionum;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        *mode  = out[0];
        *start = out[1];
        *value = *(uint32_t *)&out[2];
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_get_gpio_counter(uint8_t gpionum, uint32_t *value, uint8_t *start)
{
    unp_state_t ret;
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t out[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_GPIO_COUNTER;
    buf[offset++] = gpionum;

    ret = send_read_param_request(out, buf, offset);
    if(ret == UNP_SUCCESS) {
        *start = out[0];
        *value = *(uint32_t *)&out[1];
    }

    return ret;
}

unp_state_t QunpUCXX22::unp_set_gpio_counter(uint8_t gpionum, uint32_t value)
{
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_GPIO_COUNTER;
    buf[offset++] = gpionum;

    *(uint32_t *)(buf + offset) = value;
    offset += sizeof(uint32_t);

    return (send_write_param_request(buf, offset));
}
