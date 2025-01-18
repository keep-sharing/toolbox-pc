#ifndef __UNXX_PARAMS_H__
#define __UNXX_PARAMS_H__

//#define UNXX_MAGIC              "UC11N1"
#define UNXX_LORA_APP_PORT      0x55
#define UNXX_LORA_DTU_PORT      0x56

#define ERROR_INPUT "border:2px solid rgb(225,0,0);font-size:13px;font-family:'Arial'"
#define ERROR_INPUT2 "background-color: rgb(255, 255, 255);border:2px solid rgb(225,0,0);font-size:13px;font-family:'Arial'"
#define RECOVERY_INPUT "QLineEdit\n{\n	background-color:#ffffff;\n	border: 1px solid #a1a1a1;font-size:13px;font-family:'Arial'\n}\n\nQLineEdit:hover\n{\n	border: 1px solid rgb(58, 65, 70);\n}\nQLineEdit:focus\n{\n	 border: 1px solid rgb(94, 154, 234);\n}"
#define TYPEFACE_GREEN "color: green;font-size:13px;font-family:'Arial'"
#define TYPEFACE_RED "color: red;font-size:13px;font-family:'Arial'"

#include <QSerialPort>
#include <QThread>
#include <QDebug>
#include <QVariant>
#include <QApplication>
#include <QSettings>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "myControl/mymessagebox.h"
#include "basicmethod.h"
#include "version.h"

typedef enum {
    PN532_WAKE_UP 				= 0x14,
    PN532_WAKE_UP_ACK 			= 0x15,
    PN532_CHECK 				= 0x4a,
    PN532_CHECK_ACK				= 0x4b,
    PN532_SEND					= 0x42,
    PN532_SEND_ACK				= 0x43,
    PN532_SET_FREE				= 0x52,
    PN532_SET_FREE_ACK			= 0x53,
}pn532_type;

typedef enum {
    NFC_READ_PKT                = 0x01,
    NFC_WRITE_PKT               = 0x02,
}nfc_pack_t;

typedef enum {
    NFC_READ_STATUS             = 0x01,
    NFC_READ_FLASH              = 0x02,
    NFC_READ_PASSWORD           = 0x03,
    NFC_READ_APPKEY             = 0x04,
    NFC_READ_DEVICE             = 0x05,
    NFC_READ_FETCH              = 0x06,
    NFC_READ_SELF_CHECK         = 0x07,
    NFC_READ_COUNTER_CTRL       = 0x08,
}nfc_read_pkt;

typedef enum {
    NFC_WRITE_FLASH             = 0x01,
    NFC_WRITE_POWEN_ON          = 0x02,
    NFC_WRITE_POWEN_OFF         = 0x03,
    NFC_WRITE_UPGARDE_REQUEST   = 0x04,
    NFC_WRITE_UPGARDE_QUERY     = 0x05,
    NFC_WRITE_OP_COMPLETE       = 0x06,
    NFC_WRITE_DEVICE_RESET      = 0x07,
    NFC_WRITE_PASSWORD          = 0x08,
    NFC_WRITE_APPKEY            = 0x09,
    NFC_WRITE_LORA_RELOAD       = 0x0A,
    NFC_WRITE_DEVICE_RESTART    = 0x0B,
    NFC_WRITE_TIMESTAMP			= 0x0C,
    NFC_WRITE_CO2_CALIBRATE     = 0x0D,
    NFC_WRITE_COLLECT_REQUEST   = 0x0E,
    NFC_WRITE_GPIO_STATUS       = 0x0F,
    NFC_WRITE_CALIBRATION       = 0x10,
    NFC_WRITE_COUNTER_CTRL      = 0x11,
    NFC_WRITE_SOLENOID_STATUS   = 0x12,
}nfc_write_pkt;


enum EnumOEM{
    OEM_LINKWAN = 1,
    OEM_LUKASZ  = 2 //N1 485支持20通道
};

enum EnumUpgradeError{
    RequestError = -1,
    UpgradeOK    = -2,
    FileOpenFail = -3,
    SpaceError   = -4,
    FileOpenFail1= -5,
    ResetOK      = -6,
    ResetFail    = -7,
    UpgradePassword= -8
};

#pragma pack(1)
typedef struct flash_user_params{
    uint8_t status[128];
    uint8_t flash[1024+256];
    uint32_t crc;
    uint8_t device_type;
    uint8_t device_cmd; //0:不操作  1：lora reload  2:restart  3:reset
}flash_user_params_t;//FLASH_USER_PARAMS_SIZE
#pragma pack()

struct SerialInfo{
    QString portName;
    int connectionTimeout;
    QSerialPort::BaudRate baudrate;
    QSerialPort::DataBits databit;
    QSerialPort::Parity paritybit;
    QSerialPort::StopBits stopbit;
    QString loginPwd;
    int type;
};

typedef enum {
    UNP_SUCCESS = 0,
    UNP_FAIL,
    UNP_FLAG_ERROR,
    UNP_LEN_ERROR,
    UNP_TYPE_ERROR,
    UNP_VERITY_ERROR,
    UNP_TIMEOUT_ERROR,
    UNP_PASSWORD_ERROR
} unp_state_t;

typedef enum params_lock{
	PARAMS_LOCK   = 0x55,
	PARAMS_UNLOCK = 0,
}params_lock_t;

typedef enum ack_mask_e {
	ALARM_PKT_ACK_MASK   = 0x01,
	REGULAR_PKT_ACK_MASK = 0x02,
	
	FORCE_PKT_ACK_MASK   = 0x80,
}ack_mask_t;

#pragma pack(1)
typedef struct LoRaWANParams_e {
    uint8_t mode;				// 0: CLASS_A, 1:CLASS_B, 2:CLASS_C
	uint8_t ota;				//  0: OTA, 1: ABP
	uint8_t adr;				//  0: OFF, 1: ON
	uint32_t NetID;
	uint32_t DevAddr;
	uint8_t DevEui[8];
	uint8_t AppEui[8];
	uint8_t NwkSKey[16];
	uint8_t AppSKey[16];
	uint8_t AppKey[16];
	uint32_t RxWinDelay1;
	uint32_t RxWinDelay2;
	uint32_t JoinDelay1;
	uint32_t JoinDelay2;
	uint8_t TxPower;
	uint8_t AppPort;
	uint8_t Confirm;
	uint16_t ChanMask[6];
    uint8_t Freq[80];		// Freq:0-3B; Dr:4B; 5*n(n=16)80
	uint8_t DefDr;
	uint32_t Win2Feq;
	uint8_t Win2Dr;
	uint32_t globalDutyRate;
    uint8_t DutyCycleOn;
	uint8_t JoinRetries;
	uint8_t RetriesTx;
	uint32_t AckTimeout;
	uint8_t LinkCheck;
	uint8_t SyncWord;
	uint8_t region;
	uint32_t Resverd1;
	uint32_t Resverd2;
	uint8_t DtuPort;
    uint8_t linkwanFreqMode;
    uint8_t Resverd[808];
	uint32_t UpLinkCounter;
	uint32_t DownLinkCounter;		
} LoRaWANParams_t;//1032
#pragma pack()
#pragma pack(1)
typedef struct flash_flag {
	params_lock_t lockflag1;
	params_lock_t lockflag2;
	uint8_t 			readflag1;
	uint8_t       readflag2;
	uint32_t      crc_bak_upgrade;
	uint32_t			crc_bak_flash;
	params_lock_t lockflag3;
	uint8_t       readflag3;
	uint8_t				upgrade_enable;
} flash_flag_t;
#pragma pack()
#define FLASH_APP_BAK_ADDR						(0x08000000 + 0x44000)		//begin at 272kb
#define FLASH_APP_BAK_LEN							0x36800
#define FLASH_PARAMS_BASE_ADDR      	(0x08000000 + 0x3D800)   //begin at 246kb
             

//#define FLASH_LOCKFLAG1_ADDR         FLASH_PARAMS_BASE_ADDR

//flash flag
#define FLASH_FLAG_ADDR							(FLASH_PARAMS_BASE_ADDR)
#define FLAG_LEN										0x400
//#define FLASH_LOCKFLAG1_ADDR         FLASH_PARAMS_BASE_ADDR//(FLASH_UPGRADE_INFO_ADDR + UPGRADE_INFO_LEN + UPGRADE_INFO_RESERVED)
//#define LOCKFLAG1_LEN                0x200

//#define FLASH_LOCKFLAG2_ADDR         (FLASH_LOCKFLAG1_ADDR + LOCKFLAG1_LEN)
//#define LOCKFLAG2_LEN                0x200
//#define FLASH_UNXX_MAGIC_ADDR        (FLASH_LOCKFLAG2_ADDR + LOCKFLAG2_LEN)

#define FLASH_UNXX_MAGIC_ADDR        (FLASH_FLAG_ADDR + FLAG_LEN)
#define UNXX_MAGIC_LEN               0x200

#define FLASH_UPGRADE_INFO_ADDR      (FLASH_UNXX_MAGIC_ADDR + UNXX_MAGIC_LEN)
#define UPGRADE_INFO_LEN             0x10
#define UPGRADE_INFO_RESERVED        (0x200 - UPGRADE_INFO_LEN) 

//flash cfg   should backup start
#define FLASH_PRODUCT_INFO_ADDR      (FLASH_UPGRADE_INFO_ADDR+UPGRADE_INFO_RESERVED+UPGRADE_INFO_LEN)
#define PRODUCT_INFO_LEN             0x100

#define FLASH_PN_INFO_ADDR           (FLASH_PRODUCT_INFO_ADDR+PRODUCT_INFO_LEN)//(FLASH_PRODUCT_INFO_ADDR + PRODUCT_INFO_LEN)
#define PN_INFO_LEN                  0x80

#define FLASH_DEVICE_INFO_ADDR       (FLASH_PN_INFO_ADDR+PN_INFO_LEN)
#define DEVICE_INFO_LEN              0x100

#define FLASH_RULES_INFO_ADDR        (FLASH_DEVICE_INFO_ADDR + DEVICE_INFO_LEN)
#define RULES_INFO_LEN               0x100

#define FLASH_APPLICATION_INFO_ADDR  (FLASH_RULES_INFO_ADDR + RULES_INFO_LEN)
#define APPLICATION_INFO_LEN         0x80

#define FLASH_USR_CONFIG_ADDR        (FLASH_APPLICATION_INFO_ADDR + APPLICATION_INFO_LEN)
#define USR_CONFIG_LEN               0x400

#define FLASH_LORA_INFO_ADDR         (FLASH_USR_CONFIG_ADDR + USR_CONFIG_LEN)
#define LORA_INFO_LEN                0x800


#define FLASH_USER_PARAMS_SIZE       0x2000
#define FLASH_USER_PARAMS_ADDR       (0x08000000 + 0x3E000)
#define FLASH_USER_BAK_PARAMS_ADDR   (FLASH_USER_PARAMS_ADDR + FLASH_USER_PARAMS_SIZE)
#define FLASH_USER_READBAK_PARAMS_ADDR   (FLASH_USER_BAK_PARAMS_ADDR + FLASH_USER_PARAMS_SIZE)



extern void write_data_to_flash(uint32_t *data, uint16_t len_bytes, uint32_t addr);
extern void read_data_from_flash(uint32_t *data, uint16_t len_bytes, uint32_t addr, uint8_t fromisr);
extern void copy_readbak(void);	
extern void unxx_save_default_config(void);
extern void flash_addr_init(uint8_t * addr);
#endif

