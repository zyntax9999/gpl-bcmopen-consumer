/*
    <:copyright-BRCM:2015:DUAL/GPL:standard
    
       Copyright (c) 2015 Broadcom 
       All Rights Reserved
    
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2, as published by
    the Free Software Foundation (the "GPL").
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    
    A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
    writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
    
    :>
*/
#ifndef _RDP_DRV_NATC_H_
#define _RDP_DRV_NATC_H_

#include "rdp_common.h"
#include "rdp_drv_natc_defs.h"
#include "xrdp_drv_drivers_common_ag.h"
#include "xrdp_drv_natc_ag.h"
#include "xrdp_drv_natc_indir_ag.h"
#include "xrdp_drv_natc_cfg_ag.h"
#include "xrdp_drv_natc_ctrs_ag.h"
#include "xrdp_drv_natc_eng_ag.h"
#include "xrdp_drv_natc_ddr_cfg_ag.h"
#include "xrdp_drv_natc_key_mask_ag.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define NATC_DEFAULT_BIN_SIZE   (ddr_8_bins_per_bucket)

typedef struct natc_tbl_virt_addr
{
    void *key;
    void *res;
} natc_tbl_virt_addr_t;

typedef struct natc_tbl_phys_addr
{
    bdmf_phys_addr_t key;
    bdmf_phys_addr_t res;
} natc_tbl_phys_addr_t;

typedef struct natc_tbl_config
{
    uint8_t         tbl_idx;
    uint32_t        mask;
    uint32_t        key_len;
    uint32_t        res_len;
    uint32_t        key_tbl_size;
    uint32_t        res_tbl_size;
    uint32_t        tbl_entry_num;
    natc_tbl_virt_addr_t vir_addr;
    natc_tbl_phys_addr_t phy_addr;
    uint32_t        count;
} natc_tbl_config_t;

typedef struct natc_config
{
    uint32_t tbl_num;
    natc_ctrl_status   ctrl_status;
    tbl_control_t      tbl_cntrl[NATC_MAX_TABLES_NUM];
    natc_tbl_config_t  tbl_cfg[NATC_MAX_TABLES_NUM];
} natc_config_t;

int drv_natc_entry_counters_get(uint8_t tbl_idx, uint32_t entry_index, uint64_t *hit_count,
    uint64_t *byte_count);
int drv_natc_key_entry_add(uint8_t tbl_idx, uint32_t entry_idx, uint8_t *key);
int drv_natc_key_entry_get(uint8_t tbl_idx, uint32_t entry_index, bdmf_boolean *valid, uint8_t *key);
int drv_natc_result_entry_add(uint8_t tbl_idx, uint32_t entry_idx, uint8_t *result);
int drv_natc_result_entry_modify(uint8_t tbl_idx, uint32_t entry_idx, uint8_t *result);
int drv_natc_result_entry_get(uint8_t tbl_idx, uint32_t entry_index, uint8_t *res);
int drv_natc_key_result_entry_var_size_ctx_add(uint8_t tbl_idx, uint8_t *hash_key, uint8_t *key, uint8_t *result, uint32_t *hash_idx);
int drv_natc_key_result_entry_add(uint8_t tbl_idx, uint8_t *key, uint8_t *result, uint32_t *hash_idx);
int drv_natc_key_idx_get(uint8_t tbl_idx, uint8_t *keyword, uint32_t *hash_idx, uint32_t *entry_idx);
int drv_natc_entry_delete(uint8_t tbl_idx, uint32_t entry_index,  uint8_t lock_req, uint8_t count_delete);
int drv_natc_tbl_ctrl_set(uint8_t tbl_idx, tbl_control_t *tbl_ctrl);
int drv_natc_tbl_ctrl_get(uint8_t tbl_idx, tbl_control_t *tbl_ctrl);
int drv_natc_init(natc_config_t *cfg);
void drv_natc_cfg_build_tables(natc_config_t *cfg, natc_ddr_cfg_natc_ddr_size* ddr_size, natc_ddr_cfg_total_len* total_len, int table_base_size,
    void* table_base_addr_virt, bdmf_phys_addr_t table_base_addr_phys);
int drv_natc_set_key_mask(uint16_t mask);

ddr_nat_table_size_t _natc_tbl_ddr_size_enum(uint8_t tbl_idx, natc_ddr_cfg_natc_ddr_size *ddr_size);
total_length_t _natc_tbl_entry_size_enum(uint8_t tbl_idx, natc_ddr_cfg_total_len *total_len);

#ifdef USE_BDMF_SHELL
void drv_natc_cli_init(bdmfmon_handle_t driver_dir);
void drv_natc_cli_exit(bdmfmon_handle_t driver_dir);
#endif


#ifdef __cplusplus
}
#endif


#endif
