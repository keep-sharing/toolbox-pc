#ifndef UR_STRUCT
#define UR_STRUCT

#define UC_VERSION "   ToolBox "
#define CHANNEL_LORA_NUM 8


#define UNP_LOG_DEBUG 01

#define UR_LHR_DEBUG() qDebug() << __LINE__ << __FUNCTION__
#define UR_LHR_INFO() qInfo() << __LINE__ << __FUNCTION__
#define EQ(key1, key2) (((key1) > (key2)) - ((key1) < (key2)))

//#define ENABLE_LORA_TEMPLATE
#define ENABLE_N1_SERIAL 01
#define INTERNATION_VERSION 0
#define NOT_USE_DEVICE 0
#define Empty_Time 0
#define USE_DEVICENAME 0
#define OUTPUT_WAVEFORM 0
#define USE_ANY_CHANGE_REPORT 01
#define USE_APP_NONE 0
#define USE_LORA_APPLY 01
#define CHANNEL_QUANTITY_ENABLE 0
//#define SUPPORT_UPGRADE_UBOOT   1  //升级uboot开关

//#define SUPPORT_DOMAIN_NAME 01

#define USE_BASE64

#define IMAGE_ENCODE    1
#define IMAGE_DECODE    0
#define I1O1 2
#define I2O2 4
#define DEBUG_RESOLVE 1
#define NOT_VISIBLE "NOT VISIBLE YEASTARURSALINK"

#define ERROR_INPUT "border:2px solid rgb(225,0,0);font-size:13px;font-family:'Arial'"
#define ERROR_INPUT2 "background-color: rgb(255, 255, 255);border:2px solid rgb(225,0,0);font-size:13px;font-family:'Arial'"
#define RECOVERY_INPUT "QLineEdit\n{\n	background-color:#ffffff;\n	border: 1px solid #a1a1a1;font-size:13px;font-family:'Arial'\n}\n\nQLineEdit:hover\n{\n	border: 1px solid rgb(58, 65, 70);\n}\nQLineEdit:focus\n{\n	 border: 1px solid rgb(94, 154, 234);\n}"
#define RECOVERY_INPUT2 "background-color: rgb(255, 255, 255);font-size:13px;font-family:'Arial'"
#define RECOVERY_INPUT3 "QLineEdit\n{\n    border: 1px solid #a1a1a1;font-size:13px;font-family:'Arial'\n}\nQLineEdit:!enabled {\n	background: rgb(240, 240, 240);\n}\nQLineEdit:hover\n{\n        border: 1px solid rgb(58, 65, 70);\n}\nQLineEdit:focus\n{\n        border: 1px solid rgb(94, 154, 234);\n}"
#define Recovery_Textedit "QTextEdit\n{\n    border: 1px solid #a1a1a1;font-size:13px;font-family:'Arial'\n}\nQTextEdit:!enabled {\n	background: rgb(240, 240, 240);\n}\nQTextEdit:hover\n{\n        border: 1px solid rgb(58, 65, 70);\n}\nQTextEdit:focus\n{\n        border: 1px solid rgb(94, 154, 234);\n}"

#define SUCCESS "Success"
#define FAIL "Fail"
#define USSD_MAX_SIZE 60
#define STATUS_PAGE_REFRESH_TIME 10000 //ms
#define THEN_ADD_BTN_X1 285
#define THEN_DEL_BTN_X1 320
#define THEN_ADD_BTN_X3 790
#define THEN_ADD_BTN_X2 610
#define THEN_DEL_BTN_X2 645
#define THEN_DEL_BTN_X3 825

#define NT_GSM    "2"
#define NT_WCDMA  "3"
#define NT_LTE    "4"
#define NT_NB     "5"

#define EM_AM_TEMPLATE "EM_AM_TEMPLATE" //模板模式
#define EM500_EC5 "EC5" //土壤温湿度传感器 Soil
#define EM500_PT100 "PT100" //检测温度
#define EM500_SWL "SWL" //投入式液位监测
#define EM500_UDL "UDL" //超声波液位监测
#define EM500_CO2 "CO2" //二氧化碳、温湿度监测
#define EM500_PM25 "PM25"
#define EM500_LGT "LGT"  //光照
#define EM500_MT05 "MT05" //土壤温湿度
#define EM500_MEC20 "MEC20" //电导率
#define EM500_SMTC  "SMTC" //电导率
#define EM500_PR10 "PR10" //管道压力测试  检测管道内液位
#define EM500_PAR "PAR"  //光合有效检测
#define EM500_PP "PP"  //管道压力
#define AM100 "AM100"
#define AM102 "AM102"
#define EM300_T1 "T1"
#define EM300_TH "TH"
#define EM300_TWL "TWL"
#define EM300_SLD "SLD"
#define EM300_ZLD "ZLD"
#define EM300_TMCS "MCS"
#define EM300_SW "SW"
#define EM500_CO "CO"
#define EM500_NH3 "NH3"
#define EM500_H2S "H2S"
#define UC501 "501"
#define UC502 "502"
#define UC511 "UC511"
#define UC512 "UC512"

#endif // UR_STRUCT

