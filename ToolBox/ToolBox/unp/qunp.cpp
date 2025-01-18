#include "qunp.h"

Qunp::Qunp(QObject *parent) : QObject(parent)
{

    m_port = new QSerialPort();

    serialMaxTimeout = UNP_MAX_TIMEOUT;

}

void Qunp::deal_reset_dev(uint8_t *data, uint16_t datasize)
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

void Qunp::deal_reset_dev_ack(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(data)
    Q_UNUSED(datasize)
    g_unp_ack.type = RESET_DEVICE_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.state = UNP_SUCCESS;
}

void Qunp::deal_dtu_status(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(data)
    Q_UNUSED(datasize)
}

void Qunp::deal_lorawan_reload_ack(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(data)
    Q_UNUSED(datasize)
    g_unp_ack.type = DEVICE_RELOAD_CONFIG_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.state = UNP_SUCCESS;
}

void Qunp::deal_connect_dev(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(datasize)
    Q_UNUSED(data)
    uint8_t pkt[32] = {0};
    uint16_t pktlen;

    //passwd_verify_success = 1;
    pktlen = generate_pkt(nullptr, 0, pkt, CONNECT_DEVICE_ACK_PKT);
    unp_send_pkt(pkt, pktlen);
}

void Qunp::deal_connect_dev_ack(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(data)
    Q_UNUSED(datasize)
    g_unp_ack.type = CONNECT_DEVICE_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.state = UNP_SUCCESS;
}

void Qunp::deal_reload_config_dev_ack(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(datasize)
    Q_UNUSED(data)
    g_unp_ack.type = DEVICE_RELOAD_CONFIG_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.state = UNP_SUCCESS;
}

void Qunp::deal_reload_config_dev(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(data)
    Q_UNUSED(datasize)
    g_unp_ack.type = DEVICE_RELOAD_CONFIG_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.state = UNP_SUCCESS;
}

void Qunp::deal_passwd_input(uint8_t *data, uint16_t datasize)
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

void Qunp::deal_passwd_input_ack(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(datasize)
    g_unp_ack.type = INPUT_PASSWD_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.state = (unp_state_t)data[0];
}

void Qunp::deal_reboot(void)
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

void Qunp::deal_reboot_ack(void)
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

void Qunp::deal_upgrade(uint8_t *buffer, uint16_t datasize)
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
            }
            break;
        default :
            break;
    }
}

void Qunp::deal_upgrade_ack(uint8_t *buffer, uint16_t datasize)
{
    Q_UNUSED(datasize)
    g_unp_ack.type = UPGRADE_DEVICE_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.state = (unp_state_t)buffer[0];
}

void Qunp::deal_read_param(uint8_t *data, uint16_t len)
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

void Qunp::deal_read_param_ack(uint8_t *data, uint16_t len)
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

void Qunp::deal_write_param(uint8_t *data, uint16_t len)
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

void Qunp::deal_write_param_ack(uint8_t *data, uint16_t len)
{
    Q_UNUSED(len)
    g_unp_ack.type = WRITE_PARAM_ACK_PKT;
    g_unp_ack.received = 1;
    g_unp_ack.state = (unp_state_t)data[0];
}

void Qunp::unp_delay(uint32_t ms)
{
#ifdef USE_IN_STM32
    HAL_Delay(ms);
#else
//    waitTime(ms);
    QThread::msleep(ms);
#endif
}


unp_state_t Qunp::wait_for_ack(void)
{
    if(g_comnct_type == COMNCT_NFC){
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

uint8_t Qunp::unp_verify(void)
{
    uint8_t ret = 1;

    if(g_comnct_type == COMNCT_UART) {
        if(!passwd_verify_success) {
            ret = 0;
        }
    }

    return ret;
}

uint16_t Qunp::generate_pkt(uint8_t *data, uint16_t datasize, uint8_t *pkt, unp_pack_t type)
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

uint8_t Qunp::unp_frame_split(uint8_t *data, uint16_t datasize, uint16_t *pos, uint16_t *len)
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

void Qunp::set_comnct_type(unp_comnct_t g_comnct_type_tmp)
{
    g_comnct_type = g_comnct_type_tmp;
}

void Qunp::unp_send_pkt(uint8_t *data, uint16_t pktsize)
{
    if(g_comnct_type == COMNCT_NFC)
    {
        deal_with_unp(data,pktsize,COMNCT_NFC);
        return;
    }

    if(m_port->isOpen() && m_ackFlag){
        printf("===========Write============ \n");
        for(int i=0; i<pktsize; i++){
            printf("%02x",data[i]);
        }
        printf("   len=%d \n",pktsize);
        m_port->write(reinterpret_cast<const char *>(data), pktsize);
        m_port->waitForBytesWritten(1000);

    }else{
        qDebug()<<"SerialPort CLOSED";
    }

}


uint16_t Qunp::read_device_params(uint8_t *params, uint8_t *data)
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
        qDebug()<<m_product;
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
            memcpy(data, (void*)&pStatus->uc11t1_status, sizeof(amem_status_t));
            datasize += sizeof(amem_status_t);

            break;
        }
        case PARAM_POWER_CTRL:
        {
            uint8_t data2[32];
            memcpy(data2, (void*)&pStatus->uc11t1_status, sizeof(amem_status_t));
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

            memcpy(data, pUserConfig_am, sizeof(user_config_t_am));
            datasize += sizeof(user_config_t_am);
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
            sensor_status_am sensor_data;
            sensor_data.opt1  = pStatus->data[0];
            sensor_data.opt2  = pStatus->data[1];
            sensor_data.opt3  = pStatus->data[2];
            sensor_data.opt4  = pStatus->data[3];
            sensor_data.opt5  = pStatus->data[4];
            sensor_data.opt6  = pStatus->data[6];
            sensor_data.opt7  = pStatus->data[5];

            memcpy(data, &sensor_data, sizeof(sensor_status_am));
            datasize += sizeof(sensor_status_am);

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
        case PARAM_MODBUS_CHAN_SET:
        {
            uint8_t num;

            num = params[1];
            if(num > 0 && num <= UNXX_MAX_MODBUS_CHAN) {
                read_data_from_flash((uint32_t *)&modbus_channel, sizeof(pUserConfig->modbus.chan[num-1]), (uint32_t)&pUserConfig->modbus.chan[num-1], 0);
                data[datasize++] = modbus_channel.enable;
                data[datasize++] = modbus_channel.slaveid;
                data[datasize++] = modbus_channel.quantity;
                data[datasize++] = modbus_channel.type;
                data[datasize++] = modbus_channel.sign;
                data[datasize++] = modbus_channel.decimal;

                pdata            = (uint8_t *)&modbus_channel.address;
                data[datasize++] = pdata[0];
                data[datasize++] = pdata[1];

                num = strlen((const char *)modbus_channel.name);
                num = sizeof(modbus_channel.name) > num ? num : sizeof(modbus_channel.name);

                memcpy(data + datasize, modbus_channel.name, num);
                datasize += num;
            }
            break;
        }
        case PARAM_MODBUS_GLOBAL_SET:
        {
            qDebug("pUserConf11ig2 size  %d  %d  %d  %d\n",sizeof(user_config_t),sizeof(io_setting_t),sizeof(ai_setting_t),sizeof(modbus_setting_t));
            read_data_from_flash((uint32_t *)&modbus_global, sizeof(modbus_global), (uint32_t)&pUserConfig->modbus.global, 0);
            pdata            = (uint8_t *)&modbus_global.exec_interval;
            data[datasize++] = pdata[0];
            data[datasize++] = pdata[1];

            pdata            = (uint8_t *)&modbus_global.max_res_time;
            data[datasize++] = pdata[0];
            data[datasize++] = pdata[1];

            pdata            = (uint8_t *)&modbus_global.retrytimes;
            data[datasize++] = pdata[0];
            data[datasize++] = pdata[1];

            pdata            = (uint8_t *)&modbus_global.collect_interval;
            data[datasize++] = pdata[0];
            data[datasize++] = pdata[1];

            pdata            = (uint8_t *)&modbus_global.poweron_time;
            data[datasize++] = pdata[0];
            data[datasize++] = pdata[1];

            data[datasize++] = modbus_global.pass_through_enable;
            data[datasize++] = modbus_global.pass_through_port;
            data[datasize++] = modbus_global.power_enable;
            break;
        }
        case PARAM_AI_CHAN_SET:
        {
            uint8_t num;
            ai_channel_set_t cfg;

            num = params[1];
            if(num > 0 && num <= UNXX_MAX_AI_NUM) {
                read_data_from_flash((uint32_t *)&cfg, sizeof(pUserConfig->ai.chan[num-1]), (uint32_t)&pUserConfig->ai.chan[num-1], 0);
                data[datasize++] = cfg.enable;
                data[datasize++] = cfg.mode;
            }
            break;
        }
        case PARAM_AI_GLOBAL_SET:
        {
            ai_global_set_t cfg;

            read_data_from_flash((uint32_t *)&cfg, sizeof(cfg), (uint32_t)&pUserConfig->ai.global, 0);
            pdata            = (uint8_t *)&cfg.collect_interval;
            data[datasize++] = pdata[0];
            data[datasize++] = pdata[1];

            pdata            = (uint8_t *)&cfg.poweron_time;
            data[datasize++] = pdata[0];
            data[datasize++] = pdata[1];
            break;
        }
        case PARAM_GPIO_CFG:
        {
            uint8_t num;
            io_setting_t cfg;

            num = params[1];
            if(num > 0 && num <= UNXX_MAX_GPIO_NUM) {
                read_data_from_flash((uint32_t *)&cfg, sizeof(pUserConfig->ai.global), (uint32_t)&pUserConfig->gpio[num-1], 0);
                data[datasize++] = cfg.enable;
                data[datasize++] = cfg.type;
                data[datasize++] = cfg.pull;
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

unp_state_t Qunp::send_read_param_request(uint8_t *out, uint8_t *in, uint16_t insize)
{
    uint8_t pkt[UNP_MAX_PKTSIZE] = {0};
    uint16_t pktsize = 0;
    pktsize = generate_pkt(in, insize, pkt, READ_PARAM_PKT);

    memset(&g_unp_ack, 0, sizeof(g_unp_ack));

    unp_send_pkt(pkt, pktsize);

//    if(m_todo == PARAM_APN_SET){
//        QThread::msleep(5000);
//    }
    if(wait_for_ack() == UNP_SUCCESS) {
        memcpy(out, g_unp_ack.params, g_unp_ack.params_len);
        return UNP_SUCCESS;
    } else {
        return UNP_FAIL;
    }
}

unp_state_t Qunp::send_write_param_request(uint8_t *data, uint16_t datasize)
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

unp_state_t Qunp::write_device_params(uint8_t *data, uint16_t datasize)
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
            user_config_t_am sensor_cfg;

            memcpy(&sensor_cfg, params, real_datasize);
            write_data_to_flash((uint32_t *)&sensor_cfg, sizeof(user_config_t_am), (uint32_t)pUserConfig_am);
            qDebug("=$$$$$$$$$$$$$$$$$$$$ %d %d %d\n",pUserConfig_am->sensor1.enable,pUserConfig_am->sensor2.enable,pUserConfig_am->sensor3.enable);
            qDebug("=$$$$$$$$$$$$$$$$$$$$ %d %d %d\n",pUserConfig_am->sensor1.calibration_enable,pUserConfig_am->sensor2.calibration_enable,pUserConfig_am->sensor3.calibration_enable);
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
        case PARAM_MODBUS_CHAN_SET:
        {
            uint8_t num;

            num   = params[offset++];
            if(num > 0 && num <= UNXX_MAX_MODBUS_CHAN) {
                modbus_channel.enable   = params[offset++];
                modbus_channel.slaveid  = params[offset++];
                modbus_channel.quantity = params[offset++];
                modbus_channel.type     = (modbus_reg_t)params[offset++];
                modbus_channel.sign     = params[offset++];
                modbus_channel.decimal  = params[offset++];

                memset(temp, 0, sizeof(temp));
                memcpy(temp, params + offset, sizeof(modbus_channel.address));
                offset += sizeof(modbus_channel.address);

                modbus_channel.address  = *(uint16_t *)temp;
                real_datasize = real_datasize - offset;

                memset(modbus_channel.name, 0, sizeof(modbus_channel.name));
                memcpy(modbus_channel.name, params + offset, (sizeof(modbus_channel.name) > real_datasize ? real_datasize : sizeof(modbus_channel.name)));
                write_data_to_flash((uint32_t *)&modbus_channel, sizeof(modbus_channel), (uint32_t)&pUserConfig->modbus.chan[num-1]);
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
        case PARAM_MODBUS_GLOBAL_SET:
        {
            memset(temp, 0, sizeof(temp));
            memcpy(temp, params + offset, sizeof(modbus_global.exec_interval));
            offset += 2;
            modbus_global.exec_interval  = *(uint16_t *)temp;

            memset(temp, 0, sizeof(temp));
            memcpy(temp, params + offset, sizeof(modbus_global.max_res_time));
            offset += 2;
            modbus_global.max_res_time  = *(uint16_t *)temp;

            memset(temp, 0, sizeof(temp));
            memcpy(temp, params + offset, sizeof(modbus_global.retrytimes));
            offset += 2;
            modbus_global.retrytimes  = *(uint16_t *)temp;

            memset(temp, 0, sizeof(temp));
            memcpy(temp, params + offset, sizeof(modbus_global.collect_interval));
            offset += 2;
            modbus_global.collect_interval  = *(uint16_t *)temp;

            memset(temp, 0, sizeof(temp));
            memcpy(temp, params + offset, sizeof(modbus_global.poweron_time));
            offset += 2;
            modbus_global.poweron_time  = *(uint16_t *)temp;

            modbus_global.pass_through_enable = params[offset++];
            modbus_global.pass_through_port   = params[offset++];
            modbus_global.power_enable        = params[offset++];
            //qDebug("set modbus global, interval = %d, restime = %d, retry = %d\r\n", modbus_global.exec_interval, modbus_global.max_res_time, modbus_global.retrytimes);
            write_data_to_flash((uint32_t *)&modbus_global, sizeof(modbus_global), (uint32_t)&pUserConfig->modbus.global);
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

        case PARAM_AI_CHAN_SET:
        {
            uint8_t num;
            ai_channel_set_t cfg;

            num = params[offset++];
            if(num > 0 && num <= UNXX_MAX_AI_NUM) {
                cfg.enable = params[offset++];
                cfg.mode   = (ai_mode_t)params[offset++];

                write_data_to_flash((uint32_t *)&cfg, sizeof(cfg), (uint32_t)&pUserConfig->ai.chan[num-1]);
#ifdef USE_IN_STM32
            load_adc_cfg(1);
#endif
            }
            break;
        }
        case PARAM_AI_GLOBAL_SET:
        {
            ai_global_set_t cfg;

            cfg.collect_interval = *(uint16_t *)(params + offset);
            offset += sizeof(uint16_t);

            cfg.poweron_time = *(uint16_t *)(params + offset);
            offset += sizeof(uint16_t);

            write_data_to_flash((uint32_t *)&cfg, sizeof(cfg), (uint32_t)&pUserConfig->ai.global);
#ifdef USE_IN_STM32
            load_adc_cfg(1);
#endif
            break;
        }
        case PARAM_GPIO_CFG:
        {
            uint8_t num;
            io_setting_t cfg;

            num = params[offset++];
            if(num > 0 && num <= UNXX_MAX_GPIO_NUM) {
                cfg.enable = params[offset++];
                cfg.type   = (gpio_type_t)params[offset++];
                cfg.pull   = params[offset++];
                write_data_to_flash((uint32_t *)&cfg, sizeof(cfg), (uint32_t)&pUserConfig->gpio[num-1]);
#ifdef USE_IN_STM32
                unxx_gpio_init();
#endif
            }
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

void Qunp::get_device_passwd(uint8_t *data)
{
    Q_UNUSED(data)
    read_data_from_flash((uint32_t *)data, UNP_PASSWD_LEN, (uint32_t)pDeviceParam->password, 0);
}

void Qunp::get_device_appkey(uint8_t *data)
{
    read_data_from_flash((uint32_t *)data, 16, (uint32_t)pLoRaWANParams->AppKey, 0);
}

void Qunp::get_productid(uint8_t *data)
{
    read_data_from_flash((uint32_t *)data, UNP_PRODUCT_ID_LEN, (uint32_t)pProductInfo->productid, 0);
}

void Qunp::get_device_hwver(uint8_t *data)
{
    read_data_from_flash((uint32_t *)data, UNP_HWVER_LEN, (uint32_t)pProductInfo->hwver, 0);
}
void Qunp::set_device_swver(uint8_t *data)
{
    write_data_to_flash((uint32_t *)data, strlen((const char *)data), (uint32_t)pProductInfo->swver);
}

void Qunp::set_upgrade_enable_flag(uint8_t upgrade_enable)
{
    write_data_to_flash((uint32_t *)&upgrade_enable, 1, (uint32_t)&pFlash_flag->upgrade_enable);
}

void Qunp::set_upgrade_flag(uint8_t *buf)
{
    if(strlen((const char *)buf) < UPGRADE_INFO_LEN) {
        write_data_to_flash((uint32_t *)buf, strlen((const char *)buf), FLASH_UPGRADE_INFO_ADDR);
    }
}

void Qunp::get_upgrade_flag(uint8_t *buf)
{
    memcpy(buf, (void *)FLASH_UPGRADE_INFO_ADDR, UPGRADE_INFO_LEN);
}

void Qunp::get_device_name(uint8_t *data)
{
    read_data_from_flash((uint32_t *)data, UNP_DEVNAME_LEN, (uint32_t)pDeviceParam->name, 0);
}

void Qunp::get_device_pn_em(uint8_t *data)
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

void Qunp::get_device_real_pn(uint8_t *data)
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

void Qunp::get_device_pn(uint8_t *data)
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

void Qunp::get_device_oem(uint8_t *data)
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

void Qunp::get_device_custom(uint16_t *value)
{
    uint8_t temp[UNP_CUSTOM_LEN + 1];
    uint32_t data;

    read_data_from_flash((uint32_t *)temp, sizeof(pPNInfo->custom), (uint32_t)pPNInfo->custom, 0);
    sscanf((const char *)temp, "%x", &data);

    *value = data;
}

void Qunp::get_device_sn(uint8_t *data)
{
    read_data_from_flash((uint32_t *)data, UNP_PRODUCT_SN_LEN, (uint32_t)pProductInfo->productsn, 0);
}

void Qunp::write_data_to_flash(uint32_t *data, uint16_t len_bytes, uint32_t addr)
{
    memcpy((void *)addr, data, len_bytes);
}

void Qunp::read_data_from_flash(uint32_t *data, uint16_t len_bytes, uint32_t addr, uint8_t fromisr)
{
    Q_UNUSED(fromisr)
    memcpy(data, (void *)addr, len_bytes);
}

void Qunp::unxx_reset_device(void)
{

}
void Qunp::unxx_restart_device(void)
{

}

void Qunp::unp_set_ussd_ack(uint8_t *data, uint16_t datasize)
{
    Q_UNUSED(data)
    Q_UNUSED(datasize)
}

void Qunp::get_upgrade_info(uint8_t *flag, uint32_t *crc32, uint32_t *size)
{
    Q_UNUSED(flag)
    Q_UNUSED(size)
    Q_UNUSED(crc32)
}

void Qunp::set_upgrade_info(uint8_t flag, uint32_t crc32, uint32_t size)
{
    Q_UNUSED(flag)
    Q_UNUSED(size)
    Q_UNUSED(crc32)
}

int Qunp::deal_with_unp(uint8_t *data, uint32_t len, unp_comnct_t type)
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
 * @brief Qunp::initSerialPort
 * @param s
 * @return
 */
bool Qunp::initSerialPort(SerialInfo s)
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
void Qunp::read_serialport_data()
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
 * @brief Qunp::close_serialport
 */
void Qunp::close_serialport()
{
    if(m_port->isOpen()){
        m_port->close();
    }
}

int Qunp::unp_send_passwd(uint8_t *passwd, uint16_t len)
{
    uint8_t pkt[64] = {0};
    uint16_t pktsize = 0;
    m_ackFlag = true;

    pktsize = generate_pkt(passwd, len, pkt, INPUT_PASSWD_PKT);

    memset(&g_unp_ack, 0, sizeof(g_unp_ack));
    unp_send_pkt(pkt, pktsize);

    return (wait_for_ack());
}

unp_state_t Qunp::unp_get_product_name(uint8_t *name)
{
    unp_state_t ret;
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t out[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;
//offset++;
    buf[offset++] = PARAM_UNXX_PRODUCTID;

    ret = send_read_param_request(out, buf, offset);

#if 01
    if(ret == UNP_SUCCESS) {
        if(strstr((char*)out,"EM") || strstr((char*)out,"AM") || strstr((char*)out,UC501)  || strstr((char*)out,UC502) || strstr((char*)out,UC511)  || strstr((char*)out,UC512)){
            snprintf((char *)name, UNP_PRODUCT_NAME_LEN, "%s", out);
            qDebug();
        }else{
            qDebug("... %s ",out);
            snprintf((char *)name, UNP_PRODUCT_NAME_LEN, "UC%s", out);
            qDebug("... %s ",name);
        }
    }
    m_product = QString::asprintf("%s",out);
    qDebug()<<m_product;
#else
    if(ret == UNP_SUCCESS) {
        snprintf((char *)name, UNP_PRODUCT_NAME_LEN, "EM500", out);
    }
    m_product.sprintf("EM500",out);
#endif
    return ret;
}

unp_state_t Qunp::unp_get_product_pn(uint8_t *pn)
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
        snprintf((char *)pn, UNP_PN_TOTAL_LEN, "PT100-T200", out);
    }
#endif
    m_pn = QString::asprintf("%s",pn);
    qDebug("pn--- %s\n",pn);
    return ret;
}

unp_state_t Qunp::unp_get_product_hwver(uint8_t *hwver)
{
    unp_state_t ret;
    uint8_t buf[UNP_MAX_PKTSIZE] = {0};
    uint8_t offset = 0;

    buf[offset++] = PARAM_UNXX_HWVER;

    ret = send_read_param_request(hwver, buf, offset);

    return ret;
}

unp_state_t Qunp::unp_get_product_swver(uint8_t *swver)
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
