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

#ifndef _SENDDATA_H
#define _SENDDATA_H

#ifdef __cplusplus
extern "C"
{
#endif
	
#include "Ethernet_IP.h"

#ifdef WIN32
    int _InitWSA(WORD version);
#endif

        int CipSetDebug(int level); // pvbrowser
	void _CipFlushBuffer(void *buffer,int size);
	int _CipOpenSock(char *serveur,int port);

/********** Time-out unit is msec !!! ********************/
#ifndef PVBROWSER
	int _CipSendData(int sock,Encap_Header *header);
	Encap_Header *_CipRecvData(int sock,int timeout);
	Encap_Header *_CipSendData_WaitReply(int sock,Encap_Header *header,int sendtimeout,int rcvtimeout);
	int (*CipSendData)(int sock,Encap_Header *header);
	Encap_Header *(*CipRecvData)(int sock,int timeout);
	Encap_Header *(*CipSendData_WaitReply)(int sock,Encap_Header *header,int sendtimeout,int rcvtimeout);
#endif
	
#ifdef __cplusplus
}
#endif

#endif /* _SENDDATA_H */
