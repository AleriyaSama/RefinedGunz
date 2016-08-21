#pragma once

#include "ZPrerequisites.h"
#include "MUID.h"
#include "RTypes.h"
#include "MRTTI.h"
#include "ZModule.h"
#include "ZModule_Movable.h"
#include "ZCharacterItem.h"
#include "stuff.h"
#include "HitRegistration.h"

#include <list>
#include <string>

_USING_NAMESPACE_REALSPACE2

enum ZC_ENCHANT {
	ZC_ENCHANT_NONE = 0,
	ZC_ENCHANT_FIRE,
	ZC_ENCHANT_COLD,
	ZC_ENCHANT_LIGHTNING,
	ZC_ENCHANT_POISON,

	ZC_ENCHANT_END
};

/// ������Ʈ �浹�� �ʿ��� ��
struct ZObjectCollision
{
	bool	bCollideable;			///< �浹����
	float	fRadius;				///< ������
	float	fHeight;				///< ����
};

/// ���ӻ��� ��� ������Ʈ �θ� Ŭ����
class ZObject : public ZModuleContainer
{
	MDeclareRTTI;

private:
	bool					m_bVisible;			///< ȭ�鿡 �׸��� ����
	float					m_fSpawnTime;		///< �¾ �ð�
	float					m_fDeadTime;		///< �����ð�
protected:
	MUID					m_UID;				///< �������� �ο��� ����ũ ID(�߿�)
	bool					m_bIsNPC;			///< NPC���� ����
	bool					m_bInitialized;		///< �ʱ�ȭ�Ǿ����� ����
	ZObjectCollision		m_Collision;
	virtual void OnDraw();
	virtual void OnUpdate(float fDelta);
	virtual void OnDie() {}
public:
	bool					m_bRendered;		///< ȭ�鿡 �׷������� ����

	RVisualMesh*			m_pVMesh;
	rvector					m_Position;
	rvector					m_Direction;

	ZModule_Movable			*m_pModule_Movable;	// �ӵ��� �������� �����ϴ� ���

	ZCharacterItem			m_Items;			///< ����ϰ� �ִ� ������

public:
	ZObject();
	virtual ~ZObject();

	auto& GetPosition() const { return m_Position; }
	void SetPosition(const rvector& pos) { m_Position = pos; }
	void Draw();
	void Update(float fDelta);
	virtual bool Pick(int x,int y,RPickInfo* pInfo);
	virtual bool Pick(int x, int y, rvector* v, float* f);
	virtual bool Pick(const rvector& pos, const rvector& dir, RPickInfo* pInfo = nullptr);
	virtual bool GetHistory(rvector* pos, rvector* direction, float fTime, rvector* cameradir = nullptr);

	void SetVisualMesh(RVisualMesh* pVMesh)			{ m_pVMesh = pVMesh; }
	auto* GetVisualMesh() const						{ return m_pVMesh; }
	auto* GetVisualMesh()							{ return m_pVMesh; }
	bool IsVisible() const							{ return m_bVisible; }
	void SetVisible(bool bVisible)					{ m_bVisible = bVisible; }
	bool GetInitialized() const						{ return m_bInitialized; }
	auto& GetUID() const							{ return m_UID; }
	void SetUID(MUID& uid)							{ m_UID = uid; }
	void SetSpawnTime(float fTime);
	float GetSpawnTime() const						{ return m_fSpawnTime; }
	void SetDeadTime(float fTime);
	float GetDeadTime() const						{ return m_fDeadTime; }
	bool IsNPC() const								{ return m_bIsNPC; }
	auto& GetDirection() const						{ return m_Direction; }

	auto& GetVelocity() const					{ return m_pModule_Movable->GetVelocity(); }
	void SetVelocity(const rvector& vel)		{ m_pModule_Movable->SetVelocity(vel); }
	void SetVelocity(float x, float y, float z) { SetVelocity(rvector(x,y,z)); }
	void AddVelocity(const rvector& add)		{ SetVelocity(GetVelocity() + add); }

	float GetDistToFloor() const			{ return m_pModule_Movable->GetDistToFloor(); }
	float GetCollRadius() const				{ return m_Collision.fRadius; }
	float GetCollHeight() const				{ return m_Collision.fHeight; }
	rvector GetCenterPos() const			{ return m_Position + rvector(0.0f, 0.0f, m_Collision.fHeight*0.5f); }

	auto* GetItems() { return &m_Items; }
	auto* GetItems() const { return &m_Items; }

	virtual bool IsCollideable() { return m_Collision.bCollideable; }		
	virtual float ColTest(const rvector& pos, const rvector& vec, float radius, rplane* out=0) { return 1.0f; }
	virtual bool ColTest(const rvector& p1, const rvector& p2, float radius, float fTime);
	virtual bool IsAttackable()	 { return true; }
	virtual bool IsDie() { return false; }
	virtual void SetDirection(const rvector& dir);
	virtual bool IsGuard()	const { return false; }
	virtual bool IsGuardCustom() const {
		return false;
	}
	virtual MMatchTeam GetTeamID() { return MMT_ALL; }
	
	virtual ZOBJECTHITTEST HitTest(const rvector& origin, const rvector& to, float fTime, rvector *pOutPos = NULL) = 0;

	virtual void OnBlast(rvector &dir)	{ }	
	virtual void OnBlastDagger(rvector &dir,rvector& pos) { }

	virtual void OnGuardSuccess() { }
	virtual void OnMeleeGuardSuccess() { }
	
	virtual void OnKnockback(const rvector& dir, float fForce) { }

	void Tremble(float fValue, DWORD nMaxTime, DWORD nReturnMaxTime);

	virtual void OnDamaged(ZObject* pAttacker, rvector srcPos, ZDAMAGETYPE damageType, MMatchWeaponType weaponType,
		float fDamage, float fPiercingRatio=1.f, int nMeleeType=-1);
	virtual void OnDamagedSkill(ZObject* pAttacker, rvector srcPos, ZDAMAGETYPE damageType, MMatchWeaponType weaponType,
		float fDamage, float fPiercingRatio=1.f, int nMeleeType=-1);
	virtual void OnDamagedAnimation(ZObject *pAttacker,int type) { }
	virtual void OnScream() { }
	virtual void OnHealing(ZObject* pOwner,int nHP,int nAP);

	void OnSimpleDamaged(ZObject* pAttacker, float fDamage, float fPiercingRatio);

	virtual void OnStun(float fTime) {}

public:
	bool IsRendered() const { return m_bRendered; }

protected:
	bool Move(const rvector &diff) { return m_pModule_Movable->Move(diff); }
};

bool IsPlayerObject(ZObject* pObject);