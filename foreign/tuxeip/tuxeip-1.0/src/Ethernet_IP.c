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

#include "Ethernet_IP.h"
#include "SendData.h"
#include "EIP_Const.h"
#include "ErrCodes.h"
#include "CIP_Const.h"

void _AddRR(Encap_Header *request,CIP_UDINT interface_handle,CIP_UINT timeout);
void _AddCPF(Encap_Header *request,Eip_Item *adressitem,void *adress,Eip_Item *dataitem,void *data);
int _AddItem(Encap_Header *request,Eip_Item *item,void *data);

int IsEIP(void *Data)
{
	Eip_Command Command;
  Command=((Encap_Header *)Data)->Command;
  return((Command==EIP_NOP) ||
					(Command==EIP_LISTTARGETS) ||
					(Command==EIP_LISTSERVICES) ||
					(Command==EIP_LISTIDENTITY) ||
					(Command==EIP_LISTINTERFACES) ||
					(Command==EIP_REGISTERSESSION) ||
					(Command==EIP_UNREGISTERSESSION) ||
					(Command==EIP_SENDRRDATA) ||
					(Command==EIP_SENDUNITDATA) ||
					(Command==EIP_INDICATESTATUS) ||
					(Command==EIP_CANCEL));
}

CIP_UDINT _GetEipStatus(Encap_Header *header)
{
	return(header->Status);
}
Eip_Common_Packet *_GetEipCommonPacket(Encap_Header *header)
{
	return((Eip_Common_Packet *)(_GetEipCPF(header)));
}
Eip_CPF *_GetEipCPF(Encap_Header *header)
{
	if ((header==NULL)||(header->Length<2)) return(NULL);
	switch (header->Command)
	{
		case EIP_LISTSERVICES:
		case EIP_LISTIDENTITY:
		case EIP_LISTINTERFACES:return ((Eip_CPF*)((void*)header+sizeof(Encap_Header)));
		case EIP_SENDRRDATA:
		case EIP_SENDUNITDATA:return((Eip_CPF*)((void*)header+sizeof(SendRRData_Request)));
		default :return(NULL);
	}
}
Eip_Item *_GetItem(Eip_Common_Packet *CP,int id)
{
	Eip_Item *item=(Eip_Item *)(&CP->Adress);
 	int i;
  if ((CP==NULL)||(id>CP->Count)) return (NULL);
  for(i=0;i++;i=id)
  {
    item=(void*)item+item->Length;
  }
  return(item);
}
Eip_Item *_GetAdressItem(Encap_Header *header)
{ 
	Eip_Common_Packet *CP=_GetEipCommonPacket(header);
	if (CP==NULL) return(NULL);
	return(&CP->Adress);
}
Eip_Item *_GetDataItem(Encap_Header *header)
{ 
	Eip_Item *adressitem=_GetAdressItem(header);
	if (adressitem==NULL) return(NULL);
	return(((void *)adressitem+sizeof(Eip_Item)+adressitem->Length));
}
ListInterface_Reply *_GetInterfaces(Encap_Header *header)
{
	if ((header==NULL)||(header->Length<2)) return(NULL);
		else return((ListInterface_Reply*)(header));
}
ListServices_Reply *_GetServices(Encap_Header *header)
{
	if ((header==NULL)||(header->Length<2)) return(NULL);
		else return((ListServices_Reply*)(header));	
}
ListIdentity_Reply *_GetIdentity(Encap_Header *header)
{
	if ((header==NULL)||(header->Length<2)) return(NULL);
		else return((ListIdentity_Reply*)(header));	
}
Eip_Session *_OpenSession(char *serveur,int port,int buffer_len,int timeout)
{ Eip_Session *session=NULL;
	CIPERROR(0,0,0);
	session=malloc(sizeof(Eip_Session));
	if (session==NULL) 
	{
		CIPERROR(Sys_Error,errno,0);
		return(NULL);
	}
	memset(session,0,sizeof(Eip_Session));
	session->sock=_CipOpenSock(serveur,port);
	session->timeout=timeout;
	if (session->sock<0) 
	{
		CIPERROR(Internal_Error,E_ConnectionFailed,0);
		free(session);
		return(NULL);
	}
	 else return(session);
}
void CloseSession(Eip_Session *session)
{	
	CIPERROR(0,0,0);
	close(session->sock);
	free(session);
}
int _RegisterSession(Eip_Session *session)
{	RegisterSession_Request request;
	RegisterSession_Reply *reply=NULL;
	int res;
	CIPERROR(0,0,0);
	session->Session_Handle=0;
	memset(&request,0,sizeof(RegisterSession_Request));
	request.Header.Session_Handle=session->Session_Handle;
	request.Header.Sender_ContextL=session->Sender_ContextL;
	request.Header.Sender_ContextH=session->Sender_ContextH;
	request.Header.Command=EIP_REGISTERSESSION;
	request.Header.Length=4;
	request.Protocol_Version=EIP_VERSION;
	if ((res=CipSendData(session->sock,(Encap_Header*)&request))<0) return(res);

	if ((reply=(RegisterSession_Reply*)CipRecvData(session->sock,session->timeout))==NULL)
	{
		CIPERROR(Internal_Error,E_TimeOut,0);
		return(EX_Error);
	}
	if (reply->Header.Command!=EIP_REGISTERSESSION)
		{
			CIPERROR(Internal_Error,E_UnsolicitedMsg,0);
			free(reply);
			return(EX_Error);
		}
	CIPERROR(EIP_Error,reply->Header.Status,0);
	if (reply->Header.Status==EIP_SUCCESS) session->Session_Handle=reply->Header.Session_Handle;
	res=reply->Header.Status;
	free(reply);
	return(res);
}
int _UnRegisterSession(Eip_Session *session)
{	UnRegisterSession_Request request;
	CIPERROR(0,0,0);
	memset(&request,0,sizeof(UnRegisterSession_Request));
	request.Session_Handle=session->Session_Handle;
	request.Sender_ContextL=session->Sender_ContextL;
	request.Sender_ContextH=session->Sender_ContextH;
	request.Command=EIP_UNREGISTERSESSION;
	return(CipSendData(session->sock,(Encap_Header*)(&request)));
}
ListServices_Reply *_ListServices(Eip_Session *session)
{	ListServices_Request request;
  ListServices_Reply *reply=NULL;
  int res;
	CIPERROR(0,0,0);
	memset(&request,0,sizeof(request));
	request.Session_Handle=session->Session_Handle;
	request.Sender_ContextL=session->Sender_ContextL;
	request.Sender_ContextH=session->Sender_ContextH;
	request.Command=EIP_LISTSERVICES;
	if ((res=CipSendData(session->sock,(Encap_Header*)(&request)))<0) return(NULL);
	if ((reply=(ListServices_Reply*)CipRecvData(session->sock,session->timeout))==NULL)
	{
		CIPERROR(Internal_Error,E_TimeOut,0);
		return(NULL);
	}
	if (reply->Header.Command!=EIP_LISTSERVICES)
	{
		CIPERROR(Internal_Error,E_UnsolicitedMsg,0);
		free(reply);
		return(NULL);
	}
	CIPERROR(EIP_Error,reply->Header.Status,0);
	if (reply->Header.Status!=0) {free(reply);return(NULL);}
		else return(reply);
}
ListIdentity_Reply *_ListIdentity(Eip_Session *session)
{	int res;
	ListIdentity_Request request;
	ListIdentity_Reply *reply=NULL;
  CIPERROR(0,0,0);
	memset(&request,0,sizeof(request));
	request.Session_Handle=session->Session_Handle;
	request.Sender_ContextL=session->Sender_ContextL;
	request.Sender_ContextH=session->Sender_ContextH;
	request.Command=EIP_LISTIDENTITY;
	if ((res=CipSendData(session->sock,(Encap_Header*)(&request)))<0) return(NULL);
	if ((reply=(ListIdentity_Reply*)CipRecvData(session->sock,session->timeout))==NULL)
	{
		CIPERROR(Internal_Error,E_TimeOut,0);
		return(NULL);
	}
	if (reply->Header.Command!=EIP_LISTIDENTITY)
	{
		CIPERROR(Internal_Error,E_UnsolicitedMsg,0);
		free(reply);
		return(NULL);
	}
	CIPERROR(EIP_Error,reply->Header.Status,0);
	if (reply->Header.Status!=0) {free(reply);return(NULL);}
		else return(reply);
}
ListInterface_Reply *_ListInterfaces(Eip_Session *session)
{	int res;
	ListInterface_Request request;
	ListInterface_Reply *reply=NULL;
  CIPERROR(0,0,0);
	memset(&request,0,sizeof(request));
	request.Session_Handle=session->Session_Handle;
	request.Sender_ContextL=session->Sender_ContextL;
	request.Sender_ContextH=session->Sender_ContextH;
	request.Command=EIP_LISTINTERFACES;
	if ((res=CipSendData(session->sock,(Encap_Header*)(&request)))<0) return(NULL);
	if ((reply=(ListInterface_Reply*)CipRecvData(session->sock,session->timeout))==NULL)
	{
		CIPERROR(Internal_Error,E_TimeOut,0);
		return(NULL);
	}
	if (reply->Header.Command!=EIP_LISTINTERFACES)
	{
		CIPERROR(Internal_Error,E_UnsolicitedMsg,0);
		free(reply);
		return(NULL);
	}
	CIPERROR(EIP_Error,reply->Header.Status,0);
	if (reply->Header.Status!=0) {free(reply);return(NULL);}
		else return(reply);
}

void _AddRR(Encap_Header *request,CIP_UDINT interface_handle,CIP_UINT timeout)
{
	_AddDINT2Header(request,interface_handle);
	_AddINT2Header(request,timeout);
}
int _GetItemSize(Eip_Item *item)
{
	switch (item->Type_Id)
	{
		case ItemId_Null :return(sizeof(Eip_NAI));
		//case ItemId_ListIdentityResponse :taille=sizeof();break;
		case ItemId_ConnectionBased :return(sizeof(Eip_CAI));
		case ItemId_ConnectedTP :return(sizeof(Eip_CDI));
		case ItemId_UCM :return(sizeof(Eip_UDI));
		//case ItemId_ListServiceResponse :taille=sizeof();break;
		case ItemId_OTSocketInfo :
		case ItemId_TOSocketInfo :return(sizeof(Eip_SII));
		case ItemId_Sequenced :return(sizeof(Eip_SAI));
		default:return(0);
	}
}
int _AddItem(Encap_Header *request,Eip_Item *item,void *data)
{ int taille=_GetItemSize(item);
	int datasize=0;
	if (taille==0)
	{
		CIPERROR(Internal_Error,E_ItemUnknow,0);
		return(EX_Error);
	};	
	datasize=item->Length;
	item->Length+=taille-sizeof(Eip_Item);	
	if (data!=NULL)
	{
		_AddHeader(request,item,taille);
		if (item->Length>0) _AddHeader(request,data,datasize);
	} else _AddHeader(request,item,taille+datasize);
	return(item->Length);
}
void _AddCPF(Encap_Header *request,Eip_Item *adressitem,void *adress,
										Eip_Item *dataitem,void *data)
{
	_AddINT2Header(request,2);
	_AddItem(request,adressitem,adress);
	_AddItem(request,dataitem,data);	
}
Encap_Header *_BuildRequest(Eip_Session *session,Eip_Item *adressitem,void *adress,
										Eip_Item *dataitem,void *data,int timeout)
{ 
	CIPERROR(0,0,0);
	LogCip(LogTrace,"->Entering BuildRequest \n");
	int requestsize=sizeof(SendData_Request)+sizeof(CIP_UINT)+//sizeof(Eip_Common_Packet)+
	_GetItemSize(adressitem)+adressitem->Length+_GetItemSize(dataitem)+dataitem->Length;
	Encap_Header *request=malloc(requestsize);
	if (request==NULL)
	{
		CIPERROR(Sys_Error,errno,0);
		LogCip(LogTrace,"!Exiting BuildRequest with error : %s\n",_cip_err_msg);
		return(NULL);
	}
	memset(request,0,requestsize);
	request->Length=sizeof(CIP_UDINT)+/*Interface_Handle*/
									sizeof(CIP_UINT);/*Timeout*/
	request->Session_Handle=session->Session_Handle;
	request->Sender_ContextL=session->Sender_ContextL;
	request->Sender_ContextH=session->Sender_ContextH;
	((SendData_Request*)request)->Timeout=timeout/1000;
	_AddCPF(request,adressitem,adress,dataitem,data);
	FlushCipBuffer(LogDebug,request,requestsize);
	LogCip(LogTrace,"<-Exiting BuildRequest : size=%d (%p)\n",requestsize,request);
	return(request);
}
int _SendData(Eip_Session *session,CIP_UINT command,
							Eip_Item *adressitem,void *adress,
							Eip_Item *dataitem,void *data)
{
	CIPERROR(0,0,0);
	LogCip(LogTrace,"->Entering SendData \n");
	Encap_Header *request=_BuildRequest(session,adressitem,adress,dataitem,data,session->timeout);
	if (request==NULL)
	{
		CIPERROR(Sys_Error,errno,0);
		LogCip(LogTrace,"!Exiting SendData with error : %s\n",_cip_err_msg);
		return(EX_Error);
	}
	request->Command=command;
	int res=CipSendData(session->sock,request);
	free(request);
	LogCip(LogTrace,"<-Exiting SendData\n");
	return(res);
}
Encap_Header *_SendData_WaitReply(Eip_Session *session,CIP_UINT command,
							Eip_Item *adressitem,void *adress,
							Eip_Item *dataitem,void *data)
{
	CIPERROR(0,0,0);
	LogCip(LogTrace,"->Entering SendData_WaitReply\n");
	Encap_Header *request=_BuildRequest(session,adressitem,adress,dataitem,data,session->timeout);
	if (request==NULL)
	{
		CIPERROR(Sys_Error,errno,0);
		LogCip(LogTrace,"!Exiting SendData with error : %s\n",_cip_err_msg);
		return(NULL);
	}
	request->Command=command;
	Encap_Header *reply=CipSendData_WaitReply(session->sock,request,session->timeout,session->timeout);
	free(request);
	LogCip(LogTrace,"<-Exiting SendData_WaitReply : %p\n",request);
	return(reply);
}
Encap_Header *_SendRRData(Eip_Session *session,
								Eip_Item *adressitem,void *adressdata,
								Eip_Item *dataitem,void *data)
{ 
	return(_SendData_WaitReply(session,EIP_SENDRRDATA,adressitem,adressdata,dataitem,data));
}
Encap_Header *_SendUnitData(Eip_Session *session,
									Eip_Item *adressitem,void *adressdata,
									Eip_Item *dataitem,void *data)
{
	return(_SendData_WaitReply(session,EIP_SENDUNITDATA,adressitem,adressdata,dataitem,data));
}
Eip_CDI *_ConnectedSend( Eip_Session *session,Eip_Connection *connection,
                    void *request,int size)
{ Eip_CAI adressitem;
	Eip_CDI dataitem;
	
	LogCip(LogTrace,"->Entering ConnectedSend \n");
	
	// adressitem
	adressitem.Type_Id=ItemId_ConnectionBased;
	adressitem.Length=0;
	adressitem.CID=connection->OT_ConnID;
	
	// dataitem
	dataitem.Type_Id=ItemId_ConnectedTP;
	dataitem.Packet=++(connection->packet);
	dataitem.Length=size;
	
	Encap_Header *reply=_SendData_WaitReply(session,EIP_SENDUNITDATA,(void*)&adressitem,NULL,(void*)&dataitem,request);
	if (reply!=NULL) 
		{
			Eip_CDI *respdataitem =(Eip_CDI *)_GetDataItem(reply);
			if (respdataitem==NULL) 
			{
				CIPERROR(EIP_Error,reply->Status,0);
				free(reply);
				LogCip(LogTrace,"!Exiting ConnectedSend with error : %s\n",_cip_err_msg);
				return(NULL);
			}
			if ((reply->Command!=EIP_SENDUNITDATA)||(respdataitem->Packet!=connection->packet))
				{
					CIPERROR(Internal_Error,E_UnsolicitedMsg,0);
					free(reply);
					LogCip(LogTrace,"!Exiting ConnectedSend with error : %s\n",_cip_err_msg);
					return(NULL);
				}
			/* Result is OK */
      CIPERROR(EIP_Error,reply->Status,0);
			Eip_CDI *result=malloc(sizeof(Eip_CDI)+respdataitem->Length);
			memcpy(result,respdataitem,sizeof(Eip_Item)+respdataitem->Length);
			LogCip(LogTrace,"<-Exiting ConnectedSend : size=%d (%p)\n",sizeof(Eip_Item)+respdataitem->Length,respdataitem);
			free(reply);
			return(result);
		}
		else 
		{
			LogCip(LogTrace,"!Exiting ConnectedSend with no response\n");
			return(NULL);
		}
}
void _InitHeader(Encap_Header *header,CIP_UDINT session_handle,
								CIP_DINT Sender_ContextL,CIP_DINT Sender_ContextH)
{
	memset(header,0,sizeof(*header));
	header->Session_Handle=session_handle;
	header->Sender_ContextL=Sender_ContextL;
	header->Sender_ContextH=Sender_ContextH;
}
void _FillHeader(Encap_Header *header,CIP_UDINT session_handle,
								CIP_DINT Sender_ContextL,CIP_DINT Sender_ContextH)
{
	header->Session_Handle=session_handle;
	header->Sender_ContextL=Sender_ContextL;
	header->Sender_ContextH=Sender_ContextH;
}

int _AddHeader(Encap_Header *header,void *buffer,int size)
{ 
	if (size>(MAX_MSG_LEN-header->Length-sizeof(*header))) return(0);
	void *pos=((void*)header+sizeof(*header));
	pos+=header->Length;
	memcpy(pos,buffer,size);
	header->Length+=size;
	//LogCip(LogTrace,"AddHeader %d bytes at %p (new size is %d)\n",size,pos,header->Length);
	return(header->Length);
}

int _AddBYTE2Header(Encap_Header *header,BYTE value)
{
	return(_AddHeader(header,&value,sizeof(value)));
}
int _AddINT2Header(Encap_Header *header,CIP_INT value)
{
	return(_AddHeader(header,&value,sizeof(value)));
}
int _AddDINT2Header(Encap_Header *header,CIP_DINT value)
{
	return(_AddHeader(header,&value,sizeof(value)));
}
int _Addtab2Header(Encap_Header *header,BYTE *buff[],int size)
{
	return(_AddHeader(header,buff,size));
}
