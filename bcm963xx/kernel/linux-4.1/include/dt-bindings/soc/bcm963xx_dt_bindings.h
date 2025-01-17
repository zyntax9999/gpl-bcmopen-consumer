#ifndef __BCM63XX_DT_BINDINGS_H
#define __BCM63XX_DT_BINDINGS_H
#define CONFIG_BCM_CHIP_NUMBER 6846
#define CONFIG_BRCM_CHIP_REV 0x6846
#define CONFIG_BCM_RDPA
#define CONFIG_BCM_GLB_COHERENCY
#define CONFIG_BCM_PCIE_HCD
 #define RDP_PARAM1_DDR_SIZE ((16)*0x100000)
 #define RDP_PARAM2_DDR_SIZE ((8)*0x100000)
 #define DRAM_OFFSET_RDP_PARAM1 ((0x00000000 +0x04000000)-((16)*0x100000))
 #define DRAM_OFFSET_RDP_PARAM2 (((0x00000000 +0x04000000)-((16)*0x100000))-((8)*0x100000))
 #define DRAM_BASE 0x00000000
 #define DRAM_DEF_SIZE 0x04000000
#endif /*__BCM63XX_DT_BINDINGS_H */
