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
 
#ifndef _LGX_H
#define _LGX_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "CIP_Types.h"
#include "Ethernet_IP.h"
#include "AB.h"

#define CIP_DATA_READ 		0x4C
#define CIP_DATA_WRITE 		0x4D
#define CIP_MULTI_REQUEST 0x0A
	
#define DT_BOOL				0x00C1
#define DT_BITARRAY		0x00D3
#define DT_SINT				0x00C2
#define DT_INT				0x00C3
#define DT_DINT				0x00C4
#define DT_REAL				0x00CA

/******************    Data access ***********************************/
	
typedef struct _CommonDataService_Reply{
		//CIP_UINT Packet;
		CIP_USINT Service;
		CIP_SINT Reserved;
		CIP_UINT Status;
		}__attribute__((packed)) CommonDataService_Reply;
//typedef CommonDataService_Reply *PCommonDataService_Reply;


typedef struct _ReadDataService_Request{
		//CIP_UINT Packet;
		CIP_SINT Service;
		CIP_USINT PathSize;
		//ByteArray Path; // depend on PathSize
		CIP_UINT Number; // number of element to read
		}__attribute__((packed)) ReadDataService_Request;
//typedef ReadDataService_Request *PReadDataService_Request;

typedef struct _ReadDataService_Reply{
		//CIP_UINT Packet;
		CIP_USINT Service;
		CIP_SINT Reserved;
		CIP_UINT Status; //
		CIP_UINT DataType; // !! only valid for simple Datatypes
		//ByteArray Data;
		}__attribute__((packed)) ReadDataService_Reply;
//typedef ReadDataService_Reply *PReadDataService_Reply;

typedef struct _WriteDataService_Request{
                //CIP_UINT Packet;
                CIP_SINT Service;
                CIP_USINT PathSize;
                //ByteArray Path; // depend on PathSize
                CIP_UINT DataType;
                CIP_UINT Number; // number of element to read
                //ByteArray Data;
								}__attribute__((packed)) WriteDataService_Request;
//typedef WriteDataService_Request *PWriteDataService_Request;

typedef struct _WriteDataService_Reply{
                //CIP_UINT Packet;
                CIP_USINT Service;
                CIP_SINT Reserved;
                CIP_UINT Status;
                }__attribute__((packed)) WriteDataService_Reply;
//typedef WriteDataService_Reply *PWriteDataService_Reply;

typedef struct _MultiService_Request{
		//CIP_UINT Packet;
		CIP_SINT Service;
		CIP_USINT PathSize;// 2
		BYTE Path[4];//msg router path
		CIP_UINT Count; // number of element
		CIP_UINT Offsets[];
		}__attribute__((packed)) MultiService_Request;
//typedef MultiService_Request *PMultiService_Request;

typedef struct _MultiService_Reply{
		//CIP_UINT Packet;
		CIP_USINT Service;
		CIP_SINT Reserved;
		CIP_USINT GenSTS;
		CIP_SINT Reserved2;
		CIP_UINT Count;
		CIP_UINT Offsets[];
		}__attribute__((packed)) MultiService_Reply;
//typedef MultiService_Reply *PMultiService_Reply;	

typedef struct _LGX_Read{
								LGX_Data_Type type;
								int Varcount;
								int totalsize;
								int elementsize;
								unsigned int mask;}__attribute__((packed)) LGX_Read;
		
/********************* Global var *****************************************/

/**************************************************************************/

ReadDataService_Request *_BuildLgxReadDataRequest(char *adress,CIP_UINT number,int *requestsize);
WriteDataService_Request *_BuildLgxWriteDataRequest(char *adress,LGX_Data_Type datatype,
										void *data,int datasize,CIP_UINT number,int *requestsize);

LGX_Read *_ReadLgxData( Eip_Session *session,
                        Eip_Connection *connection,
                        char *adress,
                        CIP_UINT number); // number of element

#define ReadLgxData(session,connection,adress,number) _ReadLgxData(session,connection,adress,number)

int _WriteLgxData(Eip_Session *session,
                            Eip_Connection *connection,
                            char *adress,
                            LGX_Data_Type datatype,
                            void *data,
                            //int datasize,
                            CIP_UINT number); // number of element

#define WriteLgxData(Session,Connection,adress,datatype,data,number) _WriteLgxData(Session,Connection,adress,datatype,data,number)

CommonDataService_Reply *_GetService_Reply(Eip_Item *dataitem,unsigned int index);

CIP_INT _GetExtendedStatus(CommonDataService_Reply *reply);

int _GetService_ReplyNumber(Eip_Item *dataitem);

CommonDataService_Reply *_GetService_Reply(Eip_Item *dataitem,unsigned int index);

// pvbrowser modification because of MINGW
void *_GetData(CommonDataService_Reply *reply);
#define TuxGetData(reply) _GetData(reply)
//void *_GetData(CommonDataService_Reply *reply);
//#define GetData(reply) _GetData(reply)

int _GetLGXDataSize(LGX_Data_Type DataType);

LGX_Data_Type _LGXDataType(Data_Type DataType);
#define LGXDataType _LGXDataType

LGX_Data_Type _GetLGXDataType(CommonDataService_Reply *reply);

LGX_Read *_DecodeLGX(CommonDataService_Reply *reply,int replysize);

int _GetLGXValueAsInteger(LGX_Read *reply,int index);
#define GetLGXValueAsInteger(reply,index) _GetLGXValueAsInteger(reply,index)

float _GetLGXValueAsFloat(LGX_Read *reply,int index);
#define GetLGXValueAsFloat(reply,index) _GetLGXValueAsFloat(reply,index)



#ifdef __cplusplus
}
#endif

#endif /* _LGX_H */
