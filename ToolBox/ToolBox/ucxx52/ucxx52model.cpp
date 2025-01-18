#include "ucxx52model.h"
#include "ui_ucxx52model.h"
#include <QDateTime>

UCXX52Model::UCXX52Model(QWidget *parent) :
    MyWindowStytle(parent),
    ui(new Ui::UCXX52Model)
{
    ui->setupUi(this);

    ui->status_frame->setVisible(false);

    m_nfcPwdWnd = new PasswordVerify();
    m_upgradeWnd = new UpgradeWnd();
    m_dealThread = new UCXX52DealThread();
    m_thread = new QThread();

    m_dealThread->moveToThread(m_thread);

    qRegisterMetaType<UCXX52DealThread::StructPageStatus>("UCXX52DealThread::StructPageStatus");
    qRegisterMetaType<UCXX52DealThread::StructPageGeneral>("UCXX52DealThread::StructPageGeneral");
    qRegisterMetaType<UCXX52DealThread::StructPageSetting>("UCXX52DealThread::StructPageSetting");
    qRegisterMetaType<UCXX52DealThread::StructPageChannel>("UCXX52DealThread::StructPageChannel");
    qRegisterMetaType<StructPageLorawan>("StructPageLorawan");

    connect(this, SIGNAL(requestToDevice(int, QVariantList)), m_dealThread, SLOT(onRequestToDevice(int, QVariantList)),Qt::UniqueConnection);
    connect(m_thread,SIGNAL(started()),m_dealThread,SLOT(run()),Qt::UniqueConnection);
    connect(m_dealThread,&UCXX52DealThread::getDeviceStatus,this,&UCXX52Model::onRecvDeviceStatus,Qt::UniqueConnection);
    connect(m_dealThread,&UCXX52DealThread::getGeneral,this,&UCXX52Model::onRecvGeneral,Qt::UniqueConnection);
    connect(m_dealThread,&UCXX52DealThread::getLorawan,this,&UCXX52Model::onRecvLorawan,Qt::UniqueConnection);
    connect(m_dealThread,&UCXX52DealThread::getChannel,this,&UCXX52Model::onRecvChannelStatus,Qt::UniqueConnection);
    connect(m_dealThread,&UCXX52DealThread::getSetting,this,&UCXX52Model::onRecvDeviceCommand,Qt::UniqueConnection);

    connect(m_dealThread,&UCXX52DealThread::waitingVisible, this, [=](bool vis){
        emit waitingVisible(vis);
    },Qt::UniqueConnection);

    m_thread->start(QThread::IdlePriority);

    m_iniPath = QApplication::applicationDirPath()+"/config.ini";
    ui->upgradeBootloader_frame->setVisible(false);
    ui->reboot_frame->setVisible(false);

    connect(m_dealThread, &UCXX52DealThread::upgradeProgress, this, &UCXX52Model::onUpgradePregressChanged, Qt::UniqueConnection);
    connect(this,&UCXX52Model::getProductName,m_dealThread, &UCXX52DealThread::onGetProductName, Qt::UniqueConnection);
    connect(m_dealThread, &UCXX52DealThread::sendMsgWnd, this, [=](QString msg){
        emit waitingVisible(false);
        showWarning(this,tr("Attention"),msg);
    });

    //规则引擎
    initCmdSetting();

    //Lora页面初始化
    initLorawanSetting();

    //modbus
#ifdef ODM_LHR_INDIA
    m_channelMudbusNum = 16;
#else
    m_channelMudbusNum = 8;
#endif
    ui->modbusStatus_cbx->setItemData(QunpUCXX52::UNXX_MB_FALSE,QunpUCXX52::UNXX_MB_FALSE);
    ui->modbusStatus_cbx->setItemData(QunpUCXX52::UNXX_MB_TRUE,QunpUCXX52::UNXX_MB_TRUE);
    ui->modbusStatus_cbx->setItemData(QunpUCXX52::UNXX_MB_ABOVE,QunpUCXX52::UNXX_MB_ABOVE);
    ui->modbusStatus_cbx->setItemData(QunpUCXX52::UNXX_MB_BELOW,QunpUCXX52::UNXX_MB_BELOW);
    ui->modbusStatus_cbx->setItemData(QunpUCXX52::UNXX_MB_WITHIN,QunpUCXX52::UNXX_MB_WITHIN);

    //General
    connect(ui->rs485Bridge_cb, SIGNAL(clicked(bool)),ui->rs485BridgePort_frame,SLOT(setVisible(bool)));

    ui->rs485Databit_cbx->setItemData(0,"8");
    ui->rs485Stopbit_cbx->setItemData(0,"1");
    ui->rs485Stopbit_cbx->setItemData(1,"2");
    ui->rs485Parity_cbx->setItemData(0,"0");
    ui->rs485Parity_cbx->setItemData(1,"1");
    ui->rs485Parity_cbx->setItemData(2,"2");

    ui->rs232Databit_cbx->setItemData(0,"8");
    ui->rs232Stopbit_cbx->setItemData(0,"1");
    ui->rs232Stopbit_cbx->setItemData(1,"2");
    ui->rs232Parity_cbx->setItemData(0,"0");
    ui->rs232Parity_cbx->setItemData(1,"1");
    ui->rs232Parity_cbx->setItemData(2,"2");

    ui->rs232Protocol_cbx->setItemData(QunpUCXX52::SERIAL_TCP,QunpUCXX52::SERIAL_TCP);
    ui->rs232Protocol_cbx->setItemData(QunpUCXX52::SERIAL_UDP,QunpUCXX52::SERIAL_UDP);
    ui->rs232Protocol_cbx->setItemData(QunpUCXX52::SERIAL_TCP_SERVER,QunpUCXX52::SERIAL_TCP_SERVER);
    ui->rs232Protocol_cbx->setItemData(QunpUCXX52::SERIAL_UDP_SERVER,QunpUCXX52::SERIAL_UDP_SERVER);
}

UCXX52Model::~UCXX52Model()
{
    delete ui;
}

void UCXX52Model::onGetProductName(QString proName,QString swver, QString hwver, bool isNFC, QString loginPwd)
{
    Q_UNUSED(isNFC)
    m_proName = proName;
    m_swver = swver;
    m_hwver = hwver;
    m_bNFC = false;
    m_loginPwd = loginPwd;

    emit getProductName(proName,swver,hwver,false);

    bool islora = m_proName.contains("1152");
    ui->modbusNetworkType_cbx->setVisible(!m_proName.contains("UC35"));

    ui->loraTimeValue_frame->setVisible(!islora);
    ui->signalLevelValue_frame->setVisible(!islora);
    ui->gsmStatus_frame->setVisible(!islora);
    ui->modbusCellularSetting_gb->setVisible(!islora);
    ui->modbusAppModel_frame->setVisible(!islora);

    ui->freCN470_frame->setVisible(false);
    ui->rssisnr_frame->setVisible(islora);
    ui->joinStatus_frame->setVisible(islora);
    ui->datarateStatus_frame->setVisible(islora);
    ui->rx2drStatus_frame->setVisible(islora);
    ui->uplinkCounter_frame->setVisible(islora);
    ui->downlinkCounter_frame->setVisible(islora);
    ui->modbusGpioSetting_gb->setVisible(islora);
    ui->modbusReporting_frame->setVisible(islora);

    QStringList networklist;
    ui->modbusNetworkType_cbx->clear();
    if(m_proName.mid(3,1) == NT_GSM){
        networklist<<tr("2G");
        ui->modbusNetworkType_cbx->addItems(networklist);
        ui->modbusNetworkType_cbx->setItemData(0,QunpUCXX52::CELLULAR_2G_ONLY);

    }else if(m_proName.mid(3,1)  == NT_WCDMA){
        networklist<<tr("Auto")<<tr("3G First")<<tr("3G Only")<<tr("2G First")<<tr("2G Only");
        ui->modbusNetworkType_cbx->addItems(networklist);
        ui->modbusNetworkType_cbx->setItemData(0,QunpUCXX52::CELLULAR_AUTO);
        ui->modbusNetworkType_cbx->setItemData(1,QunpUCXX52::CELLULAR_3G_FIRST);
        ui->modbusNetworkType_cbx->setItemData(2,QunpUCXX52::CELLULAR_3G_ONLY);
        ui->modbusNetworkType_cbx->setItemData(3,QunpUCXX52::CELLULAR_2G_FIRST);
        ui->modbusNetworkType_cbx->setItemData(4,QunpUCXX52::CELLULAR_2G_ONLY);

    }else if(m_proName.mid(3,1)  == NT_LTE){
        networklist<<tr("Auto")<<tr("4G First")<<tr("4G Only")<<tr("3G First")<<tr("3G Only")<<tr("2G First")<<tr("2G Only");
        ui->modbusNetworkType_cbx->addItems(networklist);
        ui->modbusNetworkType_cbx->setItemData(0,QunpUCXX52::CELLULAR_AUTO);
        ui->modbusNetworkType_cbx->setItemData(1,QunpUCXX52::CELLULAR_4G_FIRST);
        ui->modbusNetworkType_cbx->setItemData(2,QunpUCXX52::CELLULAR_4G_ONLY);
        ui->modbusNetworkType_cbx->setItemData(3,QunpUCXX52::CELLULAR_3G_FIRST);
        ui->modbusNetworkType_cbx->setItemData(4,QunpUCXX52::CELLULAR_3G_ONLY);
        ui->modbusNetworkType_cbx->setItemData(5,QunpUCXX52::CELLULAR_2G_FIRST);
        ui->modbusNetworkType_cbx->setItemData(6,QunpUCXX52::CELLULAR_2G_ONLY);
    }

}

void UCXX52Model::onPageChanged(QString name, QString title)
{
    ui->tabTitle_label->setText(title);

    for (int i=0; i<ui->stackedWidget->count(); i++) {
        if(name.contains(ui->stackedWidget->widget(i)->objectName())){

            switch (i) {
            case UCXX52DealThread::PAGE_LORAWAN:{
                m_loraReadIndex = LG_ALL;
                emit requestToDevice(i,QVariantList());
                break;
            }
            case UCXX52DealThread::PAGE_GENERAL:{
                QVariantMap map;
                m_modbusReadIndex = ui->tabWidget_3->currentIndex();
                map.insert("readIndex",ui->tabWidget_3->currentIndex());
                QVariantList list;
                list.append(map);
                emit requestToDevice(i,list);
                break;
            }
            case UCXX52DealThread::PAGE_CHANNEL:{

                if(m_generalPageInfo.application_mode == QunpUCXX52::APP_URSALINK_CLOUD && m_proName.contains("UC3")){
                    showWarning(this,tr("Attention"),tr("You have enabled Cloud Mode, now you can only configure your device on IoT Cloud."));
                    return;
                }
                ui->upTo8Channels_label_3->setText(tr("Up to %1 channels").arg(m_channelMudbusNum));
                //初始化界面
                modbusChannelInit();
                modbusChannelGetData();

                QVariantList list;
                QVariantMap map;
                map.insert("closeWaitPage",true);
                map.insert("channelMudbusNum",m_channelMudbusNum);
                list.append(map);
                emit requestToDevice(i,list);
                break;
            }
            case UCXX52DealThread::PAGE_SETTING:{
                if(m_generalPageInfo.application_mode == QunpUCXX52::APP_URSALINK_CLOUD && m_proName.contains("UC3")){
                    showWarning(this,tr("Attention"),tr("You have enabled Cloud Mode, now you can only configure your device on IoT Cloud."));
                    return;
                }
                break;
            }
            case UCXX52DealThread::PAGE_UPGRADE:{
                break;
            }
            default:{
                emit requestToDevice(i,QVariantList());
                break;
            }
            }
            ui->stackedWidget->setCurrentIndex(i);
            break;
        }
    }
}

/**
 * 接受状态页返回数据
 * @brief UCXX52Model::onRecvDeviceStatus
 * @param info
 */
void UCXX52Model::onRecvDeviceStatus(UCXX52DealThread::StructPageStatus info)
{
    m_statusPageInfo = info;
    m_proName = basicChangeNameLoraFreq(info.proName);
    ui->modelValue_label->setText(m_proName);
    ui->modelNameNow_label->setText(m_proName);
    ui->serialNumberValue_label->setText(info.sn);
    ui->firmwareVer_label->setText(info.swVer);
    ui->hardVer_label->setText(info.hwVer);
    ui->pnValue_label->setText(info.pn);
    ui->modelNameNow_label->setText(m_proName);
    if(ui->modelValue_label->text().contains(ui->pnValue_label->text()) && !ui->pnValue_label->text().isEmpty()){
        ui->modelValue_label->setText(ui->modelValue_label->text().remove("-"+ui->pnValue_label->text()));
        ui->modelNameNow_label->setText(ui->modelValue_label->text());
    }

    ui->firmwareVerNow_label->setText(info.hwVer);
    ui->hardwareVerNow_label->setText(info.swVer);

    ui->localTimeValue_label->setText(info.time);
    ui->signalLevelValue_label->setText(info.mobileSignal.trimmed());
    ui->inputStatusValue_label->setText(info.inputioStatus);
    ui->outputStatus_label->setText(info.outputioStatus);

    ui->joinStatus_label->setText(info.join_status.toInt()==1 ? tr("Activate") : tr("De-Activate"));
    QString labelColor = QString(info.join_status.toInt()==1 ? "font-size:13px;font-family:\"Arial\";color: rgb(0, 100, 0);" : "font-size:13px;font-family:\"Arial\";color: rgb(255, 0, 0);");
    ui->joinStatus_label->setStyleSheet(labelColor);
    ui->rssiSnr_label->setText(info.rssi+"/"+info.snr);
    ui->datarate_label->setText(ui->datarate_cbx->itemText(info.datarate.toInt()));
    ui->rx2dr_label->setText(ui->rx2Datarate_cbx->itemText(info.rx2dr.toInt()));
    ui->uplinkCounter_label->setText(info.cur_up_link_counter);
    ui->downlinkCounter_label->setText(info.cur_down_link_counter);
    m_generalPageInfo.application_mode = info.application_mode;

    ui->freCN470_frame->setVisible(m_statusPageInfo.oem.toInt() == OEM_LINKWAN);

    if(m_statusPageInfo.swVer.toDouble() > 2.99){
        ui->loraAlarmConfirm_frame->setVisible(false);
        ui->loraTimeValue_frame->setVisible(false);
        ui->modbusGpioSetting_gb->setVisible(true);
        ui->if_cbx->setItemText(ui->if_cbx->findData(UCXX52DealThread::IC_Time),tr("Time(local time)"));
        m_channelMudbusNum = 16;
    }else{
        ui->if_cbx->setItemText(ui->if_cbx->findData(UCXX52DealThread::IC_Time),tr("Time(0 time zone)"));
        ui->loraTimeValue_frame->setVisible(true);
        m_channelMudbusNum = 8;
    }

    switch (info.mobileState.toInt()) {
    case QunpUCXX52::UNP_MOBILE_POWEROFF:
        ui->gsmStatus_label->setText(tr("OFF"));
        break;
    case QunpUCXX52::UNP_MOBILE_NOTREGISTER:
        ui->gsmStatus_label->setText(tr("Not registered on network"));
        break;
    case QunpUCXX52::UNP_MOBILE_REGISTERED:
        ui->gsmStatus_label->setText(tr("Registered"));
        break;
    default:
        break;
    }

    if(m_dealThread->structSupportModel.lora){
        ui->if_cbx->removeItem(ui->if_cbx->findData(UCXX52DealThread::IC_PSQ));
        ui->then1_cbx->removeItem(ui->then1_cbx->findData(UCXX52DealThread::TC_StatusMessage));
        ui->then2_cbx->removeItem(ui->then2_cbx->findData(UCXX52DealThread::TC_StatusMessage));
        ui->then3_cbx->removeItem(ui->then3_cbx->findData(UCXX52DealThread::TC_StatusMessage));

        foreach (QLineEdit *e, modbusChannelQuantityList) {
            e->setEnabled(false);
            e->setText("1");
        }

        if(m_statusPageInfo.swVer.toDouble() > 3.0){
            if(ui->if_cbx->findData(UCXX52DealThread::IC_Counter1) == -1){
                ui->if_cbx->insertItem(UCXX52DealThread::IC_Counter1,tr("Counter1"));
                ui->if_cbx->setItemData(ui->if_cbx->findText(tr("Counter1")),UCXX52DealThread::IC_Counter1);
            }
        }else{
            ui->if_cbx->removeItem(ui->if_cbx->findData(UCXX52DealThread::IC_Counter1));
        }
    }else{
        ui->loraTimeValue_frame->setVisible(true);
        foreach (QLineEdit *e, modbusChannelQuantityList) {
            e->setEnabled(true);
        }
        if(m_statusPageInfo.swVer.toDouble() < 4.03){
            m_channelMudbusNum = 8;
            ui->if_cbx->removeItem(ui->if_cbx->findData(UCXX52DealThread::IC_Counter1));
        }else{
            m_channelMudbusNum = 16;
            if(ui->if_cbx->findData(UCXX52DealThread::IC_Counter1) == -1){
                ui->if_cbx->insertItem(UCXX52DealThread::IC_Counter1,tr("Counter1"));
                ui->if_cbx->setItemData(ui->if_cbx->findText(tr("Counter1")),UCXX52DealThread::IC_Counter1);
            }
        }
#ifndef OEM_LHR_MQTTUSERNAME_LEN64
        if(m_statusPageInfo.swVer.toDouble() < 4.05){
            if(ui->modbusApplicationMode_cbx->findData(QunpUCXX52::APP_ONENET) == -1){
                ui->modbusApplicationMode_cbx->addItem("OneNET",QunpUCXX52::APP_ONENET);
            }
        }
#endif
    }

    if(m_dealThread->structSupportModel.uraws){//Ursalink Cloud
        if(ui->modbusApplicationMode_cbx->findData(QunpUCXX52::APP_URSALINK_CLOUD) == -1){
            ui->modbusApplicationMode_cbx->addItem("Ursalink Cloud",QunpUCXX52::APP_URSALINK_CLOUD);
        }
    }
    if(m_dealThread->structSupportModel.aws){
        if(ui->modbusApplicationMode_cbx->findData(QunpUCXX52::APP_AWS) == -1){
            ui->modbusApplicationMode_cbx->addItem("AWS",QunpUCXX52::APP_AWS);
        }
    }

    if(m_dealThread->structSupportModel.data ){
#ifndef ODM_LHR_AZURE
        if(ui->modbusApplicationMode_cbx->findData(QunpUCXX52::APP_TCP) == -1){
            ui->modbusApplicationMode_cbx->addItem("TCP",QunpUCXX52::APP_TCP);
        }

        if(ui->modbusApplicationMode_cbx->findData(QunpUCXX52::APP_UDP) == -1){
            ui->modbusApplicationMode_cbx->addItem("UDP",QunpUCXX52::APP_UDP);
        }

        if(ui->modbusApplicationMode_cbx->findData(QunpUCXX52::APP_MQTT) == -1){
            ui->modbusApplicationMode_cbx->addItem("MQTT",QunpUCXX52::APP_MQTT);
        }
#endif
    }else{
        ui->then1_cbx->removeItem(ui->then1_cbx->findData(UCXX52DealThread::TC_ALARM));
        ui->then2_cbx->removeItem(ui->then2_cbx->findData(UCXX52DealThread::TC_ALARM));
        ui->then3_cbx->removeItem(ui->then3_cbx->findData(UCXX52DealThread::TC_ALARM));
    }

    if(m_proName.at(3) == '5'){
        if(ui->modbusApplicationMode_cbx->findData(QunpUCXX52::APP_ALI) == -1){
            ui->modbusApplicationMode_cbx->addItem("Aliyun",QunpUCXX52::APP_ALI);
        }
    }
    ui->modbusApplicationMode_cbx->setCurrentIndex(-1);

//    if(ui->then3_cbx->findData(UCXX52DealThread::TC_Output2) == -1){
//        ui->then3_cbx->insertItem(UCXX52DealThread::TC_Output2,"Output2");
//        ui->then3_cbx->setItemData(ui->then3_cbx->findText("Output2"),UCXX52DealThread::TC_Output2);
//    }

//    ui->if_cbx->removeItem(ui->if_cbx->findData(UCXX52DealThread::IC_Analog1));
//    ui->if_cbx->removeItem(ui->if_cbx->findData(UCXX52DealThread::IC_Analog2));
//    ui->if_cbx->removeItem(ui->if_cbx->findData(UCXX52DealThread::IC_CHANNEL));
//    ui->if_cbx->removeItem(ui->if_cbx->findData(UCXX52DealThread::IC_Counter1));
//    ui->if_cbx->removeItem(ui->if_cbx->findData(UCXX52DealThread::IC_Counter2));

    emit waitingVisible(false);
}

/**===========================================UPGRADE===========================================*/
void UCXX52Model::on_brows_btn_clicked()
{
    QSettings settings(m_iniPath, QSettings::IniFormat);
    QString extFileName = QFileDialog::getOpenFileName(this, tr("Choise Image File"), settings.value("ImageFilePath/imageFilePath").toString(), tr("File (*.bin);"));
    if(!extFileName.isEmpty()){
       settings.setValue("ImageFilePath/imageFilePath",extFileName.left(extFileName.lastIndexOf('/')));
       ui->browse_lineedit->setText(extFileName);
    }
}

void UCXX52Model::on_browsUboot_btn_clicked()
{
    QSettings settings(m_iniPath, QSettings::IniFormat);
    QString extFileName = QFileDialog::getOpenFileName(this, tr("Choise Uboot File"), settings.value("ImageFilePath/UbootFilePath").toString(), tr("File (*.bin);"));
    if(!extFileName.isEmpty()){
       settings.setValue("ImageFilePath/UbootFilePath",extFileName.left(extFileName.lastIndexOf('/')));
       ui->browseUboot_lineedit->setText(extFileName);
    }
}

void UCXX52Model::onUpgradePregressChanged(int progress)
{
    if(progress == RequestError){
        m_upgradeWnd->close();
        showWarning(this,tr("Attention"),tr("Sorry,update failure:unknow error!"));

    }else if(progress == FileOpenFail){

        showWarning(this,tr("Attention"),tr("Sorry,update failure:the image file is not available!"));
        m_upgradeWnd->close();

    }else if(progress == FileOpenFail1){
        m_upgradeWnd->close();
        showWarning(this,tr("Attention"),tr("Sorry,update failure:the image file is not available!"));


    }else if(progress == SpaceError){
        m_upgradeWnd->close();
        showWarning(this,tr("Attention"),tr("Sorry,update failure:Insufficient space,please clear the data."));

    }else if(progress == UpgradeOK){

        m_upgradeWnd->onProgressChanged(100);
        m_upgradeWnd->close();
        m_upgradeWnd->onProgressChanged(0);

        showWarning(this,tr("Attention"),tr("Validation successful! The file starts to programm into the device."));
        ui->checkUpdateTip_label->clear();
        ui->checkForUpdate_btn->setText(tr("Up to date"));

    }else if(progress == ResetOK){

        showWarning(this,tr("Attention"),tr("Reset successfully!"));
        ui->checkUpdateTip_label->clear();
        ui->checkForUpdate_btn->setText(tr("Up to date"));

    }else if(progress == ResetFail){

        showWarning( this,tr("Attention"),tr("Fail to reset!"));
        ui->checkUpdateTip_label->clear();
        ui->checkForUpdate_btn->setText(tr("Up to date"));
    }else if(progress == UpgradePassword){
        m_upgradeWnd->show();
        m_upgradeWnd->onProgressChanged(0);
        emit waitingVisible(false);

    }else{
        m_upgradeWnd->show();
        m_upgradeWnd->onProgressChanged(progress);
    }

}

void UCXX52Model::on_upgradeFirmware_btn_clicked()
{
    QVariantList list;
    QVariantMap map;

    QString pathName = ui->browse_lineedit->text().trimmed();

    if(pathName.trimmed().isEmpty()){
        showWarning(this,tr("Attention"),tr("Please choose image"));
        return;
    }

    if(!ui->hardwareVerNow_label->text().isEmpty()){
        if(m_oemver == OEM_LINKWAN){
            //该设备只支持Linkwan版本升级.The device only supports Linkwan version upgrade.
            QString imagename = pathName.mid(pathName.lastIndexOf("/")+1,-1);
            if(imagename.split(".").at(1).toInt() != OEM_LINKWAN){
                showWarning(this,tr("Attention"),tr("The device only supports Linkwan version upgrade."));
                return;
            }
        }
    }
    if(m_bNFC){
        map.insert("password",m_loginPwd);
        m_upgradeWnd->setTipText(tr("Upgrading. Please keep the device close to the NFC reader during the upgrade, the device will restart automatically when the upgrade is complete."));
    }else{
        m_upgradeWnd->setTipText(tr("Upgrading, please do not power off the device, after the upgrading has completed, the device will automactically restart."));
    }

    map.insert("imageName",pathName);
    list.append(map);
    emit requestToDevice(UCXX52DealThread::PAGE_UPGRADE,list);
    m_upgradeWnd->show();
}

/**
 * 重置设备
 * @brief UCXX52Model::on_reset_btn_clicked
 */
void UCXX52Model::on_reset_btn_clicked()
{
    bool ok = true;
    QVariantList list;
    QVariantMap map;
    QSettings settings(m_iniPath, QSettings::IniFormat);

    settings.beginGroup("CloseTipAgain");
    if(settings.value("reset").toBool()){
        if(showQuestion(this,tr("Attention"),MyMessageBox::TYPE_CLOSE_WND,tr("This operation will reset the device to the factory default, please backup and save the configuration before running the reset.")) == QMessageBox::Ok){
            ok = true;
        }else{
            ok = false;
        }
    }
    settings.endGroup();

    if(ok){
        if(m_bNFC){
//            m_nfcPwdWnd->setExecutions(ui->reset_btn->objectName());
            map.insert("password",m_nfcPwdWnd->pwd);
            list.append(map);
            emit requestToDevice(UCXX52DealThread::CONFIG_RESET,list);

        }else{
           emit requestToDevice(UCXX52DealThread::CONFIG_RESET,QVariantList());
        }
    }
    return;
}

/**
 * @brief UCXX52Model::thresholdOverBelow
 * @param over
 * @param below
 * @param grater
 * @param less
 * @return
 */
bool UCXX52Model::thresholdOverBelow(QString over, QString below, QString grater, QString less)
{
    if(!over.isEmpty() && !below.isEmpty()){

        if(over.toDouble() < less.toDouble() ||
                over.toDouble() > grater.toDouble() ||
                below.toDouble() < less.toDouble() ||
                below.toDouble() > grater.toDouble() ||
                over.toDouble() == below.toDouble()){
            return false;

        }
    }else if(over.isEmpty() && !below.isEmpty()){

        if( below.toDouble() < less.toDouble() ||
                below.toDouble() > grater.toDouble()){
            return false;
        }
    }else if(!over.isEmpty() && below.isEmpty()){

        if( over.toDouble() < less.toDouble() ||
                over.toDouble() > grater.toDouble()){
            return false;
        }
    }else if(over.isEmpty() && below.isEmpty()){
        return false;
    }
    return true;
}

QString UCXX52Model::hexTobin4bit(QString strHex)
{
    QString hexMessage = strHex;
    bool OK;
    int val = hexMessage.toInt(&OK,16);//十六进制读取
    hexMessage = hexMessage.setNum(val,2);//显示为2进制
    if(hexMessage.length() < 4)//4bit
    {
       QString temp = "0";
       for(int i =1; i < 4 - hexMessage.length(); i++)
       {
          temp.append("0");//不足16 高位补0
       }
       hexMessage=temp.append(hexMessage);
    }
    return hexMessage;
}

/**
 * @brief uboxTool::hexTobin16bit
 * @param strHex
 * @return
 */
QString UCXX52Model::hexTobin16bit(QString strHex)
{
    QString hexMessage = strHex;
    bool OK;
    int val = hexMessage.toInt(&OK,16);//十六进制读取
    hexMessage = hexMessage.setNum(val,2);//显示为2进制

    if(hexMessage.length() < 16)//16bit
    {
       QString temp = "0";
       for(int i =1; i < 16 - hexMessage.length(); i++)
       {
          temp.append("0");//不足16 高位补0
       }
       hexMessage=temp.append(hexMessage);
    }
    return hexMessage;
}

/**
 * 16进制转字符串list
 * @brief uboxTool::hexTolist
 * @param hex
 * @param extNum
 * @return
 */
QStringList UCXX52Model::hexTolist(QString hex,int extNum)
{
    QStringList ret;
    for(int i=0; i<16; i++){
        if(hex.at(15-i) == '1'){
            ret.append(QString::number(i+extNum));
        }
    }
    return ret;
}


void UCXX52Model::changeEvent(QEvent *e)
{

    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

