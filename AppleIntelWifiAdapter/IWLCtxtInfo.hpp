//
//  IWLCtxtInfo.hpp
//  AppleIntelWifiAdapter
//
//  Created by 钟先耀 on 2020/2/9.
//  Copyright © 2020 IntelWifi for MacOS authors. All rights reserved.
//

#ifndef APPLEINTELWIFIADAPTER_IWLCTXTINFO_HPP_
#define APPLEINTELWIFIADAPTER_IWLCTXTINFO_HPP_

#include "IWLTransport.hpp"
#include "IWLInternal.hpp"

/* maximmum number of DRAM map entries supported by FW */
#define IWL_MAX_DRAM_ENTRY    64
#define CSR_CTXT_INFO_BA    0x40

/**
 * enum iwl_context_info_flags - Context information control flags
 * @IWL_CTXT_INFO_AUTO_FUNC_INIT: If set, FW will not wait before interrupting
 *    the init done for driver command that configures several system modes
 * @IWL_CTXT_INFO_EARLY_DEBUG: enable early debug
 * @IWL_CTXT_INFO_ENABLE_CDMP: enable core dump
 * @IWL_CTXT_INFO_RB_CB_SIZE: mask of the RBD Cyclic Buffer Size
 *    exponent, the actual size is 2**value, valid sizes are 8-2048.
 *    The value is four bits long. Maximum valid exponent is 12
 * @IWL_CTXT_INFO_TFD_FORMAT_LONG: use long TFD Format (the
 *    default is short format - not supported by the driver)
 * @IWL_CTXT_INFO_RB_SIZE: RB size mask
 *    (values are IWL_CTXT_INFO_RB_SIZE_*K)
 * @IWL_CTXT_INFO_RB_SIZE_1K: Value for 1K RB size
 * @IWL_CTXT_INFO_RB_SIZE_2K: Value for 2K RB size
 * @IWL_CTXT_INFO_RB_SIZE_4K: Value for 4K RB size
 * @IWL_CTXT_INFO_RB_SIZE_8K: Value for 8K RB size
 * @IWL_CTXT_INFO_RB_SIZE_12K: Value for 12K RB size
 * @IWL_CTXT_INFO_RB_SIZE_16K: Value for 16K RB size
 * @IWL_CTXT_INFO_RB_SIZE_20K: Value for 20K RB size
 * @IWL_CTXT_INFO_RB_SIZE_24K: Value for 24K RB size
 * @IWL_CTXT_INFO_RB_SIZE_28K: Value for 28K RB size
 * @IWL_CTXT_INFO_RB_SIZE_32K: Value for 32K RB size
 */
enum iwl_context_info_flags {
    IWL_CTXT_INFO_AUTO_FUNC_INIT    = 0x0001,
    IWL_CTXT_INFO_EARLY_DEBUG    = 0x0002,
    IWL_CTXT_INFO_ENABLE_CDMP    = 0x0004,
    IWL_CTXT_INFO_RB_CB_SIZE    = 0x00f0,
    IWL_CTXT_INFO_TFD_FORMAT_LONG    = 0x0100,
    IWL_CTXT_INFO_RB_SIZE        = 0x1e00,
    IWL_CTXT_INFO_RB_SIZE_1K    = 0x1,
    IWL_CTXT_INFO_RB_SIZE_2K    = 0x2,
    IWL_CTXT_INFO_RB_SIZE_4K    = 0x4,
    IWL_CTXT_INFO_RB_SIZE_8K    = 0x8,
    IWL_CTXT_INFO_RB_SIZE_12K    = 0x9,
    IWL_CTXT_INFO_RB_SIZE_16K    = 0xa,
    IWL_CTXT_INFO_RB_SIZE_20K    = 0xb,
    IWL_CTXT_INFO_RB_SIZE_24K    = 0xc,
    IWL_CTXT_INFO_RB_SIZE_28K    = 0xd,
    IWL_CTXT_INFO_RB_SIZE_32K    = 0xe,
};

/*
 * struct iwl_context_info_version - version structure
 * @mac_id: SKU and revision id
 * @version: context information version id
 * @size: the size of the context information in DWs
 */
struct iwl_context_info_version {
    __le16 mac_id;
    __le16 version;
    __le16 size;
    __le16 reserved;
} __packed;

/*
 * struct iwl_context_info_control - version structure
 * @control_flags: context information flags see &enum iwl_context_info_flags
 */
struct iwl_context_info_control {
    __le32 control_flags;
    __le32 reserved;
} __packed;

/*
 * struct iwl_context_info_dram - images DRAM map
 * each entry in the map represents a DRAM chunk of up to 32 KB
 * @umac_img: UMAC image DRAM map
 * @lmac_img: LMAC image DRAM map
 * @virtual_img: paged image DRAM map
 */
struct iwl_context_info_dram {
    __le64 umac_img[IWL_MAX_DRAM_ENTRY];
    __le64 lmac_img[IWL_MAX_DRAM_ENTRY];
    __le64 virtual_img[IWL_MAX_DRAM_ENTRY];
} __packed;

/*
 * struct iwl_context_info_rbd_cfg - RBDs configuration
 * @free_rbd_addr: default queue free RB CB base address
 * @used_rbd_addr: default queue used RB CB base address
 * @status_wr_ptr: default queue used RB status write pointer
 */
struct iwl_context_info_rbd_cfg {
    __le64 free_rbd_addr;
    __le64 used_rbd_addr;
    __le64 status_wr_ptr;
} __packed;

/*
 * struct iwl_context_info_hcmd_cfg  - command queue configuration
 * @cmd_queue_addr: address of command queue
 * @cmd_queue_size: number of entries
 */
struct iwl_context_info_hcmd_cfg {
    __le64 cmd_queue_addr;
    u8 cmd_queue_size;
    u8 reserved[7];
} __packed;

/*
 * struct iwl_context_info_dump_cfg - Core Dump configuration
 * @core_dump_addr: core dump (debug DRAM address) start address
 * @core_dump_size: size, in DWs
 */
struct iwl_context_info_dump_cfg {
    __le64 core_dump_addr;
    __le32 core_dump_size;
    __le32 reserved;
} __packed;

/*
 * struct iwl_context_info_pnvm_cfg - platform NVM data configuration
 * @platform_nvm_addr: Platform NVM data start address
 * @platform_nvm_size: size in DWs
 */
struct iwl_context_info_pnvm_cfg {
    __le64 platform_nvm_addr;
    __le32 platform_nvm_size;
    __le32 reserved;
} __packed;

/*
 * struct iwl_context_info_early_dbg_cfg - early debug configuration for
 *    dumping DRAM addresses
 * @early_debug_addr: early debug start address
 * @early_debug_size: size in DWs
 */
struct iwl_context_info_early_dbg_cfg {
    __le64 early_debug_addr;
    __le32 early_debug_size;
    __le32 reserved;
} __packed;

/*
 * struct iwl_context_info - device INIT configuration
 * @version: version information of context info and HW
 * @control: control flags of FH configurations
 * @rbd_cfg: default RX queue configuration
 * @hcmd_cfg: command queue configuration
 * @dump_cfg: core dump data
 * @edbg_cfg: early debug configuration
 * @pnvm_cfg: platform nvm configuration
 * @dram: firmware image addresses in DRAM
 */
struct iwl_context_info {
    struct iwl_context_info_version version;
    struct iwl_context_info_control control;
    __le64 reserved0;
    struct iwl_context_info_rbd_cfg rbd_cfg;
    struct iwl_context_info_hcmd_cfg hcmd_cfg;
    __le32 reserved1[4];
    struct iwl_context_info_dump_cfg dump_cfg;
    struct iwl_context_info_early_dbg_cfg edbg_cfg;
    struct iwl_context_info_pnvm_cfg pnvm_cfg;
    __le32 reserved2[16];
    struct iwl_context_info_dram dram;
    __le32 reserved3[16];
} __packed;

#define CSR_CTXT_INFO_BOOT_CTRL         0x0
#define CSR_CTXT_INFO_ADDR              0x118
#define CSR_IML_DATA_ADDR               0x120
#define CSR_IML_SIZE_ADDR               0x128
#define CSR_IML_RESP_ADDR               0x12c

/* Set bit for enabling automatic function boot */
#define CSR_AUTO_FUNC_BOOT_ENA          BIT(1)
/* Set bit for initiating function boot */
#define CSR_AUTO_FUNC_INIT              BIT(7)

/**
 * enum iwl_prph_scratch_mtr_format - tfd size configuration
 * @IWL_PRPH_MTR_FORMAT_16B: 16 bit tfd
 * @IWL_PRPH_MTR_FORMAT_32B: 32 bit tfd
 * @IWL_PRPH_MTR_FORMAT_64B: 64 bit tfd
 * @IWL_PRPH_MTR_FORMAT_256B: 256 bit tfd
 */
enum iwl_prph_scratch_mtr_format {
    IWL_PRPH_MTR_FORMAT_16B = 0x0,
    IWL_PRPH_MTR_FORMAT_32B = 0x40000,
    IWL_PRPH_MTR_FORMAT_64B = 0x80000,
    IWL_PRPH_MTR_FORMAT_256B = 0xC0000,
};

/**
 * enum iwl_prph_scratch_flags - PRPH scratch control flags
 * @IWL_PRPH_SCRATCH_EARLY_DEBUG_EN: enable early debug conf
 * @IWL_PRPH_SCRATCH_EDBG_DEST_DRAM: use DRAM, with size allocated
 *    in hwm config.
 * @IWL_PRPH_SCRATCH_EDBG_DEST_INTERNAL: use buffer on SRAM
 * @IWL_PRPH_SCRATCH_EDBG_DEST_ST_ARBITER: use st arbiter, mainly for
 *    multicomm.
 * @IWL_PRPH_SCRATCH_EDBG_DEST_TB22DTF: route debug data to SoC HW
 * @IWL_PRPH_SCTATCH_RB_SIZE_4K: Use 4K RB size (the default is 2K)
 * @IWL_PRPH_SCRATCH_MTR_MODE: format used for completion - 0: for
 *    completion descriptor, 1 for responses (legacy)
 * @IWL_PRPH_SCRATCH_MTR_FORMAT: a mask for the size of the tfd.
 *    There are 4 optional values: 0: 16 bit, 1: 32 bit, 2: 64 bit,
 *    3: 256 bit.
 */
enum iwl_prph_scratch_flags {
    IWL_PRPH_SCRATCH_EARLY_DEBUG_EN        = BIT(4),
    IWL_PRPH_SCRATCH_EDBG_DEST_DRAM        = BIT(8),
    IWL_PRPH_SCRATCH_EDBG_DEST_INTERNAL    = BIT(9),
    IWL_PRPH_SCRATCH_EDBG_DEST_ST_ARBITER    = BIT(10),
    IWL_PRPH_SCRATCH_EDBG_DEST_TB22DTF    = BIT(11),
    IWL_PRPH_SCRATCH_RB_SIZE_4K        = BIT(16),
    IWL_PRPH_SCRATCH_MTR_MODE        = BIT(17),
    IWL_PRPH_SCRATCH_MTR_FORMAT        = BIT(18) | BIT(19),
};

/*
 * struct iwl_prph_scratch_version - version structure
 * @mac_id: SKU and revision id
 * @version: prph scratch information version id
 * @size: the size of the context information in DWs
 * @reserved: reserved
 */
struct iwl_prph_scratch_version {
    __le16 mac_id;
    __le16 version;
    __le16 size;
    __le16 reserved;
} __packed; /* PERIPH_SCRATCH_VERSION_S */

/*
 * struct iwl_prph_scratch_control - control structure
 * @control_flags: context information flags see &enum iwl_prph_scratch_flags
 * @reserved: reserved
 */
struct iwl_prph_scratch_control {
    __le32 control_flags;
    __le32 reserved;
} __packed; /* PERIPH_SCRATCH_CONTROL_S */

/*
 * struct iwl_prph_scratch_ror_cfg - ror config
 * @ror_base_addr: ror start address
 * @ror_size: ror size in DWs
 * @reserved: reserved
 */
struct iwl_prph_scratch_ror_cfg {
    __le64 ror_base_addr;
    __le32 ror_size;
    __le32 reserved;
} __packed; /* PERIPH_SCRATCH_ROR_CFG_S */

/*
 * struct iwl_prph_scratch_hwm_cfg - hwm config
 * @hwm_base_addr: hwm start address
 * @hwm_size: hwm size in DWs
 * @reserved: reserved
 */
struct iwl_prph_scratch_hwm_cfg {
    __le64 hwm_base_addr;
    __le32 hwm_size;
    __le32 reserved;
} __packed; /* PERIPH_SCRATCH_HWM_CFG_S */

/*
 * struct iwl_prph_scratch_rbd_cfg - RBDs configuration
 * @free_rbd_addr: default queue free RB CB base address
 * @reserved: reserved
 */
struct iwl_prph_scratch_rbd_cfg {
    __le64 free_rbd_addr;
    __le32 reserved;
} __packed; /* PERIPH_SCRATCH_RBD_CFG_S */

/*
 * struct iwl_prph_scratch_ctrl_cfg - prph scratch ctrl and config
 * @version: version information of context info and HW
 * @control: control flags of FH configurations
 * @ror_cfg: ror configuration
 * @hwm_cfg: hwm configuration
 * @rbd_cfg: default RX queue configuration
 */
struct iwl_prph_scratch_ctrl_cfg {
    struct iwl_prph_scratch_version version;
    struct iwl_prph_scratch_control control;
    struct iwl_prph_scratch_ror_cfg ror_cfg;
    struct iwl_prph_scratch_hwm_cfg hwm_cfg;
    struct iwl_prph_scratch_rbd_cfg rbd_cfg;
} __packed; /* PERIPH_SCRATCH_CTRL_CFG_S */

/*
 * struct iwl_prph_scratch - peripheral scratch mapping
 * @ctrl_cfg: control and configuration of prph scratch
 * @dram: firmware images addresses in DRAM
 * @reserved: reserved
 */
struct iwl_prph_scratch {
    struct iwl_prph_scratch_ctrl_cfg ctrl_cfg;
    __le32 reserved[16];
    struct iwl_context_info_dram dram;
} __packed; /* PERIPH_SCRATCH_S */

/*
 * struct iwl_prph_info - peripheral information
 * @boot_stage_mirror: reflects the value in the Boot Stage CSR register
 * @ipc_status_mirror: reflects the value in the IPC Status CSR register
 * @sleep_notif: indicates the peripheral sleep status
 * @reserved: reserved
 */
struct iwl_prph_info {
    __le32 boot_stage_mirror;
    __le32 ipc_status_mirror;
    __le32 sleep_notif;
    __le32 reserved;
} __packed; /* PERIPH_INFO_S */

/*
 * struct iwl_context_info_gen3 - device INIT configuration
 * @version: version of the context information
 * @size: size of context information in DWs
 * @config: context in which the peripheral would execute - a subset of
 *    capability csr register published by the peripheral
 * @prph_info_base_addr: the peripheral information structure start address
 * @cr_head_idx_arr_base_addr: the completion ring head index array
 *    start address
 * @tr_tail_idx_arr_base_addr: the transfer ring tail index array
 *    start address
 * @cr_tail_idx_arr_base_addr: the completion ring tail index array
 *    start address
 * @tr_head_idx_arr_base_addr: the transfer ring head index array
 *    start address
 * @cr_idx_arr_size: number of entries in the completion ring index array
 * @tr_idx_arr_size: number of entries in the transfer ring index array
 * @mtr_base_addr: the message transfer ring start address
 * @mcr_base_addr: the message completion ring start address
 * @mtr_size: number of entries which the message transfer ring can hold
 * @mcr_size: number of entries which the message completion ring can hold
 * @mtr_doorbell_vec: the doorbell vector associated with the message
 *    transfer ring
 * @mcr_doorbell_vec: the doorbell vector associated with the message
 *    completion ring
 * @mtr_msi_vec: the MSI which shall be generated by the peripheral after
 *    completing a transfer descriptor in the message transfer ring
 * @mcr_msi_vec: the MSI which shall be generated by the peripheral after
 *    completing a completion descriptor in the message completion ring
 * @mtr_opt_header_size: the size of the optional header in the transfer
 *    descriptor associated with the message transfer ring in DWs
 * @mtr_opt_footer_size: the size of the optional footer in the transfer
 *    descriptor associated with the message transfer ring in DWs
 * @mcr_opt_header_size: the size of the optional header in the completion
 *    descriptor associated with the message completion ring in DWs
 * @mcr_opt_footer_size: the size of the optional footer in the completion
 *    descriptor associated with the message completion ring in DWs
 * @msg_rings_ctrl_flags: message rings control flags
 * @prph_info_msi_vec: the MSI which shall be generated by the peripheral
 *    after updating the Peripheral Information structure
 * @prph_scratch_base_addr: the peripheral scratch structure start address
 * @prph_scratch_size: the size of the peripheral scratch structure in DWs
 * @reserved: reserved
 */
struct iwl_context_info_gen3 {
    __le16 version;
    __le16 size;
    __le32 config;
    __le64 prph_info_base_addr;
    __le64 cr_head_idx_arr_base_addr;
    __le64 tr_tail_idx_arr_base_addr;
    __le64 cr_tail_idx_arr_base_addr;
    __le64 tr_head_idx_arr_base_addr;
    __le16 cr_idx_arr_size;
    __le16 tr_idx_arr_size;
    __le64 mtr_base_addr;
    __le64 mcr_base_addr;
    __le16 mtr_size;
    __le16 mcr_size;
    __le16 mtr_doorbell_vec;
    __le16 mcr_doorbell_vec;
    __le16 mtr_msi_vec;
    __le16 mcr_msi_vec;
    u8 mtr_opt_header_size;
    u8 mtr_opt_footer_size;
    u8 mcr_opt_header_size;
    u8 mcr_opt_footer_size;
    __le16 msg_rings_ctrl_flags;
    __le16 prph_info_msi_vec;
    __le64 prph_scratch_base_addr;
    __le32 prph_scratch_size;
    __le32 reserved;
} __packed; /* IPC_CONTEXT_INFO_S */

#endif  // APPLEINTELWIFIADAPTER_IWLCTXTINFO_HPP_
