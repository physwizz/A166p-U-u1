/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2020 MediaTek Inc.
 * Author: Scott Wang <scott.wang@mediatek.com>
 */
#ifndef _DTS_IOMMU_PORT_MT8195_H_
#define _DTS_IOMMU_PORT_MT8195_H_

#include <dt-bindings/memory/mtk-smi-larb-port.h>

#define MTK_IOMMU_LARB_NR 32
/*
 * MM IOMMU:
 * domain 0: display: larb0, larb1, larb2, larb3.
 * domain 1: video: larb19, larb20, larb21, larb22, larb23, larb24.
 * domain 2: CAM and MDP: larb5, larb6, larb7, larb8, larb9, larb10,
 *           larb11, larb12, larb13, larb14, larb16, larb17, larb18,
 *           larb25, larb26, larb27, larb28, larb29, larb30.
 * VPU IOMMU:
 * domain 0: APU CODE: larb31, port0.
 * domain 1: APU DATA: larb31, port1.
 * domain 2: APU VLM: larb31, port2.
 */

/* larb0 */
#define M4U_PORT_L0_DISP_RDMA0			MTK_M4U_DOM_ID(0, 0, 0)
#define M4U_PORT_L0_DISP_WDMA0			MTK_M4U_DOM_ID(0, 0, 1)
#define M4U_PORT_L0_DISP_OVL0_RDMA0		MTK_M4U_DOM_ID(0, 0, 2)
#define M4U_PORT_L0_DISP_OVL0_RDMA1		MTK_M4U_DOM_ID(0, 0, 3)
#define M4U_PORT_L0_DISP_OVL0_HDR		MTK_M4U_DOM_ID(0, 0, 4)
#define M4U_PORT_L0_DISP_FAKE0			MTK_M4U_DOM_ID(0, 0, 5)

/* larb1 */
#define M4U_PORT_L1_DISP_RDMA0			MTK_M4U_DOM_ID(0, 1, 0)
#define M4U_PORT_L1_DISP_WDMA0			MTK_M4U_DOM_ID(0, 1, 1)
#define M4U_PORT_L1_DISP_OVL0_RDMA0		MTK_M4U_DOM_ID(0, 1, 2)
#define M4U_PORT_L1_DISP_OVL0_RDMA1		MTK_M4U_DOM_ID(0, 1, 3)
#define M4U_PORT_L1_DISP_OVL0_HDR		MTK_M4U_DOM_ID(0, 1, 4)
#define M4U_PORT_L1_DISP_FAKE0			MTK_M4U_DOM_ID(0, 1, 5)


/* larb2 */
#define M4U_PORT_L2_MDP_RDMA0			MTK_M4U_DOM_ID(0, 2, 0)
#define M4U_PORT_L2_MDP_RDMA2			MTK_M4U_DOM_ID(0, 2, 1)
#define M4U_PORT_L2_MDP_RDMA4			MTK_M4U_DOM_ID(0, 2, 2)
#define M4U_PORT_L2_MDP_RDMA6			MTK_M4U_DOM_ID(0, 2, 3)
#define M4U_PORT_L2_DISP_FAKE1			MTK_M4U_DOM_ID(0, 2, 4)

/* larb3 */
#define M4U_PORT_L3_MDP_RDMA1			MTK_M4U_DOM_ID(0, 3, 0)
#define M4U_PORT_L3_MDP_RDMA3			MTK_M4U_DOM_ID(0, 3, 1)
#define M4U_PORT_L3_MDP_RDMA5			MTK_M4U_DOM_ID(0, 3, 2)
#define M4U_PORT_L3_MDP_RDMA7			MTK_M4U_DOM_ID(0, 3, 3)
#define M4U_PORT_L3_HDR_DS			MTK_M4U_DOM_ID(0, 3, 4)
#define M4U_PORT_L3_HDR_ADL			MTK_M4U_DOM_ID(0, 3, 5)
#define M4U_PORT_L3_DISP_FAKE1			MTK_M4U_DOM_ID(0, 3, 6)

/* larb4 */
#define M4U_PORT_L4_MDP_RDMA			MTK_M4U_DOM_ID(2, 4, 0)
#define M4U_PORT_L4_MDP_FG			MTK_M4U_DOM_ID(2, 4, 1)
#define M4U_PORT_L4_MDP_OVL			MTK_M4U_DOM_ID(2, 4, 2)
#define M4U_PORT_L4_MDP_WROT			MTK_M4U_DOM_ID(2, 4, 3)
#define M4U_PORT_L4_FAKE			MTK_M4U_DOM_ID(2, 4, 4)


/* larb5 */
#define M4U_PORT_L5_SVPP1_MDP_RDMA		MTK_M4U_DOM_ID(2, 5, 0)
#define M4U_PORT_L5_SVPP1_MDP_FG		MTK_M4U_DOM_ID(2, 5, 1)
#define M4U_PORT_L5_SVPP1_MDP_OVL		MTK_M4U_DOM_ID(2, 5, 2)
#define M4U_PORT_L5_SVPP1_MDP_WROT		MTK_M4U_DOM_ID(2, 5, 3)
#define M4U_PORT_L5_SVPP2_MDP_RDMA		MTK_M4U_DOM_ID(2, 5, 4)
#define M4U_PORT_L5_SVPP2_MDP_FG		MTK_M4U_DOM_ID(2, 5, 5)
#define M4U_PORT_L5_SVPP2_MDP_WROT		MTK_M4U_DOM_ID(2, 5, 6)
#define M4U_PORT_L5_FAKE			MTK_M4U_DOM_ID(2, 5, 7)

/* larb6 */
#define M4U_PORT_L6_SVPP3_MDP_RDMA		MTK_M4U_DOM_ID(2, 6, 0)
#define M4U_PORT_L6_SVPP3_MDP_FG		MTK_M4U_DOM_ID(2, 6, 1)
#define M4U_PORT_L6_SVPP3_MDP_WROT		MTK_M4U_DOM_ID(2, 6, 2)
#define M4U_PORT_L6_FAKE			MTK_M4U_DOM_ID(2, 6, 3)

/* larb7 */
#define M4U_PORT_L7_IMG_WPE_RDMA0		MTK_M4U_DOM_ID(2, 7, 0)
#define M4U_PORT_L7_IMG_WPE_RDMA1		MTK_M4U_DOM_ID(2, 7, 1)
#define M4U_PORT_L7_IMG_WPE_WDMA0		MTK_M4U_DOM_ID(2, 7, 2)

/* larb8 */
#define M4U_PORT_L8_IMG_WPE_RDMA0		MTK_M4U_DOM_ID(2, 8, 0)
#define M4U_PORT_L8_IMG_WPE_RDMA1		MTK_M4U_DOM_ID(2, 8, 1)
#define M4U_PORT_L8_IMG_WPE_WDMA0		MTK_M4U_DOM_ID(2, 8, 2)

/* larb9 */
#define M4U_PORT_L9_IMG_IMGI_T1_A		MTK_M4U_DOM_ID(2, 9, 0)
#define M4U_PORT_L9_IMG_IMGBI_T1_A		MTK_M4U_DOM_ID(2, 9, 1)
#define M4U_PORT_L9_IMG_IMGCI_T1_A		MTK_M4U_DOM_ID(2, 9, 2)
#define M4U_PORT_L9_IMG_SMTI_T1_A		MTK_M4U_DOM_ID(2, 9, 3)
#define M4U_PORT_L9_IMG_TNCSTI_T1_A		MTK_M4U_DOM_ID(2, 9, 4)
#define M4U_PORT_L9_IMG_TNCSTI_T4_A		MTK_M4U_DOM_ID(2, 9, 5)
#define M4U_PORT_L9_IMG_YUVO_T1_A		MTK_M4U_DOM_ID(2, 9, 6)
#define M4U_PORT_L9_IMG_TIMGO_T1_A		MTK_M4U_DOM_ID(2, 9, 7)
#define M4U_PORT_L9_IMG_YUVO_T2_A		MTK_M4U_DOM_ID(2, 9, 8)
#define M4U_PORT_L9_IMG_IMGI_T1_B		MTK_M4U_DOM_ID(2, 9, 9)
#define M4U_PORT_L9_IMG_IMGBI_T1_B		MTK_M4U_DOM_ID(2, 9, 10)
#define M4U_PORT_L9_IMG_IMGCI_T1_B		MTK_M4U_DOM_ID(2, 9, 11)
#define M4U_PORT_L9_IMG_YUVO_T5_A		MTK_M4U_DOM_ID(2, 9, 12)
#define M4U_PORT_L9_IMG_SMTI_T1_B		MTK_M4U_DOM_ID(2, 9, 13)
#define M4U_PORT_L9_IMG_TNCSO_T1_A		MTK_M4U_DOM_ID(2, 9, 14)
#define M4U_PORT_L9_IMG_SMTO_T1_A		MTK_M4U_DOM_ID(2, 9, 15)
#define M4U_PORT_L9_IMG_TNCSTO_T1_A		MTK_M4U_DOM_ID(2, 9, 16)
#define M4U_PORT_L9_IMG_YUVO_T2_B		MTK_M4U_DOM_ID(2, 9, 17)
#define M4U_PORT_L9_IMG_YUVO_T5_B		MTK_M4U_DOM_ID(2, 9, 18)
#define M4U_PORT_L9_IMG_SMTO_T1_B		MTK_M4U_DOM_ID(2, 9, 19)

/* larb10 */
#define M4U_PORT_L10_IMG_IMGI_D1_A		MTK_M4U_DOM_ID(2, 10, 0)
#define M4U_PORT_L10_IMG_IMGCI_D1_A		MTK_M4U_DOM_ID(2, 10, 1)
#define M4U_PORT_L10_IMG_DEPI_D1_A		MTK_M4U_DOM_ID(2, 10, 2)
#define M4U_PORT_L10_IMG_DMGI_D1_A		MTK_M4U_DOM_ID(2, 10, 3)
#define M4U_PORT_L10_IMG_VIPI_D1_A		MTK_M4U_DOM_ID(2, 10, 4)
#define M4U_PORT_L10_IMG_TNRWI_D1_A		MTK_M4U_DOM_ID(2, 10, 5)
#define M4U_PORT_L10_IMG_RECI_D1_A		MTK_M4U_DOM_ID(2, 10, 6)
#define M4U_PORT_L10_IMG_SMTI_D1_A		MTK_M4U_DOM_ID(2, 10, 7)
#define M4U_PORT_L10_IMG_SMTI_D6_A		MTK_M4U_DOM_ID(2, 10, 8)
#define M4U_PORT_L10_IMG_PIMGI_P1_A		MTK_M4U_DOM_ID(2, 10, 9)
#define M4U_PORT_L10_IMG_PIMGBI_P1_A		MTK_M4U_DOM_ID(2, 10, 10)
#define M4U_PORT_L10_IMG_PIMGCI_P1_A		MTK_M4U_DOM_ID(2, 10, 11)
#define M4U_PORT_L10_IMG_PIMGI_P1_B		MTK_M4U_DOM_ID(2, 10, 12)
#define M4U_PORT_L10_IMG_PIMGBI_P1_B		MTK_M4U_DOM_ID(2, 10, 13)
#define M4U_PORT_L10_IMG_PIMGCI_P1_B		MTK_M4U_DOM_ID(2, 10, 14)
#define M4U_PORT_L10_IMG_IMG3O_D1_A		MTK_M4U_DOM_ID(2, 10, 15)
#define M4U_PORT_L10_IMG_IMG4O_D1_A		MTK_M4U_DOM_ID(2, 10, 16)
#define M4U_PORT_L10_IMG_IMG3CO_D1_A		MTK_M4U_DOM_ID(2, 10, 17)
#define M4U_PORT_L10_IMG_FEO_D1_A		MTK_M4U_DOM_ID(2, 10, 18)
#define M4U_PORT_L10_IMG_IMG2O_D1_A		MTK_M4U_DOM_ID(2, 10, 19)
#define M4U_PORT_L10_IMG_TNRWO_D1_A		MTK_M4U_DOM_ID(2, 10, 20)
#define M4U_PORT_L10_IMG_SMTO_D1_A		MTK_M4U_DOM_ID(2, 10, 21)
#define M4U_PORT_L10_IMG_WROT_P1_A		MTK_M4U_DOM_ID(2, 10, 22)
#define M4U_PORT_L10_IMG_WROT_P1_B		MTK_M4U_DOM_ID(2, 10, 23)

/* larb11 */
#define M4U_PORT_L11_IMG_WPE_EIS_RDMA0_A	MTK_M4U_DOM_ID(2, 11, 0)
#define M4U_PORT_L11_IMG_WPE_EIS_RDMA1_A	MTK_M4U_DOM_ID(2, 11, 1)
#define M4U_PORT_L11_IMG_WPE_EIS_WDMA0_A	MTK_M4U_DOM_ID(2, 11, 2)
#define M4U_PORT_L11_IMG_WPE_TNR_RDMA0_A	MTK_M4U_DOM_ID(2, 11, 3)
#define M4U_PORT_L11_IMG_WPE_TNR_RDMA1_A	MTK_M4U_DOM_ID(2, 11, 4)
#define M4U_PORT_L11_IMG_WPE_TNR_WDMA0_A	MTK_M4U_DOM_ID(2, 11, 5)
#define M4U_PORT_L11_IMG_WPE_EIS_CQ0_A		MTK_M4U_DOM_ID(2, 11, 6)
#define M4U_PORT_L11_IMG_WPE_EIS_CQ1_A		MTK_M4U_DOM_ID(2, 11, 7)
#define M4U_PORT_L11_IMG_WPE_TNR_CQ0_A		MTK_M4U_DOM_ID(2, 11, 8)
#define M4U_PORT_L11_IMG_WPE_TNR_CQ1_A		MTK_M4U_DOM_ID(2, 11, 9)

/* larb12 */
#define M4U_PORT_L12_IMG_FDVT_RDA		MTK_M4U_DOM_ID(2, 12, 0)
#define M4U_PORT_L12_IMG_FDVT_RDB		MTK_M4U_DOM_ID(2, 12, 1)
#define M4U_PORT_L12_IMG_FDVT_WRA		MTK_M4U_DOM_ID(2, 12, 2)
#define M4U_PORT_L12_IMG_FDVT_WRB		MTK_M4U_DOM_ID(2, 12, 3)
#define M4U_PORT_L12_IMG_ME_RDMA		MTK_M4U_DOM_ID(2, 12, 4)
#define M4U_PORT_L12_IMG_ME_WDMA		MTK_M4U_DOM_ID(2, 12, 5)
#define M4U_PORT_L12_IMG_DVS_RDMA		MTK_M4U_DOM_ID(2, 12, 6)
#define M4U_PORT_L12_IMG_DVS_WDMA		MTK_M4U_DOM_ID(2, 12, 7)
#define M4U_PORT_L12_IMG_DVP_RDMA		MTK_M4U_DOM_ID(2, 12, 8)
#define M4U_PORT_L12_IMG_DVP_WDMA		MTK_M4U_DOM_ID(2, 12, 9)

/* larb13 */
#define M4U_PORT_L13_CAM_CAMSV_CQI_E1		MTK_M4U_DOM_ID(2, 13, 0)
#define M4U_PORT_L13_CAM_CAMSV_CQI_E2		MTK_M4U_DOM_ID(2, 13, 1)
#define M4U_PORT_L13_CAM_GCAMSV_A_IMGO_0	MTK_M4U_DOM_ID(2, 13, 2)
#define M4U_PORT_L13_CAM_SCAMSV_A_IMGO_0	MTK_M4U_DOM_ID(2, 13, 3)
#define M4U_PORT_L13_CAM_GCAMSV_B_IMGO_0	MTK_M4U_DOM_ID(2, 13, 4)
#define M4U_PORT_L13_CAM_GCAMSV_B_IMGO_1	MTK_M4U_DOM_ID(2, 13, 5)
#define M4U_PORT_L13_CAM_GCAMSV_A_UFEO_0	MTK_M4U_DOM_ID(2, 13, 6)
#define M4U_PORT_L13_CAM_GCAMSV_B_UFEO_0	MTK_M4U_DOM_ID(2, 13, 7)
#define M4U_PORT_L13_CAM_PDAI_0			MTK_M4U_DOM_ID(2, 13, 8)
#define M4U_PORT_L13_CAM_FAKE			MTK_M4U_DOM_ID(2, 13, 9)

/* larb14 */
#define M4U_PORT_L14_CAM_GCAMSV_A_IMGO_1	MTK_M4U_DOM_ID(2, 14, 0)
#define M4U_PORT_L14_CAM_SCAMSV_A_IMGO_1	MTK_M4U_DOM_ID(2, 14, 1)
#define M4U_PORT_L14_CAM_GCAMSV_C_IMGO_0	MTK_M4U_DOM_ID(2, 14, 2)
#define M4U_PORT_L14_CAM_GCAMSV_C_IMGO_1	MTK_M4U_DOM_ID(2, 14, 3)
#define M4U_PORT_L14_CAM_SCAMSV_B_IMGO_0	MTK_M4U_DOM_ID(2, 14, 4)
#define M4U_PORT_L14_CAM_SCAMSV_B_IMGO_1	MTK_M4U_DOM_ID(2, 14, 5)
#define M4U_PORT_L14_CAM_IPUI			MTK_M4U_DOM_ID(2, 14, 6)
#define M4U_PORT_L14_CAM_IPU2I			MTK_M4U_DOM_ID(2, 14, 7)
#define M4U_PORT_L14_CAM_IPUO			MTK_M4U_DOM_ID(2, 14, 8)
#define M4U_PORT_L14_CAM_IPU2O			MTK_M4U_DOM_ID(2, 14, 9)
#define M4U_PORT_L14_CAM_IPU3O			MTK_M4U_DOM_ID(2, 14, 10)
#define M4U_PORT_L14_CAM_GCAMSV_A_UFEO_1	MTK_M4U_DOM_ID(2, 14, 11)
#define M4U_PORT_L14_CAM_GCAMSV_B_UFEO_1	MTK_M4U_DOM_ID(2, 14, 12)
#define M4U_PORT_L14_CAM_PDAI_1			MTK_M4U_DOM_ID(2, 14, 13)
#define M4U_PORT_L14_CAM_PDAO			MTK_M4U_DOM_ID(2, 14, 14)

/* larb15: null */

/* larb16 */
#define M4U_PORT_L16_CAM_IMGO_R1		MTK_M4U_DOM_ID(2, 16, 0)
#define M4U_PORT_L16_CAM_CQI_R1			MTK_M4U_DOM_ID(2, 16, 1)
#define M4U_PORT_L16_CAM_CQI_R2			MTK_M4U_DOM_ID(2, 16, 2)
#define M4U_PORT_L16_CAM_BPCI_R1		MTK_M4U_DOM_ID(2, 16, 3)
#define M4U_PORT_L16_CAM_LSCI_R1		MTK_M4U_DOM_ID(2, 16, 4)
#define M4U_PORT_L16_CAM_RAWI_R2		MTK_M4U_DOM_ID(2, 16, 5)
#define M4U_PORT_L16_CAM_RAWI_R3		MTK_M4U_DOM_ID(2, 16, 6)
#define M4U_PORT_L16_CAM_UFDI_R2		MTK_M4U_DOM_ID(2, 16, 7)
#define M4U_PORT_L16_CAM_UFDI_R3		MTK_M4U_DOM_ID(2, 16, 8)
#define M4U_PORT_L16_CAM_RAWI_R4		MTK_M4U_DOM_ID(2, 16, 9)
#define M4U_PORT_L16_CAM_RAWI_R5		MTK_M4U_DOM_ID(2, 16, 10)
#define M4U_PORT_L16_CAM_AAI_R1			MTK_M4U_DOM_ID(2, 16, 11)
#define M4U_PORT_L16_CAM_FHO_R1			MTK_M4U_DOM_ID(2, 16, 12)
#define M4U_PORT_L16_CAM_AAO_R1			MTK_M4U_DOM_ID(2, 16, 13)
#define M4U_PORT_L16_CAM_TSFSO_R1		MTK_M4U_DOM_ID(2, 16, 14)
#define M4U_PORT_L16_CAM_FLKO_R1		MTK_M4U_DOM_ID(2, 16, 15)

/* larb17 */
#define M4U_PORT_L17_CAM_YUVO_R1		MTK_M4U_DOM_ID(2, 17, 0)
#define M4U_PORT_L17_CAM_YUVO_R3		MTK_M4U_DOM_ID(2, 17, 1)
#define M4U_PORT_L17_CAM_YUVCO_R1		MTK_M4U_DOM_ID(2, 17, 2)
#define M4U_PORT_L17_CAM_YUVO_R2		MTK_M4U_DOM_ID(2, 17, 3)
#define M4U_PORT_L17_CAM_RZH1N2TO_R1		MTK_M4U_DOM_ID(2, 17, 4)
#define M4U_PORT_L17_CAM_DRZS4NO_R1		MTK_M4U_DOM_ID(2, 17, 5)
#define M4U_PORT_L17_CAM_TNCSO_R1		MTK_M4U_DOM_ID(2, 17, 6)

/* larb18 */
#define M4U_PORT_L18_CAM_CCUI			MTK_M4U_DOM_ID(3, 18, 0)
#define M4U_PORT_L18_CAM_CCUO			MTK_M4U_DOM_ID(3, 18, 1)
#define M4U_PORT_L18_CAM_CCUI2			MTK_M4U_DOM_ID(4, 18, 2)
#define M4U_PORT_L18_CAM_CCUO2			MTK_M4U_DOM_ID(4, 18, 3)

/* larb19 */
#define M4U_PORT_L19_VENC_RCPU			MTK_M4U_DOM_ID(1, 19, 0)
#define M4U_PORT_L19_VENC_REC			MTK_M4U_DOM_ID(1, 19, 1)
#define M4U_PORT_L19_VENC_BSDMA			MTK_M4U_DOM_ID(1, 19, 2)
#define M4U_PORT_L19_VENC_SV_COMV		MTK_M4U_DOM_ID(1, 19, 3)
#define M4U_PORT_L19_VENC_RD_COMV		MTK_M4U_DOM_ID(1, 19, 4)
#define M4U_PORT_L19_VENC_NBM_RDMA		MTK_M4U_DOM_ID(1, 19, 5)
#define M4U_PORT_L19_VENC_NBM_RDMA_LITE		MTK_M4U_DOM_ID(1, 19, 6)
#define M4U_PORT_L19_JPGENC_Y_RDMA		MTK_M4U_DOM_ID(1, 19, 7)
#define M4U_PORT_L19_JPGENC_C_RDMA		MTK_M4U_DOM_ID(1, 19, 8)
#define M4U_PORT_L19_JPGENC_Q_TABLE		MTK_M4U_DOM_ID(1, 19, 9)
#define M4U_PORT_L19_VENC_SUB_W_LUMA		MTK_M4U_DOM_ID(1, 19, 10)
#define M4U_PORT_L19_VENC_FCS_NBM_RDMA		MTK_M4U_DOM_ID(1, 19, 11)
#define M4U_PORT_L19_JPGENC_BSDMA		MTK_M4U_DOM_ID(1, 19, 12)
#define M4U_PORT_L19_JPGDEC_WDMA0		MTK_M4U_DOM_ID(1, 19, 13)
#define M4U_PORT_L19_JPGDEC_BSDMA0		MTK_M4U_DOM_ID(1, 19, 14)
#define M4U_PORT_L19_VENC_NBM_WDMA		MTK_M4U_DOM_ID(1, 19, 15)
#define M4U_PORT_L19_VENC_NBM_WDMA_LITE		MTK_M4U_DOM_ID(1, 19, 16)
#define M4U_PORT_L19_VENC_FCS_NBM_WDMA		MTK_M4U_DOM_ID(1, 19, 17)
#define M4U_PORT_L19_JPGDEC_WDMA1		MTK_M4U_DOM_ID(1, 19, 18)
#define M4U_PORT_L19_JPGDEC_BSDMA1		MTK_M4U_DOM_ID(1, 19, 19)
#define M4U_PORT_L19_JPGDEC_BUFF_OFFSET1	MTK_M4U_DOM_ID(1, 19, 20)
#define M4U_PORT_L19_JPGDEC_BUFF_OFFSET0	MTK_M4U_DOM_ID(1, 19, 21)
#define M4U_PORT_L19_VENC_CUR_LUMA		MTK_M4U_DOM_ID(1, 19, 22)
#define M4U_PORT_L19_VENC_CUR_CHROMA		MTK_M4U_DOM_ID(1, 19, 23)
#define M4U_PORT_L19_VENC_REF_LUMA		MTK_M4U_DOM_ID(1, 19, 24)
#define M4U_PORT_L19_VENC_REF_CHROMA		MTK_M4U_DOM_ID(1, 19, 25)
#define M4U_PORT_L19_VENC_SUB_R_CHROMA		MTK_M4U_DOM_ID(1, 19, 26)

/* larb20 */
#define M4U_PORT_L20_VENC_RCPU			MTK_M4U_DOM_ID(1, 20, 0)
#define M4U_PORT_L20_VENC_REC			MTK_M4U_DOM_ID(1, 20, 1)
#define M4U_PORT_L20_VENC_BSDMA			MTK_M4U_DOM_ID(1, 20, 2)
#define M4U_PORT_L20_VENC_SV_COMV		MTK_M4U_DOM_ID(1, 20, 3)
#define M4U_PORT_L20_VENC_RD_COMV		MTK_M4U_DOM_ID(1, 20, 4)
#define M4U_PORT_L20_VENC_NBM_RDMA		MTK_M4U_DOM_ID(1, 20, 5)
#define M4U_PORT_L20_VENC_NBM_RDMA_LITE		MTK_M4U_DOM_ID(1, 20, 6)
#define M4U_PORT_L20_JPGENC_Y_RDMA		MTK_M4U_DOM_ID(1, 20, 7)
#define M4U_PORT_L20_JPGENC_C_RDMA		MTK_M4U_DOM_ID(1, 20, 8)
#define M4U_PORT_L20_JPGENC_Q_TABLE		MTK_M4U_DOM_ID(1, 20, 9)
#define M4U_PORT_L20_VENC_SUB_W_LUMA		MTK_M4U_DOM_ID(1, 20, 10)
#define M4U_PORT_L20_VENC_FCS_NBM_RDMA		MTK_M4U_DOM_ID(1, 20, 11)
#define M4U_PORT_L20_JPGENC_BSDMA		MTK_M4U_DOM_ID(1, 20, 12)
#define M4U_PORT_L20_JPGDEC_WDMA0		MTK_M4U_DOM_ID(1, 20, 13)
#define M4U_PORT_L20_JPGDEC_BSDMA0		MTK_M4U_DOM_ID(1, 20, 14)
#define M4U_PORT_L20_VENC_NBM_WDMA		MTK_M4U_DOM_ID(1, 20, 15)
#define M4U_PORT_L20_VENC_NBM_WDMA_LITE		MTK_M4U_DOM_ID(1, 20, 16)
#define M4U_PORT_L20_VENC_FCS_NBM_WDMA		MTK_M4U_DOM_ID(1, 20, 17)
#define M4U_PORT_L20_JPGDEC_WDMA1		MTK_M4U_DOM_ID(1, 20, 18)
#define M4U_PORT_L20_JPGDEC_BSDMA1		MTK_M4U_DOM_ID(1, 20, 19)
#define M4U_PORT_L20_JPGDEC_BUFF_OFFSET1	MTK_M4U_DOM_ID(1, 20, 20)
#define M4U_PORT_L20_JPGDEC_BUFF_OFFSET0	MTK_M4U_DOM_ID(1, 20, 21)
#define M4U_PORT_L20_VENC_CUR_LUMA		MTK_M4U_DOM_ID(1, 20, 22)
#define M4U_PORT_L20_VENC_CUR_CHROMA		MTK_M4U_DOM_ID(1, 20, 23)
#define M4U_PORT_L20_VENC_REF_LUMA		MTK_M4U_DOM_ID(1, 20, 24)
#define M4U_PORT_L20_VENC_REF_CHROMA		MTK_M4U_DOM_ID(1, 20, 25)
#define M4U_PORT_L20_VENC_SUB_R_CHROMA		MTK_M4U_DOM_ID(1, 20, 26)

/* larb21 */
#define M4U_PORT_L21_VDEC_MC_EXT		MTK_M4U_DOM_ID(1, 21, 0)
#define M4U_PORT_L21_VDEC_UFO_EXT		MTK_M4U_DOM_ID(1, 21, 1)
#define M4U_PORT_L21_VDEC_PP_EXT		MTK_M4U_DOM_ID(1, 21, 2)
#define M4U_PORT_L21_VDEC_PRED_RD_EXT		MTK_M4U_DOM_ID(1, 21, 3)
#define M4U_PORT_L21_VDEC_PRED_WR_EXT		MTK_M4U_DOM_ID(1, 21, 4)
#define M4U_PORT_L21_VDEC_PPWRAP_EXT		MTK_M4U_DOM_ID(1, 21, 5)
#define M4U_PORT_L21_VDEC_TILE_EXT		MTK_M4U_DOM_ID(1, 21, 6)
#define M4U_PORT_L21_VDEC_VLD_EXT		MTK_M4U_DOM_ID(1, 21, 7)
#define M4U_PORT_L21_VDEC_VLD2_EXT		MTK_M4U_DOM_ID(1, 21, 8)
#define M4U_PORT_L21_VDEC_AVC_MV_EXT		MTK_M4U_DOM_ID(1, 21, 9)

/* larb22 */
#define M4U_PORT_L22_VDEC_MC_EXT		MTK_M4U_DOM_ID(1, 22, 0)
#define M4U_PORT_L22_VDEC_UFO_EXT		MTK_M4U_DOM_ID(1, 22, 1)
#define M4U_PORT_L22_VDEC_PP_EXT		MTK_M4U_DOM_ID(1, 22, 2)
#define M4U_PORT_L22_VDEC_PRED_RD_EXT		MTK_M4U_DOM_ID(1, 22, 3)
#define M4U_PORT_L22_VDEC_PRED_WR_EXT		MTK_M4U_DOM_ID(1, 22, 4)
#define M4U_PORT_L22_VDEC_PPWRAP_EXT		MTK_M4U_DOM_ID(1, 22, 5)
#define M4U_PORT_L22_VDEC_TILE_EXT		MTK_M4U_DOM_ID(1, 22, 6)
#define M4U_PORT_L22_VDEC_VLD_EXT		MTK_M4U_DOM_ID(1, 22, 7)
#define M4U_PORT_L22_VDEC_VLD2_EXT		MTK_M4U_DOM_ID(1, 22, 8)
#define M4U_PORT_L22_VDEC_AVC_MV_EXT		MTK_M4U_DOM_ID(1, 22, 9)

/* larb23 */
#define M4U_PORT_L23_VDEC_UFO_ENC_EXT		MTK_M4U_DOM_ID(1, 23, 0)
#define M4U_PORT_L23_VDEC_RDMA_EXT		MTK_M4U_DOM_ID(1, 23, 1)

/* larb24 */
#define M4U_PORT_L24_VDEC_LAT0_VLD_EXT		MTK_M4U_DOM_ID(1, 24, 0)
#define M4U_PORT_L24_VDEC_LAT0_VLD2_EXT		MTK_M4U_DOM_ID(1, 24, 1)
#define M4U_PORT_L24_VDEC_LAT0_AVC_MC_EXT	MTK_M4U_DOM_ID(1, 24, 2)
#define M4U_PORT_L24_VDEC_LAT0_PRED_RD_EXT	MTK_M4U_DOM_ID(1, 24, 3)
#define M4U_PORT_L24_VDEC_LAT0_TILE_EXT		MTK_M4U_DOM_ID(1, 24, 4)
#define M4U_PORT_L24_VDEC_LAT0_WDMA_EXT		MTK_M4U_DOM_ID(1, 24, 5)
#define M4U_PORT_L24_VDEC_LAT1_VLD_EXT		MTK_M4U_DOM_ID(1, 24, 6)
#define M4U_PORT_L24_VDEC_LAT1_VLD2_EXT		MTK_M4U_DOM_ID(1, 24, 7)
#define M4U_PORT_L24_VDEC_LAT1_AVC_MC_EXT	MTK_M4U_DOM_ID(1, 24, 8)
#define M4U_PORT_L24_VDEC_LAT1_PRED_RD_EXT	MTK_M4U_DOM_ID(1, 24, 9)
#define M4U_PORT_L24_VDEC_LAT1_TILE_EXT		MTK_M4U_DOM_ID(1, 24, 10)
#define M4U_PORT_L24_VDEC_LAT1_WDMA_EXT		MTK_M4U_DOM_ID(1, 24, 11)

/* larb25 */
#define M4U_PORT_L25_CAM_MRAW0_LSCI_M1		MTK_M4U_DOM_ID(2, 25, 0)
#define M4U_PORT_L25_CAM_MRAW0_CQI_M1		MTK_M4U_DOM_ID(2, 25, 1)
#define M4U_PORT_L25_CAM_MRAW0_CQI_M2		MTK_M4U_DOM_ID(2, 25, 2)
#define M4U_PORT_L25_CAM_MRAW0_IMGO_M1		MTK_M4U_DOM_ID(2, 25, 3)
#define M4U_PORT_L25_CAM_MRAW0_IMGBO_M1		MTK_M4U_DOM_ID(2, 25, 4)
#define M4U_PORT_L25_CAM_MRAW2_LSCI_M1		MTK_M4U_DOM_ID(2, 25, 5)
#define M4U_PORT_L25_CAM_MRAW2_CQI_M1		MTK_M4U_DOM_ID(2, 25, 6)
#define M4U_PORT_L25_CAM_MRAW2_CQI_M2		MTK_M4U_DOM_ID(2, 25, 7)
#define M4U_PORT_L25_CAM_MRAW2_IMGO_M1		MTK_M4U_DOM_ID(2, 25, 8)
#define M4U_PORT_L25_CAM_MRAW2_IMGBO_M1		MTK_M4U_DOM_ID(2, 25, 9)
#define M4U_PORT_L25_CAM_MRAW0_AFO_M1		MTK_M4U_DOM_ID(2, 25, 10)
#define M4U_PORT_L25_CAM_MRAW2_AFO_M1		MTK_M4U_DOM_ID(2, 25, 11)

/* larb26 */
#define M4U_PORT_L26_CAM_MRAW1_LSCI_M1		MTK_M4U_DOM_ID(2, 26, 0)
#define M4U_PORT_L26_CAM_MRAW1_CQI_M1		MTK_M4U_DOM_ID(2, 26, 1)
#define M4U_PORT_L26_CAM_MRAW1_CQI_M2		MTK_M4U_DOM_ID(2, 26, 2)
#define M4U_PORT_L26_CAM_MRAW1_IMGO_M1		MTK_M4U_DOM_ID(2, 26, 3)
#define M4U_PORT_L26_CAM_MRAW1_IMGBO_M1		MTK_M4U_DOM_ID(2, 26, 4)
#define M4U_PORT_L26_CAM_MRAW3_LSCI_M1		MTK_M4U_DOM_ID(2, 26, 5)
#define M4U_PORT_L26_CAM_MRAW3_CQI_M1		MTK_M4U_DOM_ID(2, 26, 6)
#define M4U_PORT_L26_CAM_MRAW3_CQI_M2		MTK_M4U_DOM_ID(2, 26, 7)
#define M4U_PORT_L26_CAM_MRAW3_IMGO_M1		MTK_M4U_DOM_ID(2, 26, 8)
#define M4U_PORT_L26_CAM_MRAW3_IMGBO_M1		MTK_M4U_DOM_ID(2, 26, 9)
#define M4U_PORT_L26_CAM_MRAW1_AFO_M1		MTK_M4U_DOM_ID(2, 26, 10)
#define M4U_PORT_L26_CAM_MRAW3_AFO_M1		MTK_M4U_DOM_ID(2, 26, 11)

/* larb27 */
#define M4U_PORT_L27_CAM_IMGO_R1		MTK_M4U_DOM_ID(2, 27, 0)
#define M4U_PORT_L27_CAM_CQI_R1			MTK_M4U_DOM_ID(2, 27, 1)
#define M4U_PORT_L27_CAM_CQI_R2			MTK_M4U_DOM_ID(2, 27, 2)
#define M4U_PORT_L27_CAM_BPCI_R1		MTK_M4U_DOM_ID(2, 27, 3)
#define M4U_PORT_L27_CAM_LSCI_R1		MTK_M4U_DOM_ID(2, 27, 4)
#define M4U_PORT_L27_CAM_RAWI_R2		MTK_M4U_DOM_ID(2, 27, 5)
#define M4U_PORT_L27_CAM_RAWI_R3		MTK_M4U_DOM_ID(2, 27, 6)
#define M4U_PORT_L27_CAM_UFDI_R2		MTK_M4U_DOM_ID(2, 27, 7)
#define M4U_PORT_L27_CAM_UFDI_R3		MTK_M4U_DOM_ID(2, 27, 8)
#define M4U_PORT_L27_CAM_RAWI_R4		MTK_M4U_DOM_ID(2, 27, 9)
#define M4U_PORT_L27_CAM_RAWI_R5		MTK_M4U_DOM_ID(2, 27, 10)
#define M4U_PORT_L27_CAM_AAI_R1			MTK_M4U_DOM_ID(2, 27, 11)
#define M4U_PORT_L27_CAM_FHO_R1			MTK_M4U_DOM_ID(2, 27, 12)
#define M4U_PORT_L27_CAM_AAO_R1			MTK_M4U_DOM_ID(2, 27, 13)
#define M4U_PORT_L27_CAM_TSFSO_R1		MTK_M4U_DOM_ID(2, 27, 14)
#define M4U_PORT_L27_CAM_FLKO_R1		MTK_M4U_DOM_ID(2, 27, 15)

/* larb28 */
#define M4U_PORT_L28_CAM_YUVO_R1		MTK_M4U_DOM_ID(2, 28, 0)
#define M4U_PORT_L28_CAM_YUVO_R3		MTK_M4U_DOM_ID(2, 28, 1)
#define M4U_PORT_L28_CAM_YUVCO_R1		MTK_M4U_DOM_ID(2, 28, 2)
#define M4U_PORT_L28_CAM_YUVO_R2		MTK_M4U_DOM_ID(2, 28, 3)
#define M4U_PORT_L28_CAM_RZH1N2TO_R1		MTK_M4U_DOM_ID(2, 28, 4)
#define M4U_PORT_L28_CAM_DRZS4NO_R1		MTK_M4U_DOM_ID(2, 28, 5)
#define M4U_PORT_L28_CAM_TNCSO_R1		MTK_M4U_DOM_ID(2, 28, 6)


/* CCU: Fake larb29 */
#define M4U_PORT_L29_CAM_CCU_AXI0		MTK_M4U_DOM_ID(3, 29, 0)

/* CCU: Fake larb30 */
#define M4U_PORT_L30_CAM_CCU_AXI1		MTK_M4U_DOM_ID(4, 30, 0)

/* APU: Fake larb31 */
#define M4U_PORT_L31_APU_CODE			MTK_M4U_DOM_ID(0, 31, 0)
#define M4U_PORT_L31_APU_DATA			MTK_M4U_DOM_ID(1, 31, 1)
#define M4U_PORT_L31_APU_VLM			MTK_M4U_DOM_ID(2, 31, 2)

/* INFRA: FAKE */
#define M4U_PORT_INFRA_PCIE1_R			MTK_M4U_DOM_ID(0, 1, 16)
#define M4U_PORT_INFRA_PCIE1_W			MTK_M4U_DOM_ID(0, 1, 17)
#define M4U_PORT_INFRA_PCIE0_R			MTK_M4U_DOM_ID(0, 1, 18)
#define M4U_PORT_INFRA_PCIE0_W			MTK_M4U_DOM_ID(0, 1, 19)
#define M4U_PORT_INFRA_SSUSB_P3_R		MTK_M4U_DOM_ID(0, 1, 20)
#define M4U_PORT_INFRA_SSUSB_P3_W		MTK_M4U_DOM_ID(0, 1, 21)
#define M4U_PORT_INFRA_SSUSB_P2_R		MTK_M4U_DOM_ID(0, 1, 22)
#define M4U_PORT_INFRA_SSUSB_P2_W		MTK_M4U_DOM_ID(0, 1, 23)
#define M4U_PORT_INFRA_SSUSB_P1_1_R		MTK_M4U_DOM_ID(0, 1, 24)
#define M4U_PORT_INFRA_SSUSB_P1_1_W		MTK_M4U_DOM_ID(0, 1, 25)
#define M4U_PORT_INFRA_SSUSB_P1_0_R		MTK_M4U_DOM_ID(0, 1, 26)
#define M4U_PORT_INFRA_SSUSB_P1_0_W		MTK_M4U_DOM_ID(0, 1, 27)
#define M4U_PORT_INFRA_SSUSB2_R			MTK_M4U_DOM_ID(0, 1, 28)
#define M4U_PORT_INFRA_SSUSB2_W			MTK_M4U_DOM_ID(0, 1, 29)
#define M4U_PORT_INFRA_SSUSB_R			MTK_M4U_DOM_ID(0, 1, 30)
#define M4U_PORT_INFRA_SSUSB_W			MTK_M4U_DOM_ID(0, 1, 31)

#define M4U_PORT_INFRA_PCIE0_BASE		(M4U_PORT_INFRA_PCIE0_R << 16)
#define M4U_PORT_INFRA_PCIE1_BASE		(M4U_PORT_INFRA_PCIE1_R << 16)

#endif