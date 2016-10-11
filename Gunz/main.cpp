#include "stdafx.h"

#undef pi
#include <windows.h>
#include <wingdi.h>
#include <mmsystem.h>
#include <shlwapi.h>
#include <shellapi.h>

#pragma warning(push)
#pragma warning(disable:4091)
#include <ShlObj.h>
#pragma warning(pop)

#include "ZPrerequisites.h"
#include "ZConfiguration.h"
#include "ZGameClient.h"

#include "dxerr9.h"

#include "main.h"
#include "resource.h"
#include "VersionNo.h"

#include "Mint4R2.h"
#include "ZApplication.h"
#include "MDebug.h"
#include "ZMessages.h"
#include "RealSpace2.h"
#include "Mint.h"
#include "ZGameInterface.h"
#include "RFrameWork.h"
#include "ZButton.h"
#include "ZDirectInput.h"
#include "ZActionDef.h"
#include "MRegistry.h"
#include "ZInitialLoading.h"
#include "MDebug.h"
#include "MCrashDump.h"
#include "ZEffectFlashBang.h"
#include "ZMsgBox.h"
#include "ZSecurity.h"
#include "ZStencilLight.h"
#include "ZReplay.h"
#include "ZUtil.h"
#include "ZOptionInterface.h"
#include "MMatchNotify.h"

#ifdef USING_VERTEX_SHADER
#include "RShaderMgr.h"
#endif

#include "RLenzFlare.h"
#include "ZLocale.h"
#include "MSysInfo.h"

#include "MTraceMemory.h"
#include "ZInput.h"
#include "Mint4Gunz.h"

#include "RGMain.h"

RMODEPARAMS	g_ModeParams = { 800,600,FullscreenType::Fullscreen,D3DFMT_R5G6B5 };

#ifndef _DEBUG
#define SUPPORT_EXCEPTIONHANDLING
#endif


RRESULT RenderScene(void *pParam);

#define RD_STRING_LENGTH 512
char cstrReleaseDate[512];

ZApplication	g_App;
MDrawContextR2* g_pDC = NULL;
MFontR2*		g_pDefFont = NULL;
ZDirectInput	g_DInput;
ZInput*			g_pInput = NULL;
Mint4Gunz		g_Mint;


HRESULT GetDirectXVersionViaDxDiag( DWORD* pdwDirectXVersionMajor, DWORD* pdwDirectXVersionMinor, TCHAR* pcDirectXVersionLetter );

void _ZChangeGameState(int nIndex)
{
	GunzState state = GunzState(nIndex);

	if (ZApplication::GetGameInterface())
	{
		ZApplication::GetGameInterface()->SetState(state);
	}
}

RRESULT OnCreate(void *pParam)
{
	g_App.PreCheckArguments();

	g_RGMain->OnCreateDevice();

	RCreateLenzFlare("System/LenzFlare.xml");
	RGetLenzFlare()->Initialize();

	mlog("main : RGetLenzFlare()->Initialize() \n");

	RBspObject::CreateShadeMap("sfx/water_splash.bmp");
	
	sprintf_safe( cstrReleaseDate, "");
	g_DInput.Create(g_hWnd, FALSE, FALSE);
	g_pInput = new ZInput(&g_DInput);
	RSetGammaRamp(Z_VIDEO_GAMMA_VALUE);
	RSetRenderFlags(RRENDER_CLEAR_BACKBUFFER);

	ZGetInitialLoading()->Initialize(  1, 0, 0, RGetScreenWidth(), RGetScreenHeight(), 0, 0, 1024, 768 );

	mlog("main : ZGetInitialLoading()->Initialize() \n");

	struct _finddata_t c_file;
	intptr_t hFile;
	char szFileName[256];
#define FONT_DIR	"Font/"
#define FONT_EXT	"ttf"
	if( (hFile = _findfirst(FONT_DIR "*." FONT_EXT, &c_file )) != -1L ){
		do{
			strcpy_safe(szFileName, FONT_DIR);
			strcat(szFileName, c_file.name);
			AddFontResource(szFileName);
		}while( _findnext( hFile, &c_file ) == 0 );
		_findclose(hFile);
	}

	g_pDefFont = new MFontR2;

	if( !g_pDefFont->Create("Default", Z_LOCALE_DEFAULT_FONT, 9, 1.0f) )
	{
		mlog("Fail to Create defualt font : MFontR2 / main.cpp.. onCreate\n" );
		g_pDefFont->Destroy();
		SAFE_DELETE( g_pDefFont );
		g_pDefFont	= NULL;
	}

	g_pDC = new MDrawContextR2(RGetDevice());

#ifndef _FASTDEBUG
	if( ZGetInitialLoading()->IsUseEnable() )
	{
		if( ZGetLocale()->IsTeenMode() )
		{
			ZGetInitialLoading()->AddBitmap( 0, "Interface/Default/LOADING/loading_teen.jpg" );
		}
		else
		{
			ZGetInitialLoading()->AddBitmap( 0, "Interface/Default/LOADING/loading_adult.jpg" );
		}
		ZGetInitialLoading()->AddBitmapBar( "Interface/Default/LOADING/loading.bmp" );
		ZGetInitialLoading()->SetText( g_pDefFont, 10, 30, cstrReleaseDate );

		ZGetInitialLoading()->SetPercentage( 0.0f );
		ZGetInitialLoading()->Draw( MODE_FADEIN, 0 , true );
	}
#endif

	g_Mint.Initialize(800, 600, g_pDC, g_pDefFont);
	Mint::GetInstance()->SetHWND(RealSpace2::g_hWnd);

	mlog("main : g_Mint.Initialize() \n");

	ZLoadingProgress appLoading("application");
	if(!g_App.OnCreate(&appLoading))
	{
		ZGetInitialLoading()->Release();
		return R_ERROR_LOADING;
	}
	
	mlog("main : g_App.OnCreate() \n");

	ZGetSoundEngine()->SetEffectVolume(Z_AUDIO_EFFECT_VOLUME);
	ZGetSoundEngine()->SetMusicVolume(Z_AUDIO_BGM_VOLUME);
	ZGetSoundEngine()->SetEffectMute(Z_AUDIO_EFFECT_MUTE);
	ZGetSoundEngine()->SetMusicMute(Z_AUDIO_BGM_MUTE);

	g_Mint.SetWorkspaceSize(g_ModeParams.nWidth, g_ModeParams.nHeight);
	g_Mint.GetMainFrame()->SetSize(g_ModeParams.nWidth, g_ModeParams.nHeight);
	ZGetOptionInterface()->Resize(g_ModeParams.nWidth, g_ModeParams.nHeight);
    
	// Default Key
	for(int i=0; i<ZACTION_COUNT; i++){
		ZACTIONKEYDESCRIPTION& keyDesc = ZGetConfiguration()->GetKeyboard()->ActionKeys[i];
		g_pInput->RegisterActionKey(i, keyDesc.nVirtualKey);
		if(keyDesc.nVirtualKeyAlt!=-1)
			g_pInput->RegisterActionKey(i, keyDesc.nVirtualKeyAlt);
	}

	g_App.SetInitialState();

	ZGetFlashBangEffect()->SetDrawCopyScreen(true);

	ZGetInitialLoading()->SetLoadingStr("Done.");
	if( ZGetInitialLoading()->IsUseEnable() )
	{
#ifndef _FASTDEBUG
		ZGetInitialLoading()->SetPercentage( 100.f );
		ZGetInitialLoading()->Draw( MODE_FADEOUT, 0 ,true  );
#endif
		ZGetInitialLoading()->Release();
	}

	mlog("main : OnCreate() done\n");

	SetFocus(g_hWnd);

	return R_OK;
}

RRESULT OnDestroy(void *pParam)
{
	mlog("main : OnDestroy()\n");

	g_App.OnDestroy();

	SAFE_DELETE(g_pDefFont);

	g_Mint.Finalize();

	mlog("main : g_Mint.Finalize()\n");

	SAFE_DELETE(g_pInput);
	g_DInput.Destroy();

	mlog("main : g_DInput.Destroy()\n");

	mlog("main : g_App.OnDestroy()\n");

	ZGetConfiguration()->Destroy();

	mlog("main : ZGetConfiguration()->Destroy()\n");

	delete g_pDC;

	struct _finddata_t c_file;
	intptr_t hFile;
	char szFileName[256];
#define FONT_DIR	"Font/"
#define FONT_EXT	"ttf"
	if( (hFile = _findfirst(FONT_DIR" *." FONT_EXT, &c_file )) != -1L ){
		do{
			strcpy_safe(szFileName, FONT_DIR);
			strcat(szFileName, c_file.name);
			RemoveFontResource(szFileName);
		}while( _findnext( hFile, &c_file ) == 0 );
		_findclose(hFile);
	}

	MFontManager::Destroy();
	MBitmapManager::Destroy();
	MBitmapManager::DestroyAniBitmap();

	mlog("main : MBitmapManager::DestroyAniBitmap()\n");

	ZBasicInfoItem::Release(); 

	ZGetStencilLight()->Destroy();
	LightSource::Release();

	RBspObject::DestroyShadeMap();
	RDestroyLenzFlare();
	RAnimationFileMgr::GetInstance()->Destroy();
	ZStringResManager::FreeInstance();

	mlog("main : OnDestroy() done\n");

	return R_OK;
}

RRESULT OnUpdate(void* pParam)
{
	__BP(100, "main::OnUpdate");

	g_pInput->Update();

	g_App.OnUpdate();

	__EP(100);

	return R_OK;
}

RRESULT OnRender(void *pParam)
{
	auto mainOnRender = MBeginProfile("main::OnRender");
	if (!RIsActive() && RIsFullscreen())
		return R_NOTREADY;

	g_App.OnDraw();

	int nFPSLimit = ZGetConfiguration()->GetFPSLimit(); // Static object, FPS limit is set in ctor
	if (nFPSLimit > 0)
	{
		unsigned __int64 nTPS, CurTime;
		QueryPerformanceFrequency((PLARGE_INTEGER)&nTPS);
		QueryPerformanceCounter((PLARGE_INTEGER)&CurTime);

		static int nFrames = 0;
		static u64 LastSec = 0;

		if (CurTime - LastSec > nTPS){
			QueryPerformanceCounter((PLARGE_INTEGER)&LastSec);
			nFrames = 0;
		}

		double fActual = double(nFrames) / (nFPSLimit - 1);
		double fGoal = double((CurTime - LastSec) % nTPS) / nTPS;
		int nSleep = int((fActual - fGoal) * 1000);
		if (nSleep > 0){
			if (nSleep > 250)
				MLog("Large sleep %d!\n", nSleep);
			else
				Sleep(nSleep);
		}

		nFrames++;
	}

	if(g_pDefFont) {
		char buf[512];
		size_t y_offset{};
		auto PrintText = [&](const char* Format, ...)
		{
			va_list va;
			va_start(va, Format);
			vsprintf_safe(buf, Format, va);
			va_end(va);
			g_pDefFont->m_Font.DrawText(MGetWorkspaceWidth() - 200, y_offset, buf);
			y_offset += 20;
		};

		PrintText("FPS: %3.3f", g_fFPS);

#ifdef _DEBUG
		if (ZGetGame() && ZGetGame()->m_pMyCharacter)
		{
			v3 pos = ZGetGame()->m_pMyCharacter->GetPosition();
			PrintText("Pos: %d, %d, %d", int(pos.x), int(pos.y), int(pos.z));
			auto&& dir = ZGetGame()->m_pMyCharacter->GetDirection();
			PrintText("Dir: %f, %f, %f", dir.x, dir.y, dir.z);

			if (ZGetGame()->m_pMyCharacter->m_pVMesh)
			{
				pos = ZGetGame()->m_pMyCharacter->m_pVMesh->GetHeadPosition();
				PrintText("Head pos: %d, %d, %d", int(pos.x), int(pos.y), int(pos.z));

				auto lower = ZGetGame()->m_pMyCharacter->GetStateLower();
				auto upper = ZGetGame()->m_pMyCharacter->GetStateUpper();

				PrintText("Lower ani: %s\n", g_AnimationInfoTableLower[lower].Name);
				PrintText("Upper ani: %s\n", g_AnimationInfoTableUpper[upper].Name);
			}
		}
#endif
	}

	g_RGMain->OnRender();

	MEndProfile(mainOnRender);

	return R_OK;
}

RRESULT OnInvalidate(void *pParam)
{
	MBitmapR2::m_dwStateBlock=NULL;

	g_App.OnInvalidate();
	
	return R_OK;
}

RRESULT OnRestore(void *pParam)
{
	for(int i=0; i<MBitmapManager::GetCount(); i++){
		MBitmapR2* pBitmap = (MBitmapR2*)MBitmapManager::Get(i);
		pBitmap->OnLostDevice();
	}

	g_App.OnRestore();

	return R_OK;
}

RRESULT OnActivate(void *pParam)
{
	if (ZGetGameInterface() && ZGetGameClient() && Z_ETC_BOOST)
		ZGetGameClient()->PriorityBoost(true);
	return R_OK;
}

RRESULT OnDeActivate(void *pParam)
{
	if (ZGetGameInterface() && ZGetGameClient())
		ZGetGameClient()->PriorityBoost(false);
	return R_OK;
}

RRESULT OnError(void *pParam)
{
	mlog("RealSpace::OnError(%d) \n", RGetLastError());

	switch (RGetLastError())
	{
	case RERROR_INVALID_DEVICE:
		{
			D3DADAPTER_IDENTIFIER9 *ai=RGetAdapterID();
			char szLog[512];
			ZTransMsg( szLog, MSG_DONOTSUPPORT_GPCARD, 1, ai->Description);

			int ret=MessageBox(NULL, szLog, ZMsg( MSG_WARNING), MB_YESNO);
			if(ret!=IDYES)
				return R_UNKNOWN;
		}
		break;
	case RERROR_CANNOT_CREATE_D3D:
		{
			ShowCursor(TRUE);

			char szLog[512];
			sprintf_safe(szLog, ZMsg( MSG_DIRECTX_NOT_INSTALL));

			int ret=MessageBox(NULL, szLog, ZMsg( MSG_WARNING), MB_YESNO);
			if(ret==IDYES)
			{
				ShellExecute(g_hWnd, "open", ZMsg( MSG_DIRECTX_DOWNLOAD_URL), NULL, NULL, SW_SHOWNORMAL); 
			}
		}
		break;

	};

	return R_OK;
}

static void SetModeParams()
{
	g_ModeParams.FullscreenMode = ZGetConfiguration()->GetVideo()->FullscreenMode;
	g_ModeParams.nWidth = ZGetConfiguration()->GetVideo()->nWidth;
	g_ModeParams.nHeight = ZGetConfiguration()->GetVideo()->nHeight;

}

static int FindStringPos(char* str,char* word)
{
	if(!str || str[0]==0)	return -1;
	if(!word || word[0]==0)	return -1;

	int str_len = (int)strlen(str);
	int word_len = (int)strlen(word);

	char c;
	bool bCheck = false;

	for(int i=0;i<str_len;i++) {
		c = str[i];
		if(c == word[0]) {

			bCheck = true;

			for(int j=1;j<word_len;j++) {
				if(str[i+j]!=word[j]) {
					bCheck = false;
					break;
				}
			}

			if(bCheck) {
				return i;
			}
		}
	}
	return -1;
}

bool FindCrashFunc(char* pName)
{
	if(!pName) return false;

	FILE *fp;
	fp = fopen( "mlog.txt", "r" );
	if(fp==NULL)  return false;

	fseek(fp,0,SEEK_END);
	int size = ftell(fp);
	fseek(fp,0,SEEK_SET);

	char* pBuffer = new char [size];

	fread(pBuffer,1,size,fp);

	fclose(fp);

	int posSource = FindStringPos(pBuffer,"ublish");
	if(posSource==-1) return false;

	int posA = FindStringPos(pBuffer+posSource,"Function Name");
	int posB = posA + FindStringPos(pBuffer+posSource+posA,"\n");

	if(posA==-1) return false;
	if(posB==-1) return false;

	posA += 16;

	int memsize = posB-posA;
	memcpy(pName,&pBuffer[posA+posSource],memsize);

	pName[memsize] = 0;

	delete [] pBuffer;

	for(int i=0;i<memsize;i++) {
		if(pName[i]==':') {
			pName[i] = '-';
		}
	}

	return true;
}

void HandleExceptionLog()
{
	#define ERROR_REPORT_FOLDER	"ReportError"

	extern char* logfilename;

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	hFind = FindFirstFile(ERROR_REPORT_FOLDER, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		if (!CreateDirectory("ReportError", NULL)) {
			MessageBox(g_hWnd, "ReportError ������ ������ �� �����ϴ�.", APPLICATION_NAME , MB_ICONERROR|MB_OK);
			return;
		}
	} else 	{
		FindClose(hFind);
	}

	ZGameClient* pClient = (ZGameClient*)ZGameClient::GetInstance();

	char* pszCharName = NULL;
	MUID uidChar;
	MMatchObjCache* pObj;
	char szPlayer[128];

	if( pClient ) {

		uidChar = pClient->GetPlayerUID();
		pObj = pClient->FindObjCache(uidChar);
		if (pObj)
			pszCharName = pObj->GetName();

		wsprintf(szPlayer, "%s(%d%d)", pszCharName?pszCharName:"Unknown", uidChar.High, uidChar.Low);
	}
	else { 
		wsprintf(szPlayer, "Unknown(-1.-1)");
	}

		time_t currtime;
		time(&currtime);
		struct tm* pTM = localtime(&currtime);

		char cFuncName[1024];

		if(FindCrashFunc(cFuncName)==false) {
			strcpy_safe(cFuncName,"Unknown Error");
		}

		char szFileName[_MAX_DIR], szDumpFileName[_MAX_DIR];
		wsprintf(szFileName, "%s_%s_%.2d%.2d_%.2d%.2d_%s_%s", cFuncName,
				APPLICATION_NAME, pTM->tm_mon+1, pTM->tm_mday, pTM->tm_hour, pTM->tm_min, szPlayer, "mlog.txt");
		wsprintf(szDumpFileName, "%s.dmp", szFileName);

		char szFullFileName[_MAX_DIR], szDumpFullFileName[_MAX_DIR];
		wsprintf(szFullFileName, "%s/%s", ERROR_REPORT_FOLDER, szFileName);
		wsprintf(szDumpFullFileName, "%s/%s", ERROR_REPORT_FOLDER, szDumpFileName);

		if (CopyFile("mlog.txt", szFullFileName, TRUE))
		{
			CopyFile("Gunz.dmp", szDumpFullFileName, TRUE);

			// BAReport ����
			char szCmd[4048];
			char szRemoteFileName[_MAX_DIR], szRemoteDumpFileName[_MAX_DIR];
			wsprintf(szRemoteFileName, "%s/%s/%s", ZGetConfiguration()->GetBAReportDir(), "gunzlog", szFileName);
			wsprintf(szRemoteDumpFileName, "%s/%s/%s", ZGetConfiguration()->GetBAReportDir(), "gunzlog", szDumpFileName);

			wsprintf(szCmd, "BAReport app=%s;addr=%s;port=21;id=ftp;passwd=ftp@;user=%s;localfile=%s,%s;remotefile=%s,%s", 
				APPLICATION_NAME, ZGetConfiguration()->GetBAReportAddr(), szPlayer, szFullFileName, szDumpFullFileName, szRemoteFileName, szRemoteDumpFileName);

			WinExec(szCmd, SW_SHOW);

			FILE *file = fopen("bareportpara.txt","w+");
			fprintf(file,szCmd);
			fclose(file);
		}	
//	}
}

LONG_PTR FAR PASCAL WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CREATE:
			if (strlen(Z_LOCALE_HOMEPAGE_TITLE) > 0)
			{
				ShowIExplorer(false, Z_LOCALE_HOMEPAGE_TITLE);
			}
			break;
		case WM_DESTROY:
			if (strlen(Z_LOCALE_HOMEPAGE_TITLE) > 0)
			{
				ShowIExplorer(true, Z_LOCALE_HOMEPAGE_TITLE);
			}
			break;
		case WM_SETCURSOR:
			if(ZApplication::GetGameInterface())
				ZApplication::GetGameInterface()->OnResetCursor();
			return TRUE; // prevent Windows from setting cursor to window class cursor

			/*
		case  WM_LBUTTONDOWN:
			SetCapture(hWnd);
			return TRUE;
		case WM_LBUTTONUP:
			ReleaseCapture();
			return TRUE;
			*/
		case WM_KEYDOWN:
			{
				bool b = false;
			}
	}

	if(Mint::GetInstance()->ProcessEvent(hWnd, message, wParam, lParam)==true)
		return 0;

	// thread safe�ϱ����� ����
	if (message == WM_CHANGE_GAMESTATE)
	{
		_ZChangeGameState(wParam);
	}


	return DefWindowProc(hWnd, message, wParam, lParam);
}

void ClearTrashFiles()
{
}

bool CheckFileList()
{
	return true;
	MZFileSystem *pfs=ZApplication::GetFileSystem();
	MZFile mzf;
	if(!mzf.Open("system/filelist.xml",pfs))
		return false;

	char *buffer;
	buffer=new char[mzf.GetLength()+1];
	mzf.Read(buffer,mzf.GetLength());
	buffer[mzf.GetLength()]=0;

	MXmlDocument aXml;
	aXml.Create();
	if(!aXml.LoadFromMemory(buffer))
	{
		delete buffer;
		return false;
	}

	delete buffer;

	int iCount, i;
	MXmlElement		aParent, aChild;
	aParent = aXml.GetDocumentElement();
	iCount = aParent.GetChildNodeCount();

	char szTagName[256];
	for (i = 0; i < iCount; i++)
	{
		aChild = aParent.GetChildNode(i);
		aChild.GetTagName(szTagName);
		if(_stricmp(szTagName,"FILE")==0)
		{
			char szContents[256],szCrc32[256];
			aChild.GetAttribute(szContents,"NAME");
			aChild.GetAttribute(szCrc32,"CRC32");

			if(_stricmp(szContents,"config.xml")!=0)
			{
				unsigned int crc32_list = pfs->GetCRC32(szContents);
				unsigned int crc32_current;
				sscanf(szCrc32,"%x",&crc32_current);

				if(crc32_current!=crc32_list)
				{
					mlog("crc error , file %s ( current = %x, original = %x ).\n",szContents,crc32_current,crc32_list);
					// ��� ������ �˻�� �Ѵ�
					//	return false; 
				}
			}
		}
	}

	return true;
}

enum RBASE_FONT{
	RBASE_FONT_GULIM = 0,
	RBASE_FONT_BATANG = 1,

	RBASE_FONT_END
};

static int g_base_font[RBASE_FONT_END];
static char g_UserDefineFont[256];

bool _GetFileFontName(char* pUserDefineFont)
{
	if(pUserDefineFont==NULL) return false;

	FILE* fp = fopen("_Font", "rt");
	if (fp) {
		fgets(pUserDefineFont,256, fp);
		fclose(fp);
		return true;
	}
	return false;
}


bool CheckFont()
{
	char FontPath[MAX_PATH];
	char FontNames[MAX_PATH+100];

	::GetWindowsDirectory(FontPath, MAX_PATH);

	strcpy_safe(FontNames,FontPath);
	strcat(FontNames, "\\Fonts\\gulim.ttc");

	if (_access(FontNames,0) != -1)	{ g_base_font[RBASE_FONT_GULIM] = 1; }
	else							{ g_base_font[RBASE_FONT_GULIM] = 0; }

	strcpy_safe(FontNames,FontPath);
	strcat(FontNames, "\\Fonts\\batang.ttc");

	if (_access(FontNames,0) != -1)	{ g_base_font[RBASE_FONT_BATANG] = 1; }
	else							{ g_base_font[RBASE_FONT_BATANG] = 0; }

	//	strcpy_safe(FontNames,FontPath);
	//	strcat(FontNames, "\\Fonts\\System.ttc");
	//	if (_access(FontNames,0) != -1)	{ g_font[RBASE_FONT_BATANG] = 1; }
	//	else							{ g_font[RBASE_FONT_BATANG] = 0; }

	if(g_base_font[RBASE_FONT_GULIM]==0 && g_base_font[RBASE_FONT_BATANG]==0) {//�Ѵپ�����..

		if( _access("_Font",0) != -1) { // �̹� ��ϵǾ� �ִٸ�..
			_GetFileFontName( g_UserDefineFont );
		}
		else {

			int hr = IDOK;

			//hr = ::MessageBox(NULL,"������ ��ǻ�Ϳ��� ��� ����ϴ� (����,����) ��Ʈ�� ���� �� �����ϴ�.\n �ٸ� ��Ʈ�� ���� �Ͻðڽ��ϱ�?","�˸�",MB_OKCANCEL);
			//hr = ::MessageBox(NULL,"������ ��ǻ�Ϳ��� ��� ����ϴ� (����,����) ��Ʈ�� ���� �� �����ϴ�.\n ��� ���� �Ͻðڽ��ϱ�?","�˸�",MB_OKCANCEL);

			if(hr==IDOK) {
				/*			
				CFontDialog dlg;
				if(dlg.DoModal()==IDOK) {
				CString facename = dlg.GetFaceName();
				lstrcpy_safe((LPSTR)g_UserDefineFont,(LPSTR)facename.operator const char*());

				hr = ::MessageBox(NULL,"�����Ͻ� ��Ʈ�� ���� �Ͻðڽ��ϱ�?","�˸�",MB_OKCANCEL);

				if(hr==IDOK)
				_SetFileFontName(g_UserDefineFont);
				}
				*/
				return true;
			}
			else {
				return false;
			}
		}
	}
	return true;
}

void CheckFileAssociation()
{
#define GUNZ_REPLAY_CLASS_NAME	"GunzReplay"

	// üũ�غ��� ����� �ȵǾ������� ����Ѵ�. ����ڿ��� ������� �ְڴ�.
	char szValue[256];
	if (!MRegistry::Read(HKEY_CLASSES_ROOT, "." GUNZ_REC_FILE_EXT, NULL, szValue))
	{
		MRegistry::Write(HKEY_CLASSES_ROOT, "." GUNZ_REC_FILE_EXT, NULL, GUNZ_REPLAY_CLASS_NAME);

		char szModuleFileName[_MAX_PATH] = { 0, };
		GetModuleFileName(NULL, szModuleFileName, _MAX_DIR);

		char szCommand[_MAX_PATH];
		sprintf_safe(szCommand, "\"%s\" \"%%1\"", szModuleFileName);

		MRegistry::Write(HKEY_CLASSES_ROOT, GUNZ_REPLAY_CLASS_NAME "\\shell\\open\\command", NULL, szCommand);

		SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_FLUSH, NULL, NULL);
	}
}

void UpgradeMrsFile()
{
	char temp_path[ 1024];
	sprintf_safe( temp_path,"*");

	FFileList file_list;
	GetFindFileListWin(temp_path,".mrs",file_list);
	file_list.UpgradeMrs();
}

HANDLE Mutex = 0;

#ifdef _HSHIELD
int __stdcall AhnHS_Callback(long lCode, long lParamSize, void* pParam);
#endif

DWORD g_dwMainThreadID;

LONG __stdcall Filter(_EXCEPTION_POINTERS* p)
{
	return CrashExceptionDump(p, "Gunz.dmp");
}

int PASCAL WinMain(HINSTANCE this_inst, HINSTANCE prev_inst, LPSTR cmdline, int cmdshow)
{
	SetUnhandledExceptionFilter(Filter);

	_set_invalid_parameter_handler([](const wchar_t* expression,
		const wchar_t* function,
		const wchar_t* file,
		unsigned int line,
		uintptr_t pReserved)
	{
		MLog("Invalid parameter detected in function %s.\nFile: %s, line: %d.\nExpression: %s.\n", function, file, line, expression);
	});

	g_dwMainThreadID = GetCurrentThreadId();
	
#ifdef _MTRACEMEMORY
	MInitTraceMemory();
#endif

	char szModuleFileName[_MAX_DIR] = {0,};
	GetModuleFileName(NULL, szModuleFileName, _MAX_DIR);
	PathRemoveFileSpec(szModuleFileName);
	SetCurrentDirectory(szModuleFileName);

#ifdef _PUBLISH
	Mutex = CreateMutex(NULL, TRUE, "RGunz");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		MessageBox(0, "Refined Gunz is already running", "RGunz", 0);
		exit(-1);
		return 0;
	}
#endif

	InitLog(MLOGSTYLE_DEBUGSTRING | MLOGSTYLE_FILE);

	ClearTrashFiles();

	srand((unsigned int)time(nullptr));

	mlog("Refined Gunz version %d launched. Build date: " __DATE__ " " __TIME__ "\n", RGUNZ_VERSION);

	char szDateRun[128]="";
	char szTimeRun[128]="";
	_strdate( szDateRun );
	_strtime( szTimeRun );
	mlog("Log time (%s %s)\n", szDateRun, szTimeRun);


#ifndef _PUBLISH
	mlog("cmdline = %s\n",cmdline);
#endif

#ifndef _LAUNCHER
	// Don't know why this is here
	//UpgradeMrsFile();// mrs1 �̶�� mrs2�� ���׷��̵� �Ѵ�..
#endif

	MSysInfoLog();

	CheckFileAssociation();

	// Initialize MZFileSystem - MUpdate 
	MRegistry::szApplicationName=APPLICATION_NAME;

	g_App.InitFileSystem();

#ifdef _PUBLISH
//	#ifndef NETMARBLE_VERSION
		MZFile::SetReadMode( MZIPREADFLAG_MRS2 );
//	#endif
#endif

	ZGetConfiguration()->Load();

	g_RGMain = std::make_unique<RGMain>();

	ZStringResManager::MakeInstance();
	if( !ZApplication::GetInstance()->InitLocale() )
	{
		MLog("Locale Init error !!!\n");
		return false;
	}

	if( !ZGetConfiguration()->LateStringConvert() )
	{
		MLog( "main.cpp - Late string convert fail.\n" );
		return false;
	}

	DWORD ver_major = 0;
	DWORD ver_minor = 0;
	TCHAR ver_letter = ' ';

	if (ZApplication::GetInstance()->ParseArguments(cmdline) == false)
	{
		// Korean or Japan Version
		if ((ZGetLocale()->GetCountry() == MC_KOREA) || (ZGetLocale()->GetCountry() == MC_JAPAN))
		{
			mlog("Routed to Website \n");

			ShellExecute(NULL, "open", ZGetConfiguration()->GetLocale()->szHomepageUrl, NULL, NULL, SW_SHOWNORMAL);

			char szMsgWarning[128]="";
			char szMsgCertFail[128]="";
			ZTransMsg(szMsgWarning,MSG_WARNING);
			ZTransMsg(szMsgCertFail,MSG_REROUTE_TO_WEBSITE);

			mlog(szMsgWarning);
			mlog(" : ");
			mlog(szMsgCertFail);

			return 0;
		}
		else
		{
			return 0;
		}
	}

	if(!InitializeNotify(ZApplication::GetFileSystem())) {
		MLog("Check notify.xml\n");
		return 0;
	}

	if(CheckFont()==false) {
		MLog("��Ʈ�� ���� ������ ��Ʈ ������ ���\n");
		return 0;
	}

	RSetFunction(RF_CREATE	,	OnCreate);
	RSetFunction(RF_RENDER	,	OnRender);
	RSetFunction(RF_UPDATE	,	OnUpdate);
	RSetFunction(RF_DESTROY ,	OnDestroy);
	RSetFunction(RF_INVALIDATE,	OnInvalidate);
	RSetFunction(RF_RESTORE,	OnRestore);
	RSetFunction(RF_ACTIVATE,	OnActivate);
	RSetFunction(RF_DEACTIVATE,	OnDeActivate);
	RSetFunction(RF_ERROR,		OnError);

	SetModeParams();

	int nReturn = RMain(APPLICATION_NAME, this_inst, prev_inst, cmdline, cmdshow,
		&g_ModeParams, WndProc, IDI_ICON1);

#ifdef _MTRACEMEMORY
	MShutdownTraceMemory();
#endif
	return nReturn;

#ifdef _PUBLISH
	if (Mutex != 0) CloseHandle(Mutex);
#endif

	return 0;
}