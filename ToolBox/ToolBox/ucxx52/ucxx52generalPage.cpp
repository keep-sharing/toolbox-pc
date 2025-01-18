#include "ucxx52model.h"
#include "ui_ucxx52model.h"

/**
 * 点击Tab标签
 * @brief UCXX52Model::on_tabWidget_3_tabBarClicked
 * @param index
 */
void UCXX52Model::on_tabWidget_3_tabBarClicked(int index)
{
    qDebug()<<index;
//    rs232DtuTimer->stop();
    QVariantMap map;
    if(index == UCXX52DealThread::MG_BASIC){

        map.insert("readIndex",UCXX52DealThread::MG_BASIC);
        m_modbusReadIndex = UCXX52DealThread::MG_BASIC;
        if(m_dealThread->structSupportModel.lora){
            ui->modbusAwsServerAddr_frame->setVisible(false);
            ui->modbusBasic1_frame->setVisible(false);
            ui->modbusAwsCAFile_frame->setVisible(false);
            ui->modbusAwsCliCerFile_frame->setVisible(false);
            ui->modbusAwsCliKeyFile_frame->setVisible(false);
            ui->modbusNetType_frame->setVisible(false);
            ui->MudbusPinCode_frame->setVisible(false);
            ui->modbusApn_frame->setVisible(false);
            ui->modbusAPNPwd_frame->setVisible(false);
            ui->modbusAPNUser_frame->setVisible(false);
        }
    }else if(index == UCXX52DealThread::MG_RS485){
        map.insert("readIndex",UCXX52DealThread::MG_RS485);
        m_modbusReadIndex = UCXX52DealThread::MG_RS485;
    }else if(index == UCXX52DealThread::MG_RS232){
//        if(!m_dealThread->structSupportModel.lora){
//            rs232DtuTimer->start(30000);
//        }

        map.insert("readIndex",UCXX52DealThread::MG_RS232);
        m_modbusReadIndex = UCXX52DealThread::MG_RS232;
        if(m_dealThread->structSupportModel.lora){
            ui->rs232KeepAliveInterval_frame->setVisible(false);
            ui->rs232KeepAliveRetryTimes_frame->setVisible(false);
            ui->reconnectionInterval_frame->setVisible(false);
            ui->rs232RegisterString_frame->setVisible(false);
            ui->destIpAddr_frame->setVisible(false);
        }
    }

    QVariantList list;
    list.append(map);
    emit waitingVisible(true);
    emit requestToDevice(UCXX52DealThread::PAGE_GENERAL,list);
}

void UCXX52Model::onRecvGeneral(UCXX52DealThread::StructPageGeneral info)
{
    if(info.readSpecial == 9999){
        qDebug()<<info.readSpecialType<<info.counterNum<<info.gpioCounter;
        switch (info.readSpecialType) {
        case UCXX52DealThread::RNS_GPIO2_COUNTER_START:{
            if(info.counterNum == 1){
                if(ui->modbusGpioCounterStart_btn->text().contains(tr("Start"))){
                    ui->modbusGpioCounterStart_btn->setText(tr("Stop"));
                }else{
                    ui->modbusGpioCounterStart_btn->setText(tr("Start"));
                }
                ui->modbusGpioCounterRefresh_btn->setEnabled(true);
                ui->modbusGpioCounterStart_btn->setEnabled(true);
                ui->modbusGpioCounterClear_btn->setEnabled(true);

            }

        }
            break;
        case UCXX52DealThread::RNS_GPIO2_COUNTER_REFRESH:{
            if(info.counterNum == 1){
                if(info.gpioCounterStart.toInt() == 1){
                    ui->modbusGpioCounterStart_btn->setText(tr("Stop"));
                }else{
                    ui->modbusGpioCounterStart_btn->setText(tr("Start"));
                }
                ui->modbusGpioCounter_lineedit->setText(info.gpioCounter);
                ui->modbusGpioCounterRefresh_btn->setEnabled(true);
                ui->modbusGpioCounterStart_btn->setEnabled(true);
                ui->modbusGpioCounterClear_btn->setEnabled(true);

            }
        }
            break;
        case UCXX52DealThread::RNS_GPIO2_COUNTER_CLEAR:{
            if(info.counterNum == 1){
                if(info.gpioCounterStart.toInt() == 1){
                    ui->modbusGpioCounterStart_btn->setText(tr("Stop"));
                }else{
                    ui->modbusGpioCounterStart_btn->setText(tr("Start"));
                }
                ui->modbusGpioCounter_lineedit->setText(info.gpioCounter);
                ui->modbusGpioCounterRefresh_btn->setEnabled(true);
                ui->modbusGpioCounterStart_btn->setEnabled(true);
                ui->modbusGpioCounterClear_btn->setEnabled(true);

            }
        }
            break;
        default:
            break;
        }
        emit waitingVisible(false);
        return;
    }
    if(info.onlyDTUStatus){
        qDebug()<<info.dtuStatus1<<info.dtuStatus2;
        ui->rs232ServerStatus1_label->setText(info.dtuStatus1);
        ui->rs232ServerStatus2_label->setText(info.dtuStatus2);
        if(info.dtuStatus1 == "Connected"){
            ui->rs232ServerStatus1_label->setStyleSheet(QString("color: green;font-size:13px;font-family:'Arial'"));
        }else{
            ui->rs232ServerStatus1_label->setStyleSheet(QString("color: red;font-size:13px;font-family:'Arial'"));
        }
        if(info.dtuStatus2 == "Connected"){
            ui->rs232ServerStatus2_label->setStyleSheet(QString("color: green;font-size:13px;font-family:'Arial'"));
        }else{
            ui->rs232ServerStatus2_label->setStyleSheet(QString("color: red;font-size:13px;font-family:'Arial'"));
        }
        return;
    }
    m_generalPageInfo = info;
    qDebug()<<m_modbusReadIndex<<m_dealThread->structSupportModel.cloud;
    if(m_modbusReadIndex == UCXX52DealThread::MG_ALL || m_modbusReadIndex == UCXX52DealThread::MG_BASIC){
        ui->modbusAwsServerAddr_lineEdit->clear();
        if(m_dealThread->structSupportModel.cloud){
            if(info.application_mode == QunpUCXX52::APP_NONE){
                ui->modbusApplicationMode_cbx->setCurrentIndex(ui->modbusApplicationMode_cbx->findData(QunpUCXX52::APP_NONE));

            }else if(info.application_mode == QunpUCXX52::APP_URSALINK_CLOUD){
                ui->modbusApplicationMode_cbx->setCurrentIndex(ui->modbusApplicationMode_cbx->findData(QunpUCXX52::APP_URSALINK_CLOUD));

                ui->modbusAwsCAFile_frame->setEnabled(false);
                ui->modbusAwsCliCerFile_frame->setEnabled(false);
                ui->modbusAwsCliKeyFile_frame->setEnabled(false);
                ui->modbusMqttTlsCAFile_frame->setEnabled(false);
                ui->modbusMqttTlsCliCerFile_frame->setEnabled(false);
                ui->modbusMqttTlsCliKeyFile_frame->setEnabled(false);

            }else if(info.application_mode == QunpUCXX52::APP_AWS){
                ui->modbusApplicationMode_cbx->setCurrentIndex(ui->modbusApplicationMode_cbx->findData(QunpUCXX52::APP_AWS));
                ui->modbusAwsServerAddr_lineEdit->setText(info.serAddr);
                ui->modbusAwsCAFile_frame->setEnabled(true);
                ui->modbusAwsCliCerFile_frame->setEnabled(true);
                ui->modbusAwsCliKeyFile_frame->setEnabled(true);

                ui->modbusMqttTlsCAFile_frame->setEnabled(false);
                ui->modbusMqttTlsCliCerFile_frame->setEnabled(false);
                ui->modbusMqttTlsCliKeyFile_frame->setEnabled(false);

            }else if(info.application_mode == QunpUCXX52::APP_TCP){
                ui->modbusApplicationMode_cbx->setCurrentIndex(ui->modbusApplicationMode_cbx->findData(QunpUCXX52::APP_TCP));

                ui->modbusAwsCAFile_frame->setEnabled(false);
                ui->modbusAwsCliCerFile_frame->setEnabled(false);
                ui->modbusAwsCliKeyFile_frame->setEnabled(false);
                ui->modbusMqttTlsCAFile_frame->setEnabled(false);
                ui->modbusMqttTlsCliCerFile_frame->setEnabled(false);
                ui->modbusMqttTlsCliKeyFile_frame->setEnabled(false);

            }else if(info.application_mode == QunpUCXX52::APP_UDP){
                ui->modbusApplicationMode_cbx->setCurrentIndex(ui->modbusApplicationMode_cbx->findData(QunpUCXX52::APP_UDP));

                ui->modbusAwsCAFile_frame->setEnabled(false);
                ui->modbusAwsCliCerFile_frame->setEnabled(false);
                ui->modbusAwsCliKeyFile_frame->setEnabled(false);
                ui->modbusMqttTlsCAFile_frame->setEnabled(false);
                ui->modbusMqttTlsCliCerFile_frame->setEnabled(false);
                ui->modbusMqttTlsCliKeyFile_frame->setEnabled(false);

            }else if(info.application_mode == QunpUCXX52::APP_MQTT){
                ui->modbusApplicationMode_cbx->setCurrentIndex(ui->modbusApplicationMode_cbx->findData(QunpUCXX52::APP_MQTT));
                ui->modbusMqttTlsCAFile_frame->setEnabled(true);
                ui->modbusMqttTlsCliCerFile_frame->setEnabled(true);
                ui->modbusMqttTlsCliKeyFile_frame->setEnabled(true);

                ui->modbusAwsCAFile_frame->setEnabled(false);
                ui->modbusAwsCliCerFile_frame->setEnabled(false);
                ui->modbusAwsCliKeyFile_frame->setEnabled(false);

            }else if(info.application_mode == QunpUCXX52::APP_ALI){
                ui->modbusApplicationMode_cbx->setCurrentIndex(ui->modbusApplicationMode_cbx->findData(QunpUCXX52::APP_ALI));

                ui->modbusAwsCAFile_frame->setEnabled(false);
                ui->modbusAwsCliCerFile_frame->setEnabled(false);
                ui->modbusAwsCliKeyFile_frame->setEnabled(false);
                ui->modbusMqttTlsCAFile_frame->setEnabled(false);
                ui->modbusMqttTlsCliCerFile_frame->setEnabled(false);
                ui->modbusMqttTlsCliKeyFile_frame->setEnabled(false);

            }else if(info.application_mode == QunpUCXX52::APP_ONENET){
                ui->modbusApplicationMode_cbx->setCurrentIndex(ui->modbusApplicationMode_cbx->findData(QunpUCXX52::APP_ONENET));

                ui->modbusAwsCAFile_frame->setEnabled(false);
                ui->modbusAwsCliCerFile_frame->setEnabled(false);
                ui->modbusAwsCliKeyFile_frame->setEnabled(false);
                ui->modbusMqttTlsCAFile_frame->setEnabled(false);
                ui->modbusMqttTlsCliCerFile_frame->setEnabled(false);
                ui->modbusMqttTlsCliKeyFile_frame->setEnabled(false);
            }
#ifdef ODM_LHR_AZURE
            else if(info.application_mode == QunpUCXX52::APP_AZURE){
                ui->modbusApplicationMode_cbx->setCurrentIndex(ui->modbusApplicationMode_cbx->findData(QunpUCXX52::APP_AZURE));
                ui->modbusAwsCAFile_frame->setEnabled(true);
                ui->modbusAwsCliCerFile_frame->setEnabled(true);
                ui->modbusAwsCliKeyFile_frame->setEnabled(true);

                ui->modbusMqttTlsCAFile_frame->setEnabled(false);
                ui->modbusMqttTlsCliCerFile_frame->setEnabled(false);
                ui->modbusMqttTlsCliKeyFile_frame->setEnabled(false);
                ui->modbusAzureMode_cbx->setCurrentIndex(info.authMode.toInt());
                on_modbusAzureMode_cbx_currentIndexChanged(info.authMode.toInt());
            }
#endif
            ui->modbusKeepAliveInterval_lineedit->setText(QString::number(info.keepAliveInterval.toInt() ));
            ui->modbusReportInterval_lineedit->setText(QString::number(info.reportingInterval.toInt() ));

            ui->modbusApn_lineEdit->setText(info.apn);
            ui->modbusAPNUser_lineEdit->setText(info.apnUser);
            ui->modbusAPNPwd_lineEdit->setText(info.apnPwd);
            ui->modbusTcpkeepAlive_lineedit->setText(info.tcpkeepAlive);
            ui->modbusBrokerAddr_lineEdit->setText(info.brokerAddr);
            ui->modbusBrokerPort_lineEdit->setText(info.brokerPort);
            ui->modbusClientID_lineEdit->setText(info.clientID);
            ui->modbusConnectTimeout_lineEdit->setText(info.connectTimeout);
            ui->modbusMqttKeepAliveInterval_lineEdit->setText(info.mqttKeepAliveInterval);

            qDebug()<<info.customHeartbeat.toInt();
//            ui->modbusCustomHeartbeat_cb->setChecked(info.customHeartbeat.toInt());
            on_modbusCustomHeartbeat_cb_clicked(info.customHeartbeat.toInt());

            ui->modbusCustomHeartbeat_frame->setVisible(ui->modbusCustomHeartbeat_cb->isChecked());
            ui->modbusRequireResponseCb_frame->setVisible(ui->modbusCustomHeartbeat_cb->isChecked());
//            if(ui->modbusApplicationMode_cbx->currentData().toInt() == APP_UDP || ui->modbusApplicationMode_cbx->currentData().toInt() == APP_TCP)
//            ui->modbusResponseContent_frame->setVisible(ui->modbusRequireResponse_cb->isChecked() && ui->modbusCustomHeartbeat_cb->isChecked());

            ui->modbusCustomContent_lineEdit->setText(info.customContent);
            ui->modbusHeartbeatInterval_lineEdit->setText(info.heartbeatInterval);
            ui->modbusRequireResponse_cb->setChecked(info.requireResponse.toInt());
            on_modbusRequireResponse_cb_clicked(ui->modbusRequireResponse_cb->isChecked());
            ui->modbusRequireResponse_cb->setChecked(ui->modbusRequireResponse_cb->isChecked());
//            ui->modbusResponseContent_frame->setVisible(ui->modbusRequireResponse_cb->isChecked());

            ui->modbusResponseContent_lineEdit->setText(info.responseContent);
            ui->modbusServerAddr1_lineedit->setText(info.tcpServerAddr1);
            ui->modbusServerPort1_lineedit->setText(info.tcpServerPort1);
            ui->modbusServerAddr2_lineedit->setText(info.tcpServerAddr2);
            ui->modbusServerPort2_lineedit->setText(info.tcpServerPort2);
            ui->modbusServerStatus1_label->setText(info.status1);
            ui->modbusServerStatus2_label->setText(info.status2);

            if(info.status1 == "Connected"){
                ui->modbusServerStatus1_label->setStyleSheet(QString("color: green;font-size:13px;font-family:'Arial'"));
            }else{
                ui->modbusServerStatus1_label->setStyleSheet(QString("color: red;font-size:13px;font-family:'Arial'"));
            }
            if(info.status2 == "Connected"){
                ui->modbusServerStatus2_label->setStyleSheet(QString("color: green;font-size:13px;font-family:'Arial'"));
            }else{
                ui->modbusServerStatus2_label->setStyleSheet(QString("color: red;font-size:13px;font-family:'Arial'"));
            }

            ui->modbusMqttUserCreEnable_cb->setChecked(info.userCreEnable.toInt());
            on_modbusMqttUserCreEnable_cb_clicked(info.userCreEnable.toInt());
            ui->modbusMqttUserCreUsername_linEdit->setText(info.userCreUsername);
            ui->modbusMqttUserCrePwdlinEdit->setText(info.userCrePwd);
            ui->modbusMqttTlsEnable_cb->setChecked(info.tlsEnable.toInt());
            on_modbusMqttTlsEnable_cb_clicked(info.tlsEnable.toInt());

            //NB for Aliyun
            ui->modbusAliyunClientID_lineEdit->setText(info.aliClientID);
            ui->modbusAliyunProductKey_lineEdit->setText(info.aliProductKey);
            ui->modbusAliyunDeviceSecret_lineEdit->setText(info.aliDevSecret);
            ui->modbusAliyunKeepAliveInterval_lineEdit->setText(info.aliKeepAilve);
            ui->modbusAliyunQoS_cbx->setCurrentIndex(info.aliQos.toInt());

            //ONENET
            ui->modbusOneNetKeepAlive_lineEdit->setText(info.oneNetKeepAlive);
            ui->modbusOneNetKey_lineEdit->setText(info.oneNetKey);
            ui->modbusProductID_lineedit->setText(info.oneNetProductID);
#ifdef ODM_LHR_AZURE
            ui->modbusConnectStr_lineEdit->setText(info.serAddr);
#endif
        }
        ui->modbusNetworkType_cbx->setCurrentIndex(ui->modbusNetworkType_cbx->findData(info.network_type));
        ui->modbusDataPollingInterval_lineedit->setText(QString::number(info.dataCollectInterval ));
        ui->modbusPinNum_lineEdit->setText(info.pinCode);

        if(m_dealThread->structSupportModel.aws || m_dealThread->structSupportModel.data){
            //证书
            ui->modbusAwsCAFile_lineEdit->setText(info.caFile);
            ui->modbusAwsCliCerFile_lineEdit->setText(info.clientFile);
            ui->modbusAwsCliKeyFile_lineEdit->setText(info.clientKeyFile);

            ui->modbusMqttTlsCAFile_lineEdit->setText(info.caFile);
            ui->modbusMqttTlsCliCerFile_lineEdit->setText(info.clientFile);
            ui->modbusMqttTlsCliKeyFile_lineEdit->setText(info.clientKeyFile);
        }

        if(m_dealThread->structSupportModel.lora){
            on_modbusApplicationMode_cbx_currentIndexChanged(-1);
            ui->modbusReportInterval_lineedit->setText(QString::number(info.reportingInterval.toInt() ));
            ui->modbusGpioType_cbx->setCurrentIndex(info.gpioType.toInt());
            ui->modbusGpioCounter_lineedit->setText(info.gpioType.toInt() == 0 ? "0":info.gpioCounter);
            ui->modbusGpioCounterStart_btn->setText(info.gpioCounterStart.toInt() == 1 ? tr("Stop"):tr("Start"));
            ui->modbusGpioCounter_frame->setVisible(info.gpioType.toInt() == 1);

        }
    }
    if(m_modbusReadIndex == UCXX52DealThread::MG_ALL || m_modbusReadIndex == UCXX52DealThread::MG_RS485){
        ui->rs485Enabel_cb->setChecked(info.rs485Enabel==1);
        ui->rs485BaudRate_cbx->setCurrentIndex(ui->rs485BaudRate_cbx->findText(QString::number(info.rs485Baudrate)));
        ui->rs485Databit_cbx->setCurrentIndex(ui->rs485Databit_cbx->findData(info.rs485Databit));
        ui->rs485Stopbit_cbx->setCurrentIndex(ui->rs485Stopbit_cbx->findData(info.rs485Stopbit));
        ui->rs485Parity_cbx->setCurrentIndex(ui->rs485Parity_cbx->findData(info.rs485Parity));

        ui->rs485Bridge_cb->setChecked(info.rs485BridgeLoraWanEnable);
        ui->rs485BridgePort_lineedit->setText(info.rs485BridgeLoraWanPort);

        if(m_dealThread->structSupportModel.lora){
            ui->rs485BridgeEnable_frame->setVisible(true);
            ui->rs485BridgePort_frame->setVisible(ui->rs485Bridge_cb->isChecked());
        }else{
            ui->rs485BridgeEnable_frame->setVisible(ui->rs485Bridge_cb->isChecked());
            ui->rs485BridgePort_frame->setVisible(ui->rs485Bridge_cb->isChecked());
        }
        on_rs485Enabel_cb_clicked(ui->rs485Enabel_cb->isChecked());
    }
    if(m_modbusReadIndex == UCXX52DealThread::MG_ALL || m_modbusReadIndex == UCXX52DealThread::MG_RS232){
        if(m_dealThread->structSupportModel.lora)
            ui->rs232Protocol_frame->setVisible(false);
        ui->rs232Enable_cb->setChecked(info.rs232Enabel==1);
        ui->rs232BaudRate_cbx->setCurrentIndex(ui->rs232BaudRate_cbx->findText(QString::number(info.rs232Baudrate)));
        ui->rs232Databit_cbx->setCurrentIndex(ui->rs232Databit_cbx->findData(info.rs232Databit));
        ui->rs232Stopbit_cbx->setCurrentIndex(ui->rs232Stopbit_cbx->findData(info.rs232Stopbit));
        ui->rs232Parity_cbx->setCurrentIndex(ui->rs232Parity_cbx->findData(info.rs232Parity));

        ui->rs232Protocol_cbx->setCurrentIndex(ui->rs232Protocol_cbx->findData(info.rs232Protocol));
        ui->rs232KeepAliveInterval_lineeedit->setText(QString::number(info.rs232KeepAliveInterval));
        ui->rs232KeppAliveRetryTimes_lineedit->setText(QString::number(info.rs232KeepAliveRetryTimes));
        ui->rs232PacketLength_lineedit->setText(QString::number(info.rs232PacketLength));
        ui->rs232SerialFrameInterval_lineedit->setText(QString::number(info.rs232FrameInterval));
        ui->rs232ReconnectInterval_lineedit->setText(QString::number(info.rs232ReconnectInterval));
        ui->rs232RegisterString_lineedit->setText(info.rs232RegsterString);

        ui->rs232ServerStatus1_label->setText(info.dtuStatus1);
        ui->rs232ServerStatus2_label->setText(info.dtuStatus2);
        if(info.dtuStatus1 == "Connected"){
            ui->rs232ServerStatus1_label->setStyleSheet(QString("color: green;font-size:13px;font-family:'Arial'"));
        }else{
            ui->rs232ServerStatus1_label->setStyleSheet(QString("color: red;font-size:13px;font-family:'Arial'"));
        }
        if(info.dtuStatus2 == "Connected"){
            ui->rs232ServerStatus2_label->setStyleSheet(QString("color: green;font-size:13px;font-family:'Arial'"));
        }else{
            ui->rs232ServerStatus2_label->setStyleSheet(QString("color: red;font-size:13px;font-family:'Arial'"));
        }
        ui->rs232ServerAddr1_lineedit->setText(info.serverAddr1);
        ui->rs232ServerPort1_lineedit->setText(info.serverPort1);
        ui->rs232ServerAddr2_lineedit->setText(info.serverAddr2);
        ui->rs232ServerPort2_lineedit->setText(info.serverPort2);
//        if(info.rs232Protocol == QunpUCXX52::SERIAL_TCP_SERVER || info.rs232Protocol == QunpUCXX52::SERIAL_UDP_SERVER){
            ui->rs232ListenPort_lineeedit->setText(info.serverPort1);
//        }

        on_rs232Enable_cb_clicked(ui->rs232Enable_cb->isChecked());
        on_rs232Protocol_cbx_currentIndexChanged(ui->rs232Protocol_cbx->findData(info.rs232Protocol));

        if(m_dealThread->structSupportModel.lora){
            ui->rs232KeepAliveInterval_frame->setVisible(false);
            ui->rs232KeepAliveRetryTimes_frame->setVisible(false);
//            ui->rs232PacketLen_frame->setVisible(false);
//            ui->rs232SerialFrame_frame->setVisible(false);
            ui->reconnectionInterval_frame->setVisible(false);
            ui->rs232RegisterString_frame->setVisible(false);
            ui->destIpAddr_frame->setVisible(false);

            ui->modbusAwsServerAddr_frame->setVisible(false);
            ui->modbusBasic1_frame->setVisible(false);
            ui->modbusAwsCAFile_frame->setVisible(false);
            ui->modbusAwsCliCerFile_frame->setVisible(false);
            ui->modbusAwsCliKeyFile_frame->setVisible(false);
            ui->modbusNetType_frame->setVisible(false);
            ui->MudbusPinCode_frame->setVisible(false);
            ui->modbusApn_frame->setVisible(false);
            ui->modbusAPNPwd_frame->setVisible(false);
            ui->modbusAPNUser_frame->setVisible(false);
        }
    }

    if(m_dealThread->structSupportModel.lora){
        on_modbusApplicationMode_cbx_currentIndexChanged(-1);
        ui->modbusReportInterval_lineedit->setText(QString::number(info.reportingInterval.toInt() ));
    }
    emit waitingVisible(false);
}

/**
 * 改密码选择框
 * @brief UCXX52Model::on_modbusChangePwd_cb_clicked
 * @param checked
 */
void UCXX52Model::on_modbusChangePwd_cb_clicked(bool checked)
{

    ui->modbusOldPwd_lineedit->clear();
    ui->modbusNewPwd_lineedit->clear();
    ui->modbusReNewPwd_lineedit->clear();

    ui->modbusChannelChangePwd_frame->setVisible(checked);
}

/**
 * DTU状态检查
 * @brief UCXX52Model::onRs232DTUExitSlot
 */
void UCXX52Model::onRs232DTUExitSlot()
{
    QVariantMap map;
    if(ui->tabWidget_3->currentIndex()  == UCXX52DealThread::MG_RS232){
        map.insert("readIndex",UCXX52DealThread::MG_RS232);
        m_modbusReadIndex = UCXX52DealThread::MG_RS232;
        if(m_dealThread->structSupportModel.lora){
            ui->rs232KeepAliveInterval_frame->setVisible(false);
            ui->rs232KeepAliveRetryTimes_frame->setVisible(false);
            ui->reconnectionInterval_frame->setVisible(false);
            ui->rs232RegisterString_frame->setVisible(false);
            ui->destIpAddr_frame->setVisible(false);
        }
    }
    QVariantList list;
    list.append(map);
    emit requestToDevice(UCXX52DealThread::CONFIG_READ_DTU_STATUS,list);
}

/**
 * rs485 enable?
 * @brief UCXX52Model::on_rs485Enabel_cb_clicked
 * @param checked
 */
void UCXX52Model::on_rs485Enabel_cb_clicked(bool checked)
{
    ui->rs485BaudRate_cbx->setEnabled(checked);
    ui->rs485Databit_cbx->setEnabled(checked);
    ui->rs485Stopbit_cbx->setEnabled(checked);
    ui->rs485Parity_cbx->setEnabled(checked);
    ui->rs485Bridge_cb->setEnabled(checked);
    ui->rs485BridgePort_lineedit->setEnabled(checked);

}

/**
 * rs232 Enable
 * @brief UCXX52Model::on_rs232Enable_cb_clicked
 * @param checked
 */
void UCXX52Model::on_rs232Enable_cb_clicked(bool checked)
{
    ui->rs232BaudRate_cbx->setEnabled(checked);
    ui->rs232Databit_cbx->setEnabled(checked);
    ui->rs232Stopbit_cbx->setEnabled(checked);
    ui->rs232Parity_cbx->setEnabled(checked);
    ui->rs232ListenPort_lineeedit->setEnabled(checked);
    ui->rs232Protocol_cbx->setEnabled(checked);
    ui->rs232KeepAliveInterval_lineeedit->setEnabled(checked);
    ui->rs232KeppAliveRetryTimes_lineedit->setEnabled(checked);
    ui->rs232PacketLength_lineedit->setEnabled(checked);
    ui->rs232SerialFrameInterval_lineedit->setEnabled(checked);
    ui->rs232ReconnectInterval_lineedit->setEnabled(checked);
    ui->rs232RegisterString_lineedit->setEnabled(checked);
    ui->frame_25->setEnabled(checked);
    ui->frame_30->setEnabled(checked);
}


void UCXX52Model::on_modbusCustomHeartbeat_cb_clicked(bool checked)
{
    if(ui->modbusApplicationMode_cbx->currentData().toInt() != QunpUCXX52::APP_UDP && ui->modbusApplicationMode_cbx->currentData().toInt() != QunpUCXX52::APP_TCP){
        ui->modbusCustomHeartbeat_frame->setVisible(false);
        ui->modbusRequireResponseCb_frame->setVisible(false);
        ui->modbusResponseContent_frame->setVisible(false);
        ui->modbusServerStatusTitle_label->setVisible(false);
        ui->modbusServerStatus1_label->setVisible(false);
        ui->modbusServerStatus2_label->setVisible(false);
        return;
    }
    ui->modbusCustomHeartbeat_cb->setChecked(checked);
    ui->modbusCustomHeartbeat_frame->setVisible(checked);
    ui->modbusRequireResponseCb_frame->setVisible(checked);
    ui->modbusResponseContent_frame->setVisible(ui->modbusRequireResponse_cb->isChecked() && ui->modbusCustomHeartbeat_cb->isChecked());

    if(!checked)
        on_modbusRequireResponse_cb_clicked(false);
    on_modbusChangePwd_cb_clicked(ui->modbusChangePwd_cb->isChecked());
}

void UCXX52Model::on_modbusRequireResponse_cb_clicked(bool checked)
{
    if(ui->modbusApplicationMode_cbx->currentData().toInt() != QunpUCXX52::APP_UDP && ui->modbusApplicationMode_cbx->currentData().toInt() != QunpUCXX52::APP_TCP){
        ui->modbusCustomHeartbeat_frame->setVisible(false);
        ui->modbusRequireResponseCb_frame->setVisible(false);
        ui->modbusResponseContent_frame->setVisible(false);
        ui->modbusServerStatusTitle_label->setVisible(false);
        ui->modbusServerStatus1_label->setVisible(false);
        ui->modbusServerStatus2_label->setVisible(false);
        return;
    }
    ui->modbusRequireResponse_cb->setChecked(checked);
    ui->modbusResponseContent_frame->setVisible(checked);
    if(!checked){
        if(ui->modbusApplicationMode_cbx->currentData().toInt() == QunpUCXX52::APP_UDP){
            ui->modbusServerStatusTitle_label->setVisible(false);
            ui->modbusServerStatus1_label->setVisible(false);
            ui->modbusServerStatus2_label->setVisible(false);
        }else{
            ui->modbusServerStatusTitle_label->setVisible(true);
            ui->modbusServerStatus1_label->setVisible(true);
            ui->modbusServerStatus2_label->setVisible(true);
        }
    }else{
        ui->modbusServerStatusTitle_label->setVisible(true);
        ui->modbusServerStatus1_label->setVisible(true);
        ui->modbusServerStatus2_label->setVisible(true);
    }
    on_modbusChangePwd_cb_clicked(ui->modbusChangePwd_cb->isChecked());
}


void UCXX52Model::on_modbusApplicationMode_cbx_currentIndexChanged(int index)
{
    index = ui->modbusApplicationMode_cbx->currentData().toInt();

    ui->modbusAwsServerAddr_frame->setVisible(false);
    ui->modbusBasic1_frame->setVisible(false);
    ui->modbusReporting_frame->setVisible(false);
    ui->modbusAwsCAFile_frame->setVisible(false);
    ui->modbusAwsCliCerFile_frame->setVisible(false);
    ui->modbusAwsCliKeyFile_frame->setVisible(false);
    ui->modbusTcpkeepAlive_frame->setVisible(false);
    ui->modbusMqttBrokerAddr_frame->setVisible(false);
    ui->modbusMqttPort_frame->setVisible(false);
    ui->modbusMqttClientId_frame->setVisible(false);
    ui->modbusMqttConnectTimeout_frame->setVisible(false);
    ui->modbusMqttKeepAliveInterval_frame->setVisible(false);
    ui->modbusCustomHeartbeatCb_frame->setVisible(false);
    ui->modbusCustomHeartbeat_frame->setVisible(false);
    ui->modbusRequireResponseCb_frame->setVisible(false);
    ui->modbusResponseContent_frame->setVisible(false);
    ui->modbusTcpDestIpAddr_frame->setVisible(false);
    ui->modbusMqttUserCre_gb->setVisible(false);
    ui->modbusMqttTls_gb->setVisible(false);
    ui->frame_34->setVisible(false);
    ui->modbusAzureMode_frame->setVisible(false);
    ui->modbusAliyun_frame->setVisible(false);
    ui->modbusConnectStr_frame->setVisible(false);
    ui->modbusOneNetKeepAlive_frame->setVisible(false);
    ui->modbusOneNetProductID_frame->setVisible(false);
    ui->modbusOneNetKey_frame->setVisible(false);
    if(index == QunpUCXX52::APP_NONE){

    }else if(index == QunpUCXX52::APP_URSALINK_CLOUD){
        ui->modbusBasic1_frame->setVisible(true);

    }else if(index == QunpUCXX52::APP_AWS){
        ui->modbusBasic1_frame->setVisible(true);
        ui->modbusReporting_frame->setVisible(true);
        ui->modbusAwsServerAddr_frame->setVisible(true);
        ui->modbusAwsCAFile_frame->setVisible(true);
        ui->modbusAwsCliCerFile_frame->setVisible(true);
        ui->modbusAwsCliKeyFile_frame->setVisible(true);
        ui->frame_34->setVisible(true);

    }else if(index == QunpUCXX52::APP_TCP){
        ui->modbusTcpkeepAlive_frame->setVisible(true);
        ui->modbusCustomHeartbeatCb_frame->setVisible(true);
        ui->modbusTcpDestIpAddr_frame->setVisible(true);
        ui->modbusReporting_frame->setVisible(true);
        ui->frame_34->setVisible(true);

        on_modbusCustomHeartbeat_cb_clicked(false);
        on_modbusRequireResponse_cb_clicked(false);

        if(m_proName.at(3)=='5'){
            ui->modbusTcpkeepAlive_frame->setVisible(false);
        }
    }else if(index == QunpUCXX52::APP_UDP){
        ui->modbusCustomHeartbeatCb_frame->setVisible(true);
        ui->modbusTcpDestIpAddr_frame->setVisible(true);
        ui->modbusReporting_frame->setVisible(true);
        ui->frame_34->setVisible(true);

        on_modbusCustomHeartbeat_cb_clicked(false);
        on_modbusRequireResponse_cb_clicked(false);

        if(m_proName.at(3)=='5'){
            ui->modbusTcpkeepAlive_frame->setVisible(false);
        }
    }else if(index == QunpUCXX52::APP_MQTT){
        ui->modbusMqttBrokerAddr_frame->setVisible(true);
        ui->modbusMqttPort_frame->setVisible(true);
        ui->modbusMqttClientId_frame->setVisible(true);
        ui->modbusMqttConnectTimeout_frame->setVisible(true);
        ui->modbusMqttKeepAliveInterval_frame->setVisible(true);
        ui->modbusMqttUserCre_gb->setVisible(true);
        ui->modbusMqttTls_gb->setVisible(true);
        ui->modbusReporting_frame->setVisible(true);
        ui->frame_34->setVisible(true);
    }else if (index == QunpUCXX52::APP_ALI){
        ui->modbusReporting_frame->setVisible(true);
        ui->frame_34->setVisible(true);
        ui->modbusAliyun_frame->setVisible(true);
    }else if (index == QunpUCXX52::APP_ONENET){
        ui->modbusOneNetKeepAlive_frame->setVisible(true);
        ui->modbusOneNetProductID_frame->setVisible(true);
        ui->modbusOneNetKey_frame->setVisible(true);
        ui->modbusReporting_frame->setVisible(true);
        ui->frame_34->setVisible(true);

        ui->modbusCustomHeartbeat_frame->setVisible(false);
        ui->modbusRequireResponseCb_frame->setVisible(false);
        ui->modbusResponseContent_frame->setVisible(false);
        ui->modbusServerStatusTitle_label->setVisible(false);
        ui->modbusServerStatus1_label->setVisible(false);
        ui->modbusServerStatus2_label->setVisible(false);

    }
#ifdef ODM_LHR_AZURE
    else if(index == APP_AZURE){
        ui->modbusAzureMode_frame->setVisible(true);
        ui->modbusBasic1_frame->setVisible(true);
//        ui->modbusReporting_frame->setVisible(true);
        ui->modbusDescription_lineEdit_frame->setVisible(true);
        on_modbusAzureMode_cbx_currentIndexChanged(ui->azureMode_cbx->currentIndex());
    }
#endif

    if(m_dealThread->structSupportModel.lora){
        ui->modbusCellularSetting_gb->setVisible(false);
        ui->modbusReporting_frame->setVisible(true);
        ui->frame_34->setVisible(false);
//        ui->label_166->setGeometry(10,1,ui->label_166->width(),ui->label_166->height());
//        ui->label_135->setGeometry(10,1,ui->label_135->width(),ui->label_135->height());
    }
     ui->reportingIntercal_label_2->setIndent(ui->modbusAppModel_frame->isVisible() ? 30: 9);
    on_modbusChangePwd_cb_clicked(ui->modbusChangePwd_cb->isChecked());

}

void UCXX52Model::on_rs232Protocol_cbx_currentIndexChanged(int index)
{
    Q_UNUSED(index)
#ifdef ODM_LHR_AZURE
    ui->destIpAddr_frame->setVisible(false);
    ui->rs232RegisterString_frame->setVisible(false);
    ui->reconnectionInterval_frame->setVisible(false);
    ui->rs232SerialFrame_frame->setVisible(false);
    ui->rs232PacketLen_frame->setVisible(false);
    ui->rs232KeepAliveRetryTimes_frame->setVisible(false);
    ui->rs232KeepAliveInterval_frame->setVisible(false);
    ui->rs232ListenPort_frame->setVisible(false);
    ui->rs232Protocol_frame->setVisible(false);
    return;
#endif
    ui->rs232ListenPort_frame->setVisible(true);
    ui->rs232KeepAliveInterval_frame->setVisible(true);
    ui->rs232KeepAliveRetryTimes_frame->setVisible(true);
    ui->rs232PacketLen_frame->setVisible(true);
    ui->rs232SerialFrame_frame->setVisible(true);
    ui->reconnectionInterval_frame->setVisible(true);
    ui->rs232RegisterString_frame->setVisible(true);
    ui->destIpAddr_frame->setVisible(true);
    if(ui->rs232Protocol_cbx->currentData().toInt() == QunpUCXX52::SERIAL_TCP){
        ui->rs232ListenPort_frame->setVisible(false);
    }else if (ui->rs232Protocol_cbx->currentData().toInt() == QunpUCXX52::SERIAL_UDP) {
        ui->rs232ListenPort_frame->setVisible(false);
        ui->rs232KeepAliveInterval_frame->setVisible(false);
        ui->rs232KeepAliveRetryTimes_frame->setVisible(false);
        ui->reconnectionInterval_frame->setVisible(false);
    }else if(ui->rs232Protocol_cbx->currentData().toInt() == QunpUCXX52::SERIAL_TCP_SERVER){
        ui->reconnectionInterval_frame->setVisible(false);
        ui->rs232RegisterString_frame->setVisible(false);
        ui->destIpAddr_frame->setVisible(false);
        if(m_proName.mid(3,1) == NT_GSM){
            ui->rs232KeepAliveRetryTimes_frame->setVisible(false);
        }
    }else if(ui->rs232Protocol_cbx->currentData().toInt() == QunpUCXX52::SERIAL_UDP_SERVER){
        ui->rs232KeepAliveInterval_frame->setVisible(false);
        ui->rs232KeepAliveRetryTimes_frame->setVisible(false);
        ui->reconnectionInterval_frame->setVisible(false);
        ui->reconnectionInterval_frame->setVisible(false);
        ui->rs232RegisterString_frame->setVisible(false);
        ui->destIpAddr_frame->setVisible(false);
    }
}

/**
 * 保存basic
 * @brief UCXX52Model::on_modbusBasicSave_btn_clicked
 */
void UCXX52Model::on_modbusBasicSave_btn_clicked()
{
    ui->modbusConnectStr_lineEdit->setStyleSheet(RECOVERY_INPUT);
    ui->modbusAwsServerAddr_lineEdit->setStyleSheet(RECOVERY_INPUT);
    ui->modbusDataPollingInterval_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->modbusReportInterval_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->modbusKeepAliveInterval_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->modbusOneNetKeepAlive_lineEdit->setStyleSheet(RECOVERY_INPUT);
    ui->modbusMqttUserCreUsername_linEdit->setStyleSheet(RECOVERY_INPUT);
    ui->modbusMqttUserCrePwdlinEdit->setStyleSheet(RECOVERY_INPUT);
    ui->modbusHeartbeatInterval_lineEdit->setStyleSheet(RECOVERY_INPUT);
    ui->modbusTcpkeepAlive_lineedit->setStyleSheet(RECOVERY_INPUT);

    if(ui->modbusChangePwd_cb->isChecked()){
        if(ui->modbusOldPwd_lineedit->text().length() != 6){
            showWarning(this,tr("Attention"),tr("Please enter a 6-character password."));

            return;
        }

        if(ui->modbusNewPwd_lineedit->text() != ui->modbusReNewPwd_lineedit->text()){
            showWarning(this,tr("Attention"),tr("New Password and Confirm Password do not match."));

            return;
        }
        if(ui->modbusNewPwd_lineedit->text().length() != 6){
            showWarning(this,tr("Attention"),tr("Please enter a 6-character password."));

            return;
        }
        m_loginPwd = ui->modbusNewPwd_lineedit->text().trimmed();
    }

    if(ui->modbusConnectStr_lineEdit->text().isEmpty() && ui->modbusConnectStr_lineEdit->isVisible()){
        ui->modbusConnectStr_lineEdit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("This field is required."));
        ui->modbusConnectStr_lineEdit->setFocus();
        return;
    }

    if(ui->modbusAwsServerAddr_lineEdit->text().isEmpty() && ui->modbusAwsServerAddr_lineEdit->isVisible()){
        ui->modbusAwsServerAddr_lineEdit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("This field is required."));

        ui->modbusAwsServerAddr_lineEdit->setFocus();
        return;
    }
    if(ui->modbusApplicationMode_cbx->currentData().toInt() ==QunpUCXX52::APP_ALI){
        if((ui->modbusKeepAliveInterval_lineedit->text().trimmed().isEmpty() || ui->modbusKeepAliveInterval_lineedit->text().trimmed().toInt()>1200 || ui->modbusKeepAliveInterval_lineedit->text().trimmed().toInt()<30)
                && ui->modbusKeepAliveInterval_lineedit->isVisible()){
            ui->modbusKeepAliveInterval_lineedit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Valid Range：30-1200."));

            ui->modbusKeepAliveInterval_lineedit->setFocus();
            return;
        }
    }else if((ui->modbusOneNetKeepAlive_lineEdit->text().trimmed().isEmpty() || ui->modbusOneNetKeepAlive_lineEdit->text().trimmed().toInt()>3600 || ui->modbusOneNetKeepAlive_lineEdit->text().trimmed().toInt()<1)
             && ui->modbusOneNetKeepAlive_lineEdit->isVisible()){
         ui->modbusOneNetKeepAlive_lineEdit->setStyleSheet(ERROR_INPUT);
         showWarning(this,tr("Attention"),tr("Valid Range：1-3600."));

         ui->modbusOneNetKeepAlive_lineEdit->setFocus();
         return;

    }else{
        if((ui->modbusKeepAliveInterval_lineedit->text().trimmed().isEmpty() || ui->modbusKeepAliveInterval_lineedit->text().trimmed().toInt()>3600 || ui->modbusKeepAliveInterval_lineedit->text().trimmed().toInt()<1)
                && ui->modbusKeepAliveInterval_lineedit->isVisible()){
            ui->modbusKeepAliveInterval_lineedit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Valid Range：1-3600."));

            ui->modbusKeepAliveInterval_lineedit->setFocus();
            return;
        }
    }

    if((ui->modbusReportInterval_lineedit->text().trimmed().isEmpty() || ui->modbusReportInterval_lineedit->text().trimmed().toInt()>64800 || ui->modbusReportInterval_lineedit->text().trimmed().toInt()<10)
            && ui->modbusReportInterval_lineedit->isVisible()){
        ui->modbusReportInterval_lineedit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("Valid Range：10-64800."));

        ui->modbusReportInterval_lineedit->setFocus();
        return;
    }
    if((ui->modbusDataPollingInterval_lineedit->text().trimmed().isEmpty() || ui->modbusDataPollingInterval_lineedit->text().trimmed().toInt()>3600 || ui->modbusDataPollingInterval_lineedit->text().trimmed().toInt()<1)
            && ui->modbusDataPollingInterval_lineedit->isVisible()){
        ui->modbusDataPollingInterval_lineedit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("Valid Range：1-3600."));

        ui->modbusDataPollingInterval_lineedit->setFocus();
        return;
    }
    if((ui->modbusReportInterval_lineedit->text().toInt() - ui->modbusDataPollingInterval_lineedit->text().toInt()*5 > 0)
            && ui->modbusDataPollingInterval_lineedit->isVisible() && ui->modbusReportInterval_lineedit->isVisible()){
        ui->modbusDataPollingInterval_lineedit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("The interval between Reporting Interval and Data Polling Interval should be small."));

        ui->modbusDataPollingInterval_lineedit->setFocus();
        return;
    }

    if(m_proName.at(3) == '2'){
        if(ui->modbusTcpkeepAlive_lineedit->isVisible() && (ui->modbusTcpkeepAlive_lineedit->text().toInt()>30 || ui->modbusTcpkeepAlive_lineedit->text().toInt()<1)){
            ui->modbusTcpkeepAlive_lineedit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Valid Range：1-30."));

            return;
        }
    }else{
        if(ui->modbusTcpkeepAlive_lineedit->isVisible() && (ui->modbusTcpkeepAlive_lineedit->text().toInt()>120 || ui->modbusTcpkeepAlive_lineedit->text().toInt()<1)){
            ui->modbusTcpkeepAlive_lineedit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Valid Range：1-120."));

            return;
        }
    }

    if((ui->modbusHeartbeatInterval_lineEdit->text().isEmpty() || ui->modbusHeartbeatInterval_lineEdit->text().toInt()>3600 || ui->modbusHeartbeatInterval_lineEdit->text().toInt()<1) && ui->modbusHeartbeatInterval_lineEdit->isVisible()){
        ui->modbusHeartbeatInterval_lineEdit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("Valid Range：1-3600."));

        return;
    }
    if(ui->modbusMqttUserCreUsername_linEdit->isVisible() && ui->modbusMqttUserCreUsername_linEdit->isEnabled() && ui->modbusMqttUserCreUsername_linEdit->text().isEmpty()){
        ui->modbusMqttUserCreUsername_linEdit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("This field is required."));

        return;
    }
    if(ui->modbusMqttUserCrePwdlinEdit->isVisible() && ui->modbusMqttUserCrePwdlinEdit->isEnabled() && ui->modbusMqttUserCrePwdlinEdit->text().isEmpty()){
        ui->modbusMqttUserCrePwdlinEdit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("This field is required."));

        return;
    }

    //NB for Aliyum
    if(m_dealThread->structSupportModel.nb){
        if(ui->modbusAliyunClientID_lineEdit->isVisible() && ui->modbusAliyunClientID_lineEdit->text().isEmpty()){
            showWarning(this,tr("Attention"),tr("Please enter Client ID."));

            return;
        }

        if(ui->modbusAliyunProductKey_lineEdit->isVisible() && ui->modbusAliyunProductKey_lineEdit->text().isEmpty()){
            showWarning(this,tr("Attention"),tr("Please enter Product Key."));

            return;
        }

        if(ui->modbusAliyunDeviceSecret_lineEdit->isVisible() && ui->modbusAliyunDeviceSecret_lineEdit->text().isEmpty()){
            showWarning(this,tr("Attention"),tr("Please enter Device Secret."));

            return;
        }

        if((ui->modbusAliyunKeepAliveInterval_lineEdit->text().toInt() > 3600 || ui->modbusAliyunKeepAliveInterval_lineEdit->text().toInt() < 1) && ui->modbusAliyunKeepAliveInterval_lineEdit->isVisible()){
            ui->modbusAliyunKeepAliveInterval_lineEdit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Valid Range：1-3600."));

            return;
        }
    }

    m_generalPageInfo.application_mode = ui->modbusApplicationMode_cbx->currentData().toInt();
    QVariantMap map;
    m_modbusReadIndex = UCXX52DealThread::MG_BASIC;
    map.insert("readIndex",UCXX52DealThread::MG_BASIC);
    map.insert("applicationMode",ui->modbusApplicationMode_cbx->currentData().toInt());
    map.insert("oldPwd",ui->modbusOldPwd_lineedit->text());
    map.insert("newPwd",ui->modbusNewPwd_lineedit->text());
    map.insert("reNewPwd",ui->modbusReNewPwd_lineedit->text());
    map.insert("networkType",ui->modbusNetworkType_cbx->currentData().toInt());
    map.insert("pinCode",ui->modbusPinNum_lineEdit->text().trimmed());
    map.insert("apn",ui->modbusApn_lineEdit->text().trimmed());
    map.insert("apnUser",ui->modbusAPNUser_lineEdit->text().trimmed());
    map.insert("apnPwd",ui->modbusAPNPwd_lineEdit->text().trimmed());

    if(m_generalPageInfo.application_mode == QunpUCXX52::APP_AZURE){
        map.insert("awsServerAddr",ui->modbusConnectStr_lineEdit->text().trimmed());
    }else{
        map.insert("awsServerAddr", ui->modbusAwsServerAddr_lineEdit->text());
    }

    map.insert("keepAliveInterval",ui->modbusKeepAliveInterval_lineedit->text());
    map.insert("reportingInterval",ui->modbusReportInterval_lineedit->text());
    map.insert("dataCollectInterval", ui->modbusDataPollingInterval_lineedit->text());
    map.insert("tcpKeepAlive",ui->modbusTcpkeepAlive_lineedit->text());
    map.insert("customHeartbeatMode",ui->modbusCustomHeartbeat_cb->isVisible()?ui->modbusCustomHeartbeat_cb->isChecked():false);
    map.insert("brokerAddr", ui->modbusBrokerAddr_lineEdit->text().trimmed());
    map.insert("brokerPort", ui->modbusBrokerPort_lineEdit->text().trimmed());
    map.insert("clientID", ui->modbusClientID_lineEdit->text().trimmed());
    map.insert("connectTimeout", ui->modbusConnectTimeout_lineEdit->text().trimmed());
    map.insert("mqttKeepAliveInterval",ui->modbusMqttKeepAliveInterval_lineEdit->text().trimmed());
    map.insert("customContent",ui->modbusCustomContent_lineEdit->text().trimmed());
    map.insert("heartbeatInterval", ui->modbusHeartbeatInterval_lineEdit->text().trimmed());
    map.insert("requireResponse",ui->modbusRequireResponse_cb->isVisible()?ui->modbusRequireResponse_cb->isChecked():false);
    map.insert("responseContent", ui->modbusResponseContent_lineEdit->text().trimmed());
    map.insert("mqttTlsEnable",ui->modbusMqttTlsEnable_cb->isChecked());
    map.insert("mqttUserCre",ui->modbusMqttUserCreEnable_cb->isChecked());
    map.insert("mqttUsername",ui->modbusMqttUserCreUsername_linEdit->text().trimmed());
    map.insert("mqttPwd",ui->modbusMqttUserCrePwdlinEdit->text().trimmed());

    //35xx for NB Aliyum
    map.insert("aliyunClientID",ui->modbusAliyunClientID_lineEdit->text().trimmed());
    map.insert("aliyunProductKey",ui->modbusAliyunProductKey_lineEdit->text().trimmed());
    map.insert("aliyunDeviceSecret",ui->modbusAliyunDeviceSecret_lineEdit->text().trimmed());
    map.insert("aliyunKeepAliveInterval",ui->modbusAliyunKeepAliveInterval_lineEdit->text().trimmed());
    map.insert("aliyunQoS",ui->modbusAliyunQoS_cbx->currentText());

    //gpio
    m_generalPageInfo.gpioType = ui->modbusGpioType_cbx->currentIndex();
    map.insert("gpioCounter1Enable",ui->modbusGpioType_cbx->currentIndex() == 0 ? 4:3);
#ifdef ODM_LHR_AZURE
    map.insert("authMode",ui->modbusAzureMode_cbx->currentIndex());
#endif
    //onenet
    map.insert("oneNetProductID",ui->modbusProductID_lineedit->text().trimmed());
    map.insert("oneNetKey",ui->modbusOneNetKey_lineEdit->text().trimmed());
    map.insert("oneNetKeepAlive",ui->modbusOneNetKeepAlive_lineEdit->text().trimmed());

    if(m_statusPageInfo.ucpVer >= 0x13){
        map.insert("serverAddr1",ui->modbusServerAddr1_lineedit->text().trimmed().isEmpty()?"":ui->modbusServerAddr1_lineedit->text().trimmed());
        map.insert("serverAddr2",ui->modbusServerAddr2_lineedit->text().trimmed().isEmpty()?"":ui->modbusServerAddr2_lineedit->text().trimmed());
    }else{
        map.insert("serverAddr1",ui->modbusServerAddr1_lineedit->text().trimmed().isEmpty()?"0.0.0.0":ui->modbusServerAddr1_lineedit->text().trimmed());
        map.insert("serverAddr2",ui->modbusServerAddr2_lineedit->text().trimmed().isEmpty()?"0.0.0.0":ui->modbusServerAddr2_lineedit->text().trimmed());
    }
    map.insert("serverPort1",ui->modbusServerPort1_lineedit->text().trimmed().isEmpty()?"0":ui->modbusServerPort1_lineedit->text().trimmed());
    map.insert("serverPort2",ui->modbusServerPort2_lineedit->text().trimmed().isEmpty()?"0":ui->modbusServerPort2_lineedit->text().trimmed());

    QVariantList list;
    list.append(map);

    emit requestToDevice(UCXX52DealThread::CONFIG_WRITE_GENERAL,list);
    m_generalPageInfo.application_mode = ui->modbusApplicationMode_cbx->currentData().toInt();
    if(ui->modbusApplicationMode_cbx->currentData().toInt() == QunpUCXX52::APP_AWS ||
            ui->modbusApplicationMode_cbx->currentData().toInt() == QunpUCXX52::APP_AZURE){
        ui->modbusAwsCAFile_frame->setEnabled(true);
        ui->modbusAwsCliCerFile_frame->setEnabled(true);
        ui->modbusAwsCliKeyFile_frame->setEnabled(true);

        ui->modbusMqttTlsCAFile_frame->setEnabled(false);
        ui->modbusMqttTlsCliCerFile_frame->setEnabled(false);
        ui->modbusMqttTlsCliKeyFile_frame->setEnabled(false);
    }else if(ui->modbusApplicationMode_cbx->currentData().toInt() == QunpUCXX52::APP_MQTT){
        ui->modbusAwsCAFile_frame->setEnabled(false);
        ui->modbusAwsCliCerFile_frame->setEnabled(false);
        ui->modbusAwsCliKeyFile_frame->setEnabled(false);

        ui->modbusMqttTlsCAFile_frame->setEnabled(true);
        ui->modbusMqttTlsCliCerFile_frame->setEnabled(true);
        ui->modbusMqttTlsCliKeyFile_frame->setEnabled(true);

        on_modbusMqttTlsEnable_cb_clicked(ui->modbusMqttTlsEnable_cb->isChecked());
    }else{
        ui->modbusAwsCAFile_frame->setEnabled(false);
        ui->modbusAwsCliCerFile_frame->setEnabled(false);
        ui->modbusAwsCliKeyFile_frame->setEnabled(false);

        ui->modbusMqttTlsCAFile_frame->setEnabled(false);
        ui->modbusMqttTlsCliCerFile_frame->setEnabled(false);
        ui->modbusMqttTlsCliKeyFile_frame->setEnabled(false);
    }

    if(!ui->modbusAwsCAFile_lineEdit->text().isEmpty() || !ui->modbusMqttTlsCAFile_lineEdit->text().isEmpty()){
        ui->modbusAwsCADelFile_btn->setEnabled(true);
        ui->modbusMqttTlsCADelFile_btn->setEnabled(true);
    }
    if(!ui->modbusAwsCliCerFile_lineEdit->text().isEmpty() || !ui->modbusMqttTlsCliCerFile_lineEdit->text().isEmpty()){
        ui->modbusAwsCliCerDelFile_btn->setEnabled(true);
        ui->modbusMqttTlsCliCerDelFile_btn->setEnabled(true);
    }
    if(!ui->modbusAwsCliKeyFile_lineEdit->text().isEmpty() || !ui->modbusMqttTlsCliKeyFile_lineEdit->text().isEmpty()){
        ui->modbusAwsCliKeyDelFile_btn->setEnabled(true);
        ui->modbusMqttTlsCliKeyDelFile_btn->setEnabled(true);
    }

    if(ui->modbusApplicationMode_cbx->currentData().toInt() == QunpUCXX52::APP_URSALINK_CLOUD){
        for(int qq=0; qq<modbusChannelQuantityList.size(); qq++){
            modbusChannelQuantityList.at(qq)->setEnabled(false);
        }
    }else{
        for(int qq=0; qq<modbusChannelQuantityList.size(); qq++){
            modbusChannelQuantityList.at(qq)->setEnabled(true);
        }
    }
}

/**
 * RS485 保存窗口
 * @brief UCXX52Model::on_rs485Save_btn_clicked
 */
void UCXX52Model::on_rs485Save_btn_clicked()
{
    ui->rs485BridgePort_lineedit->setStyleSheet(RECOVERY_INPUT);
    qDebug()<<ui->rs485Databit_cbx->currentData()<<ui->rs485Stopbit_cbx->currentData();
    if((ui->rs485BridgePort_lineedit->text().toInt()<2 || ui->rs485BridgePort_lineedit->text().toInt()>223 || ui->rs485BridgePort_lineedit->text().toInt()==85) && ui->rs485BridgePort_lineedit->isVisible()){
        ui->rs485BridgePort_lineedit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("Port Range: 2-84,86-223."));

        return;
    }

    QVariantMap map;
    m_modbusReadIndex = UCXX52DealThread::MG_RS485;
    map.insert("readIndex",UCXX52DealThread::MG_RS485);
    map.insert("enable",ui->rs485Enabel_cb->isChecked()?"1":"0");
    map.insert("baudrate",ui->rs485BaudRate_cbx->currentText());
    map.insert("databits",ui->rs485Databit_cbx->currentData().toString());
    map.insert("stopbits",ui->rs485Stopbit_cbx->currentData().toString());
    map.insert("parity",ui->rs485Parity_cbx->currentData().toString());
    map.insert("bridgeLoraWanEnable",ui->rs485Bridge_cb->isChecked()?"1":"0");
    map.insert("bridgeLoraWanPort",ui->rs485BridgePort_lineedit->text());

    QVariantList list;
    list.append(map);

    emit requestToDevice(UCXX52DealThread::CONFIG_WRITE_GENERAL,list);
}

/**
 * RS232 保存窗口
 * @brief UCXX52Model::on_rs232Save_btn_clicked
 */
void UCXX52Model::on_rs232Save_btn_clicked()
{
    ui->rs232ListenPort_lineeedit->setStyleSheet(RECOVERY_INPUT);
    ui->rs232KeepAliveInterval_lineeedit->setStyleSheet(RECOVERY_INPUT);
    ui->rs232KeppAliveRetryTimes_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->rs232PacketLength_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->rs232SerialFrameInterval_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->rs232ReconnectInterval_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->rs232ServerAddr1_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->rs232ServerPort1_lineedit->setStyleSheet(RECOVERY_INPUT);

    if(ui->rs232Enable_cb->isChecked()){
        if(ui->rs232Protocol_cbx->currentIndex() == QunpUCXX52::SERIAL_TCP){
            if((ui->rs232KeepAliveInterval_lineeedit->text().toInt()<1 || ui->rs232KeepAliveInterval_lineeedit->text().toInt()>120) && ui->rs232KeepAliveInterval_lineeedit->isVisible()){
                ui->rs232KeepAliveInterval_lineeedit->setStyleSheet(ERROR_INPUT);
                showWarning(this,tr("Attention"),tr("Valid Range：1-120."));

                return;
            }
            if((ui->rs232KeppAliveRetryTimes_lineedit->text().toInt()<3 || ui->rs232KeppAliveRetryTimes_lineedit->text().toInt() > 10) && ui->rs232KeppAliveRetryTimes_lineedit->isVisible()){
                ui->rs232KeppAliveRetryTimes_lineedit->setStyleSheet(ERROR_INPUT);
                showWarning(this,tr("Attention"),tr("Valid Range：3-10."));

                return;
            }
        }
        if((ui->rs232ListenPort_lineeedit->text().toInt()<1 || ui->rs232ListenPort_lineeedit->text().toInt()>65535) && ui->rs232ListenPort_lineeedit->isVisible()){
            ui->rs232ListenPort_lineeedit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Valid Range：1-65535."));

            return;
        }
        if((ui->rs232PacketLength_lineedit->text().toInt()<1 || ui->rs232PacketLength_lineedit->text().toInt()>1024) && ui->rs232PacketLength_lineedit->isVisible()){
            ui->rs232PacketLength_lineedit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Valid Range：1-1024."));

            return;
        }
        if((ui->rs232SerialFrameInterval_lineedit->text().toInt()<10 || ui->rs232SerialFrameInterval_lineedit->text().toInt()>65535) && ui->rs232SerialFrameInterval_lineedit->isVisible()){
            ui->rs232SerialFrameInterval_lineedit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Valid Range：10-65535."));

            return;
        }
        if((ui->rs232ReconnectInterval_lineedit->text().toInt()<10 || ui->rs232ReconnectInterval_lineedit->text().toInt()>60) && ui->rs232ReconnectInterval_lineedit->isVisible()){
            ui->rs232ReconnectInterval_lineedit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Valid Range：10-60."));

            return;
        }
        if(ui->rs232ServerAddr1_lineedit->text().isEmpty() && ui->rs232ServerAddr1_lineedit->isVisible()){
            ui->rs232ServerAddr1_lineedit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Please add at least one destination IP addresses."));

            return;
        }
        if(ui->rs232ServerPort1_lineedit->text().isEmpty() && ui->rs232ServerPort1_lineedit->isVisible()){
            ui->rs232ServerPort1_lineedit->setStyleSheet(ERROR_INPUT);
            return;
        }
    }

    ui->rs232KeepAliveInterval_lineeedit->setStyleSheet(RECOVERY_INPUT);
    ui->rs232KeppAliveRetryTimes_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->rs232PacketLength_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->rs232SerialFrameInterval_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->rs232ReconnectInterval_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->rs232ServerAddr1_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->rs232ServerPort1_lineedit->setStyleSheet(RECOVERY_INPUT);

    QVariantMap map;
    m_modbusReadIndex = UCXX52DealThread::MG_RS232;
    map.insert("readIndex",UCXX52DealThread::MG_RS232);
    map.insert("enable",ui->rs232Enable_cb->isChecked()?"1":"0");
    map.insert("baudrate",ui->rs232BaudRate_cbx->currentText());
    map.insert("databits",ui->rs232Databit_cbx->currentData().toString());
    map.insert("stopbits",ui->rs232Stopbit_cbx->currentData().toString());
    map.insert("parity",ui->rs232Parity_cbx->currentData().toString());
    map.insert("protocol",ui->rs232Protocol_cbx->currentData().toInt());

    map.insert("keepAliveInterval",ui->rs232KeepAliveInterval_lineeedit->text().toInt());
    map.insert("keppAliveRetryTimes",ui->rs232KeppAliveRetryTimes_lineedit->text().trimmed());

    map.insert("packetLength",ui->rs232PacketLength_lineedit->text().trimmed());
    map.insert("frameInterval",ui->rs232SerialFrameInterval_lineedit->text().trimmed());
    map.insert("reconnectInterval",ui->rs232ReconnectInterval_lineedit->text().toInt());
    map.insert("registerString",ui->rs232RegisterString_lineedit->text().trimmed());

    map.insert("linstenPort",ui->rs232ListenPort_lineeedit->text().trimmed());

    if(m_statusPageInfo.ucpVer >= 0x13){
        map.insert("serverAddr1",ui->rs232ServerAddr1_lineedit->text().trimmed().isEmpty() || !ui->destIpAddr_frame->isVisible()?"":ui->rs232ServerAddr1_lineedit->text().trimmed());
        map.insert("serverAddr2",ui->rs232ServerAddr2_lineedit->text().trimmed().isEmpty() || !ui->destIpAddr_frame->isVisible()?"":ui->rs232ServerAddr2_lineedit->text().trimmed());
    }else{
        map.insert("serverAddr1",ui->rs232ServerAddr1_lineedit->text().trimmed().isEmpty() || !ui->destIpAddr_frame->isVisible()?"0.0.0.0":ui->rs232ServerAddr1_lineedit->text().trimmed());
        map.insert("serverAddr2",ui->rs232ServerAddr2_lineedit->text().trimmed().isEmpty() || !ui->destIpAddr_frame->isVisible()?"0.0.0.0":ui->rs232ServerAddr2_lineedit->text().trimmed());
    }

    map.insert("serverPort1",ui->rs232ServerPort1_lineedit->text().trimmed().isEmpty() || !ui->destIpAddr_frame->isVisible()?"0":ui->rs232ServerPort1_lineedit->text().trimmed());
    map.insert("serverPort2",ui->rs232ServerPort2_lineedit->text().trimmed().isEmpty() || !ui->destIpAddr_frame->isVisible()?"0":ui->rs232ServerPort2_lineedit->text().trimmed());

    QVariantList list;
    list.append(map);
    emit requestToDevice(UCXX52DealThread::CONFIG_WRITE_GENERAL,list);

}

void UCXX52Model::on_modbusMqttUserCreEnable_cb_clicked(bool checked)
{
    ui->modbusMqttUserCreUsername_frame->setEnabled(checked);
    ui->modbusMqttUserCrePwd_frame->setEnabled(checked);
}

void UCXX52Model::on_modbusMqttTlsEnable_cb_clicked(bool checked)
{
    if(m_generalPageInfo.application_mode == QunpUCXX52::APP_MQTT){
        ui->modbusMqttTlsCAFile_frame->setEnabled(checked);
        ui->modbusMqttTlsCliCerFile_frame->setEnabled(checked);
        ui->modbusMqttTlsCliKeyFile_frame->setEnabled(checked);
    }
}


/**
 * CA File 游览
 * @brief UCXX52Model::on_modbusAwsCASelectFile_btn_clicked
 */
void UCXX52Model::on_modbusAwsCASelectFile_btn_clicked()
{
    QString extFileName = QFileDialog::getOpenFileName(this, tr("choise CA file"), m_caFilePath, tr("File (*.pem *.crt);; File(*.*)"));
    if(!extFileName.isEmpty()){
       QSettings settings(m_iniPath, QSettings::IniFormat);
       settings.beginGroup("ImageFilePath");
       settings.setValue("caFilePath",extFileName.left(extFileName.lastIndexOf('/')));
       settings.endGroup();

       ui->modbusAwsCAFile_lineEdit->setText(extFileName);
       ui->modbusAwsCAImportFile_btn->setEnabled(true);

       ui->modbusMqttTlsCAFile_lineEdit->setText(extFileName);
       ui->modbusMqttTlsCAImportFile_btn->setEnabled(true);

       m_bcaFileBrowse = true;
    }else{
        m_bcaFileBrowse = false;
    }
}
/**
 * CA 导入
 * @brief UCXX52Model::on_modbusAwsCAImportFile_btn_clicked
 */
void UCXX52Model::on_modbusAwsCAImportFile_btn_clicked()
{
    QVariantMap map;
    map.insert("fileType","CA");
    map.insert("delete",false);
    map.insert("caFilePath",ui->modbusAwsCAFile_lineEdit->text().trimmed());
    QVariantList list;
    list.append(map);

    ui->modbusAwsCADelFile_btn->setEnabled(true);
    ui->modbusAwsCAImportFile_btn->setEnabled(false);

    ui->modbusMqttTlsCADelFile_btn->setEnabled(true);
    ui->modbusMqttTlsCAImportFile_btn->setEnabled(false);

    if(m_bcaFileBrowse)
        emit requestToDevice(UCXX52DealThread::CONFIG_IMPORT_AWS_FILE,list);

    m_bcaFileBrowse = false;
}
/**
 * CA 删除
 * @brief UCXX52Model::on_modbusAwsCADelFile_btn_clicked
 */
void UCXX52Model::on_modbusAwsCADelFile_btn_clicked()
{
    QVariantMap map;
    map.insert("fileType","CA");
    map.insert("delete",true);
    ui->modbusAwsCAFile_lineEdit->clear();
    QVariantList list;
    list.append(map);

    ui->modbusAwsCAImportFile_btn->setEnabled(false);
    ui->modbusAwsCADelFile_btn->setEnabled(false);
    ui->modbusAwsCAFile_lineEdit->clear();

    ui->modbusMqttTlsCAImportFile_btn->setEnabled(false);
    ui->modbusMqttTlsCADelFile_btn->setEnabled(false);
    ui->modbusMqttTlsCAFile_lineEdit->clear();
    emit requestToDevice(UCXX52DealThread::CONFIG_IMPORT_AWS_FILE,list);
}

/**
 * 设备证书选择
 * @brief UCXX52Model::on_modbusAwsCliCerSelectFile_btn_clicked
 */
void UCXX52Model::on_modbusAwsCliCerSelectFile_btn_clicked()
{
#ifdef ODM_LHR_AZURE
    QString extFileName = QFileDialog::getOpenFileName(this, tr("Choise CA File"), m_cliCerFilePath, tr("File (*.pem *.crt);; File(*.*)"));
#else
    QString extFileName = QFileDialog::getOpenFileName(this, tr("Choise CA File"), m_cliCerFilePath, tr("File (*.crt);; File(*.*)"));
#endif
    if(!extFileName.isEmpty()){
       QSettings settings(m_iniPath, QSettings::IniFormat);
       settings.beginGroup("ImageFilePath");
       settings.setValue("cliCerFilePath",extFileName.left(extFileName.lastIndexOf('/')));
       settings.endGroup();

       ui->modbusAwsCliCerFile_lineEdit->setText(extFileName);
       ui->modbusAwsCliCerImportFile_btn->setEnabled(true);

       ui->modbusMqttTlsCliCerFile_lineEdit->setText(extFileName);
       ui->modbusMqttTlsCliCerImportFile_btn->setEnabled(true);

       m_bclientFileBrowse = true;
    }else{
       m_bclientFileBrowse = false;
    }
}

/**
 * 设备证书导入
 * @brief UCXX52Model::on_modbusAwsCliCerImportFile_btn_clicked
 */
void UCXX52Model::on_modbusAwsCliCerImportFile_btn_clicked()
{
    QVariantMap map;
    map.insert("fileType","Client Certificate");
    map.insert("delete",false);
    map.insert("cliCerFilePath",ui->modbusAwsCliCerFile_lineEdit->text().trimmed());
    QVariantList list;
    list.append(map);

    if(m_bclientFileBrowse)
        emit requestToDevice(UCXX52DealThread::CONFIG_IMPORT_AWS_FILE,list);

    ui->modbusAwsCliCerDelFile_btn->setEnabled(true);
    ui->modbusAwsCliCerImportFile_btn->setEnabled(false);

    ui->modbusMqttTlsCliCerDelFile_btn->setEnabled(true);
    ui->modbusMqttTlsCliCerImportFile_btn->setEnabled(false);

    m_bclientFileBrowse = false;
}

/**
 * 设备证书删除
 * @brief UCXX52Model::on_modbusAwsCliCerDelFile_btn_clicked
 */
void UCXX52Model::on_modbusAwsCliCerDelFile_btn_clicked()
{
    QVariantMap map;
    map.insert("fileType","Client Certificate");
    map.insert("delete",true);
    ui->modbusAwsCliCerFile_lineEdit->clear();
    QVariantList list;
    list.append(map);
    emit requestToDevice(UCXX52DealThread::CONFIG_IMPORT_AWS_FILE,list);

    ui->modbusAwsCliCerImportFile_btn->setEnabled(false);
    ui->modbusAwsCliCerDelFile_btn->setEnabled(false);
    ui->modbusAwsCliCerFile_lineEdit->clear();

    ui->modbusMqttTlsCliCerImportFile_btn->setEnabled(false);
    ui->modbusMqttTlsCliCerDelFile_btn->setEnabled(false);
}

/**
 * 私钥选择
 * @brief UCXX52Model::on_modbusAwsCliKeySelectFile_btn_clicked
 */
void UCXX52Model::on_modbusAwsCliKeySelectFile_btn_clicked()
{
#ifdef ODM_LHR_AZURE
    QString extFileName = QFileDialog::getOpenFileName(this, tr("Choise Key File"), m_cliKeyFilePath, tr("File (*.pem *.key);; File(*.*)"));
#else
    QString extFileName = QFileDialog::getOpenFileName(this, tr("Choise Key File"), m_cliKeyFilePath, tr("File (*.key);; File(*.*)"));
#endif

    if(!extFileName.isEmpty()){
       QSettings settings(m_iniPath, QSettings::IniFormat);
       settings.beginGroup("ImageFilePath");
       settings.setValue("cliKeyFilePath",extFileName.left(extFileName.lastIndexOf('/')));
       settings.endGroup();
       ui->modbusAwsCliKeyFile_lineEdit->setText(extFileName);
       ui->modbusMqttTlsCliKeyFile_lineEdit->setText(extFileName);

       ui->modbusAwsCliKeyImportFile_btn->setEnabled(true);
       ui->modbusMqttTlsCliKeyImportFile_btn->setEnabled(true);

       m_bclientKeyBrowse = true;
    }else{
        m_bclientKeyBrowse = false;
    }
}

/**
 * 私钥导入
 * @brief UCXX52Model::on_modbusAwsCliKeyImportFile_btn_clicked
 */
void UCXX52Model::on_modbusAwsCliKeyImportFile_btn_clicked()
{
    QVariantMap map;
    map.insert("fileType","Client Key");
    map.insert("delete",false);
    map.insert("cliKeyFilePath",ui->modbusAwsCliKeyFile_lineEdit->text().trimmed());
    QVariantList list;
    list.append(map);

    if(m_bclientKeyBrowse)
        emit requestToDevice(UCXX52DealThread::CONFIG_IMPORT_AWS_FILE,list);

    ui->modbusAwsCliKeyDelFile_btn->setEnabled(true);
    ui->modbusAwsCliKeyImportFile_btn->setEnabled(false);

    ui->modbusMqttTlsCliKeyDelFile_btn->setEnabled(true);
    ui->modbusMqttTlsCliKeyImportFile_btn->setEnabled(false);

    m_bclientKeyBrowse = false;
}

/**
 * 私钥删除
 * @brief UCXX52Model::on_modbusAwsCliKeyDelFile_btn_clicked
 */
void UCXX52Model::on_modbusAwsCliKeyDelFile_btn_clicked()
{
    QVariantMap map;
    map.insert("fileType","Client Key");
    map.insert("delete",true);
    ui->modbusAwsCliKeyFile_lineEdit->clear();
    QVariantList list;
    list.append(map);
    emit requestToDevice(UCXX52DealThread::CONFIG_IMPORT_AWS_FILE,list);

    ui->modbusAwsCliKeyImportFile_btn->setEnabled(false);
    ui->modbusAwsCliKeyDelFile_btn->setEnabled(false);
    ui->modbusAwsCliKeyFile_lineEdit->clear();

    ui->modbusMqttTlsCliKeyImportFile_btn->setEnabled(false);
    ui->modbusMqttTlsCliKeyDelFile_btn->setEnabled(false);
    ui->modbusMqttTlsCliKeyFile_lineEdit->clear();


}


/**
 * 11xx GPIO counter1 功能
 * @brief UCXX52Model::on_modbusGpioType_cbx_currentIndexChanged
 * @param index
 */
void UCXX52Model::on_modbusGpioType_cbx_currentIndexChanged(int index)
{
    qDebug()<<m_generalPageInfo.gpioType<<index;
    ui->modbusGpioCounter_frame->setVisible(index == 1);
    if(m_generalPageInfo.gpioType.toInt() == 1 && index == 0){
        if(showQuestion(this,tr("Attention"),MyMessageBox::TYPE_NONE,tr("If the counter is selected, the related commands for setting DI will be invalid and cleared, please confirm.")) != QMessageBox::Ok){
            disconnect(ui->modbusGpioType_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_modbusGpioType_cbx_currentIndexChanged(int)));
            ui->modbusGpioType_cbx->setCurrentIndex(1);
            ui->modbusGpioCounter_frame->setVisible(true);
            connect(ui->modbusGpioType_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_modbusGpioType_cbx_currentIndexChanged(int)));
        }
    }else if(m_generalPageInfo.gpioType.toInt() == 0 && index == 1){

        if(showQuestion(this,tr("Attention"),MyMessageBox::TYPE_NONE,tr("If the counter is selected, the related commands for setting DI will be invalid and cleared, please confirm.")) != QMessageBox::Ok){
            disconnect(ui->modbusGpioType_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_modbusGpioType_cbx_currentIndexChanged(int)));
            ui->modbusGpioType_cbx->setCurrentIndex(0);
            ui->modbusGpioCounter_frame->setVisible(false);
            connect(ui->modbusGpioType_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_modbusGpioType_cbx_currentIndexChanged(int)));
        }
    }

}

/**
 * 1114 1122 开始计数
 * @brief UCXX52Model::on_gpioCounterStart_btn_clicked
 */
void UCXX52Model::on_modbusGpioCounterStart_btn_clicked()
{
    QVariantMap map;
    map.insert("readType",UCXX52DealThread::RNS_GPIO2_COUNTER_START);
    map.insert("start",ui->modbusGpioCounterStart_btn->text().contains(tr("Start"))?2:1);
    map.insert("counterNum",1);
    QVariantList list;
    list.append(map);

    ui->modbusGpioCounterStart_btn->setEnabled(false);
    ui->modbusGpioCounterRefresh_btn->setEnabled(false);
    ui->modbusGpioCounterClear_btn->setEnabled(false);

    emit requestToDevice(UCXX52DealThread::CONFIG_READ_GENERAL_SPECIAL,list);
}

/**
 * 1114 1122 刷新
 * @brief UCXX52Model::on_gpioCounterRefresh_btn_clicked
 */
void UCXX52Model::on_modbusGpioCounterRefresh_btn_clicked()
{
    QVariantMap map;
    map.insert("readType",UCXX52DealThread::RNS_GPIO2_COUNTER_REFRESH);
    map.insert("counterNum",1);
    QVariantList list;
    list.append(map);

    ui->modbusGpioCounterStart_btn->setEnabled(false);
    ui->modbusGpioCounterRefresh_btn->setEnabled(false);
    ui->modbusGpioCounterClear_btn->setEnabled(false);

    emit requestToDevice(UCXX52DealThread::CONFIG_READ_GENERAL_SPECIAL,list);
}

/**
 * 1114 1122 清空
 * @brief UCXX52Model::on_gpioCounterClear_btn_clicked
 */
void UCXX52Model::on_modbusGpioCounterClear_btn_clicked()
{
    QVariantMap map;
    map.insert("readType",UCXX52DealThread::RNS_GPIO2_COUNTER_CLEAR);
    map.insert("counterNum",1);
    QVariantList list;
    list.append(map);

    ui->modbusGpioCounterStart_btn->setEnabled(false);
    ui->modbusGpioCounterRefresh_btn->setEnabled(false);
    ui->modbusGpioCounterClear_btn->setEnabled(false);

    emit requestToDevice(UCXX52DealThread::CONFIG_READ_GENERAL_SPECIAL,list);
}


/**
 * ODM Azure的模式下 选择
 * @brief UCXX52Model::on_modbusAzureMode_cbx_currentIndexChanged
 * @param index
 */
void UCXX52Model::on_modbusAzureMode_cbx_currentIndexChanged(int index)
{
    ui->modbusConnectStr_lineEdit->clear();
    if(index == 0){//SAS模式
        ui->modbusConnectStr_frame->setVisible(true);
        ui->modbusAwsCAFile_frame->setVisible(false);
        ui->modbusAwsCliCerFile_frame->setVisible(false);
        ui->modbusAwsCliKeyFile_frame->setVisible(false);
        ui->connectStrTip->setVisible(false);
    }else if(index == 1){// Certificates(X.509)模式
        ui->modbusConnectStr_frame->setVisible(true);
        ui->modbusAwsCAFile_frame->setVisible(true);
        ui->modbusAwsCliCerFile_frame->setVisible(true);
        ui->modbusAwsCliKeyFile_frame->setVisible(true);
        ui->connectStrTip->setVisible(true);
    }
}
