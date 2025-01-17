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
 * Field: NATC_CFG_DDR_KEY_BASE_ADDRESS_LOWER_BAR
 ******************************************************************************/
const ru_field_rec NATC_CFG_DDR_KEY_BASE_ADDRESS_LOWER_BAR_FIELD =
{
    "BAR",
#if RU_INCLUDE_DESC
    "",
    "",
#endif
    NATC_CFG_DDR_KEY_BASE_ADDRESS_LOWER_BAR_FIELD_MASK,
    0,
    NATC_CFG_DDR_KEY_BASE_ADDRESS_LOWER_BAR_FIELD_WIDTH,
    NATC_CFG_DDR_KEY_BASE_ADDRESS_LOWER_BAR_FIELD_SHIFT,
#if RU_INCLUDE_ACCESS
    ru_access_rw
#endif
};

/******************************************************************************
 * Field: NATC_CFG_DDR_KEY_BASE_ADDRESS_LOWER_ZEROS
 ******************************************************************************/
const ru_field_rec NATC_CFG_DDR_KEY_BASE_ADDRESS_LOWER_ZEROS_FIELD =
{
    "ZEROS",
#if RU_INCLUDE_DESC
    "",
    "",
#endif
    NATC_CFG_DDR_KEY_BASE_ADDRESS_LOWER_ZEROS_FIELD_MASK,
    0,
    NATC_CFG_DDR_KEY_BASE_ADDRESS_LOWER_ZEROS_FIELD_WIDTH,
    NATC_CFG_DDR_KEY_BASE_ADDRESS_LOWER_ZEROS_FIELD_SHIFT,
#if RU_INCLUDE_ACCESS
    ru_access_rw
#endif
};

/******************************************************************************
 * Field: NATC_CFG_DDR_KEY_BASE_ADDRESS_UPPER_ZEROS
 ******************************************************************************/
const ru_field_rec NATC_CFG_DDR_KEY_BASE_ADDRESS_UPPER_ZEROS_FIELD =
{
    "ZEROS",
#if RU_INCLUDE_DESC
    "",
    "",
#endif
    NATC_CFG_DDR_KEY_BASE_ADDRESS_UPPER_ZEROS_FIELD_MASK,
    0,
    NATC_CFG_DDR_KEY_BASE_ADDRESS_UPPER_ZEROS_FIELD_WIDTH,
    NATC_CFG_DDR_KEY_BASE_ADDRESS_UPPER_ZEROS_FIELD_SHIFT,
#if RU_INCLUDE_ACCESS
    ru_access_rw
#endif
};

/******************************************************************************
 * Field: NATC_CFG_DDR_KEY_BASE_ADDRESS_UPPER_BAR
 ******************************************************************************/
const ru_field_rec NATC_CFG_DDR_KEY_BASE_ADDRESS_UPPER_BAR_FIELD =
{
    "BAR",
#if RU_INCLUDE_DESC
    "",
    "",
#endif
    NATC_CFG_DDR_KEY_BASE_ADDRESS_UPPER_BAR_FIELD_MASK,
    0,
    NATC_CFG_DDR_KEY_BASE_ADDRESS_UPPER_BAR_FIELD_WIDTH,
    NATC_CFG_DDR_KEY_BASE_ADDRESS_UPPER_BAR_FIELD_SHIFT,
#if RU_INCLUDE_ACCESS
    ru_access_rw
#endif
};

/******************************************************************************
 * Field: NATC_CFG_DDR_RESULT_BASE_ADDRESS_LOWER_BAR
 ******************************************************************************/
const ru_field_rec NATC_CFG_DDR_RESULT_BASE_ADDRESS_LOWER_BAR_FIELD =
{
    "BAR",
#if RU_INCLUDE_DESC
    "",
    "",
#endif
    NATC_CFG_DDR_RESULT_BASE_ADDRESS_LOWER_BAR_FIELD_MASK,
    0,
    NATC_CFG_DDR_RESULT_BASE_ADDRESS_LOWER_BAR_FIELD_WIDTH,
    NATC_CFG_DDR_RESULT_BASE_ADDRESS_LOWER_BAR_FIELD_SHIFT,
#if RU_INCLUDE_ACCESS
    ru_access_rw
#endif
};

/******************************************************************************
 * Field: NATC_CFG_DDR_RESULT_BASE_ADDRESS_LOWER_ZEROS
 ******************************************************************************/
const ru_field_rec NATC_CFG_DDR_RESULT_BASE_ADDRESS_LOWER_ZEROS_FIELD =
{
    "ZEROS",
#if RU_INCLUDE_DESC
    "",
    "",
#endif
    NATC_CFG_DDR_RESULT_BASE_ADDRESS_LOWER_ZEROS_FIELD_MASK,
    0,
    NATC_CFG_DDR_RESULT_BASE_ADDRESS_LOWER_ZEROS_FIELD_WIDTH,
    NATC_CFG_DDR_RESULT_BASE_ADDRESS_LOWER_ZEROS_FIELD_SHIFT,
#if RU_INCLUDE_ACCESS
    ru_access_rw
#endif
};

/******************************************************************************
 * Field: NATC_CFG_DDR_RESULT_BASE_ADDRESS_UPPER_ZEROS
 ******************************************************************************/
const ru_field_rec NATC_CFG_DDR_RESULT_BASE_ADDRESS_UPPER_ZEROS_FIELD =
{
    "ZEROS",
#if RU_INCLUDE_DESC
    "",
    "",
#endif
    NATC_CFG_DDR_RESULT_BASE_ADDRESS_UPPER_ZEROS_FIELD_MASK,
    0,
    NATC_CFG_DDR_RESULT_BASE_ADDRESS_UPPER_ZEROS_FIELD_WIDTH,
    NATC_CFG_DDR_RESULT_BASE_ADDRESS_UPPER_ZEROS_FIELD_SHIFT,
#if RU_INCLUDE_ACCESS
    ru_access_rw
#endif
};

/******************************************************************************
 * Field: NATC_CFG_DDR_RESULT_BASE_ADDRESS_UPPER_BAR
 ******************************************************************************/
const ru_field_rec NATC_CFG_DDR_RESULT_BASE_ADDRESS_UPPER_BAR_FIELD =
{
    "BAR",
#if RU_INCLUDE_DESC
    "",
    "",
#endif
    NATC_CFG_DDR_RESULT_BASE_ADDRESS_UPPER_BAR_FIELD_MASK,
    0,
    NATC_CFG_DDR_RESULT_BASE_ADDRESS_UPPER_BAR_FIELD_WIDTH,
    NATC_CFG_DDR_RESULT_BASE_ADDRESS_UPPER_BAR_FIELD_SHIFT,
#if RU_INCLUDE_ACCESS
    ru_access_rw
#endif
};

#endif /* RU_INCLUDE_FIELD_DB */

/******************************************************************************
 * Register: NATC_CFG_DDR_KEY_BASE_ADDRESS_LOWER
 ******************************************************************************/
#if RU_INCLUDE_FIELD_DB
static const ru_field_rec *NATC_CFG_DDR_KEY_BASE_ADDRESS_LOWER_FIELDS[] =
{
    &NATC_CFG_DDR_KEY_BASE_ADDRESS_LOWER_BAR_FIELD,
    &NATC_CFG_DDR_KEY_BASE_ADDRESS_LOWER_ZEROS_FIELD,
};

#endif /* RU_INCLUDE_FIELD_DB */

const ru_reg_rec NATC_CFG_DDR_KEY_BASE_ADDRESS_LOWER_REG = 
{
    "DDR_KEY_BASE_ADDRESS_LOWER",
#if RU_INCLUDE_DESC
    "Lower 32-bit of NAT table 7 key base address NAT table 7 in DDR",
    "Lower 32-bit of the base address of DDR key table"
    "Address must be 64-bit aligned (bit 2 through 0 are zero's)"
    "In order maximum number of key fetches,"
    "for 16-byte key, bit 3 should be 0 to align at 16 byte boundary"
    "for 32-byte key, bit 3 and 4 should be 0 to align at 32 bytes boundary",
#endif
    NATC_CFG_DDR_KEY_BASE_ADDRESS_LOWER_REG_OFFSET,
    0,
    0,
    1097,
#if RU_INCLUDE_ACCESS
    ru_access_rw,
#endif
#if RU_INCLUDE_FIELD_DB
    2,
    NATC_CFG_DDR_KEY_BASE_ADDRESS_LOWER_FIELDS
#endif /* RU_INCLUDE_FIELD_DB */
};

/******************************************************************************
 * Register: NATC_CFG_DDR_KEY_BASE_ADDRESS_UPPER
 ******************************************************************************/
#if RU_INCLUDE_FIELD_DB
static const ru_field_rec *NATC_CFG_DDR_KEY_BASE_ADDRESS_UPPER_FIELDS[] =
{
    &NATC_CFG_DDR_KEY_BASE_ADDRESS_UPPER_ZEROS_FIELD,
    &NATC_CFG_DDR_KEY_BASE_ADDRESS_UPPER_BAR_FIELD,
};

#endif /* RU_INCLUDE_FIELD_DB */

const ru_reg_rec NATC_CFG_DDR_KEY_BASE_ADDRESS_UPPER_REG = 
{
    "DDR_KEY_BASE_ADDRESS_UPPER",
#if RU_INCLUDE_DESC
    "Upper 32-bit of NAT table 7 key base address NAT table 7 in DDR",
    "Upper 8-bit of the base address of DDR key table"
    "For 32-bit system this field should be left as 0",
#endif
    NATC_CFG_DDR_KEY_BASE_ADDRESS_UPPER_REG_OFFSET,
    0,
    0,
    1098,
#if RU_INCLUDE_ACCESS
    ru_access_rw,
#endif
#if RU_INCLUDE_FIELD_DB
    2,
    NATC_CFG_DDR_KEY_BASE_ADDRESS_UPPER_FIELDS
#endif /* RU_INCLUDE_FIELD_DB */
};

/******************************************************************************
 * Register: NATC_CFG_DDR_RESULT_BASE_ADDRESS_LOWER
 ******************************************************************************/
#if RU_INCLUDE_FIELD_DB
static const ru_field_rec *NATC_CFG_DDR_RESULT_BASE_ADDRESS_LOWER_FIELDS[] =
{
    &NATC_CFG_DDR_RESULT_BASE_ADDRESS_LOWER_BAR_FIELD,
    &NATC_CFG_DDR_RESULT_BASE_ADDRESS_LOWER_ZEROS_FIELD,
};

#endif /* RU_INCLUDE_FIELD_DB */

const ru_reg_rec NATC_CFG_DDR_RESULT_BASE_ADDRESS_LOWER_REG = 
{
    "DDR_RESULT_BASE_ADDRESS_LOWER",
#if RU_INCLUDE_DESC
    "Lower 32-bit of NAT table 7 result base address NAT table 7 in DDR",
    "Lower 32-bit of the base address of DDR context table"
    "Address must be 64-bit aligned (bit 2 through 0 are zero's)",
#endif
    NATC_CFG_DDR_RESULT_BASE_ADDRESS_LOWER_REG_OFFSET,
    0,
    0,
    1099,
#if RU_INCLUDE_ACCESS
    ru_access_rw,
#endif
#if RU_INCLUDE_FIELD_DB
    2,
    NATC_CFG_DDR_RESULT_BASE_ADDRESS_LOWER_FIELDS
#endif /* RU_INCLUDE_FIELD_DB */
};

/******************************************************************************
 * Register: NATC_CFG_DDR_RESULT_BASE_ADDRESS_UPPER
 ******************************************************************************/
#if RU_INCLUDE_FIELD_DB
static const ru_field_rec *NATC_CFG_DDR_RESULT_BASE_ADDRESS_UPPER_FIELDS[] =
{
    &NATC_CFG_DDR_RESULT_BASE_ADDRESS_UPPER_ZEROS_FIELD,
    &NATC_CFG_DDR_RESULT_BASE_ADDRESS_UPPER_BAR_FIELD,
};

#endif /* RU_INCLUDE_FIELD_DB */

const ru_reg_rec NATC_CFG_DDR_RESULT_BASE_ADDRESS_UPPER_REG = 
{
    "DDR_RESULT_BASE_ADDRESS_UPPER",
#if RU_INCLUDE_DESC
    "Upper 32-bit of NAT table 7 result base address NAT table 7 in DDR",
    "Upper 8-bit of the base address of DDR context table"
    "For 32-bit system this field should be left as 0",
#endif
    NATC_CFG_DDR_RESULT_BASE_ADDRESS_UPPER_REG_OFFSET,
    0,
    0,
    1100,
#if RU_INCLUDE_ACCESS
    ru_access_rw,
#endif
#if RU_INCLUDE_FIELD_DB
    2,
    NATC_CFG_DDR_RESULT_BASE_ADDRESS_UPPER_FIELDS
#endif /* RU_INCLUDE_FIELD_DB */
};

/******************************************************************************
 * Block: NATC_CFG
 ******************************************************************************/
static const ru_reg_rec *NATC_CFG_REGS[] =
{
    &NATC_CFG_DDR_KEY_BASE_ADDRESS_LOWER_REG,
    &NATC_CFG_DDR_KEY_BASE_ADDRESS_UPPER_REG,
    &NATC_CFG_DDR_RESULT_BASE_ADDRESS_LOWER_REG,
    &NATC_CFG_DDR_RESULT_BASE_ADDRESS_UPPER_REG,
};

unsigned long NATC_CFG_ADDRS[] =
{
    0x82e50290,
    0x82e502a0,
    0x82e502b0,
    0x82e502c0,
    0x82e502d0,
    0x82e502e0,
    0x82e502f0,
    0x82e50300,
};

const ru_block_rec NATC_CFG_BLOCK = 
{
    "NATC_CFG",
    NATC_CFG_ADDRS,
    8,
    4,
    NATC_CFG_REGS
};

/* End of file XRDP_NATC_CFG.c */
