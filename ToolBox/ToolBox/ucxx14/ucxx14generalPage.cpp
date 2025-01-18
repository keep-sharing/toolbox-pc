#include "ucxx14model.h"
#include "ui_ucxx14model.h"

void UCXX14Model::onRecvGeneral(UCXX14DealThread::StructPageGeneral info)
{
    if(info.readSpecial == 9999){
        qDebug()<<info.readSpecialType<<info.counterNum<<info.gpioCounter;
        switch (info.readSpecialType) {
        case UCXX14DealThread::RNS_GPIO2_COUNTER_START:{
            if(info.counterNum == 1){
                if(ui->gpioCounterStart_btn->text().contains(tr("Start"))){
                    ui->gpioCounterStart_btn->setText(tr("Stop"));
                }else{
                    ui->gpioCounterStart_btn->setText(tr("Start"));
                }
                ui->gpioCounterRefresh_btn->setEnabled(true);
                ui->gpioCounterStart_btn->setEnabled(true);
                ui->gpioCounterClear_btn->setEnabled(true);

            }else{
                if(ui->gpioCounterStart2_btn->text().contains(tr("Start"))){
                    ui->gpioCounterStart2_btn->setText(tr("Stop"));
                }else{
                    ui->gpioCounterStart2_btn->setText(tr("Start"));
                }
                ui->gpioCounterRefresh2_btn->setEnabled(true);
                ui->gpioCounterStart2_btn->setEnabled(true);
                ui->gpioCounterClear2_btn->setEnabled(true);
            }

        }
            break;
        case UCXX14DealThread::RNS_GPIO2_COUNTER_REFRESH:{
            if(info.counterNum == 1){
                if(info.gpioCounterStart.toInt() == 1){
                    ui->gpioCounterStart_btn->setText(tr("Stop"));
                }else{
                    ui->gpioCounterStart_btn->setText(tr("Start"));
                }
//                n1GpioCounterAnimation->start();
                ui->gpioCounter_lineedit->setText(info.gpioCounter);
                ui->gpioCounterRefresh_btn->setEnabled(true);
                ui->gpioCounterStart_btn->setEnabled(true);
                ui->gpioCounterClear_btn->setEnabled(true);

            }else{
                if(info.gpioCounterStart.toInt() == 1){
                    ui->gpioCounterStart2_btn->setText(tr("Stop"));
                }else{
                    ui->gpioCounterStart2_btn->setText(tr("Start"));
                }
                ui->gpioCounter2_lineedit->setText(info.gpioCounter);
//                n1GpioCounterAnimation2->start();
                ui->gpioCounterRefresh2_btn->setEnabled(true);
                ui->gpioCounterStart2_btn->setEnabled(true);
                ui->gpioCounterClear2_btn->setEnabled(true);
            }

        }
            break;
        case UCXX14DealThread::RNS_GPIO2_COUNTER_CLEAR:{
            if(info.counterNum == 1){
                if(info.gpioCounterStart.toInt() == 1){
                    ui->gpioCounterStart_btn->setText(tr("Stop"));
                }else{
                    ui->gpioCounterStart_btn->setText(tr("Start"));
                }
                ui->gpioCounter_lineedit->setText(info.gpioCounter);
                ui->gpioCounterRefresh_btn->setEnabled(true);
                ui->gpioCounterStart_btn->setEnabled(true);
                ui->gpioCounterClear_btn->setEnabled(true);

            }else{
                if(info.gpioCounterStart.toInt() == 1){
                    ui->gpioCounterStart2_btn->setText(tr("Stop"));
                }else{
                    ui->gpioCounterStart2_btn->setText(tr("Start"));
                }
                ui->gpioCounter2_lineedit->setText(info.gpioCounter);
                ui->gpioCounterRefresh2_btn->setEnabled(true);
                ui->gpioCounterStart2_btn->setEnabled(true);
                ui->gpioCounterClear2_btn->setEnabled(true);
            }
        }
            break;
        default:
            break;
        }
        emit waitingVisible(false);
        return;
    }

    on_changePwd_cb_clicked(false);

    m_generalPageInfo = info;


    if(m_dealThread->structSupportModel.cloud){
        ui->cloudMode_frame->setVisible(true);
        ui->generalKeepAliveInterval_frame->setVisible(true);
        ui->generalReportingIntl_frame->setVisible(true);
        if(info.application_mode == QunpUCXX14::APP_NONE){
            ui->cloudApplicationMode_cbx->setCurrentIndex(ui->cloudApplicationMode_cbx->findData(QunpUCXX14::APP_NONE));
            on_cloudApplicationMode_cbx_currentIndexChanged(QunpUCXX14::APP_NONE);

        }else if(info.application_mode == QunpUCXX14::APP_URSALINK_CLOUD){
            ui->cloudApplicationMode_cbx->setCurrentIndex(ui->cloudApplicationMode_cbx->findData(QunpUCXX14::APP_URSALINK_CLOUD));
            on_cloudApplicationMode_cbx_currentIndexChanged(QunpUCXX14::APP_URSALINK_CLOUD);

            ui->awsCAFile_frame->setEnabled(false);
            ui->awsCliCerFile_frame->setEnabled(false);
            ui->awsCliKeyFile_frame->setEnabled(false);
            ui->mqttTlsCAFile_frame->setEnabled(false);
            ui->mqttTlsCliCerFile_frame->setEnabled(false);
            ui->mqttTlsCliKeyFile_frame->setEnabled(false);
        }else if(info.application_mode == QunpUCXX14::APP_AWS){
            ui->cloudApplicationMode_cbx->setCurrentIndex(ui->cloudApplicationMode_cbx->findData(QunpUCXX14::APP_AWS));
            on_cloudApplicationMode_cbx_currentIndexChanged(QunpUCXX14::APP_AWS);
            ui->awsServerAddr_lineEdit->setText(info.serverAddr);

            ui->awsCAFile_frame->setEnabled(true);
            ui->awsCliCerFile_frame->setEnabled(true);
            ui->awsCliKeyFile_frame->setEnabled(true);

            ui->mqttTlsCAFile_frame->setEnabled(false);
            ui->mqttTlsCliCerFile_frame->setEnabled(false);
            ui->mqttTlsCliKeyFile_frame->setEnabled(false);
        }else if(info.application_mode == QunpUCXX14::APP_TCP){
            ui->cloudApplicationMode_cbx->setCurrentIndex(ui->cloudApplicationMode_cbx->findData(QunpUCXX14::APP_TCP));
            on_cloudApplicationMode_cbx_currentIndexChanged(QunpUCXX14::APP_TCP);

            ui->awsCAFile_frame->setEnabled(false);
            ui->awsCliCerFile_frame->setEnabled(false);
            ui->awsCliKeyFile_frame->setEnabled(false);
            ui->mqttTlsCAFile_frame->setEnabled(false);
            ui->mqttTlsCliCerFile_frame->setEnabled(false);
            ui->mqttTlsCliKeyFile_frame->setEnabled(false);
        }else if(info.application_mode == QunpUCXX14::APP_UDP){
            ui->cloudApplicationMode_cbx->setCurrentIndex(ui->cloudApplicationMode_cbx->findData(QunpUCXX14::APP_UDP));
            on_cloudApplicationMode_cbx_currentIndexChanged(QunpUCXX14::APP_UDP);

            ui->awsCAFile_frame->setEnabled(false);
            ui->awsCliCerFile_frame->setEnabled(false);
            ui->awsCliKeyFile_frame->setEnabled(false);
            ui->mqttTlsCAFile_frame->setEnabled(false);
            ui->mqttTlsCliCerFile_frame->setEnabled(false);
            ui->mqttTlsCliKeyFile_frame->setEnabled(false);
        }else if(info.application_mode == QunpUCXX14::APP_MQTT){
            ui->cloudApplicationMode_cbx->setCurrentIndex(ui->cloudApplicationMode_cbx->findData(QunpUCXX14::APP_MQTT));
            on_cloudApplicationMode_cbx_currentIndexChanged(QunpUCXX14::APP_MQTT);

            ui->awsCAFile_frame->setEnabled(false);
            ui->awsCliCerFile_frame->setEnabled(false);
            ui->awsCliKeyFile_frame->setEnabled(false);
            ui->mqttTlsCAFile_frame->setEnabled(true);
            ui->mqttTlsCliCerFile_frame->setEnabled(true);
            ui->mqttTlsCliKeyFile_frame->setEnabled(true);
        }else if(info.application_mode == QunpUCXX14::APP_ALI){
            ui->cloudApplicationMode_cbx->setCurrentIndex(ui->cloudApplicationMode_cbx->findData(QunpUCXX14::APP_ALI));
            on_cloudApplicationMode_cbx_currentIndexChanged(QunpUCXX14::APP_ALI);

            ui->awsCAFile_frame->setEnabled(false);
            ui->awsCliCerFile_frame->setEnabled(false);
            ui->awsCliKeyFile_frame->setEnabled(false);
            ui->mqttTlsCAFile_frame->setEnabled(false);
            ui->mqttTlsCliCerFile_frame->setEnabled(false);
            ui->mqttTlsCliKeyFile_frame->setEnabled(false);
        }else if(info.application_mode == QunpUCXX14::APP_ONENET){
            ui->cloudApplicationMode_cbx->setCurrentIndex(ui->cloudApplicationMode_cbx->findData(QunpUCXX14::APP_ONENET));
            on_cloudApplicationMode_cbx_currentIndexChanged(QunpUCXX14::APP_ONENET);

            ui->awsCAFile_frame->setEnabled(false);
            ui->awsCliCerFile_frame->setEnabled(false);
            ui->awsCliKeyFile_frame->setEnabled(false);
            ui->mqttTlsCAFile_frame->setEnabled(false);
            ui->mqttTlsCliCerFile_frame->setEnabled(false);
            ui->mqttTlsCliKeyFile_frame->setEnabled(false);
        }
    #ifdef ODM_LHR_AZURE
        else if(info.application_mode == QunpUCXX14::APP_AZURE){
            ui->cloudApplicationMode_cbx->setCurrentIndex(ui->cloudApplicationMode_cbx->findData(QunpUCXX14::APP_AZURE));
            on_cloudApplicationMode_cbx_currentIndexChanged(QunpUCXX14::APP_AZURE);

            ui->awsServerAddr_lineEdit->setText(info.serverAddr);

            ui->awsCAFile_frame->setEnabled(true);
            ui->awsCliCerFile_frame->setEnabled(true);
            ui->awsCliKeyFile_frame->setEnabled(true);

            ui->mqttTlsCAFile_frame->setEnabled(false);
            ui->mqttTlsCliCerFile_frame->setEnabled(false);
            ui->mqttTlsCliKeyFile_frame->setEnabled(false);
        }
        ui->azureMode_cbx->setCurrentIndex(info.authMode.toInt());
        on_azureMode_cbx_currentIndexChanged(info.authMode.toInt());
    #endif
        if(m_dealThread->structSupportModel.aws || m_dealThread->structSupportModel.data){
            //证书
            ui->awsCAFile_lineEdit->setText(info.caFile);
            ui->awsCliCerFile_lineEdit->setText(info.clientFile);
            ui->awsCliKeyFile_lineEdit->setText(info.clientKeyFile);

            ui->mqttTlsCAFile_lineEdit->setText(info.caFile);
            ui->mqttTlsCliCerFile_lineEdit->setText(info.clientFile);
            ui->mqttTlsCliKeyFile_lineEdit->setText(info.clientKeyFile);
        }

        ui->cloudKeepAliveInterval_lineedit->setText(QString::number(info.keepAliveInterval.toInt() ));
        ui->cloudReportInterval_lineedit->setText(QString::number(info.reportingInterval.toInt() ));
        ui->apn_lineEdit->setText(info.apn);
        ui->apnUser_lineEdit->setText(info.apnUser);
        ui->apnPwd_lineEdit->setText(info.apnPwd);
        ui->tcpkeepAlive_lineedit->setText(info.tcpkeepAlive);
        ui->brokerAddr_lineEdit->setText(info.brokerAddr);
        ui->brokerPort_lineEdit->setText(info.brokerPort);
        ui->clientID_lineEdit->setText(info.clientID);
        ui->connectTimeout_lineEdit->setText(info.connectTimeout);
        ui->mqttKeepAliveInterval_lineEdit->setText(info.mqttKeepAliveInterval);
        on_customHeartbeat_cb_clicked(info.customHeartbeat.toInt());
        ui->customContent_lineEdit->setText(info.customContent);
        ui->heartbeatInterval_lineEdit->setText(info.heartbeatInterval);
        on_requireResponse_cb_clicked(info.requireResponse.toInt());
        ui->responseContent_lineEdit->setText(info.responseContent);
        ui->serverAddr1_lineedit->setText(info.serverAddr1);
        ui->serverPort1_lineedit->setText(info.serverPort1);
        ui->serverAddr2_lineedit->setText(info.serverAddr2);
        ui->serverPort2_lineedit->setText(info.serverPort2);
        ui->mqttUserCreEnable_cb->setChecked(info.userCreEnable.toInt());
        on_mqttUserCreEnable_cb_clicked(info.userCreEnable.toInt());
        ui->mattUserCreUsername_linEdit->setText(info.userCreUsername);
        ui->mattUserCrePwdlinEdit->setText(info.userCrePwd);
        ui->mqttTlsEnable_cb->setChecked(info.tlsEnable.toInt());
        on_mqttTlsEnable_cb_clicked(info.tlsEnable.toInt());

        ui->networkType_cbx->setCurrentIndex(ui->networkType_cbx->findData(info.network_type));
        ui->pinNum_lineEdit->setText(info.pinCode);
    //    networkTypeIndex = ui->networkType_cbx->currentIndex();
        ui->dataPollInterval_lineEdit->setText(info.dataCollectInterval);

        ui->serverStatus1_label->setText(info.status1);
        ui->serverStatus2_label->setText(info.status2);

        ui->oneNetKeepAlive_lineEdit->setText(info.oneNetKeepAlive);
        ui->oneNetKey_lineEdit->setText(info.oneNetKey);
        ui->oneNetProductID_lineedit->setText(info.oneNetProductID);

        ui->serverStatus1_label->setStyleSheet(info.status1 == "Connected" ? TYPEFACE_GREEN:TYPEFACE_RED);
        ui->serverStatus2_label->setStyleSheet(info.status2 == "Connected" ? TYPEFACE_GREEN:TYPEFACE_RED);

        //NB for Aliyun
        ui->aliyunClientID_lineEdit->setText(info.aliClientID);
        ui->aliyunProductKey_lineEdit->setText(info.aliProductKey);
        ui->aliyunDeviceSecret_lineEdit->setText(info.aliDevSecret);
        ui->aliyunKeepAliveInterval_lineEdit->setText(info.aliKeepAilve);
        ui->aliyunQoS_cbx->setCurrentIndex(info.aliQos.toInt());

    }else{
        ui->awsServerAddr_frame->setVisible(false);
        ui->awsCAFile_frame->setVisible(false);
        ui->awsCliCerFile_frame->setVisible(false);
        ui->awsCliKeyFile_frame->setVisible(false);
        ui->cloudMode_frame->setVisible(false);
    }

    if(m_dealThread->structSupportModel.lora){
        on_cloudApplicationMode_cbx_currentIndexChanged(-1);
        disconnect(ui->gpioType_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_gpioType_cbx_currentIndexChanged(int)));
        ui->cloudReportInterval_lineedit->setText(info.reportingInterval);
        ui->gpioType_cbx->setCurrentIndex(info.gpioType.toInt());
        ui->gpioCounter_lineedit->setText(info.gpioType.toInt() == 0 ? "0":info.gpioCounter);
        ui->gpioCounterStart_btn->setText(info.gpioCounterStart.toInt() == 1 ? tr("Stop"):tr("Start"));
        ui->gpioCounter_frame->setVisible(info.gpioType.toInt() == 1);
        connect(ui->gpioType_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_gpioType_cbx_currentIndexChanged(int)));

        disconnect(ui->gpioType2_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_gpioType2_cbx_currentIndexChanged(int)));
        ui->gpioType2_cbx->setCurrentIndex(info.gpio2Type.toInt());
        ui->gpioCounter2_lineedit->setText(info.gpio2Type.toInt() == 0 ? "0":info.gpio2Counter);
        ui->gpioCounterStart2_btn->setText(info.gpio2CounterStart.toInt() == 1 ? tr("Stop"):tr("Start"));
        ui->gpioCounter2_frame->setVisible(info.gpio2Type.toInt() == 1);
        connect(ui->gpioType2_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_gpioType2_cbx_currentIndexChanged(int)));

    }
    if(!m_dealThread->structSupportModel.cloud){
        on_cloudApplicationMode_cbx_currentIndexChanged(-1);
    }

    emit waitingVisible(false);
}

/**
 * 修改密码
 * @brief UCXX14Model::on_changePwd_cb_clicked
 * @param checked
 */
void UCXX14Model::on_changePwd_cb_clicked(bool checked)
{
    ui->oldPwd_lineEdit->clear();
    ui->newPwd_lineEdit->clear();
    ui->reNewPwd_lineEdit->clear();
    ui->changePwd_frame->setVisible(checked);
}

/**
 * 上云版本模式变化
 * @brief UCXX14Model::on_cloudApplicationMode_cbx_currentIndexChanged
 * @param index
 */
void UCXX14Model::on_cloudApplicationMode_cbx_currentIndexChanged(int index)
{
    index = ui->cloudApplicationMode_cbx->currentData().toInt();
    qDebug()<<index;
    ui->awsServerAddr_frame->setVisible(false);
    ui->generalKeepAliveInterval_frame->setVisible(false);
    ui->generalReportingIntl_frame->setVisible(false);
    ui->dataPollInterval_frame->setVisible(false);

    ui->awsCAFile_frame->setVisible(false);
    ui->awsCliCerFile_frame->setVisible(false);
    ui->awsCliKeyFile_frame->setVisible(false);

    ui->tcpkeepAlive_frame->setVisible(false);
    ui->mqtt_frame->setVisible(false);
    ui->customHeartbeatCb_frame->setVisible(false);
    ui->customHeartbeat_frame->setVisible(false);
    ui->requireResponseCb_frame->setVisible(false);
    ui->responseContent_frame->setVisible(false);
    ui->tcpDestIpAddr_frame->setVisible(false);

    ui->mqttUserCre_gb->setVisible(false);
    ui->mqttTls_gb->setVisible(false);

    ui->aliyun_frame->setVisible(false);

    ui->azureMode_frame->setVisible(false);

    ui->oneNetKeepAlive_frame->setVisible(false);
    ui->oneNetProductID_frame->setVisible(false);
    ui->oneNetKey_frame->setVisible(false);
    if(index == QunpUCXX14::APP_NONE){
    }else if(index == QunpUCXX14::APP_URSALINK_CLOUD){
        ui->generalKeepAliveInterval_frame->setVisible(true);

    }else if(index == QunpUCXX14::APP_AWS ){
        ui->generalKeepAliveInterval_frame->setVisible(true);
        ui->generalReportingIntl_frame->setVisible(true);
        ui->awsServerAddr_frame->setVisible(true);
        ui->awsCAFile_frame->setVisible(true);
        ui->awsCliCerFile_frame->setVisible(true);
        ui->awsCliKeyFile_frame->setVisible(true);
//        ui->dataPollInterval_frame->setVisible(true);

    }else if(index == QunpUCXX14::APP_TCP){
        ui->tcpkeepAlive_frame->setVisible(true);
        ui->customHeartbeatCb_frame->setVisible(true);
        ui->tcpDestIpAddr_frame->setVisible(true);
        ui->generalReportingIntl_frame->setVisible(true);
//        ui->dataPollInterval_frame->setVisible(true);

        on_customHeartbeat_cb_clicked(false);
        on_requireResponse_cb_clicked(false);

        if(m_proName.at(3)=='5'){
            ui->tcpkeepAlive_frame->setVisible(false);
        }
    }else if(index == QunpUCXX14::APP_UDP){
        ui->customHeartbeatCb_frame->setVisible(true);
        ui->tcpDestIpAddr_frame->setVisible(true);
        ui->generalReportingIntl_frame->setVisible(true);
//        ui->dataPollInterval_frame->setVisible(true);

        on_customHeartbeat_cb_clicked(false);
        on_requireResponse_cb_clicked(false);

        if(m_proName.at(3)=='5'){
            ui->tcpkeepAlive_frame->setVisible(false);
        }
    }else if(index == QunpUCXX14::APP_MQTT){
        ui->mqtt_frame->setVisible(true);
        ui->mqttUserCre_gb->setVisible(true);
        ui->mqttTls_gb->setVisible(true);
        ui->generalReportingIntl_frame->setVisible(true);

    }else if(index == QunpUCXX14::APP_ALI){

        ui->generalReportingIntl_frame->setVisible(true);
        ui->dataPollInterval_frame->setVisible(true);
        ui->aliyun_frame->setVisible(true);

    }else if(index == QunpUCXX14::APP_ONENET){

        ui->oneNetKeepAlive_frame->setVisible(true);
        ui->oneNetProductID_frame->setVisible(true);
        ui->oneNetKey_frame->setVisible(true);

    }else if(index == QunpUCXX14::APP_AZURE){
#ifdef ODM_LHR_AZURE
        ui->azureMode_frame->setVisible(true);
        ui->generalKeepAliveInterval_frame->setVisible(true);
        ui->generalReportingIntl_frame->setVisible(true);
        ui->awsServerAddr_frame->setVisible(true);
        ui->awsCAFile_frame->setVisible(true);
        ui->awsCliCerFile_frame->setVisible(true);
        ui->awsCliKeyFile_frame->setVisible(true);
        ui->dataPollInterval_frame->setVisible(true);
        on_azureMode_cbx_currentIndexChanged(ui->azureMode_cbx->currentIndex());
#endif
    }
    if(m_dealThread->structSupportModel.lora){
        ui->generalReportingIntl_frame->setVisible(true);
        ui->dataPollInterval_frame->setVisible(false);
        ui->cellularSetting_gb->setVisible(false);
    }

    ui->reportingIntercal_label->setIndent(ui->cloudMode_frame->isVisible() ? 30: 9);

    on_changePwd_cb_clicked(ui->changePwd_cb->isChecked());
}

/**
 * 自定义心跳包勾选框
 * @brief UCXX14Model::on_customHeartbeat_cb_clicked
 * @param checked
 */
void UCXX14Model::on_customHeartbeat_cb_clicked(bool checked)
{
    ui->customHeartbeat_cb->setChecked(checked);
    ui->customHeartbeat_frame->setVisible(checked);
    ui->requireResponseCb_frame->setVisible(checked);
    ui->responseContent_frame->setVisible(ui->requireResponse_cb->isChecked() && ui->customHeartbeat_cb->isChecked());

    if(!checked)
        on_requireResponse_cb_clicked(false);

    on_changePwd_cb_clicked(ui->changePwd_cb->isChecked());
}

void UCXX14Model::on_requireResponse_cb_clicked(bool checked)
{
    ui->requireResponse_cb->setChecked(checked);
    ui->responseContent_frame->setVisible(checked);

    if(!checked){
        if(ui->cloudApplicationMode_cbx->currentData().toInt() == QunpUCXX14::APP_UDP){
            ui->serverStatusTitle_label->setVisible(false);
            ui->serverStatus1_label->setVisible(false);
            ui->serverStatus2_label->setVisible(false);
        }else{
            ui->serverStatusTitle_label->setVisible(true);
            ui->serverStatus1_label->setVisible(true);
            ui->serverStatus2_label->setVisible(true);
        }

    }else{
        ui->serverStatusTitle_label->setVisible(true);
        ui->serverStatus1_label->setVisible(true);
        ui->serverStatus2_label->setVisible(true);

    }
    on_changePwd_cb_clicked(ui->changePwd_cb->isChecked());
}


void UCXX14Model::on_mqttUserCreEnable_cb_clicked(bool checked)
{
    ui->mattUserCreUsername_frame->setEnabled(checked);
    ui->mattUserCrePwd_frame->setEnabled(checked);
}

void UCXX14Model::on_mqttTlsEnable_cb_clicked(bool checked)
{
    if(m_generalPageInfo.application_mode == QunpUCXX14::APP_MQTT){
        ui->mqttTlsCAFile_frame->setEnabled(checked);
        ui->mqttTlsCliCerFile_frame->setEnabled(checked);
        ui->mqttTlsCliKeyFile_frame->setEnabled(checked);
    }
}

/**
 * CA File 游览
 * @brief UCXX14Model::on_awsCASelectFile_btn_clicked
 */
void UCXX14Model::on_awsCASelectFile_btn_clicked()
{
    QString extFileName = QFileDialog::getOpenFileName(this, tr("choise CA file"), m_caFilePath, tr("File (*.pem *.crt);; File(*.*)"));
    if(!extFileName.isEmpty()){
       QSettings settings(m_iniPath, QSettings::IniFormat);
       settings.beginGroup("ImageFilePath");
       settings.setValue("caFilePath",extFileName.left(extFileName.lastIndexOf('/')));
       settings.endGroup();
       ui->awsCAFile_lineEdit->setText(extFileName);
       ui->awsCAImportFile_btn->setEnabled(true);

       ui->mqttTlsCAFile_lineEdit->setText(extFileName);
       ui->mqttTlsCAImportFile_btn->setEnabled(true);

       m_bcaFileBrowse = true;
    }else{
        m_bcaFileBrowse = false;
    }
}
/**
 * CA 导入
 * @brief UCXX14Model::on_awsCAImportFile_btn_clicked
 */
void UCXX14Model::on_awsCAImportFile_btn_clicked()
{
    QVariantMap map;
    map.insert("fileType","CA");
    map.insert("delete",false);
    map.insert("caFilePath",ui->awsCAFile_lineEdit->text().trimmed());
    QVariantList list;
    list.append(map);

    ui->awsCADelFile_btn->setEnabled(true);
    ui->awsCAImportFile_btn->setEnabled(false);

    ui->mqttTlsCADelFile_btn->setEnabled(true);
    ui->mqttTlsCAImportFile_btn->setEnabled(false);

    if(m_bcaFileBrowse)
        emit requestToDevice(UCXX14DealThread::CONFIG_IMPORT_AWS_FILE,list);

    m_bcaFileBrowse = false;
}
/**
 * CA 删除
 * @brief UCXX14Model::on_awsCADelFile_btn_clicked
 */
void UCXX14Model::on_awsCADelFile_btn_clicked()
{
    QVariantMap map;
    map.insert("fileType","CA");
    map.insert("delete",true);
    ui->awsCAFile_lineEdit->clear();
    QVariantList list;
    list.append(map);
    ui->awsCAImportFile_btn->setEnabled(false);
    ui->awsCADelFile_btn->setEnabled(false);
    ui->awsCAFile_lineEdit->clear();

    ui->mqttTlsCAImportFile_btn->setEnabled(false);
    ui->mqttTlsCADelFile_btn->setEnabled(false);
    ui->mqttTlsCAFile_lineEdit->clear();

    emit requestToDevice(UCXX14DealThread::CONFIG_IMPORT_AWS_FILE,list);
}

/**
 * 设备证书选择
 * @brief UCXX14Model::on_awsCliCerSelectFile_btn_clicked
 */
void UCXX14Model::on_awsCliCerSelectFile_btn_clicked()
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
       ui->awsCliCerFile_lineEdit->setText(extFileName);
       ui->awsCliCerImportFile_btn->setEnabled(true);

       ui->mqttTlsCliCerFile_lineEdit->setText(extFileName);
       ui->mqttTlsCliCerImportFile_btn->setEnabled(true);

       m_bclientFileBrowse = true;
    }else{
       m_bclientFileBrowse = false;
    }
}

/**
 * 设备证书导入
 * @brief UCXX14Model::on_awsCliCerImportFile_btn_clicked
 */
void UCXX14Model::on_awsCliCerImportFile_btn_clicked()
{
    QVariantMap map;
    map.insert("fileType","Client Certificate");
    map.insert("delete",false);
    map.insert("cliCerFilePath",ui->awsCliCerFile_lineEdit->text().trimmed());
    QVariantList list;
    list.append(map);

    if(m_bclientFileBrowse)
        emit requestToDevice(UCXX14DealThread::CONFIG_IMPORT_AWS_FILE,list);

    ui->awsCliCerDelFile_btn->setEnabled(true);
    ui->awsCliCerImportFile_btn->setEnabled(false);

    ui->mqttTlsCliCerDelFile_btn->setEnabled(true);
    ui->mqttTlsCliCerImportFile_btn->setEnabled(false);

    m_bclientFileBrowse = false;
}

/**
 * 设备证书删除
 * @brief UCXX14Model::on_awsCliCerDelFile_btn_clicked
 */
void UCXX14Model::on_awsCliCerDelFile_btn_clicked()
{
    QVariantMap map;
    map.insert("fileType","Client Certificate");
    map.insert("delete",true);
    ui->awsCliCerFile_lineEdit->clear();
    QVariantList list;
    list.append(map);
    emit requestToDevice(UCXX14DealThread::CONFIG_IMPORT_AWS_FILE,list);
    ui->awsCliCerImportFile_btn->setEnabled(false);
    ui->awsCliCerDelFile_btn->setEnabled(false);
    ui->awsCliCerFile_lineEdit->clear();

    ui->mqttTlsCliCerImportFile_btn->setEnabled(false);
    ui->mqttTlsCliCerDelFile_btn->setEnabled(false);
    ui->mqttTlsCliCerFile_lineEdit->clear();

    ui->mqttTlsCliCerFile_lineEdit->clear();
}

/**
 * 私钥选择
 * @brief UCXX14Model::on_awsCliKeySelectFile_btn_clicked
 */
void UCXX14Model::on_awsCliKeySelectFile_btn_clicked()
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
       ui->awsCliKeyFile_lineEdit->setText(extFileName);
       ui->mqttTlsCliKeyFile_lineEdit->setText(extFileName);

       ui->awsCliKeyImportFile_btn->setEnabled(true);
       ui->mqttTlsCliKeyImportFile_btn->setEnabled(true);

       m_bclientKeyBrowse = true;
    }else{
        m_bclientKeyBrowse = false;
    }
}

/**
 * 私钥导入
 * @brief UCXX14Model::on_awsCliKeyImportFile_btn_clicked
 */
void UCXX14Model::on_awsCliKeyImportFile_btn_clicked()
{
    QVariantMap map;
    map.insert("fileType","Client Key");
    map.insert("delete",false);
    map.insert("cliKeyFilePath",ui->awsCliKeyFile_lineEdit->text().trimmed());
    QVariantList list;
    list.append(map);

    if(m_bclientKeyBrowse)
        emit requestToDevice(UCXX14DealThread::CONFIG_IMPORT_AWS_FILE,list);

    ui->awsCliKeyDelFile_btn->setEnabled(true);
    ui->awsCliKeyImportFile_btn->setEnabled(false);

    ui->mqttTlsCliKeyDelFile_btn->setEnabled(true);
    ui->mqttTlsCliKeyImportFile_btn->setEnabled(false);

    m_bclientKeyBrowse = false;
}

/**
 * 私钥删除
 * @brief UCXX14Model::on_awsCliKeyDelFile_btn_clicked
 */
void UCXX14Model::on_awsCliKeyDelFile_btn_clicked()
{
    QVariantMap map;
    map.insert("fileType","Client Key");
    map.insert("delete",true);
    ui->awsCliKeyFile_lineEdit->clear();
    QVariantList list;
    list.append(map);
    emit requestToDevice(UCXX14DealThread::CONFIG_IMPORT_AWS_FILE,list);

    ui->awsCliKeyImportFile_btn->setEnabled(false);
    ui->awsCliKeyDelFile_btn->setEnabled(false);
    ui->awsCliKeyFile_lineEdit->clear();

    ui->mqttTlsCliKeyImportFile_btn->setEnabled(false);
    ui->mqttTlsCliKeyDelFile_btn->setEnabled(false);
    ui->mqttTlsCliKeyFile_lineEdit->clear();
}


/**
 * ODM Azure的模式下 选择
 * @brief UCXX14Model::on_azureMode_cbx_currentIndexChanged
 * @param index
 */
void UCXX14Model::on_azureMode_cbx_currentIndexChanged(int index)
{
    Q_UNUSED(index)
#ifdef ODM_LHR_AZURE
    if(ui->cloudApplicationMode_cbx->currentData().toInt() == APP_AZURE){
        if(index == 0){//SAS模式
            ui->awsCAFile_frame->setVisible(true);
            ui->awsCliCerFile_frame->setVisible(false);
            ui->awsCliKeyFile_frame->setVisible(false);
        }else if(index == 1){// signed CA模式
            ui->awsCAFile_frame->setVisible(true);
            ui->awsCliCerFile_frame->setVisible(true);
            ui->awsCliKeyFile_frame->setVisible(true);
        }
    }
#endif
}


/**
 * 保存Genenal页面信息
 * @brief UCXX14Model::on_generalSave_btn_clicked
 */
void UCXX14Model::on_generalSave_btn_clicked()
{
    ui->awsServerAddr_lineEdit->setStyleSheet(RECOVERY_INPUT);
    ui->dataPollInterval_lineEdit->setStyleSheet(RECOVERY_INPUT);
    ui->cloudKeepAliveInterval_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->cloudReportInterval_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->tcpkeepAlive_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->serverAddr1_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->serverPort1_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->serverAddr2_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->serverPort2_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->heartbeatInterval_lineEdit->setStyleSheet(RECOVERY_INPUT);
    ui->mattUserCreUsername_linEdit->setStyleSheet(RECOVERY_INPUT);
    ui->mattUserCrePwdlinEdit->setStyleSheet(RECOVERY_INPUT);
    ui->aliyunKeepAliveInterval_lineEdit->setStyleSheet(RECOVERY_INPUT);


    QVariantMap map;
    if(ui->awsServerAddr_lineEdit->text().isEmpty() && ui->awsServerAddr_lineEdit->isVisible()){
        ui->awsServerAddr_lineEdit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("This field is required."));

        return;
    }
    if(ui->cloudApplicationMode_cbx->currentData().toInt() == QunpUCXX14::APP_ALI){
        if(ui->generalKeepAliveInterval_frame->isVisible() && (ui->cloudKeepAliveInterval_lineedit->text().toInt()>1200 || ui->cloudKeepAliveInterval_lineedit->text().toInt()<30)){
            ui->cloudKeepAliveInterval_lineedit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Keep Alive Interval Range：30-1200."));
            ui->cloudKeepAliveInterval_lineedit->setFocus();
            return;
        }
    }else{
        if(ui->generalKeepAliveInterval_frame->isVisible() && (ui->cloudKeepAliveInterval_lineedit->text().toInt()>3600 || ui->cloudKeepAliveInterval_lineedit->text().toInt()<1)){
            ui->cloudKeepAliveInterval_lineedit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Keep Alive Interval Range：1-3600."));

            ui->cloudKeepAliveInterval_lineedit->setFocus();
            return;
        }
    }

    if((ui->cloudReportInterval_lineedit->text().toInt() - ui->dataPollInterval_lineEdit->text().toInt() * 5 > 0 ) && ui->cloudReportInterval_lineedit->isVisible() && ui->dataPollInterval_lineEdit->isVisible()){
        ui->cloudReportInterval_lineedit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("The interval between Reporting Interval and Data Polling Interval should be small."));
        ui->cloudReportInterval_lineedit->setFocus();
        return;
    }
    if(((ui->cloudReportInterval_lineedit->text().trimmed().isEmpty()) || (ui->cloudReportInterval_lineedit->text().toInt() > 64800 || ui->cloudReportInterval_lineedit->text().toInt()<10))
           && ui->cloudReportInterval_lineedit->isVisible()  ){
        ui->cloudReportInterval_lineedit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("Report Interval Range：10-64800."));
        ui->cloudReportInterval_lineedit->setFocus();
        return;
    }
    if(m_proName.at(3) == '2'){
        if(ui->tcpkeepAlive_lineedit->isVisible() && (ui->tcpkeepAlive_lineedit->text().toInt()>30 )){
            ui->tcpkeepAlive_lineedit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Valid Range：1-30."));

            return;
        }
    }else{
        if(ui->tcpkeepAlive_lineedit->isVisible() && (ui->tcpkeepAlive_lineedit->text().toInt()>120 )){
            ui->tcpkeepAlive_lineedit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Valid Range：1-120."));

            return;
        }
    }
    if(ui->serverPort1_lineedit->text().toInt() > 65535 && ui->serverPort1_lineedit->isVisible()){
        ui->serverPort1_lineedit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("Valid Range：1-65535."));

        return;
    }
    if(ui->serverPort2_lineedit->text().toInt() > 65535 && ui->serverPort2_lineedit->isVisible()){
        ui->serverPort2_lineedit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("Valid Range：1-65535."));

        return;
    }

    if((ui->heartbeatInterval_lineEdit->text().isEmpty() || ui->heartbeatInterval_lineEdit->text().toInt()>3600) && ui->heartbeatInterval_lineEdit->isVisible()){
        ui->heartbeatInterval_lineEdit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("Valid Range：1-3600."));

        return;
    }
    if(ui->mattUserCreUsername_linEdit->isVisible() && ui->mattUserCreUsername_linEdit->isEnabled() && ui->mattUserCreUsername_linEdit->text().isEmpty()){
        ui->mattUserCreUsername_linEdit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("This field is required."));

        return;
    }
    if(ui->mattUserCrePwdlinEdit->isVisible() && ui->mattUserCrePwdlinEdit->isEnabled() && ui->mattUserCrePwdlinEdit->text().isEmpty()){
        ui->mattUserCrePwdlinEdit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("This field is required."));

        return;
    }

    if(ui->changePwd_cb->isChecked()){
        if(ui->oldPwd_lineEdit->text().length() != 6){
            showWarning(this,tr("Attention"),tr("Please enter a 6-character password."));

            return;
        }

        if(ui->newPwd_lineEdit->text() != ui->reNewPwd_lineEdit->text()){
            showWarning(this,tr("Attention"),tr("New Password and Confirm Password do not match."));

            return;
        }
        if(ui->newPwd_lineEdit->text().length() != 6){
            showWarning(this,tr("Attention"),tr("Please enter a 6-character password."));

            return;
        }
        m_loginPwd = ui->newPwd_lineEdit->text().trimmed();
    }
    if(ui->pinNum_lineEdit->text().length() <4 && !ui->pinNum_lineEdit->text().trimmed().isEmpty()){
        showWarning(this,tr("Attention"),tr("Please enter a valid PIN code."));

        return;
    }

    //NB for Aliyum
    if(m_dealThread->structSupportModel.nb){
        if(ui->aliyunClientID_lineEdit->isVisible() && ui->aliyunClientID_lineEdit->text().isEmpty()){
            showWarning(this,tr("Attention"),tr("Please enter Client ID."));

            return;
        }

        if(ui->aliyunProductKey_lineEdit->isVisible() && ui->aliyunProductKey_lineEdit->text().isEmpty()){
            showWarning(this,tr("Attention"),tr("Please enter Product Key."));

            return;
        }

        if(ui->aliyunDeviceSecret_lineEdit->isVisible() && ui->aliyunDeviceSecret_lineEdit->text().isEmpty()){
            showWarning(this,tr("Attention"),tr("Please enter Device Secret."));

            return;
        }

        if((ui->aliyunKeepAliveInterval_lineEdit->text().toInt() > 3600 || ui->aliyunKeepAliveInterval_lineEdit->text().toInt() < 1) && ui->aliyunKeepAliveInterval_lineEdit->isVisible()){
            ui->aliyunKeepAliveInterval_lineEdit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Valid Range：1-3600."));

            return;
        }
    }


    if((ui->dataPollInterval_lineEdit->text().trimmed().isEmpty() || ui->dataPollInterval_lineEdit->text().trimmed().toInt()>3600 || ui->dataPollInterval_lineEdit->text().trimmed().toInt()<1)
            && ui->dataPollInterval_lineEdit->isVisible()){
        ui->dataPollInterval_lineEdit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("Valid Range：1-3600."));
        ui->dataPollInterval_lineEdit->setFocus();
        return;

    }

    m_generalPageInfo.application_mode = ui->cloudApplicationMode_cbx->currentData().toInt();
    map.insert("applicationMode",ui->cloudApplicationMode_cbx->currentData().toInt());

    map.insert("oldPwd",ui->oldPwd_lineEdit->text());
    map.insert("newPwd",ui->newPwd_lineEdit->text());
    map.insert("reNewPwd",ui->newPwd_lineEdit->text());
    map.insert("networkType",ui->networkType_cbx->currentData().toInt());
    map.insert("pinCode",ui->pinNum_lineEdit->text().trimmed());
    map.insert("apnUser",ui->apnUser_lineEdit->text().trimmed());
    map.insert("apnPwd",ui->apnPwd_lineEdit->text().trimmed());
    map.insert("apn",ui->apn_lineEdit->text().trimmed());

    map.insert("awsServerAddr", ui->awsServerAddr_lineEdit->text());
    map.insert("keepAliveInterval",ui->cloudKeepAliveInterval_lineedit->text());
    map.insert("reportingInterval",ui->cloudReportInterval_lineedit->text());
    map.insert("dataCollectInterval", ui->dataPollInterval_lineEdit->text());
    map.insert("tcpKeepAlive",ui->tcpkeepAlive_lineedit->text());
    map.insert("customHeartbeatMode",ui->customHeartbeat_cb->isVisible()?ui->customHeartbeat_cb->isChecked():false);
    map.insert("brokerAddr", ui->brokerAddr_lineEdit->text().trimmed());
    map.insert("brokerPort", ui->brokerPort_lineEdit->text().trimmed());
    map.insert("clientID", ui->clientID_lineEdit->text().trimmed());
    map.insert("connectTimeout", ui->connectTimeout_lineEdit->text().trimmed());
    map.insert("mqttKeepAliveInterval",ui->mqttKeepAliveInterval_lineEdit->text().trimmed());
    map.insert("customContent",ui->customContent_lineEdit->text().trimmed());
    map.insert("heartbeatInterval", ui->heartbeatInterval_lineEdit->text().trimmed());
    map.insert("requireResponse",ui->requireResponse_cb->isVisible()?ui->requireResponse_cb->isChecked():false);
    map.insert("responseContent", ui->responseContent_lineEdit->text().trimmed());
    map.insert("mqttTlsEnable",ui->mqttTlsEnable_cb->isChecked());
    map.insert("mqttUserCre",ui->mqttUserCreEnable_cb->isChecked());
    map.insert("mqttUsername",ui->mattUserCreUsername_linEdit->text().trimmed());
    map.insert("mqttPwd",ui->mattUserCrePwdlinEdit->text().trimmed());

    //35xx for NB Aliyum
    map.insert("aliyunClientID",ui->aliyunClientID_lineEdit->text().trimmed());
    map.insert("aliyunProductKey",ui->aliyunProductKey_lineEdit->text().trimmed());
    map.insert("aliyunDeviceSecret",ui->aliyunDeviceSecret_lineEdit->text().trimmed());
    map.insert("aliyunKeepAliveInterval",ui->aliyunKeepAliveInterval_lineEdit->text().trimmed());
    map.insert("aliyunQoS",ui->aliyunQoS_cbx->currentText());

    //gpio
    m_generalPageInfo.gpioType = ui->gpioType_cbx->currentIndex();
    m_generalPageInfo.gpio2Type = ui->gpioType2_cbx->currentIndex();
    map.insert("gpioCounter1Enable",ui->gpioType_cbx->currentIndex() == 0 ? 4:3);
    map.insert("gpioCounter2Enable",ui->gpioType2_cbx->currentIndex() == 0 ? 4:3);

    //onenet
    map.insert("oneNetProductID",ui->oneNetProductID_lineedit->text().trimmed());
    map.insert("oneNetKey",ui->oneNetKey_lineEdit->text().trimmed());
    map.insert("oneNetKeepAlive",ui->oneNetKeepAlive_lineEdit->text().trimmed());

#ifdef ODM_LHR_AZURE
    map.insert("authMode",ui->azureMode_cbx->currentIndex());
#endif
    if(m_statusPageInfo.ucpVer >= 0x13){
        map.insert("serverAddr1",ui->serverAddr1_lineedit->text().trimmed().isEmpty()?"":ui->serverAddr1_lineedit->text().trimmed());
        map.insert("serverAddr2",ui->serverAddr2_lineedit->text().trimmed().isEmpty()?"":ui->serverAddr2_lineedit->text().trimmed());
    }else{
        map.insert("serverAddr1",ui->serverAddr1_lineedit->text().trimmed().isEmpty()?"0.0.0.0":ui->serverAddr1_lineedit->text().trimmed());
        map.insert("serverAddr2",ui->serverAddr2_lineedit->text().trimmed().isEmpty()?"0.0.0.0":ui->serverAddr2_lineedit->text().trimmed());
    }
    map.insert("serverPort1",ui->serverPort1_lineedit->text().trimmed().isEmpty()?"0":ui->serverPort1_lineedit->text().trimmed());
    map.insert("serverPort2",ui->serverPort2_lineedit->text().trimmed().isEmpty()?"0":ui->serverPort2_lineedit->text().trimmed());

    QVariantList list;
    list.append(map);

    emit requestToDevice(UCXX14DealThread::CONFIG_WRITE_GENERAL,list);

    if(ui->cloudApplicationMode_cbx->currentData().toInt() == QunpUCXX14::APP_AWS
#ifdef ODM_LHR_AZURE
       || ui->cloudApplicationMode_cbx->currentData().toInt() == QunpUCXX14::APP_AZURE
#endif
            ){
        ui->awsCAFile_frame->setEnabled(true);
        ui->awsCliCerFile_frame->setEnabled(true);
        ui->awsCliKeyFile_frame->setEnabled(true);

        ui->mqttTlsCAFile_frame->setEnabled(false);
        ui->mqttTlsCliCerFile_frame->setEnabled(false);
        ui->mqttTlsCliKeyFile_frame->setEnabled(false);
    }else if(ui->cloudApplicationMode_cbx->currentData().toInt() == QunpUCXX14::APP_MQTT){
        ui->awsCAFile_frame->setEnabled(false);
        ui->awsCliCerFile_frame->setEnabled(false);
        ui->awsCliKeyFile_frame->setEnabled(false);

        ui->mqttTlsCAFile_frame->setEnabled(true);
        ui->mqttTlsCliCerFile_frame->setEnabled(true);
        ui->mqttTlsCliKeyFile_frame->setEnabled(true);

        on_mqttTlsEnable_cb_clicked(ui->mqttTlsEnable_cb->isChecked());
    }else{
        ui->awsCAFile_frame->setEnabled(false);
        ui->awsCliCerFile_frame->setEnabled(false);
        ui->awsCliKeyFile_frame->setEnabled(false);

        ui->mqttTlsCAFile_frame->setEnabled(false);
        ui->mqttTlsCliCerFile_frame->setEnabled(false);
        ui->mqttTlsCliKeyFile_frame->setEnabled(false);
    }

    if(!ui->awsCAFile_lineEdit->text().isEmpty() || !ui->mqttTlsCAFile_lineEdit->text().isEmpty()){
        ui->awsCADelFile_btn->setEnabled(true);
        ui->mqttTlsCADelFile_btn->setEnabled(true);
    }
    if(!ui->awsCliCerFile_lineEdit->text().isEmpty() || !ui->mqttTlsCliCerFile_lineEdit->text().isEmpty()){
        ui->awsCliCerDelFile_btn->setEnabled(true);
        ui->mqttTlsCliCerDelFile_btn->setEnabled(true);
    }
    if(!ui->awsCliKeyFile_lineEdit->text().isEmpty() || !ui->mqttTlsCliKeyFile_lineEdit->text().isEmpty()){
        ui->awsCliKeyDelFile_btn->setEnabled(true);
        ui->mqttTlsCliKeyDelFile_btn->setEnabled(true);
    }
}

/**
 * 11xx GPIO counter1 功能
 * @brief UCXX14Model::on_gpioType_cbx_currentIndexChanged
 * @param index
 */
void UCXX14Model::on_gpioType_cbx_currentIndexChanged(int index)
{
    ui->gpioCounter_frame->setVisible(index == 1);

    if(m_generalPageInfo.gpioType.toInt() == 1 && index == 0){

        if(showQuestion(this,tr("Attention"),MyMessageBox::TYPE_NONE,tr("If the DI is selected, the related commands for setting the counter will be invalid and cleared, please confirm.")) != QMessageBox::Ok){
            disconnect(ui->gpioType_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_gpioType_cbx_currentIndexChanged(int)));
            ui->gpioType_cbx->setCurrentIndex(0);
            ui->gpioCounter_frame->setVisible(false);
            connect(ui->gpioType_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_gpioType_cbx_currentIndexChanged(int)));
        }
    }else if(m_generalPageInfo.gpioType.toInt() == 0 && index == 0){
        if(showQuestion(this,tr("Attention"),MyMessageBox::TYPE_NONE,tr("If the counter is selected, the related commands for setting DI will be invalid and cleared, please confirm.")) != QMessageBox::Ok){
            disconnect(ui->gpioType_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_gpioType_cbx_currentIndexChanged(int)));
            ui->gpioType_cbx->setCurrentIndex(0);
            ui->gpioCounter_frame->setVisible(false);
            connect(ui->gpioType_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_gpioType_cbx_currentIndexChanged(int)));
        }
    }
    return;
}

/**
 * 11xx GPIO counter2 功能
 * @brief UCXX14Model::on_gpioType2_cbx_currentIndexChanged
 * @param index
 */
void UCXX14Model::on_gpioType2_cbx_currentIndexChanged(int index)
{
    ui->gpioCounter2_frame->setVisible(index == 1);
    if(m_generalPageInfo.gpio2Type.toInt() == 1 && index == 0){

        if(showQuestion(this,tr("Attention"),MyMessageBox::TYPE_NONE,tr("If the DI is selected, the related commands for setting the counter will be invalid and cleared, please confirm.")) != QMessageBox::Ok){
            disconnect(ui->gpioType2_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_gpioType2_cbx_currentIndexChanged(int)));
            ui->gpioType2_cbx->setCurrentIndex(1);
            ui->gpioCounter2_frame->setVisible(true);
            connect(ui->gpioType2_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_gpioType2_cbx_currentIndexChanged(int)));
        }
    }else if(m_generalPageInfo.gpio2Type.toInt() == 0 && index == 1){
        if(showQuestion(this,tr("Attention"),MyMessageBox::TYPE_NONE,tr("If the counter is selected, the related commands for setting DI will be invalid and cleared, please confirm.")) != QMessageBox::Ok){
            disconnect(ui->gpioType2_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_gpioType2_cbx_currentIndexChanged(int)));
            ui->gpioType2_cbx->setCurrentIndex(0);
            ui->gpioCounter2_frame->setVisible(false);
            connect(ui->gpioType2_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_gpioType2_cbx_currentIndexChanged(int)));
        }
    }
}

/**
 * 1114 1122 开始计数
 * @brief UCXX14Model::on_gpioCounterStart_btn_clicked
 */
void UCXX14Model::on_gpioCounterStart_btn_clicked()
{
    QVariantMap map;
    map.insert("readType",UCXX14DealThread::RNS_GPIO2_COUNTER_START);
    map.insert("start",ui->gpioCounterStart_btn->text().contains(tr("Start"))?2:1);
    map.insert("counterNum",1);
    QVariantList list;
    list.append(map);

    ui->gpioCounterStart_btn->setEnabled(false);
    ui->gpioCounterRefresh_btn->setEnabled(false);
    ui->gpioCounterClear_btn->setEnabled(false);

    emit requestToDevice(UCXX14DealThread::CONFIG_READ_GENERAL_SPECIAL,list);
}

/**
 * 1114 1122 刷新
 * @brief UCXX14Model::on_gpioCounterRefresh_btn_clicked
 */
void UCXX14Model::on_gpioCounterRefresh_btn_clicked()
{
    QVariantMap map;
    map.insert("readType",UCXX14DealThread::RNS_GPIO2_COUNTER_REFRESH);
    map.insert("counterNum",1);
    QVariantList list;
    list.append(map);

    ui->gpioCounterStart_btn->setEnabled(false);
    ui->gpioCounterRefresh_btn->setEnabled(false);
    ui->gpioCounterClear_btn->setEnabled(false);

    emit requestToDevice(UCXX14DealThread::CONFIG_READ_GENERAL_SPECIAL,list);
}

/**
 * 1114 1122 清空
 * @brief UCXX14Model::on_gpioCounterClear_btn_clicked
 */
void UCXX14Model::on_gpioCounterClear_btn_clicked()
{
    QVariantMap map;
    map.insert("readType",UCXX14DealThread::RNS_GPIO2_COUNTER_CLEAR);
    map.insert("counterNum",1);
    QVariantList list;
    list.append(map);

    ui->gpioCounterStart_btn->setEnabled(false);
    ui->gpioCounterRefresh_btn->setEnabled(false);
    ui->gpioCounterClear_btn->setEnabled(false);

    emit requestToDevice(UCXX14DealThread::CONFIG_READ_GENERAL_SPECIAL,list);
}

/**
 * 1114 1122 Counter2开始
 * @brief UCXX14Model::on_gpioCounterStart2_btn_clicked
 */
void UCXX14Model::on_gpioCounterStart2_btn_clicked()
{
    QVariantMap map;
    map.insert("readType",UCXX14DealThread::RNS_GPIO2_COUNTER_START);
    map.insert("start",ui->gpioCounterStart2_btn->text().contains(tr("Start"))?2:1);
    map.insert("counterNum",2);
    QVariantList list;
    list.append(map);

    ui->gpioCounterStart2_btn->setEnabled(false);
    ui->gpioCounterRefresh2_btn->setEnabled(false);
    ui->gpioCounterClear2_btn->setEnabled(false);

    emit requestToDevice(UCXX14DealThread::CONFIG_READ_GENERAL_SPECIAL,list);
}

/**
 * 1114 1122 刷新
 * @brief UCXX14Model::on_gpioCounterRefresh2_btn_clicked
 */
void UCXX14Model::on_gpioCounterRefresh2_btn_clicked()
{
    QVariantMap map;
    map.insert("readType",UCXX14DealThread::RNS_GPIO2_COUNTER_REFRESH);
    map.insert("counterNum",2);
    QVariantList list;
    list.append(map);

    ui->gpioCounterStart2_btn->setEnabled(false);
    ui->gpioCounterRefresh2_btn->setEnabled(false);
    ui->gpioCounterClear2_btn->setEnabled(false);

    emit requestToDevice(UCXX14DealThread::CONFIG_READ_GENERAL_SPECIAL,list);
}

/**
 * 1114 1122 Counter2 刷新
 * @brief UCXX14Model::on_gpioCounterClear2_btn_clicked
 */
void UCXX14Model::on_gpioCounterClear2_btn_clicked()
{
    QVariantMap map;
    map.insert("readType",UCXX14DealThread::RNS_GPIO2_COUNTER_CLEAR);
    map.insert("counterNum",2);
    QVariantList list;
    list.append(map);

    ui->gpioCounterStart2_btn->setEnabled(false);
    ui->gpioCounterRefresh2_btn->setEnabled(false);
    ui->gpioCounterClear2_btn->setEnabled(false);

    emit requestToDevice(UCXX14DealThread::CONFIG_READ_GENERAL_SPECIAL,list);
}

