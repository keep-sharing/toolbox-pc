#include "ucxx52model.h"
#include "ui_ucxx52model.h"

void UCXX52Model::initCmdSetting()
{
    connect(ui->ifContain_textedit,SIGNAL(textChanged()),this,SLOT(onTextEditTextChanged()));
    connect(ui->thenContent1_textedit,SIGNAL(textChanged()),this,SLOT(onTextEditTextChanged()));
    connect(ui->thenContent2_textedit,SIGNAL(textChanged()),this,SLOT(onTextEditTextChanged()));
    connect(ui->thenContent3_textedit,SIGNAL(textChanged()),this,SLOT(onTextEditTextChanged()));

    ui->inputLevel_cbx->setItemData(UCXX52DealThread::INC_GoseActive,UCXX52DealThread::INC_GoseActive);
    ui->inputLevel_cbx->setItemData(UCXX52DealThread::INC_GoseInactive,UCXX52DealThread::INC_GoseInactive);
    ui->inputLevel_cbx->setItemData(UCXX52DealThread::INC_ChangeState,UCXX52DealThread::INC_ChangeState);
    ui->inputLevel_cbx->setItemData(UCXX52DealThread::INC_IsActive,UCXX52DealThread::INC_IsActive);
    ui->inputLevel_cbx->setItemData(UCXX52DealThread::INC_IsInactive,UCXX52DealThread::INC_IsInactive);

    ui->level1_cbx->setCurrentIndex(0);
    ui->level2_cbx->setCurrentIndex(0);
    ui->level3_cbx->setCurrentIndex(0);

    ui->level1_cbx->setItemData(UCXX52DealThread::OP_GoseHigh,UCXX52DealThread::OP_GoseHigh);
    ui->level1_cbx->setItemData(UCXX52DealThread::OP_GoseLow,UCXX52DealThread::OP_GoseLow);
    ui->level1_cbx->setItemData(UCXX52DealThread::OP_ChangeState,UCXX52DealThread::OP_ChangeState);
    ui->level1_cbx->setItemData(UCXX52DealThread::OP_FollowInput,UCXX52DealThread::OP_FollowInput);

    ui->level2_cbx->setItemData(UCXX52DealThread::OP_GoseHigh,UCXX52DealThread::OP_GoseHigh);
    ui->level2_cbx->setItemData(UCXX52DealThread::OP_GoseLow,UCXX52DealThread::OP_GoseLow);
    ui->level2_cbx->setItemData(UCXX52DealThread::OP_ChangeState,UCXX52DealThread::OP_ChangeState);
    ui->level2_cbx->setItemData(UCXX52DealThread::OP_FollowInput,UCXX52DealThread::OP_FollowInput);

    ui->level3_cbx->setItemData(UCXX52DealThread::OP_GoseHigh,UCXX52DealThread::OP_GoseHigh);
    ui->level3_cbx->setItemData(UCXX52DealThread::OP_GoseLow,UCXX52DealThread::OP_GoseLow);
    ui->level3_cbx->setItemData(UCXX52DealThread::OP_ChangeState,UCXX52DealThread::OP_ChangeState);
    ui->level3_cbx->setItemData(UCXX52DealThread::OP_FollowInput,UCXX52DealThread::OP_FollowInput);

#if OUTPUT_WAVEFORM
    ui->level1_cbx->setItemData(OP_Waveform,tr("will output a waveform with a duration of "));
    ui->level2_cbx->setItemData(OP_Waveform,tr("will output a waveform with a duration of "));
    ui->level3_cbx->setItemData(OP_Waveform,tr("will output a waveform with a duration of "));
#endif

    ui->if_cbx->setItemData(UCXX52DealThread::IC_Empty,UCXX52DealThread::IC_Empty);
    ui->if_cbx->setItemData(UCXX52DealThread::IC_Time,UCXX52DealThread::IC_Time);
    ui->if_cbx->setItemData(UCXX52DealThread::IC_PSQ,UCXX52DealThread::IC_PSQ);
    ui->if_cbx->setItemData(UCXX52DealThread::IC_Input1,UCXX52DealThread::IC_Input1);
    ui->if_cbx->setItemData(UCXX52DealThread::IC_Input2,UCXX52DealThread::IC_Input2);
    ui->if_cbx->setItemData(UCXX52DealThread::IC_In1OrIn2,UCXX52DealThread::IC_In1OrIn2);
    ui->if_cbx->setItemData(UCXX52DealThread::IC_In1AndIn2,UCXX52DealThread::IC_In1AndIn2);
    ui->if_cbx->setItemData(UCXX52DealThread::IC_MsgRecv,UCXX52DealThread::IC_MsgRecv);
    ui->if_cbx->setItemData(UCXX52DealThread::IC_DevRestars,UCXX52DealThread::IC_DevRestars);
    ui->if_cbx->setItemData(UCXX52DealThread::IC_Analog1,UCXX52DealThread::IC_Analog1);
    ui->if_cbx->setItemData(UCXX52DealThread::IC_Analog2,UCXX52DealThread::IC_Analog2);
    ui->if_cbx->setItemData(UCXX52DealThread::IC_CHANNEL,UCXX52DealThread::IC_CHANNEL);
    ui->if_cbx->setItemData(UCXX52DealThread::IC_Counter1,UCXX52DealThread::IC_Counter1);
    ui->if_cbx->setItemData(UCXX52DealThread::IC_Counter2,UCXX52DealThread::IC_Counter2);

    ui->then1_cbx->setItemData(UCXX52DealThread::TC_Empty,UCXX52DealThread::TC_Empty);
    ui->then1_cbx->setItemData(UCXX52DealThread::TC_StatusMessage,UCXX52DealThread::TC_StatusMessage);
    ui->then1_cbx->setItemData(UCXX52DealThread::TC_CustomMessage,UCXX52DealThread::TC_CustomMessage);
    ui->then1_cbx->setItemData(UCXX52DealThread::TC_ALARM,UCXX52DealThread::TC_ALARM);
    ui->then1_cbx->setItemData(UCXX52DealThread::TC_Output1,UCXX52DealThread::TC_Output1);
    ui->then1_cbx->setItemData(UCXX52DealThread::TC_Output2,UCXX52DealThread::TC_Output2);
    ui->then1_cbx->setItemData(UCXX52DealThread::TC_DevRestart,UCXX52DealThread::TC_DevRestart);

    ui->then2_cbx->setItemData(UCXX52DealThread::TC_Empty,UCXX52DealThread::TC_Empty);
    ui->then2_cbx->setItemData(UCXX52DealThread::TC_StatusMessage,UCXX52DealThread::TC_StatusMessage);
    ui->then2_cbx->setItemData(UCXX52DealThread::TC_CustomMessage,UCXX52DealThread::TC_CustomMessage);
    ui->then2_cbx->setItemData(UCXX52DealThread::TC_ALARM,UCXX52DealThread::TC_ALARM);
    ui->then2_cbx->setItemData(UCXX52DealThread::TC_Output1,UCXX52DealThread::TC_Output1);
    ui->then2_cbx->setItemData(UCXX52DealThread::TC_Output2,UCXX52DealThread::TC_Output2);
    ui->then2_cbx->setItemData(UCXX52DealThread::TC_DevRestart,UCXX52DealThread::TC_DevRestart);

    ui->then3_cbx->setItemData(UCXX52DealThread::TC_Empty,UCXX52DealThread::TC_Empty);
    ui->then3_cbx->setItemData(UCXX52DealThread::TC_StatusMessage,UCXX52DealThread::TC_StatusMessage);
    ui->then3_cbx->setItemData(UCXX52DealThread::TC_CustomMessage,UCXX52DealThread::TC_CustomMessage);
    ui->then3_cbx->setItemData(UCXX52DealThread::TC_ALARM,UCXX52DealThread::TC_ALARM);
    ui->then3_cbx->setItemData(UCXX52DealThread::TC_Output1,UCXX52DealThread::TC_Output1);
    ui->then3_cbx->setItemData(UCXX52DealThread::TC_Output2,UCXX52DealThread::TC_Output2);
    ui->then3_cbx->setItemData(UCXX52DealThread::TC_DevRestart,UCXX52DealThread::TC_DevRestart);

    QList<QComboBox *> timeCbx ;
    timeCbx<<ui->continueTime_cbx<<ui->setLockoutTime_cbx<<ui->continueTimeAnalog_cbx<<ui->setLockoutTimeAnalog_cbx<<ui->continueTimeMudbus_cbx<<ui->setLockoutTimeMudbus_cbx
           <<ui->delayTimeSec1_cbx<<ui->durationSec1_cbx<<ui->highLevelSec1_cbx<<ui->lowLevelSec1_cbx
           <<ui->delayTimeSec2_cbx<<ui->durationSec2_cbx<<ui->highLevelSec2_cbx<<ui->lowLevelSec2_cbx
           <<ui->delayTimeSec3_cbx<<ui->durationSec3_cbx<<ui->highLevelSec3_cbx<<ui->lowLevelSec3_cbx;
    foreach (QComboBox *c, timeCbx) {
        c->setItemData(0,1000);//s
        c->setItemData(1,1);//ms
        c->setItemData(2,60000);//min
    }

    connect(ui->setLockouTimeMudbus_cb,&QCheckBox::clicked,ui->locktimeMudbus_frame,&QFrame::setVisible,Qt::UniqueConnection);
    connect(ui->setLockouTimeAnalog_cb,&QCheckBox::clicked,ui->locktimeAnalog_frame,&QFrame::setVisible,Qt::UniqueConnection);
    connect(ui->setLockouTime_cb,&QCheckBox::clicked,ui->locktime_frame,&QFrame::setVisible,Qt::UniqueConnection);

    initSettingTableview();
}

/**
 * 初始化表格
 * @brief UCXX52Model::initSettingTableview
 */
void UCXX52Model::initSettingTableview()
{
    model = new QStandardItemModel();
    QStringList headerlist;
    headerlist<<"ID"<<"Configuaration"<<"Edit"<<"Delete";
    model->setHorizontalHeaderLabels(headerlist);
    ui->tableView->setModel(model);
//        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//        ui->tableView->horizontalHeader()->setDefaultSectionSize(66);
    ui->tableView->setColumnWidth(ID,90);
    ui->tableView->setColumnWidth(CONFIGURATION,640);
    ui->tableView->setColumnWidth(EDIT,66);
    ui->tableView->setColumnWidth(TDELETE,66);

    ui->tableView->verticalHeader()->setDefaultSectionSize(100);
    ui->tableView->verticalHeader()->setHidden(true);

    model->setRowCount(UNXX_MAX_WORKNUM);


    QString picEditPath = ":/new/image/edit.png";
    QString picDelPath = ":/new/image/delete.png";
    PictureDelegate *picEdit;
    PictureDelegate *picDelete;
    picEdit = new PictureDelegate(picEditPath);
    picDelete = new PictureDelegate(picDelPath);
    commandList.clear();
    for(int row=0; row<UNXX_MAX_WORKNUM; row++ ){
        model->setData(model->index(row,ID),row+1);
        model->item(row,ID)->setTextAlignment(Qt::AlignCenter);
        ui->tableView->setItemDelegateForColumn(EDIT,picEdit);
        ui->tableView->setItemDelegateForColumn(TDELETE,picDelete);
        ui->tableView->setItemDelegateForColumn(ID,new EmptyDelegate());
        ui->tableView->setItemDelegateForColumn(CONFIGURATION,new EmptyDelegate());
        QVariantMap map;
        commandList.append(map);
    }
}

/**
 * 设置页面表格点击编辑或删除
 * @brief UCXX52Model::on_tableView_clicked
 * @param index
 */
void UCXX52Model::on_tableView_clicked(const QModelIndex &index)
{
    if(index.column() == EDIT){
        settingRow = index.row();
        ui->stackedWidget->setCurrentIndex(UCXX52DealThread::PAGE_SETTING_EDIT);
        ui->settingEditTitle_label->setText(tr("Configuration for command NO.%1").arg(index.row()+1));
        recoverySettingEdit();

        QVariantMap ifmap = commandList.at(index.row()).toMap().value("if_cbx").toMap();
        QVariantMap outputmap = commandList.at(index.row()).toMap().value("outputmap").toMap();
        if(ifmap.value("index").toInt() == UCXX52DealThread::IC_Empty){
            ui->if_cbx->setCurrentIndex(UCXX52DealThread::IC_Empty);
            ui->then1_cbx->setCurrentIndex(UCXX52DealThread::TC_Empty);
            ui->then2_cbx->setCurrentIndex(UCXX52DealThread::TC_Empty);
            ui->then3_cbx->setCurrentIndex(UCXX52DealThread::TC_Empty);
            ui->then2_cbx->setVisible(false);
            ui->then3_cbx->setVisible(false);
            ui->thenAdd2_btn->setVisible(false);
            ui->then2_label->setVisible(false);
            ui->then3_label->setVisible(false);
            ui->thenDel2_btn->setVisible(false);
            ui->thenDel3_btn->setVisible(false);
            ui->if_stackedWidget->setCurrentIndex(ISW_Empty);
            ui->then1_stackedWidget->setCurrentIndex(TSW_Empty);
            ui->then2_stackedWidget->setCurrentIndex(TSW_Empty);
            ui->then3_stackedWidget->setCurrentIndex(TSW_Empty);
        }else{
            ui->if_cbx->setCurrentIndex(ui->if_cbx->findData(ifmap.value("index").toInt()));
            if(ifmap.value("index").toInt() == IC_Time){
                ui->timeisDay_cbx->setCurrentIndex(ifmap.value("timeisDay").toInt());
                ui->timeisTime_tde->setTime(QTime(ifmap.value("timeisTime").toString().split(":").at(0).toInt(),ifmap.value("timeisTime").toString().split(":").at(1).toInt()));

            }else if(ifmap.value("index").toInt() == IC_Input1 ||
                     ifmap.value("index").toInt() == IC_Input2 ||
                     ifmap.value("index").toInt() == IC_In1OrIn2 ||
                     ifmap.value("index").toInt() == IC_In1AndIn2 ){

                ui->inputLevel_cbx->setCurrentIndex(ui->inputLevel_cbx->findData(ifmap.value("inputLevel").toInt()));
//                ui->inputLevel_cbx->setCurrentIndex(ifmap.value("inputLevel").toInt());
                if(ifmap.value("continueForSec").toInt() == Empty_Time){
                    if(ifmap.value("inputLevel").toInt() == INC_IsActive || ifmap.value("inputLevel").toInt() == INC_IsInactive){
                        ui->continuedSec_frame->setVisible(false);
                    }else{
                        ui->continuedSec_frame->setVisible(true);
                    }
                    ui->continuedSec_lineedit->setText(ascMsToSec(ifmap.value("continueForSec").toString(),ifmap.value("inputContinueUnit").toInt()));
                }else{
                    ui->continuedSec_lineedit->setText(ascMsToSec(ifmap.value("continueForSec").toString(),ifmap.value("inputContinueUnit").toInt()));
                }

                if(ifmap.value("setLockTime").toInt() == Empty_Time){
                    ui->setLockouTime_cb->setChecked(false);
                    ui->locktime_frame->setVisible(false);
                    ui->lockouttime_lineedit->setText("0");
                }else{
                    ui->setLockouTime_cb->setChecked(true);
                    ui->locktime_frame->setVisible(true);
                    ui->lockouttime_lineedit->setText(ascMsToSec(ifmap.value("setLockTime").toString(),ifmap.value("locktimeUnit").toInt()));
                }

                ui->continueTime_cbx->setCurrentIndex(ifmap.value("inputContinueUnit").toInt());
                ui->setLockoutTime_cbx->setCurrentIndex(ifmap.value("locktimeUnit").toInt());

            }else if(ifmap.value("index").toInt() == IC_MsgRecv){
                ui->ifContain_textedit->setText(ifmap.value("ussd").toString());
            }else if(ifmap.value("index").toInt() == IC_DevRestars){

            }else if(ifmap.value("index").toInt() == IC_Analog1 || ifmap.value("index").toInt() == IC_Analog2){

                ui->analogStatus_cbx->setCurrentIndex(ifmap.value("analogStatus").toInt());
                ui->continuedSecAnalog_lineedit->setText(ascMsToSec(ifmap.value("continueForSecAnalog").toString(), ifmap.value("inputContinueAnalogUnit").toInt()));
                if(ifmap.value("analogStatus").toInt() == QunpUCXX52::UNXX_AI_ABOVE)
                    ui->aboveMa_lineedit->setText(mAtoThreshold(ifmap.value("aboveValue").toString(),ifmap.value("index").toInt()));
                if(ifmap.value("analogStatus").toInt() == QunpUCXX52::UNXX_AI_BELOW)
                    ui->aboveMa_lineedit->setText(mAtoThreshold(ifmap.value("belowValue").toString(),ifmap.value("index").toInt()));
                if(ifmap.value("analogStatus").toInt() == QunpUCXX52::UNXX_AI_WITHIN){
                    ui->withMa1_lineedit->setText(mAtoThreshold(ifmap.value("belowValue").toString(),ifmap.value("index").toInt()));
                    ui->withMa2_lineedit->setText(mAtoThreshold(ifmap.value("aboveValue").toString(),ifmap.value("index").toInt()));
                }

                if(ifmap.value("setLockTime").toInt() == Empty_Time){
                    ui->setLockouTimeAnalog_cb->setChecked(false);
                    ui->locktimeAnalog_frame->setVisible(false);
                    ui->lockouttimeAnalog_lineedit->setText("0");
                }else{
                    ui->setLockouTimeAnalog_cb->setChecked(true);
                    ui->locktimeAnalog_frame->setVisible(true);
                    ui->lockouttimeAnalog_lineedit->setText(ascMsToSec(ifmap.value("setLockTime").toString(), ifmap.value("locktimeAnalogUnit").toInt()));
                }
                ui->continueTimeAnalog_cbx->setCurrentIndex(ifmap.value("inputContinueAnalogUnit").toInt());
                ui->setLockoutTimeAnalog_cbx->setCurrentIndex(ifmap.value("locktimeAnalogUnit").toInt());
            }else if(ifmap.value("index").toInt() == IC_CHANNEL){
                ui->modbusChannelStatus_cbx->setCurrentIndex(ui->modbusChannelStatus_cbx->findData(ifmap.value("modbusChannelStatus").toInt()));

                qDebug()<<ui->modbusStatus_cbx->itemData(0)<<ui->modbusStatus_cbx->itemData(1)<<ifmap.value("modbusStatus").toInt()<<ifmap.value("modbusChannelStatus").toInt();
                ui->modbusStatus_cbx->setCurrentIndex(ui->modbusStatus_cbx->findData(ifmap.value("modbusStatus").toInt()));
                ui->continuedSecMudbus_lineedit->setText(ascMsToSec(ifmap.value("continueForSecMudbus").toString(), ifmap.value("inputContinueMudbusUnit").toInt()));
                if(ifmap.value("modbusStatus").toInt() == QunpUCXX52::UNXX_MB_ABOVE)
                    ui->modbusAboveMa_lineedit->setText((ifmap.value("aboveValue").toString()));
                if(ifmap.value("modbusStatus").toInt() == QunpUCXX52::UNXX_MB_BELOW)
                    ui->modbusAboveMa_lineedit->setText((ifmap.value("belowValue").toString()));
                if(ifmap.value("modbusStatus").toInt() == QunpUCXX52::UNXX_MB_WITHIN){
                    ui->modbusWithMa1_lineedit->setText((ifmap.value("belowValue").toString()));
                    ui->modbusWithMa2_lineedit->setText((ifmap.value("aboveValue").toString()));
                }

                if(ifmap.value("setLockTime").toInt() == Empty_Time){
                    ui->setLockouTimeMudbus_cb->setChecked(false);
                    ui->locktimeMudbus_frame->setVisible(false);
                    ui->lockouttimeMudbus_lineedit->setText("0");
                }else{
                    ui->setLockouTimeMudbus_cb->setChecked(true);
                    ui->locktimeMudbus_frame->setVisible(true);
                    ui->lockouttimeMudbus_lineedit->setText(ascMsToSec(ifmap.value("setLockTime").toString(), ifmap.value("locktimeMudbusUnit").toInt()));
                }
                ui->continueTimeMudbus_cbx->setCurrentIndex(ifmap.value("inputContinueMudbusUnit").toInt());
                ui->setLockoutTimeMudbus_cbx->setCurrentIndex(ifmap.value("locktimeMudbusUnit").toInt());
            }else if(ifmap.value("index").toInt() == IC_Counter1 || ifmap.value("index").toInt() == IC_Counter2){
                ui->counterNum_lineedit->setText(ifmap.value("counterNum").toString());
            }

            //Then1
            QVariantMap then1map = commandList.at(index.row()).toMap().value("then1_cbx").toMap();
            qDebug()<<then1map.value("index").toInt();
            ui->then1_cbx->setCurrentIndex(ui->then1_cbx->findData(then1map.value("index").toInt()));
            if(ui->then1_cbx->currentData() == TC_Output1 || ui->then1_cbx->currentData() == TC_Output2){

                if(ui->then1_cbx->currentData().toInt() == TC_Output1){
                    ui->delayTimeSec1_lineedit->setText(ascMsToSec(then1map.value("delay").toString(), outputmap.value("outputDelayUnit1").toInt()));
                    ui->durationSec1_lineedit->setText(ascMsToSec(then1map.value("duration").toString(), outputmap.value("durationUnit1").toInt()));
                    ui->delayTimeSec1_cbx->setCurrentIndex(outputmap.value("outputDelayUnit1").toInt());
                    ui->durationSec1_cbx->setCurrentIndex(outputmap.value("durationUnit1").toInt());
                }else if(ui->then1_cbx->currentData().toInt() == TC_Output2){
                    ui->delayTimeSec1_lineedit->setText(ascMsToSec(then1map.value("delay").toString(), outputmap.value("outputDelayUnit2").toInt()));
                    ui->durationSec1_lineedit->setText(ascMsToSec(then1map.value("duration").toString(), outputmap.value("durationUnit2").toInt()));
                    ui->delayTimeSec1_cbx->setCurrentIndex(outputmap.value("outputDelayUnit2").toInt());
                    ui->durationSec1_cbx->setCurrentIndex(outputmap.value("durationUnit2").toInt());
                }
                ui->level1_cbx->setCurrentIndex(then1map.value("level").toInt());

                qDebug()<<then1map.value("level").toInt()
                             <<then1map.value("delay").toString()
                             <<then1map.value("duration").toString();

                if(ui->durationWaveform1_lineedit->isVisible())
                    ui->durationWaveform1_lineedit->setText((then1map.value("durationWF").toString()));
                if(ui->highLevelSec1_lineedit->isVisible())
                    ui->highLevelSec1_lineedit->setText(ascMsToSec(then1map.value("high").toString()));
                if(ui->lowLevelSec1_lineedit->isVisible())
                    ui->lowLevelSec1_lineedit->setText(ascMsToSec(then1map.value("low").toString()));

            }else if(ui->then1_cbx->currentData() == TC_CustomMessage){
                ui->thenContent1_textedit->setText(then1map.value("ussd").toString());

            }

            //Then2
            QVariantMap then2map = commandList.at(index.row()).toMap().value("then2_cbx").toMap();

//            for(int i=0; i<ui->then2_cbx->count(); i++){
//                qDebug()<<ui->then2_cbx->itemData(i).toInt()<<ui->then2_cbx->itemText(i);
//            }
//            qDebug()<<then2map.value("index").toInt()<<ui->then2_cbx->findData(then2map.value("index").toInt());
            if(then2map.value("index").toInt() != UCXX52DealThread::TC_Empty){
                ui->thenAdd1_btn->click();
                ui->then2_cbx->setCurrentIndex(ui->then2_cbx->findData(then2map.value("index").toInt()));

                if(then2map.value("index").toInt() == TC_Output1 || then2map.value("index").toInt() == TC_Output2){
                    ui->level2_cbx->setCurrentIndex(then2map.value("level").toInt());
                    if(then2map.value("index").toInt() == TC_Output1){
                        ui->durationSec2_lineedit->setText(ascMsToSec(then2map.value("duration").toString(),outputmap.value("durationUnit1").toInt()));
                        ui->delayTimeSec2_lineedit->setText(ascMsToSec(then2map.value("delay").toString() ,outputmap.value("outputDelayUnit1").toInt()));
                        ui->delayTimeSec2_cbx->setCurrentIndex(outputmap.value("outputDelayUnit1").toInt());
                        ui->durationSec2_cbx->setCurrentIndex(outputmap.value("durationUnit1").toInt());
                    }else if(then2map.value("index").toInt() == TC_Output2){
                        ui->durationSec2_lineedit->setText(ascMsToSec(then2map.value("duration").toString(),outputmap.value("durationUnit2").toInt()));
                        ui->delayTimeSec2_lineedit->setText(ascMsToSec(then2map.value("delay").toString() ,outputmap.value("outputDelayUnit2").toInt()));
                        ui->delayTimeSec2_cbx->setCurrentIndex(outputmap.value("outputDelayUnit2").toInt());
                        ui->durationSec2_cbx->setCurrentIndex(outputmap.value("durationUnit2").toInt());
                    }

                    if(ui->durationWaveform2_lineedit->isVisible())
                        ui->durationWaveform2_lineedit->setText((then2map.value("durationWF").toString()));
                    if(ui->highLevelSec2_lineedit->isVisible())
                        ui->highLevelSec2_lineedit->setText(ascMsToSec(then2map.value("high").toString()));
                    if(ui->lowLevelSec2_lineedit->isVisible())
                        ui->lowLevelSec2_lineedit->setText(ascMsToSec(then2map.value("low").toString()));

                }else if(then2map.value("index").toInt() == TC_CustomMessage){
                    ui->thenContent2_textedit->setText(then2map.value("ussd").toString());
                }
            }else{
                ui->then2_cbx->setVisible(false);
                ui->thenAdd2_btn->setVisible(false);
                ui->thenDel2_btn->setVisible(false);
                ui->then2_label->setVisible(false);
                ui->then2_stackedWidget->setCurrentIndex(TSW_Empty);
            }
            //Then3
            QVariantMap then3map = commandList.at(index.row()).toMap().value("then3_cbx").toMap();
            if(then3map.value("index").toInt() != UCXX52DealThread::TC_Empty){
                ui->thenAdd2_btn->click();
                ui->then3_cbx->setCurrentIndex(ui->then3_cbx->findData(then3map.value("index").toInt()));

                if(then3map.value("index").toInt()== TC_Output1 || then3map.value("index").toInt() == TC_Output2){
                    ui->level3_cbx->setCurrentIndex(then3map.value("level").toInt());
                    if(then3map.value("index").toInt() == TC_Output1){
                        ui->durationSec3_lineedit->setText(ascMsToSec(then3map.value("duration").toString(), outputmap.value("durationUnit1").toInt()));
                        ui->delayTimeSec3_lineedit->setText(ascMsToSec(then3map.value("delay").toString(), outputmap.value("outputDelayUnit1").toInt()));
                        ui->delayTimeSec3_cbx->setCurrentIndex(outputmap.value("outputDelayUnit1").toInt());
                        ui->durationSec3_cbx->setCurrentIndex(outputmap.value("durationUnit1").toInt());
                    }else if(then3map.value("index").toInt() == TC_Output2){
                        ui->durationSec3_lineedit->setText(ascMsToSec(then3map.value("duration").toString(), outputmap.value("durationUnit2").toInt()));
                        ui->delayTimeSec3_lineedit->setText(ascMsToSec(then3map.value("delay").toString(), outputmap.value("outputDelayUnit2").toInt()));
                        ui->delayTimeSec3_cbx->setCurrentIndex(outputmap.value("outputDelayUnit2").toInt());
                        ui->durationSec3_cbx->setCurrentIndex(outputmap.value("durationUnit2").toInt());
                    }

                    if(ui->durationWaveform3_lineedit->isVisible())
                        ui->durationWaveform3_lineedit->setText((then3map.value("durationWF").toString()));
                    if(ui->highLevelSec3_lineedit->isVisible())
                        ui->highLevelSec3_lineedit->setText(ascMsToSec(then3map.value("high").toString()));
                    if(ui->lowLevelSec3_lineedit->isVisible())
                        ui->lowLevelSec3_lineedit->setText(ascMsToSec(then3map.value("low").toString()));

                }else if(then3map.value("index").toInt() == TC_CustomMessage){
                    ui->thenContent3_textedit->setText(then3map.value("ussd").toString());
                }
            }else{
                ui->then3_cbx->setVisible(false);
                ui->thenDel3_btn->setVisible(false);
                ui->then3_label->setVisible(false);
                ui->then3_stackedWidget->setCurrentIndex(TSW_Empty);
            }
        }

    }else if(index.column() == TDELETE){

        if(!model->index(index.row(),CONFIGURATION).data().toString().isEmpty()){
            QSettings settings(m_iniPath, QSettings::IniFormat);
            settings.beginGroup("CloseTipAgain");
            if(settings.value("deleteCommand").toBool()){
                if(showQuestion(this,tr("Attention"),MyMessageBox::TYPE_DELETE_CMD,tr("Do you really want to delete this command?")) == QMessageBox::Ok){
                    QVariantMap map;
                    map.insert("saveToDev",true);

                    model->setData(model->index(index.row(),CONFIGURATION),tr(""));
                    commandList.replace(index.row(),map);
                }
            }else{
                QVariantMap map;
                map.insert("saveToDev",true);

                model->setData(model->index(index.row(),CONFIGURATION),tr(""));
                commandList.replace(index.row(),map);
            }
            settings.endGroup();
        }
    }
}

/**
 * IF 变化选择
 * @brief UCXX52Model::on_if_cbx_currentIndexChanged
 * @param index
 */
void UCXX52Model::on_if_cbx_currentIndexChanged(int index)
{
    index = ui->if_cbx->currentData().toInt();

    if(index != IC_DevRestars){
        if(ui->then1_cbx->findData(TC_DevRestart) == -1){
            ui->then1_cbx->addItem(tr("Restart the device"),TC_DevRestart);
        }
        if(ui->then2_cbx->findData(TC_DevRestart) == -1){
            ui->then2_cbx->addItem(tr("Restart the device"),TC_DevRestart);
        }
        if(ui->then3_cbx->findData(TC_DevRestart) == -1){
            ui->then3_cbx->addItem(tr("Restart the device"),TC_DevRestart);
        }
    }
    ui->inputLevel_cbx->clear();
    ui->inputLevel_cbx->addItem(tr("goes active (rising edge-triggered)"),INC_GoseActive);
    ui->inputLevel_cbx->addItem(tr("goes inactive (falling edge-triggered)"),INC_GoseInactive);
    ui->inputLevel_cbx->addItem(tr("changes state(trigger on rising or falling edge)"),INC_ChangeState);
    ui->inputLevel_cbx->addItem(tr("is active (high level triggered)"),INC_IsActive);
    ui->inputLevel_cbx->addItem(tr("is inactive (low level triggered)"),INC_IsInactive);
    switch (index) {
    case IC_Empty:
        ui->if_stackedWidget->setCurrentIndex(ISW_Empty);
        break;
    case IC_Time:
        ui->if_stackedWidget->setCurrentIndex(ISW_Time);
        on_timeisDay_cbx_currentIndexChanged(ui->timeisDay_cbx->currentText());
        break;
    case IC_PSQ:
        ui->if_stackedWidget->setCurrentIndex(ISW_Empty);
        break;
    case IC_Input1:
        ui->if_stackedWidget->setCurrentIndex(ISW_Input);
        break;
    case IC_Input2:
        ui->if_stackedWidget->setCurrentIndex(ISW_Input);
        break;
    case IC_In1OrIn2:
        ui->if_stackedWidget->setCurrentIndex(ISW_Input);
        break;
    case IC_In1AndIn2:{
        ui->if_stackedWidget->setCurrentIndex(ISW_Input);
        ui->inputLevel_cbx->removeItem(ui->inputLevel_cbx->findData(INC_GoseActive));
        ui->inputLevel_cbx->removeItem(ui->inputLevel_cbx->findData(INC_GoseInactive));
        ui->inputLevel_cbx->removeItem(ui->inputLevel_cbx->findData(INC_ChangeState));

//        ui->inputLevel_cbx->removeItem(INC_GoseActive);
//        ui->inputLevel_cbx->removeItem(INC_GoseInactive);
//        ui->inputLevel_cbx->removeItem(INC_ChangeState);
    }
        break;
    case IC_MsgRecv:
        ui->if_stackedWidget->setCurrentIndex(ISW_MsgRecv);
        break;
    case IC_DevRestars:{
        ui->if_stackedWidget->setCurrentIndex(ISW_Empty);
        ui->then1_cbx->removeItem(ui->then1_cbx->findData(TC_DevRestart));
        ui->then2_cbx->removeItem(ui->then2_cbx->findData(TC_DevRestart));
        ui->then3_cbx->removeItem(ui->then3_cbx->findData(TC_DevRestart));
    }
        break;
    case IC_Analog1:{
        QSettings settings(m_iniPath,QSettings::IniFormat);
        settings.beginGroup("AiUnit");
#if NOT_USE_DEVICE
            ui->withUint1_label->setText("°C");
            ui->withUint2_label->setText("°C");
            ui->aboveUint_label->setText("°C");
#elif 1
            ui->withUint1_label->setText(settings.value("A"+m_statusPageInfo.sn).toString());
            ui->withUint2_label->setText(settings.value("A"+m_statusPageInfo.sn).toString());
            ui->aboveUint_label->setText(settings.value("A"+m_statusPageInfo.sn).toString());
#endif
        settings.endGroup();
        ui->if_stackedWidget->setCurrentIndex(ISW_Analog);

        on_analogStatus_cbx_currentIndexChanged(ui->analogStatus_cbx->currentIndex());
    }
        break;
    case IC_Analog2:{
        QSettings settings(m_iniPath,QSettings::IniFormat);
        settings.beginGroup("AiUnit");
#if NOT_USE_DEVICE
            ui->withUint1_label->setText("Ma");
            ui->withUint2_label->setText("Ma");
            ui->aboveUint_label->setText("Ma");
#elif 1
            ui->withUint1_label->setText(settings.value("B"+m_statusPageInfo.sn).toString());
            ui->withUint2_label->setText(settings.value("B"+m_statusPageInfo.sn).toString());
            ui->aboveUint_label->setText(settings.value("B"+m_statusPageInfo.sn).toString());
#endif
        settings.endGroup();
        ui->if_stackedWidget->setCurrentIndex(ISW_Analog);
        on_analogStatus_cbx_currentIndexChanged(ui->analogStatus_cbx->currentIndex());
    }
        break;
    case IC_CHANNEL:{
        ui->if_stackedWidget->setCurrentIndex(ISW_Channel);
        on_modbusStatus_cbx_currentIndexChanged(ui->modbusStatus_cbx->currentIndex());
    }
        break;
    case IC_Counter1:{
        ui->if_stackedWidget->setCurrentIndex(ISW_Counter);
    }
        break;
    case IC_Counter2:{
        ui->if_stackedWidget->setCurrentIndex(ISW_Counter);
    }
        break;
    default:
        break;
    }
}
/**
 * Input 电平选择
 * @brief UCXX52Model::on_inputLevel_cbx_currentIndexChanged
 * @param index
 */
void UCXX52Model::on_inputLevel_cbx_currentIndexChanged(int index)
{
    index = ui->inputLevel_cbx->currentData().toInt();
    if(ui->if_cbx->currentData().toInt() == IC_Input1 || ui->if_cbx->currentData().toInt() == IC_Input2){
        ui->level1_cbx->setCurrentIndex(0);
        ui->level2_cbx->setCurrentIndex(0);
        ui->level3_cbx->setCurrentIndex(0);

        ui->level1_cbx->removeItem(ui->level1_cbx->findData(OP_FollowInput));
        ui->level2_cbx->removeItem(ui->level2_cbx->findData(OP_FollowInput));
        ui->level3_cbx->removeItem(ui->level3_cbx->findData(OP_FollowInput));
    }
    switch (index) {
    case INC_GoseActive:{
        ui->continuedSec_frame->setVisible(true);
    }
        break;
    case INC_GoseInactive:{
        ui->continuedSec_frame->setVisible(true);
    }
        break;
    case INC_ChangeState:{
        ui->continuedSec_frame->setVisible(true);
//        if(ui->if_cbx->currentData().toInt() == IC_In1OrIn2){
//            ui->level1_cbx->addItem(tr("will follow the input to change"),tr("will follow the input to change"));
//            ui->level2_cbx->addItem(tr("will follow the input to change"),tr("will follow the input to change"));
//            ui->level3_cbx->addItem(tr("will follow the input to change"),tr("will follow the input to change"));
//        }
        if(ui->if_cbx->currentData().toInt() == IC_Input1){
            if(ui->then1_cbx->currentData() == TC_Output1)
                ui->level1_cbx->addItem(tr("will follow the input to change"),OP_FollowInput);
            if(ui->then2_cbx->currentData() == TC_Output1)
                ui->level2_cbx->addItem(tr("will follow the input to change"),OP_FollowInput);
            if(ui->then3_cbx->currentData() == TC_Output1)
                ui->level3_cbx->addItem(tr("will follow the input to change"),OP_FollowInput);
        }
        if(ui->if_cbx->currentData().toInt() == IC_Input2){
            if(ui->then1_cbx->currentData() == TC_Output2)
                ui->level1_cbx->addItem(tr("will follow the input to change"),OP_FollowInput);
            if(ui->then2_cbx->currentData() == TC_Output2)
                ui->level2_cbx->addItem(tr("will follow the input to change"),OP_FollowInput);
            if(ui->then3_cbx->currentData() == TC_Output2)
                ui->level3_cbx->addItem(tr("will follow the input to change"),OP_FollowInput);
        }
    }
        break;
    case INC_IsActive:{
        ui->continuedSec_frame->setVisible(false);
    }
        break;
    case INC_IsInactive:{
        ui->continuedSec_frame->setVisible(false);
    }
        break;
    default:
        break;
    }
}

//==================================================Then==========================================//
/**
 * Then1 点击add
 * @brief UCXX52Model::on_statMessAdd_btn_clicked
 */
void UCXX52Model::on_thenAdd1_btn_clicked()
{
    ui->then2_stackedWidget->setVisible(true);
    ui->then2_cbx->setVisible(true);
    ui->thenAdd2_btn->setVisible(true);
    ui->then2_label->setVisible(true);
    ui->thenDel2_btn->setVisible(true);
    ui->then2_cbx->setCurrentIndex(TC_Empty);

    ui->thenAdd1_btn->setVisible(false);
}
/**
 * Then2 点击add
 * @brief UCXX52Model::on_statMessAdd_btn_2_clicked
 */
void UCXX52Model::on_thenAdd2_btn_clicked()
{
    ui->then3_stackedWidget->setVisible(true);
    ui->then3_cbx->setVisible(true);
    ui->then3_label->setVisible(true);
    ui->thenDel3_btn->setVisible(true);
    ui->then3_cbx->setCurrentIndex(TC_Empty);

    ui->thenAdd2_btn->setVisible(false);
    ui->thenDel2_btn->setVisible(false);
}

/**
 * 删除当前Then2
 * @brief UCXX52Model::on_thenDel2_btn_clicked
 */
void UCXX52Model::on_thenDel2_btn_clicked()
{
    ui->then2_cbx->setCurrentIndex(TC_Empty);
    ui->then2_cbx->setVisible(false);
    ui->then2_label->setVisible(false);
    ui->thenAdd2_btn->setVisible(false);
    ui->thenDel2_btn->setVisible(false);

    ui->thenAdd1_btn->setVisible(true);
}
/**
 * 删除当前Then3
 * @brief UCXX52Model::on_thenDel1_btn_clicked
 */
void UCXX52Model::on_thenDel3_btn_clicked()
{
    ui->then3_cbx->setCurrentIndex(TC_Empty);
    ui->then3_cbx->setVisible(false);
    ui->then3_label->setVisible(false);
    ui->thenDel3_btn->setVisible(false);

    if(ui->then2_cbx->isVisible()){
        ui->thenAdd2_btn->setVisible(true);
        ui->thenDel2_btn->setVisible(true);
    }else{
        ui->thenAdd1_btn->setVisible(true);
    }

}

/**
 * Then 下拉框变化，stackedWidget跟随变化
 * @brief UCXX52Model::on_then1_cbx_currentIndexChanged
 * @param arg1
 */
void UCXX52Model::on_then1_cbx_currentIndexChanged(int index)
{

    disconnect(ui->then1_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then1_cbx_currentIndexChanged(int)));
    disconnect(ui->then2_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then2_cbx_currentIndexChanged(int)));
    disconnect(ui->then3_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then3_cbx_currentIndexChanged(int)));
    //1个if下不能同时存在多个msg
    removeThenCbxMsg(2);
    removeThenCbxMsg(3);

    index = ui->then1_cbx->currentData().toInt();
    qDebug()<<index;
    switch (index) {
    case TC_Empty:
        ui->then1_stackedWidget->setCurrentIndex(TSW_Empty);
        ui->thenAdd1_btn->setGeometry(THEN_ADD_BTN_X1,130,31,21);

        insertThenCbxMsg(2);
        insertThenCbxMsg(3);
        break;
    case TC_StatusMessage:{
        ui->then1_stackedWidget->setCurrentIndex(TSW_Empty);
        ui->thenAdd1_btn->setGeometry(THEN_ADD_BTN_X1,130,31,21);
    }
        break;
    case TC_CustomMessage:
        ui->then1_stackedWidget->setCurrentIndex(TSW_CustomMessage);
        ui->thenAdd1_btn->setGeometry(THEN_ADD_BTN_X3,130,31,21);

        break;
    case TC_ALARM:
        ui->then1_stackedWidget->setCurrentIndex(TSW_Empty);
        ui->thenAdd1_btn->setGeometry(THEN_ADD_BTN_X1,130,31,21);
        break;
    case TC_Output1:
        ui->then1_stackedWidget->setCurrentIndex(TSW_Output);
        ui->level1_cbx->setCurrentIndex(-1);
        ui->level1_cbx->setCurrentIndex(-0);
        ui->thenAdd1_btn->setGeometry(THEN_ADD_BTN_X2,130,31,21);

        insertThenCbxMsg(2);
        insertThenCbxMsg(3);

        ui->level1_cbx->removeItem(ui->level1_cbx->findData(OP_FollowInput));
        if((ui->if_cbx->currentData().toInt() == IC_Input1 ) &&  ui->inputLevel_cbx->currentData() == INC_ChangeState){
            ui->level1_cbx->addItem(tr("will follow the input to change"),OP_FollowInput);
        }
        break;
    case TC_Output2:
        ui->then1_stackedWidget->setCurrentIndex(TSW_Output);
        ui->level1_cbx->setCurrentIndex(-1);
        ui->level1_cbx->setCurrentIndex(-0);
        ui->thenAdd1_btn->setGeometry(THEN_ADD_BTN_X2,130,31,21);

        insertThenCbxMsg(2);
        insertThenCbxMsg(3);

        ui->level1_cbx->removeItem(ui->level1_cbx->findData(OP_FollowInput));
        if((/*ui->if_cbx->currentData().toInt() == IC_Input1 ||*/ ui->if_cbx->currentData().toInt() == IC_Input2) &&  ui->inputLevel_cbx->currentData() == INC_ChangeState){
            ui->level1_cbx->addItem(tr("will follow the input to change"),OP_FollowInput);
        }
        break;
    case TC_DevRestart:
        ui->then1_stackedWidget->setCurrentIndex(TSW_Empty);
        ui->thenAdd1_btn->setGeometry(THEN_ADD_BTN_X1,130,31,21);

        insertThenCbxMsg(2);
        insertThenCbxMsg(3);
        break;
    default:
        break;
    }

    connect(ui->then1_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then1_cbx_currentIndexChanged(int)));
    connect(ui->then2_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then2_cbx_currentIndexChanged(int)));
    connect(ui->then3_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then3_cbx_currentIndexChanged(int)));
}

void UCXX52Model::on_then2_cbx_currentIndexChanged(int index)
{
    index = ui->then2_cbx->currentData().toInt();
    disconnect(ui->then1_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then1_cbx_currentIndexChanged(int)));
    disconnect(ui->then2_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then2_cbx_currentIndexChanged(int)));
    disconnect(ui->then3_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then3_cbx_currentIndexChanged(int)));

    //1个if下不能同时存在多个msg
    removeThenCbxMsg(1);
    removeThenCbxMsg(3);

    index = ui->then2_cbx->currentData().toInt();
    switch (index) {
    case TC_Empty:
        ui->then2_stackedWidget->setCurrentIndex(TSW_Empty);
        ui->thenAdd2_btn->setGeometry(THEN_ADD_BTN_X1,220,31,21);
        ui->thenDel2_btn->setGeometry(THEN_DEL_BTN_X1,220,31,21);

        insertThenCbxMsg(1);
        insertThenCbxMsg(3);

        break;
    case TC_StatusMessage:
        ui->then2_stackedWidget->setCurrentIndex(TSW_Empty);
        ui->thenAdd2_btn->setGeometry(THEN_ADD_BTN_X1,220,31,21);
        ui->thenDel2_btn->setGeometry(THEN_DEL_BTN_X1,220,31,21);

        break;
    case TC_CustomMessage:
        ui->then2_stackedWidget->setCurrentIndex(TSW_CustomMessage);
        ui->thenAdd2_btn->setGeometry(THEN_ADD_BTN_X3,220,31,21);
        ui->thenDel2_btn->setGeometry(THEN_DEL_BTN_X3,220,31,21);
        break;
    case TC_ALARM:
        ui->then2_stackedWidget->setCurrentIndex(TSW_Empty);
        ui->thenAdd2_btn->setGeometry(THEN_ADD_BTN_X1,220,31,21);
        ui->thenDel2_btn->setGeometry(THEN_DEL_BTN_X1,220,31,21);
        break;
    case TC_Output1:
        ui->then2_stackedWidget->setCurrentIndex(TSW_Output);
        ui->level2_cbx->setCurrentIndex(-1);
        ui->level2_cbx->setCurrentIndex(0);
        ui->thenAdd2_btn->setGeometry(THEN_ADD_BTN_X2,220,31,21);
        ui->thenDel2_btn->setGeometry(THEN_DEL_BTN_X2,220,31,21);

        insertThenCbxMsg(1);
        insertThenCbxMsg(3);

        ui->level2_cbx->removeItem(ui->level2_cbx->findData(OP_FollowInput));
        if((ui->if_cbx->currentData().toInt() == IC_Input1 ) &&  ui->inputLevel_cbx->currentData() == INC_ChangeState){
            ui->level2_cbx->addItem(tr("will follow the input to change"),OP_FollowInput);
        }
        break;
    case TC_Output2:
        ui->then2_stackedWidget->setCurrentIndex(TSW_Output);
        ui->level2_cbx->setCurrentIndex(-1);
        ui->level2_cbx->setCurrentIndex(0);
        ui->thenAdd2_btn->setGeometry(THEN_ADD_BTN_X2,220,31,21);
        ui->thenDel2_btn->setGeometry(THEN_DEL_BTN_X2,220,31,21);

        insertThenCbxMsg(1);
        insertThenCbxMsg(3);

        ui->level2_cbx->removeItem(ui->level2_cbx->findData(OP_FollowInput));
        if((/*ui->if_cbx->currentData().toInt() == IC_Input1 ||*/ ui->if_cbx->currentData().toInt() == IC_Input2) &&  ui->inputLevel_cbx->currentData() == INC_ChangeState){
            ui->level2_cbx->addItem(tr("will follow the input to change"),OP_FollowInput);
        }
        break;
    case TC_DevRestart:
        ui->then2_stackedWidget->setCurrentIndex(TSW_Empty);
        ui->thenAdd2_btn->setGeometry(THEN_ADD_BTN_X1,220,31,21);
        ui->thenDel2_btn->setGeometry(THEN_DEL_BTN_X1,220,31,21);

        insertThenCbxMsg(1);
        insertThenCbxMsg(3);

        break;
    default:
        break;
    }

    connect(ui->then1_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then1_cbx_currentIndexChanged(int)));
    connect(ui->then2_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then2_cbx_currentIndexChanged(int)));
    connect(ui->then3_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then3_cbx_currentIndexChanged(int)));
}

void UCXX52Model::on_then3_cbx_currentIndexChanged(int index)
{
    index = ui->then3_cbx->currentData().toInt();
    disconnect(ui->then1_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then1_cbx_currentIndexChanged(int)));
    disconnect(ui->then2_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then2_cbx_currentIndexChanged(int)));
    disconnect(ui->then3_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then3_cbx_currentIndexChanged(int)));

    //1个if下不能同时存在多个msg
    removeThenCbxMsg(1);
    removeThenCbxMsg(2);

    index = ui->then3_cbx->currentData().toInt();
    switch (index) {
    case TC_Empty:
        ui->then3_stackedWidget->setCurrentIndex(TSW_Empty);
        ui->thenDel3_btn->setGeometry(THEN_DEL_BTN_X1,310,31,21);

        insertThenCbxMsg(1);
        insertThenCbxMsg(2);

        break;
    case TC_StatusMessage:
        ui->then3_stackedWidget->setCurrentIndex(TSW_Empty);
        ui->thenDel3_btn->setGeometry(THEN_DEL_BTN_X1,310,31,21);
        break;
    case TC_CustomMessage:
        ui->then3_stackedWidget->setCurrentIndex(TSW_CustomMessage);
        ui->thenDel3_btn->setGeometry(THEN_DEL_BTN_X3,310,31,21);
        break;
    case TC_ALARM:
        ui->then3_stackedWidget->setCurrentIndex(TSW_Empty);
        ui->thenDel3_btn->setGeometry(THEN_DEL_BTN_X1,310,31,21);
        break;
    case TC_Output1:
        ui->then3_stackedWidget->setCurrentIndex(TSW_Output);
        ui->thenDel3_btn->setGeometry(THEN_DEL_BTN_X2,310,31,21);
        ui->level3_cbx->setCurrentIndex(-1);
        ui->level3_cbx->setCurrentIndex(0);

        insertThenCbxMsg(1);
        insertThenCbxMsg(2);

        ui->level3_cbx->removeItem(ui->level3_cbx->findData(OP_FollowInput));
        if((ui->if_cbx->currentData().toInt() == IC_Input1 /*|| ui->if_cbx->currentData().toInt() == IC_Input2*/) &&  ui->inputLevel_cbx->currentData() == INC_ChangeState){
            ui->level3_cbx->addItem(tr("will follow the input to change"),OP_FollowInput);
        }
        break;
    case TC_Output2:
        ui->then3_stackedWidget->setCurrentIndex(TSW_Output);
        ui->thenDel3_btn->setGeometry(THEN_DEL_BTN_X2,310,31,21);
        ui->level3_cbx->setCurrentIndex(-1);
        ui->level3_cbx->setCurrentIndex(0);

        insertThenCbxMsg(1);
        insertThenCbxMsg(2);

        ui->level3_cbx->removeItem(ui->level3_cbx->findData(OP_FollowInput));
        if((/*ui->if_cbx->currentData().toInt() == IC_Input1 ||*/ ui->if_cbx->currentData().toInt() == IC_Input2) &&  ui->inputLevel_cbx->currentData() == INC_ChangeState){
            ui->level3_cbx->addItem(tr("will follow the input to change"),OP_FollowInput);
        }
        break;
    case TC_DevRestart:
        ui->then3_stackedWidget->setCurrentIndex(TSW_Empty);
        ui->thenDel3_btn->setGeometry(THEN_DEL_BTN_X1,310,31,21);

        insertThenCbxMsg(1);
        insertThenCbxMsg(2);

        break;
    default:
        break;
    }

    connect(ui->then1_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then1_cbx_currentIndexChanged(int)));
    connect(ui->then2_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then2_cbx_currentIndexChanged(int)));
    connect(ui->then3_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then3_cbx_currentIndexChanged(int)));
}

/**
 * 电平不同选择
 * @brief UCXX52Model::on_level1_cbx_currentIndexChanged
 * @param index
 */
void UCXX52Model::on_level1_cbx_currentIndexChanged(int index)
{
    switch (index) {
    case UCXX52DealThread::OP_GoseHigh:
        ui->delayTime1_frame->setVisible(true);
        ui->highLevel1_frame->setVisible(false);
        ui->lowLevel1_frame->setVisible(false);
        ui->duration1_frame->setVisible(true);
        ui->durationWaveform1_frame->setVisible(false);
        break;
    case UCXX52DealThread::OP_GoseLow:
        ui->delayTime1_frame->setVisible(true);
        ui->highLevel1_frame->setVisible(false);
        ui->lowLevel1_frame->setVisible(false);
        ui->duration1_frame->setVisible(true);
        ui->durationWaveform1_frame->setVisible(false);
        break;
    case UCXX52DealThread::OP_ChangeState:
        ui->delayTime1_frame->setVisible(false);
        ui->highLevel1_frame->setVisible(false);
        ui->lowLevel1_frame->setVisible(false);
        ui->duration1_frame->setVisible(false);
        ui->durationWaveform1_frame->setVisible(false);
        break;
#if OUTPUT_WAVEFORM
    case UCXX52DealThread::OP_Waveform:
        ui->delayTime1_frame->setVisible(true);
        ui->highLevel1_frame->setVisible(true);
        ui->lowLevel1_frame->setVisible(true);
        ui->duration1_frame->setVisible(false);
        ui->durationWaveform1_frame->setVisible(true);
        break;
#endif
    case UCXX52DealThread::OP_FollowInput:
        ui->delayTime1_frame->setVisible(false);
        ui->highLevel1_frame->setVisible(false);
        ui->lowLevel1_frame->setVisible(false);
        ui->duration1_frame->setVisible(false);
        ui->durationWaveform1_frame->setVisible(false);
        break;
    default:
        break;
    }
}

void UCXX52Model::on_level2_cbx_currentIndexChanged(int index)
{
    switch (index) {
    case UCXX52DealThread::OP_GoseHigh:
        ui->delayTime2_frame->setVisible(true);
        ui->highLevel2_frame->setVisible(false);
        ui->lowLevel2_frame->setVisible(false);
        ui->duration2_frame->setVisible(true);
        ui->durationWaveform2_frame->setVisible(false);
        break;
    case UCXX52DealThread::OP_GoseLow:
        ui->delayTime2_frame->setVisible(true);
        ui->highLevel2_frame->setVisible(false);
        ui->lowLevel2_frame->setVisible(false);
        ui->duration2_frame->setVisible(true);
        ui->durationWaveform2_frame->setVisible(false);
        break;
    case UCXX52DealThread::OP_ChangeState:
        ui->delayTime2_frame->setVisible(false);
        ui->highLevel2_frame->setVisible(false);
        ui->lowLevel2_frame->setVisible(false);
        ui->duration2_frame->setVisible(false);
        ui->durationWaveform2_frame->setVisible(false);
        break;
#if OUTPUT_WAVEFORM
    case UCXX52DealThread::OP_Waveform:
        ui->delayTime2_frame->setVisible(true);
        ui->highLevel2_frame->setVisible(true);
        ui->lowLevel2_frame->setVisible(true);
        ui->duration2_frame->setVisible(false);
        ui->durationWaveform2_frame->setVisible(true);
        break;
#endif
    case UCXX52DealThread::OP_FollowInput:
        ui->delayTime2_frame->setVisible(false);
        ui->highLevel2_frame->setVisible(false);
        ui->lowLevel2_frame->setVisible(false);
        ui->duration2_frame->setVisible(false);
        ui->durationWaveform2_frame->setVisible(false);
    break;
    default:
        break;
    }
}

void UCXX52Model::on_level3_cbx_currentIndexChanged(int index)
{
    switch (index) {
    case UCXX52DealThread::OP_GoseHigh:
        ui->delayTime3_frame->setVisible(true);
        ui->highLevel3_frame->setVisible(false);
        ui->lowLevel3_frame->setVisible(false);
        ui->duration3_frame->setVisible(true);
        ui->durationWaveform3_frame->setVisible(false);
        break;
    case UCXX52DealThread::OP_GoseLow:
        ui->delayTime3_frame->setVisible(true);
        ui->highLevel3_frame->setVisible(false);
        ui->lowLevel3_frame->setVisible(false);
        ui->duration3_frame->setVisible(true);
        ui->durationWaveform3_frame->setVisible(false);
        break;
    case UCXX52DealThread::OP_ChangeState:
        ui->delayTime3_frame->setVisible(false);
        ui->highLevel3_frame->setVisible(false);
        ui->lowLevel3_frame->setVisible(false);
        ui->duration3_frame->setVisible(false);
        ui->durationWaveform3_frame->setVisible(false);
        break;
#if OUTPUT_WAVEFORM
    case UCXX52DealThread::OP_Waveform:
        ui->delayTime3_frame->setVisible(true);
        ui->highLevel3_frame->setVisible(true);
        ui->lowLevel3_frame->setVisible(true);
        ui->duration3_frame->setVisible(false);
        ui->durationWaveform3_frame->setVisible(true);
        break;
#endif
    case UCXX52DealThread::OP_FollowInput:
        ui->delayTime3_frame->setVisible(false);
        ui->highLevel3_frame->setVisible(false);
        ui->lowLevel3_frame->setVisible(false);
        ui->duration3_frame->setVisible(false);
        ui->durationWaveform3_frame->setVisible(false);
    break; default:
        break;
    }
}


void UCXX52Model::on_analogStatus_cbx_currentIndexChanged(int index)
{
    switch (index) {
    case QunpUCXX52::UNXX_AI_ABOVE:{
        ui->above_frame->setVisible(true);
        ui->with_frame->setVisible(false);
    }
        break;
    case QunpUCXX52::UNXX_AI_BELOW:{
        ui->above_frame->setVisible(true);
        ui->with_frame->setVisible(false);
    }
        break;
    case QunpUCXX52::UNXX_AI_WITHIN:{
        ui->above_frame->setVisible(false);
        ui->with_frame->setVisible(true);
    }
        break;
    default:
        break;
    }
//    ui->setLockouTimeAnalog_cb->setChecked(true);
}

void UCXX52Model::on_modbusStatus_cbx_currentIndexChanged(int index)
{
    index = ui->modbusStatus_cbx->currentData().toInt();
    switch (index) {
    case QunpUCXX52::UNXX_MB_FALSE:{
        ui->modbusAbove_frame->setVisible(false);
        ui->modbusWith_frame->setVisible(false);
    }
        break;
    case QunpUCXX52::UNXX_MB_TRUE:{
        ui->modbusAbove_frame->setVisible(false);
        ui->modbusWith_frame->setVisible(false);
    }
        break;
    case QunpUCXX52::UNXX_MB_ABOVE:{
        ui->modbusAbove_frame->setVisible(true);
        ui->modbusWith_frame->setVisible(false);
    }
        break;
    case QunpUCXX52::UNXX_MB_BELOW:{
        ui->modbusAbove_frame->setVisible(true);
        ui->modbusWith_frame->setVisible(false);
    }
        break;
    case QunpUCXX52::UNXX_MB_WITHIN:{
        ui->modbusAbove_frame->setVisible(false);
        ui->modbusWith_frame->setVisible(true);
    }
        break;
    default:
        break;
    }
//    ui->setLockouTimeMudbus_cb->setChecked(true);
//    ui->locktimeMudbus_frame->setVisible(true);
}

void UCXX52Model::on_modbusChannelStatus_cbx_currentIndexChanged(int index)
{
    index = ui->modbusChannelStatus_cbx->currentData().toInt();
    for(int i=0; i<modbusChannelTypeList.size(); i++){
//        qDebug()<<modbusChannelNameList.at(i)->text() <<ui->modbusChannelStatus_cbx->currentText();
        if(QString("%1(%2)").arg(modbusChannelNameList.at(i)->text())
                .arg(modbusChannelIdList.at(i)->currentText())
                == ui->modbusChannelStatus_cbx->currentText()){
//            qDebug()<<modbusChannelTypeList.at(i)->currentData().toInt()
//                         <<modbusChannelTypeList.at(i)->currentText()
//                        <<index<<i;
            index = modbusChannelTypeList.at(i)->currentData().toInt();
        }
    }
    ui->modbusStatus_cbx->clear();
    switch (index) {
    case QunpUCXX52::MB_REG_COIL:
        ui->modbusStatus_cbx->addItem("false",QunpUCXX52::UNXX_MB_FALSE);
        ui->modbusStatus_cbx->addItem("true",QunpUCXX52::UNXX_MB_TRUE);
        break;
    case QunpUCXX52::MB_REG_DIS:
        ui->modbusStatus_cbx->addItem("false",QunpUCXX52::UNXX_MB_FALSE);
        ui->modbusStatus_cbx->addItem("true",QunpUCXX52::UNXX_MB_TRUE);
        break;
    case QunpUCXX52::MB_REG_INPUT:
        ui->modbusStatus_cbx->addItem("above",QunpUCXX52::UNXX_MB_ABOVE);
        ui->modbusStatus_cbx->addItem("below",QunpUCXX52::UNXX_MB_BELOW);
        ui->modbusStatus_cbx->addItem("within",QunpUCXX52::UNXX_MB_WITHIN);
        break;
    case QunpUCXX52::MB_REG_INPUT_INT32:
        ui->modbusStatus_cbx->addItem("above",QunpUCXX52::UNXX_MB_ABOVE);
        ui->modbusStatus_cbx->addItem("below",QunpUCXX52::UNXX_MB_BELOW);
        ui->modbusStatus_cbx->addItem("within",QunpUCXX52::UNXX_MB_WITHIN);
        break;
    case QunpUCXX52::MB_REG_INPUT_FLOAT:
        ui->modbusStatus_cbx->addItem("above",QunpUCXX52::UNXX_MB_ABOVE);
        ui->modbusStatus_cbx->addItem("below",QunpUCXX52::UNXX_MB_BELOW);
        ui->modbusStatus_cbx->addItem("within",QunpUCXX52::UNXX_MB_WITHIN);
        break;
    case QunpUCXX52::MB_REG_HOLD_INT16:
        ui->modbusStatus_cbx->addItem("above",QunpUCXX52::UNXX_MB_ABOVE);
        ui->modbusStatus_cbx->addItem("below",QunpUCXX52::UNXX_MB_BELOW);
        ui->modbusStatus_cbx->addItem("within",QunpUCXX52::UNXX_MB_WITHIN);
        break;
    case QunpUCXX52::MB_REG_HOLD_INT32:
        ui->modbusStatus_cbx->addItem("above",QunpUCXX52::UNXX_MB_ABOVE);
        ui->modbusStatus_cbx->addItem("below",QunpUCXX52::UNXX_MB_BELOW);
        ui->modbusStatus_cbx->addItem("within",QunpUCXX52::UNXX_MB_WITHIN);
        break;
    case QunpUCXX52::MB_REG_HOLD_FLOAT:
        ui->modbusStatus_cbx->addItem("above",QunpUCXX52::UNXX_MB_ABOVE);
        ui->modbusStatus_cbx->addItem("below",QunpUCXX52::UNXX_MB_BELOW);
        ui->modbusStatus_cbx->addItem("within",QunpUCXX52::UNXX_MB_WITHIN);
        break;
    case QunpUCXX52::MB_REG_INPUT_INT32_AB:
        ui->modbusStatus_cbx->addItem("above",QunpUCXX52::UNXX_MB_ABOVE);
        ui->modbusStatus_cbx->addItem("below",QunpUCXX52::UNXX_MB_BELOW);
        ui->modbusStatus_cbx->addItem("within",QunpUCXX52::UNXX_MB_WITHIN);
        break;
    case QunpUCXX52::MB_REG_INPUT_INT32_CD:
        ui->modbusStatus_cbx->addItem("above",QunpUCXX52::UNXX_MB_ABOVE);
        ui->modbusStatus_cbx->addItem("below",QunpUCXX52::UNXX_MB_BELOW);
        ui->modbusStatus_cbx->addItem("within",QunpUCXX52::UNXX_MB_WITHIN);
        break;
    case QunpUCXX52::MB_REG_HOLD_INT32_AB:
        ui->modbusStatus_cbx->addItem("above",QunpUCXX52::UNXX_MB_ABOVE);
        ui->modbusStatus_cbx->addItem("below",QunpUCXX52::UNXX_MB_BELOW);
        ui->modbusStatus_cbx->addItem("within",QunpUCXX52::UNXX_MB_WITHIN);
        break;
    case QunpUCXX52::MB_REG_HOLD_INT32_CD:
        ui->modbusStatus_cbx->addItem("above",QunpUCXX52::UNXX_MB_ABOVE);
        ui->modbusStatus_cbx->addItem("below",QunpUCXX52::UNXX_MB_BELOW);
        ui->modbusStatus_cbx->addItem("within",QunpUCXX52::UNXX_MB_WITHIN);
        break;
    default:
        break;
    }
//    qDebug()<< ui->modbusStatus_cbx->itemData(0)<<ui->modbusStatus_cbx->itemData(1)<<ui->modbusStatus_cbx->itemData(2);
}


/**
 * 设置编辑页面保存
 * @brief UCXX52Model::on_settingEditSave_btn_clicked
 */
void UCXX52Model::on_settingEditSave_btn_clicked()
{
    //if
    bool error_input = false;
    bool error_time = false;
    if(ui->lockouttime_lineedit->text().isEmpty() && ui->lockouttime_lineedit->isVisible() && ui->setLockouTime_cb->isChecked()){
        ui->lockouttime_lineedit->setStyleSheet(ERROR_INPUT);
        error_input = true;
    }

#if OUTPUT_WAVEFORM
    QList<QLineEdit *> lineeditWF;
    lineeditWF<<ui->durationWaveform1_lineedit << ui->durationWaveform2_lineedit <<ui->durationWaveform3_lineedit;

    for(int l=0; l<lineeditWF.size(); l++){
        QLineEdit *le = lineedit.at(l);
        if(le->text().trimmed().isEmpty() && le->isVisible()){
            le->setStyleSheet(ERROR_INPUT);
            error_input = true;
        }
        if(le->text().toInt() > 86400000 ){
            le->setStyleSheet(ERROR_INPUT);
            error_time = true;
        }
    }
#endif
    QList<QLineEdit *> lineedit;
    lineedit<<ui->continuedSec_lineedit<<ui->lockouttime_lineedit<<ui->continuedSecAnalog_lineedit<<ui->lockouttimeAnalog_lineedit<<ui->continuedSecMudbus_lineedit<<ui->lockouttimeMudbus_lineedit
            <<ui->delayTimeSec1_lineedit<<ui->highLevelSec1_lineedit<<ui->durationSec1_lineedit<<ui->lowLevelSec1_lineedit
            <<ui->delayTimeSec2_lineedit<<ui->highLevelSec2_lineedit<<ui->durationSec2_lineedit<<ui->lowLevelSec2_lineedit
            <<ui->delayTimeSec3_lineedit<<ui->highLevelSec3_lineedit<<ui->durationSec3_lineedit<<ui->lowLevelSec3_lineedit;

    QList<QComboBox *> timeCbx ;
    timeCbx<<ui->continueTime_cbx<<ui->setLockoutTime_cbx<<ui->continueTimeAnalog_cbx<<ui->setLockoutTime_cbx<<ui->continueTimeMudbus_cbx<<ui->setLockoutTimeMudbus_cbx
           <<ui->delayTimeSec1_cbx<<ui->durationSec1_cbx<<ui->highLevelSec1_cbx<<ui->lowLevelSec1_cbx
           <<ui->delayTimeSec2_cbx<<ui->durationSec2_cbx<<ui->highLevelSec2_cbx<<ui->lowLevelSec2_cbx
           <<ui->delayTimeSec3_cbx<<ui->durationSec3_cbx<<ui->highLevelSec3_cbx<<ui->lowLevelSec3_cbx;

    for(int l=0; l<lineedit.size(); l++){
        QLineEdit *le = lineedit.at(l);
        if(!le->isVisible()){
            continue;
        }
        if(le->text().trimmed().isEmpty() && le->isVisible()){
            le->setStyleSheet(ERROR_INPUT);
            error_input = true;
        }
        for(int t=0; t<timeCbx.size(); t++){
            QComboBox *tc = timeCbx.at(t);
            if(l==t){
                if(tc->currentText() == "ms"){
                    if(le->text().toInt() > 86400000 ){
                        le->setStyleSheet(ERROR_INPUT);
                        error_time = true;
                    }
                }else if(tc->currentText() == "s"){
                    if(le->text().toInt() > 86400 ){
                        le->setStyleSheet(ERROR_INPUT);
                        error_time = true;
                    }
                }else if(tc->currentText() == "min"){
                    if(le->text().toInt() > 1440 ){
                        le->setStyleSheet(ERROR_INPUT);
                        error_time = true;
                    }
                }
            }
        }
    }
#if 0
    float aiMix=0.00;
    float aiMax=0.00;
    if(ui->if_cbx->currentData().toInt() == IC_Analog1){
        if(osh1.toFloat() == 0.00 && osl1.toFloat() == 0.00){
            aiMax = 20.00;
            aiMix = 4.00;
        }else{
            aiMax = osh1.toFloat();
            aiMix = osl1.toFloat();
        }
    }else if(ui->if_cbx->currentData().toInt() == IC_Analog2){
        if(osh2.toFloat() == 0.00 && osl2.toFloat() == 0.00){
            aiMax = 20.00;
            aiMix = 4.00;
        }else{
            aiMax = osh2.toFloat();
            aiMix = osl2.toFloat();
        }
    }

    if(ui->analogStatus_cbx->currentIndex() == QunpUCXX52::UNXX_AI_ABOVE && ui->analogStatus_cbx->isVisible()){
        if(ui->aboveMa_lineedit->text().toFloat() <aiMix ||ui->aboveMa_lineedit->text().toFloat() > aiMax ){
            ui->aboveMa_lineedit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Invalid value."));

            return;
        }
    }

    if(ui->analogStatus_cbx->currentIndex() == QunpUCXX52::UNXX_AI_BELOW && ui->analogStatus_cbx->isVisible()){
        if(ui->aboveMa_lineedit->text().toFloat() <aiMix ||ui->aboveMa_lineedit->text().toFloat() > aiMax ){
            ui->aboveMa_lineedit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Invalid value."));

            return;
        }
    }

    if(ui->analogStatus_cbx->currentIndex() == QunpUCXX52::UNXX_AI_WITHIN && ui->analogStatus_cbx->isVisible()){
        if((ui->withMa1_lineedit->text().toFloat() - ui->withMa2_lineedit->text().toFloat()) >= 0){
            ui->withMa1_lineedit->setStyleSheet(ERROR_INPUT);
            ui->withMa2_lineedit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Invalid value."));

            return;
        }
        if(ui->withMa1_lineedit->text().toFloat() < aiMix || ui->withMa2_lineedit->text().toFloat() > aiMax ){
            ui->withMa1_lineedit->setStyleSheet(ERROR_INPUT);
            ui->withMa2_lineedit->setStyleSheet(ERROR_INPUT);
            showWarning(this,tr("Attention"),tr("Invalid value."));

            return;
        }
    }
#endif
    if(error_time){
        showWarning(this,tr("Attention"),tr("Invalid value. Please try again."));

        return;
    }

    QList<QTextEdit*> textedit;
    textedit<<ui->ifContain_textedit<<ui->thenContent1_textedit<<ui->thenContent2_textedit<<ui->thenContent3_textedit;
    foreach (QTextEdit *t, textedit) {
        if(t->toPlainText().isEmpty() && t->isVisible()){
            t->setStyleSheet(ERROR_INPUT);
            error_input = true;
        }
    }
    if(error_input){
        return;
    }

    if(ui->modbusChannelStatus_cbx->currentText().isEmpty() && ui->modbusChannelStatus_cbx->isVisible()){
        showWarning(this,tr("Attention"),tr("Please add channels."));

        return;
    }

    QVariantMap map;
    QString configuration;
    if((ui->if_cbx->currentData().toInt() != IC_Empty) && (ui->then1_cbx->currentIndex() != TC_Empty)){
        QVariantMap ifmap;
        QVariantMap then1map;
        QVariantMap then2map;
        QVariantMap then3map;
        QVariantMap outputmap;

        QString ifConfig = ui->if_cbx->currentText().trimmed() + " ";
        ifmap.insert("index",ui->if_cbx->currentData().toInt());
        if(ui->if_cbx->currentData().toInt() == IC_Time){
            ifmap.insert("timeisDay",ui->timeisDay_cbx->currentIndex());
            ifmap.insert("timeisTime",ui->timeisTime_tde->text());
            ifConfig = ifConfig+" is "+ ui->timeisDay_cbx->currentText() +" at "+ ui->timeisTime_tde->text().trimmed();
        }else if(ui->if_cbx->currentData().toInt() == IC_PSQ){
            ifConfig = tr("the signal is weak");
        }else if(ui->if_cbx->currentData().toInt() == IC_MsgRecv){
            ifConfig = tr("a message is received");
            ifmap.insert("ussd",ui->ifContain_textedit->toPlainText());
        }else if(ui->if_cbx->currentData().toInt() == IC_DevRestars){

        }else if(ui->if_cbx->currentData().toInt() == IC_Analog1 || ui->if_cbx->currentData().toInt() == IC_Analog2){

            ifmap.insert("continueForSecAnalog",ui->continuedSecAnalog_lineedit->text().toFloat() * ui->continueTimeAnalog_cbx->currentData().toInt());
            if(ui->analogStatus_cbx->currentIndex() == QunpUCXX52::UNXX_AI_ABOVE){
                ifmap.insert("analogStatus",QunpUCXX52::UNXX_AI_ABOVE);
                ifmap.insert("aboveValue",thresholdToMa(ui->aboveMa_lineedit->text().trimmed(),ui->if_cbx->currentData().toInt()));
            }else if(ui->analogStatus_cbx->currentIndex() == QunpUCXX52::UNXX_AI_BELOW){
                ifmap.insert("analogStatus",QunpUCXX52::UNXX_AI_BELOW);
                ifmap.insert("belowValue",thresholdToMa(ui->aboveMa_lineedit->text().trimmed(),ui->if_cbx->currentData().toInt()));
            }else if(ui->analogStatus_cbx->currentIndex() == QunpUCXX52::UNXX_AI_WITHIN){
                ifmap.insert("analogStatus",QunpUCXX52::UNXX_AI_WITHIN);
                ifmap.insert("belowValue",thresholdToMa(ui->withMa1_lineedit->text().trimmed(),ui->if_cbx->currentData().toInt()));
                ifmap.insert("aboveValue",thresholdToMa(ui->withMa2_lineedit->text().trimmed(),ui->if_cbx->currentData().toInt()));
            }
            if(ui->analogStatus_cbx->currentIndex() != QunpUCXX52::UNXX_AI_WITHIN){
                ifConfig = tr("the value of the ")+ ifConfig + ui->analogStatus_cbx->itemText(ifmap.value("analogStatus").toInt())+" "+
                        ui->aboveMa_lineedit->text().trimmed();
            }else {
                ifConfig = tr("the value of the ")+ ifConfig + ui->analogStatus_cbx->itemText(ifmap.value("analogStatus").toInt())+" "+
                        ui->withMa1_lineedit->text().trimmed() + " to "+ui->withMa2_lineedit->text().trimmed()+" ";
            }
            ifmap.insert("inputContinueAnalogUnit",ui->continueTimeAnalog_cbx->currentIndex());
            ifmap.insert("locktimeA.nalogUnit",ui->setLockoutTimeAnalog_cbx->currentIndex());

            ifConfig = ifConfig + QString(" for longer than %2%3")
                    .arg(ui->continuedSecAnalog_lineedit->text().toInt())
                    .arg(ui->continueTimeAnalog_cbx->currentText());

        }else if(ui->if_cbx->currentData().toInt() == IC_CHANNEL){
            ifmap.insert("modbusChannelStatus",ui->modbusChannelStatus_cbx->currentData().toInt());
            ifmap.insert("continueForSecMudbus",ui->continuedSecMudbus_lineedit->text().toFloat() * ui->continueTimeMudbus_cbx->currentData().toInt());
            ifmap.insert("modbusStatus",ui->modbusStatus_cbx->currentData().toInt());

            if(ui->modbusStatus_cbx->currentData() == QunpUCXX52::UNXX_MB_ABOVE){
                ifmap.insert("aboveValue",(ui->modbusAboveMa_lineedit->text().trimmed()));
            }else if(ui->modbusStatus_cbx->currentData() == QunpUCXX52::UNXX_MB_BELOW){
                ifmap.insert("belowValue",(ui->modbusAboveMa_lineedit->text().trimmed()));
            }else if(ui->modbusStatus_cbx->currentData() == QunpUCXX52::UNXX_MB_WITHIN){
                ifmap.insert("belowValue",(ui->modbusWithMa1_lineedit->text().trimmed()));
                ifmap.insert("aboveValue",(ui->modbusWithMa2_lineedit->text().trimmed()));
            }

    qDebug()<<ui->modbusStatus_cbx->currentData()<<ifmap.value("modbusStatus").toInt()<<ifmap.value("modbusChannelStatus").toInt();
            if(ui->modbusStatus_cbx->currentData() == QunpUCXX52::UNXX_MB_WITHIN){
                ifConfig = tr("the value of ")+ ui->modbusChannelStatus_cbx->currentText() +" is between "+
                        ui->modbusWithMa1_lineedit->text().trimmed() + " and "+ui->modbusWithMa2_lineedit->text().trimmed()+" ";
            }else if(ui->modbusStatus_cbx->currentData() == QunpUCXX52::UNXX_MB_FALSE){
                ifConfig = tr("the value of ")+ ui->modbusChannelStatus_cbx->currentText() +" is false ";
            }else if(ui->modbusStatus_cbx->currentData() == QunpUCXX52::UNXX_MB_TRUE){
                ifConfig = tr("the value of ")+ ui->modbusChannelStatus_cbx->currentText() +" is true ";
            }else if(ui->modbusStatus_cbx->currentData() == QunpUCXX52::UNXX_MB_ABOVE){
                ifConfig = tr("the value of ")+ ui->modbusChannelStatus_cbx->currentText() +" is above "+
                        ui->modbusAboveMa_lineedit->text().trimmed();
            }else if(ui->modbusStatus_cbx->currentData() == QunpUCXX52::UNXX_MB_BELOW){
                ifConfig = tr("the value of ")+ ui->modbusChannelStatus_cbx->currentText() +" is below "+
                        ui->modbusAboveMa_lineedit->text().trimmed();
            }
            ifmap.insert("inputContinueMudbusUnit",ui->continueTimeMudbus_cbx->currentIndex());
            ifmap.insert("locktimeMudbusUnit",ui->setLockoutTimeMudbus_cbx->currentIndex());

            ifConfig = ifConfig + QString(" continuing for %2%3")
                    .arg(ui->continuedSecMudbus_lineedit->text().toInt())
                    .arg(ui->continueTimeMudbus_cbx->currentText());
        }else if(ui->if_cbx->currentData().toInt() == IC_Counter1 || ui->if_cbx->currentData().toInt() == IC_Counter2){
            ifConfig = tr("counter%1 >= %2").arg(ui->if_cbx->currentData().toInt() == IC_Counter1 ? "1":"2").arg(ui->counterNum_lineedit->text());
            ifmap.insert("counterNum",ui->counterNum_lineedit->text());
            ifmap.insert("counter",ui->if_cbx->currentData().toInt() == IC_Counter1 ? 1:2);
        }else {
            ifConfig = ifConfig + ui->inputLevel_cbx->currentText().trimmed();
            if( ui->continuedSec_lineedit->isVisible() && (ui->continuedSec_lineedit->text().toInt()!=0) ){
                ifmap.insert("continueForSec",ui->continuedSec_lineedit->text().toFloat() * ui->continueTime_cbx->currentData().toInt());
                ifmap.insert("inputLevel",ui->inputLevel_cbx->currentData());
                ifConfig = ifConfig + QString("and remaining %1 for longer then %2%3")
                        .arg(ui->inputLevel_cbx->currentText().contains("active")?"active":"inactive")
                        .arg(ui->continuedSec_lineedit->text().trimmed())
                        .arg(ui->continueTime_cbx->currentText());
            }else{
                ifmap.insert("inputLevel",ui->inputLevel_cbx->currentData());
                ifmap.insert("continueForSec",0);
            }
            ifmap.insert("inputContinueUnit",ui->continueTime_cbx->currentIndex());
            ifmap.insert("locktimeUnit",ui->setLockoutTime_cbx->currentIndex());
        }

        QString then1Config = ui->then1_cbx->currentText().trimmed()+ " ";
        then1map.insert("index",ui->then1_cbx->currentData().toInt());
        then1map.insert("level",ui->level1_cbx->currentIndex());
        then1map.insert("delay",ui->delayTimeSec1_lineedit->isVisible()?ui->delayTimeSec1_lineedit->text().toFloat() * ui->delayTimeSec1_cbx->currentData().toInt():Empty_Time);
        then1map.insert("durationWF",ui->durationWaveform1_lineedit->isVisible()?ui->durationWaveform1_lineedit->text().toInt():Empty_Time);
        then1map.insert("duration",ui->durationSec1_lineedit->isVisible()?ui->durationSec1_lineedit->text().toFloat() * ui->durationSec1_cbx->currentData().toInt():Empty_Time);
        then1map.insert("high",ui->highLevelSec1_lineedit->isVisible()?ui->highLevelSec1_lineedit->text().toFloat() * ui->highLevelSec1_cbx->currentData().toInt():Empty_Time);
        then1map.insert("low",ui->lowLevelSec1_lineedit->isVisible()?ui->lowLevelSec1_lineedit->text().toFloat() * ui->lowLevelSec1_cbx->currentData().toInt():Empty_Time);
//        then1map.insert("outputDelayUnit",ui->delayTimeSec1_cbx->currentIndex());
//        then1map.insert("durationUnit",ui->durationSec1_cbx->currentIndex());

        switch (ui->then1_cbx->currentData().toInt()) {
        case TC_StatusMessage:
            break;
        case TC_CustomMessage:
            then1map.insert("ussd",ui->thenContent1_textedit->toPlainText());
            break;
        case TC_Output1:
            qDebug()<<ui->delayTimeSec1_lineedit->text().toInt()<<ui->delayTimeSec1_lineedit->text().toFloat()<<ui->delayTimeSec1_lineedit->text().toFloat()*1000;
            then1Config = then1Config + ui->level1_cbx->currentData().toString()+
                    ((ui->durationWaveform1_lineedit->isVisible()&& (ui->durationWaveform1_lineedit->text().toFloat()!=0)) ? (ui->durationWaveform1_lineedit->text().trimmed()+" "):"")+
                    ((ui->delayTimeSec1_lineedit->isVisible()    && (ui->delayTimeSec1_lineedit->text().toFloat()    !=0)) ? (" in "+ui->delayTimeSec1_lineedit->text().trimmed()+ui->delayTimeSec1_cbx->currentText()+" "):"")+
                    ((ui->durationSec1_lineedit->isVisible()     && (ui->durationSec1_lineedit->text().toFloat()     !=0)) ? ("and it will last for "+ui->durationSec1_lineedit->text().trimmed()+ui->durationSec1_cbx->currentText()+" "):" ")+
                    ((ui->highLevelSec1_lineedit->isVisible()    && (ui->highLevelSec1_lineedit->text().toFloat()    !=0)) ? ("with activate "+ui->highLevelSec1_lineedit->text().trimmed()+ui->highLevelSec1_cbx->currentText()+" "):" ")+
                    ((ui->lowLevelSec1_lineedit->isVisible()     && (ui->lowLevelSec1_lineedit->text().toFloat()     !=0)) ? ("and de-activate "+ui->lowLevelSec1_lineedit->text().trimmed()+ui->lowLevelSec1_cbx->currentText()+" "):" ");
            outputmap.insert("outputDelayUnit1",ui->delayTimeSec1_cbx->currentIndex());
            outputmap.insert("durationUnit1", ui->durationSec1_cbx->currentIndex());
            break;
        case TC_Output2:
            then1Config = then1Config + ui->level1_cbx->currentData().toString()+
                    ((ui->durationWaveform1_lineedit->isVisible()&& (ui->durationWaveform1_lineedit->text().toFloat()!=0)) ? (ui->durationWaveform1_lineedit->text().trimmed()+" "):"")+
                    ((ui->delayTimeSec1_lineedit->isVisible()    && (ui->delayTimeSec1_lineedit->text().toFloat()    !=0)) ? (" in "+ui->delayTimeSec1_lineedit->text().trimmed()+ui->delayTimeSec1_cbx->currentText()+" "):"")+
                    ((ui->durationSec1_lineedit->isVisible()     && (ui->durationSec1_lineedit->text().toFloat()     !=0)) ? ("and it will last for "+ui->durationSec1_lineedit->text().trimmed()+ui->durationSec1_cbx->currentText()+" "):" ")+
                    ((ui->highLevelSec1_lineedit->isVisible()    && (ui->highLevelSec1_lineedit->text().toFloat()    !=0)) ? ("with activate "+ui->highLevelSec1_lineedit->text().trimmed()+ui->highLevelSec1_cbx->currentText()+" "):" ")+
                    ((ui->lowLevelSec1_lineedit->isVisible()     && (ui->lowLevelSec1_lineedit->text().toFloat()     !=0)) ? ("and de-activate "+ui->lowLevelSec1_lineedit->text().trimmed()+ui->lowLevelSec1_cbx->currentText()+" "):" ");
            outputmap.insert("outputDelayUnit2",ui->delayTimeSec1_cbx->currentIndex());
            outputmap.insert("durationUnit2",ui->durationSec1_cbx->currentIndex());
            break;
        default:
            break;
        }
        configuration = QString("If %1,\nthen %2").arg(ifConfig.trimmed()).arg(then1Config.trimmed());
        then2map.insert("index",ui->then2_cbx->currentData().toInt());
        if(ui->then2_cbx->currentData().toInt() != TC_Empty){
            QString then2Config ;
            if(ui->then2_cbx->currentText().contains("message")){
                then2Config = "And "+ui->then2_cbx->currentText().trimmed()+" ";
            }else{
                then2Config = "And "+ui->then2_cbx->currentText().trimmed()+" ";
            }

            then2map.insert("level",ui->level2_cbx->currentIndex());
            then2map.insert("delay",ui->delayTimeSec2_lineedit->isVisible()?ui->delayTimeSec2_lineedit->text().toFloat() * ui->delayTimeSec2_cbx->currentData().toInt():Empty_Time);
            then2map.insert("durationWF",ui->durationWaveform2_lineedit->isVisible()?ui->durationWaveform2_lineedit->text().toInt() : Empty_Time);
            then2map.insert("duration",ui->durationSec2_lineedit->isVisible()?ui->durationSec2_lineedit->text().toFloat() * ui->durationSec2_cbx->currentData().toInt() : Empty_Time);
            then2map.insert("high",ui->highLevelSec2_lineedit->isVisible()?ui->highLevelSec2_lineedit->text().toFloat() * ui->highLevelSec2_cbx->currentData().toInt() : Empty_Time);
            then2map.insert("low",ui->lowLevelSec2_lineedit->isVisible()?ui->lowLevelSec2_lineedit->text().toFloat() * ui->lowLevelSec2_cbx->currentData().toInt() : Empty_Time);
//            then2map.insert("outputDelayUnit",ui->delayTimeSec2_cbx->currentIndex());
//            then2map.insert("durationUnit",ui->durationSec2_cbx->currentIndex());

            switch (ui->then2_cbx->currentData().toInt()) {
            case TC_StatusMessage:
                break;
            case TC_CustomMessage:
                then2map.insert("ussd",ui->thenContent2_textedit->toPlainText());
                break;
            case TC_ALARM:
                break;
            case TC_Output1:
                then2Config = then2Config + ui->level2_cbx->currentData().toString()+
                        ((ui->durationWaveform2_lineedit->isVisible()&& (ui->durationWaveform2_lineedit->text().toFloat()!=0)) ? (ui->durationWaveform2_lineedit->text().trimmed()+" "):"")+
                        ((ui->delayTimeSec2_lineedit->isVisible()    && (ui->delayTimeSec2_lineedit->text().toFloat()    !=0)) ? (" in "+ui->delayTimeSec2_lineedit->text().trimmed()+ui->delayTimeSec2_cbx->currentText()+" "):" ")+
                        ((ui->durationSec2_lineedit->isVisible()     && (ui->durationSec2_lineedit->text().toFloat()     !=0)) ? ("and it will last for "+ui->durationSec2_lineedit->text().trimmed()+ui->durationSec2_cbx->currentText()+" "):" ")+
                        ((ui->highLevelSec2_lineedit->isVisible()    && (ui->highLevelSec2_lineedit->text().toFloat()    !=0)) ? ("with activate "+ui->highLevelSec2_lineedit->text().trimmed()+ui->highLevelSec2_cbx->currentText()+" "):" ")+
                        ((ui->lowLevelSec2_lineedit->isVisible()     && (ui->lowLevelSec2_lineedit->text().toFloat()     !=0)) ? ("and de-activate "+ui->lowLevelSec2_lineedit->text().trimmed()+ui->lowLevelSec2_cbx->currentText()+" "):" ");
                outputmap.insert("outputDelayUnit1",ui->delayTimeSec2_cbx->currentIndex());
                outputmap.insert("durationUnit1", ui->durationSec2_cbx->currentIndex());
                break;
            case TC_Output2:
                then2Config = then2Config + ui->level2_cbx->currentData().toString()+
                        ((ui->durationWaveform2_lineedit->isVisible()&& (ui->durationWaveform2_lineedit->text().toFloat()!=0)) ? (ui->durationWaveform2_lineedit->text().trimmed()+" "):"")+
                        ((ui->delayTimeSec2_lineedit->isVisible()    && (ui->delayTimeSec2_lineedit->text().toFloat()    !=0)) ? (" in "+ui->delayTimeSec2_lineedit->text().trimmed()+ui->delayTimeSec2_cbx->currentText()+" "):" ")+
                        ((ui->durationSec2_lineedit->isVisible()     && (ui->durationSec2_lineedit->text().toFloat()     !=0)) ? ("and it will last for "+ui->durationSec2_lineedit->text().trimmed()+ui->durationSec2_cbx->currentText()+" "):" ")+
                        ((ui->highLevelSec2_lineedit->isVisible()    && (ui->highLevelSec2_lineedit->text().toFloat()    !=0)) ? ("with activate "+ui->highLevelSec2_lineedit->text().trimmed()+ui->highLevelSec2_cbx->currentText()+" "):" ")+
                        ((ui->lowLevelSec2_lineedit->isVisible()     && (ui->lowLevelSec2_lineedit->text().toFloat()     !=0)) ? ("and de-activate "+ui->lowLevelSec2_lineedit->text().trimmed()+ui->lowLevelSec2_cbx->currentText()+" "):" ");
                outputmap.insert("outputDelayUnit2",ui->delayTimeSec2_cbx->currentIndex());
                outputmap.insert("durationUnit2",ui->durationSec2_cbx->currentIndex());
                break;
            default:
                break;
            }
            configuration = QString("%1.\n%2").arg(configuration.trimmed()).arg(then2Config.trimmed());
        }
        then3map.insert("index",ui->then3_cbx->currentData().toInt());
        if(ui->then3_cbx->currentData().toInt() != TC_Empty){
            QString then3Config ;
            if(ui->then3_cbx->currentText().contains("message")){
                then3Config = "And "+ui->then3_cbx->currentText().trimmed()+" ";
            }else{
                then3Config = ui->then3_cbx->currentText().trimmed()+" ";
            }

            then3map.insert("level",ui->level3_cbx->currentIndex());
            then3map.insert("delay",ui->delayTimeSec3_lineedit->isVisible()?ui->delayTimeSec3_lineedit->text().toFloat() * ui->delayTimeSec3_cbx->currentData().toInt():Empty_Time);
            then3map.insert("durationWF",ui->durationWaveform3_lineedit->isVisible()?ui->durationWaveform3_lineedit->text().toInt() : Empty_Time);
            then3map.insert("duration",ui->durationSec3_lineedit->isVisible()?ui->durationSec3_lineedit->text().toFloat() * ui->durationSec3_cbx->currentData().toInt() : Empty_Time);
            then3map.insert("high",ui->highLevelSec3_lineedit->isVisible()?ui->highLevelSec3_lineedit->text().toFloat() * ui->highLevelSec3_cbx->currentData().toInt() : Empty_Time);
            then3map.insert("low",ui->lowLevelSec3_lineedit->isVisible()?ui->lowLevelSec3_lineedit->text().toFloat() * ui->lowLevelSec3_cbx->currentData().toInt() : Empty_Time);
//            then3map.insert("outputDelayUnit",ui->delayTimeSec3_cbx->currentIndex());
//            then3map.insert("durationUnit",ui->durationSec3_cbx->currentIndex());

            switch (ui->then3_cbx->currentData().toInt()) {
            case TC_StatusMessage:
                break;
            case TC_CustomMessage:
                then3map.insert("ussd",ui->thenContent3_textedit->toPlainText());
                break;
            case TC_ALARM:
                break;
            case TC_Output1:
                then3Config = then3Config + ui->level3_cbx->currentData().toString()+
                        ((ui->durationWaveform3_lineedit->isVisible()&& (ui->durationWaveform3_lineedit->text().toFloat()!=0)) ? (ui->durationWaveform3_lineedit->text().trimmed()+" "):"")+
                        ((ui->delayTimeSec3_lineedit->isVisible()    && (ui->delayTimeSec3_lineedit->text().toFloat()    !=0)) ? (" in "+ui->delayTimeSec3_lineedit->text().trimmed()+ui->delayTimeSec3_cbx->currentText()+" "):"")+
                        ((ui->durationSec3_lineedit->isVisible()     && (ui->durationSec3_lineedit->text().toFloat()     !=0)) ? ("and it will last for "+ui->durationSec3_lineedit->text().trimmed()+ui->durationSec3_cbx->currentText()+" "):" ")+
                        ((ui->highLevelSec3_lineedit->isVisible()    && (ui->highLevelSec3_lineedit->text().toFloat()    !=0)) ? ("with activate "+ui->highLevelSec3_lineedit->text().trimmed()+ui->highLevelSec3_cbx->currentText()+" "):" ")+
                        ((ui->lowLevelSec3_lineedit->isVisible()     && (ui->lowLevelSec3_lineedit->text().toFloat()     !=0)) ? ("and de-activate "+ui->lowLevelSec3_lineedit->text().trimmed()+ui->lowLevelSec3_cbx->currentText()+" "):" ");
                outputmap.insert("outputDelayUnit1",ui->delayTimeSec3_cbx->currentIndex());
                outputmap.insert("durationUnit1",ui->durationSec3_cbx->currentIndex());
                break;
            case TC_Output2:
                then3Config = then3Config + ui->level3_cbx->currentData().toString()+
                        ((ui->durationWaveform3_lineedit->isVisible()&& (ui->durationWaveform3_lineedit->text().toFloat()!=0)) ? (ui->durationWaveform3_lineedit->text().trimmed()+" "):"")+
                        ((ui->delayTimeSec3_lineedit->isVisible()    && (ui->delayTimeSec3_lineedit->text().toFloat()    !=0)) ? (" in "+ui->delayTimeSec3_lineedit->text().trimmed()+ui->delayTimeSec3_cbx->currentText()+" "):"")+
                        ((ui->durationSec3_lineedit->isVisible()     && (ui->durationSec3_lineedit->text().toFloat()     !=0)) ? ("and it will last for "+ui->durationSec3_lineedit->text().trimmed()+ui->durationSec3_cbx->currentText()+" "):" ")+
                        ((ui->highLevelSec3_lineedit->isVisible()    && (ui->highLevelSec3_lineedit->text().toFloat()    !=0)) ? ("with activate "+ui->highLevelSec3_lineedit->text().trimmed()+ui->highLevelSec3_cbx->currentText()+" "):" ")+
                        ((ui->lowLevelSec3_lineedit->isVisible()     && (ui->lowLevelSec3_lineedit->text().toFloat()     !=0)) ? ("and de-activate "+ui->lowLevelSec3_lineedit->text().trimmed()+ui->lowLevelSec3_cbx->currentText()+" "):" ");
                outputmap.insert("outputDelayUnit2",ui->delayTimeSec3_cbx->currentIndex());
                outputmap.insert("durationUnit2",ui->durationSec3_cbx->currentIndex());
                break;
            default:
                break;
            }
            configuration = QString("%1.\n%2.").arg(configuration.trimmed()).arg(then3Config.trimmed());
        }


        if(ui->setLockouTime_cb->isChecked() && ui->setLockouTime_cb->isVisible()){
            ifmap.insert("setLockTime",ui->lockouttime_lineedit->text().toFloat() * ui->setLockoutTime_cbx->currentData().toInt());
            configuration = QString("%1\n%2").arg(configuration)
                                             .arg(QString("And it will not allowed to trigger again until %1%2 has elapsed.").arg(ui->lockouttime_lineedit->text().trimmed()).arg(ui->setLockoutTime_cbx->currentText()));
        }else if(ui->setLockouTimeAnalog_cb->isChecked() && ui->setLockouTimeAnalog_cb->isVisible()){
            ifmap.insert("setLockTime",ui->lockouttimeAnalog_lineedit->text().toFloat() * ui->setLockoutTimeAnalog_cbx->currentData().toInt());
            configuration = QString("%1\n%2").arg(configuration)
                                             .arg(QString("And it will not allowed to trigger again until %1%2 has elapsed.").arg(ui->lockouttimeAnalog_lineedit->text().trimmed()).arg(ui->setLockoutTimeAnalog_cbx->currentText()));
        }else if(ui->setLockouTimeMudbus_cb->isChecked() && ui->setLockouTimeMudbus_cb->isVisible()){
            ifmap.insert("setLockTime",ui->lockouttimeMudbus_lineedit->text().toFloat() * ui->setLockoutTimeMudbus_cbx->currentData().toInt());
            configuration = QString("%1\n%2").arg(configuration)
                                             .arg(QString("And it will not allowed to trigger again until %1%2 has elapsed.").arg(ui->lockouttimeMudbus_lineedit->text().trimmed()).arg(ui->setLockoutTimeMudbus_cbx->currentText()));
        }else{
            ifmap.insert("setLockTime",Empty_Time);
        }
        //if Weak Signal 不可重复  InputX 的同一个触发条件，保存失败。
        for(int q=0; q<commandList.size(); q++){
            if(q == settingRow)
                continue;
            if(ifmap.value("index").toInt() == IC_PSQ){
                if(commandList.at(q).toMap().value("if_cbx").toMap().value("index").toInt() == IC_PSQ ){
                    showWarning(this,tr("Attention"),tr("You have already created a command with the same trigger condition."));

                    return;
                }
            }
            if(ifmap.value("index").toInt() == IC_Input1){
                if(commandList.at(q).toMap().value("if_cbx").toMap().value("index").toInt() == IC_Input1){
                    if(commandList.at(q).toMap().value("if_cbx").toMap().value("inputLevel").toInt() == ifmap.value("inputLevel").toInt()){
                        showWarning(this,tr("Attention"),tr("You have already created a command with the same trigger condition."));

                        return;
                    }
                }
            }else if(ifmap.value("index").toInt() == IC_Input2){
                if(commandList.at(q).toMap().value("if_cbx").toMap().value("index").toInt() == IC_Input2){
                    if(commandList.at(q).toMap().value("if_cbx").toMap().value("inputLevel").toInt() == ifmap.value("inputLevel").toInt()){
                        showWarning(this,tr("Attention"),tr("You have already created a command with the same trigger condition."));

                        return;
                    }
                }
            }else if(ifmap.value("index").toInt() == IC_In1AndIn2){
                if(commandList.at(q).toMap().value("if_cbx").toMap().value("index").toInt() == IC_In1AndIn2){
                    if(commandList.at(q).toMap().value("if_cbx").toMap().value("inputLevel").toInt() == ifmap.value("inputLevel").toInt()){
                        showWarning(this,tr("Attention"),tr("You have already created a command with the same trigger condition."));

                        return;
                    }
                }
            }else if(ifmap.value("index").toInt() == IC_In1OrIn2){
                if(commandList.at(q).toMap().value("if_cbx").toMap().value("index").toInt() == IC_In1OrIn2){
                    if(commandList.at(q).toMap().value("if_cbx").toMap().value("inputLevel").toInt() == ifmap.value("inputLevel").toInt()){
                        showWarning(this,tr("Attention"),tr("You have already created a command with the same trigger condition."));

                        return;
                    }
                }
            }else if(ifmap.value("index").toInt() == IC_DevRestars){
                if(commandList.at(q).toMap().value("if_cbx").toMap().value("index").toInt() == IC_DevRestars){
                    showWarning(this,tr("Attention"),tr("You have already created a command with the same trigger condition."));

                    return;
                }
            }
        }
        if(((then1map.value("index").toInt() == then2map.value("index").toInt()) && (then1map.value("index").toInt() != 0)) ||
               (then1map.value("index").toInt() == then3map.value("index").toInt() && (then1map.value("index").toInt() != 0)) ||
                (then2map.value("index").toInt() == then3map.value("index").toInt()  && (then2map.value("index").toInt() != 0))){
            showWarning(this,tr("Attention"),tr("Action can not be repeated."));

            return;
        }
        if(ifmap.value("index").toInt() == IC_DevRestars){
            if(then1map.value("index").toInt() == TC_DevRestart ||
               then2map.value("index").toInt() == TC_DevRestart ||
               then3map.value("index").toInt() == TC_DevRestart){
                showWarning(this,tr("Attention"),tr("Failed to save,Improper operation."));

                return;
            }
        }

        model->setData(model->index(settingRow,CONFIGURATION),configuration.toLower().replace("if","If"));


        map.insert("if_cbx",ifmap);
        map.insert("then1_cbx",then1map);
        map.insert("then2_cbx",then2map);
        map.insert("then3_cbx",then3map);
        map.insert("outputmap",outputmap);
        map.insert("saveToDev",true);
        map.insert("isOnlyUcp",false);
        commandList.replace(settingRow,map);
    }

    onTimeCbxChanged(settingRow);
    initThenCbx();
    ui->inputLevel_cbx->clear();
    ui->inputLevel_cbx->addItem(tr("goes active (rising edge-triggered)"),INC_GoseActive);
    ui->inputLevel_cbx->addItem(tr("goes inactive (falling edge-triggered)"),INC_GoseInactive);
    ui->inputLevel_cbx->addItem(tr("changes state(trigger on rising or falling edge)"),INC_ChangeState);
    ui->inputLevel_cbx->addItem(tr("is active (high level triggered)"),INC_IsActive);
    ui->inputLevel_cbx->addItem(tr("is inactive (low level triggered)"),INC_IsInactive);
    ui->stackedWidget->setCurrentIndex(UCXX52DealThread::PAGE_SETTING);

}

/**
 * 编辑页面点击取消
 * @brief UCXX52Model::on_settingEditCancel_btn_clicked
 */
void UCXX52Model::on_settingEditCancel_btn_clicked()
{
    initThenCbx();
    ui->stackedWidget->setCurrentIndex(UCXX52DealThread::PAGE_SETTING);
}

/**
 * 配置表格命令
 * @brief UCXX52Model::configCommandTableview
 */
void UCXX52Model::configCommandTableview(QVariantList command_list)
{
    for(int row=0; row<command_list.size(); row++){
        QVariantMap ifmap = command_list.at(row).toMap().value("if_cbx").toMap();
        QVariantMap outputtimemap = command_list.at(row).toMap().value("outputmap").toMap();
        if(ifmap.value("index").toInt() == IC_Empty){
            model->setData(model->index(row,CONFIGURATION),"");
            continue;
        }
        QString configuration;
        qDebug()<<ifmap.value("index").toInt()
        <<ifmap.value("inputContinueUnit").toInt()<<ifmap.value("continueForSec").toString().trimmed();
        QString ifConfig = ui->if_cbx->itemText(ui->if_cbx->findData(ifmap.value("index").toInt())) + " ";
        if(ifmap.value("index").toInt() == IC_Time){
            ifConfig = ifConfig+"is "+ ui->timeisDay_cbx->itemText(ifmap.value("timeisDay").toInt()) +" at "+ ifmap.value("timeisTime").toString();
        }else if(ifmap.value("index").toInt() == IC_PSQ){
        }else if(ifmap.value("index").toInt() == IC_MsgRecv){
        }else if(ifmap.value("index").toInt() == IC_DevRestars){
        }else if(ifmap.value("index").toInt() == IC_Analog1 || ifmap.value("index").toInt() == IC_Analog2){

            if(ifmap.value("analogStatus").toInt() == QunpUCXX52::UNXX_AI_ABOVE){
                ifConfig = tr("the value of the ")+ ifConfig + ui->analogStatus_cbx->itemText(ifmap.value("analogStatus").toInt())+" "+
                        mAtoThreshold(ifmap.value("aboveValue").toString(),ifmap.value("index").toInt());
            }else if(ifmap.value("analogStatus").toInt() == QunpUCXX52::UNXX_AI_WITHIN){
                ifConfig = tr("the value of the ")+ ifConfig + ui->analogStatus_cbx->itemText(ifmap.value("analogStatus").toInt())+" "+
                        mAtoThreshold(ifmap.value("belowValue").toString(),ifmap.value("index").toInt()) + " to "+mAtoThreshold(ifmap.value("aboveValue").toString(),ifmap.value("index").toInt());
            }else if(ifmap.value("analogStatus").toInt() == QunpUCXX52::UNXX_AI_BELOW){
                ifConfig = tr("the value of the ")+ ifConfig + ui->analogStatus_cbx->itemText(ifmap.value("analogStatus").toInt())+" "+
                        mAtoThreshold(ifmap.value("belowValue").toString(),ifmap.value("index").toInt());
            }
            if(ifmap.value("continueForSecAnalog").toInt()!=Empty_Time){
                ifConfig = ifConfig + QString("for longer than %2%3")
                        .arg(ascMsToSec(ifmap.value("continueForSecAnalog").toString().trimmed(),ifmap.value("inputContinueAnalogUnit").toInt()))
                        .arg(ui->continueTimeAnalog_cbx->itemText(ifmap.value("inputContinueAnalogUnit").toInt()));
            }

        }else if(ifmap.value("index").toInt() == IC_CHANNEL ){
            qDebug()<<ifmap.value("modbusStatus").toInt()<<ifmap.value("modbusChannelStatus").toInt();

            if(ifmap.value("modbusStatus").toInt() == QunpUCXX52::UNXX_MB_WITHIN){
                ifConfig = tr("the value of ")+ ui->modbusChannelStatus_cbx->itemText(ui->modbusChannelStatus_cbx->findData(ifmap.value("modbusChannelStatus").toInt())) +" is between "+
                        (ifmap.value("belowValue").toString()) + " and "+(ifmap.value("aboveValue").toString());
            }else if(ifmap.value("modbusStatus").toInt() == QunpUCXX52::UNXX_MB_FALSE){
                ifConfig = tr("the value of ")+ ui->modbusChannelStatus_cbx->itemText(ui->modbusChannelStatus_cbx->findData(ifmap.value("modbusChannelStatus").toInt())) +" is false ";
            }else if(ifmap.value("modbusStatus").toInt() == QunpUCXX52::UNXX_MB_TRUE){
                ifConfig = tr("the value of ")+ ui->modbusChannelStatus_cbx->itemText(ui->modbusChannelStatus_cbx->findData(ifmap.value("modbusChannelStatus").toInt())) +" is true ";
            }else if(ifmap.value("modbusStatus").toInt() == QunpUCXX52::UNXX_MB_ABOVE) {
                ifConfig = tr("the value of ")+ ui->modbusChannelStatus_cbx->itemText(ui->modbusChannelStatus_cbx->findData(ifmap.value("modbusChannelStatus").toInt())) +" is above "+
                        (ifmap.value("aboveValue").toString());
            }else if(ifmap.value("modbusStatus").toInt() == QunpUCXX52::UNXX_MB_BELOW) {
                ifConfig = tr("the value of ")+ ui->modbusChannelStatus_cbx->itemText(ui->modbusChannelStatus_cbx->findData(ifmap.value("modbusChannelStatus").toInt())) +" is below "+
                        (ifmap.value("belowValue").toString());
            }

            if(ifmap.value("continueForSecMudbus").toInt()!=Empty_Time){
                ifConfig = ifConfig + QString(" continuing for %2%3")
                        .arg(ascMsToSec(ifmap.value("continueForSecMudbus").toString().trimmed(),ifmap.value("inputContinueMudbusUnit").toInt()))
                        .arg(ui->continueTimeMudbus_cbx->itemText(ifmap.value("inputContinueMudbusUnit").toInt()));
            }
        }else if(ifmap.value("index").toInt() == IC_Counter1 || ifmap.value("index").toInt() == IC_Counter2){
            ifConfig = ifConfig + ">= " + ifmap.value("counterNum").toString();
        } else {
            ifConfig = ifConfig + ui->inputLevel_cbx->itemText(ifmap.value("inputLevel").toInt()).trimmed();
            if(ifmap.value("continueForSec").toInt()!=Empty_Time){
                ifConfig = ifConfig + QString("and remaining %1 for longer than %2%3")
                        .arg(ui->inputLevel_cbx->itemText(ifmap.value("inputLevel").toInt()).contains("active")?"active":"inactive")
                        .arg(ascMsToSec(ifmap.value("continueForSec").toString().trimmed(), ifmap.value("inputContinueUnit").toInt()))
                        .arg(ui->continueTime_cbx->itemText(ifmap.value("inputContinueUnit").toInt()));
            }
        }

        QVariantMap then1map = command_list.at(row).toMap().value("then1_cbx").toMap();
        QString then1Config = ui->then1_cbx->itemText(ui->then1_cbx->findData(then1map.value("index").toInt()))+ " ";
        qDebug()<<"then1map index"<<then1map.value("index").toInt();
        switch (then1map.value("index").toInt()) {
        case TC_StatusMessage:
            break;
        case TC_CustomMessage:
            break;
        case TC_ALARM:
            break;
        case TC_Output1:{
            QString levelConfing;
            if(then1map.value("level").toInt() == UCXX52DealThread::OP_FollowInput){
                levelConfing = tr("will follow the input to change");
            }else{
                levelConfing = ui->level1_cbx->itemText(ui->level1_cbx->findData(then1map.value("level").toInt()));
                qDebug()<<"############################# "<<ui->level1_cbx->findData(then1map.value("level").toInt())<<then1map.value("level").toInt()<<levelConfing;
            }
            then1Config = then1Config + levelConfing+
                    (then1map.value("durationWF").toInt()!=Empty_Time ? (ascMsToSec(then1map.value("durationWF").toString())+"s "):"")+
                    (then1map.value("delay").toInt()!=Empty_Time?(" in "+ascMsToSec(then1map.value("delay").toString(),outputtimemap.value("outputDelayUnit1").toInt())+ui->delayTimeSec1_cbx->itemText(outputtimemap.value("outputDelayUnit1").toInt())+" "):"")+
                    (then1map.value("duration").toInt()!=Empty_Time ? ("and it will last for "+ascMsToSec(then1map.value("duration").toString(),outputtimemap.value("durationUnit1").toInt())+ui->durationSec1_cbx->itemText(outputtimemap.value("durationUnit1").toInt())+" "):"")+
                    (then1map.value("high").toInt()!=Empty_Time ? ("with activate "+ascMsToSec(then1map.value("high").toString())+"s "):"")+
                    (then1map.value("low").toInt()!=Empty_Time ? ("and de-activate "+ascMsToSec(then1map.value("low").toString())+"s "):"");
        }
            break;
        case TC_Output2:{
            QString levelConfing;
            if(then1map.value("level").toInt() == UCXX52DealThread::OP_FollowInput){
                levelConfing = tr("will follow the input to change");
            }else{
                levelConfing = ui->level1_cbx->itemText(ui->level1_cbx->findData(then1map.value("level").toInt()));
            }
            then1Config = then1Config + levelConfing+
                    (then1map.value("durationWF").toInt()!=Empty_Time?(ascMsToSec(then1map.value("durationWF").toString())+"s "):"")+
                    (then1map.value("delay").toInt()!=Empty_Time?(" in "+ascMsToSec(then1map.value("delay").toString(),outputtimemap.value("outputDelayUnit2").toInt())+ui->delayTimeSec1_cbx->itemText(outputtimemap.value("outputDelayUnit2").toInt())+" "):"")+
                    (then1map.value("duration").toInt()!=Empty_Time ? ("and it will last for "+ascMsToSec(then1map.value("duration").toString(),outputtimemap.value("durationUnit2").toInt())+ui->durationSec1_cbx->itemText(outputtimemap.value("durationUnit2").toInt())+" "):"")+
                    (then1map.value("high").toInt()!=Empty_Time?("with activate "+ascMsToSec(then1map.value("high").toString())+"s "):"")+
                    (then1map.value("low").toInt()!=Empty_Time?("and de-activate "+ascMsToSec(then1map.value("low").toString())+"s "):"");
        }
            break;
        default:
            break;
        }
        configuration = QString("If %1,\nthen %2").arg(ifConfig).arg(then1Config);


        QVariantMap then2map = command_list.at(row).toMap().value("then2_cbx").toMap();
        if(then2map.value("index").toInt() != TC_Empty){
            QString then2Config = ui->then2_cbx->itemText(ui->then2_cbx->findData(then2map.value("index").toInt()))+ " ";
            switch (then2map.value("index").toInt()) {
            case TC_StatusMessage:
                break;
            case TC_CustomMessage:
                break;
            case TC_ALARM:
                break;
            case TC_Output1:{
                QString level2Confing;
                if(then2map.value("level").toInt() == UCXX52DealThread::OP_FollowInput){
                    level2Confing = tr("will follow the input to change");
                }else{
                    level2Confing = ui->level2_cbx->itemData(then2map.value("level").toInt()).toString();
                }
                then2Config = then2Config + level2Confing+
                        (then2map.value("durationWF").toInt()!=Empty_Time?(ascMsToSec(then2map.value("durationWF").toString())+"s "):"")+
                        (then2map.value("delay").toInt()!=Empty_Time?(" in "+ascMsToSec(then2map.value("delay").toString(),outputtimemap.value("outputDelayUnit1").toInt())+ui->delayTimeSec2_cbx->itemText(outputtimemap.value("outputDelayUnit1").toInt())+" "):"")+
                        (then2map.value("duration").toInt()!=Empty_Time?("and it will last for "+ascMsToSec(then2map.value("duration").toString(),outputtimemap.value("durationUnit1").toInt())+ui->durationSec2_cbx->itemText(outputtimemap.value("durationUnit1").toInt())+" "):"")+
                        (then2map.value("high").toInt()!=Empty_Time?("with activate "+ascMsToSec(then2map.value("high").toString())+"s "):"")+
                        (then2map.value("low").toInt()!=Empty_Time?("and de-activate "+ascMsToSec(then2map.value("low").toString())+"s "):"");
            }
                break;
            case TC_Output2:{
                QString level2Confing;
                if(then2map.value("level").toInt() == UCXX52DealThread::OP_FollowInput){
                    level2Confing = tr("will follow the input to change");
                }else{
                    level2Confing = ui->level2_cbx->itemData(then2map.value("level").toInt()).toString();
                }
                then2Config = then2Config + level2Confing+
                        (then2map.value("durationWF").toInt()!=Empty_Time?(ascMsToSec(then2map.value("durationWF").toString())+"s "):"")+
                        (then2map.value("delay").toInt()!=Empty_Time?(" in "+ascMsToSec(then2map.value("delay").toString(),outputtimemap.value("outputDelayUnit2").toInt())+ui->delayTimeSec2_cbx->itemText(outputtimemap.value("outputDelayUnit2").toInt())+" "):"")+
                        (then2map.value("duration").toInt()!=Empty_Time?("and it will last for "+ascMsToSec(then2map.value("duration").toString(),outputtimemap.value("durationUnit2").toInt())+ui->durationSec2_cbx->itemText(outputtimemap.value("durationUnit2").toInt())+" "):"")+
                        (then2map.value("high").toInt()!=Empty_Time?("with activate "+ascMsToSec(then2map.value("high").toString())+"s "):"")+
                        (then2map.value("low").toInt()!=Empty_Time?("and de-activate "+ascMsToSec(then2map.value("low").toString())+"s "):"");
            }
                break;
            default:
                break;
            }
            configuration = QString("%1.\nand %2").arg(configuration.trimmed()).arg(then2Config.trimmed());
        }else{
            ui->then2_stackedWidget->setCurrentIndex(TSW_Empty);
        }

        QVariantMap then3map = command_list.at(row).toMap().value("then3_cbx").toMap();
        if(then3map.value("index").toInt() != TC_Empty){
            QString then3Config = ui->then3_cbx->itemText(ui->then3_cbx->findData(then3map.value("index").toInt()))+ " ";
            switch (then3map.value("index").toInt()) {
            case TC_StatusMessage:
                break;
            case TC_CustomMessage:
                break;
            case TC_ALARM:
                break;
            case TC_Output1:{
                QString level3Confing;
                if(then3map.value("level").toInt() == UCXX52DealThread::OP_FollowInput){
                    level3Confing = tr("will follow the input to change");
                }else{
                    level3Confing = ui->level3_cbx->itemData(then3map.value("level").toInt()).toString();
                }
                then3Config = then3Config + level3Confing+
                        (then3map.value("durationWF").toInt()!=Empty_Time?(ascMsToSec(then3map.value("durationWF").toString())+"s "):"")+
                        (then3map.value("delay").toInt()!=Empty_Time?(" in "+ascMsToSec(then3map.value("delay").toString(),outputtimemap.value("outputDelayUnit1").toInt())+ui->delayTimeSec3_cbx->itemText(outputtimemap.value("outputDelayUnit1").toInt())+" "):"")+
                        (then3map.value("duration").toInt()!=Empty_Time?("and it will last for "+ascMsToSec(then3map.value("duration").toString(),outputtimemap.value("durationUnit1").toInt())+ui->durationSec3_cbx->itemText(outputtimemap.value("durationUnit1").toInt())+" "):"")+
                        (then3map.value("high").toInt()!=Empty_Time?("with activate "+ascMsToSec(then3map.value("high").toString())+"s "):"")+
                        (then3map.value("low").toInt()!=Empty_Time?("and de-activate "+ascMsToSec(then3map.value("low").toString())+"s "):"");
            }
                break;
            case TC_Output2:{
                QString level3Confing;
                if(then3map.value("level").toInt() == UCXX52DealThread::OP_FollowInput){
                    level3Confing = tr("will follow the input to change");
                }else{
                    level3Confing = ui->level3_cbx->itemData(then3map.value("level").toInt()).toString();
                }
                then3Config = then3Config + level3Confing+
                        (then3map.value("durationWF").toInt()!=Empty_Time?(ascMsToSec(then3map.value("durationWF").toString())+"s "):"")+
                        (then3map.value("delay").toInt()!=Empty_Time?(" in "+ascMsToSec(then3map.value("delay").toString(),outputtimemap.value("outputDelayUnit2").toInt())+ui->delayTimeSec3_cbx->itemText(outputtimemap.value("outputDelayUnit2").toInt())+" "):"")+
                        (then3map.value("duration").toInt()!=Empty_Time?("and it will last for "+ascMsToSec(then3map.value("duration").toString(),outputtimemap.value("durationUnit2").toInt())+ui->durationSec3_cbx->itemText(outputtimemap.value("durationUnit2").toInt())+" "):"")+
                        (then3map.value("high").toInt()!=Empty_Time?("with activate "+ascMsToSec(then3map.value("high").toString())+"s "):"")+
                        (then3map.value("low").toInt()!=Empty_Time?("and de-activate "+ascMsToSec(then3map.value("low").toString())+"s "):"");
            }
                break;
            default:
                break;
            }
            configuration = QString("%1.\n%2.").arg(configuration.trimmed()).arg(then3Config.trimmed());
        }else{
            ui->then3_stackedWidget->setCurrentIndex(TSW_Empty);
        }

        if(ifmap.value("continueForSecAnalog").toInt()!=Empty_Time){
            if(ifmap.value("setLockTime").toInt() != Empty_Time){
                configuration = QString("%1\n%2").arg(configuration)
                                                 .arg(QString("And it will not allowed to trigger again until %1%2 has elapsed.")
                                                      .arg(ascMsToSec(ifmap.value("setLockTime").toString(), ifmap.value("locktimeAnalogUnit").toInt()))
                                                      .arg(ui->setLockoutTimeAnalog_cbx->itemText(ifmap.value("locktimeAnalogUnit").toInt())));
            }
        }else{
            if(ifmap.value("setLockTime").toInt() != Empty_Time){
                configuration = QString("%1\n%2").arg(configuration)
                                                 .arg(QString("And it will not allowed to trigger again until %1%2 has elapsed.")
                                                      .arg(ascMsToSec(ifmap.value("setLockTime").toString(), ifmap.value("locktimeUnit").toInt()))
                                                      .arg(ui->setLockoutTime_cbx->itemText(ifmap.value("locktimeUnit").toInt())));
            }
        }

        model->setData(model->index(row,CONFIGURATION),configuration.toLower().replace("if","If"));
    }
}

/**
 * 读取设备配置
 * @brief UCXX52Model::on_readFromDevice_btn_clicked
 */
void UCXX52Model::on_readFromDevice_btn_clicked()
{
    emit requestToDevice(UCXX52DealThread::PAGE_SETTING,QVariantList());
}

/**
 * 读取设备信息 - 槽
 * @brief UCXX52Model::onRecvDeviceCommand
 * @param dev_device_info
 */
void UCXX52Model::onRecvDeviceCommand(QVariantList dev_device_info)
{
    QVariantList tlist;
    for(int i=0; i<dev_device_info.size(); i++){
        QVariantMap ifmap = dev_device_info.at(i).toMap().value("if_cbx").toMap();
        QVariantMap then1map = dev_device_info.at(i).toMap().value("then1_cbx").toMap();
        QVariantMap then2map = dev_device_info.at(i).toMap().value("then2_cbx").toMap();
        QVariantMap then3map = dev_device_info.at(i).toMap().value("then3_cbx").toMap();
        QVariantMap outputmap;

        QSettings settings(m_iniPath, QSettings::IniFormat);
        settings.beginGroup(QString("TimeCbx%1").arg(i));
        ifmap.insert("inputContinueUnit",settings.value("inputContinueUnit").toString());
        ifmap.insert("locktimeUnit",settings.value("locktimeUnit").toString());
        ifmap.insert("inputContinueAnalogUnit",settings.value("inputContinueAnalogUnit").toString());
        ifmap.insert("locktimeAnalogUnit",settings.value("locktimeAnalogUnit").toString());
        ifmap.insert("inputContinueMudbusUnit",settings.value("inputContinueMudbusUnit").toString());
        ifmap.insert("locktimeMudbusUnit",settings.value("locktimeMudbusUnit").toString());

        outputmap.insert("outputDelayUnit1",settings.value("outputDelayUnit1").toString());
        outputmap.insert("durationUnit1",settings.value("durationUnit1").toString());

        outputmap.insert("outputDelayUnit2",settings.value("outputDelayUnit2").toString());
        outputmap.insert("durationUnit2",settings.value("durationUnit2").toString());

        qDebug()<<QString("TimeCbx%1").arg(i)<<settings.value("inputContinueUnit").toString()<<settings.value("locktimeUnit").toString()
             <<settings.value("inputContinueAnalogUnit").toString()<<settings.value("locktimeAnalogUnit").toString()
            <<settings.value("outputDelayUnit1").toString()<<settings.value("durationUnit1").toString()
           <<settings.value("outputDelayUnit2").toString()<<settings.value("durationUnit2").toString();
        settings.endGroup();
        QVariantMap map;
        map.insert("if_cbx",ifmap);
        map.insert("then1_cbx",then1map);
        map.insert("then2_cbx",then2map);
        map.insert("then3_cbx",then3map);
        map.insert("outputmap",outputmap);
        tlist.append(map);
    }

    configCommandTableview(tlist);

    for(int i=0; i<commandList.size(); i++){
        for(int j=0; j<tlist.size(); j++){
            if(i==j){
                QVariantMap map = tlist.at(j).toMap();
                commandList.replace(i,map);
            }
        }
    }
    emit waitingVisible(false);
}

/**
 * 保存配置窗口
 * @brief UCXX52Model::on_saveToFile_btn_clicked
 */
void UCXX52Model::on_saveToFile_btn_clicked()
{
//    m_saveSetupFile->show();
    for(int i=0 ; i<commandList.size(); i++){
        QVariantMap map = commandList.at(i).toMap();
        map.insert("if_cbx",map.value("if_cbx").toMap());
        map.insert("then1_cbx",map.value("then1_cbx").toMap());
        map.insert("then2_cbx",map.value("then2_cbx").toMap());
        map.insert("then3_cbx",map.value("then3_cbx").toMap());
        map.insert("outputmap",map.value("outputmap").toMap());
        map.insert("saveToDev",true);
        map.insert("isOnlyUcp",true);
        commandList.replace(i,map);
    }

    emit requestToDevice(UCXX52DealThread::CONFIG_WRITE_SETTING,commandList);

    QString filename = QFileDialog::getSaveFileName(this,"Save File","./",tr("File (*.txt)"));//获取需要保存成的文件名
    filename.remove(".txt");
    saveSettingCommand(filename);
}

/**
 * 保存配置文件
 * @brief UCXX52Model::saveSettingCommand
 */
void UCXX52Model::saveSettingCommand(QString filename)
{
//    QString saveFile = QApplication::applicationDirPath()+"/command.ini";
    QString smsText = filename+".txt";

    QFile sf(smsText);

    QString _smsTxt;
    for(int m=0; m<smsTxt.split("\n").size()-1; m++){
        QString sms_ = smsTxt.split("\n").at(m);
        QString tmp;
        tmp.append(m_loginPwd).append(";");
        _smsTxt.append(tmp).append(sms_).append("\n");
    }
    if(sf.exists()){
        sf.remove();
    }
    if(sf.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate)){
        QTextStream in(&sf);
        in<<_smsTxt<<"\n";
    }
    sf.close();


    filename = filename +".dat";
    QSettings settings(filename, QSettings::IniFormat);
    QFile *f = new QFile(filename);
    if(f->exists()){
        f->remove();
    }
     f->exists(filename);
     settings.beginWriteArray("If_Action");
     for(int i=0; i<commandList.size(); i++){
         QVariantMap map = commandList.at(i).toMap().value("if_cbx").toMap();
         settings.setArrayIndex(i);
         settings.setValue("index",map.value("index").toString());
         settings.setValue("timeisDay",map.value("timeisDay").toString());
         settings.setValue("timeisTime",map.value("timeisTime").toString());
         settings.setValue("continueForSec",map.value("continueForSec").toString());
         settings.setValue("setLockTime",map.value("setLockTime").toString());
         settings.setValue("ussd",map.value("ussd").toString());
         settings.setValue("continueForSecAnalog",map.value("continueForSecAnalog").toString());
         settings.setValue("analogStatus",map.value("analogStatus").toString());
         settings.setValue("counterNum",map.value("counterNum").toString());


         settings.setValue("continueForSecMudbus",map.value("continueForSecMudbus").toString());
         settings.setValue("modbusStatus",map.value("modbusStatus").toString());
         settings.setValue("modbusChannelStatus",map.value("modbusChannelStatus").toString());

         settings.setValue("aboveValue",map.value("aboveValue").toString());
         settings.setValue("belowValue",map.value("belowValue").toString());

         settings.setValue("inputContinueUnit",map.value("inputContinueUnit").toString());
         settings.setValue("locktimeUnit",map.value("locktimeUnit").toString());
         settings.setValue("inputContinueAnalogUnit",map.value("inputContinueAnalogUnit").toString());
         settings.setValue("locktimeAnalogUnit",map.value("locktimeAnalogUnit").toString());
         settings.setValue("inputContinueMudbusUnit",map.value("inputContinueMudbusUnit").toString());
         settings.setValue("locktimeMudbusUnit",map.value("locktimeMudbusUnit").toString());

     }
     settings.endArray();

     settings.beginWriteArray("Then1_Action");
     for(int i=0; i<commandList.size(); i++){
         QVariantMap map = commandList.at(i).toMap().value("then1_cbx").toMap();
         settings.setArrayIndex(i);
         settings.setValue("index",map.value("index").toString());
         settings.setValue("level",map.value("level").toString());
         settings.setValue("delay",map.value("delay").toString());
         settings.setValue("durationWF",map.value("durationWF").toString());
         settings.setValue("duration",map.value("duration").toString());
         settings.setValue("high",map.value("high").toString());
         settings.setValue("low",map.value("low").toString());
         settings.setValue("ussd",map.value("ussd").toString());
//         settings.setValue("outputDelayUnit",map.value("outputDelayUnit").toString());
//         settings.setValue("durationUnit",map.value("durationUnit").toString());
     }
     settings.endArray();

     settings.beginWriteArray("Then2_Action");
     for(int i=0; i<commandList.size(); i++){
         QVariantMap map = commandList.at(i).toMap().value("then2_cbx").toMap();
         settings.setArrayIndex(i);
         settings.setValue("index",map.value("index").toString());
         settings.setValue("level",map.value("level").toString());
         settings.setValue("delay",map.value("delay").toString());
         settings.setValue("durationWF",map.value("durationWF").toString());
         settings.setValue("duration",map.value("duration").toString());
         settings.setValue("high",map.value("high").toString());
         settings.setValue("low",map.value("low").toString());
         settings.setValue("ussd",map.value("ussd").toString());
//         settings.setValue("outputDelayUnit",map.value("outputDelayUnit").toString());
//         settings.setValue("durationUnit",map.value("durationUnit").toString());
     }
     settings.endArray();

     settings.beginWriteArray("Then3_Action");
     for(int i=0; i<commandList.size(); i++){
         QVariantMap map = commandList.at(i).toMap().value("then3_cbx").toMap();
         settings.setArrayIndex(i);
         settings.setValue("index",map.value("index").toString());
         settings.setValue("level",map.value("level").toString());
         settings.setValue("delay",map.value("delay").toString());
         settings.setValue("durationWF",map.value("durationWF").toString());
         settings.setValue("duration",map.value("duration").toString());
         settings.setValue("high",map.value("high").toString());
         settings.setValue("low",map.value("low").toString());
         settings.setValue("ussd",map.value("ussd").toString());
//         settings.setValue("outputDelayUnits",map.value("outputDelayUnit").toString());
//         settings.setValue("durationUnit",map.value("durationUnit").toString());
     }
     settings.endArray();
     QSettings settings2(m_iniPath, QSettings::IniFormat);

     for(int i=0; i<commandList.size(); i++){
         QVariantMap map = commandList.at(i).toMap().value("outputmap").toMap();
         settings2.beginGroup(QString("TimeCbx%1").arg(i));
         settings2.setValue("outputDelayUnit1",map.value("outputDelayUnit1").toInt());
         settings2.setValue("durationUnit1",map.value("durationUnit1").toInt());
         settings2.setValue("outputDelayUnit2",map.value("outputDelayUnit2").toInt());
         settings2.setValue("durationUnit2",map.value("durationUnit2").toInt());
         settings2.endGroup();
     }


}

/**
 * 从配置文件打开
 * @brief UCXX52Model::on_openFromFile_btn_clicked
 */
void UCXX52Model::on_openFromFile_btn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "./", tr("File (*.dat);; ALL (*.*)"));
    if(fileName.isEmpty()){
        return;
    }
    QSettings settings(fileName,QSettings::IniFormat);
    int size= settings.beginReadArray("If_Action");
    if(size<=0){
        showWarning(this,tr("Attention"),tr("File error "));
        return;
    }

    for(int row=0; row<UNXX_MAX_WORKNUM; row++ ){
        model->setData(model->index(row,CONFIGURATION)," ");

    }
    QVariantMap map;
    QVariantList ifmaplist;
    for(int i=0; i<size; i++){
        QVariantMap ifmap;
        map.clear();
        settings.setArrayIndex(i);
        ifmap.insert("index",settings.value("index").toString());
        ifmap.insert("timeisDay",settings.value("timeisDay").toString());
        ifmap.insert("timeisTime",settings.value("timeisTime").toString());
        ifmap.insert("continueForSec",settings.value("continueForSec").toString());
        ifmap.insert("setLockTime",settings.value("setLockTime").toString());
        ifmap.insert("inputLevel",settings.value("inputLevel").toString());
        ifmap.insert("ussd",settings.value("ussd").toString());
        ifmap.insert("continueForSecAnalog",settings.value("continueForSecAnalog").toString());
        ifmap.insert("analogStatus",settings.value("analogStatus").toString());
        ifmap.insert("counterNum",settings.value("counterNum").toString());

        ifmap.insert("continueForSecMudbus",settings.value("continueForSecMudbus").toString());
        ifmap.insert("modbusStatus",settings.value("modbusStatus").toString());
        ifmap.insert("modbusChannelStatus",settings.value("modbusChannelStatus").toString());

        ifmap.insert("aboveValue",settings.value("aboveValue").toString());
        ifmap.insert("belowValue",settings.value("belowValue").toString());
        ifmap.insert("inputContinueUnit",settings.value("inputContinueUnit").toString());
        ifmap.insert("locktimeUnit",settings.value("locktimeUnit").toString());
        ifmap.insert("inputContinueAnalogUnit",settings.value("inputContinueAnalogUnit").toString());
        ifmap.insert("locktimeAnalogUnit",settings.value("locktimeAnalogUnit").toString());

        ifmap.insert("inputContinueMudbusUnit",settings.value("inputContinueMudbusUnit").toString());
        ifmap.insert("locktimeMudbusUnit",settings.value("locktimeMudbusUnit").toString());
        map.insert("if_cbx",ifmap);
        ifmaplist.append(map);
    }
    settings.endArray();

    settings.beginReadArray("Then1_Action");
    QVariantList then1maplist;
    for(int i=0; i<size; i++){
        QVariantMap then1map;
        map.clear();
        settings.setArrayIndex(i);
        then1map.insert("index",settings.value("index").toString());
        then1map.insert("level",settings.value("level").toString());
        then1map.insert("delay",settings.value("delay").toString());
        then1map.insert("durationWF",settings.value("durationWF").toString());
        then1map.insert("duration",settings.value("duration").toString());
        then1map.insert("high",settings.value("high").toString());
        then1map.insert("low",settings.value("low").toString());
        then1map.insert("ussd",settings.value("ussd").toString());
//        then1map.insert("outputDelayUnit",settings.value("outputDelayUnit").toString());
//        then1map.insert("durationUnit",settings.value("durationUnit").toString());
        map.insert("then1_cbx",then1map);
        then1maplist.append(map);
    }
    settings.endArray();

    settings.beginReadArray("Then2_Action");
    QVariantList then2maplist;
    for(int i=0; i<size; i++){
        QVariantMap then2map;
        map.clear();
        settings.setArrayIndex(i);
        then2map.insert("index",settings.value("index").toString());
        then2map.insert("level",settings.value("level").toString());
        then2map.insert("delay",settings.value("delay").toString());
        then2map.insert("durationWF",settings.value("durationWF").toString());
        then2map.insert("duration",settings.value("duration").toString());
        then2map.insert("high",settings.value("high").toString());
        then2map.insert("low",settings.value("low").toString());
        then2map.insert("ussd",settings.value("ussd").toString());
//        then2map.insert("outputDelayUnit",settings.value("outputDelayUnit").toString());
//        then2map.insert("durationUnit",settings.value("durationUnit").toString());
        map.insert("then2_cbx",then2map);
        then2maplist.append(map);
    }
    settings.endArray();

    settings.beginReadArray("Then3_Action");
    QVariantList then3maplist;
    for(int i=0; i<size; i++){
        QVariantMap then3map;
        map.clear();
        settings.setArrayIndex(i);
        then3map.insert("index",settings.value("index").toString());
        then3map.insert("level",settings.value("level").toString());
        then3map.insert("delay",settings.value("delay").toString());
        then3map.insert("durationWF",settings.value("durationWF").toString());
        then3map.insert("duration",settings.value("duration").toString());
        then3map.insert("high",settings.value("high").toString());
        then3map.insert("low",settings.value("low").toString());
        then3map.insert("ussd",settings.value("ussd").toString());
//        then3map.insert("outputDelayUnit",settings.value("outputDelayUnit").toString());
//        then3map.insert("durationUnit",settings.value("durationUnit").toString());
        map.insert("then3_cbx",then3map);
        then3maplist.append(map);
    }
    settings.endArray();

    QSettings settings2(m_iniPath,QSettings::IniFormat);
    QVariantList outputmaplist;
    for(int i=0; i<size; i++){
        map.clear();
        settings2.beginGroup(QString("TimeCbx%1").arg(i));
        QVariantMap outputmap;
        outputmap.insert("outputDelayUnit1",settings2.value("outputDelayUnit1").toInt());
        outputmap.insert("durationUnit1", settings2.value("durationUnit1").toInt());
        outputmap.insert("outputDelayUnit2",settings2.value("outputDelayUnit2").toInt());
        outputmap.insert("durationUnit2", settings2.value("durationUnit2").toInt());
        map.insert("outputmap",outputmap);
        outputmaplist.append(map);
        settings2.endGroup();
    }

    commandList.clear();
    for(int i=0; i<size; i++){
        map.clear();
        map.insert("if_cbx",ifmaplist.at(i).toMap().value("if_cbx").toMap());
        map.insert("then1_cbx",then1maplist.at(i).toMap().value("then1_cbx").toMap());
        map.insert("then2_cbx",then2maplist.at(i).toMap().value("then2_cbx").toMap());
        map.insert("then3_cbx",then3maplist.at(i).toMap().value("then3_cbx").toMap());
        map.insert("outputmap",outputmaplist.at(i).toMap().value("outputmap").toMap());
        map.insert("saveToDev",true);
        commandList.append(map);
//        qDebug()<<commandList.at(i).toMap().value("if_cbx").toMap().value("index").toString();
    }
    configCommandTableview(commandList);
}


/**
 * 保存到设备中
 * @brief UCXX52Model::on_saveToDevice_btn_clicked
 */
void UCXX52Model::on_saveToDevice_btn_clicked()
{
    for(int i=0 ; i<commandList.size(); i++){
        QVariantMap map = commandList.at(i).toMap();
        map.insert("if_cbx",map.value("if_cbx").toMap());
        map.insert("then1_cbx",map.value("then1_cbx").toMap());
        map.insert("then2_cbx",map.value("then2_cbx").toMap());
        map.insert("then3_cbx",map.value("then3_cbx").toMap());
        map.insert("outputmap",map.value("outputmap").toMap());
        map.insert("saveToDev",map.value("saveToDev").toBool());
        qDebug()<<i<<map.value("saveToDev").toBool();
        map.insert("isOnlyUcp",false);
        commandList.replace(i,map);
    }
    emit requestToDevice(UCXX52DealThread::CONFIG_WRITE_SETTING,commandList);
}


/**
 * USSD 最大字符数限制
 * @brief UCXX52Model::on_textEdit_textChanged
 *      正则表达式  ^[0-9a-zA-Z \,\-!.#*]+$
 */
void UCXX52Model::onTextEditTextChanged()
{
    QString str="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ,-!.#*";
    QString textContent;
    QTextEdit *textedit;
    QTextCursor textCursor;
    int position;
    int length;
    if(sender()->objectName() == ui->ifContain_textedit->objectName()){
        textedit = ui->ifContain_textedit;
    }else if(sender()->objectName() == ui->thenContent1_textedit->objectName()){
        textedit = ui->thenContent1_textedit;
    }else if(sender()->objectName() == ui->thenContent2_textedit->objectName()){
        textedit = ui->thenContent2_textedit;
    }else /*if(sender()->objectName() == ui->thenContent3_textedit->objectName())*/{
        textedit = ui->thenContent3_textedit;
    }

    //判断有效字符
    textContent = textedit->toPlainText();
     position =textedit->textCursor().position();
    for(int c=position; c >= 0; c--){
        textCursor = textedit->textCursor();
        if(!str.contains(textContent.mid(c - 1, 1))){
            textContent.remove(c - 1, 1);
            textedit->setText(textContent);
            textCursor.setPosition(c - 1);
            textedit->setTextCursor(textCursor);
        }
    }

    //判断是否超过最大限制
    position =textedit->textCursor().position();
    length = textContent.count();
    if((length > USSD_MAX_SIZE)) {
        textContent.remove(position - (length - USSD_MAX_SIZE), length - USSD_MAX_SIZE);
        textedit->setText(textContent);
        textCursor.setPosition(position - (length - USSD_MAX_SIZE));
        textedit->setTextCursor(textCursor);
    }
}

void UCXX52Model::recoverySettingEdit()
{
    ui->durationSec1_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->delayTimeSec1_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->durationWaveform1_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->lowLevelSec1_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->highLevelSec1_lineedit->setStyleSheet(RECOVERY_INPUT);

    ui->durationSec2_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->delayTimeSec2_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->durationWaveform2_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->lowLevelSec2_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->highLevelSec2_lineedit->setStyleSheet(RECOVERY_INPUT);

    ui->durationSec3_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->delayTimeSec3_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->durationWaveform3_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->lowLevelSec3_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->highLevelSec3_lineedit->setStyleSheet(RECOVERY_INPUT);

    ui->lockouttime_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->continuedSec_lineedit->setStyleSheet(RECOVERY_INPUT);

    ui->lockouttimeAnalog_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->continuedSecAnalog_lineedit->setStyleSheet(RECOVERY_INPUT);

    ui->lockouttimeMudbus_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->continuedSecMudbus_lineedit->setStyleSheet(RECOVERY_INPUT);

    ui->aboveMa_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->withMa1_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->withMa2_lineedit->setStyleSheet(RECOVERY_INPUT);

    ui->modbusAboveMa_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->modbusWithMa1_lineedit->setStyleSheet(RECOVERY_INPUT);
    ui->modbusWithMa2_lineedit->setStyleSheet(RECOVERY_INPUT);

    ui->setLockouTime_cb->setChecked(false);
    ui->locktime_frame->setVisible(false);

    ui->setLockouTimeAnalog_cb->setChecked(false);
    ui->locktimeAnalog_frame->setVisible(false);

    ui->setLockouTimeMudbus_cb->setChecked(false);
    ui->locktimeMudbus_frame->setVisible(false);

    ui->thenAdd1_btn->setVisible(true);
    ui->thenAdd2_btn->setVisible(true);
    ui->thenDel2_btn->setVisible(true);
    ui->thenDel3_btn->setVisible(true);

    ui->thenAdd1_btn->setGeometry(THEN_ADD_BTN_X1,130,31,21);
    ui->thenAdd2_btn->setGeometry(THEN_ADD_BTN_X1,220,31,21);
    ui->thenDel2_btn->setGeometry(THEN_DEL_BTN_X1,220,31,21);
    ui->thenDel3_btn->setGeometry(THEN_DEL_BTN_X1,310,31,21);


    QList<QComboBox *> timeCbx ;
    timeCbx<<ui->continueTime_cbx<<ui->setLockoutTime_cbx
           <<ui->delayTimeSec1_cbx<<ui->durationSec1_cbx<<ui->highLevelSec1_cbx<<ui->lowLevelSec1_cbx
           <<ui->delayTimeSec2_cbx<<ui->durationSec2_cbx<<ui->highLevelSec2_cbx<<ui->lowLevelSec2_cbx
           <<ui->delayTimeSec3_cbx<<ui->durationSec3_cbx<<ui->highLevelSec3_cbx<<ui->lowLevelSec3_cbx
           <<ui->if_cbx<<ui->then1_cbx<<ui->then2_cbx<<ui->then3_cbx;
    foreach (QComboBox *c, timeCbx) {
        c->setCurrentIndex(0);
    }

    QList<QLineEdit *> lineedit;
    lineedit<<ui->continuedSec_lineedit<<ui->lockouttime_lineedit
           <<ui->delayTimeSec1_lineedit<<ui->highLevelSec1_lineedit<<ui->durationSec1_lineedit<<ui->lowLevelSec1_lineedit<<ui->durationWaveform1_lineedit
             <<ui->delayTimeSec2_lineedit<<ui->highLevelSec2_lineedit<<ui->durationSec2_lineedit<<ui->lowLevelSec2_lineedit<<ui->durationWaveform2_lineedit
               <<ui->delayTimeSec3_lineedit<<ui->highLevelSec3_lineedit<<ui->durationSec3_lineedit<<ui->lowLevelSec3_lineedit<<ui->durationWaveform3_lineedit;
    foreach (QLineEdit *l, lineedit) {
        l->setText("0");
    }

    QList<QTextEdit*> textedit;
    textedit<<ui->ifContain_textedit<<ui->thenContent1_textedit<<ui->thenContent2_textedit<<ui->thenContent3_textedit;
    foreach (QTextEdit *t, textedit) {
        t->clear();
        t->setStyleSheet(Recovery_Textedit);
    }
}

void UCXX52Model::onTimeCbxChanged(int row)
{
    QSettings settings(m_iniPath, QSettings::IniFormat);
    settings.beginGroup(QString("TimeCbx%1").arg(row));
    settings.setValue("inputContinueUnit",ui->continueTime_cbx->currentIndex());
    settings.setValue("locktimeUnit",ui->setLockoutTime_cbx->currentIndex());

    settings.setValue("inputContinueAnalogUnit",ui->continueTimeAnalog_cbx->currentIndex());
    settings.setValue("locktimeAnalogUnit",ui->setLockoutTimeAnalog_cbx->currentIndex());


    if(ui->then1_cbx->currentData() == TC_Output1){
        settings.setValue("outputDelayUnit1",ui->delayTimeSec1_cbx->currentIndex());
        settings.setValue("durationUnit1",ui->durationSec1_cbx->currentIndex());

    }else if(ui->then2_cbx->currentData() == TC_Output1){
        settings.setValue("outputDelayUnit1",ui->delayTimeSec2_cbx->currentIndex());
        settings.setValue("durationUnit1",ui->durationSec2_cbx->currentIndex());

    }else if(ui->then3_cbx->currentData() == TC_Output1){
        settings.setValue("outputDelayUnit1",ui->delayTimeSec3_cbx->currentIndex());
        settings.setValue("durationUnit1",ui->durationSec3_cbx->currentIndex());

    }else{
        settings.setValue("outputDelayUnit1",0);
        settings.setValue("durationUnit1",0);
    }

    if(ui->then1_cbx->currentData() == TC_Output2){
        settings.setValue("outputDelayUnit2",ui->delayTimeSec1_cbx->currentIndex());
        settings.setValue("durationUnit2",ui->durationSec1_cbx->currentIndex());

    }else if(ui->then2_cbx->currentData() == TC_Output2){
        settings.setValue("outputDelayUnit2",ui->delayTimeSec2_cbx->currentIndex());
        settings.setValue("durationUnit2",ui->durationSec2_cbx->currentIndex());

    }else if(ui->then3_cbx->currentData() == TC_Output2){
        settings.setValue("outputDelayUnit2",ui->delayTimeSec3_cbx->currentIndex());
        settings.setValue("durationUnit2",ui->durationSec3_cbx->currentIndex());

    }else{
        settings.setValue("outputDelayUnit2",0);
        settings.setValue("durationUnit2",0);
    }
    settings.endGroup();
}

void UCXX52Model::removeThenCbxMsg(int index)
{
    if(index == 1){
        if(ui->then1_cbx->currentData().toInt() == TC_StatusMessage ||
           ui->then1_cbx->currentData().toInt() == TC_CustomMessage){
            return;
        }
        ui->then1_cbx->removeItem(ui->then1_cbx->findData(TC_StatusMessage));
        ui->then1_cbx->removeItem(ui->then1_cbx->findData(TC_CustomMessage));
    }else if(index == 2){
        if(ui->then2_cbx->currentData().toInt() == TC_StatusMessage ||
           ui->then2_cbx->currentData().toInt() == TC_CustomMessage){
            return;
        }
        ui->then2_cbx->removeItem(ui->then2_cbx->findData(TC_StatusMessage));
        ui->then2_cbx->removeItem(ui->then2_cbx->findData(TC_CustomMessage));
    }else if(index == 3){
        if(ui->then3_cbx->currentData().toInt() == TC_StatusMessage ||
           ui->then3_cbx->currentData().toInt() == TC_CustomMessage){
            return;
        }
        ui->then3_cbx->removeItem(ui->then2_cbx->findData(TC_StatusMessage));
        ui->then3_cbx->removeItem(ui->then2_cbx->findData(TC_CustomMessage));
    }
}

void UCXX52Model::insertThenCbxMsg(int index)
{
    qDebug()<<!m_dealThread->structSupportModel.sms<<!m_dealThread->structSupportModel.ussd<< !m_dealThread->structSupportModel.lora;
    if(m_dealThread->structSupportModel.sms || m_dealThread->structSupportModel.ussd || m_dealThread->structSupportModel.lora){
//        qDebug();
    }else{
        return;
    }

    if(ui->then1_cbx->currentData().toInt() == TC_StatusMessage ||
       ui->then1_cbx->currentData().toInt() == TC_CustomMessage ||
       ui->then2_cbx->currentData().toInt() == TC_StatusMessage ||
       ui->then2_cbx->currentData().toInt() == TC_CustomMessage ||
       ui->then3_cbx->currentData().toInt() == TC_StatusMessage ||
       ui->then3_cbx->currentData().toInt() == TC_CustomMessage ){
        return;
    }
    if(index == 1){
        if(ui->then2_cbx->currentData().toInt() == TC_StatusMessage ||
           ui->then2_cbx->currentData().toInt() == TC_CustomMessage ||
           ui->then3_cbx->currentData().toInt() == TC_StatusMessage ||
           ui->then3_cbx->currentData().toInt() == TC_CustomMessage ){
            return;
        }
        if(m_dealThread->structSupportModel.lora){
            ui->then1_cbx->insertItem(TC_CustomMessage-1,tr("Send a custom message"));
            ui->then1_cbx->setItemData(TC_CustomMessage-1,TC_CustomMessage);
        }else{
            ui->then1_cbx->insertItem(TC_StatusMessage,tr("Send a status message"));
            ui->then1_cbx->insertItem(TC_CustomMessage,tr("Send a custom message"));
            ui->then1_cbx->setItemData(TC_StatusMessage,TC_StatusMessage);
            ui->then1_cbx->setItemData(TC_CustomMessage,TC_CustomMessage);
        }

    }else if(index == 2){
        if(ui->then3_cbx->currentData().toInt() == TC_StatusMessage ||
           ui->then3_cbx->currentData().toInt() == TC_CustomMessage ||
           ui->then1_cbx->currentData().toInt() == TC_StatusMessage ||
           ui->then1_cbx->currentData().toInt() == TC_CustomMessage ){
            return;
        }
        if(m_dealThread->structSupportModel.lora){
            ui->then2_cbx->insertItem(TC_CustomMessage-1,tr("Send a custom message"));
            ui->then2_cbx->setItemData(TC_CustomMessage-1,TC_CustomMessage);
        }else{
            ui->then2_cbx->insertItem(TC_StatusMessage,tr("Send a status message"));
            ui->then2_cbx->insertItem(TC_CustomMessage,tr("Send a custom message"));
            ui->then2_cbx->setItemData(TC_StatusMessage,TC_StatusMessage);
            ui->then2_cbx->setItemData(TC_CustomMessage,TC_CustomMessage);
        }

    }else if(index == 3){

        if(ui->then1_cbx->currentData().toInt() == TC_StatusMessage ||
           ui->then1_cbx->currentData().toInt() == TC_CustomMessage ||
           ui->then2_cbx->currentData().toInt() == TC_StatusMessage ||
           ui->then2_cbx->currentData().toInt() == TC_CustomMessage){
            return;
        }
        if(m_dealThread->structSupportModel.lora){
            ui->then3_cbx->insertItem(TC_CustomMessage-1,tr("Send a custom message"));
            ui->then3_cbx->setItemData(TC_CustomMessage-1,TC_CustomMessage);
        }else{
            ui->then3_cbx->insertItem(TC_StatusMessage,tr("Send a status message"));
            ui->then3_cbx->insertItem(TC_CustomMessage,tr("Send a custom message"));
            ui->then3_cbx->setItemData(TC_StatusMessage,TC_StatusMessage);
            ui->then3_cbx->setItemData(TC_CustomMessage,TC_CustomMessage);
        }

    }
}

void UCXX52Model::initThenCbx()
{
    disconnect(ui->then1_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then1_cbx_currentIndexChanged(int)));
    disconnect(ui->then2_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then2_cbx_currentIndexChanged(int)));
    disconnect(ui->then3_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then3_cbx_currentIndexChanged(int)));

    if(m_dealThread->structSupportModel.ioNum  == I1O1){
        ui->withMa1_lineedit->clear();
        ui->withMa2_lineedit->clear();
        ui->aboveMa_lineedit->clear();
    }

    ui->then1_cbx->clear();
    ui->then2_cbx->clear();
    ui->then3_cbx->clear();

    ui->then1_cbx->addItem("",TC_Empty);
    if(m_dealThread->structSupportModel.sms || m_dealThread->structSupportModel.ussd || m_dealThread->structSupportModel.lora){
        if(m_dealThread->structSupportModel.lora){
            ui->then1_cbx->addItem(tr("Send a custom message"),TC_CustomMessage);

        }else{
            ui->then1_cbx->addItem(tr("Send a status message"),TC_StatusMessage);
            ui->then1_cbx->addItem(tr("Send a custom message"),TC_CustomMessage);
        }
    }
    if(m_dealThread->structSupportModel.data){
        ui->then1_cbx->addItem(tr("Send an alarm"),TC_ALARM);
    }
    ui->then1_cbx->addItem(tr("Output1"),TC_Output1);

    if(m_dealThread->structSupportModel.ioNum  == I2O2){
        ui->then1_cbx->addItem(tr("Output2"),TC_Output2);
    }
    ui->then1_cbx->addItem(tr("Restart the device"),TC_DevRestart);

    ui->then2_cbx->addItem("",TC_Empty);
    if(m_dealThread->structSupportModel.sms || m_dealThread->structSupportModel.ussd || m_dealThread->structSupportModel.lora){
        if(m_dealThread->structSupportModel.lora){
            ui->then2_cbx->addItem(tr("Send a custom message"),TC_CustomMessage);
        }else{
            ui->then2_cbx->addItem(tr("Send a status message"),TC_StatusMessage);
            ui->then2_cbx->addItem(tr("Send a custom message"),TC_CustomMessage);
        }
    }
    if(m_dealThread->structSupportModel.data){
        ui->then2_cbx->addItem(tr("Send an alarm"),TC_ALARM);
    }
    ui->then2_cbx->addItem(tr("Output1"),TC_Output1);
    if(m_dealThread->structSupportModel.ioNum == I2O2){
        ui->then2_cbx->addItem(tr("Output2"),TC_Output2);
    }
    ui->then2_cbx->addItem(tr("Restart the device"),TC_DevRestart);

    ui->then3_cbx->addItem("",TC_Empty);
    if(m_dealThread->structSupportModel.sms || m_dealThread->structSupportModel.ussd || m_dealThread->structSupportModel.lora){
        if(m_dealThread->structSupportModel.lora){
            ui->then3_cbx->addItem(tr("Send a custom message"),TC_CustomMessage);
        }else{
            ui->then3_cbx->addItem(tr("Send a status message"),TC_StatusMessage);
            ui->then3_cbx->addItem(tr("Send a custom message"),TC_CustomMessage);
        }
    }
    if(m_dealThread->structSupportModel.data){
        ui->then3_cbx->addItem((tr("Send an alarm")),TC_ALARM);
    }
    ui->then3_cbx->addItem(tr("Output1"),TC_Output1);
    if(m_dealThread->structSupportModel.ioNum == I2O2){
        ui->then3_cbx->addItem(tr("Output2"),TC_Output2);
    }
    ui->then3_cbx->addItem(tr("Restart the device"),TC_DevRestart);

    connect(ui->then1_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then1_cbx_currentIndexChanged(int)));
    connect(ui->then2_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then2_cbx_currentIndexChanged(int)));
    connect(ui->then3_cbx,SIGNAL(currentIndexChanged(int)),this,SLOT(on_then3_cbx_currentIndexChanged(int)));
}

/**
 * 时区转换提示
 * @brief UCXX52Model::on_timeisTime_tde_timeChanged
 * @param time
 */
void UCXX52Model::on_timeisTime_tde_timeChanged(const QTime &time)
{
    Q_UNUSED(time)
    on_timeisDay_cbx_currentIndexChanged(ui->timeisDay_cbx->currentText());
}


/**
 * 时区转换提示
 * @brief UCXX52Model::on_timeisDay_cbx_currentIndexChanged
 * @param arg1
 */
void UCXX52Model::on_timeisDay_cbx_currentIndexChanged(const QString &arg1)
{
    QDateTime datatime = QDateTime( QDate::currentDate(), ui->timeisTime_tde->time(),Qt::UTC).toTimeSpec(Qt::LocalTime);
    ui->timeToLocalTip_label->setText(tr("The acition you have set will be triggered at %1 %2 (based on your computer clock)")
                                      .arg(datatime.time().toString("hh:mm")).arg(ui->timeisDay_cbx->currentIndex() == 0 ? tr("Every day") : arg1));

}



/**
 * 接受sms密文
 * @brief UCXX52Model::onGetSmsTxt
 * @param txt
 */
void UCXX52Model::onGetSmsTxt(QString txt)
{
    smsTxt.clear();

    QString str;
    QString str2;
    QString tmp ;
    bool ok=0;
    char baseChar[256]={0};
    uint8_t dataHex[256] = {0};
    QStringList list = txt.split("\n");

    for(int i=0; i<list.size(); i++){
        str = str + list.at(i);
        str2 = tmp;
        int offset=0;
        for(int j=0; j<str.length(); j++ ){
            dataHex[offset++] = str.mid(j,2).toInt(&ok,16);
            j = j+1;
        }
//        for(int m=0; m<offset; m++){
//            printf("%02x",dataHex[m]);
//        }
//        printf("\n");
        base64_encode(dataHex,baseChar,offset);
        tmp = QString::asprintf("%s",baseChar);

        if(tmp.size() > 126){
            if(i == 0){
                str.clear();
                str2.clear();
                smsTxt.append(tmp).append("\n");
            }else{
                i--;
//                qDebug1()<<str;
//                qDebug1()<<str2;
//                char base[128]={0};
//                base64_decode(str2.toLatin1().data(),(unsigned char *)base);
//                printf("^^ %s \n",base);
                smsTxt.append(str2).append("\n");
                str.clear();
                str2.clear();
                tmp.clear();
            }
        }
    }

    if(!str.isEmpty()){
        char base[128]={0};
        base64_decode(tmp.toLatin1().data(),(unsigned char *)base);
//        printf("^^ %s \n",base);
        smsTxt.append(tmp).append("\n");
    }
}

//Base64 转换
const char * base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char * UCXX52Model::base64_encode( const unsigned char * bindata, char * base64, int binlength )
{
    int i, j;
    unsigned char current;

    for ( i = 0, j = 0 ; i < binlength ; i += 3 ) {
        current = (bindata[i] >> 2) ;
        current &= (unsigned char)0x3F;
        base64[j++] = base64char[(int)current];

        current = ( (unsigned char)(bindata[i] << 4 ) ) & ( (unsigned char)0x30 ) ;
        if ( i + 1 >= binlength ) {
            base64[j++] = base64char[(int)current];
            base64[j++] = '=';
            base64[j++] = '=';
            break;
        }

        current |= ( (unsigned char)(bindata[i+1] >> 4) ) & ( (unsigned char) 0x0F );
        base64[j++] = base64char[(int)current];

        current = ( (unsigned char)(bindata[i+1] << 2) ) & ( (unsigned char)0x3C ) ;
        if ( i + 2 >= binlength ) {
            base64[j++] = base64char[(int)current];
            base64[j++] = '=';
            break;
        }
        current |= ( (unsigned char)(bindata[i+2] >> 6) ) & ( (unsigned char) 0x03 );
        base64[j++] = base64char[(int)current];

        current = ( (unsigned char)bindata[i+2] ) & ( (unsigned char)0x3F ) ;
        base64[j++] = base64char[(int)current];
    }
    base64[j] = '\0';

    return base64;
}

int UCXX52Model::base64_decode( const char * base64, unsigned char * bindata )
{
    int i, j;
    unsigned char k;
    unsigned char temp[4];

    for ( i = 0, j = 0; base64[i] != '\0' ; i += 4 ) {
        memset( temp, 0xFF, sizeof(temp) );
        for ( k = 0 ; k < 64 ; k ++ ) {
            if ( base64char[k] == base64[i] )
                    temp[0]= k;
        }
        for ( k = 0 ; k < 64 ; k ++ ) {
            if ( base64char[k] == base64[i+1] )
                    temp[1]= k;
        }
        for ( k = 0 ; k < 64 ; k ++ ) {
            if ( base64char[k] == base64[i+2] )
                    temp[2]= k;
        }
        for ( k = 0 ; k < 64 ; k ++ ) {
            if ( base64char[k] == base64[i+3] )
                    temp[3]= k;
        }

        bindata[j++] = ((unsigned char)(((unsigned char)(temp[0] << 2))&0xFC)) |
                        ((unsigned char)((unsigned char)(temp[1]>>4)&0x03));
        if ( base64[i+2] == '=' )
                break;

        bindata[j++] = ((unsigned char)(((unsigned char)(temp[1] << 4))&0xF0)) |
                        ((unsigned char)((unsigned char)(temp[2]>>2)&0x0F));
        if ( base64[i+3] == '=' )
                break;

        bindata[j++] = ((unsigned char)(((unsigned char)(temp[2] << 6))&0xF0)) |
                        ((unsigned char)(temp[3]&0x3F));
    }

    return j;
}

/**
 * 转换毫秒到秒
 * @brief UCXX52Model::ascMsToSec
 * @param ms
 * @return
 */
QString UCXX52Model::ascMsToSec(QString ms, int unit)
{
//    qDebug()<<ms;
    if(ms.toInt() < 1){
        return ms;
    }
    QString ret;
    if(unit == 0){//sec
        ret = QString::asprintf("%lg",ms.toDouble() / 1000);
    }else if(unit == 1){
        ret = ms;
    }else if(unit == 2){
        ret = QString::asprintf("%lg",(ms.toDouble()) / 60000);
    }

    return ret;
}

/**
 * Ov = [(Osh - Osl)*(Iv - Isl)/(Ish - Isl)] + Osl
 * 换算结果 =[(Osh - Osl)*(当前读到的mA值 - 4)/16] + Osl
 * @brief UCXX52Model::thresholdToMa
 * @param value
 * @return mA的值
 */
QString UCXX52Model::thresholdToMa(QString value,int ic_analogIndex)
{
    Q_UNUSED(ic_analogIndex)
    return value;
#if 0
    float ret;
    if(ic_analogIndex == IC_Analog1){
        ret = (((value.toFloat() - osl1.toFloat()) * 16) / (osh1.toFloat() - osl1.toFloat()))+ 4;
    }else if(ic_analogIndex == IC_Analog2){
        ret = (value.toFloat() - osl2.toFloat()) * 16 / (osh2.toFloat() - osl2.toFloat()) + 4;
    }else{
        ret = 0.00;
    }
//    qDebug()<<value<<QString::asprintf("%.2f",ret);
    QString r = QString::asprintf("%.2f",ret);
    return r;
#endif
}

QString UCXX52Model::mAtoThreshold(QString value,int ic_analogIndex)
{
    Q_UNUSED(ic_analogIndex)
    return value;
#if 0
    QSettings settings(m_iniPath,QSettings::IniFormat);
    settings.beginGroup("AiUnit");
    QString unit  = settings.value("A"+m_statusPageInfo.sn).toString();
    QString unit2 = settings.value("B"+m_statusPageInfo.sn).toString();
    settings.endGroup();

    float ret;
    if(ic_analogIndex == IC_Analog1){
        if(!unit.isEmpty()){
            ret = ((osh1.toFloat() - osl1.toFloat()) * ( value.toFloat() - 4 ) / 16) + osl1.toFloat();
        }else{
            return value;
        }
    }else if(ic_analogIndex == IC_Analog2){
        if(!unit2.isEmpty()){
            ret = ((osh2.toFloat() - osl2.toFloat()) * ( value.toFloat() - 4 ) / 16) + osl2.toFloat();
        }else{
            return value;
        }
    }else{
        ret = 0.00;
    }
    QString r = QString::asprintf("%.2f",ret);
    return r;
#endif
}
