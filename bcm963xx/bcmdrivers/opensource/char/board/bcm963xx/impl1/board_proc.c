/*
* <:copyright-BRCM:2016:DUAL/GPL:standard
* 
*    Copyright (c) 2016 Broadcom 
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

#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/ctype.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/mtd/mtd.h>

#include <bcmtypes.h>
#include <bcm_map_part.h>
#include <board.h>
#include <boardparms.h>

#include "board_proc.h"
#include "board_image.h"
#include "board_wl.h"
#include "board_wd.h"
#include "bcm_mbox_map.h"

#if defined(CONFIG_BCM96838) || defined(CONFIG_BCM96848) || defined(CONFIG_BCM96858)
int proc_show_rdp_mem( struct file *file, char __user *buf, size_t len, loff_t *pos);
#endif

#if defined (WIRELESS)
static ssize_t proc_get_wl_nandmanufacture(struct file * file, char * buff, size_t len, loff_t *offset);
#ifdef BUILD_NAND
static ssize_t proc_get_wl_mtdname(struct file * file, char * buff, size_t len, loff_t *offset);
#endif
#endif

static ssize_t proc_get_param_string(struct file *, char *, size_t, loff_t *);
static ssize_t proc_set_param(struct file *, const char *, size_t, loff_t *);
static ssize_t proc_set_led(struct file *, const char *, size_t, loff_t *);

#if defined(CONFIG_BCM_WATCHDOG_TIMER)
static ssize_t proc_get_watchdog(struct file *, char *, size_t, loff_t *);
static ssize_t proc_set_watchdog(struct file *, const char *, size_t, loff_t *);
#endif /* defined(CONFIG_BCM_WATCHDOG_TIMER) */
int add_proc_files(void);
int del_proc_files(void);

static ssize_t __proc_get_socinfo(char *buf, int cnt)
{
    char socname[15] = {0};
    int i;
    int n=0;

    kerSysGetChipName( socname, strlen(socname));

    for( i=0; i< strlen(socname); i++ )
    {
        if(socname[i] == '_')
        {
            socname[i]='\0';
            break;
        }
    }
            
    n += sprintf(buf,   "SoC Name        :BCM%s\n", socname);
    n += sprintf(buf+n, "Revision        :%s\n", &socname[i+1]);

    return n;
}
static ssize_t __proc_get_wan_type(char *buf)
{
    int n = 0;

    unsigned int wan_type = 0, t;
    int i, j, len = 0;

    BpGetOpticalWan(&wan_type);
    if (wan_type == BP_NOT_DEFINED)
    {
        n=sprintf(buf, "none");
        return n;
    }

    for (i = 0, j = 0; wan_type; i++)
    {
        t = wan_type & (1 << i);
        if (!t)
            continue;

        wan_type &= ~(1 << i);
        if (j++)
        {
            sprintf(buf + len, "\n");
            len++;
        }

        switch (t)
        {
        case BP_OPTICAL_WAN_GPON:
            n+=sprintf(buf + len, "gpon");
            break;
        case BP_OPTICAL_WAN_EPON:
            n+=sprintf(buf + len, "epon");
            break;
        case BP_OPTICAL_WAN_AE:
            n+=sprintf(buf + len, "ae");
            break;
        default:
            n+=sprintf(buf + len, "unknown");
            break;
        }
        len += n;
    }

    return len;
}

static ssize_t proc_get_socinfo( struct file *file,
                                       char __user *buf,
                                       size_t len, loff_t *pos)
{
    int ret=0;
    if(len && *pos == 0)
    {
       *pos=__proc_get_socinfo(buf, len);
           if(likely(*pos != 0)) //something went wrong
        ret=*pos;
    }
    return ret;
}
static ssize_t proc_get_wan_type( struct file *file,
                                       char __user *buf,
                                       size_t len, loff_t *pos)
{
    int ret=0;
    if(len && *pos == 0)
    {
       *pos=__proc_get_wan_type(buf);
       if(likely(*pos != 0)) //something went wrong
           ret=*pos;
    }
    return ret;
}

static char nvram_query_str[256]={0};
static ssize_t proc_get_query(struct file *file,
				char __user *buf,
				size_t len, loff_t *pos)
{
    int ret=0;
    char *value=NULL;

    if(*pos == 0)
    {

        value = (unsigned char *)kmalloc(len+1, GFP_KERNEL);
        if(value != NULL)
        {
            memset(value, '\0', len+1);
            ret=envram_get_locked((char*)nvram_query_str, value, len);
            if(copy_to_user(buf, value, len) == 0)
            {
                *pos=strlen(value);
            }
            else
            {
                ret=-EFAULT;
                *pos=-1;
            }
            kfree(value);
        }
        else
            ret=-EFAULT;
    }
    return ret;

}

static ssize_t proc_set_query(struct file *file, const char *buff, size_t len, loff_t *offset)
{
char *temp_str=NULL;

    memset(nvram_query_str, '\0', sizeof(nvram_query_str));

    if ((len > sizeof(nvram_query_str)-1) || (copy_from_user(nvram_query_str, buff, len) != 0))
        return -EFAULT;
    if((temp_str=strchr(nvram_query_str, '\n')) != NULL)
    {
        *temp_str='\0';
    }
    if((temp_str=strchr(nvram_query_str, '\r')) != NULL)
    {
        *temp_str='\0';
    }
    return len;
}


static ssize_t __proc_set_param(struct file *f, const char *buf, unsigned long cnt, void *data)
{
    char input[32];

    int i = 0;
    int r = cnt;

    if ((cnt > 32) || (copy_from_user(input, buf, cnt) != 0))
        return -EFAULT;

    for (i = 0; i < r; i ++)
    {
        if (!isxdigit(input[i]) && input[i] != ':' && input[i] != ' ')
        {
            memmove(&input[i], &input[i + 1], r - i - 1);
            r --;
            i --;
        }
    }

    r=envram_set_locked((char*)data, input);
    sync_nvram_with_flash();
    if(r != -1)
        r=cnt;
    return r;
}

/* The string stored in nvram only has a terminating 0 if it is shorter than the
   max allocated space for the variable. It is however copied to a buffer via
   snprintf() and thus always ends with 0. There can be garbage after the
   terminating 0 up to max allowed (in the nvram, but not the buffer).
   Non initialized data is 0xff. */
ssize_t __proc_get_param_string(char *page, int cnt, void *data)
{
    int r = 0;
    char *value;

    if (data == NULL)
        return 0;

    value = (unsigned char *)kmalloc(cnt+1, GFP_KERNEL);
    if(value != NULL)
    {
        r=envram_get_locked((char*)data, value, cnt);

		if(value[r]) {
			r++;
			value[r] = '\n';
		}
		else {
			value[r] = '\n';
			r++;
		}

        if(copy_to_user(page, value, r > cnt ? cnt:r))
        {
            r=-EFAULT;
        }
        kfree(value);
    }
    return (r < cnt && r > 0)? r: 0;
}

static ssize_t __proc_set_led(struct file *f, const char *buf, unsigned long cnt, void *data)
{
    // char leddata[16];
    unsigned int leddata;
    char input[32];
    int i;

    if (cnt > 31)
        cnt = 31;

    if (copy_from_user(input, buf, cnt) != 0)
        return -EFAULT;


    for (i = 0; i < cnt; i ++)
    {
        if (!isxdigit(input[i]))
        {
            input[i] = 0;
        }
    }
    input[i] = 0;

    if (0 != kstrtouint(input, 16, &leddata)) 
        return -EFAULT;

    kerSysLedCtrl ((leddata & 0xff00) >> 8, leddata & 0xff);
    return cnt;
}

static ssize_t proc_get_param_string(struct file * file, char * buff, size_t len, loff_t *offset)
{

    int ret=0;
    if(len && *offset == 0)
    {
        *offset =__proc_get_param_string(buff, len, PDE_DATA(file_inode(file))); 
        if(likely(*offset != 0)) //something went wrong
            ret=*offset;
    }
    return ret;
}
static ssize_t proc_set_param(struct file *file, const char *buff, size_t len, loff_t *offset)
{
    return __proc_set_param(file,buff,len,PDE_DATA(file_inode(file)));
}
static ssize_t proc_set_led(struct file *file, const char *buff, size_t len, loff_t *offset)
{
    int ret=-1;
    if(*offset == 0)
    {
        *offset=__proc_set_led(file, buff, len, PDE_DATA(file_inode(file)));
        if(likely(*offset != 0)) //something went wrong
            ret=*offset;
    }    
    return ret;

}

#if defined(CONFIG_BCM_FAILSAFE_BOOT)
static ssize_t proc_set_failsafe_boot(struct file *f, const char *buf, size_t cnt, loff_t *data)
{
    char __in[8] = {0};
    unsigned int complete = 0;
   
    if (cnt < 1 ||  cnt > 4 || 
        copy_from_user(__in, buf, 1)) {
        return -EFAULT;
    }

    if (sscanf(__in, "%u", &complete) != 1) {
        printk("\nError format, it is as:\n");
        return -EFAULT;
    }
    if (complete) {
        if (BCM_MBOX1_STATUS()) {
            /* Done tracing failsafe*/
            unsigned int st = BCM_MBOX_MSG1_GET();
            BCM_BLR_BOOT_STATE_SET_ERR(st, 0x0);
            BCM_MBOX_MSG1_SET(st);
        }
    }
    return cnt;
}

static ssize_t proc_get_failsafe_boot(struct file *file, char __user *buff, size_t len, loff_t *offset)
{
    int r = 0;
    unsigned int st;
    if(*offset != 0)
        return 0;
    st = BCM_BLR_BOOT_STATE_GET_INFO(BCM_MBOX_MSG1_GET());
     
    r = sprintf(buff, "BOOTED  %s IMAGE\n",(st&CFE_BOOT_INFO_SECONDARY)?"FAILSAFE PREVIOUS":"ACTIVE");
    *offset =  (r < len)? r : 0;
    return *offset;
}

#endif

static int __proc_set_param_string(struct file *f, const char *buf, unsigned long cnt, void *data)
{
    char input[256];

    // Ensure ending null
    memset(input, 0, sizeof(input));

    if ((cnt >= sizeof(input)) || (copy_from_user(input, buf, cnt) != 0))
        return -EFAULT;

    /* copy_from_user gives a '\n' at the end of the buffer, don't copy that */
    if(cnt > 0 && input[cnt - 1] == '\n') {
        input[cnt - 1] = 0;
    }

    envram_sync_set_locked(data, input);

    /* Value returned from envram_sync_set_locked() is not what procfs
     * expects. Thus no point in returning that. In addition, no error
     * is returned in case of a problem storing the updated nvram data.
     * Broadcom just hopes for the best as usual. */
    return cnt;
}
static ssize_t proc_set_param_string(struct file *file, const char *buff, size_t len, loff_t *offset)
{
    return __proc_set_param_string(file, buff, len, PDE_DATA(file_inode(file)));
}


#if defined(CONFIG_BCM_WATCHDOG_TIMER)

#if defined(CONFIG_BCM963268)
#  define GET_RESET_STATUS()  (TIMER->ClkRstCtl)
#  define RESET_STATUS_POR   (1<<29)
#  define RESET_STATUS_HW    (1<<30) /* correct bits despite Broadcom has other constants in 63268_map_part.h */
#  define RESET_STATUS_SW    (1<<31)
#elif defined(CONFIG_BCM963138)
#  define GET_RESET_STATUS()  (TIMER->ResetStatus)
#  define RESET_STATUS_POR   POR_RESET_STATUS
#  define RESET_STATUS_HW    HW_RESET_STATUS
#  define RESET_STATUS_SW    SW_RESET_STATUS
#  define STRAP_RESET_MASK   0x3000
#  define STRAP_RESET_POR    0x1000
#  define STRAP_RESET_HW     0x2000
#  define STRAP_RESET_SW     0x3000
#elif defined(CONFIG_BCM96362) || defined(CONFIG_BCM963381) || defined(CONFIG_BCM963158) || defined(CONFIG_BCM963178)
#  define GET_RESET_STATUS()  (0)  /* This chip has no reset status reg */
#  define RESET_STATUS_POR   (1)
#  define RESET_STATUS_HW    (1)
#  define RESET_STATUS_SW    (1)
#else
#  error "You need to figure out what the register name/bits are for this chip!"
#endif

static ssize_t __proc_get_watchdog(char *page, int cnt, void *data)
{
    int r = 0;

    if(!page || !cnt) return 0;
    r += sprintf(page + r, "watchdog enabled=%u timer=%u us suspend=%u\n", 
                           watchdog_data.enabled, 
                           watchdog_data.timer, 
                           watchdog_data.suspend);
    r += sprintf(page + r, "         userMode=%u userThreshold=%u userTimeout=%u\n", 
                           watchdog_data.userMode, 
                           watchdog_data.userThreshold/2, 
                           watchdog_data.userTimeout/2);

    /* Special case for 63138 where Broadcom does a reboot
     * in init_arm.S every time the system starts. Likely
     * for increasing system stability. */
#if defined(CONFIG_BCM963138)
    if(MISC->miscStrapBus & MISC_STRAP_BUS_PMC_BOOT_AVS &&
            GET_RESET_STATUS() & RESET_STATUS_SW) {
        switch (MISC->miscStrapBus & STRAP_RESET_MASK) {
            case STRAP_RESET_POR:
                r += sprintf(page + r, "boot reason=POR\n");
                break;
            case STRAP_RESET_HW:
                r += sprintf(page + r, "boot reason=HW\n");
                break;
            case STRAP_RESET_SW:
                r += sprintf(page + r, "boot reason=SW\n");
                break;
            default:
                r += sprintf(page + r, "boot reason=??\n");
                break;
        }

        return (r < cnt)? r: 0;
    }
#endif

    if (GET_RESET_STATUS() & RESET_STATUS_POR)
            r += sprintf(page + r, "boot reason=POR\n");
    else if (GET_RESET_STATUS() & RESET_STATUS_HW)
            r += sprintf(page + r, "boot reason=HW\n");
    else if (GET_RESET_STATUS() & RESET_STATUS_SW)
            r += sprintf(page + r, "boot reason=SW\n");
    else
            r += sprintf(page + r, "boot reason=??\n");

    return (r < cnt)? r: 0;
}

static ssize_t __proc_set_watchdog(struct file *f, const char *buf, unsigned long cnt, void *data)
{
    char input[64];
    unsigned int enabled, timer;
    unsigned int userMode, userThreshold;
   
    if (cnt > 64) 
    {
        cnt = 64;
    }

    if (copy_from_user(input, buf, cnt) != 0) 
    {
        return -EFAULT;
    }

    if (strncasecmp(input, "OK", 2) == 0)
    {
        bcm_reset_watchdog();
        return cnt;
    }

    if (sscanf(input, "%u %u %u %u", &enabled, &timer, &userMode, &userThreshold) != 4)
    {
        printk("\nError format, it is as:\n");
        printk("\"enabled(0|1) timer(us) userMode(0|1) userThreshold\"\n");
        return -EFAULT;
    }

    bcm_set_watchdog(enabled, timer, userMode, userThreshold);

    return cnt;
}

static ssize_t proc_get_watchdog(struct file *file, char *buff, size_t len, loff_t *offset)
{

    if(*offset != 0)
        return 0;
    *offset = __proc_get_watchdog(buff, len, PDE_DATA(file_inode(file)));

    return *offset;

}
static ssize_t proc_set_watchdog (struct file *file, const char *buff, size_t len, loff_t *offset)
{
    int ret=-1;

    if(*offset == 0)
    {
       *offset=__proc_set_watchdog(file, buff, len, PDE_DATA(file_inode(file)));
       if(likely(*offset != 0)) //something went wrong
          ret=*offset;
    }
return ret;
}
#endif


#if defined(WIRELESS)
/*  for higher version 4.1 kernel */
static ssize_t proc_get_wl_nandmanufacture(struct file * file, char * buff, size_t len, loff_t *pos)
{
    ssize_t ret=0;
    if(len && *pos == 0)
    {
        (*pos) = sprintf(buff, "%d", _get_wl_nandmanufacture());
        if(likely(*pos != 0)) 
            ret=*pos;
    }
    return ret;
}

#ifdef BUILD_NAND
static ssize_t proc_get_wl_mtdname(struct file * file, char * buff, size_t len, loff_t *pos)
{
    ssize_t ret=0;
    if(len && *pos == 0)
    {
        struct mtd_info *mtd = get_mtd_device_nm(WLAN_MFG_PARTITION_NAME);
        if( !IS_ERR_OR_NULL(mtd) ) {
           (*pos) = sprintf(buff, "mtd%d",mtd->index );
           if(likely(*pos != 0)) 
               ret=*pos;
         }
    }
    return ret;
}
#endif
#endif

static struct file_operations proc_ro_str_fops = {
    .read = proc_get_param_string,
    .write = NULL,
};
static struct file_operations proc_rw_str_fops = {
    .read = proc_get_param_string,
    .write = proc_set_param_string,
};
#ifdef WIRELESS
   static struct file_operations wl_get_nandmanufacture_proc = {
       .read=proc_get_wl_nandmanufacture,
       .write=NULL,
    };
#ifdef BUILD_NAND
   static struct file_operations wl_get_mtdname_proc = {
       .read=proc_get_wl_mtdname,
       .write=NULL,
    };
#endif
#endif
   static struct file_operations base_mac_add_proc = {
       .read=proc_get_param_string,
       .write=proc_set_param,
    };
   static struct file_operations bootline_proc = {
       .read=proc_get_param_string,
       .write=NULL,
    };
    static struct file_operations led_proc = {
       .write=proc_set_led,
    };
#if defined(CONFIG_BCM96838) || defined(CONFIG_BCM96848)
    static struct file_operations rdp_mem_proc = {
       .read=proc_show_rdp_mem,
    };
#endif
    static struct file_operations supp_optical_wan_types_proc = {
       .read=proc_get_wan_type,
    };
#if defined(CONFIG_BCM_WATCHDOG_TIMER)
    static struct file_operations watchdog_proc = {
       .read=proc_get_watchdog,
       .write=proc_set_watchdog,
    };
#endif
#if defined(CONFIG_BCM_FAILSAFE_BOOT)
    static struct file_operations failsafe_boot_proc = {
       .write = proc_set_failsafe_boot,
       .read = proc_get_failsafe_boot,
    };
#endif
    static struct file_operations boardid_proc = {
       .read=proc_get_param_string,
    };
    static struct file_operations socinfo_proc = {
       .read=proc_get_socinfo,
    };
    static struct file_operations base_query_proc = {
       .read=proc_get_query,
       .write=proc_set_query
    };

int add_proc_files(void)
{
#define offset(type, elem) ((size_t)&((type *)0)->elem)

    char *mi=NVRAM_UCABASEMACADDR;
    char *bootline=NVRAM_SZBOOTLINE;
    char *boardid=NVRAM_SZBOARDID;

    struct proc_dir_entry *p0;
    struct proc_dir_entry *p1;
    struct proc_dir_entry *p2;
#if defined(CONFIG_BCM96838) || defined(CONFIG_BCM96848)
    struct proc_dir_entry *p3;
#endif
    struct proc_dir_entry *p4;
    struct proc_dir_entry *p5;

    p0 = proc_mkdir("nvram", NULL);

    if (p0 == NULL)
    {
        printk("add_proc_files: failed to create proc files!\n");
        return -1;
    }

    if(!proc_create_data("Version", S_IRUGO, p0, &proc_ro_str_fops, NVRAM_ULVERSION))
        goto err_create;

    if(!proc_create_data("ulBoardStuffOption", S_IWUSR | S_IRUGO, p0,
            &proc_rw_str_fops, NVRAM_ULBOARDSTUFFOPTION))
        goto err_create;

    if(!proc_create_data("Bootline", S_IWUSR | S_IRUGO, p0,
            &proc_rw_str_fops, NVRAM_SZBOOTLINE))
        goto err_create;

    if(!proc_create_data("BoardId", S_IWUSR | S_IRUGO, p0,
            &proc_rw_str_fops, NVRAM_SZBOARDID))
        goto err_create;

    if(!proc_create_data("gponSerialNumber", S_IRUGO, p0, &proc_ro_str_fops,
            NVRAM_GPONSERIALNUMBER))
        goto err_create;

    if(!proc_create_data("gponPassword", S_IRUGO, p0, &proc_ro_str_fops,
            NVRAM_GPONPASSWORD))
        goto err_create;

    if(!proc_create_data("wpsDevicePin", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops,
            NVRAM_WPSDEVICEPIN))
        goto err_create;

    if(!proc_create_data("wlanParams", S_IRUGO, p0, &proc_ro_str_fops,
            NVRAM_WLANPARAMS))
        goto err_create;

    if(!proc_create_data("wlanFeature", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops,
            NVRAM_WLANFEAT))
        goto err_create;

    if(!proc_create_data("VoiceBoardId", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops,
            NVRAM_SZVOICEBOARDID))
        goto err_create;

    if(!proc_create_data("AuthKey", S_IWUSR | S_IRUGO, p0,
            &proc_rw_str_fops, NVRAM_AUTHKEY))
        goto err_create;

    if(!proc_create_data("DesKey", S_IWUSR | S_IRUGO, p0,
            &proc_rw_str_fops, NVRAM_DESKEY))
        goto err_create;

    if(!proc_create_data("WpaKey", S_IWUSR | S_IRUGO, p0,
            &proc_rw_str_fops, NVRAM_WPAKEY))
        goto err_create;

    if(!proc_create_data("SerialNumber", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops,
            NVRAM_SERIALNO))
        goto err_create;

    if(!proc_create_data("rfpi", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops, NVRAM_RFPI))
        goto err_create;

    if(!proc_create_data("bcm_mod_dev", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops,
            NVRAM_MODDEV))
        goto err_create;

    if(!proc_create_data("bcm_def_freq", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops,
            NVRAM_DEFFREQ))
        goto err_create;

    if(!proc_create_data("fixed_emc", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops,
            NVRAM_FIXEDEMC))
        goto err_create;

    if(!proc_create_data("dslAnnex", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops,
            NVRAM_DSLANNEX))
        goto err_create;

    if(!proc_create_data("iVersion", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops,
            NVRAM_IVERSION))
        goto err_create;

    if(!proc_create_data("iAntenna", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops,
            NVRAM_IANTENNA))
        goto err_create;

    if(!proc_create_data("psn", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops,
            NVRAM_PSN))
        goto err_create;

    if(!proc_create_data("pcbasn", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops,
            NVRAM_PCBASN))
        goto err_create;

    if(!proc_create_data("NumMacAddrs", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops,
            NVRAM_ULNUMMACADDRS))
        goto err_create;

    if(!proc_create_data("HV", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops,
            NVRAM_HWVER))
        goto err_create;

    if(!proc_create_data("Production", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops,
            NVRAM_PRODUCTION))
        goto err_create;

    if(!proc_create_data("AcsPassword", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops,
            NVRAM_ACS_PASS))
        goto err_create;

    if(!proc_create_data("Variant", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops,
            NVRAM_VARIANT))
        goto err_create;

    if(!proc_create_data("UserPassword", S_IWUSR | S_IRUGO, p0, &proc_rw_str_fops,
            NVRAM_USER_PASS))
        goto err_create;

#if defined(WIRELESS)
    p1 = proc_create("wl_nand_manufacturer", S_IRUSR, p0,&wl_get_nandmanufacture_proc);
    if (p1 == NULL)
    {
        printk("add_proc_files: failed to create proc files!\n");
        return -1;
    }

#ifdef BUILD_NAND

    p1 = proc_create("wl_nand_mtdname", S_IRUSR, p0,&wl_get_mtdname_proc);
    if (p1 == NULL)
    {
        printk("add_proc_files: failed to create proc files!\n");
        return -1;
    }
#endif
#endif
     p1 = proc_create_data("BaseMacAddr", S_IRUSR, p0, &base_mac_add_proc, mi);

    if (p1 == NULL)
    {
        printk("add_proc_files: failed to create proc files!\n");
        return -1;
    }

     p1 = proc_create_data("bootline", S_IRUSR, p0, &bootline_proc, bootline);

    if (p1 == NULL)
    {
        printk("add_proc_files: failed to create proc files!\n");
        return -1;
    }

    p1 = proc_create("led", S_IWUSR | S_IRUSR, NULL, &led_proc);
    if (p1 == NULL)
        return -1;

#if defined(CONFIG_BCM96838) || defined(CONFIG_BCM96848) 
    p3 = proc_create("show_rdp_mem", S_IRUSR, p0, &rdp_mem_proc);
    if (p3 == NULL)
        return -1;
#endif

    p2 = proc_create("supported_optical_wan_types", S_IRUSR, p0, &supp_optical_wan_types_proc);
    if (p2 == NULL)
        return -1;

#if defined(CONFIG_BCM_WATCHDOG_TIMER)
    p2 = proc_create("watchdog", S_IRUSR|S_IWUSR, p0, &watchdog_proc);
    if (p2 == NULL)
    {
        printk("add_proc_files: failed to create watchdog proc file!\n");
        return -1;
    }
#endif /* defined(CONFIG_BCM_WATCHDOG_TIMER) */

    p4 = proc_create_data("boardid", S_IRUSR, p0, &boardid_proc, boardid);
    if (p4 == NULL)
        return -1;

    p5 = proc_create("socinfo", S_IRUSR, NULL, &socinfo_proc);
    if (p5 == NULL)
        return -1;

    p1 = proc_create("query", S_IRUSR, p0, &base_query_proc);

    if (p1 == NULL)
    {
err_create:
        printk("add_proc_files: failed to create proc files!\n");
        return -1;
    }

#if defined(CONFIG_BCM_FAILSAFE_BOOT)
    p0 = proc_mkdir("boot", NULL);
    if (p0 == NULL) {
        printk("add_proc_files: failed to create proc files!\n");
        return -1;
    }
    p2 = proc_create("failsafe", S_IRUSR|S_IWUSR, p0, &failsafe_boot_proc );
    if (p2 == NULL) {
        printk("add_proc_files: failed to create failsafe proc file!\n");
        return -1;
    }
#endif /* defined(CONFIG_BCM_WATCHDOG_TIMER) */
    return 0;
}

int del_proc_files(void)
{
    remove_proc_entry("nvram", NULL);
    remove_proc_entry("led", NULL);

#if defined(CONFIG_BCM_FAILSAFE_BOOT)
    remove_proc_entry("failsafe", NULL);
#endif
    return 0;
}
