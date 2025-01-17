/*
   Copyright (c) 2015 Broadcom
   All Rights Reserved

    <:label-BRCM:2015:DUAL/GPL:standard
    
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

#include "ru.h"

#if RU_INCLUDE_FIELD_DB
/******************************************************************************
 * Field: RNR_MEM_HIGH_DATA_MEM
 ******************************************************************************/
const ru_field_rec RNR_MEM_HIGH_DATA_MEM_FIELD =
{
    "DATA_MEM",
#if RU_INCLUDE_DESC
    "data_memory",
    "data memory",
#endif
    RNR_MEM_HIGH_DATA_MEM_FIELD_MASK,
    0,
    RNR_MEM_HIGH_DATA_MEM_FIELD_WIDTH,
    RNR_MEM_HIGH_DATA_MEM_FIELD_SHIFT,
#if RU_INCLUDE_ACCESS
    ru_access_rw
#endif
};

/******************************************************************************
 * Field: RNR_MEM_LOW_DATA_MEM
 ******************************************************************************/
const ru_field_rec RNR_MEM_LOW_DATA_MEM_FIELD =
{
    "DATA_MEM",
#if RU_INCLUDE_DESC
    "data_memory",
    "data memory",
#endif
    RNR_MEM_LOW_DATA_MEM_FIELD_MASK,
    0,
    RNR_MEM_LOW_DATA_MEM_FIELD_WIDTH,
    RNR_MEM_LOW_DATA_MEM_FIELD_SHIFT,
#if RU_INCLUDE_ACCESS
    ru_access_rw
#endif
};

#endif /* RU_INCLUDE_FIELD_DB */

/******************************************************************************
 * Register: RNR_MEM_HIGH
 ******************************************************************************/
#if RU_INCLUDE_FIELD_DB
static const ru_field_rec *RNR_MEM_HIGH_FIELDS[] =
{
    &RNR_MEM_HIGH_DATA_MEM_FIELD,
};

#endif /* RU_INCLUDE_FIELD_DB */

const ru_reg_rec RNR_MEM_HIGH_REG = 
{
    "HIGH",
#if RU_INCLUDE_DESC
    "DATA_MEMORY_ENTRY_HIGH Register",
    "Data memory entry",
#endif
    RNR_MEM_HIGH_REG_OFFSET,
    RNR_MEM_HIGH_REG_RAM_CNT,
    8,
    308,
#if RU_INCLUDE_ACCESS
    ru_access_rw,
#endif
#if RU_INCLUDE_FIELD_DB
    1,
    RNR_MEM_HIGH_FIELDS
#endif /* RU_INCLUDE_FIELD_DB */
};

/******************************************************************************
 * Register: RNR_MEM_LOW
 ******************************************************************************/
#if RU_INCLUDE_FIELD_DB
static const ru_field_rec *RNR_MEM_LOW_FIELDS[] =
{
    &RNR_MEM_LOW_DATA_MEM_FIELD,
};

#endif /* RU_INCLUDE_FIELD_DB */

const ru_reg_rec RNR_MEM_LOW_REG = 
{
    "LOW",
#if RU_INCLUDE_DESC
    "DATA_MEMORY_ENTRY_LOW Register",
    "Data memory entry",
#endif
    RNR_MEM_LOW_REG_OFFSET,
    RNR_MEM_LOW_REG_RAM_CNT,
    8,
    309,
#if RU_INCLUDE_ACCESS
    ru_access_rw,
#endif
#if RU_INCLUDE_FIELD_DB
    1,
    RNR_MEM_LOW_FIELDS
#endif /* RU_INCLUDE_FIELD_DB */
};

/******************************************************************************
 * Block: RNR_MEM
 ******************************************************************************/
static const ru_reg_rec *RNR_MEM_REGS[] =
{
    &RNR_MEM_HIGH_REG,
    &RNR_MEM_LOW_REG,
};

unsigned long RNR_MEM_ADDRS[] =
{
    0x82c00000,
    0x82c20000,
    0x82c40000,
};

const ru_block_rec RNR_MEM_BLOCK = 
{
    "RNR_MEM",
    RNR_MEM_ADDRS,
    3,
    2,
    RNR_MEM_REGS
};

/* End of file XRDP_RNR_MEM.c */
