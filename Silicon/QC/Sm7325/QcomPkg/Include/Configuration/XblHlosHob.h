#ifndef _XBL_HLOS_HOB_H_
#define _XBL_HLOS_HOB_H_

typedef enum {
  PLATFORM_SUBTYPE_UNKNOWN                = 0x0,
  PLATFORM_SUBTYPE_EV1                    = 0x1,
  PLATFORM_SUBTYPE_EV1_1                  = 0x2,
  PLATFORM_SUBTYPE_EV2                    = 0x3,
  PLATFORM_SUBTYPE_EV2_1                  = 0x4,
  PLATFORM_SUBTYPE_EV2_2                  = 0x5,
  PLATFORM_SUBTYPE_EV2_wifi               = 0x6,
  PLATFORM_SUBTYPE_SKIP                   = 0x7,
  PLATFORM_SUBTYPE_EV3_Retail             = 0x8,
  PLATFORM_SUBTYPE_EV3_Debug              = 0x9,
  PLATFORM_SUBTYPE_DV_Retail              = 0xA,
  PLATFORM_SUBTYPE_DV_Debug               = 0xB,
  PLATFORM_SUBTYPE_MP_Retail              = 0xC,
  PLATFORM_SUBTYPE_INVALID,
}sboard_id_t;

#pragma pack(1)
#define MCFG_MODE                   0
#define CUST_MODE                   1
#define MAX_VERSION_LEN             16
#define DISPLAY_RDID_LEN            3
#define DISPLAY_TDM_VERSION_INDEX   1
#define MAX_PMIC_BLOCK_LEN          71
#define MAX_PMIC_SIZE               6
#define MAX_PMIC_SDAM_BLOCK_LEN     128

/* DO NOT CHANGE ORDER, any additions to this structure in include/linux/soc/surface/surface_utils.h should also be updated exactly the same way in boot_images/boot/Sm8350FamilyPkg/Include/XblHlosHob.h*/
typedef enum {
   OEM_UNITIALISED = 0,
   SURFACE_DUO     = 1,
   SURFACE_DUO2    = 2,
}sproduct_id_t;

typedef enum
{
  PM_SDAM_1,
  PM_SDAM_5 = 4,
  PM_SDAM_6 = 5,
  PM_SDAM_7 = 6,
  PM_SDAM_8 = 7,
  PM_SDAM_48 = 47,
}pm_sdam_type;
// Note: Need to take care alignment of struct member
typedef struct XBL_HLOS_HOB
{
    UINT8 BoardID;                          // (00)
    UINT8 BatteryPresent;                   // (01) Indicates battery presence: 0 - battery absent, 1 - battery present
    UINT8 HwInitRetries;                    // (02) Indicates retries attempted to initialize descrete hardware circuit
    UINT8 IsCustomerMode;                   // (03) Indicates whether the device is in Manufacturing Mode: 0 - in manuf mode, 1 - in Customer mode
    UINT8 IsActMode;                        // (04) Indicates whether device has act mode enabled. 0 - disabled 1 - enabled
    UINT8 PmicResetReason;                  // (05) PmicResetReason: 9 - battery driver triggered
    CHAR8 TouchFWVersion[MAX_VERSION_LEN];  // (06) Current Touch Firmware version number
    UINT16 ProductId;                       // (07) Product ID of the device.
    UINT16 OCPErrorLocation;                // (08) Identify which power rail has the OCP Error
                                              //      Bit(s)     Meaning
                                              //      15         More than one OCP error occurred
                                              //      14-12      PMIC
                                              //      11-7       SMPS
                                              //      6-2        LDO
                                              //      1-0        BOB
    UINT8 IsRaflaMode;                      // (09) Indicates whether the device is in Rafla Mode: 0 - not in Rafla mode, 1 - in Rafla mode
    UINT8 DisplayRDID[DISPLAY_RDID_LEN];    // (10) Indicates which TDM RDID has been read.
                                              //      Index 0 is related to manufacturer, LGD--, Here we will see 0x81 for Zeta
                                              //      Index 1 is related to TDM version, EV1, EV2, EV3, DV, MP etc
                                              //      0         - Unknown TDM, we have bigger problems.
                                              //      0x31-0x3F - EV2
                                              //      0x41-0x4F - EV3
                                              //      Index 2 tells us which one we read, left side or right side, we will mstly see left side
                                              //      0x9        - Left side
                                              //      0x10       - right side
    UINT8 Future;                           // (11)
    UINT8 PmicPonBlock[MAX_PMIC_SIZE][MAX_PMIC_BLOCK_LEN]; //(12) PMIC pon block from 0x885 to 0x8cb
    UINT8 PmicSdamBlock48[MAX_PMIC_SDAM_BLOCK_LEN]; // PMIC SDAM48 block from 0x9F40 to 0x9FBF
    UINT8 PmicSdamBlock08[MAX_PMIC_SDAM_BLOCK_LEN]; // PMIC SDAM8  block from 0x7740 to 0x77BF
    UINT8 PmicSdamBlock07[MAX_PMIC_SDAM_BLOCK_LEN]; // PMIC SDAM7  block from 0x7640 to 0x76BF
    UINT8 PmicSdamBlock06[MAX_PMIC_SDAM_BLOCK_LEN]; // PMIC SDAM6  block from 0x7540 to 0x75BF
    UINT8 PmicSdamBlock05[MAX_PMIC_SDAM_BLOCK_LEN]; // PMIC SDAM5  block from 0x7440 to 0x74BF
    UINT8 PmicSdamBlock01[MAX_PMIC_SDAM_BLOCK_LEN]; // PMIC SDAM1  block from 0x7040 to 0x70BF
} *PXBL_HLOS_HOB;

#pragma pack()

#endif /* _XBL_HLOS_HOB_H_ */