#ifndef _ZMAP_H
#define _ZMAP_H

#include "ZFilePath.h"
// �ʰ� ���õ� �͵��� �� ���� �����ô�.


class MWidget;

template<size_t size>
void ZGetCurrMapPath(char(&outPath)[size]) {
	ZGetCurrMapPath(outPath, size);
}
void ZGetCurrMapPath(char* outPath, int maxlen);

// �ش�����(�޺��ڽ�)�� ���Ӱ����� ���� �߰��Ѵ�.
bool InitMaps(MWidget *pWidget);


#endif