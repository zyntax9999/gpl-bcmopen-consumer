/*
 * <:copyright-BRCM:2013:DUAL/GPL:standard
 * 
 *    Copyright (c) 2013 Broadcom 
 *    All Rights Reserved
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as published by
 * the Free Software Foundation (the "GPL").
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * 
 * A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
 * writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 * 
 * :> 
 */


#ifndef _RDD_STUBS_H_
#define _RDD_STUBS_H_

#include "rdd_defs.h"
#include "bdmf_interface.h"

/* Temporary stuff to make rdpa_ingress_class.c compile */

#define BL_LILAC_RDD_CPU_BRIDGE_PORT  12

typedef enum
{
    RDD_SUBNET_FLOW_CACHE = 0,
    RDD_SUBNET_BRIDGE,
    RDD_SUBNET_BRIDGE_IPTV,
    RDD_SUBNET_LAN,
} rdd_subnet_id_t;

typedef struct
{
    uint16_t vid;
    rdd_vport_vector_t isolation_mode_port_vector;
    rdd_vport_vector_t aggregation_mode_port_vector;
    uint16_t aggregation_vid_index;
} rdd_lan_vid_cfg_t;

typedef enum
{
    RDD_IC_LKP_MODE_IH = 0,
    RDD_IC_LKP_MODE_OPTIMIZED,
    RDD_IC_LKP_MODE_SHORT,
    RDD_IC_LKP_MODE_LONG,
} rdd_ic_lkp_mode_t;

static inline int rdd_mac_entry_delete(bdmf_mac_t *mac_addr, bdmf_boolean is_dynamic)
{
    RDD_BTRACE("mac_addr = %p, is_dynamic = %d\n", mac_addr, is_dynamic);
    RDD_TRACE("This is stub function, consider to implement\n");
    return 0;
}

static inline int rdd_sa_mac_lkp_cfg(rdd_vport_id_t vport, bdmf_boolean enable)
{
    RDD_BTRACE("vport = %d, enable = %d\n", vport, enable);
    RDD_TRACE("This is stub function, consider to implement\n");
    return 0;
}

static inline int rdd_unknown_sa_mac_cmd_cfg(rdd_vport_id_t vport, rdpa_forward_action slf_cmd)
{
    RDD_BTRACE("vport = %d, slf_cmd = %d\n", vport, slf_cmd);
    RDD_TRACE("This is stub function, consider to implement\n");
    return 0;
}

static inline int rdd_da_mac_lkp_cfg(rdd_vport_id_t vport, bdmf_boolean enable)
{
    RDD_BTRACE("vport = %d, enable = %d\n", vport, enable);
    RDD_TRACE("This is stub function, consider to implement\n");
    return 0;
}

static inline int rdd_unknown_da_mac_cmd_cfg(rdd_vport_id_t vport, rdpa_forward_action dlf_cmd)
{
    RDD_BTRACE("vport = %d, dlf_cmd = %d\n", vport, dlf_cmd);
    RDD_TRACE("This is stub function, consider to implement\n");
    return 0;
}

static inline int rdd_lan_vid_entry_cfg(uint32_t entry_idx, rdd_lan_vid_cfg_t *cfg)
{
    RDD_BTRACE("entry_idx = %d, cfg = %p\n", entry_idx, cfg);
    RDD_TRACE("This is stub function, consider to implement\n");
    return 0;
}

static inline int rdd_us_vlan_aggregation_config(rdd_vport_id_t vport, bdmf_boolean enable)
{
    RDD_BTRACE("vport = %d, enable %d\n", vport, enable);
    RDD_TRACE("This is stub function, consider to implement\n");
    return 0;
}

#if !defined(BCM63158)
static inline int rdd_broadcom_switch_ports_mapping_table_config(rdd_vport_id_t vport,
    uint8_t broadcom_switch_port)
{
    RDD_BTRACE("vport = %d, broadcom_switch_port = %d\n", vport, broadcom_switch_port);
    RDD_TRACE("This is stub function, consider to implement\n");
    return 0;
}
#endif

static inline int rdd_wan_channel_rate_limiter_cfg(rdd_wan_channel_id_t channel_id, bdmf_boolean rate_limiter_enabled,
    int prio)
{
    RDD_BTRACE("channel_id = %d, rate_limiter_enabled = %d, prio = %d\n", channel_id, rate_limiter_enabled, prio);
    RDD_TRACE("This is stub function, consider to implement\n");
    return 0;
}


static inline void rdd_us_overall_rate_limiter_cfg(rdd_rate_limit_params_t *budget)
{
    RDD_BTRACE("budget = %p\n", budget);
    RDD_TRACE("This is stub function, consider to implement\n");
}

static inline int rdd_wan_tx_queue_svcq_scheduler_set(rdd_wan_channel_id_t channel_id,
    int rate_controller_id, int queue_id, bdmf_boolean enable)
{
    RDD_BTRACE("channel_id = %d, rc_id = %d, queue_id = %d, enable = %d\n", channel_id, rate_controller_id, queue_id, enable);
    RDD_TRACE("This is stub function, consider to implement\n");
    return 0;
}

#endif

