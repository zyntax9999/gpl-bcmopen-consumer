// <:copyright-BRCM:2013:DUAL/GPL:standard
// 
//    Copyright (c) 2013 Broadcom 
//    All Rights Reserved
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License, version 2, as published by
// the Free Software Foundation (the "GPL").
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// 
// A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
// writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.
// 
// :>
/*
 * pbit_to_queue object user header file.
 * This header file is generated automatically. Do not edit!
 */
#ifndef _RDPA_AG_PBIT_TO_QUEUE_USR_H_
#define _RDPA_AG_PBIT_TO_QUEUE_USR_H_

#include <sys/ioctl.h>
#include "rdpa_user.h"
#include "rdpa_user_types.h"
#include "rdpa_pbit_to_queue_user_ioctl_ag.h"

/** \addtogroup pbit_to_queue
 * @{
 */


/** Get pbit_to_queue type handle.
 *
 * This handle should be passed to bdmf_new_and_set() function in
 * order to create a pbit_to_queue object.
 * \return pbit_to_queue type handle
 */
static inline bdmf_type_handle rdpa_pbit_to_queue_drv(void)
{
	rdpa_ioctl_cmd_t pa = {0};
	int fd, ret = 0;

	pa.cmd = RDPA_PBIT_TO_QUEUE_DRV;
	fd = open(RDPA_USR_DEV_NAME, O_RDWR);
	if (fd < 0)
	{
		rdpa_usr_error("%s: %s\n", RDPA_USR_DEV_NAME, strerror(errno));
		return 0;
	}

	ret = ioctl(fd, RDPA_PBIT_TO_QUEUE_IOCTL, &pa);
	if (ret)
	{
		rdpa_usr_error("ioctl failed, Errno[%s] ret=%d\n", strerror(errno), ret);
		close(fd);
		return 0;
	}

	close(fd);
	return pa.drv;
}

/** Get pbit_to_queue object by key.

 * This function returns pbit_to_queue object instance by key.
 * \param[in] table_    Object key
 * \param[out] pbit_to_queue_obj    Object handle
 * \return    0=OK or error <0
 */
static inline int rdpa_pbit_to_queue_get(bdmf_number table_, bdmf_object_handle *pbit_to_queue_obj)
{
	rdpa_ioctl_cmd_t pa = {0};
	int fd, ret = 0;

	pa.cmd = RDPA_PBIT_TO_QUEUE_GET;
	pa.parm = (uint64_t)(long)table_;

	fd = open(RDPA_USR_DEV_NAME, O_RDWR);
	if (fd < 0)
	{
		rdpa_usr_error("%s: %s\n", RDPA_USR_DEV_NAME, strerror(errno));
		return -EINVAL;
	}
	ret = ioctl(fd, RDPA_PBIT_TO_QUEUE_IOCTL, &pa);
	if (ret)
	{
		rdpa_usr_error("ioctl failed, Errno[%s] ret=%d\n", strerror(errno), ret);
		close(fd);
		return ret;
	}

	*pbit_to_queue_obj = pa.mo;
	close(fd);
	return pa.ret;
}

/** Get pbit_to_queue/table attribute.
 *
 * Get Table index.
 * \param[in]   mo_ pbit_to_queue object handle or mattr transaction handle
 * \param[out]  table_ Attribute value
 * \return 0 or error code < 0
 * The function can be called in task and softirq contexts.
 */
static inline int rdpa_pbit_to_queue_table_get(bdmf_object_handle mo_, bdmf_number *table_)
{
	rdpa_ioctl_cmd_t pa = {0};
	int fd, ret;

	pa.mo = mo_;
	pa.ptr = (bdmf_ptr)(unsigned long)table_;
	pa.cmd = RDPA_PBIT_TO_QUEUE_TABLE_GET;

	fd = open(RDPA_USR_DEV_NAME, O_RDWR);
	if (fd < 0)
	{
		rdpa_usr_error("%s: %s\n", RDPA_USR_DEV_NAME, strerror(errno));
		return -EINVAL;
	}
	ret = ioctl(fd, RDPA_PBIT_TO_QUEUE_IOCTL, &pa);
	if (ret)
	{
		rdpa_usr_error("ioctl failed, ret=%d\n", ret);
		close(fd);
		return ret;
	}

	close(fd);
	return pa.ret;
}


/** Set pbit_to_queue/table attribute.
 *
 * Set Table index.
 * \param[in]   mo_ pbit_to_queue object handle or mattr transaction handle
 * \param[in]   table_ Attribute value
 * \return 0 or error code < 0
 * The function can be called in task and softirq contexts.
 */
static inline int rdpa_pbit_to_queue_table_set(bdmf_object_handle mo_, bdmf_number table_)
{
	rdpa_ioctl_cmd_t pa = {0};
	int fd, ret;

	pa.mo = mo_;
	pa.parm = (uint64_t)(long)table_;
	pa.cmd = RDPA_PBIT_TO_QUEUE_TABLE_SET;

	fd = open(RDPA_USR_DEV_NAME, O_RDWR);
	if (fd < 0)
	{
		rdpa_usr_error("%s: %s\n", RDPA_USR_DEV_NAME, strerror(errno));
		return -EINVAL;
	}
	ret = ioctl(fd, RDPA_PBIT_TO_QUEUE_IOCTL, &pa);
	if (ret)
	{
		rdpa_usr_error("ioctl failed, ret=%d\n", ret);
		close(fd);
		return ret;
	}

	close(fd);
	return pa.ret;
}


/** Get pbit_to_queue/pbit_map attribute entry.
 *
 * Get Priority array.
 * \param[in]   mo_ pbit_to_queue object handle or mattr transaction handle
 * \param[in]   ai_ Attribute array index
 * \param[out]  pbit_map_ Attribute value
 * \return 0 or error code < 0
 * The function can be called in task context only.
 */
static inline int rdpa_pbit_to_queue_pbit_map_get(bdmf_object_handle mo_, bdmf_index ai_, bdmf_number *pbit_map_)
{
	rdpa_ioctl_cmd_t pa = {0};
	int fd, ret;

	pa.mo = mo_;
	pa.ai = (bdmf_index)(long)ai_;
	pa.ptr = (bdmf_ptr)(unsigned long)pbit_map_;
	pa.cmd = RDPA_PBIT_TO_QUEUE_PBIT_MAP_GET;

	fd = open(RDPA_USR_DEV_NAME, O_RDWR);
	if (fd < 0)
	{
		rdpa_usr_error("%s: %s\n", RDPA_USR_DEV_NAME, strerror(errno));
		return -EINVAL;
	}
	ret = ioctl(fd, RDPA_PBIT_TO_QUEUE_IOCTL, &pa);
	if (ret)
	{
		rdpa_usr_error("ioctl failed, ret=%d\n", ret);
		close(fd);
		return ret;
	}

	close(fd);
	return pa.ret;
}


/** Set pbit_to_queue/pbit_map attribute entry.
 *
 * Set Priority array.
 * \param[in]   mo_ pbit_to_queue object handle or mattr transaction handle
 * \param[in]   ai_ Attribute array index
 * \param[in]   pbit_map_ Attribute value
 * \return 0 or error code < 0
 * The function can be called in task context only.
 */
static inline int rdpa_pbit_to_queue_pbit_map_set(bdmf_object_handle mo_, bdmf_index ai_, bdmf_number pbit_map_)
{
	rdpa_ioctl_cmd_t pa = {0};
	int fd, ret;

	pa.mo = mo_;
	pa.ai = (bdmf_index)(long)ai_;
	pa.parm = (uint64_t)(long)pbit_map_;
	pa.cmd = RDPA_PBIT_TO_QUEUE_PBIT_MAP_SET;

	fd = open(RDPA_USR_DEV_NAME, O_RDWR);
	if (fd < 0)
	{
		rdpa_usr_error("%s: %s\n", RDPA_USR_DEV_NAME, strerror(errno));
		return -EINVAL;
	}
	ret = ioctl(fd, RDPA_PBIT_TO_QUEUE_IOCTL, &pa);
	if (ret)
	{
		rdpa_usr_error("ioctl failed, ret=%d\n", ret);
		close(fd);
		return ret;
	}

	close(fd);
	return pa.ret;
}

/** @} end of pbit_to_queue Doxygen group */




#endif /* _RDPA_AG_PBIT_TO_QUEUE_USR_H_ */