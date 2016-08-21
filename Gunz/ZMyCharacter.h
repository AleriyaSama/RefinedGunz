#ifndef _ZMYCHARACTER_H
#define _ZMYCHARACTER_H


//#pragma once

#include "MRTTI.h"
#include "ZCharacter.h"

enum ZChangeWeaponType
{
	ZCWT_NONE = 0,
	ZCWT_PREV,
	ZCWT_NEXT,
	ZCWT_MELEE,
	ZCWT_PRIMARY,
	ZCWT_SECONDARY,
	ZCWT_CUSTOM1,
	ZCWT_CUSTOM2,
	ZCWT_END,
};

enum ZUsingStamina{
	ZUS_Tumble = 0,// + dash
	ZUS_Jump,
};

enum ZDELAYEDWORK {
	ZDW_RECOIL,
	ZDW_UPPERCUT,	// ��� ����
	ZDW_DASH,		// �ܰ� Ư����
	ZDW_MASSIVE,		// ��Ƽ� Į��
	ZDW_RG_SLASH,
	ZDW_RG_MASSIVE,
	ZDW_RG_RECOIL,
};

struct ZDELAYEDWORKITEM {
	float fTime;		// ����� �ð�
	ZDELAYEDWORK nWork;	// ����� ���        
	void *Data;
};

typedef list<ZDELAYEDWORKITEM*> ZDELAYEDWORKLIST;


class ZMyCharacter : public ZCharacter {
	MDeclareRTTI;
protected:
	virtual void OnDraw();
public:
#ifdef _DEBUG
	bool m_bGuardTest;
#endif

	float	m_fDeadTime;		// ���� �ð�

	float	m_fNextShotTimeType[MMCIP_END];
	float	m_fNextShotTime;	// ������ ���� �߻� ���� �ð�
	float	m_fWallJumpTime;

	int		m_nTumbleDir;

	float LastDamagedTime;

	// ��ŷ�Ǵ� �÷��׵�
	union {
		struct {
			bool	m_bWallHang:1;		// ���� �Ŵ޸� �����϶� true

			bool	m_bLimitJump:1;
			bool	m_bLimitTumble:1;
			bool	m_bLimitWall:1;

			bool	m_bMoveLimit:1;
			bool	m_bMoving:1;

			bool	m_bReleasedJump:1;				// ������ �ѹ� �ϸ� �����ٰ� ������ �ؾ��Ѵ�.
			bool	m_bJumpQueued:1;
			bool	m_bWallJumpQueued:1;
			bool	m_bHangSuccess:1;
			bool	m_bSniferMode:1;

			bool	m_bEnterCharge:1;				// ù��° Į������ ��� �������־�����.

			bool	m_bJumpShot:1;
			bool	m_bShot:1;						// Į�����϶�.
			bool	m_bShotReturn:1;				// Į���ϴ� idle �ǵ��ƿ��� ������

			bool	m_bSkill:1;						// �������� ������ ��ų
			bool	m_b1ShotSended:1;				// ù��° Į���� �����̰� �ִ�

			bool	m_bSplashShot:1;				// ������ ���÷��� Į�� �ؾ� �ϴ���..
			bool	m_bGuard:1;
			bool	m_bGuardBlock_ret:1;
			bool	m_bGuardStart:1;
			bool	m_bGuardCancel:1;
			bool	m_bGuardKey:1;
			bool	m_bGuardByKey:1;
			bool	m_bDrop:1;
			bool	m_bSlash:1;				// ����� ����
			bool	m_bJumpSlash:1;			// ���߿��� ����� ����
			bool	m_bJumpSlashLanding:1;	// ���� ��������
			bool	m_bReserveDashAttacked:1;

			bool	m_bLButtonPressed:1;			// LButton �������ִ���.
			bool	m_bLButtonFirstPressed:1;		// LButton �� ó������ ����������
			bool	m_bLButtonQueued:1;				// LButton ����Ǿ��ִ���

			bool	m_bRButtonPressed:1;
			bool	m_bRButtonFirstPressed:1;		// RButton �� ó������ ����������
			bool	m_bRButtonFirstReleased:1;		// RButton �� �������ִٰ� ��������
		};

		DWORD dwFlags[2];	// 2005.12.9 ���� 35��
	}; // ��ŷ ��.

	bool bWasPressingSecondaryLastFrame;

	float	m_fSplashShotTime;

	float	m_fLastJumpPressedTime;			// ���� ���� (�ణ �̸� ������ �ڴ�)
	float	m_fJump2Time;					// �������� �� �ð�
	float	m_fHangTime;
	rvector m_HangPos;

	int		m_nWallJump2Dir;

// ��ư ���� ����	: �ʿ��ϸ� �� �����. UpdateButtonState() ���� ����
	float	m_fLastLButtonPressedTime;		// LButton �� ó������ ������ �ð�
	float	m_fLastRButtonPressedTime;		// RButton �� ������ �ð�

	int		m_nShot;						// Į�� ���ӱ��� ���° ����
	int		m_nJumpShotType;
	float	m_f1ShotTime;					// ù��° Į�� ������ �ð�

	float	m_fSkillTime;					// �ߵ��� �ð�

	/*
	bool	m_bSkillSended;					// �����Ƶ� ������ �����̰� �ִ�
	*/

	float	m_fLastShotTime;				// ������ �ѿ� ���� �ð�
	int		m_nGuardBlock;
	float	m_fGuardStartTime;				// ���� �ߵ��ð�

	float	m_fDropTime;			// ����ð�.

	float	m_bJumpSlashTime;		// ���� ������ ���۽ð�

	rvector	m_vReserveDashAttackedDir;
	float	m_fReserveDashAttackedTime;
	MUID	m_uidReserveDashAttacker;

	float	m_fStunEndTime;				///< stun Ǯ���� �ð�, 5��Ÿ���� ����


	void WallJump2();

	ZMyCharacter();
	~ZMyCharacter();

	void InitSpawn();//�ַο����� ���忡 �ش�..

	void ProcessInput(float fDelta);

	bool CheckWall(rvector& Pos);

	virtual void UpdateAnimation();
	virtual void OnUpdate(float fTime);

	virtual void UpdateLimit();
	
	virtual void OnChangeWeapon(const char* WeaponModelName) override;

	void Animation_Reload();

	void OnTumble(int nDir);
	virtual void OnBlast(rvector &dir);
	void OnRecoil(int nControlability);
	void OnDashAttacked(rvector &dir);
	void ReserveDashAttacked(MUID uid, float time,rvector &dir);

	virtual void InitBullet();
	virtual void InitStatus();
	virtual void InitRound();
	
	virtual void SetDirection(const rvector& dir);
	virtual void OnDamagedAnimation(ZObject *pAttacker,int type);

	void OutputDebugString_CharacterState();

	float GetCAFactor() { return m_fCAFactor; }
	virtual bool IsGuard() const override;
	virtual bool IsGuardCustom() const override;

	void ShotBlocked();

	void ReleaseButtonState();

	void AddRecoilTarget(ZCharacter *pTarget);

	virtual void OnGuardSuccess() override;
	virtual void OnDamaged(ZObject* pAttacker, rvector srcPos,
		ZDAMAGETYPE damageType, MMatchWeaponType weaponType,
		float fDamage, float fPiercingRatio = 1.f, int nMeleeType = -1) override;
	virtual void OnKnockback(const rvector& dir, float fForce) override;
	virtual void OnMeleeGuardSuccess() override;

	virtual void OnStun(float fTime) override;

	bool IsDirLocked() const {
		return m_bSkill || m_bWallJump || m_bWallJump2 || m_bWallHang ||
			m_bTumble || m_bBlast || m_bBlastStand || m_bBlastDrop;
	}

private:
	float m_fCAFactor;		// Controllability factor for weapon spread
	float m_fElapsedCAFactorTime;

	ZDELAYEDWORKLIST m_DelayedWorkList;

	void OnDelayedWork(ZDELAYEDWORKITEM *pItem);
	void AddDelayedWork(float fTime,ZDELAYEDWORK nWork, void *Data = 0);
	void ProcessDelayedWork();

	virtual void	OnDie();
	void CalcRangeShotControllability(rvector& vOutDir, const rvector& vSrcDir, int nControllability, u32 Seed);
	void IncreaseCAFactor();
	float GetControllabilityFactor();
	void UpdateCAFactor(float fDelta);
	void ReleaseLButtonQueue();

	void UpdateButtonState();

	void ProcessShot();
	void ProcessGadget();
	void ProcessGuard();

	void OnGadget_Hanging();
	void OnGadget_Snifer();

	void OnShotCustom();
	void OnShotItem();
	void OnShotRocket();
	void OnShotMelee();
	void OnShotRange();

	void Charged();
	void EnterCharge();
	void Discharged();
	void ChargedShot();
	void JumpChargedShot();

	float GetGravityConst();
};



#ifndef _PUBLISH
// ���� ĳ���� - �׽�Ʈ�� ����Ѵ�.
class ZDummyCharacter : public ZMyCharacter
{
private:
	float m_fNextAniTime;
	float m_fElapsedTime;

	float m_fNextShotTime;
	float m_fShotElapsedTime;

	float m_fShotDelayElapsedTime;

	bool m_bShotting;
	bool m_bShotEnable;
	virtual void  OnUpdate(float fDelta);
public:
	ZDummyCharacter();
	virtual ~ZDummyCharacter();
	

	void SetShotEnable(bool bEnable) { m_bShotEnable = bEnable; }
};
#endif // #ifndef _PUBLISH

#endif