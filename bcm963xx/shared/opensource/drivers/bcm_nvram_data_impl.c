/*
<:copyright-BRCM:2017:DUAL/GPL:standard 

   Copyright (c) 2017 Broadcom 
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

/*
 ***************************************************************************
 * File Name  : bcm_nvram_data_impl.c
 *
 * Description: This file contains the nvram_data APIs for bcm63xx board. 
 *
 *
 ***************************************************************************/

#if !defined (_CFE_)
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/crc32.h>
#endif
#include <bcmtypes.h>
#include <bcm_map_part.h>
#include <board.h>
#include <bcmTag.h>

enum
{
	INTEGER_STRING,
	INT8_STRING,
	INT16_STRING,
	SHORT_STRING,
	STRING,
	HEX_STRING,
	MAC_ID_STRING,
	COMMA_SEPARATED_INTEGER_STRING,
	COMMA_SEPARATED_HEX_INTEGER_STRING,
	COMMA_SEPARATED_SHORT_STRING,
	COMMA_SEPARATED_STRING,
	BINARY_DATA,
	MAX_TYPE
};

struct nvdata_params_struct
{
	char *param;
	void* offset;
	int size;
	int type;
};

static struct nvdata_params_struct nps[]=
{
	{NVRAM_ULVERSION, &((NVRAM_DATA*)0)->ulVersion, sizeof(((NVRAM_DATA*)0)->ulVersion), INTEGER_STRING},
	{NVRAM_SZBOOTLINE, &((NVRAM_DATA*)0)->szBootline, sizeof(((NVRAM_DATA*)0)->szBootline), STRING},
	{NVRAM_SZBOARDID, &((NVRAM_DATA*)0)->szBoardId, sizeof(((NVRAM_DATA*)0)->szBoardId), STRING},
	{NVRAM_ULMAINTPNUM, &((NVRAM_DATA*)0)->ulMainTpNum, sizeof(((NVRAM_DATA*)0)->ulMainTpNum), INTEGER_STRING },
	{NVRAM_ULPSISIZE, &((NVRAM_DATA*)0)->ulPsiSize, sizeof(((NVRAM_DATA*)0)->ulPsiSize), INTEGER_STRING },
	{NVRAM_ULNUMMACADDRS, &((NVRAM_DATA*)0)->ulNumMacAddrs, sizeof(((NVRAM_DATA*)0)->ulNumMacAddrs), INTEGER_STRING},
	{NVRAM_UCABASEMACADDR, &((NVRAM_DATA*)0)->ucaBaseMacAddr, sizeof(((NVRAM_DATA*)0)->ucaBaseMacAddr), MAC_ID_STRING},
	{NVRAM_PAD, &((NVRAM_DATA*)0)->pad, sizeof(((NVRAM_DATA*)0)->pad), INT8_STRING}, //unused
	{NVRAM_BACKUPPSI, &((NVRAM_DATA*)0)->backupPsi, sizeof(((NVRAM_DATA*)0)->backupPsi), INT8_STRING },
	{NVRAM_ULCHECKSUMV4, &((NVRAM_DATA*)0)->ulCheckSumV4, sizeof(((NVRAM_DATA*)0)->ulCheckSumV4), INTEGER_STRING },
	{NVRAM_GPONSERIALNUMBER, &((NVRAM_DATA*)0)->gponSerialNumber, sizeof(((NVRAM_DATA*)0)->gponSerialNumber), STRING }, //??
	{NVRAM_GPONPASSWORD, &((NVRAM_DATA*)0)->gponPassword, sizeof(((NVRAM_DATA*)0)->gponPassword), STRING}, //??
	{NVRAM_WPSDEVICEPIN, &((NVRAM_DATA*)0)->wpsDevicePin, sizeof(((NVRAM_DATA*)0)->wpsDevicePin), STRING}, //??
	{NVRAM_WLANPARAMS, &((NVRAM_DATA*)0)->wlanParams, sizeof(((NVRAM_DATA*)0)->wlanParams), HEX_STRING}, //??
	{NVRAM_ULSYSLOGSIZE, &((NVRAM_DATA*)0)->ulSyslogSize, sizeof(((NVRAM_DATA*)0)->ulSyslogSize), INTEGER_STRING },
	{NVRAM_ULNANDPARTOFSKB, &((NVRAM_DATA*)0)->ulNandPartOfsKb, sizeof(((NVRAM_DATA*)0)->ulNandPartOfsKb), COMMA_SEPARATED_INTEGER_STRING },// separated
	{NVRAM_ULNANDPARTSIZEKB, &((NVRAM_DATA*)0)->ulNandPartSizeKb, sizeof(((NVRAM_DATA*)0)->ulNandPartSizeKb), COMMA_SEPARATED_INTEGER_STRING },// separated
	{NVRAM_SZVOICEBOARDID, &((NVRAM_DATA*)0)->szVoiceBoardId, sizeof(((NVRAM_DATA*)0)->szVoiceBoardId), STRING},
	{NVRAM_AFEID, &((NVRAM_DATA*)0)->afeId, sizeof(((NVRAM_DATA*)0)->afeId), COMMA_SEPARATED_HEX_INTEGER_STRING},
	{NVRAM_OPTICRXPWRREADING, &((NVRAM_DATA*)0)->opticRxPwrReading, sizeof(((NVRAM_DATA*)0)->opticRxPwrReading), INT16_STRING},
	{NVRAM_OPTICRXPWROFFSET, &((NVRAM_DATA*)0)->opticRxPwrOffset, sizeof(((NVRAM_DATA*)0)->opticRxPwrOffset), INT16_STRING},
	{NVRAM_OPTICTXPWRREADING, &((NVRAM_DATA*)0)->opticTxPwrReading, sizeof(((NVRAM_DATA*)0)->opticTxPwrReading), INT16_STRING},
	{NVRAM_UCUNUSED2, &((NVRAM_DATA*)0)->ucUnused2, sizeof(((NVRAM_DATA*)0)->ucUnused2), INTEGER_STRING},
	{NVRAM_UCFLASHBLKSIZE, &((NVRAM_DATA*)0)->ucFlashBlkSize, sizeof(((NVRAM_DATA*)0)->ucFlashBlkSize), INT8_STRING},
	{NVRAM_UCAUXFSPERCENT, &((NVRAM_DATA*)0)->ucAuxFSPercent, sizeof(((NVRAM_DATA*)0)->ucAuxFSPercent), INT8_STRING},
	{NVRAM_UCUNUSED3, &((NVRAM_DATA*)0)->ucUnused3, sizeof(((NVRAM_DATA*)0)->ucUnused3), INTEGER_STRING},
	{NVRAM_ULBOARDSTUFFOPTION, &((NVRAM_DATA*)0)->ulBoardStuffOption, sizeof(((NVRAM_DATA*)0)->ulBoardStuffOption), INTEGER_STRING},
	{NVRAM_ALLOCS, &((NVRAM_DATA*)0)->allocs, sizeof(((NVRAM_DATA*)0)->allocs), HEX_STRING},
	{NVRAM_ULMEMORYCONFIG, &((NVRAM_DATA*)0)->ulMemoryConfig, sizeof(((NVRAM_DATA*)0)->ulMemoryConfig), INTEGER_STRING},
	{NVRAM_PART_INFO, &((NVRAM_DATA*)0)->part_info, sizeof(((NVRAM_DATA*)0)->part_info), COMMA_SEPARATED_SHORT_STRING},
	{NVRAM_ALLOC_DHD, &((NVRAM_DATA*)0)->alloc_dhd, sizeof(((NVRAM_DATA*)0)->alloc_dhd), HEX_STRING},
	{NVRAM_ULFEATURES, &((NVRAM_DATA*)0)->ulFeatures, sizeof(((NVRAM_DATA*)0)->ulFeatures), INTEGER_STRING},
	{NVRAM_CHUNUSED, &((NVRAM_DATA*)0)->chUnused, sizeof(((NVRAM_DATA*)0)->chUnused), INTEGER_STRING},
	{NVRAM_ULCHECKSUM, &((NVRAM_DATA*)0)->ulCheckSum, sizeof(((NVRAM_DATA*)0)->ulCheckSum), HEX_STRING},
	{NVRAM_WLANFEAT, &((NVRAM_DATA*)0)->wlanParams + sizeof(((NVRAM_DATA*)0)->wlanParams) - 1, sizeof(char), HEX_STRING},
	{NVRAM_AUTHKEY, &((NVRAM_DATA*)0)->szAuthKey, sizeof(((NVRAM_DATA*)0)->szAuthKey), STRING},
	{NVRAM_DESKEY, &((NVRAM_DATA*)0)->szDesKey, sizeof(((NVRAM_DATA*)0)->szDesKey), STRING},
	{NVRAM_WPAKEY, &((NVRAM_DATA*)0)->szWpaKey, sizeof(((NVRAM_DATA*)0)->szWpaKey), STRING},
	{NVRAM_SERIALNO, &((NVRAM_DATA*)0)->szSerialNumber, sizeof(((NVRAM_DATA*)0)->szSerialNumber), STRING},
	{NVRAM_RFPI, &((NVRAM_DATA*)0)->rfpi, sizeof(((NVRAM_DATA*)0)->rfpi), HEX_STRING},
	{NVRAM_MODDEV, &((NVRAM_DATA*)0)->bcm_mod_dev, sizeof(((NVRAM_DATA*)0)->bcm_mod_dev), HEX_STRING},
	{NVRAM_DEFFREQ, &((NVRAM_DATA*)0)->bcm_def_freq, sizeof(((NVRAM_DATA*)0)->bcm_def_freq), HEX_STRING},
	{NVRAM_FIXEDEMC, &((NVRAM_DATA*)0)->fixed_emc, sizeof(((NVRAM_DATA*)0)->fixed_emc), HEX_STRING},
	{NVRAM_DSLANNEX, &((NVRAM_DATA*)0)->dslAnnex, sizeof(((NVRAM_DATA*)0)->dslAnnex), STRING},
	{NVRAM_IVERSION, &((NVRAM_DATA*)0)->iVersion, sizeof(((NVRAM_DATA*)0)->iVersion), HEX_STRING},
	{NVRAM_IANTENNA, &((NVRAM_DATA*)0)->iAntenna, sizeof(((NVRAM_DATA*)0)->iAntenna), HEX_STRING},
	{NVRAM_PSN, &((NVRAM_DATA*)0)->psn, sizeof(((NVRAM_DATA*)0)->psn), STRING},
	{NVRAM_PCBASN, &((NVRAM_DATA*)0)->pcbasn, sizeof(((NVRAM_DATA*)0)->pcbasn), STRING},
	{NVRAM_HWVER, &((NVRAM_DATA*)0)->hwVer, sizeof(((NVRAM_DATA*)0)->hwVer), STRING},
	{NVRAM_PRODUCTION, &((NVRAM_DATA*)0)->production, sizeof(((NVRAM_DATA*)0)->production), HEX_STRING},
	{NVRAM_ACS_PASS, &((NVRAM_DATA*)0)->acsPassword, sizeof(((NVRAM_DATA*)0)->acsPassword), STRING},
	{NVRAM_VARIANT, &((NVRAM_DATA*)0)->variant, sizeof(((NVRAM_DATA*)0)->variant), STRING},
	{NVRAM_USER_PASS, &((NVRAM_DATA*)0)->userPass, sizeof(((NVRAM_DATA*)0)->userPass), STRING},
	{NULL,NULL, 0, 0}
};

//void updateInMemNvramData(const unsigned char *data, int len, int offset);
static NVRAM_DATA* inMemNvramData_ptr;

static void init_inMemNvramData(void)
{
	if(inMemNvramData_ptr == NULL) 
		inMemNvramData_ptr=get_inMemNvramData();
}

int eNvramGet(char *param, char *value, int len)
{
struct nvdata_params_struct *nps_ptr=nps;
char *ptr=NULL, filler=' ';
int total_used=0,index, used, to_copy;

	if(is_cfe_boot())
	{

		init_inMemNvramData();

		while(nps_ptr->param != NULL)
		{
			if(param == nps_ptr->param || strcmp(param, nps_ptr->param) == 0)
			{
				// always assumed inMemNvramData is pre populated
				ptr=(char *)inMemNvramData_ptr + (long)(int*)nps_ptr->offset;
				total_used=0;
				index=0;
				to_copy=nps_ptr->size;
				switch(nps_ptr->type)
				{
					case INTEGER_STRING:
						total_used=snprintf(value, len, "%d", *(int*)ptr);
						break;
					case INT8_STRING:
						total_used=snprintf(value, len, "%hhd", *(char*)ptr);
						break;
					case INT16_STRING:
						total_used=snprintf(value, len, "%hd", *(short*)ptr);
						break;
					case STRING:
						if (len > to_copy) len = to_copy + 1;					// Ensure ending null. Might be missing in nvram.
						total_used=snprintf(value, len, "%s", ptr);
						if (total_used > to_copy) total_used = to_copy;				// String were truncated.
						break;
					case MAC_ID_STRING:
						filler=':';
						to_copy=6;//mac_id size
					//intentionally left out a break statement so the rest of the code will execute
					case HEX_STRING:
						while(len > 3 && index < to_copy)
						{
							used=snprintf(value+total_used, len,"%02hhx%c", ptr[index], filler );
							index++;
							total_used+=used;
							len-=used;
							if(to_copy-index == 1) filler='\0';
						}
						break;
					case COMMA_SEPARATED_INTEGER_STRING:
						total_used=0;
						while(len > 1 && index < nps_ptr->size)
						{
							used=snprintf(value+total_used,len, "%d;", *((int*)(ptr+index)));
							index+=sizeof(int);
							total_used+=used;
							len-=used;
						}
						break;
					case COMMA_SEPARATED_HEX_INTEGER_STRING:
						total_used=0;
						while(len > 1 && index < nps_ptr->size)
						{
							used=snprintf(value+total_used,len, "%x;", *((int*)(ptr+index)));
							index+=sizeof(int);
							total_used+=used;
							len-=used;
						}
						break;
					case COMMA_SEPARATED_SHORT_STRING:
						total_used=0;
						while(len > 1 && index < nps_ptr->size)
						{
							used=snprintf(value+total_used,len, "%hi:", *((short*)(ptr+index)));
							index+=sizeof(short);
							total_used+=used;
							len-=used;
						}
						break;
				}
				break;
			}
			nps_ptr++;
		}
	}
	else
	{
			// uboot?
	}
return total_used;
}

int eNvramSet(char *param, char *value)
{

struct nvdata_params_struct *nps_ptr=nps;
char *ptr=NULL;
int total_used=0,index,ret=0,temp;

	if(is_cfe_boot())
	{

		init_inMemNvramData();

		while(nps_ptr->param != NULL)
		{
			if(param == nps_ptr->param || strcmp(param, nps_ptr->param) == 0)
			{
				// always assumed inMemNvramData is pre populated
				ptr=(char *)inMemNvramData_ptr + (long)(int*)nps_ptr->offset;
				total_used=0;
				index=0;
				switch(nps_ptr->type)
				{
					case INTEGER_STRING:
						sscanf(value, "%u", (unsigned int*) ptr);
						break;
					case INT8_STRING:
						sscanf(value, "%d", &temp);
						if(temp <= 255)
						{
							ptr[0]=temp&0xff;
						}
						break;
					case INT16_STRING:
						sscanf(value, "%hi", (short*)ptr);
						break;
					case STRING:
						strncpy(ptr, value, nps_ptr->size);
						break;
					case MAC_ID_STRING:
						if(strchr(value, ':'))
							sscanf(value, "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
								&ptr[0], &ptr[1],&ptr[2],&ptr[3],&ptr[4],&ptr[5]);
						else if(strchr(value, '-'))
							sscanf(value, "%02hhx-%02hhx-%02hhx-%02hhx-%02hhx-%02hhx",
								&ptr[0], &ptr[1],&ptr[2],&ptr[3],&ptr[4],&ptr[5]);

						else
							sscanf(value, "%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx",
								&ptr[0], &ptr[1],&ptr[2],&ptr[3],&ptr[4],&ptr[5]);
						total_used=6;

						break;
					case HEX_STRING:
						while(total_used < nps_ptr->size && index < strlen(value) )
						{
							sscanf(value+index, "%02hhx", ptr+total_used);
							index+=3;//skip 2 digits and a space
							total_used++;
						}
						break;
					case COMMA_SEPARATED_INTEGER_STRING:
						total_used=0;
						while(value != NULL && total_used < nps_ptr->size)
						{
							sscanf(value, "%d;", (int*)ptr+total_used);
							total_used+=sizeof(int);
							value=strchr(value,';');
						}
						break;
					case COMMA_SEPARATED_HEX_INTEGER_STRING:
						total_used=0;
						while(value != ((void *)0) && total_used < nps_ptr->size)
						{
							sscanf(value, "%x;", (int*)ptr+total_used);
							total_used+=sizeof(int);
							value=strchr(value,';');
						}
						break;
					case COMMA_SEPARATED_SHORT_STRING:
						total_used=0;
						while(value != NULL && total_used < nps_ptr->size)
						{
							sscanf(ptr+total_used, "%hi;", (short*)value+total_used);
							total_used+=sizeof(short);
							value=strchr(value,';');
						}
					break;

				}
				break;
			}

			nps_ptr++;
		}
		inMemNvramData_ptr->ulCheckSum=0;
		ret=total_used;
	}
	else
	{
			// uboot?
	}
return ret;
}
