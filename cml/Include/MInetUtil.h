#ifndef _MINETUTIL_H
#define _MINETUTIL_H

#include <string>


/// . �ִ� IP ���ڿ��� . ���� IP ���ڿ�(12����Ʈ)�� ��ȯ
void MConvertCompactIP(char* szOut, int maxlen, const char* szInputDottedIP);


template <size_t size>
void GetLocalIP(char (&szOutIP)[size])
{
	char szHostName[256];
	PHOSTENT pHostInfo;

	if (gethostname(szHostName, sizeof(szHostName)) == 0)
	{
		if ((pHostInfo = gethostbyname(szHostName)) != NULL)
		{
			auto ip = inet_ntoa(*(struct in_addr *)*pHostInfo->h_addr_list);
			strcpy_safe(szOutIP, ip);
		}
	}
}


#endif