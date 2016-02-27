#ifndef _ZREPLAY_H
#define _ZREPLAY_H

struct REPLAY_STAGE_SETTING_NODE_OLD 
{
	MUID				uidStage;
	char				szMapName[32];	// ���̸�
	char				nMapIndex;					// ���ε���
	MMATCH_GAMETYPE		nGameType;					// ����Ÿ��
	int					nRoundMax;					// ����
	int					nLimitTime;					// ���ѽð�(1 - 1��)
	int					nLimitLevel;				// ���ѷ���
	int					nMaxPlayers;				// �ִ��ο�
	bool				bTeamKillEnabled;			// ��ų����
	bool				bTeamWinThePoint;			// ������ ����
	bool				bForcedEntryEnabled;		// ������ ���� ����
};

struct REPLAY_STAGE_SETTING_NODE
{
	MUID				uidStage;
	char				szStageName[64];
	char				szMapName[MAPNAME_LENGTH];
	char				nMapIndex;
	MMATCH_GAMETYPE		nGameType;
	int					nRoundMax;
	int					nLimitTime;
	int					nLimitLevel;
	int					nMaxPlayers;
	bool				bTeamKillEnabled;
	bool				bTeamWinThePoint;
	bool				bForcedEntryEnabled;
	bool				bAutoTeamBalancing;
};

struct REPLAY_STAGE_SETTING_NODE_FG
{
	MUID				uidStage;
	char				szMapName[32];
	char				nMapIndex;
	MMATCH_GAMETYPE		nGameType;
	int					nRoundMax;
	int					nLimitTime;
	int					nLimitLevel;
	int					nMaxPlayers;
	bool				bTeamKillEnabled;
	bool				bTeamWinThePoint;
	bool				bForcedEntryEnabled;
	char				szStageName[64];
};

#pragma pack(push)
#pragma pack(1)

struct MTD_CharInfo_FG_V7_0
{
	char				szName[32];
	char				szClanName[16];
	DWORD		nClanGrade;
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
	DWORD	nUGradeID;

	// ClanCLID
	unsigned int		nClanCLID;

	// ������ �����ʸ�Ʈ ���
	int					nDTLastWeekGrade;

	char unk[204];
};

struct MTD_CharInfo_FG_V7_1
{
	char				szName[32];
	char				szClanName[16];
	DWORD		nClanGrade;
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

	DWORD	nUGradeID;

	unsigned int		nClanCLID;

	int					nDTLastWeekGrade;

	__int64				uidEquipedItem[22];
	unsigned long int	nEquipedItemCount[22];
	unsigned long int	nEquipedItemRarity[22];
	unsigned long int	nEquipedItemLevel[22];
};

struct MTD_CharInfo_FG_V9
{
	char				szName[32];
	char				szClanName[16];
	DWORD		nClanGrade;
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
	DWORD	nUGradeID;

	// ClanCLID
	unsigned int		nClanCLID;

	// ������ �����ʸ�Ʈ ���
	int					nDTLastWeekGrade;

	DWORD unk[6];

	// ������ ���� �߰�
	__int64				uidEquipedItem[22];
	unsigned long int	nEquipedItemCount[22];
	unsigned long int	nEquipedItemRarity[22];
	unsigned long int	nEquipedItemLevel[22];

	char unk2[24];
};

#pragma pack(pop)

extern bool g_bTestFromReplay;

bool CreateReplayGame(char *filename);


// ���� ���÷��� ����
#define GUNZ_REC_FILE_ID		0x95b1308a

// version 4 : duel ����� ���� ���� ������ �߰��Ǿ����ϴ�.
#define GUNZ_REC_FILE_VERSION	4
#define GUNZ_REC_FILE_EXT		"gzr"

class ZReplay
{
private:
public:
	ZReplay() {}
	~ZReplay() {}

};

enum SERVER
{
	SERVER_NONE,
	SERVER_OFFICIAL, // igunz, ijji gunz, aeria gunz
	SERVER_REFINED_GUNZ,
	SERVER_FREESTYLE_GUNZ,
};

struct ReplayVersion
{
	SERVER Server;
	int nVersion;
	int nSubVersion;
};

class ZGame;

class ZReplayLoader
{
private:
	ZFile *pFile;
	ReplayVersion Version;
	REPLAY_STAGE_SETTING_NODE m_StageSetting;
	float m_fGameTime;
	BYTE *FileBuffer;

	bool LoadHeader();
	bool LoadStageSetting();
	bool LoadStageSettingEtc();
	bool LoadCharInfo();
	bool LoadCommandStream();

	void ConvertStageSettingNode(REPLAY_STAGE_SETTING_NODE* pSource, MSTAGE_SETTING_NODE* pTarget);
	void ChangeGameState();

	bool CreateCommandFromStream(char* pStream, MCommand **pRetCommand);
	MCommand* CreateCommandFromStreamVersion2(char* pStream);
	bool ParseVersion2Command(char* pStream, MCommand* pCmd);
	MCommandParameter* MakeVersion2CommandParameter(MCommandParameterType nType, char* pStream, unsigned short int* pnDataCount);
public:
	ZReplayLoader();
	~ZReplayLoader();
	bool Load(const char* filename);	
	float GetGameTime() const { return m_fGameTime; }
};






#endif