#pragma once

#include "MRTTI.h"
#include "ZCharacterObject.h"
#include "MUID.h"
#include "RTypes.h"
#include "RPathFinder.h"
#include "RVisualMeshMgr.h"

#include "MObjectTypes.h"
#include "ZItem.h"
#include "ZCharacterItem.h"
#include "RCharCloth.h"
#include "ZFile.h"
#include "Mempool.h"

#include "ZModule_HPAP.h"

#include <list>
#include <string>

#include "ZCharacterStructs.h"
#include "AnimationStuff.h"
#include "BasicInfoHistory.h"
#include "ZReplayStructs.h"

using namespace std;

_USING_NAMESPACE_REALSPACE2

#define MAX_SPEED			1000.f			// �ִ�ӵ�..
#define RUN_SPEED			630.f			// �޸��� �ӵ�
#define BACK_SPEED			450.f			// �ڳ� ������ ���� �ӵ�
#define ACCEL_SPEED			7000.f			// ���ӵ�
#define STOP_SPEED			3000.f			// �ƹ�Ű�� �ȴ������� ���ӵ�..
#define STOP_FORMAX_SPEED	7100.f			// �޸��� �ӵ� �̻����� �ö����� ���� �����ϴ� �ӵ�

#define CHARACTER_RADIUS	35.f		// ĳ���� �浹 ������
#define CHARACTER_HEIGHT	180.0f		// ĳ���� �浹 ����

#define ARRIVAL_TOLER		5.f

class ZShadow;

struct ZFACECOSTUME
{
	char* szMaleMeshName;
	char* szFemaleMeshName;
};


enum ZC_SKILL {

	ZC_SKILL_NONE = 0,

	ZC_SKILL_UPPERCUT,
	ZC_SKILL_SPLASHSHOT,
	ZC_SKILL_DASH,
	ZC_SKILL_CHARGEDSHOT,

	ZC_SKILL_END
};


enum ZC_DIE_ACTION
{
	ZC_DIE_ACTION_RIFLE = 0,
	ZC_DIE_ACTION_KNIFE,
	ZC_DIE_ACTION_SHOTGUN,
	ZC_DIE_ACTION_ROCKET,

	ZC_DIE_ACTION_END
};

enum ZC_SPMOTION_TYPE {

	ZC_SPMOTION_TAUNT = 0,
	ZC_SPMOTION_BOW ,
	ZC_SPMOTION_WAVE ,
	ZC_SPMOTION_LAUGH ,
	ZC_SPMOTION_CRY ,
	ZC_SPMOTION_DANCE ,

	ZC_SPMOTION_END
};

enum ZC_WEAPON_SLOT_TYPE {

	ZC_SLOT_MELEE_WEAPON = 0,
	ZC_SLOT_PRIMARY_WEAPON,
	ZC_SLOT_SECONDARY_WEAPON,
	ZC_SLOT_ITEM1,
	ZC_SLOT_ITEM2,

	ZC_SLOT_END,
};

enum ZSTUNTYPE {
	ZST_NONE	=	-1,
	ZST_DAMAGE1	=	0,
	ZST_DAMAGE2,
	ZST_SLASH,			// ������ ����
	ZST_BLOCKED,		// Į �������� ����
	ZST_LIGHTNING,		// ��æƮ�� Lightning
	ZST_LOOP,			// ��ų�� root �Ӽ�
};


class ZSlot {
public:
	ZSlot() {
		m_WeaponID = 0;
	}

	int m_WeaponID;
};

// �̰��� ĳ���ͳ��� �ְ�޴� �����ͷ� ���߿� ��ǥ ������ �ٰŰ� �ȴ�.
/*
struct ZHPItem {
	MUID muid;
	float fHP;
};
*/

//struct ZHPInfoItem : public CMemPoolSm<ZHPInfoItem>{
//	ZHPInfoItem()	{ pHPTable=NULL; }
//	~ZHPInfoItem()	{ if(pHPTable) delete pHPTable; }
//	
//	int		nCount;
//	ZHPItem *pHPTable;
//};


//class ZHPInfoHistory : public list<ZHPInfoItem*> {
//};

#define CHARACTER_ICON_DELAY		2.f
#define CHARACTER_ICON_FADE_DELAY	.2f
#define CHARACTER_ICON_SIZE			32.f		// ������ ũ�� (640x480����)

class ZModule_HPAP;
class ZModule_QuestStatus;

/// ĳ���� Ŭ����
class ZCharacter : public ZCharacterObject
{
	MDeclareRTTI;
	//friend class ZCharacterManager;
private:
protected:

	// ����. �ѹ� �����ǰ� �Ҹ�ɶ� ���� �����
	ZModule_HPAP			*m_pModule_HPAP;
	ZModule_QuestStatus		*m_pModule_QuestStatus;
	ZModule_Resistance		*m_pModule_Resistance;
	ZModule_FireDamage		*m_pModule_FireDamage;
	ZModule_ColdDamage		*m_pModule_ColdDamage;
	ZModule_PoisonDamage	*m_pModule_PoisonDamage;
	ZModule_LightningDamage	*m_pModule_LightningDamage;
	

	ZCharacterProperty		m_Property;		///< HP ���� ĳ���� �Ӽ�
	ZCharacterStatus		m_Status;		///< �÷��̾� ���°�

	MTD_CharInfo			m_InitialInfo;	///< �ʱ�����

	char	m_szUserName[MATCHOBJECT_NAME_LENGTH];			///< �����̸�(��ڴ� '���')
	char	m_szUserAndClanName[MATCHOBJECT_NAME_LENGTH];	///< �����̸�(Ŭ���̸�)


	// ��ŷ
	union {
		struct {
			bool	m_bAdminHide:1;					///< admin hide �Ǿ��ִ���..
			bool	m_bDie:1;						///< �׾����� üũ
			bool	m_bStylishShoted:1;				///< ���������� ��� ��Ÿ�ϸ��� �ߴ��� üũ
			bool	m_bFallingToNarak:1;			///< �������� �������� �ִ��� ����
			bool	m_bStun:1;						///< stun ..�����ϼ����ԵȻ���.
			bool	m_bDamaged:1;					///< ������ ����
			
			bool	m_bPlayDone:1;				// �ִϸ��̼� �÷��̰� �� �Ǿ�����. ������������ �Ѿ�� ����
			bool	m_bPlayDone_upper:1;		// ��ü �ִϸ��̼� �÷��̰� �� �Ǿ�����. ������������ �Ѿ�� ����
			bool	m_bIsLowModel:1;
			bool	m_bTagger:1;					///< ����

		};
		DWORD dwFlagsProtected;
	}; // ��ŷ ��


	ZSTUNTYPE	m_nStunType;				///< �´� �ִϸ��̼� ����.. 2:������Ÿ��,4:lightning,5:����

	int			m_nKillsThisRound;
	float		m_fLastKillTime;
	ZDAMAGETYPE	m_LastDamageType;	
	MMatchWeaponType m_LastDamageWeapon;
	rvector		m_LastDamageDir;
	float		m_LastDamageDot;
	float		m_LastDamageDistance;

	MUID		m_LastThrower;
	float		m_tmLastThrowClear;

	int			m_nWhichFootSound;

	DWORD		m_dwInvincibleStartTime;
	DWORD		m_dwInvincibleDuration;

	virtual void UpdateSound();

	void InitMesh();
	void InitProperties();

	void CheckLostConn();
	virtual void OnLevelDown();
	virtual void OnLevelUp();
	virtual void OnDraw();
	virtual void	OnDie();

public:
	BasicInfoHistoryManager BasicInfoHistory;

	bool GetHistory(rvector *pos, rvector *direction, float fTime) override;
	void GetPositions(v3* Head, v3* Foot, double Time);

	float	m_fLastValidTime;

	union {
		struct {
			bool	m_bLand:1;
			bool	m_bWallJump:1;
			bool	m_bJumpUp:1;
			bool	m_bJumpDown:1;
			bool	m_bWallJump2:1;
			bool	m_bTumble:1;
			bool	m_bBlast:1;
			bool	m_bBlastFall:1;
			bool	m_bBlastDrop:1;
			bool	m_bBlastStand:1;
			bool	m_bBlastAirmove:1;
			bool	m_bSpMotion:1;
			bool	m_bCommander:1;
			bool	m_bCharging:1;
			bool	m_bCharged:1;
			bool	m_bLostConEffect:1;
			bool	m_bChatEffect:1;
			bool	m_bBackMoving:1;
		};
		u32 dwFlagsPublic;
	};


	float	m_fChargedFreeTime;
	int		m_nWallJumpDir;
	int		m_nBlastType;


	ZC_STATE_LOWER	m_SpMotion;

	int m_t_parts[6];
	int m_t_parts2[6];
	
	
	rvector		m_vProxyPosition, m_vProxyDirection;

	ZCharacter();
	virtual ~ZCharacter();

	virtual bool Create(const MTD_CharInfo& pCharInfo);
	virtual void Destroy();
	
	void InitMeshParts();
	
	void EmptyHistory();

	void Draw() {
		OnDraw();
	}

	rvector m_TargetDir;
	rvector m_DirectionLower,m_DirectionUpper;
	rvector m_RealPositionBefore;
	rvector m_AnimationPositionDiff;
	rvector m_Accel;


	ZC_STATE_UPPER	m_AniState_Upper;
	ZC_STATE_LOWER	m_AniState_Lower;
	ZANIMATIONINFO *m_pAnimationInfo_Upper,*m_pAnimationInfo_Lower;

	void AddIcon(int nIcon);

	int		m_nVMID;
	MMatchTeam		m_nTeamID;

	MCharacterMoveMode		m_nMoveMode;
	MCharacterMode			m_nMode;
	MCharacterState			m_nState;

	float	m_fAttack1Ratio;

	float	m_fLastReceivedTime;

	float	m_fTimeOffset;
	float	m_fAccumulatedTimeError;
	int		m_nTimeErrorCount;


	float	m_fGlobalHP;
	int		m_nReceiveHPCount;

	int		m_nLastShotItemID;
	float	m_fLastShotTime;

	void	SetInvincibleTime(int nDuration)
	{
		m_dwInvincibleStartTime = GetGlobalTimeMS();
		m_dwInvincibleDuration = nDuration;
	}

	bool	isInvincible();

	bool IsMan();

	virtual void  OnUpdate(float fDelta);
	virtual void  UpdateSpeed();
	virtual float GetMoveSpeedRatio();

	virtual void UpdateVelocity(float fDelta);
	virtual void UpdateHeight(float fDelta);
	virtual void UpdateMotion(float fDelta=0.f);
	virtual void UpdateAnimation();

	void UpdateLoadAnimation();

	void Stop();

	void CheckDrawWeaponTrack();
	void UpdateSpWeapon();

	void SetAnimation(const char *AnimationName,bool bEnableCancel,int tick);
	void SetAnimation(RAniMode mode, const char *AnimationName,bool bEnableCancel,int tick);

	void SetAnimationLower(ZC_STATE_LOWER nAni);
	void SetAnimationUpper(ZC_STATE_UPPER nAni);
	
	ZC_STATE_LOWER GetStateLower() { return m_AniState_Lower; }
	ZC_STATE_UPPER GetStateUpper() { return m_AniState_Upper; }

	bool IsUpperPlayDone()	{ return m_bPlayDone_upper; }

	bool IsMoveAnimation();

	bool IsTeam(ZCharacter* pChar);

	bool IsRunWall();
	bool IsMeleeWeapon();
	virtual bool IsCollideable();

	void SetTargetDir(rvector vDir); 

	virtual bool Pick(rvector& pos,rvector& dir, RPickInfo* pInfo = NULL);

	virtual void OnChangeWeapon(char* WeaponModelName);
	void OnChangeParts(RMeshPartsType type,int PartsID);
	void OnAttack(int type,rvector& pos);
	void OnShot();

	void ChangeWeapon(MMatchCharItemParts nParts);

	int GetLastShotItemID()	{ return m_nLastShotItemID; }
	float GetLastShotTime()						{ return m_fLastShotTime; }
	bool CheckValidShotTime(int nItemID, float fTime, ZItem* pItem);
	void UpdateValidShotTime(int nItemID, float fTime) 
	{ 
		m_nLastShotItemID = nItemID;
		m_fLastShotTime = fTime;
	}

	bool IsDie() { return m_bDie; }
	bool IsAlive() const { return !m_bDie; }
	void ForceDie() { SetHP(0); m_bDie = true; }

	void SetAccel(const rvector& accel) { m_Accel = accel; }
	virtual void SetDirection(const rvector& dir);

	int		m_nSelectSlot;
	ZSlot	m_Slot[ZC_SLOT_END];

	ZCharacterStatus* GetStatus()	{ return &m_Status; }

	ZCharacterProperty* GetProperty() { return &m_Property; }

	MMatchUserGradeID GetUserGrade()	{ return m_InitialInfo.nUGradeID; }
	unsigned int GetClanID()	{ return m_InitialInfo.nClanCLID; }

	void SetName(const char* szName) { strcpy_safe(m_Property.szName, szName); }

	const char *GetUserName()			{ return m_szUserName;	}
	const char *GetUserAndClanName()	{ return m_szUserAndClanName; }
	bool IsAdmin();
	bool IsAdminHide() const		{ return m_bAdminHide;	}
	void SetAdminHide(bool bHide) { m_bAdminHide = bHide; }

	int GetHP();
	int GetAP();
	void SetHP(int nHP);
	void SetAP(int nAP);

	int GetKils() { return GetStatus()->nKills; }

	bool CheckDrawGrenade();

	bool GetStylishShoted() { return m_bStylishShoted; }
	void UpdateStylishShoted();
	
	MUID GetLastAttacker() { return m_pModule_HPAP->GetLastAttacker(); }
	void SetLastAttacker(MUID uid) { m_pModule_HPAP->SetLastAttacker(uid); }
	ZDAMAGETYPE GetLastDamageType() { return m_LastDamageType; }
	void SetLastDamageType(ZDAMAGETYPE type) { m_LastDamageType = type; }

	bool DoingStylishMotion();
	
	bool IsObserverTarget();

	MMatchTeam GetTeamID() { return m_nTeamID; }
	void SetTeamID(MMatchTeam nTeamID) { m_nTeamID = nTeamID; }
	bool IsSameTeam(ZCharacter* pCharacter) 
	{ 
		if (pCharacter->GetTeamID() == -1) return false;
		if (pCharacter->GetTeamID() == GetTeamID()) return true; return false; 
	}
	bool IsTagger() { return m_bTagger; }
	void SetTagger(bool bTagger) { m_bTagger = bTagger; }

	void SetLastThrower(MUID uid, float fTime) { m_LastThrower = uid; m_tmLastThrowClear = fTime; }
	const MUID& GetLastThrower() { return m_LastThrower; }
	float GetLastThrowClearTime() { return m_tmLastThrowClear; }

	void Revival();
	void Die();
	void ActDead();
	virtual void InitHPAP();
	virtual void InitBullet();
	virtual void InitStatus();
	virtual void InitRound();


	void TestChangePartsAll();
	void TestToggleCharacter();

	virtual void OutputDebugString_CharacterState();

	void ToggleClothSimulation();
	void ChangeLowPolyModel();
	bool IsFallingToNarak() { return m_bFallingToNarak; }

	MMatchItemDesc* GetSelectItemDesc() {
		if(GetItems())
			if(GetItems()->GetSelectedWeapon())
				return GetItems()->GetSelectedWeapon()->GetDesc();
		return NULL;
	}

	void LevelUp();
	void LevelDown();

	void Save(ReplayPlayerInfo& Info);
	void Load(const ReplayPlayerInfo& Info);

	RMesh *GetWeaponMesh(MMatchCharItemParts parts);

	virtual float ColTest(const rvector& pos, const rvector& vec, float radius, rplane* out=0) override;
	virtual bool IsAttackable() override;

	virtual bool IsGuard() const override;
	virtual bool IsGuardCustom() const override {
		return IsGuard();
	}
	virtual void OnMeleeGuardSuccess() override;

	void AddMassiveEffect(const rvector &pos, const rvector &dir);


	virtual void OnDamagedAnimation(ZObject *pAttacker, int type) override;

	// ZObject�� �°� ���� �����̳� �̺�Ʈ�� ���� �͵�.
	virtual ZOBJECTHITTEST HitTest(const rvector& origin, const rvector& to, float fTime, rvector *pOutPos = NULL) override;

	virtual void OnKnockback(const rvector& dir, float fForce) override;
	virtual void OnDamaged(ZObject* pAttacker, rvector srcPos, ZDAMAGETYPE damageType, MMatchWeaponType weaponType,
		float fDamage, float fPiercingRatio=1.f, int nMeleeType=-1) override;
	virtual void OnScream() override;
};

void ZChangeCharParts(RVisualMesh* pVMesh, MMatchSex nSex, int nHair, int nFace, unsigned long int* pItemID);
void ZChangeCharWeaponMesh(RVisualMesh* pVMesh, unsigned long int nWeaponID);
bool CheckTeenVersionMesh(RMesh** ppMesh);

enum CHARACTER_LIGHT_TYPE
{
	GUN,
	SHOTGUN,
	CANNON,
	NUM_LIGHT_TYPE,
};

struct sCharacterLight
{
	int			iType;
	float		fLife;
	rvector		vLightColor;
	float		fRange;
};