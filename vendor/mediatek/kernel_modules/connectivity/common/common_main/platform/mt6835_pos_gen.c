/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2022 MediaTek Inc.
 */


/* AUTO-GENERATED FILE.  DO NOT MODIFY.
 *
 * This file, mt6835_pos_gen.c was automatically generated
 * by the tool from the POS data DE provided.
 * It should not be modified by hand.
 *
 * Reference POS file,
 * - Cxxxxxn_connsys_power_on_sequence_20220322.xlsx
 */


#include <linux/types.h>
#include <linux/clk.h>
#include <linux/io.h>
#include "osal_typedef.h"
#include "mt6835.h"
#include "mt6835_pos_gen.h"
#include "mtk_wcn_consys_hw.h"


void consys_set_if_pinmux_mt6835_gen(int enable)
{
	void __iomem *vir_addr_consys_gen_gpio_base = NULL;
	void __iomem *vir_addr_consys_gen_iocfg_rt_base = NULL;

	vir_addr_consys_gen_gpio_base =
		ioremap(CONSYS_GEN_GPIO_BASE_ADDR, 0x460);
	vir_addr_consys_gen_iocfg_rt_base =
		ioremap(CONSYS_GEN_IOCFG_RT_BASE_ADDR, 0x14);

	if (!vir_addr_consys_gen_gpio_base) {
		pr_notice("vir_addr_consys_gen_gpio_base(%x) ioremap fail\n",
			CONSYS_GEN_GPIO_BASE_ADDR);
		return;
	}

	if (!vir_addr_consys_gen_iocfg_rt_base) {
		pr_notice("vir_addr_consys_gen_iocfg_rt_base(%x) ioremap fail\n",
			CONSYS_GEN_IOCFG_RT_BASE_ADDR);
		iounmap(vir_addr_consys_gen_gpio_base);
		return;
	}

	if (enable == 1) {
		/* set pinmux for the interface between D-die and A-die (Aux1) */
		CONSYS_REG_WRITE_MASK(vir_addr_consys_gen_gpio_base +
			CONSYS_GEN_GPIO_MODE21_OFFSET_ADDR, 0x11110000, 0x77770000);
		CONSYS_REG_WRITE_MASK(vir_addr_consys_gen_gpio_base +
			CONSYS_GEN_GPIO_MODE22_OFFSET_ADDR, 0x11111, 0x77777);

		/* set BT_SPI and TOP_SPI pinmux driving to 4mA */
		/* (TOP_SPI 8 mA for bring up ), */
		/* others keep default driving 2mA */
		CONSYS_REG_WRITE_MASK(vir_addr_consys_gen_iocfg_rt_base +
			CONSYS_GEN_DRV_CFG0_SET_OFFSET_ADDR, 0x9240000, 0x3FFC0000);
		CONSYS_REG_WRITE_MASK(vir_addr_consys_gen_iocfg_rt_base +
			CONSYS_GEN_DRV_CFG1_SET_OFFSET_ADDR, 0x0, 0x1F8);

		/* set GPIO24 or GPIO151 pinmux for TCXO mode (Aux1) */
		#if CLK_CTRL_TCXOENA_REQ
			if (wmt_plat_soc_co_clock_flag_get() == 0) {
				CONSYS_REG_WRITE_MASK(vir_addr_consys_gen_gpio_base +
					CONSYS_GEN_GPIO_MODE3_OFFSET_ADDR, 0x1, 0x7);
				CONSYS_REG_WRITE_MASK(vir_addr_consys_gen_gpio_base +
					CONSYS_GEN_GPIO_MODE18_OFFSET_ADDR, 0x10000000, 0x70000000);
			}
		#endif
		/* set pinmux PUPD setting: CONN_TOP_DATA/CONN_BT_DATA as PU */
		if (mtk_wcn_consys_get_adie_chipid() == TERTIARY_ADIE) {
			CONSYS_REG_WRITE_MASK(vir_addr_consys_gen_iocfg_rt_base +
				CONSYS_GEN_PU_SET_OFFSET_ADDR, 0x900, 0x900);
			CONSYS_REG_WRITE_MASK(vir_addr_consys_gen_iocfg_rt_base +
				CONSYS_GEN_PD_CLR_OFFSET_ADDR, 0x900, 0x900);
		}
	} else {
		/* set pinmux for the interface between D-die and A-die (Aux0) */
		CONSYS_REG_WRITE_MASK(vir_addr_consys_gen_gpio_base +
			CONSYS_GEN_GPIO_MODE21_OFFSET_ADDR, 0x0, 0x77770000);
		CONSYS_REG_WRITE_MASK(vir_addr_consys_gen_gpio_base +
			CONSYS_GEN_GPIO_MODE22_OFFSET_ADDR, 0x0, 0x77777);

		/* set GPIO24 or GPIO151 pinmux for TCXO mode (Aux0) */
		#if CLK_CTRL_TCXOENA_REQ
			if (wmt_plat_soc_co_clock_flag_get() == 0) {
				CONSYS_REG_WRITE_MASK(vir_addr_consys_gen_gpio_base +
					CONSYS_GEN_GPIO_MODE3_OFFSET_ADDR, 0x0, 0x7);
				CONSYS_REG_WRITE_MASK(vir_addr_consys_gen_gpio_base +
					CONSYS_GEN_GPIO_MODE18_OFFSET_ADDR, 0x0, 0x70000000);
			}
		#endif

		/*set pinmux PUPD setting: CONN_TOP_DATA/CONN_BT_DATA as PD */
		if (mtk_wcn_consys_get_adie_chipid() == TERTIARY_ADIE) {
			CONSYS_REG_WRITE_MASK(vir_addr_consys_gen_iocfg_rt_base +
				CONSYS_GEN_PD_SET_OFFSET_ADDR, 0x900, 0x900);
			CONSYS_REG_WRITE_MASK(vir_addr_consys_gen_iocfg_rt_base +
				CONSYS_GEN_PU_CLR_OFFSET_ADDR, 0x900, 0x900);
		}
	}

	if (vir_addr_consys_gen_gpio_base)
		iounmap(vir_addr_consys_gen_gpio_base);

	if (vir_addr_consys_gen_iocfg_rt_base)
		iounmap(vir_addr_consys_gen_iocfg_rt_base);
}

void consys_hw_reset_bit_set_mt6835_gen(int enable)
{
	if (conn_reg.ap_rgu_base == 0) {
		pr_notice("conn_reg.ap_rgu_base is not defined\n");
		return;
	}

	if (conn_reg.mcu_conn_hif_on_base == 0) {
		pr_notice("conn_reg.mcu_conn_hif_on_base is not defined\n");
		return;
	}

	if (enable == 1) {
		/* assert CONNSYS CPU SW reset (apply this for default value patching) */
		CONSYS_REG_WRITE_MASK(conn_reg.ap_rgu_base +
			CONSYS_GEN_WDT_VCORE_SWSYSRST0_OFFSET_ADDR, 0x88000001, 0xFF000001);
	} else {
		/* de-assert CONNSYS CPU SW reset */
		CONSYS_REG_WRITE_MASK(conn_reg.ap_rgu_base +
			CONSYS_GEN_WDT_VCORE_SWSYSRST0_OFFSET_ADDR, 0x88000000, 0xFF000001);

		/* de-assert CONNSYS CPU SW reset (locate at host csr) */
		CONSYS_SET_BIT(conn_reg.mcu_conn_hif_on_base +
			CONSYS_GEN_CONN_HIF_ON_CONN_CFG_OFFSET_ADDR, (0x1U << 0));
	}
}

void consys_hw_spm_clk_gating_enable_mt6835_gen(void)
{
	if (conn_reg.spm_base == 0) {
		pr_notice("conn_reg.spm_base is not defined\n");
		return;
	}

	/* turn on SPM clock */
	/* (apply this for SPM's CONNSYS power control related CR accessing) */
	CONSYS_REG_WRITE_MASK(conn_reg.spm_base +
		CONSYS_GEN_POWERON_CONFIG_EN_OFFSET_ADDR, 0xB160001, 0xFFFF0001);
}

int consys_hw_power_ctrl_mt6835_gen(int enable)
{
	int check = 0;

	if (conn_reg.spm_base == 0) {
		pr_notice("conn_reg.spm_base is not defined\n");
		return -1;
	}

	if (conn_reg.topckgen_base == 0) {
		pr_notice("conn_reg.topckgen_base is not defined\n");
		return -1;
	}

	if (conn_reg.mcu_conn_hif_on_base == 0) {
		pr_notice("conn_reg.mcu_conn_hif_on_base is not defined\n");
		return -1;
	}

	if (enable == 1) {
		/* assert "conn_top_on" primary part power on, set "connsys_on_domain_pwr_on"=1 */
		CONSYS_SET_BIT(conn_reg.spm_base +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1U << 2));

		/* check "conn_top_on" primary part power status, */
		/* check "connsys_on_domain_pwr_ack"=1 */
		/* (polling "10 times" and each polling interval is "0.5ms") */
		check = 0;
		CONSYS_REG_BIT_POLLING(conn_reg.spm_base +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR,
			30, 1, 10, 500, check);
		if (check != 0) {
			pr_notice("check conn_top_on primary part power status fail, Status=0x%08x\n",
				CONSYS_REG_READ(conn_reg.spm_base +
					CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR));
		}

		/* assert "conn_top_on" secondary part power on, */
		/* set "connsys_on_domain_pwr_on_s"=1 */
		CONSYS_SET_BIT(conn_reg.spm_base +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1U << 3));

		/* check "conn_top_on" secondary part power status, */
		/* check "connsys_on_domain_pwr_ack_s"=1 */
		/* (polling "10 times" and each polling interval is "0.5ms") */
		check = 0;
		CONSYS_REG_BIT_POLLING(conn_reg.spm_base +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR,
			31, 1, 10, 500, check);
		if (check != 0) {
			pr_notice("check conn_top_on secondary part power status fail, Status=0x%08x\n",
				CONSYS_REG_READ(conn_reg.spm_base +
					CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR));
		}

		/* turn on AP-to-CONNSYS bus clock, */
		/* set "conn_clk_dis"=0 */
		/* (apply this for bus clock toggling) */
		CONSYS_CLR_BIT(conn_reg.spm_base +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1U << 4));

		udelay(1);

		/* de-assert "conn_top_on" isolation, set "connsys_iso_en"=0 */
		CONSYS_CLR_BIT(conn_reg.spm_base +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1U << 1));

		/* de-assert CONNSYS S/W reset (SPM CR), set "conn_pwr_rst_b"=1 */
		CONSYS_SET_BIT(conn_reg.spm_base +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1U << 0));

		mdelay(5);

		udelay(10);

		/* Turn off AHB RX bus sleep protect */
		/* (AP2CONN AHB Bus protect) */
		/* (apply this for INFRA AHB bus accessing when CONNSYS had been turned on) */
		CONSYS_CLR_BIT(conn_reg.topckgen_base +
			CONSYS_GEN_MCU_CONNSYS_PROTECT_EN_STA_0_OFFSET_ADDR, (0x1U << 0));

		/* check AHB RX bus sleep protect turn off */
		/* (polling "10 times" and each polling interval is "0.5ms") */
		check = 0;
		CONSYS_REG_BIT_POLLING(conn_reg.topckgen_base +
			CONSYS_GEN_MCU_CONNSYS_PROTECT_RDY_STA_0_OFFSET_ADDR,
			0, 0, 10, 500, check);
		if (check != 0) {
			pr_notice("check AHB RX bus sleep protect turn off fail, Status=0x%08x\n",
				CONSYS_REG_READ(conn_reg.topckgen_base +
					CONSYS_GEN_MCU_CONNSYS_PROTECT_RDY_STA_0_OFFSET_ADDR));
		}

		/* Turn off AXI Rx bus sleep protect */
		/* (CONN2AP AXI Rx Bus protect) */
		/* (disable sleep protection when CONNSYS had been turned on) */
		CONSYS_CLR_BIT(conn_reg.topckgen_base +
			CONSYS_GEN_INFRASYS_PROTECT_EN_STA_0_OFFSET_ADDR, (0x1U << 8));

		/* check AXI Rx bus sleep protect turn off */
		/* (polling "10 times" and each polling interval is "0.5ms") */
		check = 0;
		CONSYS_REG_BIT_POLLING(conn_reg.topckgen_base +
			CONSYS_GEN_INFRASYS_PROTECT_RDY_STA_0_OFFSET_ADDR,
			8, 0, 10, 500, check);
		if (check != 0) {
			pr_notice("check AXI Rx bus sleep protect turn off fail, Status=0x%08x\n",
				CONSYS_REG_READ(conn_reg.topckgen_base +
					CONSYS_GEN_INFRASYS_PROTECT_RDY_STA_0_OFFSET_ADDR));
		}

		/* Turn off AXI TX bus sleep protect */
		/* (CONN2AP AXI Tx Bus protect) */
		/* (disable sleep protection when CONNSYS had been turned on) */
		CONSYS_CLR_BIT(conn_reg.topckgen_base +
			CONSYS_GEN_MCU_CONNSYS_PROTECT_EN_STA_0_OFFSET_ADDR, (0x1U << 1));

		/* check AXI Tx bus sleep protect turn off */
		/* (polling "10 times" and each polling interval is "0.5ms") */
		check = 0;
		CONSYS_REG_BIT_POLLING(conn_reg.topckgen_base +
			CONSYS_GEN_MCU_CONNSYS_PROTECT_RDY_STA_0_OFFSET_ADDR,
			1, 0, 10, 500, check);
		if (check != 0) {
			pr_notice("check AXI Tx bus sleep protect turn off fail, Status=0x%08x\n",
				CONSYS_REG_READ(conn_reg.topckgen_base +
					CONSYS_GEN_MCU_CONNSYS_PROTECT_RDY_STA_0_OFFSET_ADDR));
		}

		/* Turn off AHB TX bus sleep protect */
		/* (AP2CONN AHB Bus protect) */
		/* (apply this for INFRA AHB bus accessing when CONNSYS had been turned on) */
		CONSYS_CLR_BIT(conn_reg.topckgen_base +
			CONSYS_GEN_INFRASYS_PROTECT_EN_STA_1_OFFSET_ADDR, (0x1U << 12));

		/* check AHB TX bus sleep protect turn off */
		/* (polling "10 times" and each polling interval is "0.5ms") */
		check = 0;
		CONSYS_REG_BIT_POLLING(conn_reg.topckgen_base +
			CONSYS_GEN_INFRASYS_PROTECT_RDY_STA_1_OFFSET_ADDR,
			12, 0, 10, 500, check);
		if (check != 0) {
			pr_notice("check AHB TX bus sleep protect turn off fail, Status=0x%08x\n",
				CONSYS_REG_READ(conn_reg.topckgen_base +
					CONSYS_GEN_INFRASYS_PROTECT_RDY_STA_1_OFFSET_ADDR));
		}
	} else {
		/* assert CONNSYS CPU SW reset (locate at host csr) */
		CONSYS_CLR_BIT(conn_reg.mcu_conn_hif_on_base +
			CONSYS_GEN_CONN_HIF_HOST_CSR_CONN_HIF_ON_CONN_CFG_OFFSET_ADDR, (0x1U << 0));

		/* Turn on AHB TX bus sleep protect */
		/* (AP2CONN AHB Bus protect) */
		/* (apply this for INFRA AXI bus protection to prevent bus hang when CONNSYS had been turned off) */
		CONSYS_SET_BIT(conn_reg.topckgen_base +
			CONSYS_GEN_INFRASYS_PROTECT_EN_STA_1_OFFSET_ADDR, (0x1U << 12));

		/* check AHB TX bus sleep protect turn on (polling "10 times") */
		check = 0;
		CONSYS_REG_BIT_POLLING(conn_reg.topckgen_base +
			CONSYS_GEN_INFRASYS_PROTECT_RDY_STA_1_OFFSET_ADDR,
			12, 1, 10, 1000, check);
		if (check != 0) {
			pr_notice("check AHB TX bus sleep protect turn on fail, Status=0x%08x\n",
				CONSYS_REG_READ(conn_reg.topckgen_base +
					CONSYS_GEN_INFRASYS_PROTECT_RDY_STA_1_OFFSET_ADDR));
		}

		/* Turn on AXI Tx bus sleep protect */
		/* (CONN2AP AXI Tx Bus protect) */
		/* (apply this for INFRA AXI bus protection to prevent bus hang when CONNSYS had been turned off) */
		CONSYS_SET_BIT(conn_reg.topckgen_base +
			CONSYS_GEN_MCU_CONNSYS_PROTECT_EN_STA_0_OFFSET_ADDR, (0x1U << 1));

		/* check AXI Tx bus sleep protect turn on */
		/* (polling "100 times", */
		/* polling interval is 1ms) */
		check = 0;
		CONSYS_REG_BIT_POLLING(conn_reg.topckgen_base +
			CONSYS_GEN_MCU_CONNSYS_PROTECT_RDY_STA_0_OFFSET_ADDR,
			1, 1, 100, 1000, check);
		if (check != 0) {
			pr_notice("check AXI Tx bus sleep protect turn on fail, Status=0x%08x\n",
				CONSYS_REG_READ(conn_reg.topckgen_base +
					CONSYS_GEN_MCU_CONNSYS_PROTECT_RDY_STA_0_OFFSET_ADDR));
		}

		/* Turn on AXI Rx bus sleep protect */
		/* (CONN2AP AXI RX Bus protect) */
		/* (apply this for INFRA AXI bus protection to prevent bus hang when CONNSYS had been turned off) */
		CONSYS_SET_BIT(conn_reg.topckgen_base +
			CONSYS_GEN_INFRASYS_PROTECT_EN_STA_0_OFFSET_ADDR, (0x1U << 8));

		/* check AXI Rx bus sleep protect turn on */
		/* (polling "100 times", */
		/* polling interval is 1ms) */
		check = 0;
		CONSYS_REG_BIT_POLLING(conn_reg.topckgen_base +
			CONSYS_GEN_INFRASYS_PROTECT_RDY_STA_0_OFFSET_ADDR,
			8, 1, 100, 1000, check);
		if (check != 0) {
			pr_notice("check AXI Rx bus sleep protect turn on fail, Status=0x%08x\n",
				CONSYS_REG_READ(conn_reg.topckgen_base +
					CONSYS_GEN_INFRASYS_PROTECT_RDY_STA_0_OFFSET_ADDR));
		}

		/* Turn on AHB RX bus sleep protect */
		/* (AP2CONN AHB Bus protect) */
		/* (apply this for INFRA AXI bus protection to prevent bus hang when CONNSYS had been turned off) */
		CONSYS_SET_BIT(conn_reg.topckgen_base +
			CONSYS_GEN_MCU_CONNSYS_PROTECT_EN_STA_0_OFFSET_ADDR, (0x1U << 0));

		/* check AHB RX bus sleep protect turn on (polling "10 times") */
		check = 0;
		CONSYS_REG_BIT_POLLING(conn_reg.topckgen_base +
			CONSYS_GEN_MCU_CONNSYS_PROTECT_RDY_STA_0_OFFSET_ADDR,
			0, 1, 10, 1000, check);
		if (check != 0) {
			pr_notice("check AHB RX bus sleep protect turn on fail, Status=0x%08x\n",
				CONSYS_REG_READ(conn_reg.topckgen_base +
					CONSYS_GEN_MCU_CONNSYS_PROTECT_RDY_STA_0_OFFSET_ADDR));
		}

		/* assert "conn_top_on" isolation, set "connsys_iso_en"=1 */
		CONSYS_SET_BIT(conn_reg.spm_base +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1U << 1));

		/* assert CONNSYS S/W reset (SPM CR), set "conn_pwr_rst_b"=0 */
		CONSYS_CLR_BIT(conn_reg.spm_base +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1U << 0));

		/* turn off AP-to-CONNSYS bus clock, */
		/* set "conn_clk_dis"=1 */
		/* (apply this for bus clock gating) */
		CONSYS_SET_BIT(conn_reg.spm_base +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1U << 4));

		udelay(1);

		/* de-assert "conn_top_on" primary part power on, set "connsys_on_domain_pwr_on"=0 */
		CONSYS_CLR_BIT(conn_reg.spm_base +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1U << 2));

		/* de-assert "conn_top_on" secondary part power on, */
		/* set "connsys_on_domain_pwr_on_s"=0 */
		CONSYS_CLR_BIT(conn_reg.spm_base +
			CONSYS_GEN_CONN_PWR_CON_OFFSET_ADDR, (0x1U << 3));
	}

	return 0;
}

int polling_consys_chipid_mt6835_gen(unsigned int *pconsys_ver_id, unsigned int *pconsys_fw_ver)
{
	int check = 0;
	int retry = 0;
	unsigned int consys_ver_id = 0;

	if (conn_reg.mcu_top_misc_off_base == 0) {
		pr_notice("conn_reg.mcu_top_misc_off_base is not defined\n");
		return -1;
	}

	if (conn_reg.mcu_base == 0) {
		pr_notice("conn_reg.mcu_base is not defined\n");
		return -1;
	}

	/* check CONNSYS version ID */
	/* (polling "10 times" for specific project code and each polling interval is "20ms") */
	retry = 11;
	while (retry-- > 0) {
		consys_ver_id = CONSYS_REG_READ(
			conn_reg.mcu_top_misc_off_base +
			CONSYS_GEN_CONN_CONNSYS_VERSION_OFFSET_ADDR);
		if (consys_ver_id == CONSYS_GEN_CONN_HW_VER) {
			check = 0;
			pr_info("Consys HW version id(0x%08x), retry(%d)\n", consys_ver_id, retry);
			if (pconsys_ver_id != NULL)
				*pconsys_ver_id = consys_ver_id;
			break;
		}
		check = -1;
		msleep(20);
	}

	if (check != 0) {
		pr_notice("Read CONSYS version id fail. Expect 0x%08x but get 0x%08x\n",
			CONSYS_GEN_CONN_HW_VER, consys_ver_id);
		#if defined(KERNEL_clk_buf_show_status_info)
			KERNEL_clk_buf_show_status_info();  /* dump clock buffer */
		#endif
		return -1;
	}

	/* check CONNSYS configuration ID */
	check = CONSYS_REG_READ(conn_reg.mcu_top_misc_off_base + CONSYS_GEN_CONN_CONNSYS_CONFIG_OFFSET_ADDR);
	if (((check & 0xf) >> 0) != 0x1)
		pr_notice("[%s] read CONNSYS configuration ID fail (0x%x)\n", __func__, check);
	else
		pr_info("[%s] read CONNSYS configuration ID pass (0x%x)\n", __func__, check);

	/* check CONNSYS HW version ID */
	check = CONSYS_REG_READ(conn_reg.mcu_base + CONSYS_GEN_HW_VER_OFFSET_ADDR);
	if (((check & 0xffff) >> 0) != 0x8A00)
		pr_notice("[%s] read CONNSYS HW version ID fail (0x%x)\n", __func__, check);
	else
		pr_info("[%s] read CONNSYS HW version ID pass (0x%x)\n", __func__, check);

	/* check CONNSYS FW version ID */
	check = CONSYS_REG_READ(conn_reg.mcu_base + CONSYS_GEN_FW_VER_OFFSET_ADDR);
	if (pconsys_fw_ver != NULL)
		*pconsys_fw_ver = check;
	if (((check & 0xffff) >> 0) != 0x8A00)
		pr_notice("[%s] read CONNSYS FW version ID fail (0x%x)\n", __func__, check);
	else
		pr_info("[%s] read CONNSYS FW version ID pass (0x%x)\n", __func__, check);

	return 0;
}

void consys_set_access_emi_hw_mode_mt6835_gen(void)
{
	if (conn_reg.mcu_top_misc_on_base == 0) {
		pr_notice("conn_reg.mcu_top_misc_on_base is not defined\n");
		return;
	}

	/* conn2ap access EMI hw mode with slpprotect ctrl */
	CONSYS_SET_BIT(conn_reg.mcu_top_misc_on_base +
		CONSYS_GEN_CONN_ON_MCU_EMI_SLPPROT_EN_OFFSET_ADDR, (0x1U << 0));
}

void consys_emi_entry_address_mt6835_gen(void)
{
	if (conn_reg.mcu_base == 0) {
		pr_notice("conn_reg.mcu_base is not defined\n");
		return;
	}

	/* write 0x18002504[31:0] = 0xf0170000 */
	CONSYS_REG_WRITE(conn_reg.mcu_base +
		CONSYS_GEN_BT_EMI_ENTRY_ADDR_OFFSET_ADDR, 0xF0170000);

	/* write 0x18002508[31:0] = 0xf02a0000 */
	CONSYS_REG_WRITE(conn_reg.mcu_base +
		CONSYS_GEN_WF_EMI_ENTRY_ADDR_OFFSET_ADDR, 0xF02A0000);
}

void consys_set_xo_osc_ctrl_mt6835_gen(void)
{
	if (conn_reg.mcu_top_misc_on_base == 0) {
		pr_notice("conn_reg.mcu_top_misc_on_base is not defined\n");
		return;
	}

	if (consys_is_rc_mode_enable_mt6835() == 0) {
		/* disable conn_top rc osc_ctrl_top */
		CONSYS_CLR_BIT(conn_reg.mcu_top_misc_on_base +
			CONSYS_GEN_CONN_ON_RC_OSC_CTL_0_OFFSET_ADDR, (0x1U << 7));

		/* set CR "XO initial stable time" and "XO bg stable time" to optimize the wakeup time after sleep */
		if (wmt_plat_soc_co_clock_flag_get()) {
			CONSYS_REG_WRITE_MASK(conn_reg.mcu_top_misc_on_base +
				CONSYS_GEN_CONN_ON_OSC_CTL_2_OFFSET_ADDR, 0x600, 0xFF00);
			CONSYS_REG_WRITE_MASK(conn_reg.mcu_top_misc_on_base +
				CONSYS_GEN_CONN_ON_OSC_CTL_OFFSET_ADDR, 0x708, 0xFFFF);
		}

		/* clear "source clock enable ack to XO state" mask */
		if (wmt_plat_soc_co_clock_flag_get()) {
			CONSYS_CLR_BIT(conn_reg.mcu_top_misc_on_base +
				CONSYS_GEN_CONN_CFG_ON_CONN_ON_OSC_CTL_2_OFFSET_ADDR, (0x1U << 0));
		}
	} else {
		/* GPS RC OSC control stable time */
		if (wmt_plat_soc_co_clock_flag_get()) {
			CONSYS_REG_WRITE(conn_reg.mcu_top_misc_on_base +
				CONSYS_GEN_CONN_ON_RC_OSC_CTL_GPS_0_OFFSET_ADDR, 0x2080706);
		} else {
			CONSYS_REG_WRITE(conn_reg.mcu_top_misc_on_base +
				CONSYS_GEN_CONN_CFG_ON_CONN_ON_RC_OSC_CTL_GPS_0_OFFSET_ADDR, 0x24B4A49);
		}

		/* GPS RC OSC control unmask conn_srcclkena_ack */
		CONSYS_CLR_BIT(conn_reg.mcu_top_misc_on_base +
			CONSYS_GEN_CONN_ON_RC_OSC_CTL_GPS_1_OFFSET_ADDR, (0x1U << 16));

		/* BT RC OSC control stable time */
		if (wmt_plat_soc_co_clock_flag_get()) {
			CONSYS_REG_WRITE(conn_reg.mcu_top_misc_on_base +
				CONSYS_GEN_CONN_ON_RC_OSC_CTL_BT_0_OFFSET_ADDR, 0x2080706);
		} else {
			CONSYS_REG_WRITE(conn_reg.mcu_top_misc_on_base +
				CONSYS_GEN_CONN_CFG_ON_CONN_ON_RC_OSC_CTL_BT_0_OFFSET_ADDR, 0x24B4A49);
		}

		/* BT RC OSC control unmask conn_srcclkena_ack */
		CONSYS_CLR_BIT(conn_reg.mcu_top_misc_on_base +
			CONSYS_GEN_CONN_ON_RC_OSC_CTL_BT_1_OFFSET_ADDR, (0x1U << 16));

		/* WF RC OSC control stable time */
		if (wmt_plat_soc_co_clock_flag_get()) {
			CONSYS_REG_WRITE(conn_reg.mcu_top_misc_on_base +
				CONSYS_GEN_CONN_ON_RC_OSC_CTL_WF_0_OFFSET_ADDR, 0x2080706);
		} else {
			CONSYS_REG_WRITE(conn_reg.mcu_top_misc_on_base +
				CONSYS_GEN_CONN_CFG_ON_CONN_ON_RC_OSC_CTL_WF_0_OFFSET_ADDR, 0x24B4A49);
		}

		/* WF RC OSC control unmask conn_srcclkena_ack */
		CONSYS_CLR_BIT(conn_reg.mcu_top_misc_on_base +
			CONSYS_GEN_CONN_ON_RC_OSC_CTL_WF_1_OFFSET_ADDR, (0x1U << 16));

		/* TOP RC OSC control stable time */
		if (wmt_plat_soc_co_clock_flag_get()) {
			CONSYS_REG_WRITE(conn_reg.mcu_top_misc_on_base +
				CONSYS_GEN_CONN_ON_RC_OSC_CTL_TOP_0_OFFSET_ADDR, 0x2080706);
		} else {
			CONSYS_REG_WRITE(conn_reg.mcu_top_misc_on_base +
				CONSYS_GEN_CONN_CFG_ON_CONN_ON_RC_OSC_CTL_TOP_0_OFFSET_ADDR, 0x24B4A49);
		}

		/* TOP RC OSC control unmask conn_srcclkena_ack */
		CONSYS_CLR_BIT(conn_reg.mcu_top_misc_on_base +
			CONSYS_GEN_CONN_ON_RC_OSC_CTL_TOP_1_OFFSET_ADDR, (0x1U << 16));

		/* enable conn_top rc osc_ctrl_gps */
		CONSYS_REG_WRITE_MASK(conn_reg.mcu_top_misc_on_base +
			CONSYS_GEN_CONN_CFG_ON_CONN_ON_RC_OSC_CTL_0_OFFSET_ADDR, 0x1010, 0x1010);

		/* enable conn_top rc osc_ctrl_bt */
		CONSYS_REG_WRITE_MASK(conn_reg.mcu_top_misc_on_base +
			CONSYS_GEN_CONN_CFG_ON_CONN_ON_RC_OSC_CTL_0_OFFSET_ADDR, 0x2020, 0x2020);

		/* enable conn_top rc osc_ctrl_wf */
		CONSYS_REG_WRITE_MASK(conn_reg.mcu_top_misc_on_base +
			CONSYS_GEN_CONN_CFG_ON_CONN_ON_RC_OSC_CTL_0_OFFSET_ADDR, 0x4040, 0x4040);

		/* enable conn_top rc osc_ctrl_top */
		CONSYS_REG_WRITE_MASK(conn_reg.mcu_top_misc_on_base +
			CONSYS_GEN_CONN_CFG_ON_CONN_ON_RC_OSC_CTL_0_OFFSET_ADDR, 0x8080, 0x8080);

		/* disable legacy osc control */
		CONSYS_CLR_BIT(conn_reg.mcu_top_misc_on_base +
			CONSYS_GEN_CONN_CFG_ON_CONN_ON_RC_OSC_CTL_0_OFFSET_ADDR, (0x1U << 8));
	}
}

void consys_identify_adie_mt6835_gen(void)
{
	int adie_chipid = mtk_wcn_consys_get_adie_chipid();

	if (conn_reg.mcu_top_misc_on_base == 0) {
		pr_notice("conn_reg.mcu_top_misc_on_base is not defined\n");
		return;
	}

	/* write reserverd cr for identify adie is 6635, 6631, or 6637 */
	if (adie_chipid == SECONDARY_ADIE) {
		CONSYS_CLR_BIT(conn_reg.mcu_top_misc_on_base +
			CONSYS_GEN_CONN_ON_RSV_OFFSET_ADDR, (0x1U << 8));
	} else if (adie_chipid == PRIMARY_ADIE) {
		CONSYS_SET_BIT(conn_reg.mcu_top_misc_on_base +
			CONSYS_GEN_CONN_CFG_ON_CONN_ON_RSV_OFFSET_ADDR, (0x1U << 8));
	} else if (adie_chipid == TERTIARY_ADIE) {
		CONSYS_SET_BIT(conn_reg.mcu_top_misc_on_base +
			CONSYS_GEN_CONN_CFG_ON_CONN_ON_RSV_OFFSET_ADDR, (0x3U << 8));
	}
}

void consys_wifi_ctrl_setting_mt6835_gen(void)
{
	void __iomem *vir_addr_consys_gen_gpio_base = NULL;
	int adie_chipid = mtk_wcn_consys_get_adie_chipid();

	if (adie_chipid == PRIMARY_ADIE)
		return;

	vir_addr_consys_gen_gpio_base =
		ioremap(CONSYS_GEN_GPIO_BASE_ADDR, 0x460);

	if (!vir_addr_consys_gen_gpio_base) {
		pr_notice("vir_addr_consys_gen_gpio_base(%x) ioremap fail\n",
			CONSYS_GEN_GPIO_BASE_ADDR);
		return;
	}

	CONSYS_SET_BIT(vir_addr_consys_gen_gpio_base +
		CONSYS_GEN_GPIO_DIR5_OFFSET_ADDR, (0x1U << 20));
	if (adie_chipid == SECONDARY_ADIE)
		CONSYS_SET_BIT(vir_addr_consys_gen_gpio_base +
			CONSYS_GEN_GPIO_DOUT5_OFFSET_ADDR, (0x1U << 20));
	else
		CONSYS_CLR_BIT(vir_addr_consys_gen_gpio_base +
			CONSYS_GEN_GPIO_DOUT5_OFFSET_ADDR, (0x1U << 20));
	CONSYS_REG_WRITE_MASK(vir_addr_consys_gen_gpio_base +
		CONSYS_GEN_GPIO_MODE22_OFFSET_ADDR, 0x0, 0x70000);

	if (vir_addr_consys_gen_gpio_base)
		iounmap(vir_addr_consys_gen_gpio_base);
}

void consys_bus_timeout_config_mt6835_gen(void)
{
	void __iomem *vir_addr_consys_gen_conn_rgu_on_base = NULL;

	if (conn_reg.mcu_base == 0) {
		pr_notice("conn_reg.mcu_base is not defined\n");
		return;
	}

	vir_addr_consys_gen_conn_rgu_on_base =
		ioremap(CONSYS_GEN_CONN_RGU_ON_BASE_ADDR, 0x284);

	if (!vir_addr_consys_gen_conn_rgu_on_base) {
		pr_notice("vir_addr_consys_gen_conn_rgu_on_base(%x) ioremap fail\n",
			CONSYS_GEN_CONN_RGU_ON_BASE_ADDR);
		return;
	}

	/* connsys bus time out configure */
	CONSYS_REG_WRITE(conn_reg.mcu_base +
		CONSYS_GEN_BUSHANGCR_OFFSET_ADDR, 0x90000002);

	/* set mcu_mem_pdn_delay chain dummy cr for the timing between SLEEPB and ISOINTB when sleep */
	CONSYS_REG_WRITE_MASK(vir_addr_consys_gen_conn_rgu_on_base +
		CONSYS_GEN_MCUSYS_DLY_CHAIN_CTL_OFFSET_ADDR, 0x40000, 0xF0000);

	if (vir_addr_consys_gen_conn_rgu_on_base)
		iounmap(vir_addr_consys_gen_conn_rgu_on_base);
}

void consys_bus_config_gps_access_tia_mt6835_gen(void)
{
	if (conn_reg.mcu_base == 0) {
		pr_notice("conn_reg.mcu_base is not defined\n");
		return;
	}

	/* connsys bus configure for not request apsrc_req/ddr_en when connsys gps access TIA */
	/* (Infra_bus by 0X78xx_xxxx) */
	CONSYS_REG_WRITE_MASK(conn_reg.mcu_base +
		CONSYS_GEN_TO_INFRA_CR_CTL_OFFSET_ADDR, 0x4, 0x6);
}

int consys_polling_goto_idle_mt6835_gen(unsigned int *pconsys_ver_id)
{
	unsigned int consys_ver_id = 0;
	unsigned int cnt = 0;

	if (conn_reg.mcu_base == 0) {
		pr_notice("conn_reg.mcu_base is not defined\n");
		return -1;
	}

	/* check CONNSYS power-on completion */
	/* (polling "0x8000_0600[31:0]" == 0x1D1E and each polling interval is "1ms") */
	/* ([NOTE] this setting could be changed at different CONNSYS ROM code) */
	consys_ver_id = CONSYS_REG_READ(conn_reg.mcu_base + CONSYS_GEN_COM_REG0_OFFSET_ADDR);
	while (consys_ver_id != 0x1d1e) {
		if (cnt > 40) {
			pr_notice("can not go into idle loop!\n");
			break;
		}

		consys_ver_id = CONSYS_REG_READ(conn_reg.mcu_base + CONSYS_GEN_COM_REG0_OFFSET_ADDR);

		if (consys_ver_id == 0x1d1e) {
			pr_info("go into idle loop pass, count=[%d]!\n", cnt);
			break;
		}

		usleep_range(5000, 6000);
		cnt++;
	}

	if (pconsys_ver_id != NULL)
		*pconsys_ver_id = consys_ver_id;

	if (consys_ver_id != 0x1d1e)
		return -1;

	return 0;
}

void consys_wifi_ctrl_switch_conn_mode_mt6835_gen(void)
{
	void __iomem *vir_addr_consys_gen_gpio_base = NULL;


	if (mtk_wcn_consys_get_adie_chipid() == PRIMARY_ADIE)
		return;

	vir_addr_consys_gen_gpio_base =
		ioremap(CONSYS_GEN_GPIO_BASE_ADDR, 0x460);

	if (!vir_addr_consys_gen_gpio_base) {
		pr_notice("vir_addr_consys_gen_gpio_base(%x) ioremap fail\n",
			CONSYS_GEN_GPIO_BASE_ADDR);
		return;
	}

	/* CONN_WF_CTRL2 swtich to CONN mode */
	CONSYS_REG_WRITE_MASK(vir_addr_consys_gen_gpio_base +
		CONSYS_GEN_GPIO_MODE22_OFFSET_ADDR, 0x10000, 0x70000);

	if (vir_addr_consys_gen_gpio_base)
		iounmap(vir_addr_consys_gen_gpio_base);
}
