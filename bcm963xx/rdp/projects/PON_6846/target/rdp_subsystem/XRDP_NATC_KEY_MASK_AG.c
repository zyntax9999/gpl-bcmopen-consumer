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
 * Field: NATC_KEY_MASK_KEY_MASK_KEY_MASK
 ******************************************************************************/
const ru_field_rec NATC_KEY_MASK_KEY_MASK_KEY_MASK_FIELD =
{
    "KEY_MASK",
#if RU_INCLUDE_DESC
    "",
    "Specifies the key mask for each byte in the key."
    "each bit corresponds to one byte."
    "0 enables the compare and 1 disables the compare."
    "bit 0 corresponds to byte 0"
    "bit 1 corresponds to byte 1"
    "bit 2 corresponds to byte 2"
    "......................"
    "bit 31 corresponds to byte 31",
#endif
    NATC_KEY_MASK_KEY_MASK_KEY_MASK_FIELD_MASK,
    0,
    NATC_KEY_MASK_KEY_MASK_KEY_MASK_FIELD_WIDTH,
    NATC_KEY_MASK_KEY_MASK_KEY_MASK_FIELD_SHIFT,
#if RU_INCLUDE_ACCESS
    ru_access_rw
#endif
};

#endif /* RU_INCLUDE_FIELD_DB */

/******************************************************************************
 * Register: NATC_KEY_MASK_KEY_MASK
 ******************************************************************************/
#if RU_INCLUDE_FIELD_DB
static const ru_field_rec *NATC_KEY_MASK_KEY_MASK_FIELDS[] =
{
    &NATC_KEY_MASK_KEY_MASK_KEY_MASK_FIELD,
};

#endif /* RU_INCLUDE_FIELD_DB */

const ru_reg_rec NATC_KEY_MASK_KEY_MASK_REG = 
{
    "KEY_MASK",
#if RU_INCLUDE_DESC
    "NAT table 7 key mask register",
    "NAT Cache key Mask Register",
#endif
    NATC_KEY_MASK_KEY_MASK_REG_OFFSET,
    0,
    0,
    1106,
#if RU_INCLUDE_ACCESS
    ru_access_rw,
#endif
#if RU_INCLUDE_FIELD_DB
    1,
    NATC_KEY_MASK_KEY_MASK_FIELDS
#endif /* RU_INCLUDE_FIELD_DB */
};

/******************************************************************************
 * Block: NATC_KEY_MASK
 ******************************************************************************/
static const ru_reg_rec *NATC_KEY_MASK_REGS[] =
{
    &NATC_KEY_MASK_KEY_MASK_REG,
};

unsigned long NATC_KEY_MASK_ADDRS[] =
{
    0x82e503b0,
    0x82e503b4,
    0x82e503b8,
    0x82e503bc,
    0x82e503c0,
    0x82e503c4,
    0x82e503c8,
    0x82e503cc,
};

const ru_block_rec NATC_KEY_MASK_BLOCK = 
{
    "NATC_KEY_MASK",
    NATC_KEY_MASK_ADDRS,
    8,
    1,
    NATC_KEY_MASK_REGS
};

/* End of file XRDP_NATC_KEY_MASK.c */
