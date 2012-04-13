// EzSessionInfo.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Wtsapi32.h"
#include "EzSessionInfo.h"


int sessionId = -1;
int state = -1;

// This is an example of an exported variable
EZSESSIONINFO_API int nEzSessionInfo=0;

EZCALLBACK exCallBack;

EZSESSIONINFO_API void SetCallBack( EZCALLBACK MyCallBack)
{
	exCallBack = MyCallBack;
}

EZSESSIONINFO_API int IsRemoteRDPSession(int sessionID)
{
	LPTSTR  ppBuffer			   = NULL;
	DWORD   pBytesReturned	       = 0;
	int IsRDPSession = 0;

	if( WTSQuerySessionInformation( WTS_CURRENT_SERVER_HANDLE,
						  		    sessionID,
								    WTSClientProtocolType,
								    &ppBuffer,
								    &pBytesReturned) )
	{
		switch( *ppBuffer )
		{
		case WTS_PROTOCOL_TYPE_CONSOLE:
			
			break;
		case WTS_PROTOCOL_TYPE_ICA:
			
			break;
		case WTS_PROTOCOL_TYPE_RDP:
			IsRDPSession = 1;
			break;
		default:
			break;
		}
	}
	else
	{
		IsRDPSession = -1;
	}

	WTSFreeMemory( ppBuffer );

	return IsRDPSession;
}

// This is an example of an exported function.
EZSESSIONINFO_API void GetAllActiveSessions( )
{
	PACTIVESESSIONS ppactiveSessioninfo = NULL;

	PWTS_SESSION_INFO ppSessionInfo = NULL;
	DWORD			  pCount = 0;
	WTS_SESSION_INFO  wts;

	WTSEnumerateSessions( WTS_CURRENT_SERVER_HANDLE,
	                      0,
	 				      1,
						  &ppSessionInfo,
						  &pCount ); // pCount - Pointer to the variable that receives
						             // the number of WTS_SESSION_INFO structures
								     // returned in the ppSessionInfo buffer

	int length = 0;
	
	for( DWORD i = 0; i < pCount; i++ )
	{
		wts = ppSessionInfo[i];
		sessionId = wts.SessionId;
			
		WTS_CONNECTSTATE_CLASS	TSState			  = wts.State;
		
		//strcpy( SessionList , wts.SessionId

		if( exCallBack )
		{
			
			state = TSState;
			exCallBack( sessionId, state );
			Sleep(200);
			
		}


		/*switch( TSState )
		{
		    case WTSActive:
				
				length++;

				break;
			case WTSConnected:
				objItem.ConnectionState = "Connected";
				break;
			case WTSConnectQuery:
				objItem.ConnectionState = "ConnectQuery";
				break;
			case WTSShadow:
				objItem.ConnectionState = "Shadow";
				break;
			case WTSDisconnected:
				objItem.ConnectionState = "Disconnected";
				break;
			case WTSIdle:
				objItem.ConnectionState = "Idle";
				break;
			case WTSListen:
				objItem.ConnectionState = "Listen";
				break;
			case WTSReset:
				objItem.ConnectionState = "Reset";
				break;
			case WTSDown:
				objItem.ConnectionState = "Down";
				break;
			case WTSInit:
				objItem.ConnectionState = "Init";
				break;
		}*/
		/*ppactiveSessioninfo = new ACTIVESESSIONS[length];

		for( DWORD i = 0; i < pCount; i++ )
		{
			wts = ppSessionInfo[i];
			
			WTS_CONNECTSTATE_CLASS	TSState			  = wts.State;
			switch( TSState )
			{
				case WTSActive:
					ppactiveSessioninfo[i].SessionID = wts.SessionId;
				break;
			}
		}*/
	}
	
	//Count = length;

	
}

// This is the constructor of a class that has been exported.
// see EzSessionInfo.h for the class definition
CEzSessionInfo::CEzSessionInfo()
{
	return;
}
