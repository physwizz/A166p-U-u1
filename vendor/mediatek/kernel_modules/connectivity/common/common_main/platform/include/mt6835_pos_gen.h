/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2022 MediaTek Inc.
 */


/* AUTO-GENERATED FILE.  DO NOT MODIFY.
 *
 * This file, mt6835_pos_gen.h was automatically generated
 * by the tool from the POS data DE provided.
 * It should not be modified by hand.
 *
 * Reference POS file,
 * - Cxxxxxn_connsys_power_on_sequence_20220322.xlsx
 */


#ifndef MT6835_POS_GEN_H
#define MT6835_POS_GEN_H

void consys_set_if_pinmux_mt6835_gen(int enable);
void consys_hw_reset_bit_set_mt6835_gen(int enable);
void consys_hw_spm_clk_gating_enable_mt6835_gen(void);
int consys_hw_power_ctrl_mt6835_gen(int enable);
int polling_consys_chipid_mt6835_gen(unsigned int *pconsys_ver_id, unsigned int *pconsys_fw_ver);
void consys_set_access_emi_hw_mode_mt6835_gen(void);
void consys_emi_entry_address_mt6835_gen(void);
void consys_set_xo_osc_ctrl_mt6835_gen(void);
void consys_identify_adie_mt6835_gen(void);
void consys_wifi_ctrl_setting_mt6835_gen(void);
void consys_bus_timeout_config_mt6835_gen(void);
void consys_bus_config_gps_access_tia_mt6835_gen(void);
int consys_polling_goto_idle_mt6835_gen(unsigned int *pconsys_ver_id);
void consys_wifi_ctrl_switch_conn_mode_mt6835_gen(void);

/**********************************************************************************/
/* Base: CONSYS_GEN_GPIO_BASE_ADDR (0x1000_5000)                                  */
/**********************************************************************************/
#define CONSYS_GEN_GPIO_BASE_ADDR                                         0x10005000
#define CONSYS_GEN_GPIO_DIR5_OFFSET_ADDR                                  0x50
#define CONSYS_GEN_GPIO_DOUT5_OFFSET_ADDR                                 0x150
#define CONSYS_GEN_GPIO_MODE3_OFFSET_ADDR                                 0x330
#define CONSYS_GEN_GPIO_MODE18_OFFSET_ADDR                                0x420
#define CONSYS_GEN_GPIO_MODE21_OFFSET_ADDR                                0x450
#define CONSYS_GEN_GPIO_MODE22_OFFSET_ADDR                                0x460

/**********************************************************************************/
/* Base: CONSYS_GEN_IOCFG_RT_BASE_ADDR (0x11EC_0000)                              */
/**********************************************************************************/
#define CONSYS_GEN_IOCFG_RT_BASE_ADDR                                     0x11EC0000
#define CONSYS_GEN_DRV_CFG0_SET_OFFSET_ADDR                               0x4
#define CONSYS_GEN_DRV_CFG1_SET_OFFSET_ADDR                               0x14
#define CONSYS_GEN_PU_SET_OFFSET_ADDR                                     0x74
#define CONSYS_GEN_PU_CLR_OFFSET_ADDR                                     0x78
#define CONSYS_GEN_PD_SET_OFFSET_ADDR                                     0x64
#define CONSYS_GEN_PD_CLR_OFFSET_ADDR                                     0x68

/**********************************************************************************/
/* Base: conn_reg.ap_rgu_base (0x1C00_7000)                                       */
/**********************************************************************************/
#define CONSYS_GEN_WDT_VCORE_SWSYSRST0_OFFSET_ADDR                        0x208

/**********************************************************************************/
/* Base: conn_reg.spm_base (0x1C00_1000)                                          */
/**********************************************************************************/
#define CONSYS_GEN_POWERON_CONFIG_EN_OFFSET_ADDR                          0x0
#define CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR                               0xE04

/**********************************************************************************/
/* Base: conn_reg.topckgen_base (0x1000_1000)                                     */
/**********************************************************************************/
#define CONSYS_GEN_INFRASYS_PROTECT_EN_STA_0_OFFSET_ADDR                  0xC40
#define CONSYS_GEN_INFRASYS_PROTECT_RDY_STA_0_OFFSET_ADDR                 0xC4C
#define CONSYS_GEN_INFRASYS_PROTECT_EN_STA_1_OFFSET_ADDR                  0xC50
#define CONSYS_GEN_INFRASYS_PROTECT_RDY_STA_1_OFFSET_ADDR                 0xC5C
#define CONSYS_GEN_MCU_CONNSYS_PROTECT_EN_STA_0_OFFSET_ADDR               0xC90
#define CONSYS_GEN_MCU_CONNSYS_PROTECT_RDY_STA_0_OFFSET_ADDR              0xC9C

/**********************************************************************************/
/* Base: conn_reg.mcu_top_misc_off_base (0x180B_1000)                             */
/**********************************************************************************/
#define CONSYS_GEN_CONN_CONNSYS_VERSION_OFFSET_ADDR                       0x10
#define CONSYS_GEN_CONN_CONNSYS_CONFIG_OFFSET_ADDR                        0x1C

/**********************************************************************************/
/* Base: CONSYS_GEN_CONN_HW_VER (0x100D_0000)                                     */
/**********************************************************************************/
#define CONSYS_GEN_CONN_HW_VER                                            0x100D0000

/**********************************************************************************/
/* Base: conn_reg.mcu_base (0x1800_2000)                                          */
/**********************************************************************************/
#define CONSYS_GEN_HW_VER_OFFSET_ADDR                                     0x0
#define CONSYS_GEN_FW_VER_OFFSET_ADDR                                     0x4
#define CONSYS_GEN_TO_INFRA_CR_CTL_OFFSET_ADDR                            0x17C
#define CONSYS_GEN_BUSHANGCR_OFFSET_ADDR                                  0x440
#define CONSYS_GEN_BT_EMI_ENTRY_ADDR_OFFSET_ADDR                          0x504
#define CONSYS_GEN_WF_EMI_ENTRY_ADDR_OFFSET_ADDR                          0x508
#define CONSYS_GEN_COM_REG0_OFFSET_ADDR                                   0x600

/**********************************************************************************/
/* Base: conn_reg.mcu_top_misc_on_base (0x180C_1000)                              */
/**********************************************************************************/
#define CONSYS_GEN_CONN_ON_RSV_OFFSET_ADDR                                0x130
#define CONSYS_GEN_CONN_CFG_ON_CONN_ON_RSV_OFFSET_ADDR                    0x130
#define CONSYS_GEN_CONN_ON_MCU_EMI_SLPPROT_EN_OFFSET_ADDR                 0x168
#define CONSYS_GEN_CONN_ON_OSC_CTL_OFFSET_ADDR                            0x200
#define CONSYS_GEN_CONN_ON_OSC_CTL_2_OFFSET_ADDR                          0x204
#define CONSYS_GEN_CONN_CFG_ON_CONN_ON_OSC_CTL_2_OFFSET_ADDR              0x204
#define CONSYS_GEN_CONN_ON_RC_OSC_CTL_0_OFFSET_ADDR                       0x240
#define CONSYS_GEN_CONN_CFG_ON_CONN_ON_RC_OSC_CTL_0_OFFSET_ADDR           0x240
#define CONSYS_GEN_CONN_ON_RC_OSC_CTL_GPS_0_OFFSET_ADDR                   0x244
#define CONSYS_GEN_CONN_CFG_ON_CONN_ON_RC_OSC_CTL_GPS_0_OFFSET_ADDR       0x244
#define CONSYS_GEN_CONN_ON_RC_OSC_CTL_GPS_1_OFFSET_ADDR                   0x248
#define CONSYS_GEN_CONN_ON_RC_OSC_CTL_BT_0_OFFSET_ADDR                    0x24c
#define CONSYS_GEN_CONN_CFG_ON_CONN_ON_RC_OSC_CTL_BT_0_OFFSET_ADDR        0x24c
#define CONSYS_GEN_CONN_ON_RC_OSC_CTL_BT_1_OFFSET_ADDR                    0x250
#define CONSYS_GEN_CONN_ON_RC_OSC_CTL_WF_0_OFFSET_ADDR                    0x254
#define CONSYS_GEN_CONN_CFG_ON_CONN_ON_RC_OSC_CTL_WF_0_OFFSET_ADDR        0x254
#define CONSYS_GEN_CONN_ON_RC_OSC_CTL_WF_1_OFFSET_ADDR                    0x258
#define CONSYS_GEN_CONN_ON_RC_OSC_CTL_TOP_0_OFFSET_ADDR                   0x25c
#define CONSYS_GEN_CONN_CFG_ON_CONN_ON_RC_OSC_CTL_TOP_0_OFFSET_ADDR       0x25c
#define CONSYS_GEN_CONN_ON_RC_OSC_CTL_TOP_1_OFFSET_ADDR                   0x260

/**********************************************************************************/
/* Base: CONSYS_GEN_CONN_RGU_ON_BASE_ADDR (0x180C_0000)                           */
/**********************************************************************************/
#define CONSYS_GEN_CONN_RGU_ON_BASE_ADDR                                  0x180C0000
#define CONSYS_GEN_MCUSYS_DLY_CHAIN_CTL_OFFSET_ADDR                       0x284

/**********************************************************************************/
/* Base: conn_reg.mcu_conn_hif_on_base (0x1800_7000)                              */
/**********************************************************************************/
#define CONSYS_GEN_CONN_HIF_ON_CONN_CFG_OFFSET_ADDR                       0x24
#define CONSYS_GEN_CONN_HIF_HOST_CSR_CONN_HIF_ON_CONN_CFG_OFFSET_ADDR     0x24

#endif /* MT6835_POS_GEN_H */
