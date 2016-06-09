#ifndef _ZCHARACTEROBJECT_H
#define _ZCHARACTEROBJECT_H

#include "ZObject.h"
#include "stuff.h"

// ZCharacter �� ZActor �� ���̾��°͵��� ���� class ..

class ZShadow;

struct ZBasicInfoItem : public CMemPoolSm<ZBasicInfoItem>
{
	ZBasicInfo info;
	float	fReceivedTime;
	float	fSendTime;			// �����ð� (ping���� ����)
};

class ZBasicInfoHistory : public list<ZBasicInfoItem*> {
};


class ZCharacterObject : public ZObject
{
	MDeclareRTTI;
private:
	float			m_fTremblePower;	///< �ѿ� ������ ���� ���� ����
public:
	ZCharacterObject();
	virtual ~ZCharacterObject();

public:

	bool CreateShadow();
	void DestroyShadow();

	bool GetWeaponTypePos(WeaponDummyType type,rvector* pos,bool bLeft=false);

	int GetWeapondummyPos(rvector* pVec);

	bool GetCurrentWeaponDirection(rvector* dir);

	void UpdateEnchant();

	void DrawEnchantSub(ZC_ENCHANT etype,rvector& pos);

	void DrawEnchant(ZC_STATE_LOWER AniState_Lower,bool bCharged);
	void EnChantWeaponEffect(ZC_ENCHANT etype,int nLevel);
	void EnChantSlashEffect(rvector* pOutPos,int cnt,ZC_ENCHANT etype,bool bDoubleWeapon);
	void EnChantMovingEffect(rvector* pOutPos,int cnt,ZC_ENCHANT etype,bool bDoubleWeapon);

	MMatchItemDesc* GetEnchantItemDesc();
	ZC_ENCHANT	GetEnchantType();

	void DrawShadow();		// Manager���� ȣ���Ѵ�.
	void Draw_SetLight(rvector& vPosition);

	bool IsDoubleGun();

	void SetHero(bool bHero = true) { m_bHero = bHero; }
	bool IsHero() { return m_bHero; }

	void EmptyHistory();
	virtual bool GetHistory(rvector *pos,rvector *direction,float fTime); // ����/�������� ������ �����͸� ��´�

protected:

	bool	m_bHero;					///< ���� �����ϴ� ������� ����

public:

	ZBasicInfoHistory	m_BasicHistory;		///< ������ ���� ���ʰ��� �����͸� �������ִ´�

	char	m_pSoundMaterial[16];

	bool	m_bLeftShot;				// ��� ���� ��� ������ ���鼭 ��½..��½..

	float	m_fTime;					// �ý��� �ð�

	int		m_iDLightType;				// ����Ʈ�� ����
	float	m_fLightLife;				// ����Ʈ ���� �ð�
	rvector	m_vLightColor;				// ����Ʈ ��..

	ZShadow*	m_pshadow;				//�׸���
	bool		m_bDynamicLight;		// �߰����� ����Ʈ ȿ������

	// knockback�� ����޾ƾ��Ѵ�
	virtual void OnKnockback(const rvector& dir, float fForce);
	void SetTremblePower(float fPower)		{ m_fTremblePower = fPower; }
};

#endif//_ZCHARACTEROBJECT_H