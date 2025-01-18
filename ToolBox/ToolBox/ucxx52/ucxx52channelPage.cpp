#include "ucxx52model.h"
#include "ui_ucxx52model.h"
#include <QGraphicsOpacityEffect>
#include <QSequentialAnimationGroup>

/**
 * 初始化modbuschannel界面
 * @brief UCXX52Model::modbusChannelInit
 */
void UCXX52Model::modbusChannelInit()
{
    qDebug()<<modbusChannelFrameList.size()<<m_channelMudbusNum;
    for(int i=0; i<modbusChannelFrameList.size(); i++){
        disconnect(modbusChannelTypeList.at(i),SIGNAL(currentIndexChanged(int)),this,SLOT(onModbusChannelTypeCbxChange()));
        disconnect(modbusChannelAddList.at(i),SIGNAL(clicked(bool)),this,SLOT(onModbusChannelAddBtnClicked()));
        disconnect(modbusChannelDelList.at(i),SIGNAL(clicked(bool)),this,SLOT(onModBusChannelDelBtnClicked()));
        disconnect(modbusChannelFetchList.at(i),SIGNAL(clicked(bool)),this,SLOT(onModbusChannelFetchClicked()));
        disconnect(modbusChannelIdList.at(i),SIGNAL(currentIndexChanged(int)),this,SLOT(modbusChannelGetData()));
        disconnect(modbusChannelNameList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
        disconnect(modbusChannelSlaveidList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
        disconnect(modbusChannelAddrList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
        disconnect(modbusChannelQuantityList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
        disconnect(modbusChannelTypeList.at(i),SIGNAL(currentIndexChanged(int)),this,SLOT(modbusChannelGetData()));
        disconnect(modbusChannelSignList.at(i),SIGNAL(clicked(bool)),this,SLOT(modbusChannelGetData()));
        disconnect(modbusChannelDecimalList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
    }

    m_modbusChannelDelRow = -1;
    modbusChannelIdList.clear();
    modbusChannelIdList<<ui->modbusChannelId_cbx<<ui->modbusChannelId2_cbx<<ui->modbusChannelId3_cbx<<ui->modbusChannelId4_cbx
                         <<ui->modbusChannelId5_cbx<<ui->modbusChannelId6_cbx<<ui->modbusChannelId7_cbx<<ui->modbusChannelId8_cbx;

    modbusChannelNameList.clear();
    modbusChannelNameList<<ui->modbusChannelName_lineedit<<ui->modbusChannelName2_lineedit<<ui->modbusChannelName3_lineedit<<ui->modbusChannelName4_lineedit
                           <<ui->modbusChannelName5_lineedit<<ui->modbusChannelName6_lineedit<<ui->modbusChannelName7_lineedit<<ui->modbusChannelName8_lineedit;

    modbusChannelSlaveidList.clear();
    modbusChannelSlaveidList<<ui->modbusChannelSlaveID_lineedit<<ui->modbusChannelSlaveID2_lineedit<<ui->modbusChannelSlaveID3_lineedit<<ui->modbusChannelSlaveID4_lineedit
                              <<ui->modbusChannelSlaveID5_lineedit<<ui->modbusChannelSlaveID6_lineedit<<ui->modbusChannelSlaveID7_lineedit<<ui->modbusChannelSlaveID8_lineedit;

    modbusChannelAddrList.clear();
    modbusChannelAddrList<<ui->modbusChannelAddr_lineedt<<ui->modbusChannelAddr2_lineedt<<ui->modbusChannelAddr3_lineedt<<ui->modbusChannelAddr4_lineedt
                           <<ui->modbusChannelAddr5_lineedt<<ui->modbusChannelAddr6_lineedt<<ui->modbusChannelAddr7_lineedt<<ui->modbusChannelAddr8_lineedt;

    modbusChannelQuantityList.clear();
    modbusChannelQuantityList<<ui->modbusChannelNum_lineedit<<ui->modbusChannelNum2_lineedit<<ui->modbusChannelNum3_lineedit<<ui->modbusChannelNum4_lineedit
                            <<ui->modbusChannelNum5_lineedit<<ui->modbusChannelNum6_lineedit<<ui->modbusChannelNum7_lineedit<<ui->modbusChannelNum8_lineedit;

    modbusChannelTypeList.clear();
    modbusChannelTypeList<<ui->modbusChannelType_cbx<<ui->modbusChannelType2_cbx<<ui->modbusChannelType3_cbx<<ui->modbusChannelType4_cbx
                           <<ui->modbusChannelType5_cbx<<ui->modbusChannelType6_cbx<<ui->modbusChannelType7_cbx<<ui->modbusChannelType8_cbx;

    modbusChannelSignList.clear();
    modbusChannelSignList<<ui->modbusChannelSign_cb<<ui->modbusChannelSign2_cb<<ui->modbusChannelSign3_cb<<ui->modbusChannelSign4_cb
                           <<ui->modbusChannelSign5_cb<<ui->modbusChannelSign6_cb<<ui->modbusChannelSign7_cb<<ui->modbusChannelSign8_cb;

    modbusChannelDecimalList.clear();
    modbusChannelDecimalList<<ui->modbusChannelDp_lineedit<<ui->modbusChannelDp2_lineedit<<ui->modbusChannelDp3_lineedit<<ui->modbusChannelDp4_lineedit
                              <<ui->modbusChannelDp5_lineedit<<ui->modbusChannelDp6_lineedit<<ui->modbusChannelDp7_lineedit<<ui->modbusChannelDp8_lineedit;

    modbusChannelCurValList.clear();
    modbusChannelCurValList<<ui->modbusChannelCurVal_lineedit<<ui->modbusChannelCurVal2_lineedit<<ui->modbusChannelCurVal3_lineedit<<ui->modbusChannelCurVal4_lineedit
                          <<ui->modbusChannelCurVal5_lineedit<<ui->modbusChannelCurVal6_lineedit<<ui->modbusChannelCurVal7_lineedit<<ui->modbusChannelCurVal8_lineedit;

    modbusChannelReList.clear();
    modbusChannelReList<<ui->modbusChannelFetchFlag1_btn<<ui->modbusChannelFetchFlag2_btn<<ui->modbusChannelFetchFlag3_btn<<ui->modbusChannelFetchFlag4_btn
                     <<ui->modbusChannelFetchFlag5_btn<<ui->modbusChannelFetchFlag6_btn<<ui->modbusChannelFetchFlag7_btn<<ui->modbusChannelFetchFlag8_btn;

    modbusChannelFetchList.clear();
    modbusChannelFetchList<<ui->modbusChannelFetch1_btn<<ui->modbusChannelFetch2_btn<<ui->modbusChannelFetch3_btn<<ui->modbusChannelFetch4_btn
                        <<ui->modbusChannelFetch5_btn<<ui->modbusChannelFetch6_btn<<ui->modbusChannelFetch7_btn<<ui->modbusChannelFetch8_btn;

    modbusChannelAddList.clear();
    modbusChannelAddList<<ui->modbusChannelAdd1_btn<<ui->modbusChannelAdd2_btn<<ui->modbusChannelAdd3_btn<<ui->modbusChannelAdd4_btn
                          <<ui->modbusChannelAdd5_btn<<ui->modbusChannelAdd6_btn<<ui->modbusChannelAdd7_btn<<ui->modbusChannelAdd8_btn;

    modbusChannelDelList.clear();
    modbusChannelDelList<<ui->modbusChannelDel1_btn<<ui->modbusChannelDel2_btn<<ui->modbusChannelDel3_btn<<ui->modbusChannelDel4_btn
                          <<ui->modbusChannelDel5_btn<<ui->modbusChannelDel6_btn<<ui->modbusChannelDel7_btn<<ui->modbusChannelDel8_btn;

    modbusChannelFrameList.clear();
    modbusChannelFrameList<<ui->modbusChannel1_frame<<ui->modbusChannel2_frame<<ui->modbusChannel3_frame<<ui->modbusChannel4_frame
                            <<ui->modbusChannel5_frame<<ui->modbusChannel6_frame<<ui->modbusChannel7_frame<<ui->modbusChannel8_frame;

    if(m_channelMudbusNum == 16){
        modbusChannelIdList<<ui->modbusChannelId9_cbx<<ui->modbusChannelId10_cbx<<ui->modbusChannelId11_cbx<<ui->modbusChannelId12_cbx
                             <<ui->modbusChannelId13_cbx<<ui->modbusChannelId14_cbx<<ui->modbusChannelId15_cbx<<ui->modbusChannelId16_cbx;

        modbusChannelNameList<<ui->modbusChannelName9_lineedit<<ui->modbusChannelName10_lineedit<<ui->modbusChannelName11_lineedit<<ui->modbusChannelName12_lineedit
                               <<ui->modbusChannelName13_lineedit<<ui->modbusChannelName14_lineedit<<ui->modbusChannelName15_lineedit<<ui->modbusChannelName16_lineedit;

        modbusChannelSlaveidList<<ui->modbusChannelSlaveID9_lineedit<<ui->modbusChannelSlaveID10_lineedit<<ui->modbusChannelSlaveID11_lineedit<<ui->modbusChannelSlaveID12_lineedit
                               <<ui->modbusChannelSlaveID13_lineedit<<ui->modbusChannelSlaveID14_lineedit<<ui->modbusChannelSlaveID15_lineedit<<ui->modbusChannelSlaveID16_lineedit;

        modbusChannelAddrList<<ui->modbusChannelAddr9_lineedt<<ui->modbusChannelAddr10_lineedt<<ui->modbusChannelAddr11_lineedt<<ui->modbusChannelAddr12_lineedt
                               <<ui->modbusChannelAddr13_lineedt<<ui->modbusChannelAddr14_lineedt<<ui->modbusChannelAddr15_lineedt<<ui->modbusChannelAddr16_lineedt;

        modbusChannelQuantityList<<ui->modbusChannelNum9_lineedit<<ui->modbusChannelNum10_lineedit<<ui->modbusChannelNum11_lineedit<<ui->modbusChannelNum12_lineedit
                                <<ui->modbusChannelNum13_lineedit<<ui->modbusChannelNum14_lineedit<<ui->modbusChannelNum15_lineedit<<ui->modbusChannelNum16_lineedit;

        modbusChannelTypeList<<ui->modbusChannelType9_cbx<<ui->modbusChannelType10_cbx<<ui->modbusChannelType11_cbx<<ui->modbusChannelType12_cbx
                               <<ui->modbusChannelType13_cbx<<ui->modbusChannelType14_cbx<<ui->modbusChannelType15_cbx<<ui->modbusChannelType16_cbx;

        modbusChannelSignList<<ui->modbusChannelSign9_cb<<ui->modbusChannelSign10_cb<<ui->modbusChannelSign11_cb<<ui->modbusChannelSign12_cb
                               <<ui->modbusChannelSign13_cb<<ui->modbusChannelSign14_cb<<ui->modbusChannelSign15_cb<<ui->modbusChannelSign16_cb;

        modbusChannelDecimalList<<ui->modbusChannelDp9_lineedit<<ui->modbusChannelDp10_lineedit<<ui->modbusChannelDp11_lineedit<<ui->modbusChannelDp12_lineedit
                                  <<ui->modbusChannelDp13_lineedit<<ui->modbusChannelDp14_lineedit<<ui->modbusChannelDp15_lineedit<<ui->modbusChannelDp16_lineedit;

        modbusChannelCurValList<<ui->modbusChannelCurVal9_lineedit<<ui->modbusChannelCurVal10_lineedit<<ui->modbusChannelCurVal11_lineedit<<ui->modbusChannelCurVal12_lineedit
                              <<ui->modbusChannelCurVal13_lineedit<<ui->modbusChannelCurVal14_lineedit<<ui->modbusChannelCurVal15_lineedit<<ui->modbusChannelCurVal16_lineedit;

        modbusChannelReList<<ui->modbusChannelFetchFlag9_btn<<ui->modbusChannelFetchFlag10_btn<<ui->modbusChannelFetchFlag11_btn<<ui->modbusChannelFetchFlag12_btn
                              <<ui->modbusChannelFetchFlag13_btn<<ui->modbusChannelFetchFlag14_btn<<ui->modbusChannelFetchFlag15_btn<<ui->modbusChannelFetchFlag16_btn;

        modbusChannelFetchList<<ui->modbusChannelFetch9_btn<<ui->modbusChannelFetch10_btn<<ui->modbusChannelFetch11_btn<<ui->modbusChannelFetch12_btn
                              <<ui->modbusChannelFetch13_btn<<ui->modbusChannelFetch14_btn<<ui->modbusChannelFetch15_btn<<ui->modbusChannelFetch16_btn;

        modbusChannelAddList<<ui->modbusChannelAdd9_btn<<ui->modbusChannelAdd10_btn<<ui->modbusChannelAdd11_btn<<ui->modbusChannelAdd12_btn
                              <<ui->modbusChannelAdd13_btn<<ui->modbusChannelAdd14_btn<<ui->modbusChannelAdd15_btn<<ui->modbusChannelAdd16_btn;

        modbusChannelDelList<<ui->modbusChannelDel9_btn<<ui->modbusChannelDel10_btn<<ui->modbusChannelDel11_btn<<ui->modbusChannelDel12_btn
                              <<ui->modbusChannelDel13_btn<<ui->modbusChannelDel14_btn<<ui->modbusChannelDel15_btn<<ui->modbusChannelDel16_btn;

        modbusChannelFrameList<<ui->modbusChannel9_frame<<ui->modbusChannel10_frame<<ui->modbusChannel11_frame<<ui->modbusChannel12_frame
                                <<ui->modbusChannel13_frame<<ui->modbusChannel14_frame<<ui->modbusChannel15_frame<<ui->modbusChannel16_frame;
    }else{
        ui->modbusChannel9_frame->setVisible(false);
        ui->modbusChannel10_frame->setVisible(false);
        ui->modbusChannel11_frame->setVisible(false);
        ui->modbusChannel12_frame->setVisible(false);
        ui->modbusChannel13_frame->setVisible(false);
        ui->modbusChannel14_frame->setVisible(false);
        ui->modbusChannel15_frame->setVisible(false);
        ui->modbusChannel16_frame->setVisible(false);
    }

    for(int i=1; i<modbusChannelFrameList.size(); i++){
        modbusChannelFrameList.at(i)->setVisible(false);
        modbusChannelFrameList.at(i)->setEnabled(false);
    }

    modbusChannelAnimationList.clear();
    for(int i=0; i<modbusChannelFrameList.size(); i++){
        modbusChannelTypeList.at(i)->setItemData(0,QunpUCXX52::MB_REG_COIL);
        modbusChannelTypeList.at(i)->setItemData(1,QunpUCXX52::MB_REG_DIS);
        modbusChannelTypeList.at(i)->setItemData(2,QunpUCXX52::MB_REG_INPUT);
        modbusChannelTypeList.at(i)->setItemData(3,QunpUCXX52::MB_REG_INPUT_INT32);
        modbusChannelTypeList.at(i)->setItemData(4,QunpUCXX52::MB_REG_INPUT_FLOAT);
        modbusChannelTypeList.at(i)->setItemData(5,QunpUCXX52::MB_REG_HOLD_INT16);
        modbusChannelTypeList.at(i)->setItemData(6,QunpUCXX52::MB_REG_HOLD_INT32);
        modbusChannelTypeList.at(i)->setItemData(7,QunpUCXX52::MB_REG_HOLD_FLOAT);
        modbusChannelTypeList.at(i)->setItemData(8,QunpUCXX52::MB_REG_INPUT_INT32_AB);
        modbusChannelTypeList.at(i)->setItemData(9,QunpUCXX52::MB_REG_INPUT_INT32_CD);
        modbusChannelTypeList.at(i)->setItemData(10,QunpUCXX52::MB_REG_HOLD_INT32_AB);
        modbusChannelTypeList.at(i)->setItemData(11,QunpUCXX52::MB_REG_HOLD_INT32_CD);
        modbusChannelTypeList.at(i)->view()->setFixedWidth(280);
#if 01
        QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
        //opacity
        QGraphicsOpacityEffect *pButtonOpacity = new QGraphicsOpacityEffect(this);
        pButtonOpacity->setOpacity(0);
        modbusChannelReList.at(i)->setGraphicsEffect(pButtonOpacity);

        //显示
        QPropertyAnimation *pOpacityAnimation2 = new QPropertyAnimation(pButtonOpacity, "opacity");
        pOpacityAnimation2->setDuration(100);
        pOpacityAnimation2->setStartValue(0);
        pOpacityAnimation2->setEndValue(1);
        pOpacityAnimation2->setDirection(QAbstractAnimation::Backward);

        //消失
        QPropertyAnimation *pOpacityAnimation1 = new QPropertyAnimation(pButtonOpacity, "opacity");
        pOpacityAnimation1->setDuration(100);
        pOpacityAnimation1->setStartValue(1);
        pOpacityAnimation1->setEndValue(0);

        QSequentialAnimationGroup *pOpacityGroup = new QSequentialAnimationGroup(this);
        pOpacityGroup->addAnimation(pOpacityAnimation2);
        pOpacityGroup->addPause(3000);
        pOpacityGroup->addAnimation(pOpacityAnimation1);

        group->addAnimation(pOpacityGroup);
        group->setLoopCount(1);
        modbusChannelAnimationList.append(group);
#endif
        connect(modbusChannelTypeList.at(i),SIGNAL(currentIndexChanged(int)),this,SLOT(onModbusChannelTypeCbxChange()));
        connect(modbusChannelAddList.at(i),SIGNAL(clicked(bool)),this,SLOT(onModbusChannelAddBtnClicked()));
        connect(modbusChannelDelList.at(i),SIGNAL(clicked(bool)),this,SLOT(onModBusChannelDelBtnClicked()));
        connect(modbusChannelFetchList.at(i),SIGNAL(clicked(bool)),this,SLOT(onModbusChannelFetchClicked()));
        connect(modbusChannelIdList.at(i),SIGNAL(currentIndexChanged(int)),this,SLOT(modbusChannelGetData()));
        connect(modbusChannelNameList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
        connect(modbusChannelSlaveidList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
        connect(modbusChannelAddrList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
        connect(modbusChannelQuantityList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
        connect(modbusChannelTypeList.at(i),SIGNAL(currentIndexChanged(int)),this,SLOT(modbusChannelGetData()));
        connect(modbusChannelSignList.at(i),SIGNAL(clicked(bool)),this,SLOT(modbusChannelGetData()));
        connect(modbusChannelDecimalList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));

        modbusChannelNameList.at(i)->setValidator(new QRegExpValidator(QRegExp("^[0-9a-zA-Z\u4e00-\u9fa5-_, ]+$")));
        modbusChannelSlaveidList.at(i)->setValidator(new QRegExpValidator(QRegExp("^[0-9+]+$")));
        modbusChannelAddrList.at(i)->setValidator(new QRegExpValidator(QRegExp("^[0-9+]+$")));
        modbusChannelQuantityList.at(i)->setValidator(new QRegExpValidator(QRegExp("^[0-9+]+$")));
        modbusChannelDecimalList.at(i)->setValidator(new QRegExpValidator(QRegExp("^[0-9+]+$")));
    }

}

void UCXX52Model::onRecvChannelStatus(UCXX52DealThread::StructPageChannel info)
{
    if(info.readSpecial == 9999){
        switch (info.readSpecialType) {
        case UCXX52DealThread::RMS_Serial:
            for(int i=1; i<=modbusChannelFrameList.size(); i++){
                if(i == info.serialIndex){
                    if(info.fetchPkgLen!=0){
                        modbusChannelTypeList.at(i-1)->setCurrentIndex(modbusChannelTypeList.at(i-1)->findData(info.serialType.toInt()));
                        modbusChannelSignList.at(i-1)->setChecked(info.serialSign.toInt());
                        modbusChannelCurValList.at(i-1)->setText(info.serialValue);
                        modbusChannelQuantityList.at(i-1)->setText(info.serialQuantity);
                        modbusChannelDecimalList.at(i-1)->setText(info.serialDp);
                    }else{
                        modbusChannelCurValList.at(i-1)->setText("");
                    }
                    modbusChannelReList.at(i-1)->setEnabled(info.fetchPkgLen==0?false:true);
                    modbusChannelAnimationList.at(i-1)->start();
                }
            }
            break;
        default:
            break;
        }
        emit waitingVisible(false);
        return;
    }

    ui->executionInterval_lineedit->setText(QString::number(info.executionInterval));
    ui->maxRespTime_lineedit->setText(QString::number(info.maxRespTime));
    ui->maxRetryTimes_lineedit->setText(QString::number(info.maxRetrytime));
    m_modbusChannelData = info.dataList;

    if(m_modbusChannelData.size() == 0){
        modbusChannelAddList.at(0)->setVisible(true);
        modbusChannelDelList.at(0)->setVisible(true);
        ui->modbusbusChannelData1_widget->setVisible(false);
        ui->modbusbusChannelData1_widget->setEnabled(false);
        QStringList idlist;

        for(int m=1; m<=m_channelMudbusNum; m++){
            idlist<<QString::number(m);
        }

        for(int i=0; i<modbusChannelFrameList.size(); i++){
            modbusChannelIdList.at(i)->clear();
            modbusChannelIdList.at(i)->addItems(idlist);
            modbusChannelIdList.at(i)->setCurrentIndex(-1);
            modbusChannelNameList.at(i)->clear();
            modbusChannelSlaveidList.at(i)->clear();
            modbusChannelAddrList.at(i)->clear();
            modbusChannelTypeList.at(i)->setCurrentIndex(modbusChannelTypeList.at(i)->findData(QunpUCXX52::MB_REG_INPUT));
            modbusChannelSignList.at(i)->setChecked(false);
            modbusChannelDecimalList.at(i)->clear();
        }
        emit waitingVisible(false);
        return;
    }

    if(m_modbusChannelData.size() == 8 ){
        for(int i=0; i<m_modbusChannelData.size(); i++){
            modbusChannelFrameList.at(i)->setVisible(true);
            modbusChannelFrameList.at(i)->setEnabled(true);
        }
    }else{
        for(int i=0; i<m_modbusChannelData.size(); i++){
            modbusChannelFrameList.at(i)->setVisible(true);
            modbusChannelFrameList.at(i)->setEnabled(true);
        }
    }

    modbusChannelAddDelChange();
    modbusChannelDataChange();
    ui->modbusChannelStatus_cbx->clear();
    QString modbusChannelNameStatus;
    for(int i=0; i<modbusChannelSlaveidList.size();i++){
        if(!modbusChannelFrameList.at(i)->isEnabled())
            continue;
        qDebug()<<QString("%1(%2)").arg(modbusChannelNameList.at(i)->text()).arg(modbusChannelIdList.at(i)->currentText());
        ui->modbusChannelStatus_cbx->addItem(QString("%1(%2)").arg(modbusChannelNameList.at(i)->text()).arg(modbusChannelIdList.at(i)->currentText()),
                                             modbusChannelIdList.at(i)->currentText());
        modbusChannelNameStatus = modbusChannelNameStatus +modbusChannelNameList.at(i)->text() +",";
    }

    if(!modbusChannelNameStatus.isEmpty()){
        if(modbusChannelNameStatus.mid(modbusChannelNameStatus.length()-1 ,1) == ","){
            modbusChannelNameStatus.remove(modbusChannelNameStatus.length()-1 ,1);
        }
        ui->channelNameStatus_label_2->setText(modbusChannelNameStatus);
    }

    emit waitingVisible(false);

}

/**
 * Channel 页面Type变化
 * @brief UCXX52Model::onModbusChannelTypeCbxChange
 */
void UCXX52Model::onModbusChannelTypeCbxChange()
{
    for(int i=0; i<modbusChannelTypeList.size(); i++){
        if(sender()->objectName() == modbusChannelTypeList.at(i)->objectName()){
            if(modbusChannelTypeList.at(i)->currentData()==QunpUCXX52::MB_REG_COIL|| modbusChannelTypeList.at(i)->currentData()==QunpUCXX52::MB_REG_DIS){
                modbusChannelSignList.at(i)->setEnabled(false);
                modbusChannelDecimalList.at(i)->setEnabled(false);
                modbusChannelSignList.at(i)->setChecked(false);
                modbusChannelDecimalList.at(i)->clear();
            }else if(modbusChannelTypeList.at(i)->currentData()==QunpUCXX52::MB_REG_HOLD_FLOAT || modbusChannelTypeList.at(i)->currentData()==QunpUCXX52::MB_REG_INPUT_FLOAT){
                modbusChannelSignList.at(i)->setEnabled(false);
                modbusChannelSignList.at(i)->setChecked(true);
            }else{
                modbusChannelSignList.at(i)->setEnabled(true);
                modbusChannelDecimalList.at(i)->setEnabled(true);
            }
        }
    }
}

/**
 * Channel 添加通道 总是添加最后一个 每次添加都要重新填表
 * @brief UCXX52Model::onModbusChannelAddBtnClicked
 */
void UCXX52Model::onModbusChannelAddBtnClicked()
{
    for(int i=0; i<modbusChannelFrameList.size(); i++){
        if(!ui->modbusbusChannelData1_widget->isVisible() && i==0){
            ui->modbusbusChannelData1_widget->setVisible(true);
            ui->modbusbusChannelData1_widget->setEnabled(true);
            break;
        }else{
            if(!modbusChannelFrameList.at(i)->isVisible()){
                modbusChannelFrameList.at(i)->setVisible(true);
                modbusChannelFrameList.at(i)->setEnabled(true);
                break;
            }
        }

    }
    modbusChannelAddDelChange();
    modbusChannelGetData();
    modbusChannelDataChange();

}

/**
 * 删除通道 总是删除最后一个 每次删除都要重新填表
 * @brief UCXX52Model::onModBusChannelDelBtnClicked
 */
void UCXX52Model::onModBusChannelDelBtnClicked()
{
    QSettings settings(m_iniPath, QSettings::IniFormat);
    settings.beginGroup("CloseTipAgain");
    if(settings.value("again").toBool()){
        if(showQuestion(this,tr("Attention"),MyMessageBox::TYPE_DELETE_CMD,tr("Do you want to delete this channel?")) == QMessageBox::Ok){
            goto DEL_CHANNEL;
        }else{
            settings.endGroup();
            return;
        }
    }else{
        goto DEL_CHANNEL;
    }

DEL_CHANNEL:
    settings.endGroup();
    for(int i=modbusChannelFrameList.size()-1; i>=0; i--){
        if(i==0){
            ui->modbusbusChannelData1_widget->setVisible(false);
            ui->modbusbusChannelData1_widget->setEnabled(false);
//                modbusChannelFrameList.at(i)->setEnabled(false);
            break;
        }else if(modbusChannelFrameList.at(i)->isVisible()){
            modbusChannelFrameList.at(i)->setVisible(false);
            modbusChannelFrameList.at(i)->setEnabled(false);
            break;
        }
    }
    for(int i=0; i<modbusChannelDelList.size(); i++){
        if(sender()->objectName() == modbusChannelDelList.at(i)->objectName()){
            for(int j=0; j<m_modbusChannelData.size(); j++){
                if(m_modbusChannelData.at(j).toMap().value("frameid").toString() == modbusChannelDelList.at(i)->objectName()){
                    m_modbusChannelDelRow = j;
                    m_modbusChannelData.removeAt(j);
                }
            }
        }
    }
    modbusChannelAddDelChange();
    modbusChannelDataChange();
}

/**
 * 每行获取当前值点击  Serial
 * @brief UCXX52Model::onN1ChannelFetchClicked
 */
void UCXX52Model::onModbusChannelFetchClicked()
{
    for(int i=0; i<modbusChannelFetchList.size(); i++){
        if(sender()->objectName() == modbusChannelFetchList.at(i)->objectName()){
            QVariantMap map;
            map.insert("readType",UCXX52DealThread::RMS_Serial);
            map.insert("index",i+1);
            map.insert("name",modbusChannelIdList.at(i)->currentText());
            QVariantList list;
            list.append(map);
            emit requestToDevice(UCXX52DealThread::CONFIG_WRITE_CHANNEL_SPECIAL,list);
            break;
        }
    }
}


/**
 * 处理Channel数据  把modbusChannelData数据写进表格
 * @brief UCXX52Model::modbusChannelDataChange
 */
void UCXX52Model::modbusChannelDataChange()
{
    for(int i=0; i<modbusChannelFrameList.size(); i++){
        disconnect(modbusChannelIdList.at(i),SIGNAL(currentIndexChanged(int)),this,SLOT(modbusChannelGetData()));
        disconnect(modbusChannelNameList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
        disconnect(modbusChannelSlaveidList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
        disconnect(modbusChannelAddrList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
        disconnect(modbusChannelQuantityList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
        disconnect(modbusChannelTypeList.at(i),SIGNAL(currentIndexChanged(int)),this,SLOT(modbusChannelGetData()));
        disconnect(modbusChannelSignList.at(i),SIGNAL(clicked(bool)),this,SLOT(modbusChannelGetData()));
        disconnect(modbusChannelDecimalList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
    }

    int dataIndex=0;
    for(int i=0; i<modbusChannelIdList.size(); i++){
        QStringList idlist;
        for(int m=1; m<=m_channelMudbusNum; m++){
            idlist<<QString::number(m);
        }
        modbusChannelIdList.at(i)->clear();
        modbusChannelIdList.at(i)->addItems(idlist);
        modbusChannelIdList.at(i)->setCurrentIndex(-1);
    }

    for(int i=0; i<modbusChannelFrameList.size(); i++){

        if(!modbusChannelFrameList.at(i)->isEnabled() || !ui->modbusbusChannelData1_widget->isEnabled()){
            modbusChannelIdList.at(i)->clear();
            modbusChannelNameList.at(i)->clear();
            modbusChannelSlaveidList.at(i)->clear();
            modbusChannelAddrList.at(i)->clear();
#if CHANNEL_QUANTITY_ENABLE
            modbusChannelQuantityList.at(i)->clear();
#endif
            modbusChannelTypeList.at(i)->setCurrentIndex(modbusChannelTypeList.at(i)->findData(QunpUCXX52::MB_REG_INPUT));
            modbusChannelSignList.at(i)->setChecked(false);
            modbusChannelDecimalList.at(i)->clear();
            continue;
        }
//        qDebug()<<"row"<<i<<modbusChannelFrameList.at(i)->isEnabled();
        QVariantMap map = m_modbusChannelData.at(i).toMap();

//        qDebug()<<m_modbusChannelData.size()<<m_modbusChannelDelRow
//                 <<"name"+QString::number(dataIndex)
//                <<m_modbusChannelData.at(0).toMap().value("name0").toString()
//                <<map.value("slaveid"+QString::number(dataIndex)).toString()
//               <<QString::number(map.value("num").toInt()-1);

        if(m_modbusChannelDelRow == dataIndex)
            dataIndex++;
//        qDebug()<<dataIndex<<modbusChannelIdList.size()<<map.value("name"+QString::number(dataIndex)).toString();
        for(int m=0; m<modbusChannelIdList.size(); m++){
            if(m==i)
                continue;
            modbusChannelIdList.at(m)->removeItem(modbusChannelIdList.at(m)->findText(QString::number(map.value("num").toInt())));
        }
        modbusChannelIdList.at(i)->setCurrentIndex(modbusChannelIdList.at(i)->findText(QString::number(map.value("num").toInt())));
//        modbusChannelIdList.at(i)->setEnabled(false);

        modbusChannelNameList.at(i)->setText(map.value("name"+QString::number(dataIndex)).toString());
        modbusChannelSlaveidList.at(i)->setText(map.value("slaveid"+QString::number(dataIndex)).toString());
        modbusChannelAddrList.at(i)->setText(map.value("addr"+QString::number(dataIndex)).toString());
        modbusChannelQuantityList.at(i)->setText(map.value("quantity"+QString::number(dataIndex)).toString());
        modbusChannelTypeList.at(i)->setCurrentIndex(modbusChannelTypeList.at(i)->findData(map.value("type"+QString::number(dataIndex)).toInt()));
        modbusChannelSignList.at(i)->setChecked(map.value("sign"+QString::number(dataIndex)).toBool());
        modbusChannelDecimalList.at(i)->setText(map.value("dp"+QString::number(dataIndex)).toString());
        modbusChannelCurValList.at(i)->setText(map.value("value"+QString::number(dataIndex)).toString());

        dataIndex++;
    }
    for(int i=0; i<modbusChannelFrameList.size(); i++){
        connect(modbusChannelIdList.at(i),SIGNAL(currentIndexChanged(int)),this,SLOT(modbusChannelGetData()));
        connect(modbusChannelNameList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
        connect(modbusChannelSlaveidList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
        connect(modbusChannelAddrList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
        connect(modbusChannelQuantityList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
        connect(modbusChannelTypeList.at(i),SIGNAL(currentIndexChanged(int)),this,SLOT(modbusChannelGetData()));
        connect(modbusChannelSignList.at(i),SIGNAL(clicked(bool)),SLOT(modbusChannelGetData()));
        connect(modbusChannelDecimalList.at(i),SIGNAL(textChanged(QString)),this,SLOT(modbusChannelGetData()));
    }

    modbusChannelGetData();
}
/**
 * 读取表格数据到Map m_modbusChannelData
 * @brief UCXX52Model::modbusChannelGetData
 */
void UCXX52Model::modbusChannelGetData()
{
    m_modbusChannelGetDataMutex.lock();
    m_modbusChannelData.clear();
    m_modbusChannelDelRow = -1;

    if(m_proName.contains("1152")){
        for(int i=0; i<modbusChannelIdList.size(); i++){
            if(sender()->objectName() == modbusChannelTypeList.at(i)->objectName()){
                if(modbusChannelTypeList.at(i)->currentData().toInt() >= QunpUCXX52::MB_REG_HOLD_INT32){
                    modbusChannelQuantityList.at(i)->setEnabled(false);
                    modbusChannelQuantityList.at(i)->setText("1");
                }else{
                    modbusChannelQuantityList.at(i)->setEnabled(true);
                }
            }
        }
    }

    QStringList c_indexList;
    for(int i=0; i<modbusChannelIdList.size(); i++){
        QStringList idlist;
        disconnect(modbusChannelIdList.at(i),SIGNAL(currentIndexChanged(int)),this,SLOT(modbusChannelGetData()));
        c_indexList<<modbusChannelIdList.at(i)->currentText();

        for(int m=1; m<=m_channelMudbusNum; m++){
            idlist<<QString::number(m);
        }
        modbusChannelIdList.at(i)->clear();
        modbusChannelIdList.at(i)->addItems(idlist);
        modbusChannelIdList.at(i)->setCurrentIndex(-1);
        connect(modbusChannelIdList.at(i),SIGNAL(currentIndexChanged(int)),this,SLOT(modbusChannelGetData()));
    }

    for(int i=0; i<modbusChannelIdList.size(); i++){
        disconnect(modbusChannelIdList.at(i),SIGNAL(currentIndexChanged(int)),this,SLOT(modbusChannelGetData()));
        for (int j=0; j<c_indexList.size(); j++) {
            if(j==i)
                continue;
            modbusChannelIdList.at(i)->removeItem(modbusChannelIdList.at(i)->findText(c_indexList.at(j)));
        }
        connect(modbusChannelIdList.at(i),SIGNAL(currentIndexChanged(int)),this,SLOT(modbusChannelGetData()));
    }

    for(int i=0; i<modbusChannelFrameList.size(); i++){
        if(!modbusChannelFrameList.at(i)->isEnabled()){
            continue;
        }

        disconnect(modbusChannelIdList.at(i),SIGNAL(currentIndexChanged(int)),this,SLOT(modbusChannelGetData()));
        modbusChannelIdList.at(i)->setCurrentIndex(modbusChannelIdList.at(i)->findText(c_indexList.at(i)));
        connect(modbusChannelIdList.at(i),SIGNAL(currentIndexChanged(int)),this,SLOT(modbusChannelGetData()));

        QVariantMap map;
        map.insert("num",modbusChannelIdList.at(i)->currentText().toInt());
        map.insert("name"+QString::number(i),modbusChannelNameList.at(i)->text());
        map.insert("slaveid"+QString::number(i),modbusChannelSlaveidList.at(i)->text());
        map.insert("addr"+QString::number(i),modbusChannelAddrList.at(i)->text());
        map.insert("quantity"+QString::number(i),modbusChannelQuantityList.at(i)->text());
        map.insert("type"+QString::number(i),modbusChannelTypeList.at(i)->currentData().toInt());
        map.insert("sign"+QString::number(i),modbusChannelSignList.at(i)->isChecked()?"1":"0");
        map.insert("dp"+QString::number(i),modbusChannelDecimalList.at(i)->text());
        map.insert("value"+QString::number(i),modbusChannelCurValList.at(i)->text());
        map.insert("frameid",modbusChannelDelList.at(i)->objectName());
        m_modbusChannelData.append(map);
    }

    m_modbusChannelGetDataMutex.unlock();
}

/**
 * 添加删除按键是否显示
 * @brief UCXX52Model::modbusChannelAddDelChange
 */
void UCXX52Model::modbusChannelAddDelChange()
{
    int visibleIndex=0;
    for(int i=0; i<modbusChannelFrameList.size(); i++){
        if(modbusChannelFrameList.at(i)->isVisible()){
           visibleIndex++;
           modbusChannelAddList.at(i)->setVisible(false);
           modbusChannelDelList.at(i)->setVisible(true);
        }
    }

    if(visibleIndex==0){
        modbusChannelAddList.at(visibleIndex)->setVisible(true);
        modbusChannelDelList.at(visibleIndex)->setVisible(true);
        return;
    }
    if(visibleIndex == m_channelMudbusNum){
        modbusChannelAddList.at(visibleIndex-1)->setVisible(true);
        modbusChannelDelList.at(visibleIndex-1)->setVisible(true);
    }else if(visibleIndex == 1){
        modbusChannelAddList.at(visibleIndex-1)->setVisible(true);
        modbusChannelDelList.at(visibleIndex-1)->setVisible(true);
    }else{
        modbusChannelAddList.at(visibleIndex-1)->setVisible(true);
        modbusChannelDelList.at(visibleIndex-1)->setVisible(true);
    }
    ui->modbusChannel_scrollAreaWidget->setGeometry(ui->modbusChannel_scrollAreaWidget->x(),ui->modbusChannel_scrollAreaWidget->y(),
                                                    ui->modbusChannel_scrollAreaWidget->width(),ui->frame_20->y()+ui->frame_20->height());

}

/**
 * 保存
 * @brief UCXX52Model::on_modbusChannelSave_btn_clicked
 */
void UCXX52Model::on_modbusChannelSave_btn_clicked()
{

    for(int i=0; i<modbusChannelFrameList.size(); i++){
        modbusChannelIdList.at(i)->setStyleSheet(RECOVERY_INPUT3);
        modbusChannelNameList.at(i)->setStyleSheet(RECOVERY_INPUT3);
        modbusChannelSlaveidList.at(i)->setStyleSheet(RECOVERY_INPUT3);
        modbusChannelAddrList.at(i)->setStyleSheet(RECOVERY_INPUT3);
        modbusChannelQuantityList.at(i)->setStyleSheet(RECOVERY_INPUT3);
        modbusChannelDecimalList.at(i)->setStyleSheet(RECOVERY_INPUT3);
    }
    ui->executionInterval_lineedit->setStyleSheet(RECOVERY_INPUT2);
    ui->maxRespTime_lineedit->setStyleSheet(RECOVERY_INPUT2);
    ui->maxRetryTimes_lineedit->setStyleSheet(RECOVERY_INPUT2);

    if(ui->executionInterval_lineedit->text().toInt() < 0 || ui->executionInterval_lineedit->text().toInt() > 600){
        ui->executionInterval_lineedit->setStyleSheet(ERROR_INPUT2);
        showWarning(this,tr("Attention"),tr("Valid Range：0-600."));

        return;
    }

    if(ui->maxRespTime_lineedit->text().toInt() < 10 || ui->maxRespTime_lineedit->text().toInt() > 1000){
        ui->maxRespTime_lineedit->setStyleSheet(ERROR_INPUT2);
        showWarning(this,tr("Attention"),tr("Valid Range：10-1000."));

        return;
    }

    if(ui->maxRetryTimes_lineedit->text().toInt() < 0 || ui->maxRetryTimes_lineedit->text().toInt() > 5){
        ui->maxRetryTimes_lineedit->setStyleSheet(ERROR_INPUT2);
        showWarning(this,tr("Attention"),tr("Valid Range：0-5."));

        return;
    }

    int ok=-1;
    for(int i=0; i<modbusChannelFrameList.size(); i++){
        if(modbusChannelIdList.at(i)->currentText().isEmpty() && modbusChannelIdList.at(i)->isVisible()){
            modbusChannelIdList.at(i)->setStyleSheet(ERROR_INPUT2);
            ok = 6;
        }
        if(modbusChannelNameList.at(i)->text().isEmpty() && modbusChannelNameList.at(i)->isVisible()){
            modbusChannelNameList.at(i)->setStyleSheet(ERROR_INPUT2);
            ok = 1;
        }
        if((modbusChannelSlaveidList.at(i)->text().isEmpty() || modbusChannelSlaveidList.at(i)->text().toInt() > 255 )
                && modbusChannelSlaveidList.at(i)->isVisible()){
            modbusChannelSlaveidList.at(i)->setStyleSheet(ERROR_INPUT2);
            ok = 2;
        }

        if((modbusChannelAddrList.at(i)->text().isEmpty() || modbusChannelAddrList.at(i)->text().toInt() > 65534 )
                && modbusChannelAddrList.at(i)->isVisible()){
            modbusChannelAddrList.at(i)->setStyleSheet(ERROR_INPUT2);
            ok = 3;
        }
//#ifdef ODM_LHR_INDIA
        if((modbusChannelQuantityList.at(i)->text().isEmpty() || modbusChannelQuantityList.at(i)->text().toInt() > 9 || modbusChannelQuantityList.at(i)->text().toInt() < 1)
//#elif 1
//        if((modbusChannelQuantityList.at(i)->text().isEmpty() || modbusChannelQuantityList.at(i)->text().toInt() > 4 || modbusChannelQuantityList.at(i)->text().toInt() < 1)
//#endif
                && modbusChannelQuantityList.at(i)->isVisible()){
            modbusChannelQuantityList.at(i)->setStyleSheet(ERROR_INPUT2);
            ok = 4;
        }
        if((modbusChannelDecimalList.at(i)->text().isEmpty() || modbusChannelDecimalList.at(i)->text().toInt() > 5)
                && modbusChannelDecimalList.at(i)->isVisible() && modbusChannelDecimalList.at(i)->isEnabled()){
            modbusChannelDecimalList.at(i)->setStyleSheet(ERROR_INPUT2);
            ok = 5;
        }
    }
    if(ok == 1){
        showWarning(this,tr("Attention"),tr("Only 0-9, a-z, A-Z, Chinese characters, hyphen (-), uderscore (_) and blanks are allowed."));

        return;
    }else if(ok == 2){
        showWarning(this,tr("Attention"),tr("Valid Range：0-255."));

        return;
    }else if(ok == 3){
        showWarning(this,tr("Attention"),tr("Valid Range：0-65534."));

        return;
    }else if(ok == 4){
//#ifdef ODM_LHR_INDIA
        showWarning(this,tr("Attention"),tr("Valid Range：1-9."));
//#elif 1
//        showWarning(this,tr("Attention"),tr("Valid Range：1-4."));
//#endif

        return;
    }else if(ok == 5){
        showWarning(this,tr("Attention"),tr("Valid Range：0-5."));

        return;
    }else if(ok == 6){
        showWarning(this,tr("Attention"),tr("Valid Range：1-%1.").arg(m_channelMudbusNum));
        return;
    }


    modbusChannelGetData();
    QVariantMap mapData;
    mapData.insert("channelMudbusNum",m_channelMudbusNum);
    mapData.insert("executionInterval",ui->executionInterval_lineedit->text().trimmed());
    mapData.insert("maxRespTime",ui->maxRespTime_lineedit->text().trimmed());
    mapData.insert("maxRetryTime",ui->maxRetryTimes_lineedit->text().trimmed());
    mapData.insert("channelData",m_modbusChannelData);

    ui->modbusChannelStatus_cbx->clear();
    for(int i=0; i<modbusChannelSlaveidList.size();i++){
        if(!modbusChannelSlaveidList.at(i)->isVisible())
            continue;
        ui->modbusChannelStatus_cbx->addItem(QString("%1(%2)").arg(modbusChannelNameList.at(i)->text()).arg(modbusChannelIdList.at(i)->currentText()),
                                             modbusChannelIdList.at(i)->currentText());

    }

    emit waitingVisible(true);
    QVariantList list;
    list.append(mapData);
    emit requestToDevice(UCXX52DealThread::CONFIG_WRITE_CHANNEL,list);
}

