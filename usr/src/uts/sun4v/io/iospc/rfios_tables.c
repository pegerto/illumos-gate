/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

/*
 * RF IOS tables and functions to drive the IO performance counter driver.
 *
 * Please see rfiospc-tables.h for an explanation of how the table is put
 * together.
 */

#include <sys/types.h>
#include <sys/kstat.h>
#include <sys/sunndi.h>
#include <sys/pci.h>
#include <sys/hsvc.h>
#include "iospc.h"
#include "rfios_acc.h"
#include "rfios_tables.h"

static iospc_event_t rfios_imu_ctr_0_evts[] = {
	{ RFIOS_IMU01_S_EVT_NONE,
	    RFIOS_IMU01_EVT_NONE },
	{ RFIOS_IMU01_S_EVT_CLK,
	    RFIOS_IMU01_EVT_CLK },
	{ RFIOS_IMU01_S_EVT_TOTAL_MSIX,
	    RFIOS_IMU01_EVT_TOTAL_MSIX },
	{ RFIOS_IMU01_S_EVT_IOS_MSI,
	    RFIOS_IMU01_EVT_IOS_MSI },
	{ RFIOS_IMU01_S_EVT_PCIE_MSIX,
	    RFIOS_IMU01_EVT_PCIE_MSIX },
	{ RFIOS_IMU01_S_EVT_PCIE_MSGS,
	    RFIOS_IMU01_EVT_PCIE_MSGS },
	{ RFIOS_IMU01_S_EVT_FILTERED_MSIX,
	    RFIOS_IMU01_EVT_FILTERED_MSIX },
	{ RFIOS_IMU01_S_EVT_EQ_WR,
	    RFIOS_IMU01_EVT_EQ_WR },
	{ RFIOS_IMU01_S_EVT_MONDOS,
	    RFIOS_IMU01_EVT_MONDOS },
	{ COMMON_S_CLEAR_PIC,
	    RFIOS_IMU_CTR_EVT_MASK }
};

static iospc_event_t rfios_imu_ctr_1_evts[] = {
	{ RFIOS_IMU01_S_EVT_NONE,
	    RFIOS_IMU01_EVT_NONE },
	{ RFIOS_IMU01_S_EVT_CLK,
	    RFIOS_IMU01_EVT_CLK },
	{ RFIOS_IMU01_S_EVT_TOTAL_MSIX,
	    RFIOS_IMU01_EVT_TOTAL_MSIX },
	{ RFIOS_IMU01_S_EVT_IOS_MSI,
	    RFIOS_IMU01_EVT_IOS_MSI },
	{ RFIOS_IMU01_S_EVT_PCIE_MSIX,
	    RFIOS_IMU01_EVT_PCIE_MSIX },
	{ RFIOS_IMU01_S_EVT_PCIE_MSGS,
	    RFIOS_IMU01_EVT_PCIE_MSGS },
	{ RFIOS_IMU01_S_EVT_FILTERED_MSIX,
	    RFIOS_IMU01_EVT_FILTERED_MSIX },
	{ RFIOS_IMU01_S_EVT_EQ_WR,
	    RFIOS_IMU01_EVT_EQ_WR },
	{ RFIOS_IMU01_S_EVT_MONDOS,
	    RFIOS_IMU01_EVT_MONDOS },
	{ COMMON_S_CLEAR_PIC,
	    RFIOS_IMU_CTR_EVT_MASK }
};

static iospc_event_t rfios_atu_ctr_0_evts[] = {
	{ RFIOS_ATU01_S_EVT_NONE,
	    RFIOS_ATU01_EVT_NONE },
	{ RFIOS_ATU01_S_EVT_CLK,
	    RFIOS_ATU01_EVT_CLK },
	{ RFIOS_ATU01_S_EVT_FLOW_CTRL_STALL,
	    RFIOS_ATU01_EVT_FLOW_CTRL_STALL },
	{ RFIOS_ATU01_S_EVT_CLUMP_ACC,
	    RFIOS_ATU01_EVT_CLUMP_ACC },
	{ RFIOS_ATU01_S_EVT_CLUMP_MISS,
	    RFIOS_ATU01_EVT_CLUMP_MISS },
	{ RFIOS_ATU01_S_EVT_CLUMP_RESETS,
	    RFIOS_ATU01_EVT_CLUMP_RESETS },
	{ RFIOS_ATU01_S_EVT_CLUMP_TBL_WALK,
	    RFIOS_ATU01_EVT_CLUMP_TBL_WALK },
	{ RFIOS_ATU01_S_EVT_VIRT_ACC,
	    RFIOS_ATU01_EVT_VIRT_ACC },
	{ RFIOS_ATU01_S_EVT_VIRT_MISS,
	    RFIOS_ATU01_EVT_VIRT_MISS },
	{ RFIOS_ATU01_S_EVT_VIRT_RESETS,
	    RFIOS_ATU01_EVT_VIRT_RESETS },
	{ RFIOS_ATU01_S_EVT_VIRT_TBL_WALK,
	    RFIOS_ATU01_EVT_VIRT_TBL_WALK },
	{ RFIOS_ATU01_S_EVT_REAL_ACC,
	    RFIOS_ATU01_EVT_REAL_ACC },
	{ RFIOS_ATU01_S_EVT_REAL_MISS,
	    RFIOS_ATU01_EVT_REAL_MISS },
	{ RFIOS_ATU01_S_EVT_REAL_RESETS,
	    RFIOS_ATU01_EVT_REAL_RESETS },
	{ RFIOS_ATU01_S_EVT_REAL_TBL_WALK,
	    RFIOS_ATU01_EVT_REAL_TBL_WALK },
	{ RFIOS_ATU01_S_EVT_CMD_ERRORS,
	    RFIOS_ATU01_EVT_CMD_ERRORS },
	{ RFIOS_ATU01_S_EVT_VIRT_TRANS,
	    RFIOS_ATU01_EVT_VIRT_TRANS },
	{ RFIOS_ATU01_S_EVT_REAL_TRANS,
	    RFIOS_ATU01_EVT_REAL_TRANS },
	{ RFIOS_ATU01_S_EVT_PHYS_TRANS,
	    RFIOS_ATU01_EVT_PHYS_TRANS },
	{ RFIOS_ATU01_S_EVT_STRICT_ORDER_FORCED,
	    RFIOS_ATU01_EVT_STRICT_ORDER_FORCED },
	{ RFIOS_ATU01_S_EVT_RELAX_ORDER_FORCED,
	    RFIOS_ATU01_EVT_RELAX_ORDER_FORCED },
	{ RFIOS_ATU01_S_EVT_RELAX_ORDER_TLP,
	    RFIOS_ATU01_EVT_RELAX_ORDER_TLP },
	{ RFIOS_ATU01_S_EVT_RELAX_ORDER_TOTAL,
	    RFIOS_ATU01_EVT_RELAX_ORDER_TOTAL },
	{ COMMON_S_CLEAR_PIC,
	    RFIOS_ATU_CTR_EVT_MASK }
};

static iospc_event_t rfios_atu_ctr_1_evts[] = {
	{ RFIOS_ATU01_S_EVT_NONE,
	    RFIOS_ATU01_EVT_NONE },
	{ RFIOS_ATU01_S_EVT_CLK,
	    RFIOS_ATU01_EVT_CLK },
	{ RFIOS_ATU01_S_EVT_FLOW_CTRL_STALL,
	    RFIOS_ATU01_EVT_FLOW_CTRL_STALL },
	{ RFIOS_ATU01_S_EVT_CLUMP_ACC,
	    RFIOS_ATU01_EVT_CLUMP_ACC },
	{ RFIOS_ATU01_S_EVT_CLUMP_MISS,
	    RFIOS_ATU01_EVT_CLUMP_MISS },
	{ RFIOS_ATU01_S_EVT_CLUMP_RESETS,
	    RFIOS_ATU01_EVT_CLUMP_RESETS },
	{ RFIOS_ATU01_S_EVT_CLUMP_TBL_WALK,
	    RFIOS_ATU01_EVT_CLUMP_TBL_WALK },
	{ RFIOS_ATU01_S_EVT_VIRT_ACC,
	    RFIOS_ATU01_EVT_VIRT_ACC },
	{ RFIOS_ATU01_S_EVT_VIRT_MISS,
	    RFIOS_ATU01_EVT_VIRT_MISS },
	{ RFIOS_ATU01_S_EVT_VIRT_RESETS,
	    RFIOS_ATU01_EVT_VIRT_RESETS },
	{ RFIOS_ATU01_S_EVT_VIRT_TBL_WALK,
	    RFIOS_ATU01_EVT_VIRT_TBL_WALK },
	{ RFIOS_ATU01_S_EVT_REAL_ACC,
	    RFIOS_ATU01_EVT_REAL_ACC },
	{ RFIOS_ATU01_S_EVT_REAL_MISS,
	    RFIOS_ATU01_EVT_REAL_MISS },
	{ RFIOS_ATU01_S_EVT_REAL_RESETS,
	    RFIOS_ATU01_EVT_REAL_RESETS },
	{ RFIOS_ATU01_S_EVT_REAL_TBL_WALK,
	    RFIOS_ATU01_EVT_REAL_TBL_WALK },
	{ RFIOS_ATU01_S_EVT_CMD_ERRORS,
	    RFIOS_ATU01_EVT_CMD_ERRORS },
	{ RFIOS_ATU01_S_EVT_VIRT_TRANS,
	    RFIOS_ATU01_EVT_VIRT_TRANS },
	{ RFIOS_ATU01_S_EVT_REAL_TRANS,
	    RFIOS_ATU01_EVT_REAL_TRANS },
	{ RFIOS_ATU01_S_EVT_PHYS_TRANS,
	    RFIOS_ATU01_EVT_PHYS_TRANS },
	{ RFIOS_ATU01_S_EVT_STRICT_ORDER_FORCED,
	    RFIOS_ATU01_EVT_STRICT_ORDER_FORCED },
	{ RFIOS_ATU01_S_EVT_RELAX_ORDER_FORCED,
	    RFIOS_ATU01_EVT_RELAX_ORDER_FORCED },
	{ RFIOS_ATU01_S_EVT_RELAX_ORDER_TLP,
	    RFIOS_ATU01_EVT_RELAX_ORDER_TLP },
	{ RFIOS_ATU01_S_EVT_RELAX_ORDER_TOTAL,
	    RFIOS_ATU01_EVT_RELAX_ORDER_TOTAL },
	{ COMMON_S_CLEAR_PIC,
	    RFIOS_ATU_CTR_EVT_MASK }
};

static iospc_event_t rfios_npu_ctr_0_evts[] = {
	{ RFIOS_NPU01_S_EVT_NONE,
	    RFIOS_NPU01_EVT_NONE },
	{ RFIOS_NPU01_S_EVT_CLK,
	    RFIOS_NPU01_EVT_CLK },
	{ RFIOS_NPU01_S_EVT_ZERO_BYTE_READ,
	    RFIOS_NPU01_EVT_ZERO_BYTE_READ },
	{ RFIOS_NPU01_S_EVT_DMA_WRITE_LATENCY,
	    RFIOS_NPU01_EVT_DMA_WRITE_LATENCY },
	{ RFIOS_NPU01_S_EVT_DMA_WRITE_LATENCY_NUM,
	    RFIOS_NPU01_EVT_DMA_WRITE_LATENCY_NUM },
	{ RFIOS_NPU01_S_EVT_OSB_FULL_CYCLES,
	    RFIOS_NPU01_EVT_OSB_FULL_CYCLES },
	{ RFIOS_NPU01_S_EVT_DMA_READ_LATENCY,
	    RFIOS_NPU01_EVT_DMA_READ_LATENCY },
	{ RFIOS_NPU01_S_EVT_DMA_READ_LATENCY_NUM,
	    RFIOS_NPU01_EVT_DMA_READ_LATENCY_NUM },
	{ RFIOS_NPU01_S_EVT_PSB_FULL_CYCLES,
	    RFIOS_NPU01_EVT_PSB_FULL_CYCLES },
	{ RFIOS_NPU01_S_EVT_ICB_FULL_CYCLES,
	    RFIOS_NPU01_EVT_ICB_FULL_CYCLES },
	{ RFIOS_NPU01_S_EVT_ECB_FULL_CYCLES,
	    RFIOS_NPU01_EVT_ECB_FULL_CYCLES },
	{ RFIOS_NPU01_S_EVT_ATU_CSR_CFG_WRITES,
	    RFIOS_NPU01_EVT_ATU_CSR_CFG_WRITES },
	{ RFIOS_NPU01_S_EVT_ATU_CSR_CFG_READS,
	    RFIOS_NPU01_EVT_ATU_CSR_CFG_READS },
	{ RFIOS_NPU01_S_EVT_ATU_CSR_MEM_WRITES,
	    RFIOS_NPU01_EVT_ATU_CSR_MEM_WRITES },
	{ RFIOS_NPU01_S_EVT_ATU_CSR_MEM_READS,
	    RFIOS_NPU01_EVT_ATU_CSR_MEM_READS },
	{ RFIOS_NPU01_S_EVT_IMU_CSR_CFG_WRITES,
	    RFIOS_NPU01_EVT_IMU_CSR_CFG_WRITES },
	{ RFIOS_NPU01_S_EVT_IMU_CSR_CFG_READS,
	    RFIOS_NPU01_EVT_IMU_CSR_CFG_READS },
	{ RFIOS_NPU01_S_EVT_IMU_CSR_MEM_WRITES,
	    RFIOS_NPU01_EVT_IMU_CSR_MEM_WRITES },
	{ RFIOS_NPU01_S_EVT_IMU_CSR_MEM_READS,
	    RFIOS_NPU01_EVT_IMU_CSR_MEM_READS },
	{ RFIOS_NPU01_S_EVT_NPU_CSR_CFG_WRITES,
	    RFIOS_NPU01_EVT_NPU_CSR_CFG_WRITES },
	{ RFIOS_NPU01_S_EVT_NPU_CSR_CFG_READS,
	    RFIOS_NPU01_EVT_NPU_CSR_CFG_READS },
	{ RFIOS_NPU01_S_EVT_NPU_CSR_MEM_WRITES,
	    RFIOS_NPU01_EVT_NPU_CSR_MEM_WRITES },
	{ RFIOS_NPU01_S_EVT_NPU_CSR_MEM_READS,
	    RFIOS_NPU01_EVT_NPU_CSR_MEM_READS },
	{ RFIOS_NPU01_S_EVT_OTHER_CSR_CFG_WRITES,
	    RFIOS_NPU01_EVT_OTHER_CSR_CFG_WRITES },
	{ RFIOS_NPU01_S_EVT_OTHER_CSR_CFG_READS,
	    RFIOS_NPU01_EVT_OTHER_CSR_CFG_READS },
	{ RFIOS_NPU01_S_EVT_OTHER_CSR_MEM64_WRITES,
	    RFIOS_NPU01_EVT_OTHER_CSR_MEM64_WRITES },
	{ RFIOS_NPU01_S_EVT_OTHER_CSR_MEM64_READS,
	    RFIOS_NPU01_EVT_OTHER_CSR_MEM64_READS },
	{ RFIOS_NPU01_S_EVT_OTHER_CSR_MEM32_WRITES,
	    RFIOS_NPU01_EVT_OTHER_CSR_MEM32_WRITES },
	{ RFIOS_NPU01_S_EVT_OTHER_CSR_MEM32_READS,
	    RFIOS_NPU01_EVT_OTHER_CSR_MEM32_READS },
	{ RFIOS_NPU01_S_EVT_IO_SPACE_WRITES,
	    RFIOS_NPU01_EVT_IO_SPACE_WRITES },
	{ RFIOS_NPU01_S_EVT_IO_SPACE_READS,
	    RFIOS_NPU01_EVT_IO_SPACE_READS },
	{ RFIOS_NPU01_S_EVT_TOTAL_MSI,
	    RFIOS_NPU01_EVT_TOTAL_MSI },
	{ RFIOS_NPU01_S_EVT_ATU_MSI,
	    RFIOS_NPU01_EVT_ATU_MSI },
	{ RFIOS_NPU01_S_EVT_IMU_MSI,
	    RFIOS_NPU01_EVT_IMU_MSI },
	{ RFIOS_NPU01_S_EVT_NPU_MSI,
	    RFIOS_NPU01_EVT_NPU_MSI },
	{ RFIOS_NPU01_S_EVT_RETIRED_TAGS_CTO,
	    RFIOS_NPU01_EVT_RETIRED_TAGS_CTO },
	{ RFIOS_NPU01_S_EVT_NO_POSTED_TAGS_CYCYLES,
	    RFIOS_NPU01_EVT_NO_POSTED_TAGS_CYCYLES },
	{ COMMON_S_CLEAR_PIC,
	    RFIOS_NPU_CTR_EVT_MASK }
};

static iospc_event_t rfios_npu_ctr_1_evts[] = {
	{ RFIOS_NPU01_S_EVT_NONE,
	    RFIOS_NPU01_EVT_NONE },
	{ RFIOS_NPU01_S_EVT_CLK,
	    RFIOS_NPU01_EVT_CLK },
	{ RFIOS_NPU01_S_EVT_ZERO_BYTE_READ,
	    RFIOS_NPU01_EVT_ZERO_BYTE_READ },
	{ RFIOS_NPU01_S_EVT_DMA_WRITE_LATENCY,
	    RFIOS_NPU01_EVT_DMA_WRITE_LATENCY },
	{ RFIOS_NPU01_S_EVT_DMA_WRITE_LATENCY_NUM,
	    RFIOS_NPU01_EVT_DMA_WRITE_LATENCY_NUM },
	{ RFIOS_NPU01_S_EVT_OSB_FULL_CYCLES,
	    RFIOS_NPU01_EVT_OSB_FULL_CYCLES },
	{ RFIOS_NPU01_S_EVT_DMA_READ_LATENCY,
	    RFIOS_NPU01_EVT_DMA_READ_LATENCY },
	{ RFIOS_NPU01_S_EVT_DMA_READ_LATENCY_NUM,
	    RFIOS_NPU01_EVT_DMA_READ_LATENCY_NUM },
	{ RFIOS_NPU01_S_EVT_PSB_FULL_CYCLES,
	    RFIOS_NPU01_EVT_PSB_FULL_CYCLES },
	{ RFIOS_NPU01_S_EVT_ICB_FULL_CYCLES,
	    RFIOS_NPU01_EVT_ICB_FULL_CYCLES },
	{ RFIOS_NPU01_S_EVT_ECB_FULL_CYCLES,
	    RFIOS_NPU01_EVT_ECB_FULL_CYCLES },
	{ RFIOS_NPU01_S_EVT_ATU_CSR_CFG_WRITES,
	    RFIOS_NPU01_EVT_ATU_CSR_CFG_WRITES },
	{ RFIOS_NPU01_S_EVT_ATU_CSR_CFG_READS,
	    RFIOS_NPU01_EVT_ATU_CSR_CFG_READS },
	{ RFIOS_NPU01_S_EVT_ATU_CSR_MEM_WRITES,
	    RFIOS_NPU01_EVT_ATU_CSR_MEM_WRITES },
	{ RFIOS_NPU01_S_EVT_ATU_CSR_MEM_READS,
	    RFIOS_NPU01_EVT_ATU_CSR_MEM_READS },
	{ RFIOS_NPU01_S_EVT_IMU_CSR_CFG_WRITES,
	    RFIOS_NPU01_EVT_IMU_CSR_CFG_WRITES },
	{ RFIOS_NPU01_S_EVT_IMU_CSR_CFG_READS,
	    RFIOS_NPU01_EVT_IMU_CSR_CFG_READS },
	{ RFIOS_NPU01_S_EVT_IMU_CSR_MEM_WRITES,
	    RFIOS_NPU01_EVT_IMU_CSR_MEM_WRITES },
	{ RFIOS_NPU01_S_EVT_IMU_CSR_MEM_READS,
	    RFIOS_NPU01_EVT_IMU_CSR_MEM_READS },
	{ RFIOS_NPU01_S_EVT_NPU_CSR_CFG_WRITES,
	    RFIOS_NPU01_EVT_NPU_CSR_CFG_WRITES },
	{ RFIOS_NPU01_S_EVT_NPU_CSR_CFG_READS,
	    RFIOS_NPU01_EVT_NPU_CSR_CFG_READS },
	{ RFIOS_NPU01_S_EVT_NPU_CSR_MEM_WRITES,
	    RFIOS_NPU01_EVT_NPU_CSR_MEM_WRITES },
	{ RFIOS_NPU01_S_EVT_NPU_CSR_MEM_READS,
	    RFIOS_NPU01_EVT_NPU_CSR_MEM_READS },
	{ RFIOS_NPU01_S_EVT_OTHER_CSR_CFG_WRITES,
	    RFIOS_NPU01_EVT_OTHER_CSR_CFG_WRITES },
	{ RFIOS_NPU01_S_EVT_OTHER_CSR_CFG_READS,
	    RFIOS_NPU01_EVT_OTHER_CSR_CFG_READS },
	{ RFIOS_NPU01_S_EVT_OTHER_CSR_MEM64_WRITES,
	    RFIOS_NPU01_EVT_OTHER_CSR_MEM64_WRITES },
	{ RFIOS_NPU01_S_EVT_OTHER_CSR_MEM64_READS,
	    RFIOS_NPU01_EVT_OTHER_CSR_MEM64_READS },
	{ RFIOS_NPU01_S_EVT_OTHER_CSR_MEM32_WRITES,
	    RFIOS_NPU01_EVT_OTHER_CSR_MEM32_WRITES },
	{ RFIOS_NPU01_S_EVT_OTHER_CSR_MEM32_READS,
	    RFIOS_NPU01_EVT_OTHER_CSR_MEM32_READS },
	{ RFIOS_NPU01_S_EVT_IO_SPACE_WRITES,
	    RFIOS_NPU01_EVT_IO_SPACE_WRITES },
	{ RFIOS_NPU01_S_EVT_IO_SPACE_READS,
	    RFIOS_NPU01_EVT_IO_SPACE_READS },
	{ RFIOS_NPU01_S_EVT_TOTAL_MSI,
	    RFIOS_NPU01_EVT_TOTAL_MSI },
	{ RFIOS_NPU01_S_EVT_ATU_MSI,
	    RFIOS_NPU01_EVT_ATU_MSI },
	{ RFIOS_NPU01_S_EVT_IMU_MSI,
	    RFIOS_NPU01_EVT_IMU_MSI },
	{ RFIOS_NPU01_S_EVT_NPU_MSI,
	    RFIOS_NPU01_EVT_NPU_MSI },
	{ RFIOS_NPU01_S_EVT_RETIRED_TAGS_CTO,
	    RFIOS_NPU01_EVT_RETIRED_TAGS_CTO },
	{ RFIOS_NPU01_S_EVT_NO_POSTED_TAGS_CYCYLES,
	    RFIOS_NPU01_EVT_NO_POSTED_TAGS_CYCYLES },
	{ COMMON_S_CLEAR_PIC,
	    RFIOS_NPU_CTR_EVT_MASK }
};

static iospc_event_t rfios_pex_ctr_0_evts[] = {
	{ RFIOS_PEX01_S_EVT_NONE,
	    RFIOS_PEX01_EVT_NONE },
	{ RFIOS_PEX01_S_EVT_CLK,
	    RFIOS_PEX01_EVT_CLK },
	{ RFIOS_PEX01_S_EVT_PEU0_DMA_WR_REC,
	    RFIOS_PEX01_EVT_PEU0_DMA_WR_REC },
	{ RFIOS_PEX01_S_EVT_PEU0_PIO_RD_REC,
	    RFIOS_PEX01_EVT_PEU0_PIO_RD_REC },
	{ RFIOS_PEX01_S_EVT_PEU0_DMA_RD_SENT,
	    RFIOS_PEX01_EVT_PEU0_DMA_RD_SENT },
	{ RFIOS_PEX01_S_EVT_PEU0_TLP_REC,
	    RFIOS_PEX01_EVT_PEU0_TLP_REC },
	{ RFIOS_PEX01_S_EVT_PEU0_TRP_FULL_CYCLES,
	    RFIOS_PEX01_EVT_PEU0_TRP_FULL_CYCLES },
	{ RFIOS_PEX01_S_EVT_PEU0_TCH_FULL_CYCLES,
	    RFIOS_PEX01_EVT_PEU0_TCH_FULL_CYCLES },
	{ RFIOS_PEX01_S_EVT_PEU0_TCD_FULL_CYCLES,
	    RFIOS_PEX01_EVT_PEU0_TCD_FULL_CYCLES },
	{ RFIOS_PEX01_S_EVT_NON_POSTED_PIOS_LATENCY,
	    RFIOS_PEX01_EVT_NON_POSTED_PIOS_LATENCY },
	{ RFIOS_PEX01_S_EVT_NON_POSTED_PIOS_NUM,
	    RFIOS_PEX01_EVT_NON_POSTED_PIOS_NUM },
	{ RFIOS_PEX01_S_EVT_PEX_CFG_WRITE,
	    RFIOS_PEX01_EVT_PEX_CFG_WRITE },
	{ RFIOS_PEX01_S_EVT_PEX_CFG_READ,
	    RFIOS_PEX01_EVT_PEX_CFG_READ },
	{ RFIOS_PEX01_S_EVT_PEX_MEM_WRITE,
	    RFIOS_PEX01_EVT_PEX_MEM_WRITE },
	{ RFIOS_PEX01_S_EVT_PEX_MEM_READ,
	    RFIOS_PEX01_EVT_PEX_MEM_READ },
	{ RFIOS_PEX01_S_EVT_PEU1_DMA_WR_REC,
	    RFIOS_PEX01_EVT_PEU1_DMA_WR_REC },
	{ RFIOS_PEX01_S_EVT_PEU1_PIO_RD_REC,
	    RFIOS_PEX01_EVT_PEU1_PIO_RD_REC },
	{ RFIOS_PEX01_S_EVT_PEU1_DMA_RD_SENT,
	    RFIOS_PEX01_EVT_PEU1_DMA_RD_SENT },
	{ RFIOS_PEX01_S_EVT_PEU1_TLP_REC,
	    RFIOS_PEX01_EVT_PEU1_TLP_REC },
	{ RFIOS_PEX01_S_EVT_PEU1_TRP_FULL_CYCLES,
	    RFIOS_PEX01_EVT_PEU1_TRP_FULL_CYCLES },
	{ RFIOS_PEX01_S_EVT_PEU1_TCH_FULL_CYCLES,
	    RFIOS_PEX01_EVT_PEU1_TCH_FULL_CYCLES },
	{ RFIOS_PEX01_S_EVT_PEU1_TCD_FULL_CYCLES,
	    RFIOS_PEX01_EVT_PEU1_TCD_FULL_CYCLES },
	{ COMMON_S_CLEAR_PIC,
	    RFIOS_PEX_CTR_EVT_MASK }
};

static iospc_event_t rfios_pex_ctr_1_evts[] = {
	{ RFIOS_PEX01_S_EVT_NONE,
	    RFIOS_PEX01_EVT_NONE },
	{ RFIOS_PEX01_S_EVT_CLK,
	    RFIOS_PEX01_EVT_CLK },
	{ RFIOS_PEX01_S_EVT_PEU0_DMA_WR_REC,
	    RFIOS_PEX01_EVT_PEU0_DMA_WR_REC },
	{ RFIOS_PEX01_S_EVT_PEU0_PIO_RD_REC,
	    RFIOS_PEX01_EVT_PEU0_PIO_RD_REC },
	{ RFIOS_PEX01_S_EVT_PEU0_DMA_RD_SENT,
	    RFIOS_PEX01_EVT_PEU0_DMA_RD_SENT },
	{ RFIOS_PEX01_S_EVT_PEU0_TLP_REC,
	    RFIOS_PEX01_EVT_PEU0_TLP_REC },
	{ RFIOS_PEX01_S_EVT_PEU0_TRP_FULL_CYCLES,
	    RFIOS_PEX01_EVT_PEU0_TRP_FULL_CYCLES },
	{ RFIOS_PEX01_S_EVT_PEU0_TCH_FULL_CYCLES,
	    RFIOS_PEX01_EVT_PEU0_TCH_FULL_CYCLES },
	{ RFIOS_PEX01_S_EVT_PEU0_TCD_FULL_CYCLES,
	    RFIOS_PEX01_EVT_PEU0_TCD_FULL_CYCLES },
	{ RFIOS_PEX01_S_EVT_NON_POSTED_PIOS_LATENCY,
	    RFIOS_PEX01_EVT_NON_POSTED_PIOS_LATENCY },
	{ RFIOS_PEX01_S_EVT_NON_POSTED_PIOS_NUM,
	    RFIOS_PEX01_EVT_NON_POSTED_PIOS_NUM },
	{ RFIOS_PEX01_S_EVT_PEX_CFG_WRITE,
	    RFIOS_PEX01_EVT_PEX_CFG_WRITE },
	{ RFIOS_PEX01_S_EVT_PEX_CFG_READ,
	    RFIOS_PEX01_EVT_PEX_CFG_READ },
	{ RFIOS_PEX01_S_EVT_PEX_MEM_WRITE,
	    RFIOS_PEX01_EVT_PEX_MEM_WRITE },
	{ RFIOS_PEX01_S_EVT_PEX_MEM_READ,
	    RFIOS_PEX01_EVT_PEX_MEM_READ },
	{ RFIOS_PEX01_S_EVT_PEU1_DMA_WR_REC,
	    RFIOS_PEX01_EVT_PEU1_DMA_WR_REC },
	{ RFIOS_PEX01_S_EVT_PEU1_PIO_RD_REC,
	    RFIOS_PEX01_EVT_PEU1_PIO_RD_REC },
	{ RFIOS_PEX01_S_EVT_PEU1_DMA_RD_SENT,
	    RFIOS_PEX01_EVT_PEU1_DMA_RD_SENT },
	{ RFIOS_PEX01_S_EVT_PEU1_TLP_REC,
	    RFIOS_PEX01_EVT_PEU1_TLP_REC },
	{ RFIOS_PEX01_S_EVT_PEU1_TRP_FULL_CYCLES,
	    RFIOS_PEX01_EVT_PEU1_TRP_FULL_CYCLES },
	{ RFIOS_PEX01_S_EVT_PEU1_TCH_FULL_CYCLES,
	    RFIOS_PEX01_EVT_PEU1_TCH_FULL_CYCLES },
	{ RFIOS_PEX01_S_EVT_PEU1_TCD_FULL_CYCLES,
	    RFIOS_PEX01_EVT_PEU1_TCD_FULL_CYCLES },
	{ COMMON_S_CLEAR_PIC,
	    RFIOS_PEX_CTR_EVT_MASK }
};

static iospc_event_t rfios_peu_ctr_0_evts[] = {
	{ RFIOS_PEU01_S_EVT_NONE,
    RFIOS_PEU01_EVT_NONE },
	{ RFIOS_PEU01_S_EVT_CLK,
    RFIOS_PEU01_EVT_CLK },
	{ RFIOS_PEU01_S_EVT_INT_CFG_WR_RECD,
    RFIOS_PEU01_EVT_INT_CFG_WR_RECD },
	{ RFIOS_PEU01_S_EVT_INT_CFG_RD_RECD,
    RFIOS_PEU01_EVT_INT_CFG_RD_RECD },
	{ RFIOS_PEU01_S_EVT_INT_MEM_WR_RECD,
    RFIOS_PEU01_EVT_INT_MEM_WR_RECD },
	{ RFIOS_PEU01_S_EVT_INT_MEM_RD_RECD,
    RFIOS_PEU01_EVT_INT_MEM_RD_RECD },
	{ RFIOS_PEU01_S_EVT_EXT_CFG_WR_RECD,
    RFIOS_PEU01_EVT_EXT_CFG_WR_RECD },
	{ RFIOS_PEU01_S_EVT_EXT_CFG_RD_RECD,
    RFIOS_PEU01_EVT_EXT_CFG_RD_RECD },
	{ RFIOS_PEU01_S_EVT_EXT_MEM_WR_RECD,
    RFIOS_PEU01_EVT_EXT_MEM_WR_RECD },
	{ RFIOS_PEU01_S_EVT_EXT_MEM_RD_RECD,
    RFIOS_PEU01_EVT_EXT_MEM_RD_RECD },
	{ RFIOS_PEU01_S_EVT_MEM_RD_REQ_RECD_ALL,
    RFIOS_PEU01_EVT_MEM_RD_REQ_RECD_ALL },
	{ RFIOS_PEU01_S_EVT_MEM_RD_REQ_RECD_1_15DW,
    RFIOS_PEU01_EVT_MEM_RD_REQ_RECD_1_15DW },
	{ RFIOS_PEU01_S_EVT_MEM_RD_REQ_RECD_16_31DW,
    RFIOS_PEU01_EVT_MEM_RD_REQ_RECD_16_31DW },
	{ RFIOS_PEU01_S_EVT_MEM_RD_REQ_RECD_32_63DW,
    RFIOS_PEU01_EVT_MEM_RD_REQ_RECD_32_63DW },
	{ RFIOS_PEU01_S_EVT_MEM_RD_REQ_RECD_64_127DW,
    RFIOS_PEU01_EVT_MEM_RD_REQ_RECD_64_127DW },
	{ RFIOS_PEU01_S_EVT_MEM_RD_REQ_RECD_128_255DW,
    RFIOS_PEU01_EVT_MEM_RD_REQ_RECD_128_255DW },
	{ RFIOS_PEU01_S_EVT_MEM_RD_REQ_RECD_256_511DW,
    RFIOS_PEU01_EVT_MEM_RD_REQ_RECD_256_511DW },
	{ RFIOS_PEU01_S_EVT_MEM_RD_REQ_RECD_512_1024DW,
    RFIOS_PEU01_EVT_MEM_RD_REQ_RECD_512_1024DW },
	{ RFIOS_PEU01_S_EVT_MEM_WR_REQ_RECD_ALL,
    RFIOS_PEU01_EVT_MEM_WR_REQ_RECD_ALL },
	{ RFIOS_PEU01_S_EVT_MEM_WR_REQ_RECD_1_15DW,
    RFIOS_PEU01_EVT_MEM_WR_REQ_RECD_1_15DW },
	{ RFIOS_PEU01_S_EVT_MEM_WR_REQ_RECD_16_31DW,
    RFIOS_PEU01_EVT_MEM_WR_REQ_RECD_16_31DW },
	{ RFIOS_PEU01_S_EVT_MEM_WR_REQ_RECD_32_63DW,
    RFIOS_PEU01_EVT_MEM_WR_REQ_RECD_32_63DW },
	{ RFIOS_PEU01_S_EVT_MEM_WR_REQ_RECD_64_127DW,
    RFIOS_PEU01_EVT_MEM_WR_REQ_RECD_64_127DW },
	{ RFIOS_PEU01_S_EVT_MEM_WR_REQ_RECD_128_255DW,
    RFIOS_PEU01_EVT_MEM_WR_REQ_RECD_128_255DW },
	{ RFIOS_PEU01_S_EVT_MEM_WR_REQ_RECD_256_511DW,
    RFIOS_PEU01_EVT_MEM_WR_REQ_RECD_256_511DW },
	{ RFIOS_PEU01_S_EVT_MEM_WR_REQ_RECD_512_1024DW,
    RFIOS_PEU01_EVT_MEM_WR_REQ_RECD_512_1024DW },
	{ RFIOS_PEU01_S_EVT_XMIT_POSTED_HDR_NA_CYC,
    RFIOS_PEU01_EVT_XMIT_POSTED_HDR_NA_CYC },
	{ RFIOS_PEU01_S_EVT_XMIT_POSTED_DATA_NA_CYC,
    RFIOS_PEU01_EVT_XMIT_POSTED_DATA_NA_CYC },
	{ RFIOS_PEU01_S_EVT_XMIT_NON_POSTED_HDR_NA_CYC,
    RFIOS_PEU01_EVT_XMIT_NON_POSTED_HDR_NA_CYC },
	{ RFIOS_PEU01_S_EVT_XMIT_NON_POSTED_DATA_NA_CYC,
    RFIOS_PEU01_EVT_XMIT_NON_POSTED_DATA_NA_CYC },
	{ RFIOS_PEU01_S_EVT_XMIT_COMPL_HDR_NA_CYC,
    RFIOS_PEU01_EVT_XMIT_COMPL_HDR_NA_CYC },
	{ RFIOS_PEU01_S_EVT_XMIT_COMPL_DATA_NA_CYC,
    RFIOS_PEU01_EVT_XMIT_COMPL_DATA_NA_CYC },
	{ RFIOS_PEU01_S_EVT_NO_XMIT_CRED_CYC,
    RFIOS_PEU01_EVT_NO_XMIT_CRED_CYC },
	{ RFIOS_PEU01_S_EVT_RETRY_BUFF_NA_CYC,
    RFIOS_PEU01_EVT_RETRY_BUFF_NA_CYC },
	{ RFIOS_PEU01_S_EVT_REC_FLCTRL_COMP_EXST_CYC,
    RFIOS_PEU01_EVT_REC_FLCTRL_COMP_EXST_CYC },
	{ RFIOS_PEU01_S_EVT_REC_FLCTRL_NPOST_EXST_CYC,
    RFIOS_PEU01_EVT_REC_FLCTRL_NPOST_EXST_CYC },
	{ RFIOS_PEU01_S_EVT_REC_FLCTRL_PST_DAT_EXST,
    RFIOS_PEU01_EVT_REC_FLCTRL_PST_DAT_EXST },
	{ RFIOS_PEU01_S_EVT_REC_FLCTRL_PST_DT_CDT_EXST,
    RFIOS_PEU01_EVT_REC_FLCTRL_PST_DT_CDT_EXST },
	{ RFIOS_PEU01_S_EVT_REC_FLCTRL_PST_CDT_EXST,
    RFIOS_PEU01_EVT_REC_FLCTRL_PST_CDT_EXST },
	{ RFIOS_PEU01_S_EVT_REC_FLCTRL_CDT_EXST,
    RFIOS_PEU01_EVT_REC_FLCTRL_CDT_EXST },
	{ RFIOS_PEU01_S_EVT_DLLP_CRC_ERRORS,
    RFIOS_PEU01_EVT_DLLP_CRC_ERRORS },
	{ RFIOS_PEU01_S_EVT_TLP_CRC_ERRORS,
    RFIOS_PEU01_EVT_TLP_CRC_ERRORS },
	{ RFIOS_PEU01_S_EVT_TLP_RECD_WITH_EDB,
    RFIOS_PEU01_EVT_TLP_RECD_WITH_EDB },
	{ RFIOS_PEU01_S_EVT_RECD_FC_TIMEOUT_ERROR,
    RFIOS_PEU01_EVT_RECD_FC_TIMEOUT_ERROR },
	{ RFIOS_PEU01_S_EVT_REPLAY_NUM_ROLLOVERS,
    RFIOS_PEU01_EVT_REPLAY_NUM_ROLLOVERS },
	{ RFIOS_PEU01_S_EVT_REPLAY_TIMER_TIMEOUTS,
    RFIOS_PEU01_EVT_REPLAY_TIMER_TIMEOUTS },
	{ RFIOS_PEU01_S_EVT_REPLAYS_INITIATED,
    RFIOS_PEU01_EVT_REPLAYS_INITIATED },
	{ RFIOS_PEU01_S_EVT_LTSSM_RECOVERY_CYC,
    RFIOS_PEU01_EVT_LTSSM_RECOVERY_CYC },
	{ RFIOS_PEU01_S_EVT_ENTRIES_LTSSM_RECOVERY,
    RFIOS_PEU01_EVT_ENTRIES_LTSSM_RECOVERY },
	{ RFIOS_PEU01_S_EVT_REC_L0S_STATE_CYC,
    RFIOS_PEU01_EVT_REC_L0S_STATE_CYC },
	{ RFIOS_PEU01_S_EVT_REC_L0S_STATE_TRANS,
    RFIOS_PEU01_EVT_REC_L0S_STATE_TRANS },
	{ RFIOS_PEU01_S_EVT_XMIT_L0S_STATE_CYC,
    RFIOS_PEU01_EVT_XMIT_L0S_STATE_CYC },
	{ RFIOS_PEU01_S_EVT_XMIT_L0S_STATE_TRANS,
    RFIOS_PEU01_EVT_XMIT_L0S_STATE_TRANS },
	{ COMMON_S_CLEAR_PIC,
    RFIOS_PEU_CTR_EVT_MASK }
};

static iospc_event_t rfios_peu_ctr_1_evts[] = {
	{ RFIOS_PEU01_S_EVT_NONE,
	    RFIOS_PEU01_EVT_NONE },
	{ RFIOS_PEU01_S_EVT_CLK,
	    RFIOS_PEU01_EVT_CLK },
	{ RFIOS_PEU01_S_EVT_INT_CFG_WR_RECD,
	    RFIOS_PEU01_EVT_INT_CFG_WR_RECD },
	{ RFIOS_PEU01_S_EVT_INT_CFG_RD_RECD,
	    RFIOS_PEU01_EVT_INT_CFG_RD_RECD },
	{ RFIOS_PEU01_S_EVT_INT_MEM_WR_RECD,
	    RFIOS_PEU01_EVT_INT_MEM_WR_RECD },
	{ RFIOS_PEU01_S_EVT_INT_MEM_RD_RECD,
	    RFIOS_PEU01_EVT_INT_MEM_RD_RECD },
	{ RFIOS_PEU01_S_EVT_EXT_CFG_WR_RECD,
	    RFIOS_PEU01_EVT_EXT_CFG_WR_RECD },
	{ RFIOS_PEU01_S_EVT_EXT_CFG_RD_RECD,
	    RFIOS_PEU01_EVT_EXT_CFG_RD_RECD },
	{ RFIOS_PEU01_S_EVT_EXT_MEM_WR_RECD,
	    RFIOS_PEU01_EVT_EXT_MEM_WR_RECD },
	{ RFIOS_PEU01_S_EVT_EXT_MEM_RD_RECD,
	    RFIOS_PEU01_EVT_EXT_MEM_RD_RECD },
	{ RFIOS_PEU01_S_EVT_MEM_RD_REQ_RECD_ALL,
	    RFIOS_PEU01_EVT_MEM_RD_REQ_RECD_ALL },
	{ RFIOS_PEU01_S_EVT_MEM_RD_REQ_RECD_1_15DW,
	    RFIOS_PEU01_EVT_MEM_RD_REQ_RECD_1_15DW },
	{ RFIOS_PEU01_S_EVT_MEM_RD_REQ_RECD_16_31DW,
	    RFIOS_PEU01_EVT_MEM_RD_REQ_RECD_16_31DW },
	{ RFIOS_PEU01_S_EVT_MEM_RD_REQ_RECD_32_63DW,
	    RFIOS_PEU01_EVT_MEM_RD_REQ_RECD_32_63DW },
	{ RFIOS_PEU01_S_EVT_MEM_RD_REQ_RECD_64_127DW,
	    RFIOS_PEU01_EVT_MEM_RD_REQ_RECD_64_127DW },
	{ RFIOS_PEU01_S_EVT_MEM_RD_REQ_RECD_128_255DW,
	    RFIOS_PEU01_EVT_MEM_RD_REQ_RECD_128_255DW },
	{ RFIOS_PEU01_S_EVT_MEM_RD_REQ_RECD_256_511DW,
	    RFIOS_PEU01_EVT_MEM_RD_REQ_RECD_256_511DW },
	{ RFIOS_PEU01_S_EVT_MEM_RD_REQ_RECD_512_1024DW,
	    RFIOS_PEU01_EVT_MEM_RD_REQ_RECD_512_1024DW },
	{ RFIOS_PEU01_S_EVT_MEM_WR_REQ_RECD_ALL,
	    RFIOS_PEU01_EVT_MEM_WR_REQ_RECD_ALL },
	{ RFIOS_PEU01_S_EVT_MEM_WR_REQ_RECD_1_15DW,
	    RFIOS_PEU01_EVT_MEM_WR_REQ_RECD_1_15DW },
	{ RFIOS_PEU01_S_EVT_MEM_WR_REQ_RECD_16_31DW,
	    RFIOS_PEU01_EVT_MEM_WR_REQ_RECD_16_31DW },
	{ RFIOS_PEU01_S_EVT_MEM_WR_REQ_RECD_32_63DW,
	    RFIOS_PEU01_EVT_MEM_WR_REQ_RECD_32_63DW },
	{ RFIOS_PEU01_S_EVT_MEM_WR_REQ_RECD_64_127DW,
	    RFIOS_PEU01_EVT_MEM_WR_REQ_RECD_64_127DW },
	{ RFIOS_PEU01_S_EVT_MEM_WR_REQ_RECD_128_255DW,
	    RFIOS_PEU01_EVT_MEM_WR_REQ_RECD_128_255DW },
	{ RFIOS_PEU01_S_EVT_MEM_WR_REQ_RECD_256_511DW,
	    RFIOS_PEU01_EVT_MEM_WR_REQ_RECD_256_511DW },
	{ RFIOS_PEU01_S_EVT_MEM_WR_REQ_RECD_512_1024DW,
	    RFIOS_PEU01_EVT_MEM_WR_REQ_RECD_512_1024DW },
	{ RFIOS_PEU01_S_EVT_XMIT_POSTED_HDR_NA_CYC,
	    RFIOS_PEU01_EVT_XMIT_POSTED_HDR_NA_CYC },
	{ RFIOS_PEU01_S_EVT_XMIT_POSTED_DATA_NA_CYC,
	    RFIOS_PEU01_EVT_XMIT_POSTED_DATA_NA_CYC },
	{ RFIOS_PEU01_S_EVT_XMIT_NON_POSTED_HDR_NA_CYC,
	    RFIOS_PEU01_EVT_XMIT_NON_POSTED_HDR_NA_CYC },
	{ RFIOS_PEU01_S_EVT_XMIT_NON_POSTED_DATA_NA_CYC,
	    RFIOS_PEU01_EVT_XMIT_NON_POSTED_DATA_NA_CYC },
	{ RFIOS_PEU01_S_EVT_XMIT_COMPL_HDR_NA_CYC,
	    RFIOS_PEU01_EVT_XMIT_COMPL_HDR_NA_CYC },
	{ RFIOS_PEU01_S_EVT_XMIT_COMPL_DATA_NA_CYC,
	    RFIOS_PEU01_EVT_XMIT_COMPL_DATA_NA_CYC },
	{ RFIOS_PEU01_S_EVT_NO_XMIT_CRED_CYC,
	    RFIOS_PEU01_EVT_NO_XMIT_CRED_CYC },
	{ RFIOS_PEU01_S_EVT_RETRY_BUFF_NA_CYC,
	    RFIOS_PEU01_EVT_RETRY_BUFF_NA_CYC },
	{ RFIOS_PEU01_S_EVT_REC_FLCTRL_COMP_EXST_CYC,
	    RFIOS_PEU01_EVT_REC_FLCTRL_COMP_EXST_CYC },
	{ RFIOS_PEU01_S_EVT_REC_FLCTRL_NPOST_EXST_CYC,
	    RFIOS_PEU01_EVT_REC_FLCTRL_NPOST_EXST_CYC },
	{ RFIOS_PEU01_S_EVT_REC_FLCTRL_PST_DAT_EXST,
	    RFIOS_PEU01_EVT_REC_FLCTRL_PST_DAT_EXST },
	{ RFIOS_PEU01_S_EVT_REC_FLCTRL_PST_DT_CDT_EXST,
	    RFIOS_PEU01_EVT_REC_FLCTRL_PST_DT_CDT_EXST },
	{ RFIOS_PEU01_S_EVT_REC_FLCTRL_PST_CDT_EXST,
	    RFIOS_PEU01_EVT_REC_FLCTRL_PST_CDT_EXST },
	{ RFIOS_PEU01_S_EVT_REC_FLCTRL_CDT_EXST,
	    RFIOS_PEU01_EVT_REC_FLCTRL_CDT_EXST },
	{ RFIOS_PEU01_S_EVT_DLLP_CRC_ERRORS,
	    RFIOS_PEU01_EVT_DLLP_CRC_ERRORS },
	{ RFIOS_PEU01_S_EVT_TLP_CRC_ERRORS,
	    RFIOS_PEU01_EVT_TLP_CRC_ERRORS },
	{ RFIOS_PEU01_S_EVT_TLP_RECD_WITH_EDB,
	    RFIOS_PEU01_EVT_TLP_RECD_WITH_EDB },
	{ RFIOS_PEU01_S_EVT_RECD_FC_TIMEOUT_ERROR,
	    RFIOS_PEU01_EVT_RECD_FC_TIMEOUT_ERROR },
	{ RFIOS_PEU01_S_EVT_REPLAY_NUM_ROLLOVERS,
	    RFIOS_PEU01_EVT_REPLAY_NUM_ROLLOVERS },
	{ RFIOS_PEU01_S_EVT_REPLAY_TIMER_TIMEOUTS,
	    RFIOS_PEU01_EVT_REPLAY_TIMER_TIMEOUTS },
	{ RFIOS_PEU01_S_EVT_REPLAYS_INITIATED,
	    RFIOS_PEU01_EVT_REPLAYS_INITIATED },
	{ RFIOS_PEU01_S_EVT_LTSSM_RECOVERY_CYC,
	    RFIOS_PEU01_EVT_LTSSM_RECOVERY_CYC },
	{ RFIOS_PEU01_S_EVT_ENTRIES_LTSSM_RECOVERY,
	    RFIOS_PEU01_EVT_ENTRIES_LTSSM_RECOVERY },
	{ RFIOS_PEU01_S_EVT_REC_L0S_STATE_CYC,
	    RFIOS_PEU01_EVT_REC_L0S_STATE_CYC },
	{ RFIOS_PEU01_S_EVT_REC_L0S_STATE_TRANS,
	    RFIOS_PEU01_EVT_REC_L0S_STATE_TRANS },
	{ RFIOS_PEU01_S_EVT_XMIT_L0S_STATE_CYC,
	    RFIOS_PEU01_EVT_XMIT_L0S_STATE_CYC },
	{ RFIOS_PEU01_S_EVT_XMIT_L0S_STATE_TRANS,
	    RFIOS_PEU01_EVT_XMIT_L0S_STATE_TRANS },
	{ COMMON_S_CLEAR_PIC,
	    RFIOS_PEU_CTR_EVT_MASK }
};


static iospc_regsel_fld_t rfios_imu_regsel_flds[] = {
	{ rfios_imu_ctr_0_evts, NUM_EVTS(rfios_imu_ctr_0_evts),
	    RFIOS_IMU_CTR_EVT_MASK, RFIOS_IMU_CTR_0_EVT_OFF },
	{ rfios_imu_ctr_1_evts, NUM_EVTS(rfios_imu_ctr_1_evts),
	    RFIOS_IMU_CTR_EVT_MASK, RFIOS_IMU_CTR_1_EVT_OFF }
};

static iospc_regsel_fld_t rfios_atu_regsel_flds[] = {
	{ rfios_atu_ctr_0_evts, NUM_EVTS(rfios_atu_ctr_0_evts),
	    RFIOS_ATU_CTR_EVT_MASK, RFIOS_ATU_CTR_0_EVT_OFF },
	{ rfios_atu_ctr_1_evts, NUM_EVTS(rfios_atu_ctr_1_evts),
	    RFIOS_ATU_CTR_EVT_MASK, RFIOS_ATU_CTR_1_EVT_OFF }
};

static iospc_regsel_fld_t rfios_npu_regsel_flds[] = {
	{ rfios_npu_ctr_0_evts, NUM_EVTS(rfios_npu_ctr_0_evts),
	    RFIOS_NPU_CTR_EVT_MASK, RFIOS_NPU_CTR_0_EVT_OFF },
	{ rfios_npu_ctr_1_evts, NUM_EVTS(rfios_npu_ctr_1_evts),
	    RFIOS_NPU_CTR_EVT_MASK, RFIOS_NPU_CTR_1_EVT_OFF }
};

static iospc_regsel_fld_t rfios_pex_regsel_flds[] = {
	{ rfios_pex_ctr_0_evts, NUM_EVTS(rfios_pex_ctr_0_evts),
	    RFIOS_PEX_CTR_EVT_MASK, RFIOS_PEX_CTR_0_EVT_OFF },
	{ rfios_pex_ctr_1_evts, NUM_EVTS(rfios_pex_ctr_1_evts),
	    RFIOS_PEX_CTR_EVT_MASK, RFIOS_PEX_CTR_1_EVT_OFF }
};
static iospc_regsel_fld_t rfios_peu_regsel_flds[] = {
	{ rfios_peu_ctr_0_evts, NUM_EVTS(rfios_peu_ctr_0_evts),
	    RFIOS_PEU_CTR_EVT_MASK, RFIOS_PEU_CTR_0_EVT_OFF },
	{ rfios_peu_ctr_1_evts, NUM_EVTS(rfios_peu_ctr_1_evts),
	    RFIOS_PEU_CTR_EVT_MASK, RFIOS_PEU_CTR_1_EVT_OFF }
};

static iospc_regsel_t rfios_imu_regsel = {
	HVIO_RFIOS_PERFREG_IMU_SEL,
	rfios_imu_regsel_flds,
	NUM_FLDS(rfios_imu_regsel_flds)
};

static iospc_regsel_t rfios_atu_regsel = {
	HVIO_RFIOS_PERFREG_ATU_SEL,
	rfios_atu_regsel_flds,
	NUM_FLDS(rfios_atu_regsel_flds)
};

static iospc_regsel_t rfios_npu_regsel = {
	HVIO_RFIOS_PERFREG_NPU_SEL,
	rfios_npu_regsel_flds,
	NUM_FLDS(rfios_npu_regsel_flds)
};

static iospc_regsel_t rfios_pex_regsel = {
	HVIO_RFIOS_PERFREG_PEX_SEL,
	rfios_pex_regsel_flds,
	NUM_FLDS(rfios_pex_regsel_flds)
};

static iospc_regsel_t rfios_peu0_regsel = {
	HVIO_RFIOS_PERFREG_PEU0_SEL,
	rfios_peu_regsel_flds,
	NUM_FLDS(rfios_peu_regsel_flds)
};

static iospc_regsel_t rfios_peu1_regsel = {
	HVIO_RFIOS_PERFREG_PEU1_SEL,
	rfios_peu_regsel_flds,
	NUM_FLDS(rfios_peu_regsel_flds)
};

/* reg off, reg size, field mask */
static iospc_cntr_t rfios_imu_cntrs[] = {
	{ HVIO_RFIOS_PERFREG_IMU_CNT0, FULL64BIT,
		HVIO_RFIOS_PERFREG_IMU_CNT0, 0ULL},
	{ HVIO_RFIOS_PERFREG_IMU_CNT1, FULL64BIT,
		HVIO_RFIOS_PERFREG_IMU_CNT1, 0ULL}
};

static iospc_cntr_t rfios_atu_cntrs[] = {
	{ HVIO_RFIOS_PERFREG_ATU_CNT0, FULL64BIT,
		HVIO_RFIOS_PERFREG_ATU_CNT0, 0ULL},
	{ HVIO_RFIOS_PERFREG_ATU_CNT1, FULL64BIT,
		HVIO_RFIOS_PERFREG_ATU_CNT1, 0ULL}
};

static iospc_cntr_t rfios_npu_cntrs[] = {
	{ HVIO_RFIOS_PERFREG_NPU_CNT0, FULL64BIT,
		HVIO_RFIOS_PERFREG_NPU_CNT0, 0ULL},
	{ HVIO_RFIOS_PERFREG_NPU_CNT1, FULL64BIT,
		HVIO_RFIOS_PERFREG_NPU_CNT1, 0ULL}
};

static iospc_cntr_t rfios_pex_cntrs[] = {
	{ HVIO_RFIOS_PERFREG_PEX_CNT0, FULL64BIT,
		HVIO_RFIOS_PERFREG_PEX_CNT0, 0ULL},
	{ HVIO_RFIOS_PERFREG_PEX_CNT1, FULL64BIT,
		HVIO_RFIOS_PERFREG_PEX_CNT1, 0ULL}
};

static iospc_cntr_t rfios_peu0_cntrs[] = {
	{ HVIO_RFIOS_PERFREG_PEU0_CNT0, FULL64BIT,
		HVIO_RFIOS_PERFREG_PEU0_CNT0, 0ULL},
	{ HVIO_RFIOS_PERFREG_PEU0_CNT1, FULL64BIT,
		HVIO_RFIOS_PERFREG_PEU0_CNT1, 0ULL}
};

static iospc_cntr_t rfios_peu1_cntrs[] = {
	{ HVIO_RFIOS_PERFREG_PEU1_CNT0, FULL64BIT,
		HVIO_RFIOS_PERFREG_PEU0_CNT0, 0ULL},
	{ HVIO_RFIOS_PERFREG_PEU1_CNT1, FULL64BIT,
		HVIO_RFIOS_PERFREG_PEU0_CNT1, 0ULL}
};

static iospc_grp_t rfios_imu_grp = {
	"imu",
	&rfios_imu_regsel,
	rfios_imu_cntrs,
	NUM_CTRS(rfios_imu_cntrs),
	rfios_access_init,
	rfios_access_hv,
	rfios_access_fini,
	NULL		/* Name kstats pointer, filled in at runtime. */
};

static iospc_grp_t rfios_atu_grp = {
	"atu",
	&rfios_atu_regsel,
	rfios_atu_cntrs,
	NUM_CTRS(rfios_atu_cntrs),
	rfios_access_init,
	rfios_access_hv,
	rfios_access_fini,
	NULL		/* Name kstats pointer, filled in at runtime. */
};

static iospc_grp_t rfios_npu_grp = {
	"npu",
	&rfios_npu_regsel,
	rfios_npu_cntrs,
	NUM_CTRS(rfios_npu_cntrs),
	rfios_access_init,
	rfios_access_hv,
	rfios_access_fini,
	NULL		/* Name kstats pointer, filled in at runtime. */
};

static iospc_grp_t rfios_pex_grp = {
	"pex",
	&rfios_pex_regsel,
	rfios_pex_cntrs,
	NUM_CTRS(rfios_pex_cntrs),
	rfios_access_init,
	rfios_access_hv,
	rfios_access_fini,
	NULL		/* Name kstats pointer, filled in at runtime. */
};

static iospc_grp_t rfios_peuzero_grp = {
	"peuzero",
	&rfios_peu0_regsel,
	rfios_peu0_cntrs,
	NUM_CTRS(rfios_peu0_cntrs),
	rfios_access_init,
	rfios_access_hv,
	rfios_access_fini,
	NULL		/* Name kstats pointer, filled in at runtime. */
};
static iospc_grp_t rfios_peuone_grp = {
	"peuone",
	&rfios_peu1_regsel,
	rfios_peu1_cntrs,
	NUM_CTRS(rfios_peu1_cntrs),
	rfios_access_init,
	rfios_access_hv,
	rfios_access_fini,
	NULL		/* Name kstats pointer, filled in at runtime. */
};

iospc_grp_t *rfios_leaf_grps[] = {
	&rfios_imu_grp,
	&rfios_atu_grp,
	&rfios_npu_grp,
	&rfios_pex_grp,
	&rfios_peuzero_grp,
	&rfios_peuone_grp,
	NULL
};