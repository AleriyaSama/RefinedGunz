// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "../../cml/Include/targetver.h"

#define POINTER_64 __ptr64


#define WIN32_LEAN_AND_MEAN		// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#ifdef MFC
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include <afx.h>
#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#endif

#include <cassert>
#define ASSERT assert

// #define _FILTER_TEST

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
