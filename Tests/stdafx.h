#pragma once

#include "targetver.h"

#define POINTER_64 __ptr64

// Windows ��� �����Դϴ�.
#include <afxdb.h>
#include <afxtempl.h>
#include <afxdtctl.h>

#define WIN32_LEAN_AND_MEAN		// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#include <windows.h>

#include <winsock2.h>
#include <mswsock.h>

#include <crtdbg.h>

#include <mmsystem.h>
#include <shlwapi.h>
#include <shellapi.h>

// C�� ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>
#include <cstddef>
#include <comutil.h>
#include <stdio.h>