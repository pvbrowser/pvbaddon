/***************************************************************************
 *   Copyright (C) 2006 by TuxPLC					                                 *
 *   Author Stephane JEANNE s.jeanne@tuxplc.net                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "AB.h"
#include "CIP_IOI.h"
#include "ErrCodes.h"
#include "CM.h"

Eip_Connection *_ConnectPLCOverCNET(
		Eip_Session *session,
		Plc_Type Plc,
		BYTE Priority,
		CIP_USINT TimeOut_Ticks,//used to calculate request timeout information
		CIP_UDINT TO_ConnID, //originator's CIP consumed session ID
		CIP_UINT ConnSerialNumber,// session serial number
		CIP_UINT OriginatorVendorID,
		CIP_UDINT OriginatorSerialNumber,
		CIP_USINT TimeOutMultiplier,
		CIP_UDINT RPI,// originator to target packet rate in msec
		CIP_USINT Transport,
		BYTE *path,CIP_USINT pathsize)
{ int pathlen=pathsize+sizeof(ROUTER_PATH);
   CIP_UINT Parameters;
	BYTE *tpath=malloc(pathlen);
	if (tpath==NULL) {CIPERROR(Sys_Error,errno,0);return(NULL);}
	memcpy(tpath,path,pathsize);
	memcpy(tpath+pathsize,&ROUTER_PATH,sizeof(ROUTER_PATH));
	switch (Plc)
	{
		case PLC5:Parameters=0x4302;break;
		case SLC500:Parameters=0x4302;break;
		default:Parameters=0x43f8;
	}
	Eip_Connection *res=_Forward_Open(session,_Priority,_TimeOut_Ticks,TO_ConnID,
	ConnSerialNumber,_OriginatorVendorID,_OriginatorSerialNumber,_TimeOutMultiplier,
	RPI,Parameters,_Transport,tpath,pathlen);
	free(tpath);
	return(res);
}
Eip_Connection *_ConnectPLCOverDHP(		
		Eip_Session *session,
		Plc_Type Plc,
		BYTE Priority,
		CIP_USINT TimeOut_Ticks,//used to calculate request timeout information
		CIP_UDINT TO_ConnID, //originator's CIP consumed session ID
		CIP_UINT ConnSerialNumber,// session serial number
		CIP_UINT OriginatorVendorID,
		CIP_UDINT OriginatorSerialNumber,
		CIP_USINT TimeOutMultiplier,
		CIP_UDINT RPI,// originator to target packet rate in msec
		CIP_USINT Transport,
		DHP_Channel channel,
		BYTE *path,CIP_USINT pathsize)
{ int pathlen=pathsize+sizeof(DHPA_PROXY_PATH);
  CIP_UINT Parameters;
	BYTE *tpath=malloc(pathlen);
	if (tpath==NULL) {CIPERROR(Sys_Error,errno,0);return(NULL);}
	memcpy(tpath,path,pathsize);
	if (channel==Channel_A) memcpy(tpath+pathsize,&DHPA_PROXY_PATH,sizeof(DHPA_PROXY_PATH));
		else memcpy(tpath+pathsize,&DHPB_PROXY_PATH,sizeof(DHPB_PROXY_PATH));
	switch (Plc)
	{
		case PLC5:Parameters=0x4302;break;
		case SLC500:Parameters=0x4302;break;
		default:Parameters=0x43f8;
	}
	Eip_Connection *res=_Forward_Open(session,_Priority,_TimeOut_Ticks,TO_ConnID,
	ConnSerialNumber,_OriginatorVendorID,_OriginatorSerialNumber,_TimeOutMultiplier,
	RPI,Parameters,_Transport,tpath,pathlen);
	free(tpath);
	return(res);
}
