#pragma once
#ifndef _MMATCHGLOBAL_H
#define _MMATCHGLOBAL_H

#include "MBaseLocale.h"

#define MATCHOBJECT_NAME_LENGTH		32		// ĳ���� �̸� ����
#define MAX_CHAR_COUNT				4		// ���� �� �ִ� ĳ���� ��


#define CYCLE_STAGE_UPDATECHECKSUM	500		// �渮��Ʈ ���� ������� �����ִ� ������ - 0.5��

// ���� Rule ����
#define NUM_APPLYED_TEAMBONUS_TEAM_PLAYERS		3		// �������� ���ο��� 3�� �̻��϶��� ����ġ ���ʽ��� �����Ѵ�
#define RESPAWN_DELAYTIME_AFTER_DYING			7000	///< �װ��� �������Ǵ� �����̽ð�

#define MAX_XP_BONUS_RATIO						2.0f	///< ����ġ ���ʽ��� �ִ� 2���̴�.
#define MAX_BP_BONUS_RATIO						2.0f	///< �ٿ�Ƽ ���ʽ��� �ִ� 2���̴�.

// �������� ����
#define STAGENAME_LENGTH			64			// ���̸� ����
#define STAGEPASSWD_LENGTH			8			// �н����� �ִ����
#define STAGE_QUEST_MAX_PLAYER		4			// ����Ʈ ���Ӹ���� �ִ��ο�


#define TRANS_STAGELIST_NODE_COUNT				8	// �ѹ��� Ŭ���̾�Ʈ���� �����ִ� ����������� ����
#define TRANS_STANDBY_CLANLIST_NODE_COUNT		4	// Ŭ�������� �ѹ��� Ŭ���̾�Ʈ���� �����ִ� ����� Ŭ�� ����


#define MAX_REPLIER	16			// proposal �亯�ڴ� �ִ� 16��

//
// Clan
//
#define CLAN_SPONSORS_COUNT			4		// Ŭ�������� �ʿ��� �߱��� ��
#define CLAN_CREATING_NEED_BOUNTY		1000	// Ŭ�������� �ʿ��� �ٿ�Ƽ
#define CLAN_CREATING_NEED_LEVEL		10		// Ŭ�������� �ʿ��� ����


#define CLAN_NAME_LENGTH			16		// Ŭ�� �̸� �ִ� ���� - �̰� ����Ǹ� �������� ������ ����Ǿ�� ��
#define MIN_CLANNAME	4				// �ּ� 4���̻� 12�����ϸ� Ŭ�� �̸��� ���� �� �ִ�.
#define MAX_CLANNAME	12

enum MMatchClanGrade : i32
{
	MCG_NONE = 0,
	MCG_MASTER = 1,
	MCG_ADMIN = 2,

	MCG_MEMBER = 9,
	MCG_END
};

//
// Character
//
#define MIN_CHARNAME	4				// �ּ� 4���̻� 12�� ���ϸ� ĳ���� �̸��� ���� �� �ִ�.
#define MAX_CHARNAME	16

#define MAX_CHAR_LEVEL	99

#define MATCH_SIMPLE_DESC_LENGTH	64

enum MMatchUserGradeID : i32
{
	MMUG_FREE = 0,
	MMUG_REGULAR = 1,
	MMUG_STAR = 2,

	MMUG_CRIMINAL = 100,
	MMUG_WARNING_1 = 101,
	MMUG_WARNING_2 = 102,
	MMUG_WARNING_3 = 103,
	MMUG_CHAT_LIMITED = 104,
	MMUG_PENALTY = 105,

	MMUG_EVENTMASTER = 252,
	MMUG_BLOCKED = 253,
	MMUG_DEVELOPER = 254,
	MMUG_ADMIN = 255
};

enum MMatchPlace
{
	MMP_OUTSIDE = 0,
	MMP_LOBBY = 1,
	MMP_STAGE = 2,
	MMP_BATTLE = 3,
	MMP_END
};

enum MMatchObjectStageState
{
	MOSS_NONREADY = 0,
	MOSS_READY = 1,
	MOSS_SHOP = 2,
	MOSS_EQUIPMENT = 3,
	MOSS_END
};

//
// Clan war
//
#define ACTIONLEAGUE_TEAM_MEMBER_COUNT		4		// �׼Ǹ��״� 4���� ��� �Բ� �����ؾߵȴ�.
#define MAX_LADDER_TEAM_MEMBER				4		// �������� 1~4����� ���� �� �ִ�.
#define MAX_CLANBATTLE_TEAM_MEMBER			8		// Ŭ������ �ִ� 8����� ���� �� �ִ�.

#define CLAN_BATTLE					// Ŭ���� ���߿� ������ - ������ ������ ����� ����

//
// Channel
//
#define CHANNELNAME_LEN		64
#define CHANNELRULE_LEN		64
#define DEFAULT_CHANNEL_MAXPLAYERS			200
#define DEFAULT_CHANNEL_MAXSTAGES			100
#define MAX_CHANNEL_MAXSTAGES				500
#define NUM_PLAYERLIST_NODE					6
#define CHANNEL_NO_LEVEL					(-1)

enum MCHANNEL_TYPE {
	MCHANNEL_TYPE_PRESET = 0,
	MCHANNEL_TYPE_USER = 1,
	MCHANNEL_TYPE_PRIVATE = 2,
	MCHANNEL_TYPE_CLAN = 3,
	MCHANNEL_TYPE_MAX
};




enum MMatchTeam
{
	MMT_ALL			= 0,
	MMT_SPECTATOR	= 1,
	MMT_RED			= 2,
	MMT_BLUE		= 3,
	MMT_END
};


// �������
enum MMatchServerMode
{
	MSM_NORMAL_		= 0,		// �Ϲ�
	MSM_CLAN		= 1,		// Ŭ���� ���� ����
	MSM_LADDER		= 2,		// ���� ���� ����
	MSM_EVENT		= 3,		// �̺�Ʈ ����
	MSM_TEST		= 4,		// �׽�Ʈ ����
	MSM_MAX,

	MSM_ALL			= 100,		// event���� ���ȴ�.
};

// ���� ����
enum MMatchProposalMode
{
	MPROPOSAL_NONE = 0,				// ������� ����
	MPROPOSAL_LADDER_INVITE,		// �������� ��û
	MPROPOSAL_CLAN_INVITE,			// Ŭ���� ��û
	MPROPOSAL_END
};


// ���� Ÿ��
enum MLADDERTYPE {
	MLADDERTYPE_NORMAL_2VS2		= 0,
	MLADDERTYPE_NORMAL_3VS3,
	MLADDERTYPE_NORMAL_4VS4,
//	MLADDERTYPE_NORMAL_8VS8,
	MLADDERTYPE_MAX
};

// �� ����Ÿ�Ժ� �ʿ��� �ο���
const int g_nNeedLadderMemberCount[MLADDERTYPE_MAX] = {	2, 3, 4/*, 8*/};


/// Clan����.
#define DEFAULT_CLAN_POINT			1000			// �⺻ Ŭ�� ����Ʈ
#define DAY_OF_DELETE_CLAN			(7)				// Ŭ�� ����û�� DAY_OF_DELETE_CLAN�ϸ�ŭ ������ �м��۾��� �����.
#define MAX_WAIT_CLAN_DELETE_HOUR	(24)			// DAY_OF_DELETE_CLAN + MAX_WAIT_CLAN_DELETE_HOUR�� ��񿡼� Ŭ������.
#define UNDEFINE_DELETE_HOUR		(2000000000)	// �������� Ŭ���� DeleteTime�� null��ó����.

enum MMatchClanDeleteState
{
	MMCDS_NORMAL = 1,
	MMCDS_WAIT,
	MMCDS_DELETE,

	MMCDS_END,
};


// �ɼ� ����
enum MBITFLAG_USEROPTION {
	MBITFLAG_USEROPTION_REJECT_WHISPER	= 1,
	MBITFLAG_USEROPTION_REJECT_INVITE	= 1<<1
};

// ����Ʈ ���� ///////////////////////////////////////////////////////////////////////////////

#define MAX_QUEST_MAP_SECTOR_COUNT					16			// ����Ʈ���� �ִ� ������� �� �ִ� �� ����
#define MAX_QUEST_NPC_INFO_COUNT					8			// ����Ʈ���� �ִ� ���� NPC ���� ����


#define ALL_PLAYER_NOT_READY					1	// ��� ������ ���� ���� ���ؼ� ������ �������� ����.
#define QUEST_START_FAILED_BY_SACRIFICE_SLOT	2	// ��� ������ ���� �˻�� ������ �־ ������ ������.

#define MIN_QUESTITEM_ID							200001	// item id�� 200001���ʹ� ����Ʈ �������̴�
#define MAX_QUESTITEM_ID							299999

// Keeper Manager���� Schedule����. ////////////////////////////////////////////////////////////

enum KMS_SCHEDULE_TYPE
{
	KMST_NO = 0,
	KMST_REPEAT,
	KMST_COUNT,
	KMST_ONCE,

	KMS_SCHEDULE_TYPE_END,
};

enum KMS_COMMAND_TYPE
{
	KMSC_NO = 0,
	KMSC_ANNOUNCE,
	KMSC_STOP_SERVER,
	KMSC_RESTART_SERVER,
	
	KMS_COMMAND_TYPE_END,
};

enum SERVER_STATE_KIND
{
	SSK_OPENDB = 0,

	SSK_END,
};

enum SERVER_ERR_STATE
{
	SES_NO = 0,
	SES_ERR_DB,
    
	SES_END,
};

enum SERVER_TYPE
{
	ST_NULL = 0,
	ST_DEBUG,
	ST_NORMAL,
	ST_CLAN,
	ST_QUEST,
	ST_EVENT,
};


enum MMatchBlockLevel
{
	MMBL_NO = 0,
	MMBL_ACCOUNT,
	MMBL_LOGONLY,

	MMBL_END,
};

/////////////////////////////////////////////////////////////////////////////////////////////
// Util �Լ�

/// ����� ��ȯ
inline MMatchTeam NegativeTeam(MMatchTeam nTeam)
{
	if (nTeam == MMT_RED) return MMT_BLUE;
	else if (nTeam == MMT_BLUE) return MMT_RED;
	return nTeam;
}

#endif