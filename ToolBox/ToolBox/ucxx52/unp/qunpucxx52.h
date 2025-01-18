#ifndef QUNPUCXX52_H
#define QUNPUCXX52_H

#include <QObject>
#include "unxx_params.h"
#include "loraunp.h"

#define LORAWAN_DEVICE
#ifdef USE_IN_STM32
#include "list.h"
#endif

#define FLASH_UBL_BASE_ADDR     0x08000000
#if defined(LORAWAN_DEVICE)
#define FLASH_APP_BASE_ADDR     0x08006000    //16KB for ubl
#define FLASH_APP_ENDADDR       (0x08004000 + 0x18400)
#else
#define FLASH_APP_BASE_ADDR     0x08007000    //28KB for ubl
#define FLASH_APP_ENDADDR       (0x08004000 + 0x18400)
#endif

#define UNP_VERSION             0x13
#define UNP_FRAME_FLAG          0x7e
#define UNP_MAX_PKTSIZE         320
#define UNP_MIN_PKTSIZE         16
#define UNP_MAX_TIMEOUT         12000
#define UNP_PASSWD_LEN          6
#define UNP_ONE_TIME_SIZE       128
#define UNP_UPGRADE_CHUNKSIZE   1000
#define UNP_UPGRADE_BOOTLOADER_CHUNKSIZE   256

#define UNP_MSG_MAX_LENGTH      64
#define UNP_MSG_MAX_LENGTH_LORAWAN      128

#define UNP_SCA_MAX_LENGTH      32
#define UNP_PIN_MAX_LENGTH      8
#define UNP_POOR_SIGNAL_VAL     10
#define UNP_PRODUCT_NAME_LEN    8
#define UNP_PRODUCT_ID_LEN      4
#define UNP_PRODUCT_ID_LEN_EM   8
#define UNP_PRODUCT_SN_LEN      12
#define UNP_PRODUCT_SN_LEN2     16
#define UNP_DEVDESC_LEN         32
#define UNP_DEVNAME_LEN         0
#define UNP_HWVER_LEN           4
#define UNP_SWVER_LEN           4
#define UNP_SERIES_LEN          4
#define UNP_PN_LEN              4
#define UNP_PN_LEN_EM          	8
#define UNP_PN_NUM              4
#define UNP_CUSTOM_LEN          4
#define UNP_REGION_LEN          2
#define UNP_PLMN_MAX_LEN        6
#define UNP_NONCE_LEN           6
#define UNP_APN_MAX_LENGTH      31
#define UNP_APN_MAX_LENGTH_LORAWAN 16
#define UNP_MAX_RULES_NUM       2
#define UNP_APN_USERNAME_LEN    31
#define UNP_APN_PASSWORD_LEN    31
#define UNP_PN_TOTAL_LEN        (UNP_REGION_LEN + UNP_CUSTOM_LEN + UNP_PN_LEN*UNP_PN_NUM + 4)
#define UNP_REAL_PN_TOTAL_LEN   (UNP_PN_LEN_EM*UNP_PN_NUM + 3)
#define UNP_REPORT_NUM_MAX_CNT  6
#define UNP_CTRL_NUM_MAX_CNT    2
#define UNP_NUM_MAX_LEN         16
#define UNP_USSD_PREFIX_MAX_LEN 16
#define UNP_MODBUS_NAME_MAX_LEN 16
#define UNP_UPGRADE_FLAG_MAX    32
#define UNP_DTU_REG_PACKET_LEN  32
#define UNP_AI_COLLECT_BUFNUM   5
#define UNP_DTU_SERVER_NUM      2
#define UNP_TCP_SERVER_NUM      2
#define UNP_UDP_SERVER_NUM      2
#define UNP_SERVER_IP_LEN       64
#define UNP_MQTT_CLIENTID_LEN   32
#define UNP_MQTT_USERNAME_LEN   32
#define UNP_MQTT_PASSWORD_LEN   32
#define UNP_RESET_REPORT_FLAG   0x55
#define UNP_UPGRADING_FLAG      "unxx@"
#define UNP_UPGRADE_FAIL_INFO   "fail"
#define UNP_UPGRADE_SUCC_INFO   "succ"
#define UNP_UPGRADE_REQUEST     "1111222233334444@"
#define UNP_UPGRADE_COMPLETE    "4444333322221111@"
#define UNP_STATUS_FLAGS        "@status@"
#define UNP_STATUS_MESSAGE      UNP_STATUS_FLAGS

#define UNXX_MAGIC                   "UN00666"
#define UNXX_GET_EVENT(X)            (1 << (X))
#define UNXX_MAX_AI_NUM              2
#define UNXX_MAX_INPUT_IO_NUM        2
#define UNXX_MAX_OUTPUT_IO_NUM       2
#define UNXX_MAX_GPIO_NUM            2

#define UNXX_MAX_NORMAL_IO_NUM       2
#define UNXX_MAX_AI_IO_NUM           1
#define UNXX_MAX_LORA_IO_NUM         2
#define UNXX_MAX_WORKNUM             8
#define UNXX_MAX_MODBUS_CHAN         16
#define UNXX_MAX_MODBUS_QUANTITY     8
#define UNXX_MAX_CLOCK               UNXX_MAX_WORKNUM
#define UNXX_MAX_MSGNUM              UNXX_MAX_WORKNUM
#define UNXX_MAX_CLOCKNUM            UNXX_MAX_WORKNUM

#define UPGRADE_FLAGS_VALUE           0x55
#define UPGRADE_ONE_TIME_READ_SIZE    256
#define UPGRADE_IMAGE_ADDR            0x00
#define UPGRADE_IMAGE_ADDR_LORAWAN            0x7000
#define UPGRADE_IMAGE_SIZE            0x3d800   //246KB

#define UPGRADE_LENGTH_ADDR           (UPGRADE_IMAGE_ADDR + UPGRADE_IMAGE_SIZE)
#define UPGRADE_LENGTH_SIZE           0x04

#define UPGRADE_CRC32_ADDR            (UPGRADE_LENGTH_ADDR + UPGRADE_LENGTH_SIZE)
#define UPGRADE_CRC32_SIZE            0x04

#define UPGRADE_FLAGS_ADDR            (UPGRADE_CRC32_ADDR + UPGRADE_CRC32_SIZE)
#define UPGRADE_FLAGS_SIZE            0x01

#define NFC_MAGIC               0x6666666777777777
#define NFC_VERSION             0x01
#define NFC_MAX_TIMEOUT         5
#define NFC_CHECK_STATUS        100
#define NFC_MAX_LEN             64

#define PRODUCT_INFO_ADDR       0
#define PN_INFO_ADDR            (PRODUCT_INFO_ADDR+PRODUCT_INFO_LEN)//(FLASH_PRODUCT_INFO_ADDR + PRODUCT_INFO_LEN)
#define DEVICE_INFO_ADDR        (PN_INFO_ADDR+PN_INFO_LEN)
#define RULES_INFO_ADDR         (DEVICE_INFO_ADDR + DEVICE_INFO_LEN)
#define APPLICATION_INFO_ADDR   (RULES_INFO_ADDR + RULES_INFO_LEN)
#define USR_CONFIG_ADDR         (APPLICATION_INFO_ADDR + APPLICATION_INFO_LEN)
#define LORA_INFO_ADDR          (USR_CONFIG_ADDR + USR_CONFIG_LEN)

class QunpUCXX52 : public QObject
{
    Q_OBJECT

public:
    typedef enum {
        INPUT_PASSWD_PKT          = 0x01,
        REBOOT_DEVICE_PKT         = 0x02,
        UPGRADE_DEVICE_PKT        = 0x03,
        READ_PARAM_PKT            = 0x04,
        WRITE_PARAM_PKT           = 0x05,
        CONNECT_DEVICE_PKT        = 0x06,
        RESET_DEVICE_PKT          = 0x07,
        DEVICE_CTRL_PKT           = 0x08,
    #ifdef SUPPORT_UPGRADE_UBOOT
        UPGRADE_UBOOT_PKT         = 0x09,
    #endif
        DEVICE_RELOAD_CONFIG        = 0x10,

        INPUT_PASSWD_ACK_PKT      = 0x81,
        REBOOT_DEVICE_ACK_PKT     = 0x82,
        UPGRADE_DEVICE_ACK_PKT    = 0x83,
        READ_PARAM_ACK_PKT        = 0x84,
        WRITE_PARAM_ACK_PKT       = 0x85,
        CONNECT_DEVICE_ACK_PKT    = 0x86,
        RESET_DEVICE_ACK_PKT      = 0x87,
        DEVICE_CTRL_ACK_PKT       = 0x88,

    #ifdef SUPPORT_UPGRADE_UBOOT
        UPGRADE_UBOOT_ACK_PKT  = 0x89,
    #endif
        DEVICE_RELOAD_CONFIG_ACK_PKT    = 0x90,

        DEVICE_STATUS_PKT             = 0xf0,
        DEVICE_COMMON_REPORT_PKT      = 0xf1,
        DEVICE_CHANGE_REPORT_PKT      = 0xf2,
        DEVICE_ATTRIBUTE_REPORT_PKT   = 0xf3,
        DEVICE_REGULAR_REPORT_PKT     = 0xf4,
        DEVICE_PARAMS_REPORT_PKT      = 0xf5,
        DEVICE_DTU_REPORT_PKT         = 0xf6,
        DEVICE_ALARM_REPORT_PKT       = 0xf7,
        DEVICE_INTELLIGENT_REPORT_PKT = 0xf8,
    } unp_pack_t;

    typedef enum {
        PARAM_IDENTIFICATION         = 0x01,
        PARAM_CONSOLE_CTRL           = 0x02,
        PARAM_CONSOLE_CFG            = 0x03,
        PARAM_DELIMITER              = 0x04,
        PARAM_USER_WORK              = 0x05,
        PARAM_USER_CONFIG            = 0x06,
        PARAM_IO_CONDITION           = 0x07,
        PARAM_IO_ACTION              = 0x08,
        PARAM_MSG_CONDITION          = 0x09,
        PARAM_MSG_ACTION             = 0x0a,
        PARAM_DEVICE_TIME            = 0x0b,
        PARAM_DEVICE_CLOCK           = 0x0c,
        PARAM_GSM_STATUS             = 0x0d,
        PARAM_GSM_SIGNAL             = 0x0e,
        PARAM_INPUT_IO_STATUS        = 0x0f,
        PARAM_OUTPUT_IO_STATUS       = 0x10,
        PARAM_DEVICE_PASSWD          = 0x11,
        PARAM_MOBILE_NET             = 0x12,
        PARAM_MOBILE_SCA             = 0x13,
        PARAM_MOBILE_PIN             = 0x14,
        PARAM_APP_MODE               = 0x15,
        PARAM_USSD_PREFIX            = 0x16,
        PARAM_REPORT_INTERVAL        = 0x17,
        PARAM_SUCC_REPORT            = 0x18,
        PARAM_FAIL_REPORT            = 0x19,
        PARAM_CHANGE_REPORT          = 0x1a,
        PARAM_SMS_DCS                = 0x1b,
        PARAM_REPORT_BY_SMS          = 0x1c,
        PARAM_CTRL_BY_SMS            = 0x1d,
        PARAM_CONTEXT_TYPE           = 0x1e,
        PARAM_REPORT_NUMBER          = 0x1f,
        PARAM_CTRL_NUMBER            = 0x20,
        PARAM_DEVICE_STATUS          = 0x21,
        PARAM_MOBILE_OPERATOR        = 0x22,
        PARAM_AWS_NAME               = 0x23,
        PARAM_AWS_ADDR               = 0x24,
        PARAM_ROOT_CRT               = 0x25,
        PARAM_DEV_CRT                = 0x26,
        PARAM_PRI_KEY                = 0x27,
        PARAM_CLOUD_REPORT_PERIOD    = 0x28,
        PARAM_COLLECT_PERIOD         = 0x29,
        PARAM_OSH                    = 0x2a,
        PARAM_OSL                    = 0x2b,
        PARAM_AI_SETTING             = 0x2c,
        PARAM_AI_VALUE               = 0x2d,
        PARAM_MQTT_KEEPALIVE         = 0x2e,
        PARAM_MODBUS_CHAN_SET        = 0x2f,
        PARAM_MODBUS_GLOBAL_SET      = 0x30,
        PARAM_MODBUS_RULES           = 0x31,
        PARAM_NONCE_VALUE            = 0x32,
        PARAM_APN_SET                = 0x33,
        PARAM_USSD_ACK               = 0x34,
        PARAM_MQTT_SET               = 0x35,
        PARAM_DEV_DESC               = 0x36,
        PARAM_TCPUDP_SET             = 0x37,
        PARAM_TCPUDP_STATUS          = 0x38,
        PARAM_DEVICE_TIMESTAMP       = 0x39,
    #ifdef ODM_LHR_AZURE
        PARAM_AZURE_AUTH                        = 0x3A,
    #endif
        //35xx
        PARAM_ALI_PRODUCTKEY         = 0x40,
        PARAM_ALI_DEVICESECRET       = 0x41,
        PARAM_ALI_CLIENTID	         = 0x42,
        PARAM_ALI_QOS                = 0x43,
        PARAM_ALI_KEEPALIVE          = 0x44,
        PARAM_ALI_WLII				 = 0x45,
        PARAM_ALI_CFG                = 0x46,

        PARAM_LORA                   = 0x50,
        PARAM_HT_VALUE               = 0x51,
        PARAM_HT_ALARM               = 0x52,
        PARAM_GPIO_CFG               = 0x53,
        PARAM_AI_CHAN_SET            = 0x54,
        PARAM_AI_GLOBAL_SET          = 0x55,
        PARAM_AUTO_REPORT            = 0x56,
        PARAM_MODBUS_VALUE           = 0x57,
        PARAM_3V3_SET                = 0x58,
        PARAM_POWER_CTRL 			 = 0x59,
        PARAM_KEEP_PWR_STATE         = 0x5a,
        PARAM_DEVICE_STATE			 = 0x5b,
        PARAM_CLASSA_RESPONSE_TIME   = 0x5c,
        PARAM_REPORT_ENABLE_TYPE     = 0x5d,

        PARAM_GPIO_COUNTER           = 0x60,
        PARAM_TEMP_COMPENSATE        = 0x61,

        PARAM_INTELLIGENT_DISPLAY    = 0x62,
        PARAM_DISPLAY_MODE           = 0x63,
        PARAM_ABNORMAL_SET	         = 0x64,
        PARAM_CO2_CALIBRATE	         = 0x65,

        PARAM_UNP_VERSION            = 0x70,
        PARAM_UNXX_PRODUCTID,
        PARAM_UNXX_SN,
        PARAM_UNXX_HWVER,
        PARAM_UNXX_SWVER,
        PARAM_UNXX_PN                = 0x75,
        PARAM_UNXX_CHECK             = 0x76,
        PARAM_UNXX_REAL_PN           = 0x77,
        PARAM_UNXX_OEM               = 0x78,
        PARAM_UNXX_NB                = 0x79,
        PARAM_ONENET_CFG             = 0x7A
    } unp_param_t;

    typedef enum unp_comnct_e {
        COMNCT_UART,
        COMNCT_USSD,
        COMNCT_DATA,
        COMNCT_SMS,
        COMNCT_URSALINK_CLOUD,
        COMNCT_LORAWAN,
        COMNCT_LORA,
        COMNCT_NFC,
    } unp_comnct_t;

    typedef struct unp_ack_e {
        unp_pack_t type;
        unp_state_t state;
        uint8_t received;
        uint8_t params[UNP_MAX_PKTSIZE];
        uint16_t params_len;
    } unp_ack_t;

    typedef enum {
        UNP_MOBILE_POWEROFF,
        UNP_MOBILE_NOTREGISTER,
        UNP_MOBILE_REGISTERED,
        UNP_MOBILE_PIN_ERROR,
    } unp_mobile_state_t;


    typedef enum alarm_mode_e {
        ALARM_NONE = 0,
        ALARM_MODE_BELOW,
        ALARM_MODE_ABOVE,
        ALARM_MODE_WITHIN,
        ALARM_MODE_BELOW_ABOVE,
    } alarm_mode_t;

    #pragma pack(1)
    typedef struct alarm_rules_e {
        alarm_mode_t mode;
        int16_t max_value;
        int16_t min_value;
        uint16_t continue_time;
        uint16_t lock_time;
        uint8_t enable;
        int16_t max_value2;
        int16_t min_value2;
    } alarm_rules_t;
    #pragma pack()

    typedef struct abnormal_check_set_e{
        uint8_t enable;
        int16_t range;
        uint8_t percentage;
    }abnormal_check_set_t;

    typedef struct abnormal_check_patch_set_e{
        uint8_t percentage;
        uint8_t retry_count;
        uint8_t retry_interval;
        uint8_t reserved[8];
    }abnormal_check_patch_set_t;

    typedef struct application_set_am_e {
        uint16_t collect_cycle;
        uint16_t report_cycle;
        uint8_t intelligent_display;
        abnormal_check_set_t abnormal_check_set;
        uint8_t display_mode;
        abnormal_check_patch_set_t abnormal_check_patch_set;
    } application_set_am_t;

    typedef struct application_set_e {
        uint16_t collect_cycle;
        uint16_t report_cycle;
        uint8_t enable_3v3_out1;
        uint8_t enable_3v3_out2;
        uint8_t keep_pwr_state; //保持电源状态参数  2保持  3开机开阀  4开机关阀
        uint8_t pwr_state;              //电源状态，不用
        uint8_t connect_pwr;            //线开关机参数  0失能  1使能
        uint32_t classa_response_time;  //响应时间参数  10 ~ 6000
        uint8_t report_enable_type; //上报数据类型  0全上报  1上报1  2上报2
    } application_set_t;//6

    typedef struct product_id_e {
        uint8_t id[UNP_PRODUCT_ID_LEN];
        uint8_t name[UNP_PRODUCT_NAME_LEN + 1];
    } product_id_t;

    typedef enum {
        UNXX_GPIO_RISING = 0,
        UNXX_GPIO_FALLING,
        UNXX_GPIO_RISING_FALLING,
        UNXX_GPIO_TRIGER_HIGH,
        UNXX_GPIO_TRIGER_LOW,
        UNXX_GPIO_COUNTER,
    } unxx_gpio_intmode_t;

    typedef enum {
        UNXX_GPIO_LOW = 0,
        UNXX_GPIO_HIGH,
        UNXX_GPIO_PWM,
        UNXX_GPIO_FOLLOW,
        UNXX_GPIO_RESERVAL
    } unxx_gpio_outmode_t;

    typedef enum unxx_aimode_e{
        UNXX_AI_ABOVE,
        UNXX_AI_BELOW,
        UNXX_AI_WITHIN,
    } unxx_aimode_t;

    typedef enum unxx_mbmode_e{
        UNXX_MB_FALSE = 0,
        UNXX_MB_TRUE,
        UNXX_MB_ABOVE,
        UNXX_MB_BELOW,
        UNXX_MB_WITHIN,
    } unxx_mbmode_t;

    #define S_DIN_MASK     0x3ff
    #define S_ALARM_MASK   0x800
    #define S_SIGNAL_MASK  0x1000
    #define S_RESTART_MASK 0x2000
    #define S_AI_MASK      0xc000
    #define S_MB_MASK      0xff0000

    typedef enum event_source_e {
        S_IN_IO1_FALLING = 0,
        S_IN_IO1_RISING,
        S_IN_IO1_HIGH,
        S_IN_IO1_LOW,
        S_IN_IO1_CHANGE,
        S_IN_IO2_FALLING,
        S_IN_IO2_RISING,
        S_IN_IO2_HIGH,
        S_IN_IO2_LOW,
        S_IN_IO2_CHANGE,
        S_MSG,
        S_ALARM,
        S_SIGNAL_POOR,
        S_RESTART,
        S_AI1,
        S_AI2,
        S_MODBUS1,
        S_MODBUS2,
        S_MODBUS3,
        S_MODBUS4,
        S_MODBUS5,
        S_MODBUS6,
        S_MODBUS7,
        S_MODBUS8,
        S_IN_COUNTER1,    //新增计数器1事件
        S_IN_COUNTER2,    //新增计数器2事件
        S_MODBUSX2,       //与上S_MODBUS1到S_MODBUS8分别表示9-16通道
    } event_source_t;

    typedef enum event_dest_e {
        D_OUT_IO1 = 0,
        D_OUT_IO2,
        D_MSG,
        D_RESTART,
        D_CLOUD_ALARM
    } event_dest_t;

    typedef enum pn1_context_e {
        PN1_GPS = 0,
        PN1_POE,
        PN1_USSD,
        PN1_SMS,
        PN1_CLOUD,
        PN1_WORKNUM,
    } pn1_context_t;

    typedef enum app_mode_e {
        APP_NONE = 0,
        APP_USSD,
        APP_TCP,
        APP_UDP,
        APP_AWS,
        APP_URSALINK_CLOUD,
        APP_MQTT,
        APP_ALI,
        APP_ONENET,
        APP_AZURE

    } app_mode_t;

    typedef enum custom_ocet_e {
        CUSTOM_USSD_ENABLE   = (1 << 15),
        CUSTOM_SMS_ENABLE    = (1 << 14),
        CUSTOM_DATA_ENABLE   = (1 << 13),
        CUSTOM_AWS_ENABLE    = (1 << 12),
        CUSTOM_URUSSD_ENABLE = (1 << 11),
        CUSTOM_URAWS_ENABLE  = (1 << 10),
        CUSTOM_AZURE_ENABLE  = (1 << 9),
        CUSTOM_LORA_ENABLE   = (1 << 8),
    } custom_ocet_t;


    typedef enum context_type_e {
        PLAINTEXT,
        UCP
    } context_type_t;

    typedef enum sms_dcs_e {
        GSM_7BIT = 0,
        GSM_8BIT = 4,
        GSM_UCS2 = 8
    } sms_dcs_t;


    typedef enum cellular_network_e {
        CELLULAR_AUTO = 0,
        CELLULAR_4G_FIRST,
        CELLULAR_4G_ONLY,
        CELLULAR_3G_FIRST,
        CELLULAR_3G_ONLY,
        CELLULAR_2G_FIRST,
        CELLULAR_2G_ONLY,
    } cellular_network_t;

    typedef enum console_id_e {
        CONSOLE_UART_ID = 0,
        RS485_UART_ID,
        RS232_UART_ID,
        UART_MAX_ID
    } console_id_t;


    typedef enum calibrate_id_s {
            RESTORE_CAL = 0,
            ABC_CAL,
            TARGET_CAL,
            BACKGROUND_CAL,
            ZERO_CAL,
            CAL_ID_MAX
    } calibrate_id_t;

    typedef enum mode_type_s{
        mode_di = 0,
        mode_counter,
    } mode_type_t;

    typedef struct cellular_setting_e {
        cellular_network_t net_type;
        uint8_t sca[UNP_SCA_MAX_LENGTH + 1];
        uint8_t pin[UNP_PIN_MAX_LENGTH + 1];
        uint8_t sms_dcs;
        uint8_t apn[UNP_APN_MAX_LENGTH + 1];
    } cellular_setting_t;

    typedef struct app_mqtt_e {
        uint8_t mqtt_enable_tls;
        uint8_t mqtt_enable_auth;
        uint8_t broker_addr[64];
        uint8_t clientid[UNP_MQTT_CLIENTID_LEN + 1];
        uint8_t username[UNP_MQTT_USERNAME_LEN + 1];
        uint8_t password[UNP_MQTT_PASSWORD_LEN + 1];
        uint16_t broker_port;
        uint32_t connect_timeout;
        uint32_t keepalive;
    } app_mqtt_t;

    typedef struct app_cloud_e {
        uint32_t cloud_report_interval;
        uint32_t collection_cycle;
        uint32_t mqtt_keep_alive;
    #ifdef ODM_LHR_AZURE
        uint8_t azure_auth;
    #endif
    } app_cloud_t;

    typedef struct app_smsussd_e {
        context_type_t context_type;
        uint8_t ctrl_by_sms;
        uint8_t report_by_sms;
        uint8_t succ_report;
        uint8_t fail_report;
        uint8_t change_report;
        uint32_t report_interval;
        uint8_t report_number[UNP_REPORT_NUM_MAX_CNT][UNP_NUM_MAX_LEN];
        uint8_t ctrl_number[UNP_CTRL_NUM_MAX_CNT][UNP_NUM_MAX_LEN];
        uint8_t ussd_prefix[UNP_USSD_PREFIX_MAX_LEN];
    } app_smsussd_t;

    typedef struct app_tcpudp_e {
        uint8_t keepalive_interval;   //fenzhong
        uint8_t enable_custom_heartbeat;
        uint8_t custom_heartbeat_need_ack;
        uint8_t custom_heartbeat[64];
        uint8_t server_ack[64];
        uint16_t custom_heartbeat_interval;
        uint16_t server_port[UNP_TCP_SERVER_NUM];
        uint8_t server_ip[UNP_TCP_SERVER_NUM][4];
        uint8_t server_name[UNP_TCP_SERVER_NUM][UNP_SERVER_IP_LEN];

    } app_tcpudp_t;

    typedef struct ucxx_application_e {
        app_mode_t mode;
        app_smsussd_t app_smsussd;
        app_cloud_t app_cloud;
        app_mqtt_t app_mqtt;
        app_tcpudp_t app_tcpudp;

        uint8_t change_report;
        uint8_t succ_report;
        uint8_t fail_report;
        uint32_t report_interval;
        context_type_t context_type;
        uint32_t cloud_report_interval;
        uint32_t collection_cycle;
        uint32_t mqtt_keep_alive;
    } ucxx_application_t;


    typedef enum serial_mode_e {
        MODBUS_MASTER = 0,
        DTU,
    } serial_mode_t;

    typedef enum ai_mode_e {
        CURRENT_MODE = 0,
        VOLTAGE_MODE,
    } ai_mode_t;

    typedef enum serial_protocol_e {
        SERIAL_TCP = 0,
        SERIAL_UDP,
        SERIAL_TCP_SERVER,
        SERIAL_UDP_SERVER
    } serial_protocol_t;

    typedef enum {
        MB_REG_COIL,
        MB_REG_DIS,
        MB_REG_INPUT,

        MB_REG_HOLD_INT16,
        MB_REG_HOLD_INT32,
        MB_REG_HOLD_FLOAT,

        MB_REG_INPUT_INT32,
        MB_REG_INPUT_FLOAT,

        MB_REG_INPUT_INT32_AB,
        MB_REG_INPUT_INT32_CD,
        MB_REG_HOLD_INT32_AB,
        MB_REG_HOLD_INT32_CD,
    } modbus_reg_t;

    typedef struct modbus_channel_set_e {
        uint8_t enable;
        uint8_t slaveid;
        uint8_t quantity;
        uint8_t type;//modbus_reg_t
        uint8_t sign;
        uint8_t decimal;
        uint16_t address;
        uint8_t name[UNP_MODBUS_NAME_MAX_LEN];
    } modbus_channel_set_t;

    typedef struct modbus_global_set_e {
        uint16_t exec_interval;
        uint16_t max_res_time;
        uint16_t retrytimes;
        uint16_t collect_interval;
        uint16_t poweron_time;
        uint8_t pass_through_enable;
        uint8_t pass_through_port;
        uint8_t power_enable;
    } modbus_global_set_t;

    typedef struct modbus_setting_e {
        modbus_global_set_t global;
    #if UNXX_MAX_MODBUS_CHAN > 0
        modbus_channel_set_t chan[UNXX_MAX_MODBUS_CHAN];
    #endif
    } modbus_setting_t;

    typedef struct ai_global_set_e {
        uint16_t collect_interval;
        uint16_t poweron_time;
        uint8_t power_enable;
    } ai_global_set_t;

    typedef struct ai_channel_set_e {
        uint8_t enable;
        uint8_t mode;//ai_mode_t 0表示4~20mA，1表示0~10V
    } ai_channel_set_t;

    typedef struct ai_settting_e {
        ai_global_set_t global;
        ai_channel_set_t chan[UNXX_MAX_AI_NUM];
    } ai_setting_t;

    typedef enum gpio_type_e {
        GPIO_INPUT = 0,
        GPIO_OUTPUT,
        GPIO_COUNTER,
    } gpio_type_t;

    #pragma pack(1)
    typedef struct io_setting_e {
        uint8_t enable;
        uint8_t type; //gpio_type_t
        uint8_t pull;
        uint8_t save_counter;
        uint8_t filter;
    } io_setting_t;
    #pragma pack()

    typedef struct modbus_rules_e {
        unxx_mbmode_t mode;
        uint32_t continue_time;
        uint32_t lock_time;
        float high_value;
        float low_value;
    } modbus_rules_t;

    struct serial_server_address {
        uint8_t ip[UNP_DTU_SERVER_NUM][5];
        uint16_t port[UNP_DTU_SERVER_NUM];
        uint8_t name[UNP_DTU_SERVER_NUM][UNP_SERVER_IP_LEN];
    };
    #pragma pack(1)
    struct serial_app {
        uint8_t mode;
        uint8_t enable;
        serial_protocol_t protocol;
        uint16_t idle_time;
        uint16_t interval_time;
        uint16_t probe_cnt;
        uint16_t bytes_per_frame;
        uint16_t interval_per_frame;
        struct serial_server_address destination;
        uint8_t register_packet[UNP_DTU_REG_PACKET_LEN];
        //1152 rs485 bridge lorawan
        uint8_t pass_through_enable;
        uint8_t pass_through_port;
    };
    #pragma pack()
    struct console_param {
        uint32_t baud;
        uint8_t databits;
        uint8_t stopbits;
        uint8_t parity;
        uint8_t flow;
        struct serial_app app;
    };

    struct io_trigger_condition {
        unxx_gpio_intmode_t mode;
        uint32_t jitter_time;
        uint32_t lock_time;
    };

    //#pragma anon_unions
    struct io_trigger_action {
    #ifdef USE_IN_STM32
        GPIO_PinState powon_value;
    #endif
        unxx_gpio_outmode_t mode;
        uint32_t delay_time;
        uint32_t continue_time;
        uint32_t pwm_num;
        uint32_t low_time;
        uint32_t high_time;
    };

    struct ai_trigger_condition {
        unxx_aimode_t mode;
        uint32_t continue_time;
        uint32_t lock_time;
        float high_value;
        float low_value;
    };

    struct ai_config {
        float osh;
        float osl;
        struct ai_trigger_condition ai_condition[UNXX_MAX_WORKNUM];
    };

    struct io_config {
        struct io_trigger_condition condition;
        struct io_trigger_action action;
    };

    struct msg_config {
        uint8_t enable;
        uint8_t condition[UNP_MSG_MAX_LENGTH];
        uint8_t action[UNP_MSG_MAX_LENGTH];
    };

    #pragma pack(1)
    typedef struct unxxtime_e {
        uint8_t sec;
        uint8_t min;
        uint8_t hour;
        uint8_t date;
        uint8_t month;
        uint16_t year;
        uint8_t weekday;
    } unxxtime_t;
    #pragma pack()
    struct clock {
        uint8_t enable;
        unxxtime_t alarm;
    };

    typedef struct device_status_e {
        uint8_t battery;
        uint8_t joinstate;
        uint8_t power_state;
        int8_t snr;
        int16_t rssi;
        uint32_t uplink_counter;
        uint32_t downlink_counter;
        uint16_t chanmask[7];
    } device_status_t;

    typedef struct uc11t1_temphumi_e {
        uint8_t humi;
        int16_t temp;
        uint8_t humi_origin;
        int16_t temp_origin;
    } uc11t1_temphumi_t;


    typedef struct work_event_e {
        uint8_t msg_active;
        uint8_t alarm_active;
        uint8_t poor_signal_active;
    } work_event_t;

    struct unxx_work {
        uint8_t id;
        uint8_t active;
        uint8_t and_or;
        uint32_t event_source_or/* = UNXX_GET_EVENT(S_IN_IO1) | UNXX_GET_EVENT(S_IN_IO2)*/;
        uint32_t event_source_and ;
        uint32_t event_destnation;
    #ifdef USE_IN_STM32
        struct list_head list;
    #endif
    };


    typedef struct unxx_magic {
        uint8_t magic[10];
        uint8_t reset_report;
    } unxx_magic_t;
    #pragma pack(1)
    typedef struct product_info_e {
        uint8_t productid[UNP_PRODUCT_ID_LEN + 1];
        uint8_t series[UNP_SERIES_LEN + 1];
        uint8_t productsn[UNP_PRODUCT_SN_LEN2 + 1];
        uint8_t hwver[UNP_HWVER_LEN + 1];
        uint8_t swver[UNP_SWVER_LEN + 1];
        uint8_t nonce[UNP_NONCE_LEN + 1];
        uint8_t is_first_program;
        uint8_t ucp_version;
        uint8_t productid_em[UNP_PRODUCT_ID_LEN_EM+1];
    } product_info_t;
    #pragma pack()
    typedef struct pn_info_e {
        uint8_t custom[UNP_CUSTOM_LEN + 1];
        uint8_t region[UNP_REGION_LEN + 1];
        uint8_t pn[UNP_PN_NUM][UNP_PN_LEN + 1];
        uint8_t pn_em[UNP_PN_NUM][UNP_PN_LEN_EM + 1];
    //    uint8_t real_pn[UNP_PN_NUM][UNP_PN_LEN_EM + 1];
    } pn_info_t;

    typedef struct sensor_cfg_s {//01 00 01 00f8 ff 00 0000000000000000 00 01000
            uint8_t enable;
            uint8_t unit;
            uint8_t calibration_enable;
            int16_t calibration_value;
            uint8_t auto_report_enable;
            uint8_t auto_report_diff;
            int16_t calibration_value2;
            uint16_t alarm_value;
            uint8_t alarm_enable;
            int8_t reserved[3];
    } sensor_cfg_t;

    /* AM102、AM100/EM500-CO2：temperature/humi/pir/als/co2/dpr/tvoc
     * EM500-MEC20: temp/humi/conductivity
     *
    */
    typedef struct user_config_e {
            sensor_cfg_t sensor1;//EM
            sensor_cfg_t sensor2;
            sensor_cfg_t sensor3;
            sensor_cfg_t sensor4;
            sensor_cfg_t sensor5;
            sensor_cfg_t sensor6;
            sensor_cfg_t sensor7;
    } user_config_t;

    typedef struct sensor_status_a {
        int16_t opt1;//10
        int16_t opt2;//2
        uint16_t opt3;
        uint16_t opt4;
        uint16_t opt5;
        uint16_t opt6; //10
        uint16_t opt7;
    } sensor_status;

    typedef struct sensor_status_e {
        int32_t opt1;//10
        int32_t opt2;//2
        int32_t opt3;
        int32_t opt4;

    } sensor_status_em;

    #pragma pack(1)
    typedef struct alarm_params_e {
        alarm_rules_t rules[UNP_MAX_RULES_NUM];
        sensor_cfg_t sensor_cfg;
    } alarm_params_t;//10
    #pragma pack()

    typedef struct uc3x_device_param_e {
        uint8_t name[UNP_DEVNAME_LEN + 1];
        uint8_t password[UNP_PASSWD_LEN + 1];
        uint8_t debug;
        uint8_t delimiter;
        struct console_param con_param[UART_MAX_ID];
        uint8_t desc[UNP_DEVDESC_LEN + 1];
    } uc3x_device_param_t;

    //N1 NFC
    #pragma pack(1)
    typedef struct device_param_e {
        uint8_t name[UNP_PRODUCT_SN_LEN + 1];
        uint8_t password[UNP_PASSWD_LEN + 1];
        uint8_t debug;
        uint8_t change_battery;
        uint8_t abort_reboot;
        uint8_t device_state;
        uint32_t timestamp;
        int16_t timezone;
        struct console_param con_param[UART_MAX_ID];
    } device_param_t;//228
    #pragma pack()

    typedef struct uc3x_user_config {
        struct io_config input[UNXX_MAX_WORKNUM][UNXX_MAX_INPUT_IO_NUM];
        struct io_config output[UNXX_MAX_WORKNUM][UNXX_MAX_OUTPUT_IO_NUM];
        struct msg_config msg[UNXX_MAX_MSGNUM];
        struct clock clock[UNXX_MAX_CLOCK];
        struct ai_config ai[UNXX_MAX_AI_NUM];

        modbus_setting_t modbus;
        modbus_rules_t mb_rules[UNXX_MAX_WORKNUM][UNXX_MAX_MODBUS_CHAN];

        io_setting_t gpio[UNXX_MAX_GPIO_NUM];
        ai_setting_t ai_t1n1;

    } uc3x_user_config_t;

    typedef struct user_work {
        struct unxx_work work[UNXX_MAX_WORKNUM];
    } user_work_t;

    typedef struct status_message {
        unxxtime_t local_time;
        uint8_t gsm_status;
        uint8_t signal;
        uint8_t input_status[UNXX_MAX_INPUT_IO_NUM];
        uint8_t output_status[UNXX_MAX_OUTPUT_IO_NUM];
    } status_message_t;

    typedef enum Qos {
        QOs0 = 0,
        QOs1 = 1,
        QOs2 = 2,
    } Qos;

    typedef struct unxx_ali_will_cfg {
        uint8_t will_flag;
        Qos will_qos;
        uint8_t will_topic[64];
        uint8_t will_message[64];
    } unxx_ali_will_cfg;

    typedef struct counter_config{
        mode_type_t mode;
        uint8_t start;
        uint32_t total_value;
        uint32_t report_value;
        uint32_t alarm_value[UNXX_MAX_WORKNUM];
    }counter_config_t;

    #pragma pack(1)
    typedef struct unxx_ali_setting_t {
        Qos qos;
        uint16_t keepalive;
        uint8_t ali_clientID[32];
        uint8_t ali_ProductKey[32];
        uint8_t ali_DeviceSecret[64];
    } unxx_ali_setting_t;
    #pragma pack()

    #pragma pack(1)
    typedef struct unxx_onenet_setting_t {
        uint8_t  qos;
        uint16_t keepalive;
        uint8_t productID[32];        //设备所属产品的产品ID
        uint8_t key[64];                        //设备的key
    } unxx_onenet_setting_t;
    #pragma pack()

    typedef struct device_msg{
        pn_info_t *pn_msg;
        product_info_t *pro_msg;
        uint8_t *DevEui;
        uint8_t *device_state;
     }device_msg_t;

    typedef struct update_time{
        int tm_sec;   /* seconds after the minute, 0 to 60(0 - 60 allows for the occasional leap second) */
        int tm_min;   /* minutes after the hour, 0 to 59 */
        int tm_hour;  /* hours since midnight, 0 to 23 */
        int tm_mday;  /* day of the month, 1 to 31 */
        int tm_mon;   /* months since January, 0 to 11 */
        int tm_year;  /* years since 1900 */
        int tm_wday;
     }update_time_t;

    typedef struct status_msg{
        device_status_t uc11t1_status;
        uint32_t timpstamp;
        uint32_t data[8];//EM的全部是data[0]
     }status_msg_t;


    explicit QunpUCXX52(QObject *parent = nullptr);

    QString get_sms_cmd_txt();
    void set_sms_cmd_flag(bool flag);
    void set_only_ucp_flag(bool flag);
    unp_state_t unp_set_io_condition(uint8_t worknum, uint8_t num, struct io_trigger_condition *io_condition);
    unp_state_t unp_get_io_condition(uint8_t worknum, uint8_t num, struct io_trigger_condition *io_condition);
    unp_state_t unp_set_io_action(uint8_t worknum, uint8_t gpionum, struct io_trigger_action *io_action);
    unp_state_t unp_get_io_action(uint8_t worknum, uint8_t gpionum, struct io_trigger_action *io_action);
    unp_state_t unp_set_user_work(uint8_t num, struct unxx_work *userwork);
    unp_state_t unp_get_user_work(uint8_t num, struct unxx_work *userwork);
    unp_state_t unp_set_msg_condition(uint8_t num, uint8_t *context);
    unp_state_t unp_get_msg_condition(uint8_t num, uint8_t *out);
    unp_state_t unp_set_msg_action(uint8_t num, uint8_t *context);
    unp_state_t unp_get_msg_action(uint8_t num, uint8_t *out);
    unp_state_t unp_set_alarm_clock(uint8_t num, struct clock *alarmclock);
    unp_state_t unp_get_alarm_clock(uint8_t num, struct clock *alarmclock);
    unp_state_t unp_set_ai_condition(uint8_t worknum, uint8_t num, struct ai_trigger_condition *condition);
    unp_state_t unp_get_ai_condition(uint8_t worknum, uint8_t num, struct ai_trigger_condition *condition);
    unp_state_t unp_set_modbus_rules(modbus_rules_t *rules, uint8_t worknum, uint8_t num);
    unp_state_t unp_get_modbus_rules(modbus_rules_t *rules, uint8_t worknum, uint8_t num);

    bool initSerialPort(SerialInfo s);
    void close_serialport();
    bool reopen_serialport();
    int deal_with_unp(uint8_t *data, uint32_t len, unp_comnct_t type);
    int unp_send_passwd(uint8_t *passwd, uint16_t len);
    int unp_get_product_name(uint8_t *name);
    int unp_get_product_pn(uint8_t *pn);
    unp_state_t unp_connect_device(void);
    unp_state_t unp_get_version(uint8_t *version);
    unp_state_t unp_reset_device();
    unp_state_t unp_send_reboot_request(void);
    unp_state_t unp_set_lora_reload_config();
    unp_state_t unp_send_upgrade_request(void);
    unp_state_t unp_upgrade_check(uint32_t crc32, uint8_t *productid, uint8_t *hwver, uint8_t *swver, uint8_t *pn, int imageVer);
    unp_state_t unp_send_upgrade_image(uint8_t *data, uint32_t datasize);
    unp_state_t unp_upgrade_complete(void);
    unp_state_t unp_set_passwd(uint8_t *old_passwd, uint8_t *new_passwd);
    unp_state_t unp_get_product_hwver(uint8_t *hwver);
    unp_state_t unp_get_product_swver(uint8_t *swver);
    unp_state_t unp_get_product_sn(uint8_t *sn);
    unp_state_t unp_get_oem(uint8_t *oem);
    unp_state_t unp_get_product_real_pn(uint8_t *pn);
    unp_state_t unp_get_lora_status(uint32_t dataoffset, uint32_t datasize, uint8_t *out);
    unp_state_t unp_get_lora(uint32_t dataoffset, uint32_t datasize, uint8_t *out);
    unp_state_t unp_set_lora(uint8_t value, uint8_t valueoffset);
    unp_state_t unp_set_lora(uint8_t *value, uint8_t valueoffset, uint16_t datasize);
    unp_state_t unp_set_lora(uint32_t value, uint8_t valueoffset, uint16_t datasize);
    unp_state_t unp_get_device_status(device_status_t *status);
    unp_state_t unp_get_device_time(uint32_t *timestamp, int16_t *timezone);
    unp_state_t unp_get_sensor_data(sensor_status_em *temphumi);
    unp_state_t unp_get_collect_cycle(uint32_t *cycle);
    unp_state_t unp_set_collect_cycle(uint32_t cycle);
    unp_state_t unp_get_cloud_cycle(uint32_t *cycle);
    unp_state_t unp_set_cloud_cycle(uint32_t cycle);
    unp_state_t unp_get_sensor_cfg(user_config_t *sensors_cfg);
    unp_state_t unp_set_sensor_cfg(user_config_t *sensors_cfg);
    unp_state_t unp_get_abnormal_set(abnormal_check_set_t * abnormal, abnormal_check_patch_set_t *abnormal_patch);
    unp_state_t unp_set_abnormal_set(abnormal_check_set_t * abnormal, abnormal_check_patch_set_t *abnormal_patch);
    unp_state_t unp_get_alarm(uint8_t num, alarm_rules_t *alarmconfig);
    unp_state_t unp_set_alarm(uint8_t num, alarm_rules_t *alarmconfig);
    unp_state_t unp_set_product_pn(uint8_t *pn);
    unp_state_t unp_get_uc11t1_data(uc11t1_temphumi_t *temphumi);
    unp_state_t unp_get_temp_humi_compensate(uint8_t *temp_enable, int16_t *temp_value, uint8_t *humi_enable, int16_t *humi_value);
    unp_state_t unp_set_temp_humi_compensate(uint8_t temp_enable, int16_t temp_value, uint8_t humi_enable, int16_t humi_value);
    unp_state_t unp_set_uc11t1_alarm(uint8_t num, alarm_rules_t *alarmconfig);
    unp_state_t unp_get_uc11t1_alarm(uint8_t num, alarm_rules_t *alarmconfig);
    unp_state_t unp_get_enable_auto_report(uint8_t *state);
    unp_state_t unp_set_enable_auto_report(uint8_t state);
    unp_state_t unp_get_mobile_state(unp_mobile_state_t *state);
    unp_state_t unp_get_mobile_signal(uint8_t *signal);
    unp_state_t unp_get_inputio_status(uint8_t gpionum, uint8_t *value);
    unp_state_t unp_get_outputio_status(uint8_t gpionum, uint8_t *value);
    unp_state_t unp_set_current_time(unxxtime_t *cur);
    unp_state_t unp_get_current_time(unxxtime_t *cur);
    unp_state_t unp_get_app_mode(app_mode_t *mode);
    unp_state_t unp_set_app_mode(app_mode_t mode);
    unp_state_t unp_set_mqtt_keepalive(uint32_t keepalive);
    unp_state_t unp_get_mqtt_keepalive(uint32_t *keepalive);
    unp_state_t unp_get_mobile_apn(uint8_t *apn, uint8_t *username, uint8_t *password);
    unp_state_t unp_set_mobile_apn(uint8_t *apn, uint8_t *username, uint8_t *password);
    unp_state_t unp_get_mobile_apn(uint8_t *apn);
    unp_state_t unp_get_prikey(uint8_t *data, uint16_t datasize);//私钥 key file
    unp_state_t unp_set_update_prikey(uint8_t *data, uint16_t datasize);
    unp_state_t unp_get_devcrt(uint8_t *data, uint16_t datasize);//设备证书 certificate
    unp_state_t unp_set_update_devcrt(uint8_t *data, uint16_t datasize);
    unp_state_t unp_get_rootcrt(uint8_t *data, uint16_t datasize);//根证书 CA
    unp_state_t unp_set_update_rootcrt(uint8_t *data, uint16_t datasize);
    unp_state_t unp_get_endpoint_addr(uint8_t *addr);
    unp_state_t unp_set_endpoint_addr(uint8_t *addr);
    unp_state_t unp_get_endpoint_name(uint8_t *name);
    unp_state_t unp_set_endpoint_name(uint8_t *name);
    unp_state_t unp_get_device_desc(uint8_t *desc);
    unp_state_t unp_set_device_desc(uint8_t *desc);
    unp_state_t unp_get_tcpudp_config(app_tcpudp_t *tcpudp_set);
    unp_state_t unp_set_tcpudp_config(app_tcpudp_t *tcpudp_set);
    unp_state_t unp_set_mqtt_config(app_mqtt_t *mqtt_set);
    unp_state_t unp_get_mqtt_config(app_mqtt_t *mqtt_set);
    unp_state_t unp_set_onenet_config(unxx_onenet_setting_t *mqtt_set);
    unp_state_t unp_get_onenet_config(unxx_onenet_setting_t *onenet_get);
    unp_state_t unp_set_ali_cfg(unxx_ali_setting_t *ali_cfg);
    unp_state_t unp_get_ali_cfg(unxx_ali_setting_t *ali_cfg);
    unp_state_t unp_get_cellular_pin(uint8_t *pin);
    unp_state_t unp_set_cellular_pin(uint8_t *pin);
    unp_state_t unp_get_cellular_sca(uint8_t *sca);
    unp_state_t unp_set_cellular_sca(uint8_t *sca);
    unp_state_t unp_get_cellular_net_type(cellular_network_t *value);
    unp_state_t unp_set_cellular_net_type(cellular_network_t value);
    unp_state_t unp_get_sms_dcs(sms_dcs_t *code);
    unp_state_t unp_set_sms_dcs(sms_dcs_t code);
    unp_state_t unp_get_tcpudp_status(uint8_t *state);
    unp_state_t unp_get_osl(uint8_t num, float *osl);
    unp_state_t unp_set_osl(uint8_t num, float osl);
    unp_state_t unp_get_osh(uint8_t num, float *osh);
    unp_state_t unp_set_osh(uint8_t num, float osh);
    unp_state_t unp_get_ai_value(uint8_t num, float *current, float *usrdata);
    unp_state_t unp_get_11xx_gpio_counter(uint8_t gpionum, uint8_t *mode, uint8_t *start, uint32_t *value);
    unp_state_t unp_get_gpio_counter(uint8_t gpionum, uint32_t *value, uint8_t *start);
    unp_state_t unp_set_gpio_counter(uint8_t gpionum, uint32_t value);
    unp_state_t unp_get_dtu(uint8_t *status, uint8_t *size);
    unp_state_t unp_set_uartcfg(struct console_param *uartcfg, uint8_t id, uint8_t new_version);
    unp_state_t unp_get_uartcfg(struct console_param *uartcfg, uint8_t id);
    unp_state_t unp_set_modbus_chan_cfg(modbus_channel_set_t *chan_cfg, uint8_t num);
    unp_state_t unp_get_modbus_chan_cfg(modbus_channel_set_t *chan_cfg, uint8_t num);
    unp_state_t unp_set_modbus_global_cfg(modbus_global_set_t *global_cfg);
    unp_state_t unp_get_modbus_global_cfg(modbus_global_set_t *global_cfg);
    unp_state_t unp_get_modbus_value2(uint8_t channum, modbus_channel_set_t *channel_set, uint8_t *value, uint16_t *size);
    unp_state_t unp_get_modbus_value(uint8_t channum, modbus_channel_set_t *channel_set, uint8_t *value, uint16_t *size);
    unp_state_t unp_get_modbus_value(uint8_t channum, uint8_t *value, uint16_t *size);

    void set_comnct_type(unp_comnct_t g_comnct_type_tmp);
signals:
    void getImageSize(uint32_t pktsize);

private:
    QSerialPort         *m_port;
    QString             sms_command;
    QString             m_product;
    QString             m_pn;
    QString             m_oem;
    int                 serialMaxTimeout;
    bool                m_ackFlag;
    bool                onlyUcp;
    bool                save_sms_command;
    uint8_t             passwd_verify_success ;

    unp_ack_t           g_unp_ack;
    unp_comnct_t        g_comnct_type;
    status_msg_t        *pStatus;
    user_config_t       *pUserConfig;
    flash_flag_t        *pFlash_flag;
    product_info_t      *pProductInfo;
    pn_info_t           *pPNInfo;
    unxx_magic_t        *pUNxxMagic;
    device_param_t      *pDeviceParam;
    alarm_params_t      *pAlarmParams;
    application_set_t   *pApplication;
    application_set_am_t *pApplication_am;
    LoRaWANParams_t 	 *pLoRaWANParams;
    LoRaWANParams_t 	 default_LoRaWANParams;
    uc11t1_temphumi_t    g_uc11t1_data;
    modbus_global_set_t  modbus_global;
    modbus_channel_set_t modbus_channel;

    void unp_delay(uint32_t ms);
    unp_state_t wait_for_ack(void);
    uint8_t unp_verify(void);
    uint16_t generate_pkt(uint8_t *data, uint16_t datasize, uint8_t *pkt, unp_pack_t type);
    uint8_t unp_frame_split(uint8_t *data, uint16_t datasize, uint16_t *pos, uint16_t *len);
    void unp_set_ussd_ack(uint8_t *data, uint16_t datasize);
    unp_state_t send_read_param_request(uint8_t *out, uint8_t *in, uint16_t insize);
    unp_state_t send_write_param_request(uint8_t *data, uint16_t datasize);
    unp_state_t write_device_params(uint8_t *data, uint16_t datasize);
    uint16_t read_device_params(uint8_t *params, uint8_t *data);
    QString hexToString(uint8_t *in,int len);

    void read_serialport_data();
    void unp_send_pkt(uint8_t *data, uint16_t pktsize);
    void deal_passwd_input(uint8_t *data, uint16_t datasize);
    void deal_reboot(void);
    void deal_upgrade(uint8_t *data, uint16_t datasize);
    void deal_read_param(uint8_t *data, uint16_t len);
    void deal_write_param(uint8_t *data, uint16_t len);
    void deal_reload_config_dev(uint8_t *data, uint16_t datasize);
    void deal_passwd_input_ack(uint8_t *data, uint16_t datasize);
    void deal_reboot_ack(void);
    void deal_upgrade_ack(uint8_t *buffer, uint16_t datasize);
    void deal_read_param_ack(uint8_t *data, uint16_t len);
    void deal_write_param_ack(uint8_t *data, uint16_t len);
    void deal_connect_dev(uint8_t *data, uint16_t datasize);
    void deal_connect_dev_ack(uint8_t *data, uint16_t datasize);
    void deal_reload_config_dev_ack(uint8_t *data, uint16_t datasize);
    void deal_reset_dev(uint8_t *data, uint16_t datasize);
    void deal_reset_dev_ack(uint8_t *data, uint16_t datasize);
    void deal_dtu_status(uint8_t *data, uint16_t datasize);
    void deal_lorawan_reload_ack(uint8_t *data, uint16_t datasize);

    void get_device_sn(uint8_t *data);
    void get_device_passwd(uint8_t *data);
    void get_device_appkey(uint8_t *data);
    void get_productid(uint8_t *data);
    void get_device_hwver(uint8_t *data);
    void set_device_swver(uint8_t *data);
    void get_device_name(uint8_t *data);
    void set_upgrade_flag(uint8_t *buf);
    void get_device_pn(uint8_t *data);
    void get_device_pn_em(uint8_t *data);
    void get_device_oem(uint8_t *data);
    void get_device_real_pn(uint8_t *data);
    void get_device_custom(uint16_t *value);
    void get_upgrade_flag(uint8_t *buf);
    void get_upgrade_info(uint8_t *flag, uint32_t *crc32, uint32_t *size);
    void set_upgrade_info(uint8_t flag, uint32_t crc32, uint32_t size);
    void write_data_to_flash(uint32_t *data, uint16_t len_bytes, uint32_t addr);
    void read_data_from_flash(uint32_t *data, uint16_t len_bytes, uint32_t addr, uint8_t fromisr);
    void write_image_to_flash(uint32_t *data, uint16_t len_bytes, uint32_t addr);
    void set_upgrade_enable_flag(uint8_t upgrade_enable);
    void unxx_reset_device(void);
    void unxx_restart_device(void);
};

#endif // QUNPUCXX52_H
