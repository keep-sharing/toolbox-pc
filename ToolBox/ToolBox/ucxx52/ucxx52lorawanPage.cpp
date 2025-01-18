#include "ucxx52model.h"
#include "ui_ucxx52model.h"

static bool compareByAsc(const QString &s1, const QString &s2);

//根据SN升序
static bool compareByAsc(const QString &s1, const QString &s2)
{
    if(s1.toInt() < s2.toInt()){
        return true;
    }
    else{
        return false;
    }
}


void UCXX52Model::initLorawanSetting()
{
#ifdef OEM_LHR_MILESIGHT
//    ui->logo_btn->setIcon(QIcon(":/new/image/MilesightLogo.png"));
//    ui->fixedLoraChannelEnableIndex_lineedit->setValidator(new QRegExpValidator(QRegExp("^[0-9]+$")));
//    ui->fixedLoraChannelEnableIndex_lineedit->setMaxLength(2);
//    ui->cellularTip_11->setToolTip(tr("You can only enable one channel."));

//    ui->channelAll_cb->setVisible(false);
//    ui->loraFixedChannelTitle_label->setText("Channel Plan");
//    ui->loraFixedChannelTitle_label_2->setText("Channel Plan");
//    ui->maxDatarate_label->setText(tr("Spread Factor"));
//    ui->minDatarate_label->setVisible(false);

    maxcbxList.clear();
    maxcbxList<<ui->maxDatarate0_cbx<<ui->maxDatarate1_cbx<<ui->maxDatarate2_cbx <<ui->maxDatarate3_cbx<<ui->maxDatarate4_cbx<<ui->maxDatarate5_cbx<<ui->maxDatarate6_cbx<<ui->maxDatarate7_cbx;
    QList<QComboBox *> mincbx;
    mincbx<<ui->minDatarate0_cbx<<ui->minDatarate1_cbx<<ui->minDatarate2_cbx <<ui->minDatarate3_cbx<<ui->minDatarate4_cbx<<ui->minDatarate5_cbx<<ui->minDatarate6_cbx<<ui->minDatarate7_cbx;
    for (int i=0; i<maxcbxList.size(); i++) {
        maxcbxList.at(i)->setEnabled(true);
//        mincbx.at(i)->setVisible(false);
    }

#else

    ui->fixedLoraChannelEnableIndex_lineedit->setValidator(new QRegExpValidator(QRegExp("^[0-9allALL,-]+$")));
    ui->frame_96->setVisible(false);
    QList<QCheckBox*> cb;
    cb<<ui->channel0_cb<<ui->channel1_cb<<ui->channel2_cb<<ui->channel3_cb<<ui->channel4_cb<<ui->channel5_cb<<ui->channel6_cb<<ui->channel7_cb;
    foreach (QCheckBox *c, cb) {
        connect(c,SIGNAL(clicked(bool)),this,SLOT(onCheckChannelAllClicked()));
    }
    QList<QLineEdit*> le;
    le<<ui->frequency0_lineedit<<ui->frequency1_lineedit<<ui->frequency2_lineedit<<ui->frequency3_lineedit<<ui->frequency4_lineedit<<ui->frequency5_lineedit<<ui->frequency6_lineedit<<ui->frequency7_lineedit;
    foreach (QLineEdit *let, le) {
        let->setValidator(new QRegExpValidator(QRegExp("^[0-9]+([.]{1}[0-9]+){0,1}$")));
    }
#endif
}
/**
 * 点击Tab标签
 * @brief uboxTool::on_tabWidget_2_tabBarClicked
 * @param index
 */
void UCXX52Model::on_tabWidget_2_tabBarClicked(int index)
{
    QVariantMap map;
    if(index == LG_BASIC){
        map.insert("readIndex",LG_BASIC);
        m_loraReadIndex = LG_BASIC;

    }else if(index == LG_ADVANCED){
        map.insert("readIndex",LG_ADVANCED);
        m_loraReadIndex = LG_ADVANCED;

    }else if(index == LG_CHANNEL){
        map.insert("readIndex",LG_CHANNEL);
        m_loraReadIndex = LG_CHANNEL;
    }

    QVariantList list;
    list.append(map);
    emit requestToDevice(UCXX52DealThread::PAGE_LORAWAN,list);

}

/**
 * 接收Lorewan页面返回数据
 * @brief UCXX52Model::onRecvLorawan
 * @param info
 */
void UCXX52Model::onRecvLorawan(StructPageLorawan info)
{
    m_lorawanPageInfo = info;
    ui->writeAll_btn->setVisible(false);
    qDebug()<<m_loraReadIndex;
    if((m_loraReadIndex == LG_BASIC || m_loraReadIndex == LG_ALL) && !m_bLoraBasicSave ){
        ui->deviceEUI_lineedit->setText(info.devEui.toUpper());
        ui->appEUI_lineedit->setText(info.appEui.toUpper());
        ui->appKey_lineEdit->setText(info.appKey);
        ui->networkID_lineEdit->setText(info.netId);
        ui->devAddr_lineEdit->setText(info.devAddr);
        ui->ApplicationPort_lineedit->setText(info.appPort);
        ui->loraRs232Port_lineedit->setText(info.rs232Port);
        ui->networkSessionKey_lineEdit->setText(info.nwksKey);
        ui->appSessionKey_lineEdit->setText(info.appsKey);
        ui->datarate_cbx->setCurrentIndex(ui->datarate_cbx->findData(info.defDr.toInt()));
        ui->adrMode_cb->setChecked(info.adr.toInt()==1?true:false);
        ui->adrSpr_cbx->setCurrentIndex(ui->adrSpr_cbx->findData(info.defDr.toInt()));
        ui->adrSpr_frame->setVisible(false);
        ui->loraRegularConfirmed_cb->setChecked(info.confirm.toInt() == 3 || info.confirm.toInt() == 2);
        ui->loraAlarmConfirm_cb->setChecked(info.confirm.toInt() == 3 || info.confirm.toInt() == 1);
        connect(ui->adrMode_cb, &QCheckBox::clicked, this, [=] (){
           ui->adrSpr_frame->setVisible(false);
        },Qt::UniqueConnection);

        ui->joinType_cbx->setCurrentIndex(info.ota.toInt()); //0=OTAA 1=ABP
        on_joinType_cbx_currentIndexChanged(info.ota.toInt());
        ui->loraVersion_cbx->setCurrentIndex(ui->loraVersion_cbx->findData(info.loraVersion.toInt()));

        ui->freCN470_cbx->setCurrentIndex(info.linkwanFreqMode.toInt() == 1? 0 : 1);

        ui->datarate_frame->setVisible(true);

        ui->appKey_lineEdit->setText("********************************");
        ui->devAddr_lineEdit->setText("********************************");
        ui->networkSessionKey_lineEdit->setText("********************************");
        ui->appSessionKey_lineEdit->setText("********************************");
    }

    if((m_loraReadIndex == LG_CHANNEL || m_loraReadIndex == LG_ALL) && !m_bLoraChannelSave ){
        setLoraChannelData(info);
    }

    if((m_loraReadIndex == LG_ADVANCED || m_loraReadIndex == LG_ALL) && !m_bLoraAdvancedSave){
//        ui->confirmMode_cb->setChecked(info.confirm.toInt()==1?true:false);
        ui->txPower_lineedit->setText(info.txPower);
        ui->receDelay1_lineedit->setText(info.rxWinDelay1);
        ui->receDelay2_lineedit->setText(info.rxWinDelay2);
        ui->joinDelay_lineedit->setText(info.joinDelay1);
        ui->joinTrials_lineedit->setText(info.joinRetries);
        ui->retx_lineedit->setText(info.retriesTx);
        ui->rx2ChannelFreq_lineedit->setText(QString::number(info.win2Feq.toDouble()/1000000));
        if(info.win2Dr.toInt()<6){
            ui->rx2Datarate_cbx->setCurrentIndex(info.win2Dr.toInt());
        }
        ui->ackTimeout_lineedit->setText(info.ackTimeout);
        ui->dutyCycleSwitch_cb->setChecked(info.dutyCycleOn.toInt()!=0?true:false);
        ui->dutyCycle_lineedit->setText(info.globalDutyRate);
        ui->uplinkFrameCounter_lineEdit->setText(info.upLinkCounter);
        ui->downlinkFrameCounter_lineEdit->setText(info.downLinkCounter);
    }
    ui->adrSpr_cbx->setCurrentIndex(ui->adrSpr_cbx->findData(info.defDr.toInt()));
    ui->datarate_cbx->setCurrentIndex(ui->datarate_cbx->findData(info.defDr.toInt()));

    emit waitingVisible(false);
}
/**
 * 保存lora basic页面数据
 * @brief UCXX52Model::on_generalBasicSave_btn_clicked
 */
bool UCXX52Model::on_generalBasicSave_btn_clicked()
{
    QList<QLineEdit*> allle;
    allle<<ui->deviceEUI_lineedit<<ui->appEUI_lineedit
        <<ui->appKey_lineEdit <<ui->ApplicationPort_lineedit<<ui->loraRs232Port_lineedit<<ui->devAddr_lineEdit<<ui->networkID_lineEdit<<ui->networkSessionKey_lineEdit<<ui->appSessionKey_lineEdit;
    foreach (QLineEdit *e, allle) {
        e->setStyleSheet(RECOVERY_INPUT);
    }
    if(ui->deviceEUI_lineedit->text().length()<16 && ui->deviceEUI_lineedit->isVisible()){
        ui->deviceEUI_lineedit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("Please enter a 16 character device EUI."));
        return false;
    }
    if(ui->appEUI_lineedit->text().length()<16 && ui->appEUI_lineedit->isVisible() ){
        ui->appEUI_lineedit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("Please enter a 16 character App EUI."));
        return false;
    }
    if((ui->ApplicationPort_lineedit->text().toInt() > 223 || ui->ApplicationPort_lineedit->text().toInt() <1 ) && ui->ApplicationPort_lineedit->isVisible()){
        ui->ApplicationPort_lineedit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("The value you entered is out of the valid range.Valid Range: 1 - 223."));
        return false;
    }
    if((ui->loraRs232Port_lineedit->text().toInt() > 223 || ui->loraRs232Port_lineedit->text().toInt() <1 ) && ui->loraRs232Port_lineedit->isVisible() ){
        ui->loraRs232Port_lineedit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("The value you entered is out of the valid range.Valid Range: 1 - 223."));
        return false;
    }
    QList<QLineEdit*> le;
    bool ok=true;
    if(m_lorawanPageInfo.ota == 1){
        le<<ui->devAddr_lineEdit<<ui->networkSessionKey_lineEdit<<ui->appSessionKey_lineEdit;
        foreach (QLineEdit *e, le) {
            if(e->text().isEmpty() && e->isVisible()){
                e->setStyleSheet(ERROR_INPUT);
                ok = false;
            }
        }
        if(!ok){
            showWarning(this,tr("Attention"),tr("Invalid value."));

            return false;
        }
        if(ui->devAddr_lineEdit->text().length() != 8 && ui->devAddr_lineEdit->isVisible() && !ui->devAddr_lineEdit->text().contains("***")){
            ui->devAddr_lineEdit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Please enter a 8 character device address."));

            return false;
        }
        if(ui->networkSessionKey_lineEdit->text().length() != 32 && ui->networkSessionKey_lineEdit->isVisible() && !ui->networkSessionKey_lineEdit->text().contains("***")){
            ui->networkSessionKey_lineEdit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Please enter a 32 character netnwork session key."));

            return false;
        }

        if(ui->appSessionKey_lineEdit->text().length() != 32 && ui->appSessionKey_lineEdit->isVisible() && !ui->appSessionKey_lineEdit->text().contains("***")){
            ui->appSessionKey_lineEdit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Please enter a 32 character application session key."));

            return false;
        }
    }else{
        if(ui->appKey_lineEdit->text().isEmpty() && ui->appKey_lineEdit->isVisible()){
            showWarning(this,tr("Attention"),tr("Invalid value."));

            return false;
        }
        if(ui->appKey_lineEdit->text().length() != 32 && ui->appKey_lineEdit->isVisible()){
            ui->appKey_lineEdit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Please enter a 32 character application key."));

            return false;
        }
    }
    foreach (QLineEdit *e, le) {
        if(e->text().isEmpty()){
            e->setStyleSheet(RECOVERY_INPUT);
        }
    }

    QVariantMap map;
    QString comf ;
    if(ui->loraRegularConfirmed_cb->isChecked()){
        comf = "1";
    }else {
        comf = "0";
    }

    if(ui->loraAlarmConfirm_cb->isChecked()){
        comf += "1";
    }else {
        comf += "0";
    }
    bool z=true;

    map.insert("devEui",ui->deviceEUI_lineedit->text().trimmed());
    map.insert("appEui",ui->appEUI_lineedit->text().trimmed());
    map.insert("appPort",ui->ApplicationPort_lineedit->text().trimmed());
    map.insert("rs232Port",ui->loraRs232Port_lineedit->text().trimmed());
    map.insert("workingMode",(ui->loraWorkingMode_cbx->currentText()=="Class A" ? "0":"2") );
    map.insert("joinType",QString::number(ui->joinType_cbx->currentIndex()));
    map.insert("loraVersion",ui->loraVersion_cbx->currentData().toInt());
    map.insert("appKey",ui->appKey_lineEdit->text());
    map.insert("networkId",ui->networkID_lineEdit->text().trimmed());
    map.insert("devAddr",ui->devAddr_lineEdit->text().trimmed());
    map.insert("networkSessionkey",ui->networkSessionKey_lineEdit->text().trimmed());
    map.insert("appSessionKey",ui->appSessionKey_lineEdit->text().trimmed());
    map.insert("datarate",ui->datarate_cbx->isVisible() ? ui->datarate_cbx->currentData().toInt() : ui->adrSpr_cbx->currentData().toInt());
    map.insert("comfirmMode",QString::number(comf.toInt(&z,2)));
    map.insert("adrMode",(ui->adrMode_cb->isChecked()?"01":"00") );
    map.insert("linkwanFreMode",ui->freCN470_cbx->currentText().contains(tr("同频"))?1:2);
    QVariantList list;

    m_cacheDataMap.insert("loraBasic",map);

    QVariantMap map2;
    map2.insert("basicModify",true);
    map2.insert("channelModify",false);
    map2.insert("loraBasic",map);
    list.append(map2);

    if(m_bNFC){
        m_bLoraBasicSave = true;
        ui->writeAll_btn->setVisible(true);
    }
    emit requestToDevice(UCXX52DealThread::CONFIG_WRITE_LORAWAN,list);
    map.insert("devEui","**********");
    map.insert("appKey","**********");
    map.insert("devAddr","**********");
    map.insert("networkSessionkey","**********");
    map.insert("appSessionKey","**********");
    backupMap.insert("lorawan_basic",map);
    return true;
}

/**
 * advanced 页面保存
 * @brief uboxTool::on_generalBasicSave_btn_clicked
 */
bool UCXX52Model::on_generalJTNSave_btn_clicked()
{
    QList<QLineEdit*> le;
    bool ok=true;
    le<<ui->txPower_lineedit<<ui->joinDelay_lineedit<<ui->receDelay1_lineedit<<ui->receDelay2_lineedit<<ui->joinTrials_lineedit<<ui->retx_lineedit
     <<ui->rx2ChannelFreq_lineedit<<ui->ackTimeout_lineedit<<ui->dutyCycle_lineedit;
    foreach (QLineEdit *e, le) {
        e->setStyleSheet(RECOVERY_INPUT);
    }

    foreach (QLineEdit *e, le) {
        if(e->text().isEmpty()){
            e->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Invalid value."));
            ok = false;
        }
    }
    if(!ok)
        return  false;

    if(ui->txPower_lineedit->text().toInt() > 15){
        ui->txPower_lineedit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("The value you entered is out of the valid range.Valid Range: 0 - 15."));
        return false;
    }

    if(ui->receDelay1_lineedit ->text().toInt() > 3600000){
        ui->receDelay1_lineedit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("The value you entered is out of the valid range.Valid Range: 0 - 3600000."));
        return false;
    }

    if(ui->receDelay2_lineedit ->text().toInt() > 3600000){
        ui->receDelay2_lineedit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("The value you entered is out of the valid range.Valid Range: 0 - 3600000."));
        return false;
    }

    if(ui->joinTrials_lineedit->text().toInt() > 255){
        ui->joinTrials_lineedit->setStyleSheet(ERROR_INPUT);
        showWarning(this,tr("Attention"),tr("The value you entered is out of the valid range.Valid Range: 0 - 255."));
        return false;
    }
    foreach (QLineEdit *e, le) {
        if(e->text().isEmpty()){
            e->setStyleSheet(RECOVERY_INPUT);
        }
    }

     QVariantMap map;
#if 01
    if(ui->uplinkFrameCounter_lineEdit->text().isEmpty()){
        map.insert("uplinkFrameCounter",0);
    }else{
        map.insert("uplinkFrameCounter",ui->uplinkFrameCounter_lineEdit->text().trimmed());
    }
    if(ui->downlinkFrameCounter_lineEdit->text().isEmpty()){
        map.insert("downlinkFrameCounter",0);
    }else{
        map.insert("downlinkFrameCounter",ui->downlinkFrameCounter_lineEdit->text().trimmed());
    }

#endif
    map.insert("txPower",ui->txPower_lineedit->text());
    map.insert("joinDelay1",ui->joinDelay_lineedit->text());
    map.insert("receiveDelay1",ui->receDelay1_lineedit->text());
    map.insert("receiveDelay2",ui->receDelay2_lineedit->text());
    map.insert("joinTrials",ui->joinTrials_lineedit->text());
    map.insert("retx",ui->retx_lineedit->text());
    map.insert("rx2Datarate",ui->rx2Datarate_cbx->currentIndex());
    map.insert("rx2Fre",ui->rx2ChannelFreq_lineedit->text().toFloat()*10000);
    map.insert("actTimeout",ui->ackTimeout_lineedit->text());
    map.insert("dutyCycleSwitch",ui->dutyCycleSwitch_cb->isChecked()?"01":"00");
    map.insert("dutyCycle",ui->dutyCycle_lineedit->text());

    QVariantList list;
    m_cacheDataMap.insert("loraAdvanced",map);

    QVariantMap map2;
    map2.insert("basicModify",false);
    map2.insert("channelModify",false);
    map2.insert("advancedModify",true);
    map2.insert("loraAdvanced",map);
    list.append(map2);

    if(m_bNFC){
        m_bLoraAdvancedSave = true;
        ui->writeAll_btn->setVisible(true);
    }else{
        emit requestToDevice(UCXX52DealThread::CONFIG_WRITE_LORAWAN,list);
    }

    backupMap.insert("lorawan_advance",map);
    return true;
}

void UCXX52Model::setLoraChannelData(StructPageLorawan info)
{
    //channel
    QList<QCheckBox*> cb;
    cb<<ui->channel0_cb<<ui->channel1_cb<<ui->channel2_cb<<ui->channel3_cb<<ui->channel4_cb<<ui->channel5_cb<<ui->channel6_cb<<ui->channel7_cb;

    QList<QLineEdit*> le;
    le <<ui->frequency0_lineedit<<ui->frequency1_lineedit<<ui->frequency2_lineedit<<ui->frequency3_lineedit<<ui->frequency4_lineedit<<ui->frequency5_lineedit<<ui->frequency6_lineedit<<ui->frequency7_lineedit;

    foreach (QCheckBox *c, cb) {
        c->setChecked(false);
        c->setEnabled(true);
    }
    foreach (QLineEdit *l, le) {
        l->setText("0");
        l->setEnabled(false);
    }

//    info.region = US915;
    qDebug()<<"region: "<<info.region;
    defaultFre.clear();

    QStringList frelist;
    QVariantMap channelMap;
    switch (info.region.toInt()) {
    case CN470:{

        frelist.clear();
        frelist<<"CN470";

        m_freMin = float(470.3);
        m_freMax = float(489.3);
        m_rxFreMax = float(500.3);
        m_rxFreMax = float(509.7);

        ui->loraFixedChannelNote_label->setText(tr("Note: \n"
                                                "80 channels numbered 0 to 79 utilizing LoRa 125 kHz BW starting at 470.3 MHz and incrementing linearly by 0.2 MHz to 486.1\n"
                                                "16 channels numbered 80 to 95 utilizing LoRa 125 kHz BW starting at 486.3 MHz and incrementing linearly by 1.6 MHz to 489.3"));
        ui->loraChannel_stackedWidget->setCurrentIndex(1);
        channelMap.insert("fixFre1","470.3 - 473.3");
        channelMap.insert("fixInt1","0.2");
        channelMap.insert("fixBW1" ,"125");

        channelMap.insert("fixFre2","473.5 - 476.5");
        channelMap.insert("fixInt2","0.2");
        channelMap.insert("fixBW2" ,"125");

        channelMap.insert("fixFre3","476.7 - 479.7");
        channelMap.insert("fixInt3","0.2");
        channelMap.insert("fixBW3" ,"125");

        channelMap.insert("fixFre4"," 479.9 - 482.9");
        channelMap.insert("fixInt4","0.2");
        channelMap.insert("fixBW4" ,"125");

        channelMap.insert("fixFre5","483.1 - 486.1");
        channelMap.insert("fixInt5","0.2");
        channelMap.insert("fixBW5" ,"125");
        channelMap.insert("fixIndex5","64 - 79");

        channelMap.insert("fixFre6","486.3 - 489.3");
        channelMap.insert("fixInt6","0.2");
        channelMap.insert("fixBW6" ,"125");
        setLoraChannelFixFre(channelMap,true);

    }
        break;
    case EU433:{
        frelist.clear();
        frelist<<"EU433";

        m_freMin = float(433.175);
        m_freMax = float(434.665);
        defaultFre<<"433.175"<<"433.375"<<"433.575";
        ui->loraChannel_stackedWidget->setCurrentIndex(0);
    }
        break;
    case AS923:{
        frelist.clear();
        frelist<<"AS923"<<"AU915"<<"US915"<<"KR920";

        m_freMin = 920.0;
        m_freMax = 925.0;

        defaultFre<<"923.2"<<"923.4";
        ui->loraChannel_stackedWidget->setCurrentIndex(0);
    }
        break;
    case AU915:{

        frelist.clear();
        frelist<<"AU915"<<"US915"<<"AS923"<<"KR920";

        m_freMin = float(915.2);
        m_freMax = float(927.1);
//            ui->loraFixedChannelTitle_label->setText("Support Frequency : AU915");
        ui->loraFixedChannelNote_label->setText(tr("Note: \n"
                                                "64 channels numbered 0 to 63 utilizing LoRa 125 kHz BW starting at 915.2 MHz and incrementing linearly by 0.2 MHz to 927.8\n"
                                                "8 channels numbered 64 to 71 utilizing LoRa 500 kHz BW starting at 915.9 MHz and incrementing linearly by 1.6 MHz to 927.1"));
        ui->loraChannel_stackedWidget->setCurrentIndex(1);
        channelMap.insert("fixFre1","915.2 - 918.2");
        channelMap.insert("fixInt1","0.2");
        channelMap.insert("fixBW1" ,"125");

        channelMap.insert("fixFre2","918.4 - 921.4");
        channelMap.insert("fixInt2","0.2");
        channelMap.insert("fixBW2" ,"125");

        channelMap.insert("fixFre3","921.6 - 924.6");
        channelMap.insert("fixInt3","0.2");
        channelMap.insert("fixBW3" ,"125");

        channelMap.insert("fixFre4","924.8 - 927.8");
        channelMap.insert("fixInt4","0.2");
        channelMap.insert("fixBW4" ,"125");

        channelMap.insert("fixFre5","915.9 - 927.1");
        channelMap.insert("fixInt5","1.6");
        channelMap.insert("fixBW5" ,"500");
        channelMap.insert("fixIndex5","64 - 71");
        setLoraChannelFixFre(channelMap,false);
    }
        break;
    case EU868:{
        frelist.clear();
        frelist<<"EU868"<<"IN865"<<"RU864";

        m_freMin = 863.0;
        m_freMax = 870.0;

        defaultFre<<"868.1"<<"868.3"<<"868.5";
        ui->loraChannel_stackedWidget->setCurrentIndex(0);
    }
        break;
    case KR920:{
        frelist.clear();
        frelist<<"KR920"<<"AU915"<<"US915"<<"AS923";

        m_freMin = float(920.9);
        m_freMax = float(923.3);

        defaultFre<<"922.1"<<"922.3"<<"922.5";
        ui->loraChannel_stackedWidget->setCurrentIndex(0);
    }
        break;
    case IN865:{
        frelist.clear();
        frelist<<"IN865"<<"RU864"<<"EU868";

        m_freMin = 865.0;
        m_freMax = 867.0;

        defaultFre<<"865.0625"<<"865.4025"<<"865.985";
        ui->loraChannel_stackedWidget->setCurrentIndex(0);
    }
        break;
    case US915:{
        frelist.clear();
        frelist<<"US915"<<"AU915"<<"AS923"<<"KR920";

        m_freMin = float(902.3);
        m_freMax = float(914.2);
        ui->loraFixedChannelNote_label->setText(tr("Note: \n"
                                                "64 channels numbered 0 to 63 utilizing LoRa 125 kHz BW starting at 902.3 MHz and incrementing linearly by 0.2 MHz to 914.9\n"
                                                "8 channels numbered 64 to 71 utilizing LoRa 500 kHz BW starting at 903.0 MHz and incrementing linearly by 1.6 MHz to 914.2"));
        ui->loraChannel_stackedWidget->setCurrentIndex(1);
        channelMap.insert("fixFre1","902.3 - 905.3");
        channelMap.insert("fixInt1","0.2");
        channelMap.insert("fixBW1" ,"125");

        channelMap.insert("fixFre2","905.5 - 908.5");
        channelMap.insert("fixInt2","0.2");
        channelMap.insert("fixBW2" ,"125");

        channelMap.insert("fixFre3","908.7 - 911.7");
        channelMap.insert("fixInt3","0.2");
        channelMap.insert("fixBW3" ,"125");

        channelMap.insert("fixFre4","911.9 - 914.9");
        channelMap.insert("fixInt4","0.2");
        channelMap.insert("fixBW4" ,"125");

        channelMap.insert("fixFre5","903.0 - 914.2");
        channelMap.insert("fixInt5","1.6");
        channelMap.insert("fixBW5" ,"500");
        channelMap.insert("fixIndex5","64 - 71");
        setLoraChannelFixFre(channelMap,false);
    }
        break;
    case RU864:{
        frelist.clear();
        frelist<<"RU864"<<"EU868"<<"IN865";

        m_freMin = 864.0;
        m_freMax = 870.0;

        defaultFre<<"868.9"<<"869.1";
        ui->loraChannel_stackedWidget->setCurrentIndex(0);
    }
        break;
    default:
        break;
    }

    if(info.frequencyUpdateFlag != "ZZZZZZ"){
        ui->supportFre_cbx->clear();
        ui->supportFre2_cbx->clear();
        ui->supportFre_cbx->addItems(frelist);
        ui->supportFre2_cbx->addItems(frelist);
    }

    int adrspr = ui->adrSpr_cbx->currentData().toInt();
    int dar = ui->datarate_cbx->currentData().toInt();
    qDebug();
    if(ui->loraChannel_stackedWidget->currentIndex() == 0){
        QString last4 = hexTobin4bit(info.chanMask.mid(2,1));
        QString first4= hexTobin4bit(info.chanMask.mid(3,1));

        qDebug()<<info.chanMask<<hexTobin4bit(info.chanMask.mid(2,1))<<hexTobin4bit(info.chanMask.mid(3,1))
                     <<first4.mid(0,1)<<first4.mid(3,1);
        qDebug()<<info.fre0<<info.fre1<<info.fre2<<info.fre3;

        if(first4.mid(3,1).toInt() !=0 ){
            cb.at(0)->setChecked(true);
        }

        if(first4.mid(2,1).toInt() !=0 ){
            cb.at(1)->setChecked(true);
        }

        if(first4.mid(1,1).toInt() !=0 ){
            cb.at(2)->setChecked(true);
        }

        if(first4.mid(0,1).toInt() !=0 ){
            cb.at(3)->setChecked(true);
        }

        if(last4.mid(3,1).toInt() !=0 ){
            cb.at(4)->setChecked(true);
        }

        if(last4.mid(2,1).toInt() !=0 ){
            cb.at(5)->setChecked(true);
        }

        if(last4.mid(1,1).toInt() !=0 ){
            cb.at(6)->setChecked(true);
        }

        if(last4.mid(0,1).toInt() !=0 ){
            cb.at(7)->setChecked(true);
        }

        le.at(0)->setText(QString::number(QString(info.fre0.mid(0,3)+"."+info.fre0.mid(3,4)).toDouble(),'G',7));
        le.at(1)->setText(QString::number(QString(info.fre1.mid(0,3)+"."+info.fre1.mid(3,4)).toDouble(),'G',7));
        le.at(2)->setText(QString::number(QString(info.fre2.mid(0,3)+"."+info.fre2.mid(3,4)).toDouble(),'G',7));
        le.at(3)->setText(QString::number(QString(info.fre3.mid(0,3)+"."+info.fre3.mid(3,4)).toDouble(),'G',7));
        le.at(4)->setText(QString::number(QString(info.fre4.mid(0,3)+"."+info.fre4.mid(3,4)).toDouble(),'G',7));
        le.at(5)->setText(QString::number(QString(info.fre5.mid(0,3)+"."+info.fre5.mid(3,4)).toDouble(),'G',7));
        le.at(6)->setText(QString::number(QString(info.fre6.mid(0,3)+"."+info.fre6.mid(3,4)).toDouble(),'G',7));
        le.at(7)->setText(QString::number(QString(info.fre7.mid(0,3)+"."+info.fre7.mid(3,4)).toDouble(),'G',7));


        for(int cbi=0; cbi<cb.size(); cbi++){
#ifdef OEM_LHR_MILESIGHT
            maxcbxList.at(cbi)->setEnabled(cb.at(cbi)->isChecked());
            qDebug()<<cbi<<info.defDr;
            if(maxcbxList.at(cbi)->isEnabled()){
                maxcbxList.at(cbi)->setCurrentIndex(info.defDr.toInt());
            }
            le.at(cbi)->setEnabled(cb.at(cbi)->isChecked());
#else
            cb.at(cbi)->setEnabled(defaultFre.indexOf(le.at(cbi)->text()) == -1? true:false);
            le.at(cbi)->setEnabled(defaultFre.indexOf(le.at(cbi)->text()) == -1? cb.at(cbi)->isChecked():false);
#endif


#ifdef OEM_LHR_M2MLab
            cb.at(cbi)->setEnabled(true);
            le.at(cbi)->setEnabled(cb.at(cbi)->isChecked());
#endif
        }
        ui->adrSpr_cbx->clear();
        if(info.region.toInt() == AS923){
            ui->adrSpr_cbx->addItem("SF7-DR5",5);
            ui->adrSpr_cbx->addItem("SF8-DR4",4);
            ui->adrSpr_cbx->addItem("SF9-DR3",3);
            ui->adrSpr_cbx->addItem("SF10-DR2",2);
        }else{
            ui->adrSpr_cbx->addItem("SF7-DR5",5);
            ui->adrSpr_cbx->addItem("SF8-DR4",4);
            ui->adrSpr_cbx->addItem("SF9-DR3",3);
            ui->adrSpr_cbx->addItem("SF10-DR2",2);
            ui->adrSpr_cbx->addItem("SF11-DR1",1);
            ui->adrSpr_cbx->addItem("SF12-DR0",0);
        }


    }else{
        qDebug()<<hexTobin16bit(info.chanMask)<<hexTobin16bit(info.chanMask16_31)<<hexTobin16bit(info.chanMask32_47)
                     <<hexTobin16bit(info.chanMask48_63)<<hexTobin16bit(info.chanMask64_79)<<hexTobin16bit(info.chanMask80_95);

        qDebug()<<hexTolist(hexTobin16bit(info.chanMask))<<hexTolist(hexTobin16bit(info.chanMask16_31),16)<<hexTolist(hexTobin16bit(info.chanMask32_47),32)
                        <<hexTolist(hexTobin16bit(info.chanMask48_63),48)<<hexTolist(hexTobin16bit(info.chanMask64_79),64)<<hexTolist(hexTobin16bit(info.chanMask80_95),80);

        QStringList cm1list = hexTolist(hexTobin16bit(info.chanMask));
        QStringList cm2list = hexTolist(hexTobin16bit(info.chanMask16_31),16);
        QStringList cm3list = hexTolist(hexTobin16bit(info.chanMask32_47),32);
        QStringList cm4list = hexTolist(hexTobin16bit(info.chanMask48_63),48);
        QStringList cm5list = hexTolist(hexTobin16bit(info.chanMask64_79),64);
        QStringList cm6list = hexTolist(hexTobin16bit(info.chanMask80_95),80);

        QList<int> cmAll;
        foreach (QString cm,cm1list) {
            cmAll.append(cm.toInt());
        }
        foreach (QString cm,cm2list) {
            cmAll.append(cm.toInt());
        }
        foreach (QString cm,cm3list) {
            cmAll.append(cm.toInt());
        }
        foreach (QString cm,cm4list) {
            cmAll.append(cm.toInt());
        }
        foreach (QString cm,cm5list) {
            cmAll.append(cm.toInt());
        }
        foreach (QString cm,cm6list) {
            cmAll.append(cm.toInt());
        }

        int index_start = 0;
        QString part;
        QStringList partList;
        bool o = true;
        bool over63 = false;
        bool between163 = false;
        for(int i=1; i<cmAll.size(); i++){
            if(cmAll.at(i) == cmAll.at(index_start) + (i - index_start)){
                part = QString::number(cmAll.at(index_start)) + "-" + QString::number(cmAll.at(i));
                o = false;
            }else{
                if(o && partList.indexOf(QString::number(cmAll.at(0))) == -1){
                    partList.append(QString::number(cmAll.at(0)));
                }
                if((partList.indexOf(part) == -1 || partList.isEmpty()) && !part.isEmpty() ){
                    partList.append(part);
                }
                index_start = i;
                partList.append(QString::number(cmAll.at(i)));
            }
            if(cmAll.at(i) > 63){
                over63 = true;
            }
            if(cmAll.at(i) >= 0 && cmAll.at(i) < 63){
                between163 = true;
            }
        }

        ui->adrSpr_cbx->clear();
        if(ui->supportFre2_cbx->currentText() == "US915"){
            if(over63 && !between163){
                ui->adrSpr_cbx->addItem("SF8-DR4",4);
            }else{
                ui->adrSpr_cbx->addItem("SF7-DR3" ,3);
                ui->adrSpr_cbx->addItem("SF8-DR2" ,2);
                ui->adrSpr_cbx->addItem("SF9-DR1" ,1);
                ui->adrSpr_cbx->addItem("SF10-DR0",0);
            }
        }else if(ui->supportFre2_cbx->currentText() == "AU915"){
            if(over63 && !between163){
                ui->adrSpr_cbx->addItem("SF8-DR6", 6);
            }else{
                ui->adrSpr_cbx->addItem("SF7-DR5" ,5);
                ui->adrSpr_cbx->addItem("SF8-DR4" ,4);
                ui->adrSpr_cbx->addItem("SF9-DR3" ,3);
                ui->adrSpr_cbx->addItem("SF10-DR2",2);
            }
        }else{
            ui->adrSpr_cbx->addItem("SF7-DR5",5);
            ui->adrSpr_cbx->addItem("SF8-DR4",4);
            ui->adrSpr_cbx->addItem("SF9-DR3",3);
            ui->adrSpr_cbx->addItem("SF10-DR2",2);
            ui->adrSpr_cbx->addItem("SF11-DR1",1);
            ui->adrSpr_cbx->addItem("SF12-DR0",0);
        }


        if(cmAll.size() == 1){
            partList.append(QString::number(cmAll.at(0)));
        }else if(partList.indexOf(part) == -1 || partList.isEmpty()){
            partList.append(part);
        }
        qDebug()<<cmAll<<partList<<cmAll.size()<<partList.size();
        for(int i=0; i<partList.size(); i++){
            for(int j=0; j<partList.size(); j++){
                QString t1 = partList.at(i);
                QString t2 = partList.at(j);
                if(t1.contains("-") && !t2.contains("-") && (t1.split("-").at(0)==t2 || t1.split("-").at(1)==t2) ){
                    partList.removeOne(partList.at(j));
                }
            }

        }
        QString txt;
        foreach (QString s, partList) {
            txt += s + ",";
        }
        qDebug()<<partList;
        ui->fixedLoraChannelEnableIndex_lineedit->setText(txt.remove(txt.length()-1,1));
#ifdef OEM_LHR_MILESIGHT
        if(info.region.toInt() == AU915){
            if(ui->fixedLoraChannelDatarate_cbx->findText("6-SF8BW500") == -1){
                ui->fixedLoraChannelDatarate_cbx->addItem("6-SF8BW500");
            }
        }else{
            if(ui->fixedLoraChannelDatarate_cbx->findText("6-SF8BW500") != -1){
                ui->fixedLoraChannelDatarate_cbx->removeItem(ui->fixedLoraChannelDatarate_cbx->findText("6-SF8BW500"));
            }
        }
        ui->fixedLoraChannelDatarate_cbx->setCurrentIndex(info.defDr.toInt());
#endif
    }
    ui->datarate_cbx->clear();
    for(int i=0; i< ui->adrSpr_cbx->count(); i++){
        ui->datarate_cbx->addItem(ui->adrSpr_cbx->itemText(i),ui->adrSpr_cbx->itemData(i));
    }

    ui->datarate_cbx->setCurrentIndex(ui->datarate_cbx->findData(dar) == -1 ? 0 : ui->datarate_cbx->findData(dar));
    ui->adrSpr_cbx->setCurrentIndex(ui->adrSpr_cbx->findData(adrspr) == -1 ? 0 : ui->adrSpr_cbx->findData(adrspr));
}

void UCXX52Model::setLoraChannelFixFre(QVariantMap map,bool lastVis)
{
    ui->freFre_gb_6->setVisible(lastVis);

    ui->fixedFrequency_lineedit->setText(map.value("fixFre1").toString());
    ui->fixedInterval_lineedit->setText(map.value("fixInt1").toString());
    ui->fixedBW_lineedit->setText(map.value("fixBW1").toString());

    ui->fixedFrequency_lineedit_2->setText(map.value("fixFre2").toString());
    ui->fixedInterval_lineedit_2->setText(map.value("fixInt2").toString());
    ui->fixedBW_lineedit_2->setText(map.value("fixBW2").toString());

    ui->fixedFrequency_lineedit_3->setText(map.value("fixFre3").toString());
    ui->fixedInterval_lineedit_3->setText(map.value("fixInt3").toString());
    ui->fixedBW_lineedit_3->setText(map.value("fixBW3").toString());

    ui->fixedFrequency_lineedit_4->setText(map.value("fixFre4").toString());
    ui->fixedInterval_lineedit_4->setText(map.value("fixInt4").toString());
    ui->fixedBW_lineedit_4->setText(map.value("fixBW4").toString());

    ui->fixedFrequency_lineedit_5->setText(map.value("fixFre5").toString());
    ui->fixedInterval_lineedit_5->setText(map.value("fixInt5").toString());
    ui->fixedBW_lineedit_5->setText(map.value("fixBW5").toString());
    ui->fixedChannelIndex_label_5->setText(map.value("fixIndex5").toString());

    ui->fixedFrequency_lineedit_6->setText(map.value("fixFre6").toString());
    ui->fixedInterval_lineedit_6->setText(map.value("fixInt6").toString());
    ui->fixedBW_lineedit_6->setText(map.value("fixBW6").toString());
}

void UCXX52Model::on_joinType_cbx_currentIndexChanged(int index)
{
    ui->loraVersion_cbx->clear();
    if(index == OTA){//OTAAq
        ui->loraVersion_cbx->addItem("V1.0.2",1);
        ui->loraVersion_cbx->addItem("V1.0.3",2);
        ui->loraVersion_cbx->addItem("V1.1.0",3);
        ui->appKey_frame->setVisible(true);
        ui->networkId_frame->setVisible(false);
        ui->devAddr_frame->setVisible(false);
        ui->networkSessionKey_frame->setVisible(false);
        ui->appSessionKey_frame->setVisible(false);
    }
    else{
        ui->loraVersion_cbx->addItem("V1.0.2",1);
        ui->loraVersion_cbx->addItem("V1.0.3",3);
        ui->loraVersion_cbx->setCurrentIndex(1);

        ui->devAddr_lineEdit->setEnabled(true);
        ui->appSessionKey_lineEdit->setEnabled(true);
        ui->networkSessionKey_lineEdit->setEnabled(true);

        ui->appKey_frame->setVisible(false);
        ui->networkId_frame->setVisible(true);
        ui->devAddr_frame->setVisible(true);
        ui->networkSessionKey_frame->setVisible(true);
        ui->appSessionKey_frame->setVisible(true);
    }
}

bool UCXX52Model::on_generalChannelSave_btn_clicked()
{
    QList<QCheckBox*> cb;
    cb<<ui->channel0_cb<<ui->channel1_cb<<ui->channel2_cb<<ui->channel3_cb<<ui->channel4_cb<<ui->channel5_cb<<ui->channel6_cb<<ui->channel7_cb;

    QList<QLineEdit*> le;
    le<<ui->frequency0_lineedit<<ui->frequency1_lineedit<<ui->frequency2_lineedit<<ui->frequency3_lineedit<<ui->frequency4_lineedit<<ui->frequency5_lineedit<<ui->frequency6_lineedit<<ui->frequency7_lineedit;

    bool ischeck = false;
    foreach (QCheckBox *c, cb) {
        if(c->isChecked()){
            ischeck = true;
        }
    }
    if(!ischeck) {
        showWarning(this,tr("Attention"),tr("Please enable at least one channel."));
        return false;
    }

    for(int i=0; i<cb.size(); i++){
        if(cb.at(i)->isChecked()){
            if(le.at(i)->text().toFloat() > m_freMax || le.at(i)->text().toFloat() < m_freMin){
                showWarning(this,tr("Attention"),tr("The value you entered is out of the valid range.Valid Range: %1 - %2").arg((double)m_freMax).arg((double)m_freMin));

                return false;
            }
        }
    }

    for(int i=0; i<le.size(); i++){
        for(int j=0; j<le.size(); j++){
            if(le.at(i)->text() == le.at(j)->text() && i != j && cb.at(i)->isChecked() && cb.at(j)->isChecked()){
                showWarning(this,tr("Attention"),tr("The values you entered cannot be repeated."));
                return false;
            }
        }
    }

    QVariantMap map;

    map.insert("fre0",ui->frequency0_lineedit->text().toFloat() * 10000);
    map.insert("fre1",ui->frequency1_lineedit->text().toFloat() * 10000);
    map.insert("fre2",ui->frequency2_lineedit->text().toFloat() * 10000);
    map.insert("fre3",ui->frequency3_lineedit->text().toFloat() * 10000);
    map.insert("fre4",ui->frequency4_lineedit->text().toFloat() * 10000);
    map.insert("fre5",ui->frequency5_lineedit->text().toFloat() * 10000);
    map.insert("fre6",ui->frequency6_lineedit->text().toFloat() * 10000);
    map.insert("fre7",ui->frequency7_lineedit->text().toFloat() * 10000);

    QVariantMap map2;
    map2.insert("fre0",map.value("fre0").toString()+"00");
    map2.insert("fre1",map.value("fre1").toString()+"00");
    map2.insert("fre2",map.value("fre2").toString()+"00");
    map2.insert("fre3",map.value("fre3").toString()+"00");
    map2.insert("fre4",map.value("fre4").toString()+"00");
    map2.insert("fre5",map.value("fre5").toString()+"00");
    map2.insert("fre6",map.value("fre6").toString()+"00");
    map2.insert("fre7",map.value("fre7").toString()+"00");

    QString channelMask ;
    for(int q=cb.size()-1; q>=0; q--){
        QCheckBox *c = cb.at(q);
        channelMask += c->isChecked()?"1":"0";
    }
    bool ok=0;

    map2.insert("channemMask","00"+QString::number(channelMask.toInt(&ok,2),16));
    map2.insert("frequenceName",ui->supportFre_cbx->currentText().trimmed());
    map2.insert("frequenceIndex",ui->supportFre_cbx->currentIndex());

    #ifdef OEM_LHR_MILESIGHT
    foreach(QComboBox *b , maxcbxList){
        if(b->isEnabled()){
            map2.insert("datarate", QString::number(b->currentIndex()));
            break;
        }
    }
    #endif
    map2.insert("fixedFre",false);
    QVariantList list;
    m_cacheDataMap.insert("loraChannel",map2);

    QVariantMap map3;

    map3.insert("basicModify",false);
    map3.insert("channelModify",true);
    map3.insert("loraChannel",map2);
    map3.insert("advancedModify",false);
    list.append(map3);

    if(m_bNFC){
        m_bLoraChannelSave = true;
        ui->writeAll_btn->setVisible(true);
    }else{
        emit requestToDevice(UCXX52DealThread::CONFIG_WRITE_LORAWAN,list);

    }
    backupMap.insert("lorawan_channel",map2);
    return true;

}

bool UCXX52Model::on_fixedFreSave_btn_clicked()
{
    qDebug()<< ui->fixedLoraChannelEnableIndex_lineedit->text();
    if(ui->fixedLoraChannelEnableIndex_lineedit->text().isEmpty()){
        showWarning(this,tr("Attention"),tr("Please enable at least one channel."));

        return false;
    }

    QVariantMap map2;
    QSet<QString> setmap;
    QStringList cmlist = ui->fixedLoraChannelEnableIndex_lineedit->text().replace("，",",").replace("-","-").split(",");
    qDebug()<<cmlist.size();
    foreach (QString cm, cmlist) {
        if(cm.toUpper() == "ALL")
            break;
        if(cm.contains("-")){
            if(cm.split("-").size() != 2){
                showWarning(this,tr("Attention"),tr("Please enter the enabled channel index according to the hints."));
                return false;
            }
            int k=cm.split("-").at(0).toInt();
            while(k<=cm.split("-").at(1).toInt()){
                if(k>71 && ui->supportFre2_cbx->currentText().contains("US915")){
                    showWarning(this,tr("Attention"),tr("Only allows values in the range 0-71."));
                    return false;
                }
                if(k>71 && ui->supportFre2_cbx->currentText().contains("AU915")){
                    showWarning(this,tr("Attention"),tr("Only allows values in the range 0-71."));
                    return false;
                }
                if(k>95 && ui->supportFre2_cbx->currentText().contains("CN470")){
                    showWarning(this,tr("Attention"),tr("Only allows values in the range 0-95."));
                    return false;
                }
                setmap.insert(QString::number(k));
                k++;
            }
        }else{
            if(cm.toInt()>71 && ui->supportFre2_cbx->currentText().contains("US915")){
                showWarning(this,tr("Attention"),tr("Only allows values in the range 0-71."));
                return false;
            }
            if(cm.toInt()>71 && ui->supportFre2_cbx->currentText().contains("AU915")){
                showWarning(this,tr("Attention"),tr("Only allows values in the range 0-71."));
                return false;
            }
            if(cm.toInt()>95 && ui->supportFre2_cbx->currentText().contains("CN470")){
                showWarning(this,tr("Attention"),tr("Only allows values in the range 0-95."));
                return false;
            }
            setmap.insert(cm);
        }
    }

    QStringList aa = setmap.values();
    std::sort(aa.begin(),aa.end(),compareByAsc);

    int m1,m2,m3,m4,m5,m6;
    m1 = m2 = m3 = m4 = m5 = m6 = 0;

    foreach (QString s, aa) {
        if(s.toInt()<16){
            m1 = m1 | (1<<(s.toInt()));
        }else if(s.toInt() >= 16 && s.toInt() <= 31){
            m2 = m2 | (1<<(s.toInt()-16));
        }else if(s.toInt() >= 32 && s.toInt() <= 47){
            m3 = m3 | (1<<(s.toInt()-32));
        }else if(s.toInt() >= 48 && s.toInt() <= 63){
            m4 = m4 | (1<<(s.toInt()-48));
        }else if(s.toInt() >= 64 && s.toInt() <= 79){
            m5 = m5 | (1<<(s.toInt()-64));
        }else if(s.toInt() >= 80 && s.toInt() <= 95){
            m6 = m6 | (1<<(s.toInt()-80));
        }
    }
    if(ui->fixedLoraChannelEnableIndex_lineedit->text().toUpper().contains("ALL")){
        m1 = m2 = m3 = m4 = m5 = m6 = 65535;
    }
    qDebug()<<m1<<m2<<m3<<m4<<m5<<m6;
    qDebug()<<QString::number(QString::number(m1).toInt(),16)
                  <<QString::number(QString::number(m2).toInt(),16)
                  <<QString::number(QString::number(m3).toInt(),16)
                  <<QString::number(QString::number(m4).toInt(),16)
                  <<QString::number(QString::number(m5).toInt(),16)
                  <<QString::number(QString::number(m6).toInt(),16);

    qDebug()<<m1<<m2<<m3<<m4<<m5<<m6
                 <<QString("%1").arg(m1,4,16,QLatin1Char('0'));

    map2.insert("cm1",QString("%1").arg(m1,4,16,QLatin1Char('0')));
    map2.insert("cm2",QString("%1").arg(m2,4,16,QLatin1Char('0')));
    map2.insert("cm3",QString("%1").arg(m3,4,16,QLatin1Char('0')));
    map2.insert("cm4",QString("%1").arg(m4,4,16,QLatin1Char('0')));
    map2.insert("cm5",QString("%1").arg(m5,4,16,QLatin1Char('0')));
    map2.insert("cm6",QString("%1").arg(m6,4,16,QLatin1Char('0')));

    map2.insert("frequenceName",ui->supportFre2_cbx->currentText().trimmed());
    map2.insert("frequenceIndex",ui->supportFre2_cbx->currentIndex());

#ifdef OEM_LHR_MILESIGHT
    map2.insert("datarate", QString::number(ui->fixedLoraChannelDatarate_cbx->currentIndex()));
#endif
    map2.insert("fixedFre",true);
    QVariantList list;
    m_cacheDataMap.insert("loraChannel",map2);

    QVariantMap map3;

    map3.insert("basicModify",false);
    map3.insert("channelModify",true);
    map3.insert("loraChannel",map2);
    map3.insert("advancedModify",false);
    list.append(map3);

    if(m_bNFC){
        m_bLoraChannelSave = true;
        ui->writeAll_btn->setVisible(true);
    }else{

        emit requestToDevice(UCXX52DealThread::CONFIG_WRITE_LORAWAN,list);
    }
    backupMap.insert("lorawan_channel",map2);
    return true;
}

void UCXX52Model::on_supportFre2_cbx_currentIndexChanged(const QString &arg1)
{
    on_supportFre_cbx_currentIndexChanged(arg1);
    ui->supportFre_cbx->setCurrentIndex(ui->supportFre_cbx->findText(arg1));
}

void UCXX52Model::on_supportFre_cbx_currentIndexChanged(const QString &arg1)
{
    StructPageLorawan info;

    if(arg1 == "EU868"){
        info.region = QString::number(EU868);
        info.chanMask = "0007";
        info.fre0 = "8681000000";
        info.fre1 = "8683000000";
        info.fre2 = "8685000000";

    }else if(arg1 == "IN865"){
        info.region = QString::number(IN865);
        info.chanMask = "0007";
        info.fre0 = "8650625000";
        info.fre1 = "8654025000";
        info.fre2 = "8659850000";

    }else if(arg1 == "RU864"){
        info.region = QString::number(RU864);
        info.chanMask = "0003";
        info.fre0 = "8689000000";
        info.fre1 = "8691000000";


    }else if(arg1 == "US915"){
        info.region = QString::number(US915);
        info.chanMask = "FFFF";
        info.chanMask16_31 = "FFFF";
        info.chanMask32_47 = "FFFF";
        info.chanMask48_63 = "FFFF";
        info.chanMask64_79 = "00FF";
        info.chanMask80_95 = "0000";

    }else if(arg1 == "AU915"){
        info.region = QString::number(AU915);
        info.chanMask = "FFFF";
        info.chanMask16_31 = "FFFF";
        info.chanMask32_47 = "FFFF";
        info.chanMask48_63 = "FFFF";
        info.chanMask64_79 = "00FF";
        info.chanMask80_95 = "0000";

    }else if(arg1 == "AS923"){
        info.region = QString::number(AS923);
        info.chanMask = "0003";
        info.fre0 = "9232000000";
        info.fre1 = "9234000000";

    }else if(arg1 == "KR920"){
        info.region = QString::number(KR920);
        info.chanMask = "0007";
        info.fre0 = "9221000000";
        info.fre1 = "9223000000";
        info.fre2 = "9225000000";

    }else if(arg1 == "EU433"){
        info.region = QString::number(EU433);
        info.chanMask = "0007";
        info.fre0 = "4331750000";
        info.fre1 = "4333750000";
        info.fre2 = "4335750000";

    }else if(arg1 == "CN470"){
        info.region = QString::number(CN470);
        info.chanMask = "FFFF";
        info.chanMask16_31 = "FFFF";
        info.chanMask32_47 = "FFFF";
        info.chanMask48_63 = "FFFF";
        info.chanMask64_79 = "FFFF";
        info.chanMask80_95 = "FFFF";

    }
    info.frequencyUpdateFlag = "ZZZZZZ";

    setLoraChannelData(info);
    ui->supportFre2_cbx->setCurrentIndex(ui->supportFre2_cbx->findText(arg1));
}

void UCXX52Model::onCheckChannelAllClicked()
{
    QList<QCheckBox*> cb;
    cb<<ui->channel0_cb<<ui->channel1_cb<<ui->channel2_cb<<ui->channel3_cb<<ui->channel4_cb<<ui->channel5_cb<<ui->channel6_cb<<ui->channel7_cb;

    QList<QLineEdit*> le;
    le<<ui->frequency0_lineedit<<ui->frequency1_lineedit<<ui->frequency2_lineedit<<ui->frequency3_lineedit<<ui->frequency4_lineedit<<ui->frequency5_lineedit<<ui->frequency6_lineedit<<ui->frequency7_lineedit;

    #ifdef OEM_LHR_MILESIGHT
    int index =0;
    foreach (QCheckBox *c, cb) {
        if(c->objectName() == sender()->objectName() && c->isChecked()){
            le.at(index)->setEnabled(true);
            maxcbxList.at(index)->setEnabled(true);
        }else{
            c->setChecked(false);
            le.at(index)->setEnabled(false);
            maxcbxList.at(index)->setEnabled(false);
        }
        index++;
    }
    #else
    int q=0;
    foreach (QCheckBox *c, cb) {
        if(c->isChecked()){
            q++;
        }
    }
    if(q != CHANNEL_LORA_NUM){
        ui->channelAll_cb->setChecked(false);
    }else{
        ui->channelAll_cb->setChecked(true);
    }

    int index=0;
    QCheckBox *cc =dynamic_cast<QCheckBox *>(sender());
    for(int i=0; i<cb.size(); i++){
        QCheckBox *c = cb.at(i);
        if(sender()->objectName() == c->objectName()){
            index = i;
        }
    }

    le.at(index)->setEnabled(cc->isChecked());
    #endif
}

void UCXX52Model::on_channelAll_cb_clicked(bool checked)
{
    QList<QCheckBox*> cb;
    cb<<ui->channel0_cb<<ui->channel1_cb<<ui->channel2_cb<<ui->channel3_cb<<ui->channel4_cb<<ui->channel5_cb<<ui->channel6_cb<<ui->channel7_cb;

    QList<QLineEdit*> le;
    le<<ui->frequency0_lineedit<<ui->frequency1_lineedit<<ui->frequency2_lineedit<<ui->frequency3_lineedit<<ui->frequency4_lineedit<<ui->frequency5_lineedit<<ui->frequency6_lineedit<<ui->frequency7_lineedit;

    for(int i=0; i<cb.size(); i++){
        if(!cb.at(i)->isEnabled())
            continue;
        cb.at(i)->setChecked(checked);
        le.at(i)->setEnabled(checked);
    }
}
