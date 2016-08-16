#ifndef _MMATCHCLAN_H
#define _MMATCHCLAN_H


#include "MMatchGlobal.h"
#include "MUID.h"
#include "MSmartRefresh.h"
#include <string>
#include <list>
using namespace std;

// Ŭ������� nSrcGrade�� nDstGrade���� ���ų� �� ������ �Ǻ��Ѵ�.
inline bool IsUpperClanGrade(MMatchClanGrade nSrcGrade, MMatchClanGrade nDstGrade)
{
	if ((nSrcGrade != MCG_NONE) && ((int)nSrcGrade <= (int)nDstGrade)) return true;
	return false;
}

///////////////////////////////////
class MMatchObject;

/// Ŭ��
class MMatchClan
{
private:
	int				m_nCLID;							///< Ŭ�� ������ ID
	char			m_szClanName[CLAN_NAME_LENGTH];		///< �̸�
	unsigned long	m_nDBRefreshLifeTime;

	struct ClanInfoEx
	{
		int	nLevel;							///< ����
		int	nTotalPoint;					///< ��Ż����Ʈ
		int	nPoint;							///< ����Ʈ
		int	nWins;							///< ���� - �¼�
		int	nLosses;						///< ���� - �м�
		int nRanking;						///< ��ŷ
		int	nTotalMemberCount;				///< ���ο�
		char szMaster[MATCHOBJECT_NAME_LENGTH];	
		char szEmblemUrl[256];					///< Ŭ����ũ URL
		int nEmblemChecksum;					///< Ŭ����ũ üũ��
	};

	ClanInfoEx		m_ClanInfoEx;
	MMatchObjectMap	m_Members;							///< �÷��̾��
	MSmartRefresh	m_SmartRefresh;						///< �÷��̾� ĳ��

	int				m_nSeriesOfVictories;				///< Ŭ���� ���¼�
	list<int>		m_MatchedClanList;					///< �����ߴ� Ŭ��

	unsigned long	m_nEmptyPeriod;

	void	Clear();
	void InitClanInfoEx(const int nLevel, const int nTotalPoint, const int nPoint, const int nRanking,
		                const int nWins, const int nLosses, const int nTotalMemberCount, const char* szMaster,
						const char* szEmblemUrl, int nEmblemChecksum);
public:
	MMatchClan();
	virtual ~MMatchClan();

	// MMatchClanMap���� ����ϴ� �Լ�
	void Create(int nCLID, const char* szClanName);
	void AddObject(const MUID& uid, MMatchObject* pObj);
	void RemoveObject(const MUID& uid);

	
	void Tick(u64 nClock);
	void SyncPlayerList(MMatchObject* pObj, int nCategory);
	void InitClanInfoFromDB();			// db���� Ŭ�������� �ʱ�ȭ�Ѵ�.
	bool CheckLifePeriod();

	// get ������
	int			GetCLID()						{ return m_nCLID; }
	const char* GetName()						{ return m_szClanName; }
//	int			GetLevel()						{ return m_nLevel; }
	int			GetMemberCount()				{ return (int)m_Members.size(); }
	ClanInfoEx*	GetClanInfoEx()					{ return &m_ClanInfoEx; }
	bool		IsInitedClanInfoEx()			{ return (m_ClanInfoEx.nLevel != 0); }
	int			GetSeriesOfVictories()			{ return m_nSeriesOfVictories; }
	const char*	GetEmblemURL()					{ return m_ClanInfoEx.szEmblemUrl; }
	int			GetEmblemChecksum()				{ return m_ClanInfoEx.nEmblemChecksum; }
	

	// Inc
	void IncWins(int nAddedWins) { 
		m_ClanInfoEx.nWins += nAddedWins; m_nSeriesOfVictories++; 
	}
	void IncLosses(int nAddedLosses) { 
		m_ClanInfoEx.nLosses += nAddedLosses; m_nSeriesOfVictories=0; 
	}
	void IncPoint(int nAddedPoint)				{ m_ClanInfoEx.nPoint += nAddedPoint; 
													if (nAddedPoint > 0) m_ClanInfoEx.nTotalPoint += nAddedPoint; 
													if (m_ClanInfoEx.nPoint < 0) m_ClanInfoEx.nPoint =0;
												}
	void InsertMatchedClanID(int nCLID);	///< �����ߴ� Ŭ��

	auto GetMemberBegin()	{ return m_Members.begin(); }
	auto GetMemberEnd()		{ return m_Members.end(); }
};

///////////////////////////////////

class MMatchClanMap : public std::map<int, MMatchClan*>
{
private:
	u64	m_nLastTick;
	std::map<std::string, MMatchClan*>	m_ClanNameMap;
	void CreateClan(int nCLID, const char* szClanName);
	void DestroyClan(int nCLID, MMatchClanMap::iterator* pNextItor);
	bool CheckTick(u64 nClock);
public:
	MMatchClanMap();
	virtual ~MMatchClanMap();
	void Destroy(); 
	void Tick(u64 nClock);

	void AddObject(const MUID& uid, MMatchObject* pObj);
	void RemoveObject(const MUID& uid, MMatchObject* pObj);
	MMatchClan* GetClan(const int nCLID);
	MMatchClan* GetClan(const char* szClanName);
};


#endif