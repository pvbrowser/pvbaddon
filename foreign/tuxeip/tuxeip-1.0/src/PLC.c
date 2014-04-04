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

#include "PLC.h"
#include "ErrCodes.h"
#include "CIP_Const.h"
#include "CM.h"
#include "CIP_IOI.h"

PCCC_Requestor_ID _PCCC_RequestorID={7,TuxPlcVendorId,0x23456789};//  7=sizeof(PCCC_Requestor_ID)

int _BuildLogicalBinaryAddress(char* address,Logical_Binary_Address *lba)
{   int len=strlen(address);
    CIP_UINT i=0;int j=0;int level=0;
		int encoding_bit=0;
    char *tail;char *str;
		memset(lba,0,sizeof(Logical_Binary_Address));
		lba->size=1;
		//lba->mask=0xffff;
    tail=str=address;
    do
    {
      i=strtol(str,&tail,0);
      if (tail!=str)
      { if (encoding_bit)
				{
					lba->mask=1<<i;
				}else
				{
					level++;
					lba->address[0]|=(1<<level);     
					if (i<255)
					{
					 lba->address[lba->size]=i;
					 lba->size+=1;   
					} else
					{
					 lba->address[lba->size]=0xff;
					 lba->size+=1;
					 memcpy(&(lba->address[lba->size]),&i,sizeof(CIP_UINT));
					 lba->size+=2;
					}
				}
      } else
			{
				i=0;j=0;
				if (!strncasecmp(str,"/",1)) encoding_bit=1;
				
				if (!strncasecmp(str,"CTL",3)) i=1;
				if (!strncasecmp(str,"PRE",3)) i=2;
				if (!strncasecmp(str,"ACC",3)) i=3;
					
				if (!strncasecmp(str,"CTL0",4)) i=1; //for use with PD files
				if (!strncasecmp(str,"CTL1",4)) i=2;
				
				if (!strncasecmp(str,"SP",2)) i=3;
				if (!strncasecmp(str,"KP",2)) i=5;
				if (!strncasecmp(str,"KI",2)) i=7;
				if (!strncasecmp(str,"KD",2)) i=9;
				if (!strncasecmp(str,"PV",2)) i=27;
				
				if (!strncasecmp(str,"DN",2)) {i=1;j=14;};
				if (!strncasecmp(str,"EN",2)) {i=1;j=16;};
				if (!strncasecmp(str,"TT",2)) {i=1;j=15;};
				
				if (!strncasecmp(str,"OV",2)) {i=1;j=13;};
				if (!strncasecmp(str,"CU",2)) {i=1;j=16;};
				
				if (!strncasecmp(str,"SWM",3)) {i=1;j=5;};
				if (!strncasecmp(str,"MO",2)) {i=1;j=2;};
				if (!strncasecmp(str,"OLL",3)) {i=2;j=11;};
				if (!strncasecmp(str,"OLH",3)) {i=2;j=10;};
	
				if (i)
				{
					lba->address[0]|=(1<<++level);
					lba->address[lba->size]=i-1;
					lba->size+=1;
				}
				if (j)
				{
					lba->mask=1<<(j-1);
				}
			}
      if (str==tail) str+=1; else str=tail;  
    } while (tail<(address+len));
 return(0);   
}
int _BuildThreeAddressField(char* address,Three_Address_Fields *taf)
{ int len=strlen(address);
	CIP_UINT i=0;int level=0;
	int j=0;
	int filetype=0;
	char *tail;char *str;
	memset(taf,0,sizeof(Three_Address_Fields));
	//taf->mask=0xffff;
	switch (address[0])
	{
		case 'S':
		case 's':filetype=TAF_STATUS;break;
		case 'B':
		case 'b':filetype=TAF_BIT;break;
		case 'T':
		case 't':filetype=TAF_TIMER;break;
		case 'C':
		case 'c':filetype=TAF_COUNTER;break;
		case 'N':
		case 'n':filetype=TAF_INTEGER;break;
		case 'F':
		case 'f':filetype=TAF_FLOATING;break;
		case 'I':
		case 'i':filetype=TAF_INPUT;break;
		case 'O':
		case 'o':filetype=TAF_OUTPUT;break;
	}
	if (filetype==0) return(EX_Error);
	tail=str=address+1;
	do
	{
		i=strtol(str,&tail,0);// get value
		if (tail!=str) // there is a value
		{ 
			if(level==1)
			{
				taf->address[taf->size]=filetype;
				taf->size+=1; 
			}
			if (i<255)
			{
			 taf->address[taf->size]=i;
			 taf->size+=1;   
			} else
			{
			 taf->address[taf->size]=0xff;
			 taf->size+=1;
			 memcpy(&(taf->address[taf->size]),&i,sizeof(CIP_UINT));
			 taf->size+=2;
			}
			level++;
		} else 
		{
			i=0;j=0;
			if (!strncasecmp(str,"CTL",3)) i=1;
			if (!strncasecmp(str,"PRE",3)) i=2;
			if (!strncasecmp(str,"ACC",3)) i=3;
			
			if (!strncasecmp(str,"SP",2)) i=3;
			if (!strncasecmp(str,"KP",2)) i=5;
			if (!strncasecmp(str,"KI",2)) i=7;
			if (!strncasecmp(str,"KD",2)) i=9;
			if (!strncasecmp(str,"PV",2)) i=27;
			
			if (!strncasecmp(str,"DN",2)) j=1;
			if (!strncasecmp(str,"EN",2)) j=2;
			if (!strncasecmp(str,"TT",2)) j=3;

			if (i)
			{
				taf->address[taf->size]=i-1;
				taf->size+=1;
			}
			if (j)
			{
				taf->mask=1<<j;
			}
		}
		str=tail+1;  
	} while (tail<(address+len));
	
	if (level<3) // no sub element ??
	{
		taf->size+=3-level; // sub elt=0
	}
 return(0);   
}
PCCC_Header *_BuildPLCReadDataRequest(Plc_Type type,CIP_UINT tns,
																		Logical_Binary_Address *lba,CIP_UINT number,int *requestsize)
{ 
	int len=lba->size;
	CIP_UINT num=1*number;//size in word (???) * number of elements ???*/
	int rsize=sizeof(PCCC_SLCRW_Request)+len+sizeof(num);
	PCCC_SLCRW_Request *request=malloc(rsize);
	if (request==NULL)
	{
		CIPERROR(Sys_Error,errno,0);
		if (requestsize!=NULL) *requestsize=0;
		return(NULL);
	}
	memset(request,0,rsize);
	request->CMD=PCCC_TYPED_READ_CMD;
	request->TNS=tns;
	request->FNC=PCCC_TYPED_READ_FNC;
	request->Offset=0;
	request->Trans=number; // number of elements to read ???
	char *adr=(char*)((void*)request+sizeof(PCCC_SLCRW_Request));
	memcpy(adr,&lba->address,len);
	adr+=(len);
	memcpy(adr,&num,sizeof(num));
	if (requestsize!=NULL) *requestsize=rsize;
	return((PCCC_Header*)request);
}
PCCC_Header *_BuildPLCWriteDataRequest(Plc_Type type,CIP_UINT tns,Logical_Binary_Address *lba,
	CIP_UINT number,PLC_Data_Type datatype,void *data,int *requestsize)
{ 
	int len=lba->size;
	void *encodeddatatype=NULL;
	int datatypesize=_EncodePLCDataType(&encodeddatatype,datatype,number);
	int datasize=number*_GetPLCDataSize(datatype);
	if (datasize<0)
	{
		CIPERROR(Internal_Error,E_UnsupportedDataType,0);
		if (requestsize!=NULL) *requestsize=0;
		return(NULL);
	}
	int rsize=sizeof(PCCC_SLCRW_Request)+len+datatypesize+datasize;
	PCCC_SLCRW_Request *request=malloc(rsize);
	if (request==NULL)
	{
		CIPERROR(Sys_Error,errno,0);
		if (requestsize!=NULL) *requestsize=0;
		return(NULL);
	}
	memset(request,0,rsize);
	request->CMD=PCCC_TYPED_WRITE_CMD;
	request->TNS=tns;
	request->FNC=PCCC_TYPED_WRITE_FNC;
	request->Offset=0;
	request->Trans=number; // number of elements to read ???
	char *adr=(char*)((void*)request+sizeof(PCCC_SLCRW_Request));
	memcpy(adr,&lba->address,len);
	adr+=(len);
	memcpy(adr,encodeddatatype,datatypesize);
	adr+=datatypesize;
	memcpy(adr,data,datasize);
	free(encodeddatatype);
	if (requestsize!=NULL) *requestsize=rsize;
	return((PCCC_Header*)request);
}
PCCC_Header *_SendUnConnectedPCCCRequest(
								Eip_Session *session,
								DHP_Header *dhp,
								PCCC_Header *PCCCRequest,
								int PCCCrequestsize,
								BYTE *routepath,CIP_USINT routepathsize,
								int *replysize)
{ LogCip(LogTrace,"->Entering SendUnConnectedPCCCRequest \n");
	int dhpsize=0;if (dhp!=NULL) dhpsize=sizeof(DHP_Header);
	int reqlen=PCCCrequestsize+sizeof(PCCC_Requestor_ID)+dhpsize;
	void *request=malloc(reqlen);
	int Datasize=0;
	int mrreqlen;
	CIPERROR(Internal_Error,0,0);
	if (request==NULL) 
	{
		CIPERROR(Sys_Error,errno,0);
		if (replysize!=NULL) *replysize=0;
		LogCip(LogTrace,"!Exiting SendUnConnectedPCCCRequest with error : %s\n",_cip_err_msg);
		return(NULL);
	};
		
	((PCCC_Requestor_ID*)(request))->Length=0x07;
	((PCCC_Requestor_ID*)(request))->VendorID=_OriginatorVendorID;
	((PCCC_Requestor_ID*)(request))->Serial_Number=_OriginatorSerialNumber;
	if (dhpsize>0) memcpy(request+sizeof(PCCC_Requestor_ID),dhp,sizeof(DHP_Header));
	memcpy(request+sizeof(PCCC_Requestor_ID)+dhpsize,PCCCRequest,PCCCrequestsize);
	
	MR_Request *mrrequest=_BuildMRRequest(EXECUTE_PCCC,PCCC_PATH,sizeof(PCCC_PATH),request,reqlen,&mrreqlen);
	free(request);
	MR_Reply *mrreply=_UnconnectedSend(session,_Priority,_TimeOut_Ticks,mrrequest,mrreqlen,routepath,routepathsize,&Datasize);
	free(mrrequest);
	
	if (mrreply==NULL) 
	{
		if (replysize!=NULL) *replysize=0;
		LogCip(LogTrace,"!Exiting SendUnConnectedPCCCRequest with error : %s\n",_cip_err_msg);			
		return(NULL);
	}
	if (mrreply->General_Status)
	{
		free(mrreply);
		if (replysize!=NULL) *replysize=0;
		LogCip(LogTrace,"!Exiting SendUnConnectedPCCCRequest with error : %s\n",_cip_err_msg);
		return(NULL);
	}
	Datasize-=sizeof(MR_Reply)+2*mrreply->Add_Status_Size; //Size of MR Reply Data
	if (Datasize<0)
	{
		CIPERROR(MR_Error,mrreply->General_Status,_GetMRExtendedStatus(mrreply));
		free(mrreply);
		LogCip(LogTrace,"!Exiting SendUnConnectedPCCCRequest with error : %s\n",_cip_err_msg);
		return(NULL);
	}	
	PCCC_Requestor_ID *Requestor_ID=(PCCC_Requestor_ID *)(_GetMRData(mrreply));
	PCCC_Header *PCCCReply=(PCCC_Header *)((void *)(Requestor_ID)+(Requestor_ID)->Length);
	Datasize-=Requestor_ID->Length; // Size of PCCC reply
	if (Datasize<0)
	{
		CIPERROR(Internal_Error,E_PLC,__LINE__);
		free(mrreply);
		LogCip(LogTrace,"!Exiting SendUnConnectedPCCCRequest with error : %s\n",_cip_err_msg);
		return(NULL);
	}	
	if (PCCCReply->STS!=0)
	{ BYTE *ext_sts=(BYTE*)((void*)(PCCCReply)+sizeof(*PCCCReply));
		if (PCCCReply->STS==0xF0) {CIPERROR(PCCC_Error,PCCCReply->STS,*ext_sts);}
			else {CIPERROR(PCCC_Error,PCCCReply->STS,0);}
	}
	if (replysize==NULL) *replysize=Datasize;//(end-(void*)PCCCReply);
	PCCC_Header *reply=malloc(Datasize);
	if (reply==NULL) 
	{
		CIPERROR(Sys_Error,errno,0);
		free(mrreply);
		LogCip(LogTrace,"!Exiting SendUnConnectedPCCCRequest with error : %s\n",_cip_err_msg);
		return(NULL);
	};
	memcpy(reply,PCCCReply,Datasize);
	free(mrreply);
	LogCip(LogTrace,"->Exiting SendUnConnectedPCCCRequest : size=%d (%p)\n",Datasize,reply);
	return(reply);
}
PCCC_Header *_SendConnectedPCCCRequest(
							Eip_Session *session,
							Eip_Connection *connection,
							DHP_Header *dhp,
							PCCC_Header *PCCCRequest,
							int PCCCrequestsize,
							int *replysize)
{ 
	int reqlen=0;
	void *request=NULL;
	if (replysize==NULL) *replysize=0;
		
	if (dhp==NULL) // communication method is NOT DH+
  { LogCip(LogTrace,"->Entering SendConnectedPCCCRequest method is NOT DH+\n");
		reqlen=PCCCrequestsize+sizeof(PCCC_Requestor_ID);
		request=malloc(reqlen);
		if (request==NULL) 
		{
			CIPERROR(Sys_Error,errno,0);
			LogCip(LogTrace,"!Exiting SendConnectedPCCCRequest with error : %s\n",_cip_err_msg);
			return(NULL);
		};
		((PCCC_Requestor_ID*)(request))->Length=0x07;
 		((PCCC_Requestor_ID*)(request))->VendorID=_OriginatorVendorID;
 		((PCCC_Requestor_ID*)(request))->Serial_Number=_OriginatorSerialNumber;
 		memcpy(request+sizeof(PCCC_Requestor_ID),PCCCRequest,PCCCrequestsize);
		int mrreqsize=0;
  	MR_Request *mrrequest=_BuildMRRequest(EXECUTE_PCCC,PCCC_PATH,sizeof(PCCC_PATH),request,reqlen,&mrreqsize);
  	free(request);
		
		Eip_CDI *cdi=_ConnectedSend(session,connection,mrrequest,mrreqsize);
		free(mrrequest);
		
		if (cdi==NULL) return(NULL);
		// Analyze MR Reply
		int Datasize=cdi->Length-sizeof(cdi->Packet);  //Size of MR Reply
		if (Datasize<sizeof(MR_Reply))
		{
			CIPERROR(Internal_Error,E_PLC,__LINE__);
			free(cdi);
			LogCip(LogTrace,"!Exiting SendConnectedPCCCRequest with error : %s\n",_cip_err_msg);
			return(NULL);
		}
		MR_Reply *mrrep=(void*)cdi+sizeof(Eip_CDI);

		if (mrrep->Service!=(EXECUTE_PCCC+0x80)) 
		{
			CIPERROR(Internal_Error,E_UnsolicitedMsg,0);
			free(cdi);
			LogCip(LogTrace,"!Exiting SendConnectedPCCCRequest with error : %s\n",_cip_err_msg);
			return(NULL);
		}
		Datasize=Datasize-(sizeof(MR_Reply)+2*mrrep->Add_Status_Size); //Size of MR Reply Data
		if (Datasize<0)
		{
			CIPERROR(MR_Error,mrrep->General_Status,_GetMRExtendedStatus(mrrep));
			free(cdi);
			LogCip(LogTrace,"!Exiting SendConnectedPCCCRequest with error : %s\n",_cip_err_msg);
			return(NULL);
		}	
		PCCC_Requestor_ID *Requestor_ID=(PCCC_Requestor_ID *)(_GetMRData(mrrep));
		PCCC_Header *PCCCReply=(PCCC_Header *)((void *)(Requestor_ID)+(Requestor_ID)->Length);
		Datasize=Datasize-Requestor_ID->Length; // Size of PCCC reply
		if (Datasize<0)
		{
			CIPERROR(Internal_Error,E_PLC,__LINE__);
			free(cdi);
			LogCip(LogTrace,"!Exiting SendConnectedPCCCRequest with error : %s\n",_cip_err_msg);
			return(NULL);
		}	
		if (PCCCReply->STS!=0)
		{ 
			BYTE *ext_sts=(BYTE*)((void*)(PCCCReply)+sizeof(*PCCCReply));
			if (PCCCReply->STS==0xF0) 
			{
				CIPERROR(PCCC_Error,PCCCReply->STS,*ext_sts);
			}	else 
			{
				CIPERROR(PCCC_Error,PCCCReply->STS,0);
			}
		}
		if (replysize==NULL) *replysize=Datasize;//(end-(void*)PCCCReply);
		PCCC_Header *reply=malloc(Datasize);
		if (reply==NULL) 
		{
			CIPERROR(Sys_Error,errno,0);
			free(cdi);
			LogCip(LogTrace,"!Exiting SendConnectedPCCCRequest with error : %s\n",_cip_err_msg);
			return(NULL);
		};
		memcpy(reply,PCCCReply,Datasize);
		free(cdi);
		LogCip(LogTrace,"->Exiting SendUnConnectedPCCCRequest : size=%d (%p)\n",Datasize,PCCCReply);
		return(reply);
	
  } else // communication method is DH+
  {
		LogCip(LogTrace,"->Entering SendConnectedPCCCRequest method is DH+\n");
		reqlen=PCCCrequestsize+sizeof(DHP_Header);
		request=malloc(reqlen);
		if (request==NULL) 
		{
			CIPERROR(Sys_Error,errno,0);
			LogCip(LogTrace,"!Exiting SendConnectedPCCCRequest with error : %s\n",_cip_err_msg);
			return(NULL);
		};
		memcpy(request,dhp,sizeof(DHP_Header));
		memcpy(request+sizeof(DHP_Header),PCCCRequest,PCCCrequestsize);
		Eip_CDI *cdi=_ConnectedSend(session,connection,request,reqlen);
		free(request);
		
		if (cdi==NULL) return(NULL);
		// Analyze PCCC Reply
		int Datasize=cdi->Length-sizeof(cdi->Packet)-sizeof(DHP_Header);
		if (Datasize<=0)
		{
			CIPERROR(Internal_Error,E_PLC,__LINE__);
			LogCip(LogTrace,"!Exiting SendConnectedPCCCRequest with error : %s\n",_cip_err_msg);
			return(NULL);
		}
		PCCC_Header *PCCCReply=(PCCC_Header *)((void *)(cdi)+sizeof(Eip_CDI)+sizeof(DHP_Header));
		if (PCCCReply->STS!=0)
		{ 
			BYTE *ext_sts=(BYTE*)((void*)(PCCCReply)+sizeof(*PCCCReply));
			if (PCCCReply->STS==0xF0) 
			{
				CIPERROR(PCCC_Error,PCCCReply->STS,*ext_sts);
			}	else 
			{
				CIPERROR(PCCC_Error,PCCCReply->STS,0);
			}
		}
		PCCC_Header *reply=malloc(Datasize);
		if (reply==NULL) 
		{
			CIPERROR(Sys_Error,errno,0);
			free(cdi);
			LogCip(LogTrace,"!Exiting SendConnectedPCCCRequest with error : %s\n",_cip_err_msg);
			return(NULL);
		};
		memcpy(reply,PCCCReply,Datasize);
		free(cdi);
		LogCip(LogTrace,"->Exiting SendUnConnectedPCCCRequest : size=%d (%p)\n",Datasize,PCCCReply);
		return(reply);
  }
}
PLC_Read *_ReadPLCData(
												Eip_Session *session,
												Eip_Connection *connection,
												DHP_Header *dhp,
												BYTE *routepath,CIP_USINT routepathsize,
												Plc_Type type,CIP_UINT tns,
												char *address,CIP_UINT number)
{	
	Logical_Binary_Address lba;
	_BuildLogicalBinaryAddress(address,&lba);
	return(_ReadPLCData_Ex(session,connection,dhp,routepath, routepathsize,type,tns,&lba,number));
}
PLC_Read *_ReadPLCData_Ex(
													Eip_Session *session,
													Eip_Connection *connection,
													DHP_Header *dhp,
													BYTE *routepath,CIP_USINT routepathsize,
													Plc_Type type,CIP_UINT tns,
													Logical_Binary_Address *lba,CIP_UINT number)
{	
	PCCC_Header *reply;
	int replysize;
	int requestsize;
	PCCC_Header *PCCCRequest=_BuildPLCReadDataRequest(type,tns,lba,number,&requestsize);
	if (connection==NULL)
	{
		reply=_SendUnConnectedPCCCRequest(session,dhp,PCCCRequest,requestsize,routepath,routepathsize,&replysize);
	}	else reply=_SendConnectedPCCCRequest(session,connection,dhp,PCCCRequest,requestsize,&replysize);
	free(PCCCRequest);
	if (reply!=NULL)
	{ 
		PLC_Read *result=_DecodePCCC(reply);
		if (result!=NULL) result->mask=lba->mask;
		CIPERROR(PCCC_Error,reply->STS,0);
		free(reply);
		return(result);
	}	else return(NULL);
}
int _WritePLCData(
									Eip_Session *session,
									Eip_Connection *connection,
									DHP_Header *dhp,
									BYTE *routepath,CIP_USINT routepathsize,
									Plc_Type type,CIP_UINT tns,
									char *address,
									PLC_Data_Type datatype,
									void *data,
									CIP_UINT number)
{	
	PCCC_Header *res;
	Logical_Binary_Address lba;
	int replysize;
	
	_BuildLogicalBinaryAddress(address,&lba);
	int requestsize;
	PCCC_Header *PCCCRequest=_BuildPLCWriteDataRequest(type,tns,&lba,number,datatype,data,&requestsize);	
	if (connection==NULL)
	{
		res=_SendUnConnectedPCCCRequest(session,dhp,PCCCRequest,requestsize,routepath,routepathsize,&replysize);
	}	else res=_SendConnectedPCCCRequest(session,connection,dhp,PCCCRequest,requestsize,&replysize);
	free(PCCCRequest);
	if (res!=NULL)
	{ 
		CIPERROR(PCCC_Error,res->STS,0);
		int result=res->STS;
		free(res);
		return(result);
	}	else return(EX_Error);	
}
int _GetPLCDataSize(PLC_Data_Type DataType)
{
	switch (DataType)
	{
	case PLC_BYTE_STRING:return(1);break;
	case PLC_INTEGER:return(2);break;
	case PLC_TIMER:return(6);break;
	case PLC_COUNTER:return(6);break;
	case PLC_CONTROL:return(6);break;
	case PLC_FLOATING:return(4);break;
	default:
			//*data=NULL;
			return(EX_Error);
		break;
	}
}
PLC_Data_Type _PLCDataType(Data_Type DataType)
{
	switch (DataType)
	{
	case BIT:return(PLC_BIT);break;
	case SINT:
	case TUXINT:    // pvbrowser modification 
	//case INT:
	case DINT:return(PLC_INTEGER);break;
	case TIMER:return(PLC_TIMER);break;
	case COUNTER:return(PLC_COUNTER);break;
	case REAL:return(PLC_FLOATING);break;
	default:
			return(EX_Error);
		break;
	}
}
void *_DecodePLCDataType(PCCC_Header *reply,PLC_Data_Type *type,int *tsize,int *esize)
{ *type=0;*tsize=0;*esize=0;
	int datasize=0;
	PCCC_SLCRW_Reply *rep=(PCCC_SLCRW_Reply*)reply;
	if (reply==NULL) return(NULL);
	if (rep->STS!=0) return(NULL);

	BYTE *data=&(rep->Ext_STS);
	BYTE flag=*data;
	data++;

	if ((flag>>4)<8) 
	{ 
		*type=(flag>>4);
	}	else
	{ 
		datasize =((flag>>4)&0x07);
		switch (datasize)
		{
			case 1:	*type=*((BYTE*)data);
							data+=1;
							break;
			case 2:	*type=*((WORD*)data);
							data+=2;
							break;
			case 4:	*type=*((LONGWORD*)data);
							data+=4;
							break;
			default:*type=0;*tsize=0;*esize=0;return(NULL);
		}
	}
	if ((flag&0x0f)<8) 
	{ 
		*tsize=(flag&0x0f);
	}	else
	{ 
		datasize =(flag&0x07);
		switch (datasize)
		{
			case 1:	*tsize=*((BYTE*)data);
							data+=1;
							break;
			case 2:	*tsize=*((WORD*)data);
							data+=2;
							break;
			case 4:	*tsize=*((LONGWORD*)data);
							data+=4;
							break;
			default:*type=0;*tsize=0;*esize=0;return(NULL);
		}
	}
	if (*type==PLC_ARRAY)
	{
		flag=*data;
		data++;
		if ((flag>>4)<8) 
		{ 
			*type=(flag>>4);
		}	else
		{ 
			datasize =((flag>>4)&0x07);
			*tsize-=datasize;
			switch (datasize)
			{
				case 1:	*type=*((BYTE*)data);
								data+=1;
								break;
				case 2:	*type=*((WORD*)data);
								data+=2;
								break;
				case 4:	*type=*((LONGWORD*)data);
								data+=4;
								break;
				default:*type=0;*tsize=0;*esize=0;return(NULL);
			}
		}
		if ((flag&0x0f)<8) 
		{ 
			*esize=(flag&0x0f);
		}	else
		{ 
			datasize =(flag&0x07);
			*tsize-=datasize;
			switch (datasize)
			{
				case 1:	*esize=*((BYTE*)data);
								data+=1;
								break;
				case 2:	*esize=*((WORD*)data);
								data+=2;
								break;
				case 4:	*esize=*((LONGWORD*)data);
								data+=4;
								break;
				default:*type=0;*tsize=0;*esize=0;return(NULL);
			}
		}
	}
	(*tsize)--; // elements size - descriptor size
	return(data);
}
int _EncodePLCDataType(void **data,PLC_Data_Type type,int number)
{ *data=NULL;
	if (_GetPLCDataSize(type)==EX_Error)
	{
		CIPERROR(Internal_Error,E_UnsupportedDataType,0);
		return(EX_Error);
	}
	CIP_USINT typeidlen=0;
	CIP_USINT elementsizelen=0;
	CIP_USINT typelen=_GetPLCDataSize(type);
	if (type>7) typeidlen=1;
	if (typelen>7) elementsizelen=1;
		
	int len=4+typeidlen+elementsizelen;
	*data=malloc(len);
	void *ptr=*data;
	*((BYTE*)(ptr++))=0x99;
	*((BYTE*)(ptr++))=0x09;
	*((BYTE*)(ptr++))=number*typelen+typeidlen+elementsizelen+1;
	if ((typeidlen==0)&&(elementsizelen==0))
	{
		*((BYTE*)(ptr))=(type<<4)|(typelen&0x0F);
	}
	if ((typeidlen==0)&&(elementsizelen>0))
	{
		*((BYTE*)(ptr++))=(type<<4)|(0x09);
		*((BYTE*)(ptr))=typelen;
	}
	if ((typeidlen>0)&&(elementsizelen==0))
	{
		*((BYTE*)(ptr++))=(0x09<<4)|(typelen&0x0F);
		*((BYTE*)(ptr))=type;
	}
	if ((typeidlen>0)&&(elementsizelen>0))
	{
		*((BYTE*)(ptr++))=0x99;
		*((BYTE*)(ptr++))=type;
		*((BYTE*)(ptr))=typelen;
	}
	return(len);
	
}
PLC_Read *_DecodePCCC(PCCC_Header *reply)
{ 
	int datasize=0;
	PCCC_SLCRW_Reply *rep=(PCCC_SLCRW_Reply*)reply;
	if (reply==NULL) return(NULL);
	if (rep->STS!=0) return(NULL);
		
	PLC_Read *result=malloc(sizeof(PLC_Read));
	if (result==NULL) 
	{
		CIPERROR(Sys_Error,errno,0);
		return(NULL);
	};
	memset(result,0,sizeof(PLC_Read));
	BYTE *data=&(rep->Ext_STS);
	BYTE flag=*data;
	data++;

	if ((flag>>4)<8) 
	{ 
		result->type=(flag>>4);
	}	else
	{ 
		datasize =((flag>>4)&0x07);
		switch (datasize)
		{
			case 1:	result->type=*((BYTE*)data);
							data+=1;
							break;
			case 2:	result->type=*((WORD*)data);
							data+=2;
							break;
			case 4:	result->type=*((LONGWORD*)data);
							data+=4;
							break;
			default:result->type=0;result->totalsize=0;result->elementsize=0;return(0);
		}
	}
	if ((flag&0x0f)<8) 
	{ 
		result->totalsize=(flag&0x0f);
	}	else
	{ 
		datasize =(flag&0x07);
		switch (datasize)
		{
			case 1:	result->totalsize=*((BYTE*)data);
							data+=1;
							break;
			case 2:	result->totalsize=*((WORD*)data);
							data+=2;
							break;
			case 4:	result->totalsize=*((LONGWORD*)data);
							data+=4;
							break;
			default:result->type=0;result->totalsize=0;result->elementsize=0;return(0);
		}
	}
	if (result->type==PLC_ARRAY)
	{
		flag=*data;
		data++;
		if ((flag>>4)<8) 
		{ 
			result->type=(flag>>4);
		}	else
		{ 
			datasize =((flag>>4)&0x07);
			result->totalsize-=datasize;
			switch (datasize)
			{
				case 1:	result->type=*((BYTE*)data);
								data+=1;
								break;
				case 2:	result->type=*((WORD*)data);
								data+=2;
								break;
				case 4:	result->type=*((LONGWORD*)data);
								data+=4;
								break;
				default:result->type=0;result->totalsize=0;result->elementsize=0;return(0);
			}
		}
		if ((flag&0x0f)<8) 
		{ 
			result->elementsize=(flag&0x0f);
		}	else
		{ 
			datasize =(flag&0x07);
			result->totalsize-=datasize;
			switch (datasize)
			{
				case 1:	result->elementsize=*((BYTE*)data);
								data+=1;
								break;
				case 2:	result->elementsize=*((WORD*)data);
								data+=2;
								break;
				case 4:	result->elementsize=*((LONGWORD*)data);
								data+=4;
								break;
				default:result->type=0;result->totalsize=0;result->elementsize=0;return(0);
			}
		}
	}
	(result->totalsize)--; // elements size - descriptor size
	if (result->elementsize==0) 
	{
		CIPERROR(Internal_Error,E_PLC,__LINE__);
		free(result);
		return(NULL);
	}
	result->Varcount=result->totalsize/result->elementsize;
	if(result->Varcount<1)
	{
		CIPERROR(Internal_Error,E_PLC,__LINE__);
		free(result);
		return(NULL);
	}
	result=realloc(result,sizeof(PLC_Read)+result->totalsize);
	if (result==NULL) 
	{
		CIPERROR(Sys_Error,errno,0);
		return(NULL);
	};
	memcpy((void*)result+sizeof(PLC_Read),data,result->totalsize);
	return(result);
}
int _PCCC_GetValueAsBoolean(PLC_Read *reply,int index)
{	if ((reply->Varcount==0)||(reply->totalsize==0))
	{
		CIPERROR(Internal_Error,E_InvalidReply,0);
		return(0);
	}
	float value=0;
	CIPERROR(Internal_Error,Success,0);
	if (index>reply->Varcount-1) CIPERROR(Internal_Error,E_OutOfRange,0);
	unsigned int mask=-1;
	if (reply->mask) mask=reply->mask;	
	switch (reply->type)
	{
		case PLC_INTEGER:value=*((CIP_INT*)((void*)reply+sizeof(PLC_Read)+index*reply->elementsize));break;
		case PLC_FLOATING:value=*((float*)((void*)reply+sizeof(PLC_Read)+index*reply->elementsize));break;
		default:CIPERROR(Internal_Error,E_UnsupportedDataType,0);return(EX_Error);
	}
	if (mask!=-1)
	{
		if (((unsigned int)value) & (mask)) return(1); else return(0);
	} else return(value);
}
int _PCCC_GetValueAsInteger(PLC_Read *reply,int index)
{	if ((reply->Varcount==0)||(reply->totalsize==0))
	{
		CIPERROR(Internal_Error,E_InvalidReply,0);
		return(0);
	}
	float value=0;
	CIPERROR(Internal_Error,Success,0);
	if (index>reply->Varcount-1) CIPERROR(Internal_Error,E_OutOfRange,0);
	unsigned int mask=-1;
	switch (reply->type)
	{
		case PLC_INTEGER:value=*((CIP_INT*)((void*)reply+sizeof(PLC_Read)+index*reply->elementsize));break;
		case PLC_FLOATING:value=*((float*)((void*)reply+sizeof(PLC_Read)+index*reply->elementsize));break;
		default:CIPERROR(Internal_Error,E_UnsupportedDataType,0);return(EX_Error);
	}
	if (mask!=-1)
	{
		if (((unsigned int)value) & (mask)) return(1); else return(0);
	} else return(value);
}
float _PCCC_GetValueAsFloat(PLC_Read *reply,int index)
{	if ((reply->Varcount==0)||(reply->totalsize==0))
	{
		CIPERROR(Internal_Error,E_InvalidReply,0);
		return(0);
	}
	float value=0;
	CIPERROR(Internal_Error,Success,0);
	if (index>reply->Varcount-1) CIPERROR(Internal_Error,E_OutOfRange,0);
	unsigned int mask=-1;
	switch (reply->type)
	{
		case PLC_INTEGER:value=*((CIP_INT*)((void*)reply+sizeof(PLC_Read)+index*reply->elementsize));break;
		case PLC_FLOATING:value=*((float*)((void*)reply+sizeof(PLC_Read)+index*reply->elementsize));break;
		default:CIPERROR(Internal_Error,E_UnsupportedDataType,0);return(EX_Error);
	}
	if (mask!=-1)
	{
		if (((unsigned int)value) & (mask)) return(1); else return(0);
	} else return(value);
}
