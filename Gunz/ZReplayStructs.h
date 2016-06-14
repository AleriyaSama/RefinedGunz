#pragma once

#include "ZCharacterStructs.h"

#pragma pack(push)
#pragma pack(1)

struct REPLAY_STAGE_SETTING_NODE
{
	MUID				uidStage;
	char				szStageName[64];
	char				szMapName[MAPNAME_LENGTH];
	u32					nMapIndex;
	MMATCH_GAMETYPE		nGameType;
	i32					nRoundMax;
	i32					nLimitTime;
	i32					nLimitLevel;
	i32					nMaxPlayers;
	bool				bTeamKillEnabled;
	bool				bTeamWinThePoint;
	bool				bForcedEntryEnabled;
	bool				bAutoTeamBalancing;
};

struct REPLAY_STAGE_SETTING_NODE_OLD
{
	MUID				uidStage;
	char				szMapName[32];	// ���̸�
	u32					nMapIndex;					// ���ε���
	MMATCH_GAMETYPE		nGameType;					// ����Ÿ��
	int					nRoundMax;					// ����
	int					nLimitTime;					// ���ѽð�(1 - 1��)
	int					nLimitLevel;				// ���ѷ���
	int					nMaxPlayers;				// �ִ��ο�
	bool				bTeamKillEnabled;			// ��ų����
	bool				bTeamWinThePoint;			// ������ ����
	bool				bForcedEntryEnabled;		// ������ ���� ����
};
struct REPLAY_STAGE_SETTING_NODE_V11
{
	MUID				uidStage;
	char				szMapName[32];
	char				unk[32];
	u32					nMapIndex;
	MMATCH_GAMETYPE		nGameType;
	int					nRoundMax;
	int					nLimitTime;
	int					nLimitLevel;
	int					nMaxPlayers;
	bool				bTeamKillEnabled;
	bool				bTeamWinThePoint;
	bool				bForcedEntryEnabled;
	char unk2;
};

struct REPLAY_STAGE_SETTING_NODE_FG
{
	MUID				uidStage;
	char				szMapName[32];
	u32					nMapIndex;
	MMATCH_GAMETYPE		nGameType;
	int					nRoundMax;
	int					nLimitTime;
	int					nLimitLevel;
	int					nMaxPlayers;
	bool				bTeamKillEnabled;
	bool				bTeamWinThePoint;
	bool				bForcedEntryEnabled;
	char				szStageName[64];
	char unk;
};

struct REPLAY_STAGE_SETTING_NODE_DG
{
	MUID				uidStage;
	char				szMapName[32];	// ���̸�
	u32					nMapIndex;					// ���ε���
	MMATCH_GAMETYPE		nGameType;					// ����Ÿ��
	int					nRoundMax;					// ����
	int					nLimitTime;					// ���ѽð�(1 - 1��)
	int					nLimitLevel;				// ���ѷ���
	int					nMaxPlayers;				// �ִ��ο�
	bool				bTeamKillEnabled;			// ��ų����
	bool				bTeamWinThePoint;			// ������ ����
	bool				bForcedEntryEnabled;		// ������ ���� ����
	char unk[5];
};

struct MTD_CharInfo_V5
{
	// ĳ���� ����
	char				szName[32];
	char				szClanName[16];
	MMatchClanGrade		nClanGrade;
	unsigned short		nClanContPoint;
	char				nCharNum;
	unsigned short		nLevel;
	char				nSex;
	char				nHair;
	char				nFace;
	unsigned long int	nXP;
	int					nBP;
	float				fBonusRate;
	unsigned short		nPrize;
	unsigned short		nHP;
	unsigned short		nAP;
	unsigned short		nMaxWeight;
	unsigned short		nSafeFalls;
	unsigned short		nFR;
	unsigned short		nCR;
	unsigned short		nER;
	unsigned short		nWR;

	// ������ ����
	unsigned long int	nEquipedItemDesc[12];

	// account �� ����
	MMatchUserGradeID	nUGradeID;

	// ClanCLID
	unsigned int		nClanCLID;
};

struct MTD_CharInfo_V6
{
	char				szName[32];
	char				szClanName[16];
	MMatchClanGrade		nClanGrade;
	unsigned short		nClanContPoint;
	char				nCharNum;
	unsigned short		nLevel;
	char				nSex;
	char				nHair;
	char				nFace;
	unsigned long int	nXP;
	int					nBP;
	float				fBonusRate;
	unsigned short		nPrize;
	unsigned short		nHP;
	unsigned short		nAP;
	unsigned short		nMaxWeight;
	unsigned short		nSafeFalls;
	unsigned short		nFR;
	unsigned short		nCR;
	unsigned short		nER;
	unsigned short		nWR;

	// ������ ����
	unsigned long int	nEquipedItemDesc[17];

	// account �� ����
	MMatchUserGradeID	nUGradeID;

	// ClanCLID
	unsigned int		nClanCLID;

	// ������ �����ʸ�Ʈ ���
	int					nDTLastWeekGrade;

	MUID				uidEquipedItem[17];
	unsigned long int	nEquipedItemCount[17];
};

struct MTD_CharInfo_V11
{
	char				szName[32];
	char				szClanName[16];
	MMatchClanGrade		nClanGrade;
	unsigned short		nClanContPoint;
	char				nCharNum;
	unsigned short		nLevel;
	char				nSex;
	char				nHair;
	char				nFace;
	unsigned long int	nXP;
	int					nBP;
	float				fBonusRate;
	unsigned short		nPrize;
	unsigned short		nHP;
	unsigned short		nAP;
	unsigned short		nMaxWeight;
	unsigned short		nSafeFalls;
	unsigned short		nFR;
	unsigned short		nCR;
	unsigned short		nER;
	unsigned short		nWR;

	// ������ ����
	unsigned long int	nEquipedItemDesc[17];

	// account �� ����
	MMatchUserGradeID	nUGradeID;

	// ClanCLID
	unsigned int		nClanCLID;

	// ������ �����ʸ�Ʈ ���
	int					nDTLastWeekGrade;

	MUID				uidEquipedItem[17];
	unsigned long int	nEquipedItemCount[17];

	char unk[8];
};

typedef MTD_CharInfo_V6 MTD_CharInfo_FG_V7_0;

struct MTD_CharInfo_FG_V7_1
{
	char				szName[32];
	char				szClanName[16];
	MMatchClanGrade		nClanGrade;
	unsigned short		nClanContPoint;
	char				nCharNum;
	unsigned short		nLevel;
	char				nSex;
	char				nHair;
	char				nFace;
	unsigned long int	nXP;
	int					nBP;
	float				fBonusRate;
	unsigned short		nPrize;
	unsigned short		nHP;
	unsigned short		nAP;
	unsigned short		nMaxWeight;
	unsigned short		nSafeFalls;
	unsigned short		nFR;
	unsigned short		nCR;
	unsigned short		nER;
	unsigned short		nWR;

	unsigned long int	nEquipedItemDesc[22];

	MMatchUserGradeID	nUGradeID;

	unsigned int		nClanCLID;

	int					nDTLastWeekGrade;

	int64_t				uidEquipedItem[22];
	unsigned long int	nEquipedItemCount[22];
	unsigned long int	nEquipedItemRarity[22];
	unsigned long int	nEquipedItemLevel[22];
};

struct MTD_CharInfo_FG_V8
{
	char				szName[32];
	char				szClanName[16];
	MMatchClanGrade		nClanGrade;
	unsigned short		nClanContPoint;
	char				nCharNum;
	unsigned short		nLevel;
	char				nSex;
	char				nHair;
	char				nFace;
	unsigned long int	nXP;
	int					nBP;
	float				fBonusRate;
	unsigned short		nPrize;
	unsigned short		nHP;
	unsigned short		nAP;
	unsigned short		nMaxWeight;
	unsigned short		nSafeFalls;
	unsigned short		nFR;
	unsigned short		nCR;
	unsigned short		nER;
	unsigned short		nWR;

	// ������ ����
	unsigned long int	nEquipedItemDesc[22];

	// account �� ����
	MMatchUserGradeID	nUGradeID;

	// ClanCLID
	unsigned int		nClanCLID;

	// ������ �����ʸ�Ʈ ���
	int					nDTLastWeekGrade;

	uint32_t unk[6];

	// ������ ���� �߰�
	int64_t				uidEquipedItem[22];
	unsigned long int	nEquipedItemCount[22];
	unsigned long int	nEquipedItemRarity[22];
	unsigned long int	nEquipedItemLevel[22];
};

struct MTD_CharInfo_FG_V9
{
	char				szName[32];
	char				szClanName[16];
	MMatchClanGrade		nClanGrade;
	unsigned short		nClanContPoint;
	char				nCharNum;
	unsigned short		nLevel;
	char				nSex;
	char				nHair;
	char				nFace;
	unsigned long int	nXP;
	int					nBP;
	float				fBonusRate;
	unsigned short		nPrize;
	unsigned short		nHP;
	unsigned short		nAP;
	unsigned short		nMaxWeight;
	unsigned short		nSafeFalls;
	unsigned short		nFR;
	unsigned short		nCR;
	unsigned short		nER;
	unsigned short		nWR;

	// ������ ����
	unsigned long int	nEquipedItemDesc[22];

	// account �� ����
	MMatchUserGradeID	nUGradeID;

	// ClanCLID
	unsigned int		nClanCLID;

	// ������ �����ʸ�Ʈ ���
	int					nDTLastWeekGrade;

	uint32_t unk[6];

	// ������ ���� �߰�
	int64_t				uidEquipedItem[22];
	unsigned long int	nEquipedItemCount[22];
	unsigned long int	nEquipedItemRarity[22];
	unsigned long int	nEquipedItemLevel[22];

	char unk2[24];
};

struct BulletInfo
{
	int Clip;
	int Magazine;
};

template<size_t NumItems>
struct ZCharacterReplayStateImpl
{
	MUID UID;
	ZCharacterProperty Property;
	float HP;
	float AP;
	ZCharacterStatus Status;

	BulletInfo BulletInfos[NumItems];

	D3DXVECTOR3 Position;
	D3DXVECTOR3 Direction;

	MMatchTeam Team;

	bool Dead;

	bool HidingAdmin;
};

using ZCharacterReplayState = ZCharacterReplayStateImpl<MMCIP_END>;
using ZCharacterReplayState_FG_V7_0 = ZCharacterReplayStateImpl<17>;
using ZCharacterReplayState_FG_V7_1 = ZCharacterReplayStateImpl<22>;
using ZCharacterReplayState_FG_V8 = ZCharacterReplayStateImpl<23>;
using ZCharacterReplayState_FG_V9 = ZCharacterReplayStateImpl<24>;
using ZCharacterReplayState_Official_V6 = ZCharacterReplayStateImpl<17>;
using ZCharacterReplayState_Official_V11 = ZCharacterReplayStateImpl<34>;

template <typename CharInfo, typename ReplayState>
struct ReplayPlayerInfoImpl
{
	bool IsHero;
	CharInfo Info;
	ReplayState State;
};

struct MTD_CharInfo_DG
{
	char				szName[32];
	char				szClanName[16];
	MMatchClanGrade		nClanGrade;
	unsigned short		nClanContPoint;
	char				nCharNum;
	unsigned short		nLevel;
	char				nSex;
	char				nHair;
	char				nFace;
	unsigned long int	nXP;
	int					nBP;
	float				fBonusRate;
	unsigned short		nPrize;
	unsigned short		nHP;
	unsigned short		nAP;
	unsigned short		nMaxWeight;
	unsigned short		nSafeFalls;
	unsigned short		nFR;
	unsigned short		nCR;
	unsigned short		nER;
	unsigned short		nWR;

	// ������ ����
	unsigned long int	nEquipedItemDesc[17];

	// account �� ����
	MMatchUserGradeID	nUGradeID;

	// ClanCLID
	unsigned int		nClanCLID;

	// ������ �����ʸ�Ʈ ���
	int					nDTLastWeekGrade;

	MUID				uidEquipedItem[17];
	unsigned long int	nEquipedItemCount[17];

	char unk[6];
};

struct ZCharacterReplayState_DG
{
	MUID UID;
	ZCharacterProperty Property;
	float HP;
	float AP;
	ZCharacterStatus Status;

	BulletInfo BulletInfos[17];

	char unk[8];

	D3DXVECTOR3 Position;
	D3DXVECTOR3 Direction;

	MMatchTeam Team;

	bool Dead;

	bool HidingAdmin;
};

struct ReplayPlayerInfo_DG
{
	bool IsHero;
	char unk[32];
	MTD_CharInfo_DG Info;
	ZCharacterReplayState_DG State;
};

using ReplayPlayerInfo = ReplayPlayerInfoImpl<MTD_CharInfo, ZCharacterReplayState>;

using ReplayPlayerInfo_FG_V7_0 = ReplayPlayerInfoImpl<MTD_CharInfo_FG_V7_0, ZCharacterReplayState_FG_V7_0>;
using ReplayPlayerInfo_FG_V7_1 = ReplayPlayerInfoImpl<MTD_CharInfo_FG_V7_1, ZCharacterReplayState_FG_V7_1>;
using ReplayPlayerInfo_FG_V8 = ReplayPlayerInfoImpl<MTD_CharInfo_FG_V8, ZCharacterReplayState_FG_V8>;
using ReplayPlayerInfo_FG_V9 = ReplayPlayerInfoImpl<MTD_CharInfo_FG_V9, ZCharacterReplayState_FG_V9>;
using ReplayPlayerInfo_Official_V6 = ReplayPlayerInfoImpl<MTD_CharInfo_V6, ZCharacterReplayState_Official_V6>;
using ReplayPlayerInfo_Official_V11 = ReplayPlayerInfoImpl<MTD_CharInfo_V11, ZCharacterReplayState_Official_V11>;

#pragma pack(pop)