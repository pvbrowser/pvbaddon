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
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "MR.h"
#include "ErrCodes.h"
#include "CIP_Const.h"

// BYTE *_mrbuffer[MAX_MSG_LEN];

int _GetMRExtendedStatus(MR_Reply *MRReply)
{	if (MRReply==NULL) return(-1);
	switch (MRReply->Add_Status_Size)
	{
		case  1:return(*((CIP_INT*)(&(MRReply->Add_Status))));
		case  2:return(*((CIP_DINT*)(&(MRReply->Add_Status))));
		default:return(0);
	}
}
void *_GetMRData(MR_Reply *MRReply)
{	if (MRReply==NULL) return (NULL);
		else return((void *)((void *)MRReply+sizeof(*MRReply)+2*(MRReply->Add_Status_Size)));
}
int _GetMRDataSize(Encap_Header *header)
{	int size=_GetMRReplySize(header);
	MR_Reply *reply=_GetMRReply(header);
	if (reply!=NULL) return(size-sizeof(MR_Reply)-2*(reply->Add_Status_Size));
		else return(EX_Error);
}
MR_Reply *_GetMRReply(Encap_Header *header)
{ Eip_Item *dataitem=_GetDataItem(header);
	if (dataitem==NULL) return(NULL);
	switch (dataitem->Type_Id)
	{
		case ItemId_UCM:return((MR_Reply*)((void*)dataitem+sizeof(Eip_UDI)));
			break;
		case ItemId_ConnectedTP:return((MR_Reply*)((void*)dataitem+sizeof(Eip_CDI)));
			break;
		case ItemId_OTSocketInfo:return((MR_Reply*)((void*)dataitem+sizeof(Eip_SII)));
			break;
		default:return((MR_Reply*)((void*)dataitem+sizeof(Eip_Item)));
			break;
	}
}
int _GetMRReplySize(Encap_Header *header)
{	Eip_Item *dataitem=_GetDataItem(header);
	if (dataitem==NULL) return(0);
	switch (dataitem->Type_Id)
	{
		case ItemId_UCM:return(dataitem->Length);
			break;
		case ItemId_ConnectedTP:return(dataitem->Length-sizeof(CIP_INT)); // size of packet id
			break;
		case ItemId_OTSocketInfo:return(dataitem->Length-sizeof(Eip_SII));
			break;
		default:return(dataitem->Length);
			break;
	}
}
MR_Request *_BuildMRRequest(CIP_USINT service,BYTE *path,CIP_USINT requestpathsize,
										void *requestdata,int requestdatasize,int *requestsize)
{ int mrsize=_GetMRRequestSize(requestpathsize,requestdatasize);
	if (mrsize<=0)
	{
		CIPERROR(Internal_Error,E_MR,__LINE__)
	}
	MR_Request *request=malloc(mrsize);
	if (request==NULL)
	{
		CIPERROR(Sys_Error,errno,0);
		return(NULL);
	}
	memset(request,0,mrsize);
	request->Service=service;
	request->Request_Path_Size=requestpathsize/2;
	memcpy((void *)request+sizeof(MR_Request),path,requestpathsize);
	memcpy((void *)request+sizeof(MR_Request)+requestpathsize,requestdata,requestdatasize);
	if (requestsize!=NULL) *requestsize=mrsize;
	return(request);
}
MR_Reply *_ExSendMRRequest(Eip_Session *session,MR_Request *request,int size,int *replysize)
{
	Eip_Item adressitem;
	Eip_Item dataitem;
	
	// adressitem
	adressitem.Type_Id=ItemId_Null;
	adressitem.Length=0;
	// dataitem
	dataitem.Type_Id=ItemId_UCM;
	dataitem.Length=size;
	
	Encap_Header *reply=_SendRRData(session,&adressitem,NULL,&dataitem,request);
	
	if (reply==NULL) return(NULL); // no response
	MR_Reply *mrrep=_GetMRReply(reply);
	if (mrrep!=NULL)
	{
		int size=_GetMRReplySize(reply);
		MR_Reply *result=malloc(size);
		if (result==NULL)
		{
			CIPERROR(Sys_Error,errno,0);
			free(reply);
			return(NULL);
		}
		memcpy(result,mrrep,size);
		free(reply);
		CIPERROR(MR_Error,result->General_Status,_GetMRExtendedStatus(result));
		if (replysize!=NULL) *replysize=size;
		return(result);
	}else 
	{
		CIPERROR(EIP_Error,reply->Status,0);
		free(reply);
		return(NULL);
	}
}
MR_Reply *_SendMRRequest(Eip_Session *session,CIP_USINT service,BYTE *path,
                    CIP_USINT requestpathsize,void *requestdata,int requestdatasize,int *replysize)
{	int mrsize=0;
	MR_Request *request=_BuildMRRequest(service,path,requestpathsize,requestdata,requestdatasize,&mrsize);
	MR_Reply *reply=_ExSendMRRequest(session,request,mrsize,replysize);
	free(request);
	return(reply);
}
