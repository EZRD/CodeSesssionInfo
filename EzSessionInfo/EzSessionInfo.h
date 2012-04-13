// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the EZSESSIONINFO_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// EZSESSIONINFO_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef EZSESSIONINFO_EXPORTS
#define EZSESSIONINFO_API __declspec(dllexport)
#else
#define EZSESSIONINFO_API __declspec(dllimport)
#endif

typedef  void (*EZCALLBACK)(int sessionId, int State);

extern EZCALLBACK exCallBack;

typedef struct ActiveSessions
{
	int SessionID;
}ACTIVESESSIONS,* PACTIVESESSIONS;

// This class is exported from the EzSessionInfo.dll
class EZSESSIONINFO_API CEzSessionInfo {
public:
	CEzSessionInfo(void);

	// TODO: add your methods here.
};

extern EZSESSIONINFO_API int nEzSessionInfo;

EZSESSIONINFO_API void GetAllActiveSessions( );

EZSESSIONINFO_API int IsRemoteRDPSession(int SessionId) ;

EZSESSIONINFO_API void SetCallBack() ;



