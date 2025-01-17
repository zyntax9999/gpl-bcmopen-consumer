













































typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;






typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;



typedef long int __quad_t;
typedef unsigned long int __u_quad_t;







typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;







typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;

typedef int __daddr_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;


typedef long int __fsword_t;

typedef long int __ssize_t;


typedef long int __syscall_slong_t;

typedef unsigned long int __syscall_ulong_t;



typedef __off64_t __loff_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;




typedef int __sig_atomic_t;






static __inline __uint16_t
__bswap_16 (__uint16_t __bsx)
{

  return __builtin_bswap16 (__bsx);



}






static __inline __uint32_t
__bswap_32 (__uint32_t __bsx)
{

  return __builtin_bswap32 (__bsx);



}

__extension__ static __inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{

  return __builtin_bswap64 (__bsx);



}



static __inline __uint16_t
__uint16_identity (__uint16_t __x)
{
  return __x;
}

static __inline __uint32_t
__uint32_identity (__uint32_t __x)
{
  return __x;
}

static __inline __uint64_t
__uint64_identity (__uint64_t __x)
{
  return __x;
}













static int targetEndianess = 0;




typedef struct _FILE_TAG
{
    char tagVersion[4];
    char signiture_1[20];
    char signiture_2[14];
    char chipId[6];
    char boardId[16];
    char bigEndian[2];
    char totalImageLen[10];
    char cfeAddress[12];
    char cfeLen[10];
    char rootfsAddress[12];
    char rootfsLen[10];
    union {
        char kernelAddress[12];
        char bootfsAddress[12];
    };
    union {
        char kernelLen[10];
        char bootfsLen[10];
    };
    char imageSequence[2 * 2];
    char imageVersion[32];
    union {
        char dtbAddress[12];
        char mdataAddress[12];
    };
    union {
        char dtbLen[10];
        char mdataLen[10];
    };
    unsigned int imageFlags;
    char reserved[(256 - 4 - 20 - 14 - 6 - 16 - (5*10) - (4*12) - (3*2) - (2*20) - 32 - sizeof(unsigned int))];
    char imageValidationToken[20];

    char tagValidationToken[20];
} FILE_TAG, *PFILE_TAG;

typedef struct _WFI_TAG
{
    unsigned int wfiCrc;
    unsigned int wfiVersion;
    unsigned int wfiChipId;
    unsigned int wfiFlashType;
    unsigned int wfiFlags;
} WFI_TAG, *PWFI_TAG;

typedef struct
{

    unsigned char magic_num[8];




    unsigned int header_len;

    unsigned int header_crc;
    unsigned int header_version;





    unsigned int version_min;
    unsigned int version_max;

    unsigned int combo_image_revision;

    unsigned int image_count;

    unsigned int header_flags;

    unsigned int next_tag_offset;

    unsigned int extended_combo_header;
} Comboimg_header_tag;


typedef struct
{

    char board_id[16];

    unsigned int chip_id;

    unsigned int image_len;

    unsigned int image_offset;

    unsigned int image_flags;

    unsigned int next_tag_offset;

    unsigned int extended_image_header;
} Comboimg_individual_img_tag;

static unsigned int Crc32_table[256] = {
    0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA,
    0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
    0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
    0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
    0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE,
    0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
    0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC,
    0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
    0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
    0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
    0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940,
    0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
    0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116,
    0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
    0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
    0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
    0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A,
    0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
    0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818,
    0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
    0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
    0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
    0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C,
    0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
    0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2,
    0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
    0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
    0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
    0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086,
    0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
    0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4,
    0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
    0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
    0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
    0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8,
    0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
    0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE,
    0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
    0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
    0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
    0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252,
    0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
    0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60,
    0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
    0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
    0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
    0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04,
    0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
    0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A,
    0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
    0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
    0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
    0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E,
    0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
    0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C,
    0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
    0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
    0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
    0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0,
    0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
    0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6,
    0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
    0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
    0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};





enum bp_id {
  bp_cpBoardId,
  bp_cpComment,
  bp_ulCompatChipId,
  bp_ulGpioOverlay,
  bp_usGpioLedAdsl,
  bp_usGpioLedAdslFail,
  bp_usGpioSecLedAdsl,
  bp_usGpioSecLedAdslFail,
  bp_usGpioLedSesWireless,
  bp_usGpioLedWanData,
  bp_usGpioSecLedWanData,
  bp_usGpioLedWanError,
  bp_usGpioLedBlPowerOn,
  bp_usGpioLedBlStop,
  bp_usGpioFpgaReset,
  bp_usGpioLedGpon,
  bp_usGpioLedGponFail,
  bp_usGpioLedMoCA,
  bp_usGpioLedMoCAFail,
  bp_usGpioLedEpon,
  bp_usGpioLedEponFail,
  bp_usExtIntrResetToDefault,
  bp_usExtIntrResetToDefault2,
  bp_usExtIntrSesBtnWireless,
  bp_usExtIntrNfc,
  bp_usGpioNfcWake,
  bp_usGpioNfcPower,
  bp_usGpioBitbangI2cScl,
  bp_usGpioBitbangI2cSda,
  bp_usAntInUseWireless,
  bp_usWirelessFlags,
  bp_usGpioWirelessPowerDown,
  bp_ucPhyType0,
  bp_ucPhyType1,
  bp_ucPhyAddress,
  bp_usConfigType,
  bp_ulPortMap,
  bp_ulPhyId0,
  bp_ulPhyId1,
  bp_ulPhyId2,
  bp_ulPhyId3,
  bp_ulPhyId4,
  bp_ulPhyId5,
  bp_ulPhyId6,
  bp_ulPhyId7,
  bp_ulPhyId8,
  bp_ulPhyId9,
  bp_ulPhyId10,
  bp_ulPhyId11,
  bp_ulPhyId12,
  bp_ulPhyId13,
  bp_ulPhyId14,
  bp_ulPhyId15,
  bp_usDuplexLed,
  bp_usLinkLed,
  bp_usSpeedLed100,
  bp_usSpeedLed1000,
  bp_usPhyConnType,
  bp_usGpioPhyReset,
  bp_ucPhyDevName,
  bp_ucDspType0,
  bp_ucDspType1,
  bp_ucDspAddress,
  bp_usGpioLedVoip,
  bp_usGpioVoip1Led,
  bp_usGpioVoip1LedFail,
  bp_usGpioVoip2Led,
  bp_usGpioVoip2LedFail,
  bp_usGpioPotsLed,
  bp_usGpioDectLed,
  bp_usGpioPassDyingGasp,
  bp_ulAfeId0,
  bp_ulAfeId1,
  bp_usGpioExtAFEReset,
  bp_usGpioExtAFELDPwr,
  bp_usGpioExtAFELDMode,
  bp_usGpioIntAFELDPwr,
  bp_usGpioIntAFELDMode,
  bp_usGpioAFELDRelay,
  bp_usGpioAFELDPwrBoost,
  bp_usGpioAFEVR5P3PwrEn,
  bp_usUart1Sdin,
  bp_usUart1Sdout,
  bp_usGpioUart2Sdin,
  bp_usGpioUart2Sdout,
  bp_usGpioUart2Cts,
  bp_usGpioUart2Rts,
  bp_usGpioLaserDis,
  bp_usGpioLaserTxPwrEn,
  bp_usGpioLaserRxPwrEn,
  bp_usGpioEponOpticalSD,
  bp_usVregSel1P2,
  bp_ucVreg1P8,
  bp_usVregAvsMin,
  bp_usGpioFemtoReset,
  bp_usEphyBaseAddress,
  bp_usGpioSpiSlaveReset,
  bp_usGpioSpiSlaveBootMode,
  bp_usSpiSlaveBusNum,
  bp_usSpiSlaveSelectNum,
  bp_usSpiSlaveSelectGpioNum,
  bp_usSpiSlaveMode,
  bp_ulSpiSlaveCtrlState,
  bp_ulSpiSlaveMaxFreq,
  bp_usSpiSlaveProtoRev,
  bp_usGpioIntAFELDData,
  bp_usGpioIntAFELDClk,
  bp_usGpioExtAFELDData,
  bp_usGpioExtAFELDClk,
  bp_ulNumFePorts,
  bp_ulNumGePorts,
  bp_ulNumVoipPorts,
  bp_usGpioI2cScl,
  bp_usGpioI2cSda,
  bp_usGpioI2c2Scl,
  bp_usGpioI2c2Sda,
  bp_usPortNum,
  bp_ulBusDevId,
  bp_ulI2cClock,
  bp_usI2cMuxSel,
  bp_usGpioI2CMux,
  bp_elemTemplate,
  bp_usSerialLEDMuxSel,
  bp_ulDeviceOptions,
  bp_pPhyInit,
  bp_usGpioLaserReset,
  bp_usGpio_Intr,
  bp_usGphyBaseAddress,
  bp_cpPersonalityName,
  bp_usExtIntrMocaHostIntr,
  bp_usExtIntrMocaSBIntr0,
  bp_usExtIntrMocaSBIntr1,
  bp_usExtIntrMocaSBIntr2,
  bp_usExtIntrMocaSBIntr3,
  bp_usExtIntrMocaSBIntr4,
  bp_usExtIntrMocaSBIntrAll,
  bp_usMocaType0,
  bp_usMocaType1,
  bp_pMocaInit,
  bp_usGpioMocaReset,
  bp_ulDyingGaspIntrPin,
  bp_usGpioPLCPwrEn,
  bp_usGpioPLCReset,
  bp_usExtIntrPLCStandBy,
  bp_ulPortFlags,
  bp_usMocaRfBand,
  bp_usGpioLedOpticalLinkFail,
  bp_usGpioLedOpticalLinkStat,
  bp_usGpioLedLan,
  bp_usGpioLedWL2_4GHz,
  bp_usGpioLedWL5GHz,
  bp_usGpioLedUSB,
  bp_usGpioLedUSB2,
  bp_usGpioBoardReset,
  bp_usGpioUsb0,
  bp_usGpioUsb1,
  bp_ulOpticalWan,
  bp_ulSimInterfaces,
  bp_ulSlicInterfaces,
  bp_usGpioPonTxEn,
  bp_usGpioPonRxEn,
  bp_usRogueOnuEn,
  bp_usGpioLedSim,
  bp_usGpioLedSim_ITMS,
  bp_usPinMux,
  bp_usGpioSpromClk,
  bp_usGpioSpromData,
  bp_usGpioSpromRst,
  bp_usGpioAttachedDevReset,
  bp_usTsync1025mhz,
  bp_usTsync8khz,
  bp_usTsync1pps,
  bp_usGpioTsyncPonUnstable,
  bp_usGpioLedReserved,
  bp_usGpioReserved,
  bp_usSerialLedData,
  bp_usSerialLedClk,
  bp_usSerialLedMask,
  bp_usSerialLedShiftOrder,
  bp_ReservedDslCtl,
  bp_ReservedAnyGpio,
  bp_ReservedAnyLed,
  bp_ulCrossbar,
  bp_ulCrossbarPhyId,
  bp_ulInterfaceEnable,
  bp_ulMemoryConfig,
  bp_usBatteryEnable,
  bp_ulPinmuxTableSelect,
  bp_usExtIntrPmdAlarm,
  bp_usGpioPmdReset,
  bp_usPmdMACEwakeEn,
  bp_ulPortMaxRate,
  bp_ulAttachedIdx,
  bp_usExtIntrTrplxrTxFail,
  bp_usExtIntrTrplxrSd,
  bp_usTxLaserOnOutN,
  bp_usGpioPonReset,
  bp_usGpio1ppsStable,
  bp_usWanNco10MClk,
  bp_usGpioLteReset,
  bp_usTrxSignalDetect,
  bp_usGpioStrapTxEn,
  bp_usExtIntrWifiOnOff,
  bp_usExtIntrLTE,
  bp_usMiiInterfaceEn,
  bp_usFxsFxo1SpiSSNum,
  bp_usFxsFxo2SpiSSNum,
  bp_usFxsFxo3SpiSSNum,
  bp_usFxsFxo4SpiSSNum,
  bp_usGpioFxsFxoRst1,
  bp_usGpioFxsFxoRst2,
  bp_usGpioFxsFxoRst3,
  bp_usGpioFxsFxoRst4,
  bp_usGpioDectRst,
  bp_usGpioVoipRelayCtrl1,
  bp_usGpioVoipRelayCtrl2,
  bp_usGpioLe9540Reset,
  bp_usSi32392SpiSSNum,
  bp_usHvgMaxPwm,
  bp_usZarIfSclk,
  bp_usZarIfSdout,
  bp_usZarIfSdin,
  bp_usZarIfEnable,
  bp_iDectCfg,
  bp_daughterCardList,
  bp_usSgmiiDetect,
  bp_usVregSync,
  bp_usGpioLedPwmReserved,
  bp_usAePolarity,
  bp_usButtonIdx,
  bp_usButtonExtIntr,
  bp_usButtonAction,
  bp_ulButtonActionParm,
  bp_usCfeResetToDefaultBtnIdx,
  bp_usUsbPwrOn0,
  bp_usUsbPwrOn1,
  bp_usUsbPwrFlt0,
  bp_usUsbPwrFlt1,
  bp_usGpioSfpDetect,
  bp_usSimDat,
  bp_usSimClk,
  bp_usSimPresence,
  bp_usSimVccEn,
  bp_usSimVccVolSel,
  bp_usSimRst,
  bp_usSimVppEn,
  bp_usMiiMdc,
  bp_usMiiMdio,
  bp_usProbeClk,
  bp_usGpioWanSignalDetected,
  bp_usExtIntrWanSignalDetected,
  bp_usOamIndex,
  bp_usXdResetGpio,
  bp_cpXdResetName,
  bp_usXdResetReleaseOnInit,
  bp_usXdGpio,
  bp_usXdGpioInitValue,
  bp_cpXdGpioInfo,
  bp_cpXdGpioInfoValue0,
  bp_cpXdGpioInfoValue1,
  bp_ulLedBlPowerOnBlinkTimeOn,
  bp_ulLedBlPowerOnBlinkTimeOff,
  bp_usWanEarlyTxEn,
  bp_usMs1588TodAlarm,
  bp_usWanNcoProgMClk,
  bp_usNtrRefIn,
  bp_usGpioBtReset,
  bp_usGpioBtWake,
  bp_InvSerdesRxPol,
  bp_InvSerdesTxPol,
  bp_pmdFunc,
  bp_usPcmSdin,
  bp_usPcmSdout,
  bp_usPcmClk,
  bp_usPcmFs,
  bp_usI2sSdata,
  bp_usI2sTxSdata=bp_usI2sSdata,
  bp_usI2sRxSdata,
  bp_usI2sSclk,
  bp_usI2sMclk,
  bp_usI2sLrck,
  bp_usGpioTxDis0,
  bp_usGpioTxDis1,
  bp_usGpioTxDis2,
  bp_usGpioTxDis3,
  bp_usSFPSerdesSIGDET0,
  bp_usSFPSerdesSIGDET1,
  bp_usSFPSerdesSIGDET2,
  bp_usSFPSerdesSIGDET3,
  bp_usSFPSerdesMODDEF0,
  bp_usSFPSerdesMODDEF1,
  bp_usSFPSerdesMODDEF2,
  bp_usSFPSerdesMODDEF3,
  bp_usGpioLedAggregateLnk,
  bp_usGpioLedAggregateAct,
  bp_ulMaxNumCpu,
  bp_usExtIntrOpticalModulePresence,
  bp_usGpioOpticalModuleFixup,
  bp_usGpioOpticalModuleTxPwrDown,
  bp_usGpioPonMuxOe,
  bp_usGpioPonMux0,
  bp_usGpioPonMux1,
  bp_ucDHDMemReserve0,
  bp_ucDHDMemReserve1,
  bp_ucDHDMemReserve2,
  bp_usNetLed0,
  bp_usNetLed1,
  bp_usNetLed2,
  bp_usNetLed3,
  bp_ulNetLedLink,
  bp_ulNetLedActivity,
  bp_ulNetLedSetting,
  bp_ulPciFlags,

  bp_usPonLbe,
  bp_usExtIntrSDCardDetect,
  bp_usI2cDefXponBus,
  bp_usI2cNumBus,






  bp_usGpioPwrSync,
  bp_usUsbDis,
  bp_usPciDis,
  bp_usSataDis,
  bp_usGpioWireless0Disable,
  bp_usGpioWireless2Disable,
  bp_usGpioWireless3Disable,
  bp_usGpioWlanReserved,
  bp_ulLedChannelId,
  bp_usGpioInitState,
  bp_usGpioLedWL0Act,
  bp_usGpioLedWL1Act,
  bp_usGpioWlanReserved1,
  bp_last
};



typedef struct bp_elem {
  enum bp_id id;
  union {
    char * cp;
    unsigned char * ucp;
    unsigned char uc;
    unsigned short us;
    unsigned int ul;
    void * ptr;
    struct bp_elem * bp_elemp;
  } u;
} bp_elem_t;

extern bp_elem_t * g_pCurrentBp;
extern bp_elem_t * g_BoardParms[];

typedef struct bp_pinmux_defs {
  enum bp_id id;
  short port;
  short func;
  unsigned int mux_info;
} bp_pinmux_defs_t;

typedef struct bp_pinmux_fn_defs {
  unsigned int function;
  unsigned int mux_info;
} bp_pinmux_fn_defs_t;


enum cmdToExec
{
    CMD_READ,
    CMD_WRITE,
    CMD_WAIT,
    CMD_END
};

typedef struct
{
    enum cmdToExec command;
    unsigned int addr;
    unsigned int value;
} BpCmdElem;


typedef struct _BP_SPISLAVE_INFO {
  unsigned short resetGpio;
  unsigned short bootModeGpio;
  unsigned short busNum;
  unsigned short select;
  unsigned short mode;
  unsigned int ctrlState;
  unsigned int maxFreq;
} BP_SPISLAVE_INFO, *PBP_SPISLAVE_INFO;



typedef struct _BP_MOCA_INFO {
  unsigned int type;
  unsigned int rfBand;
  unsigned short intr[7];
  unsigned short intrGpio[7];
  BpCmdElem* initCmd;
  BP_SPISLAVE_INFO spiDevInfo;
} BP_MOCA_INFO, *PBP_MOCA_INFO;

typedef struct {
  unsigned short duplexLed;
  unsigned short speedLed100;
  unsigned short speedLed1000;
  unsigned short LedLan;
} LED_INFO;

struct bp_mdio_init_write {
    unsigned short op;
    unsigned short reg;
    unsigned int data;
};

struct bp_mdio_init_update {
    unsigned short op;
    unsigned short reg;
    unsigned short mask;
    unsigned short data;
};

struct bp_mdio_init_template {
    unsigned short op;
    unsigned short dummy1;
    unsigned int dummy2;
};

typedef struct bp_mdio_init {
  union {
    struct bp_mdio_init_template op;
    struct bp_mdio_init_write write;
    struct bp_mdio_init_update update;
  } u;
} bp_mdio_init_t;

typedef struct {
  unsigned int switch_port;
  unsigned int phy_id;
  unsigned int phy_id_ext;
  unsigned int phyconn;
  char *phy_devName;
  LED_INFO ledInfo;
  bp_mdio_init_t* phyinit;
  unsigned int port_flags;
  unsigned short phyReset;
  short oamIndex;
  unsigned int portMaxRate;
} ETHERNET_CROSSBAR_INFO;


typedef struct {
  unsigned int port_map;
  unsigned int phy_id[8];
  unsigned int phy_id_ext[8];
  unsigned int phyconn[8];
  char *phy_devName[8];
  LED_INFO ledInfo[8];
  bp_mdio_init_t* phyinit[8];
  unsigned int port_flags[8];
  unsigned short phyReset[8];
  short oamIndex[8];
  unsigned int portMaxRate[8];
  ETHERNET_CROSSBAR_INFO crossbar[5];
} ETHERNET_SW_INFO;


typedef struct {
    unsigned int is_activity_led_present;
    struct {
        unsigned int SpeedLed[4];
        unsigned int ActivityLed[4];
        short skip_in_aggregate;
    } ledInfo[8];
} LEDS_ADVANCED_INFO;

enum pmd_polarity
{
    pmd_use_def_polarity,
    pmd_polarity_invert
};

typedef struct EthernetMacInfo
{
    unsigned char ucPhyType;
    unsigned char ucPhyAddress;
    unsigned short usConfigType;
    ETHERNET_SW_INFO sw;
    unsigned short usGpioMDC;
    unsigned short usGpioMDIO;
} ETHERNET_MAC_INFO, *PETHERNET_MAC_INFO;

typedef struct
{
  unsigned int port_map;
  unsigned int ports[16];
  char *devnames[16];
} BP_ATTACHED_INFO;

typedef struct WlanSromEntry {
    unsigned short wordOffset;
    unsigned short value;
} WLAN_SROM_ENTRY;

typedef struct WlanSromPatchInfo {
    char szboardId[16];
    unsigned short usWirelessChipId;
    unsigned short usNeededSize;
    WLAN_SROM_ENTRY *uniqueEntries;
    WLAN_SROM_ENTRY *commonEntries;
} WLAN_SROM_PATCH_INFO, *PWLAN_SROM_PATCH_INFO;

typedef struct WlanPciEntry {
    char name[16];
    unsigned int dwordOffset;
    unsigned int value;
} WLAN_PCI_ENTRY;

typedef struct WlanPciPatchInfo {
    char szboardId[16];
    unsigned int usWirelessPciId;
    int usNeededSize;
    WLAN_PCI_ENTRY entries[32];
} WLAN_PCI_PATCH_INFO, *PWLAN_PCI_PATCH_INFO;




typedef struct VoIPDspInfo
{
    unsigned char ucDspType;
    unsigned char ucDspAddress;
    unsigned short usGpioLedVoip;
    unsigned short usGpioVoip1Led;
    unsigned short usGpioVoip1LedFail;
    unsigned short usGpioVoip2Led;
    unsigned short usGpioVoip2LedFail;
    unsigned short usGpioPotsLed;
    unsigned short usGpioDectLed;

} VOIP_DSP_INFO;





typedef struct {
  unsigned char gpio_for_oc_detect;
  unsigned char gpio_for_oc_output;
} GPIO_USB_INFO;







typedef struct {
    unsigned short busNum;
    unsigned short mode;
    unsigned int ctrlState;
    unsigned int maxFreq;
    unsigned short protoRev;
    unsigned short nbSlaves;
    unsigned short selectNum[8];
    unsigned short reset[8];
} XDSL_DISTPOINT_SPI_SLAVE_INFO;

typedef struct {
    unsigned short gpio;
    char *name;
    unsigned short releaseOnInit;
} XDSL_DISTPOINT_RESET_INFO;

typedef struct {
    unsigned short gpio;
    unsigned short initValue;
    char *info;
    char *infoValue0;
    char *infoValue1;
} XDSL_DISTPOINT_GPIO_INFO;

typedef struct {
    unsigned short nbReset;
    unsigned short nbGpio;
    XDSL_DISTPOINT_SPI_SLAVE_INFO spi;
    XDSL_DISTPOINT_RESET_INFO reset[8];
    XDSL_DISTPOINT_GPIO_INFO gpio[16];
} XDSL_DISTPOINT_INFO, *PXDSL_DISTPOINT_INFO;

extern WLAN_SROM_PATCH_INFO wlanPaInfo[];
extern WLAN_PCI_PATCH_INFO wlanPciInfo[];

int BpSetBoardId(const char *pszBoardId );
int BpGetBoardId( char *pszBoardId);
char * BpGetBoardIdNameByIndex( int i );
int BpGetBoardIds( char *pszBoardIds, int nBoardIdsSize );
int BPGetNumBoardIds(void);


int BpGetComment( char **pcpValue );

int BpGetGPIOverlays( unsigned int *pusValue );

int BpGetRj11InnerOuterPairGpios( unsigned short *pusInner, unsigned short *pusOuter );
int BpGetRtsCtsUartGpios( unsigned short *pusRts, unsigned short *pusCts );

int BpGetAdslLedGpio( unsigned short *pusValue );
int BpGetAdslFailLedGpio( unsigned short *pusValue );
int BpGetSecAdslLedGpio( unsigned short *pusValue );
int BpGetSecAdslFailLedGpio( unsigned short *pusValue );
int BpGetPwrSyncGpio( unsigned short *pusValue );
int BpGetVregSyncGpio( unsigned short *pusValue );
int BpGetWirelessSesLedGpio( unsigned short *pusValue );
int BpGetWanDataLedGpio( unsigned short *pusValue );
int BpGetSecWanDataLedGpio( unsigned short *pusValue );
int BpGetWanErrorLedGpio( unsigned short *pusValue );
int BpGetBootloaderPowerOnLedGpio( unsigned short *pusValue );
int BpGetBootloaderPowerOnLedBlinkTimeOn( unsigned int *pulValue );
int BpGetBootloaderPowerOnLedBlinkTimeOff( unsigned int *pulValue );
int BpGetBootloaderStopLedGpio( unsigned short *pusValue );
int BpGetPassDyingGaspGpio( unsigned short *pusValue );
int BpGetDyingGaspIntrPin( unsigned int *pusValue );
int BpGetFpgaResetGpio( unsigned short *pusValue );
int BpGetGponLedGpio( unsigned short *pusValue );
int BpGetGponFailLedGpio( unsigned short *pusValue );
int BpGetOpticalLinkFailLedGpio( unsigned short *pusValue );
int BpGetUSBLedGpio( unsigned short *pusValue );
int BpGetMoCALedGpio( unsigned short *pusValue );
int BpGetMoCAFailLedGpio( unsigned short *pusValue );
int BpGetEponLedGpio( unsigned short *pusValue );
int BpGetEponFailLedGpio( unsigned short *pusValue );
int BpGetAggregateLnkLedGpio( unsigned short *pusValue );
int BpGetAggregateActLedGpio( unsigned short *pusValue );
int BpGetPLCResetGpio( unsigned short *pusValue );
int BpGetPLCPwrEnGpio( unsigned short *pusValue );

int BpGetPLCStandByExtIntr( unsigned short *pusValue );
int BpGetResetToDefaultExtIntr( unsigned short *pusValue );
int BpGetResetToDefault2ExtIntr( unsigned short *pusValue );
int BpGetButtonInfo( void **token,
                     unsigned short *pusIdx,
                     unsigned short *pusGpio,
                     unsigned short *pusExtIrq,
                     unsigned short *pusNumHooks,
                     unsigned short *pausHooks,
                     void **pausHookParms
                     );
int BpGetButtonInfoByIdx( unsigned short btnIdx,
                            unsigned short *pusIdx,
                            unsigned short *pusGpio,
                            unsigned short *pusExtIrq,
                            unsigned short *pusNumHooks,
                            unsigned short *pausHooks,
                            void **pausHookParms
                            );


int BpGetWirelessSesExtIntr( unsigned short *pusValue );
int BpGetNfcExtIntr( unsigned short *pusValue );
int BpGetNfcPowerGpio( unsigned short *pusValue );
int BpGetNfcWakeGpio( unsigned short *pusValue );
int BpGetBitbangSclGpio( unsigned short *pusValue );
int BpGetBitbangSdaGpio( unsigned short *pusValue );
int BpGetBtResetGpio( unsigned short *pusValue );
int BpGetBtWakeGpio( unsigned short *pusValue );
int BpGetResetToDefaultExtIntrGpio( unsigned short *pusValue );
int BpGetResetToDefault2ExtIntrGpio( unsigned short *pusValue );
int BpGetOpticalModuleTxPwrDownGpio( unsigned short *pusValue );
int BpGetWirelessSesExtIntrGpio( unsigned short *pusValue );

int BpGetMocaInfo( PBP_MOCA_INFO pMocaInfos, int* pNumEntry );

int BpGetWirelessAntInUse( unsigned short *pusValue );
int BpGetWirelessFlags( unsigned short *pusValue );
int BpGetWirelessPowerDownGpio( unsigned short *pusValue );
int BpUpdateWirelessSromMap(unsigned short chipID, unsigned short* pBase, int sizeInWords);
int BpUpdateWirelessPciConfig (unsigned int pciID, unsigned int* pBase, int sizeInDWords);

int BpGetEthernetMacInfo( PETHERNET_MAC_INFO pEnetInfos, int nNumEnetInfos );
const ETHERNET_MAC_INFO* BpGetEthernetMacInfoArrayPtr(void);
int BpGetPortConnectedToExtSwitch(void);
int BpGet6829PortInfo( unsigned char *portInfo6829 );
int BpGetDslPhyAfeIds( unsigned int *pulValues );
int BpGetDslPhyAfeIdByIntfIdx( int intfId, unsigned int *pulValues );







int BpGetAFELDPwrBoostGpio( unsigned short *pusValue );
int BpGetAFELDRelayGpio( unsigned short *pusValue );
int BpGetAFEVR5P3PwrEnGpio( unsigned short *pusValue );
int BpGetOpticalModulePresenceExtIntrGpio( unsigned short *pusValue );
int BpGetOpticalModulePresenceExtIntr( unsigned short *pusValue );

int BpGetI2cDefXponBus( unsigned short *pusValue );
int BpGetExtAFEResetGpio( unsigned short *pulValues );
int BpGetExtAFELDPwrGpio( unsigned short *pulValues );
int BpGetExtAFELDModeGpio( unsigned short *pulValues );
int BpGetIntAFELDPwrGpio( unsigned short *pusValue );
int BpGetIntAFELDModeGpio( unsigned short *pulValues );
int BpGetExtAFELDDataGpio( unsigned short *pusValue );
int BpGetExtAFELDClkGpio( unsigned short *pusValue );
int BpGetExtAFELDPwrDslCtl( unsigned short *pulValues );
int BpGetExtAFELDModeDslCtl( unsigned short *pulValues );
int BpGetIntAFELDPwrDslCtl( unsigned short *pusValue );
int BpGetIntAFELDModeDslCtl( unsigned short *pulValues );
int BpGetIntAFELDDataDslCtl( unsigned short *pusValue );
int BpGetIntAFELDClkDslCtl( unsigned short *pusValue );
int BpGetExtAFELDDataDslCtl( unsigned short *pusValue );
int BpGetExtAFELDClkDslCtl( unsigned short *pusValue );
int BpGetUart2SdoutGpio( unsigned short *pusValue );
int BpGetUart2SdinGpio( unsigned short *pusValue );
int BpGetSerialLedData( unsigned short *pusValue );
int BpGetSerialLedShiftOrder( unsigned short *pusValue );


int BpGetEthSpdLedGpio( unsigned short port, unsigned short enetIdx,
                         unsigned short ledIdx, unsigned short *pusValue );

VOIP_DSP_INFO *BpGetVoipDspConfig( unsigned char dspNum );
int BpGetVoipLedGpio( unsigned short *pusValue );
int BpGetVoip1LedGpio( unsigned short *pusValue );
int BpGetVoip1FailLedGpio( unsigned short *pusValue );
int BpGetVoip2LedGpio( unsigned short *pusValue );
int BpGetVoip2FailLedGpio( unsigned short *pusValue );
int BpGetPotsLedGpio( unsigned short *pusValue );
int BpGetDectLedGpio( unsigned short *pusValue );

int BpGetLaserDisGpio( unsigned short *pusValue );
int BpGetLaserTxPwrEnGpio( unsigned short *pusValue );
int BpGetLaserResetGpio( unsigned short *pusValue );
int BpGetEponOpticalSDGpio( unsigned short *pusValue );
int BpGetVregSel1P2( unsigned short *pusValue );
int BpGetVreg1P8( unsigned char *pucValue );
int BpGetVregAvsMin( unsigned short *pusValue );
int BpGetMiiOverGpioFlag( unsigned int* pMiiOverGpioFlag );
int BpGetFemtoResetGpio( unsigned short *pusValue );
int BpGetEphyBaseAddress( unsigned short *pusValue );
int BpGetGphyBaseAddress( unsigned short *pusValue );

int bpstrcmp(const char *dest,const char *src);
int BpGetI2cGpios( unsigned short *pusScl, unsigned short *pusSda );
int BpGetSgmiiGpios( unsigned short *sgmiiGpio);
int BpGetSfpDetectGpio( unsigned short *sfpDetectGpio);
int BpGetPortMacType(unsigned short port, unsigned int *pulValue );
int BpGetNumFePorts( unsigned int *pulValue );
int BpGetNumGePorts( unsigned int *pulValue );
int BpGetNumVoipPorts( unsigned int *pulValue );
int BpGetSwitchPortMap (unsigned int *pulValue);

int BpGetSpiSlaveResetGpio( unsigned short *pusValue );
int BpGetSpiSlaveBootModeGpio( unsigned short *pusValue );
int BpGetSpiSlaveBusNum( unsigned short *pusValue );
int BpGetSpiSlaveSelectNum( unsigned short *pusValue );
int BpGetSpiSlaveMode( unsigned short *pusValue );
int BpGetSpiSlaveCtrlState( unsigned int *pulValue );
int BpGetSpiSlaveMaxFreq( unsigned int *pulValue );
int BpGetSpiSlaveProtoRev( unsigned short *pusValue );
int BpGetSimInterfaces( unsigned short *pusValue );
int BpGetSlicInterfaces( unsigned short *pusValue );
int BpGetAePolarity( unsigned short *pusValue );
int BpGetPonTxEnGpio( unsigned short *pusValue );
int BpGetPonRxEnGpio( unsigned short *pusValue );
int BpGetPonResetGpio( unsigned short *pusValue );
int BpGetRogueOnuEn( unsigned short *pusValue );
int BpGetGpioLedSim( unsigned short *pusValue );
int BpGetGpioLedSimITMS( unsigned short *pusValue );

int BpGetSerialLEDMuxSel( unsigned short *pusValue );
int BpGetDeviceOptions( unsigned int *pulValue );

int BpGetGpioGpio(int idx, void** token, unsigned short *pusValue);
int BpGetLedGpio(int idx, void** token, unsigned short *pusValue);
int BpGetExtIntrNumGpio(int idx, void** token, unsigned short *pusExtInt, unsigned short *pusGpio);
int BpCheckExtIntr(int ext_int_num, int gpio, int first);
int BpIsGpioInUse(unsigned short gpio);
int BpGetEponGpio(int idx, unsigned short *pusValue);

int BpGetPhyResetGpio(int unit, int port, unsigned short *pusValue);
int BpGetBoardResetGpio(unsigned short *pusValue);
int BpGetUSBGpio(int usb, GPIO_USB_INFO *gpios);
int BpGetPhyAddr(int unit, int port);
int BpGetOpticalWan( unsigned int *pulValue );
int BpGetLedPinMuxGpio(int idx, unsigned short *pusValue);

int BpGetTsync1025mhzPin( unsigned short *pusValue );
int BpGetTsync8khzPin( unsigned short *pusValue );
int BpGetTsync1ppsPin( unsigned short *pusValue );
int BpGetTsyncPonUnstableGpio( unsigned short *pusValue );

int BpGetAllPinmux(int maxnum, int *outcnt, int *errcnt, unsigned short *pusFunction, unsigned int *pulMuxInfo);
int BpGetIfacePinmux(unsigned int interface, int maxnum, int *outcnt, int *errcnt, unsigned short *pusFunction, unsigned int *pulMuxInfo);
int BpGetMemoryConfig( unsigned int *pulValue );
int BpGetBatteryEnable( unsigned short *pusValue );

int BpGetPmdMACEwakeEn( unsigned short *pusValue );
int BpGetPmdAlarmExtIntr( unsigned short *pusValue );
int BpGetPmdInvSerdesRxPol( unsigned short *pusValue );
int BpGetPmdInvSerdesTxPol( unsigned short *pusValue );
int BpGetWanSignalDetectedExtIntr( unsigned short *pusValue );
int BpGetPmdAlarmExtIntrGpio( unsigned short *pusValue );
int BpGetWanSignalDetectedExtIntrGpio( unsigned short *pusValue );
int BpGetGpioPmdReset( unsigned short *pusValue );
int BpGetPmdFunc( unsigned short *pusValue );

int BpGetAttachedInfo(int attached_port_idx, BP_ATTACHED_INFO *bp_attached_info);
int BpGetTrplxrTxFailExtIntr( unsigned short *pusValue );
int BpGetTrplxrTxFailExtIntrGpio( unsigned short *pusValue );
int BpGetTrplxrSdExtIntr( unsigned short *pusValue );
int BpGetTrplxrSdExtIntrGpio( unsigned short *pusValue );
int BpGetTxLaserOnOutN( unsigned short *pusValue );
int BpGet1ppsStableGpio( unsigned short *pusValue );
int BpGetLteResetGpio( unsigned short *pusValue );
int BpGetStrapTxEnGpio( unsigned short *pusValue );
int BpGetWanNco10M( unsigned short *pusValue );
int BpGetTrxSignalDetect( unsigned short *pusValue );
int BpGetWifiOnOffExtIntr( unsigned short *pusValue );
int BpGetWifiOnOffExtIntrGpio( unsigned short *pusValue );
int BpGetLteExtIntr( unsigned short *pusValue );
int BpGetLteExtIntrGpio( unsigned short *pusValue );

int BpGetSDCardDetectExtIntrGpio( unsigned short *pusValue );
int BpGetSDCardDetectExtIntr( unsigned short *pusValue );

int BpGetGpioSpromClk( unsigned short *pusValue );
int BpGetGpioSpromData( unsigned short *pusValue );
int BpGetGpioSpromRst( unsigned short *pusValue );
int BpGetGpioAttachedDevReset( unsigned short *pusValue );
int BpGetXdslDistpointInfo(PXDSL_DISTPOINT_INFO pXdslDistpointInfo);
int BpGetMiiInterfaceEn( unsigned short *pusValue );

int BpGetWanSignalDetectedGpio( unsigned short *pusValue );

int BpGetUsbPwrOn0( unsigned short *pusValue );
int BpGetUsbPwrOn1( unsigned short *pusValue );
int BpGetUsbPwrFlt0( unsigned short *pusValue );
int BpGetUsbPwrFlt1( unsigned short *pusValue );
int BpGetMaxNumCpu( unsigned int *pulValue );
int BpGetDHDMemReserve( int index, unsigned char *pucValue );

int BpEnumCompatChipId( void** token, unsigned int *pulValue );
int BpEnumGpioInitState( void** token, unsigned short *pusValue );






int BpGetTxDisGpio( int lane, unsigned short *pusValue );
int BpGetLedsAdvancedInfo(LEDS_ADVANCED_INFO *pLedsInfo);
int BpGetPciPortDualLane( int port, int *enabled );

int BpGetUsbDis(unsigned short *pusValue);
int BpGetPciDis(unsigned short *pusValue);
int BpGetSataDis(unsigned short *pusValue);

int BpGetWirelessDisGpio(int index, unsigned short *pusValue);

int BpGetWL0ActLedGpio( unsigned short *pusValue );
int BpGetWL1ActLedGpio( unsigned short *pusValue );






struct allocs_rdp {
    unsigned char param1_size;
    unsigned char param2_size;
    unsigned char reserved[2];
};

struct allocs_dhd {
    unsigned char dhd_size[3];
    unsigned char reserved;
};


typedef struct
{
    unsigned int ulVersion;
    char szBootline[256];
    char szBoardId[16];
    unsigned int ulMainTpNum;
    unsigned int ulPsiSize;
    unsigned int ulNumMacAddrs;
    unsigned char ucaBaseMacAddr[6];
    char pad;
    char backupPsi;
    unsigned int ulCheckSumV4;
    char gponSerialNumber[13];
    char gponPassword[11];
    char wpsDevicePin[8];
    char wlanParams[256];
    unsigned int ulSyslogSize;
    unsigned int ulNandPartOfsKb[5];
    unsigned int ulNandPartSizeKb[5];
    char szVoiceBoardId[16];
    unsigned int afeId[2];
    unsigned short opticRxPwrReading;
    unsigned short opticRxPwrOffset;
    unsigned short opticTxPwrReading;
    unsigned char ucUnused2[58];
    unsigned char ucFlashBlkSize;
    unsigned char ucAuxFSPercent;
    unsigned char ucUnused3[2];
    unsigned int ulBoardStuffOption;
    union {
        unsigned int reserved;
        struct allocs_rdp alloc_rdp;
    } allocs;
    unsigned int ulMemoryConfig;
    struct partition_info {

 unsigned short size;
    } part_info[4];
    struct allocs_dhd alloc_dhd;




    unsigned int ulFeatures;
    char chUnused[80];
    char acsPassword[16];
    char variant[6];
    char userPass[8];
    char production;
    char hwVer[4];
    char pcbasn[12];
    char psn[16];
    char iAntenna;
    char iVersion;
    char dslAnnex;
    char rfpi[5];
    char bcm_mod_dev[1];
    char bcm_def_freq[2];
    char fixed_emc[2];
    char szAuthKey[16];
    char szDesKey[32];
    char szWpaKey[32];
    char szSerialNumber[32];

    unsigned int ulCheckSum;
} NVRAM_DATA, *PNVRAM_DATA;

typedef struct
{
        int active_idx;
        unsigned long offset[20];
        unsigned long image_size[20];
        unsigned short image_type[20];

        unsigned short write_fail_count[20];
        int cferom_crc;
}BOOT_BLOCK_MIRROR_INFO;

typedef struct _SP_HEADER
{
    char SPMagicNum[8];
    int SPVersion;
    char NvramData2[20];

} SP_HEADER, *PSP_HEADER;

typedef struct _TOKEN_DEF
{
    char tokenName[16];
    int tokenLen;
} SP_TOKEN, *PSP_TOKEN;

typedef struct
{
    char bootState;
    unsigned char *p;
    int block;
    unsigned int version;
    unsigned int inode;
} JFFS2_SEARCH_STRUCT;


typedef enum
{
    PERSISTENT,
    NVRAM,
    BCM_IMAGE_CFE,
    BCM_IMAGE_FS,
    BCM_IMAGE_KERNEL,
    BCM_IMAGE_WHOLE,
    SCRATCH_PAD,
    FLASH_SIZE,
    SET_CS_PARAM,
    BACKUP_PSI,
    SYSLOG,
    ENVRAM
} BOARD_IOCTL_ACTION;

typedef struct boardIoctParms
{
    union {
     char *string;
     char *value;
 };
    union {
      char *buf;
      char *param;
    };
    union {
        int strLen;
        int value_length;
    };
    int offset;
    BOARD_IOCTL_ACTION action;
    int result;
} BOARD_IOCTL_PARMS;

typedef struct boardMemaccessIoctlParms
{
    int op;
    int space;
    unsigned long long address;
    int size;
    int count;
    char *buf;
} BOARD_MEMACCESS_IOCTL_PARMS;


typedef enum
{
    DG_ENABLE = 0,
    DG_ENABLE_FORCE,
    DG_DISABLE,
    DG_DISABLE_PREVENT_ENABLE,
} DGASP_ENABLE_OPTS;


typedef enum
{
    kLedAdsl,
    kLedSecAdsl,
    kLedWanData,
    kLedSes,
    kLedVoip,
    kLedVoip1,
    kLedVoip2,
    kLedPots,
    kLedDect,
    kLedGpon,
    kLedMoCA,
    kLedEth0Duplex,
    kLedEth0Spd100,
    kLedEth0Spd1000,
    kLedEth1Duplex,
    kLedEth1Spd100,
    kLedEth1Spd1000,







    kLedWL0,
    kLedWL1,
    kLedEnd
} BOARD_LED_NAME;

typedef enum
{
    kLedStateOff,
    kLedStateOn,
    kLedStateFail,
    kLedStateSlowBlinkContinues,
    kLedStateFastBlinkContinues,
    kLedStateUserWpsInProgress,
    kLedStateUserWpsError,
    kLedStateUserWpsSessionOverLap
} BOARD_LED_STATE;

typedef void (*HANDLE_LED_FUNC)(BOARD_LED_STATE ledState);

typedef enum
{
    kGpioInactive,
    kGpioActive
} GPIO_STATE_t;




typedef struct flashaddrinfo
{
    int flash_persistent_start_blk;
    int flash_persistent_number_blk;
    int flash_persistent_length;
    unsigned long flash_persistent_blk_offset;
    int flash_scratch_pad_start_blk;
    int flash_scratch_pad_number_blk;
    int flash_scratch_pad_length;
    unsigned long flash_scratch_pad_blk_offset;
    unsigned long flash_rootfs_start_offset;
    int flash_backup_psi_start_blk;



    int flash_backup_psi_number_blk;


    int flash_syslog_start_blk;
    int flash_syslog_number_blk;
    int flash_syslog_length;


    int flash_meta_start_blk;


} FLASH_ADDR_INFO, *PFLASH_ADDR_INFO;

typedef struct flash_partition_info {

    char name[32];

    int start_blk;
    int number_blk;
    int total_len;
    int sect_size;

    unsigned long blk_offset;


    unsigned long mem_base;
    int mem_length;
} FLASH_PARTITION_INFO, *PFLASH_PARTITION_INFO;



extern void kerSysFlashPartInfoGet(PFLASH_PARTITION_INFO pflash_partition_info);






void flash_init_info(const NVRAM_DATA *nvRam, FLASH_ADDR_INFO *fInfo);

unsigned int flash_get_reserved_bytes_at_end(const FLASH_ADDR_INFO *fInfo);
unsigned int flash_get_reserved_bytes_auxfs(void);


NVRAM_DATA* get_inMemNvramData(void);
int eNvramGet(char *param, char *value, int len);
int eNvramSet(char *param, char *value);
int is_cfe_boot(void);
void sync_nvram_with_flash(void);
void lock_inMemNvramData_mutex(void);
void unlock_inMemNvramData_mutex(void);
static inline int envram_get_locked(char *param, char *value, int len)
{
   int ret=0;
   lock_inMemNvramData_mutex();
   ret=eNvramGet(param, value, len);
   unlock_inMemNvramData_mutex();
   return ret;
}

static inline int envram_set_locked(char *param, char *value)
{
   int ret=0;
   lock_inMemNvramData_mutex();
   ret=eNvramSet(param, value);
   unlock_inMemNvramData_mutex();
   return ret;
}

static inline int envram_sync_set_locked(char *param, char *value)
{
   int ret=0;
   lock_inMemNvramData_mutex();
   ret=eNvramSet(param, value);
   unlock_inMemNvramData_mutex();
   sync_nvram_with_flash();
   return ret;
}


typedef struct cs_config_pars_tag
{
  int mode;
  int base;
  int size;
  int wait_state;
  int setup_time;
  int hold_time;
} cs_config_pars_t;

typedef enum
{
    MAC_ADDRESS_OP_GET=0,
    MAC_ADDRESS_OP_RELEASE,
    MAC_ADDRESS_OP_MAX
} MAC_ADDRESS_OPERATION;

typedef enum
{
 USB_HOST_FUNC,
 USB_DEVICE_FUNC,
 USB_ALL_FUNC
} USB_FUNCTION;


typedef void (* kerSysMacAddressNotifyHook_t)(unsigned char *pucaMacAddr, MAC_ADDRESS_OPERATION op);

void dumpaddr( unsigned char *pAddr, int nLen );

extern void easysoc_netlink_sendmsg(const char *s);

extern void kerSysEarlyFlashInit( void );
extern int kerSysGetChipId( void );
extern char * kerSysGetChipName( char *buf, int len);
extern int kerSysGetDslPhyEnable( void );
extern void kerSysFlashInit( void );
extern void kerSysFlashAddrInfoGet(PFLASH_ADDR_INFO pflash_addr_info);
extern int kerSysCfeVersionGet(char *string, int stringLength);

extern int kerSysNvRamSet(const char *string, int strLen, int offset);
extern void kerSysNvRamGet(char *string, int strLen, int offset);
extern void kerSysNvRamLoad(void * mtd_ptr);
extern void kerSysNvRamGetBootline(char *bootline);
extern void kerSysNvRamGetBootlineLocked(char *bootline);
extern void kerSysNvRamGetBoardId(char *boardId);
extern void kerSysNvRamGetBoardIdLocked(char *boardId);
extern void kerSysNvRamGetBaseMacAddr(unsigned char *baseMacAddr);
extern unsigned long kerSysNvRamGetVersion(void);

extern int kerSysIsRootfsSet(void);
extern int kerSysIsIkosBootSet(void);
extern PFILE_TAG kerSysImageTagGet(void);
extern PFILE_TAG kerSysUpdateTagSequenceNumber(int imageNumber);

extern void kerSysSendtoMonitorTask(int msgType, char *msgData, int msgDataLen);

extern void kerSysDisableDyingGaspInterrupt(void);
extern void kerSysEnableDyingGaspInterrupt(void);






extern int kerSysIsBatteryEnabled(void);
extern int kerSysGetResetStatus(void);

extern int kerSysFsFileSet(const char *filename, char *buf, int len);
extern int kerSysFsFileGet(const char *filename, char *buf, int len);
extern int kerSysPersistentGet(char *string, int strLen, int offset);
extern int kerSysPersistentSet(char *string, int strLen, int offset);
extern int kerSysBackupPsiGet(char *string, int strLen, int offset);
extern int kerSysBackupPsiSet(char *string, int strLen, int offset);
extern int kerSysSyslogGet(char *string, int strLen, int offset);
extern int kerSysSyslogSet(char *string, int strLen, int offset);
extern int kerSysScratchPadList(char *tokBuf, int tokLen);
extern int kerSysScratchPadGet(char *tokName, char *tokBuf, int tokLen);
extern int kerSysScratchPadSet(char *tokName, char *tokBuf, int tokLen);
extern int kerSysScratchPadClearAll(void);
extern int kerSysBcmImageSet( int flash_start_addr, char *string, int size,
    int should_yield);
extern int kerSysGetSequenceNumber(int imageNumber);
extern int kerSysSetBootImageState( int state );
extern int kerSysGetBootImageState( void );
extern int kerSysSetOpticalPowerValues(unsigned short rxReading, unsigned short rxOffset,
    unsigned short txReading);
extern int kerSysGetOpticalPowerValues(unsigned short *prxReading, unsigned short *prxOffset,
    unsigned short *ptxReading);
extern int kerSysBlParmsGetInt( char *name, int *pvalue );
extern int kerSysBlParmsGetStr( char *name, char *pvalue, int size );
extern unsigned long kerSysGetMacAddressType( unsigned char *ifName );
extern int kerSysMacAddressNotifyBind(kerSysMacAddressNotifyHook_t hook);
extern int kerSysGetMacAddress( unsigned char *pucaAddr, unsigned long ulId );
extern int kerSysReleaseMacAddress( unsigned char *pucaAddr );
extern int kerSysGetMacAddresses( unsigned char *pucaMacAddr, unsigned int num_addresses, unsigned long ulId );
extern int kerSysReleaseMacAddresses( unsigned char *pucaMacAddr, unsigned int num_addresses );
extern void kerSysGetGponSerialNumber( unsigned char *pGponSerialNumber);
extern void kerSysGetGponPassword( unsigned char *pGponPassword);
extern int kerSysGetSdramSize( void );
extern void kerSysGetBootline(char *string, int strLen);
extern void kerSysSetBootline(char *string, int strLen);
extern void kerSysSoftReset(void);
extern void kerSysLedCtrl(BOARD_LED_NAME, BOARD_LED_STATE);
extern int kerSysFlashSizeGet(void);
extern int kerSysMemoryMappedFlashSizeGet(void);
extern unsigned long kerSysReadFromFlash( void *toaddr, unsigned long fromaddr, unsigned long len );
extern int kerSysEraseFlash(unsigned long eraseaddr, unsigned long len);
extern int kerSysWriteToFlash( unsigned long toaddr, void * fromaddr, unsigned long len);
extern void kerSysRegisterDyingGaspHandler(char *devname, void *cbfn, void *context);
extern void kerSysDeregisterDyingGaspHandler(char *devname);
extern int kerSysIsDyingGaspTriggered(void);
extern int kerConfigCs(BOARD_IOCTL_PARMS *parms);

extern int kerSysGetPciePortEnable(int port);
extern int kerSysGetPciePortMode(int port);
extern int kerSysGetSataPortEnable(void);
extern int kerSysGetUsbHostPortEnable(int port);
extern int kerSysGetUsbDeviceEnable(void);
extern int kerSysGetUsb30HostEnable(void);
extern int kerSysSetUsbPower(int on, USB_FUNCTION func);
extern void kerSysSetBootParm(char *name, char *value);
extern void kerSysInitPinmuxInterface(unsigned int interface);

extern unsigned char kerSysGetWlanFeature(void);
unsigned int kerSysGetWifiLed(unsigned char core);
void kerSysWifiLed(unsigned int led, unsigned int on);

extern void kerSysSetGpioState(unsigned short bpGpio, GPIO_STATE_t state);
extern void kerSysSetGpioStateLocked(unsigned short bpGpio, GPIO_STATE_t state);
extern void kerSysSetGpioDir(unsigned short bpGpio);
extern void kerSysSetGpioDirLocked(unsigned short bpGpio);
extern int kerSysSetGpioDirInput(unsigned short bpGpio);
extern int kerSysGetGpioValue(unsigned short bpGpio);






extern unsigned int kerSysGetUbusFreq(unsigned int miscStrapBus);
extern int kerSysGetAfeId( unsigned int *afeId );


typedef void (*MocaHostIntrCallback)(int irq, void * arg);
extern void kerSysMocaHostIntrReset(int dev);
extern void kerSysRegisterMocaHostIntrCallback(MocaHostIntrCallback callback, void * userArg, int dev);
extern void kerSysMocaHostIntrEnable(int dev);
extern void kerSysMocaHostIntrDisable(int dev);

extern unsigned int kerSysGetExtIntInfo(unsigned int irq);

void kerSysRegisterPlcUkeCallback( void (* callback)(unsigned long timeInMs, void* param), void* param );
void kerSysDeregisterPlcUkeCallback( void (* callback)(unsigned long timeInMs, void* param) );
void kerSysRegisterPlcRandomizeCallback( void (* callback)(unsigned long timeInMs, void* param), void* param );
void kerSysDeregisterPlcRandomizeCallback( void (* callback)(unsigned long timeInMs, void* param) );


extern void* kerSysGetDslPhyMemory(void);

extern const unsigned char* bcm_get_blparms(void);
unsigned int bcm_get_blparms_size(void);

extern int rdp_post_init(void);




unsigned int for_script_image_base=(0xA0000000 | 0x1FC00000);
unsigned int for_script_nvram_offset=0x0580;
int for_script_numOfMac = 10;
int for_script_tpNum = 0;
int for_script_psiSize = 128;
int for_script_logSize= 0;
int for_script_backupPsi = 0;
int for_script_flashBlkSize = 64;
int for_script_auxFSPercent = 0;
int for_script_token_len = 20;
int for_script_pmc_flag_bit=0x1;
