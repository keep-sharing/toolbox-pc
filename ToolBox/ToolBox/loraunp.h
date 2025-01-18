#ifndef LORAUNP
#define LORAUNP

#include <QObject>
#include "stdint.h"

typedef enum {
    LORA_MODE = 0,
    LORA_OTA ,
    LORA_ADR ,
    LORA_NET_ID ,
    LORA_DEV_ADDR = 7,
    LORA_DEV_EUI = 11,
    LORA_APP_EUI = 19,
    LORA_NWKS_KEY = 27,
    LORA_APPS_KEY = 43,
    LORA_APP_KEY = 59,
    LORA_RX_WIN_DELAY1 = 75,
    LORA_RX_WIN_DELAY2 = 79,
    LORA_JOIN_DELAY1 = 83,
    LORA_JOIN_DELAY2 = 87,
    LORA_TX_POWER = 91,
    LORA_APP_PORT = 92,
    LORA_CONFIRM = 93,
    LORA_CHAN_MASK = 94,

    LORA_FREQ = 96,
    LORA_DEFDR = 176,
    LORA_WIN2_FEQ = 177,
    LORA_WIN2_DR = 181,
    LORA_DUTY_CYCLE_VALUE = 182,
    LORA_DUTY_CYCLE_SWITCH = 186,
    LORA_JOIN_RETRIES = 187,
    LORA_RETRIES_TX = 188,
    LORA_ACK_TIMEOUT = 189,
    LORA_LINK_CHECK = 193,
    LORA_SYNC_WORD = 194,
    LORA_REGION = 195,
    LORA_RESVERD1 = 196,
    LORA_RESVERD2 = 200,
    LORA_RS232_PORT = 204,
    LORA_CHANNELMASK15_95 = 205,
    LORA_LINKWAN_FREQ_MODE = 215,
    LORA_VERSION=216,
    LORA_MAX_CONFIRM_NUM = 217,
    LORA_MAX_CONFIRM_ENABLE = 218,
    LORA_RESVERD3=219,
    LORA_UPTIME=234,
    LORA_BATTERY_CONSUME=238,
    LORA_BATTERY_LEFT = 242,
    LORA_RESVERD = 246,
    LORA_UP_LINK_COUNTER = 248,
    LORA_DOWN_LINK_COUNTER= 252

}lora_offset_t;

typedef enum {
    LORA_T1N1_CHANNELMASK15_95 = 96,
    LORA_T1N1_FREQ = 106,
    LORA_T1N1_DEFDR = 186,
    LORA_T1N1_WIN2_FEQ = 187,
    LORA_T1N1_WIN2_DR = 191,
    LORA_T1N1_DUTY_CYCLE_VALUE = 192,
    LORA_T1N1_DUTY_CYCLE_SWITCH = 196,
    LORA_T1N1_JOIN_RETRIES = 197,
    LORA_T1N1_RETRIES_TX = 198,
    LORA_T1N1_ACK_TIMEOUT = 199,
    LORA_T1N1_LINK_CHECK = 203,
    LORA_T1N1_SYNC_WORD = 204,
    LORA_T1N1_REGION = 205,
    LORA_T1N1_RESVERD1 = 206,
    LORA_T1N1_RESVERD2 = 210,
    LORA_T1N1_RS232_PORT = 214,
    LORA_T1N1_LINKWAN_FREQ_MODE=215,
    LORA_T1N1_VERSION=216,
    LORA_T1N1_MAX_CONFIRM_NUM = 217,
    LORA_T1N1_MAX_CONFIRM_ENABLE = 218,
    LORA_T1N1_AS923PLAN_SUPPORT=219,
    LORA_T1N1_AS923_PLAN=220,
    LORA_T1N1_RESVERD = 221,
    LORA_T1N1_UP_LINK_COUNTER = 248,
    LORA_T1N1_DOWN_LINK_COUNTER= 252
}lora_t1n1_offset_t;

typedef enum lora_work_mode_e {
    CLASS_A = 0,
    CLASS_B = 1,
    CLASS_C = 2,
}lora_work_mode_t;

typedef enum lora_ota_e {
    OTA = 0,
    ABP ,
}lora_ota_t;

typedef enum lora_adr_e {
    OFF = 0,
    ON
}lora_adr_t;

typedef enum{
    LORA_SNR = 5,
    LORA_RSSI,
    LORA_JOIN_STATUS = 8,
    LORA_CHAN = 9,
    LORA_DATARATE ,
    LORA_RX2DR,
    LORA_RX2FREQ,
    LORA_MAX_EIRP = 16,
    LORA_RECEIVE_DELAY1 =17,
    LORA_RECEIVE_DELAY2 =21,
    LORA_CUR_RETRY_COUNTS = 25,
    LORA_STATE = 26,
    LORA_CUR_UP_LINK_COUNTER = 27,
    LORA_CUR_DOWN_LINK_COUNTER = 31,
    LORA_INPUT = 35,
    LORA_OUTPUT = 36
}lora_status_offset_t;

typedef enum lora_state_e{
    STATUS_IDLE = 0,
    STATUS_TXING,
    STATUS_TXDONE,
    STATUS_RXOPEN1,
    STATUS_RXDONE1,
    STATUS_RXOPEN2,
    STATUS_RXDONE2,
}lora_state_t;

typedef enum lora_datarate_e{
    SF12,
    SF11,
    SF10,
    SF9,
    SF8,
    SF7,
}lora_datarate_t;

enum lora_region{
    CN470 = 0,
    EU433,
    AS923,
    AU915,
    EU868,
    KR920,
    IN865,
    US915,
    US915_HYBRID,
    CN779,
    RU864
};

struct GET_LORA_STATUS_INFO{
    QString snr;
    QString rssi;
    QString join_status;
    QString chan;
    QString datarate;
    QString rx2dr;
    QString rx2freq;
    QString maxEIRP;
    QString receive_delay1;
    QString receive_delay2;
    QString cur_retry_counts;
    QString state;
    QString cur_up_link_counter;
    QString cur_down_link_counter;
    QString input;
    QString output;
    QString battery;
    QString temperature;
    QString humidity;
};

struct StructPageLorawan{
    QString regularReport;
    QString mode;
    QString ota;
    QString adr;
    QString adrSqr;
    QString netId;
    QString devAddr;
    QString devEui;
    QString appEui;
    QString nwksKey;
    QString appsKey;
    QString appKey;
    QString rxWinDelay1;
    QString rxWinDelay2;
    QString joinDelay1;
    QString joinDelay2;
    QString txPower;
    QString appPort;
    QString rs232Port;
    QString confirm;
    QString rejoin;
    QString rejoinCount;
    QString chanMask;
    QString loraVersion;
//    uint8_t Freq[80];  // Freq:0-3B; Dr:4B; 5*n(n=16)80
    QString fre0;
    QString fre1;
    QString fre2;
    QString fre3;
    QString fre4;
    QString fre5;
    QString fre6;
    QString fre7;

    QString defDr;
    QString win2Feq;
    QString win2Dr;
    QString globalDutyRate;
    QString dutyCycleOn;
    QString joinRetries;
    QString retriesTx;
    QString ackTimeout;
    QString linkCheck;
    QString syncWord;
    QString region;
//     uint8_t Resverd[60];
    QString upLinkCounter;
    QString downLinkCounter;
    QString chanMask16_31;
    QString chanMask32_47;
    QString chanMask48_63;
    QString chanMask64_79;
    QString chanMask80_95;

    QString reportingInterval;
    QString temGreater;
    QString temLess;
    QString temLockTime;
    QString temContinueTime;
    QString temMode;
    QString autoReport;
    QString calibrationEnable;
    QString tempCalibrationValue;
    QString humiCalibrationValue;

    QString linkwanFreqMode;
    QString frequencyUpdateFlag;

};


#pragma pack()


#endif // LORAUNP

