//
//	Misc Functions about File
//
//                                              written by lee jang ho
//
//////////////////////////////////////////////////////////////////////
#ifndef _FILEINFO_H
#define _FILEINFO_H

#include <windows.h>
#include <time.h>

// ������ �ֱ� ������Ʈ�� �ð� ���
BOOL GetLastUpdate(const char *pFileName, FILETIME *ft);

// ������ ������Ʈ �Ǿ��°�?
//		pFileName
//		ot			:	���� �ð� ( ���� �������� �� �ð� )
BOOL IsModifiedOutside(const char *pFileName, FILETIME ot);

// Extension ����
BOOL RemoveExtension(char *pRemoveExt, int maxlen, const char *pFileName);

// Extension ��ü
void ReplaceExtension(char *pTargetName, int maxlen, const char *pSourceName, char *pExt);

template<size_t size> void GetRelativePath(char(&pRelativePath)[size], const char *pBasePath, const char *pPath)
{
	GetRelativePath(pRelativePath, size, pBasePath, pPath);
}

// ��� ��� ���
void GetRelativePath(char *pRelativePath, int maxlen, const char *pBasePath, const char *pPath);

// ���� ��� ���
void GetFullPath(char *pFullPath, int maxlen, const char *pBasePath, const char *pRelativePath);
//�� ���� ��� ���... current directory�� ��������...
void GetFullPath(char *pFullPath, int maxlen, const char *pRelativePath);

template<size_t size> void GetPurePath(char(&pPurePath)[size], const char *pFilename) {
	GetPurePath(pPurePath, size, pFilename);
}
// path �� ����..
void GetPurePath(char *pPurePath, int maxlen, const char *pFilename);
// path �� extension�� ������ ������ �����̸� ���.
template <size_t size>
void GetPureFilename(char (&PureFilename)[size],const char *pFilename)
{
	char drive[_MAX_DRIVE], dir[_MAX_DIR], ext[_MAX_EXT];
	_splitpath_s(pFilename, drive, dir, PureFilename, ext);
}
// extension �� ����
template <size_t size>
void GetPureExtension(char (&PureExtension)[size],const char *pFilename)
{
	char drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME];
	_splitpath_s(pFilename, drive, dir, fname, PureExtension);
}

// ���� ����ΰ�? ( ��Ʈ��ũ ��δ� �������� ���� )
BOOL IsFullPath(const char *pPath);

// ��� �б� ( ����� ���� int�� ��� ��ü ũ�⸦ ������ �ִ�. )
BOOL ReadHeader(HANDLE hFile, void *pHeader, int nHeaderSize);

// File�� CheckSum�� ���Ѵ�. (��¥, ������, ������ ����)
DWORD GetFileCheckSum(char* pszFileName);

// ������ �����ϴ°�?
bool IsExist(const char *filename);

// �θ� ���丮 �̸��� ��´�.
void GetParentDirectory(char* pszFileName);

// �־��� ��α����� ���丮�� �����Ѵ�.
bool MakePath(const char* pszFileName);

// time_t �� FILETIME ���� ��ȯ Code from MSDN
void time_tToFILETIME(time_t t, LPFILETIME pft);

// ������ WriteTime �� �����Ѵ�
BOOL MSetFileTime(LPCTSTR lpszPath, FILETIME ft);

bool GetMyDocumentsPath(char* path);

bool CreatePath(char* path);


#ifdef WIN32
#pragma comment(lib, "Shlwapi.lib")
#endif

#endif	// _FILEINFO_H
