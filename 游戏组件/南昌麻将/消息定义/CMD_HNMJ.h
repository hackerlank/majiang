#ifndef CMD_SPARROW_HEAD_FILE
#define CMD_SPARROW_HEAD_FILE
#include <vector>

//////////////////////////////////////////////////////////////////////////
//�����궨��
#pragma pack(1)

#define KIND_ID						310									//��Ϸ I D

//�������
#define GAME_PLAYER					4									//��Ϸ����
#define VERSION_SERVER				PROCESS_VERSION(6,0,3)				//����汾
#define VERSION_CLIENT				PROCESS_VERSION(6,0,3)				//����汾

#define GAME_NAME					TEXT("�ϲ��齫")					//��Ϸ����
#define GAME_GENRE					(GAME_GENRE_SCORE|GAME_GENRE_MATCH|GAME_GENRE_GOLD)	//��Ϸ����

//��Ϸ״̬
#define GS_MJ_FREE					GAME_STATUS_FREE								//����״̬
#define GS_MJ_PLAY					(GAME_STATUS_PLAY+1)							//��Ϸ״̬
#define GS_MJ_XIAOHU				(GAME_STATUS_PLAY+2)							//С��״̬

//��������
#define MAX_WEAVE					4									//������
#define MAX_INDEX					34									//�������
#define MAX_COUNT					14									//�����Ŀ
#define MAX_REPERTORY				108									//�����
#define MAX_REPERTORY_HZ			112									//�����齫�����

#define MAX_NIAO_CARD				10									//���������


#define MAX_RIGHT_COUNT				1									//���ȨλDWORD����	

#define GAME_TYPE_ZZ				0
#define GAME_TYPE_CS				1

#define GAME_TYPE_ZZ_ZIMOHU			1		//ֻ����ģ��
#define GAME_TYPE_ZZ_QIDUI			2		//�ɺ��߶�
#define GAME_TYPE_ZZ_QIANGGANGHU	3		//�����ܺ�
#define GAME_TYPE_ZZ_ZHANIAO2		4		//����2��
#define GAME_TYPE_ZZ_ZHANIAO4		5		//����4��
#define GAME_TYPE_ZZ_ZHANIAO6		6		//����6��
#define GAME_TYPE_ZZ_HONGZHONG		7		//�������
#define GAME_TYPE_CS_ZHUANGXIANFEN	8		//ׯ�з�
#define GAME_TYPE_ZZ_ZHANIAO3		9		//����3��
#define GAME_TYPE_ZZ_ZHANIAO5		10		//����5��
#define GAME_TYPE_ZZ_258			11		//258���� ��ɳ�齫
#define GAME_TYPE_ZZ_HONGZHONG_GZ	12		//�ϲ��淨 ��������2�� ���ɽ���

#define GAME_TYPE_ZZ_LIUJU_4CARD	13		//ʣ��4�Ż�ׯ
#define GAME_TYPE_ZZ_ZHANIAO1		14		//����1��
#define GAME_TYPE_ZZ_ZHANIAO_DOUBLE	15		//���񷭱�


#define PAO_FEN           1
#define ZIMO_FEN			2
#define GANG_FEN          3
#define ANGANG_FEN        2
#define ZIMO_GANG_FEN     1

//////////////////////////////////////////////////////////////////////////

//�������
struct CMD_WeaveItem
{
	DWORD						cbWeaveKind;						//�������
	BYTE							cbCenterCard;						//�����˿�
	BYTE							cbPublicCard;						//������־
	WORD							wProvideUser;						//��Ӧ�û�
};

//////////////////////////////////////////////////////////////////////////
//����������ṹ

#define SUB_S_GAME_START			100									//��Ϸ��ʼ
#define SUB_S_OUT_CARD				101									//��������
#define SUB_S_SEND_CARD				102									//�����˿�
#define SUB_S_SEND_CARD_CSGANG		103									//�����˿�
#define SUB_S_OPERATE_NOTIFY		104									//������ʾ
#define SUB_S_OPERATE_RESULT		105									//��������
#define SUB_S_GAME_END				106									//��Ϸ����
#define SUB_S_TRUSTEE				107									//�û��й�
#define SUB_S_CHI_HU				108									//
#define SUB_S_GANG_SCORE			110									//
#define SUB_S_OUT_CARD_CSGANG		111									//
#define SUB_S_XIAO_HU				112									//С��
#define SUB_S_GAME_END_LAST_CARD	113									//ʣ����
#define SUB_S_USE_HAIDI_CARD		114									//�Ƿ��ú���


#define SUB_S_MASTER_HANDCARD		120									//
#define SUB_S_MASTER_LEFTCARD		121									//ʣ���ƶ�

#define SUB_S_ANDROID_RULE         200                                 //���͹����������
//��Ϸ״̬
struct CMD_S_StatusFree
{
	LONGLONG						lCellScore;							//�������
	WORD							wBankerUser;						//ׯ���û�
	bool							bTrustee[GAME_PLAYER];				//�Ƿ��й�
};

//��Ϸ״̬
struct CMD_S_StatusPlay
{
	//��Ϸ����
	LONGLONG						lCellScore;									//��Ԫ����
	WORD							wBankerUser;								//ׯ���û�
	WORD							wCurrentUser;								//��ǰ�û�

	//״̬����
	BYTE							cbActionCard;								//�����˿�
	DWORD							cbActionMask;								//��������
	BYTE							cbLeftCardCount;							//ʣ����Ŀ
	bool							bTrustee[GAME_PLAYER];						//�Ƿ��й�
	WORD							wWinOrder[GAME_PLAYER];						//

	//������Ϣ
	WORD							wOutCardUser;								//�����û�
	BYTE							cbOutCardData;								//�����˿�
	BYTE							cbDiscardCount[GAME_PLAYER];				//������Ŀ
	BYTE							cbDiscardCard[GAME_PLAYER][60];				//������¼

	//�˿�����
	BYTE							cbCardCount;								//�˿���Ŀ
	BYTE							cbCardData[MAX_COUNT];						//�˿��б�
	BYTE							cbSendCardData;								//�����˿�

	//����˿�
	BYTE							cbWeaveCount[GAME_PLAYER];					//�����Ŀ
	CMD_WeaveItem					WeaveItemArray[GAME_PLAYER][MAX_WEAVE];		//����˿�

	bool                           bHasCSGang[GAME_PLAYER];
};

//��Ϸ��ʼ
struct CMD_S_GameStart
{
	LONG							lSiceCount;									//���ӵ���
	WORD							wBankerUser;								//ׯ���û�
	WORD							wCurrentUser;								//��ǰ�û�
	DWORD							cbUserAction;								//�û�����
	BYTE							cbCardData[MAX_COUNT*GAME_PLAYER];			//�˿��б�
	BYTE							cbLeftCardCount;							//
	BYTE							cbXiaoHuTag;                           //С����� 0 ûС�� 1 ��С����

};

//��������
struct CMD_S_OutCard
{
	WORD							wOutCardUser;						//�����û�
	BYTE							cbOutCardData;						//�����˿�
};

//��������
struct CMD_S_OutCard_CSGang
{
	WORD							wOutCardUser;						//�����û�
	BYTE							cbOutCardData1;						//�����˿�
	BYTE							cbOutCardData2;						//�����˿�
};
//�����˿�
struct CMD_S_SendCard
{
	BYTE							cbCardData;							//�˿�����
	DWORD							cbActionMask;						//��������
	WORD							wCurrentUser;						//��ǰ�û�
	bool							bTail;								//ĩβ����
};

//�����˿�
struct CMD_S_UseHaiDi
{
	WORD							wCurrentUser;						//��ǰ�û�
};

//�����˿�
struct CMD_S_SendCard_CSGang
{
	BYTE							cbCardData1;						//�˿�����
	BYTE							cbCardData2;						//�˿�����
	DWORD							cbActionMask;						//��������
	WORD							wCurrentUser;						//��ǰ�û�
};

//������ʾ
struct CMD_S_OperateNotify
{
	WORD							wResumeUser;						//��ԭ�û�
	DWORD							cbActionMask;						//��������
	BYTE							cbActionCard;						//�����˿�
};

//��������
struct CMD_S_OperateResult
{
	WORD							wOperateUser;						//�����û�
	WORD							wProvideUser;						//��Ӧ�û�
	DWORD							cbOperateCode;						//��������
	BYTE							cbOperateCard;						//�����˿�
};

//��Ϸ����
struct CMD_S_GameEnd
{
	BYTE							cbCardCount[GAME_PLAYER];			//
	BYTE							cbCardData[GAME_PLAYER][MAX_COUNT];	//
	//������Ϣ
	WORD							wProvideUser[GAME_PLAYER];			//��Ӧ�û�
	DWORD							dwChiHuRight[GAME_PLAYER];			//��������
	DWORD							dwStartHuRight[GAME_PLAYER];			//���ֺ�������
	LONGLONG						lStartHuScore[GAME_PLAYER];			//���ֺ��Ʒ���

	//������Ϣ
	LONGLONG						lGameScore[GAME_PLAYER];			//��Ϸ����
	int								lGameTax[GAME_PLAYER];				//

	WORD							wWinOrder[GAME_PLAYER];				//��������

	LONGLONG						lGangScore[GAME_PLAYER];//��ϸ�÷�
	BYTE							cbGenCount[GAME_PLAYER];			//
	WORD							wLostFanShu[GAME_PLAYER][GAME_PLAYER];
	WORD							wLeftUser;	//

	//����˿�
	BYTE							cbWeaveCount[GAME_PLAYER];					//�����Ŀ
	CMD_WeaveItem					WeaveItemArray[GAME_PLAYER][MAX_WEAVE];		//����˿�


	BYTE							cbCardDataNiao[MAX_NIAO_CARD];	// ����
	BYTE							cbNiaoCount;	//���Ƹ���
	BYTE							cbNiaoPick;	//�������
};

struct CMD_S_GameEnd_LastCard
{
	BYTE							cbCardCout;//ʣ�����
	BYTE							cbCardData[108];	//ʣ����
};

//�û��й�
struct CMD_S_Trustee
{
	bool							bTrustee;							//�Ƿ��й�
	WORD							wChairID;							//�й��û�
};

//
struct CMD_S_ChiHu
{
	WORD							wChiHuUser;							//
	WORD							wProviderUser;						//
	BYTE							cbChiHuCard;						//
	BYTE							cbCardCount;						//
	LONGLONG						lGameScore;							//
	BYTE							cbWinOrder;							//
};
//
struct CMD_S_XiaoHu
{
	WORD							wXiaoHuUser;							//
	DWORD							dwXiaoCode;

	BYTE							cbCardCount;
	BYTE							cbCardData[MAX_COUNT];

};

//
struct CMD_S_GangScore
{
	WORD							wChairId;							//
	BYTE							cbXiaYu;							//
	LONGLONG						lGangScore[GAME_PLAYER];			//
};

struct CMD_S_AndroidRule
{
	BYTE							cbGameTypeIdex;	//��Ϸ����
	DWORD						dwGameRuleIdex;	//��Ϸ����
};

//////////////////////////////////////////////////////////////////////////
//�ͻ�������ṹ

#define SUB_C_OUT_CARD				1									//��������
#define SUB_C_OPERATE_CARD			3									//�����˿�
#define SUB_C_TRUSTEE				4									//�û��й�
#define SUB_C_XIAOHU				5									//С��
#define SUB_C_MASTER_LEFTCARD		6									//ʣ���ƶ�
#define SUB_C_MASTER_CHEAKCARD		7									//ѡ�����
#define SUB_C_MASTER_ZHANIAO		8									//����
#define SUB_C_OUT_CARD_CSGANG		9									//��ɳ�ܴ��
#define SUB_C_USE_HAIDI				10									//�ú�����

//��������
struct CMD_C_OutCard
{
	BYTE							cbCardData;							//�˿�����
};
//��������
struct CMD_C_OutCard_CSGang
{
	BYTE							cbCardData1;							//�˿�����
	BYTE							cbCardData2;							//�˿�����
};
//��������
struct CMD_C_OperateCard
{
	DWORD							cbOperateCode;						//��������
	BYTE							cbOperateCard;						//�����˿�
};
//��������
struct CMD_C_Use_HaiDi
{
	DWORD							cbUseHaiDi;							//�Ƿ�Ҫ����
};

//�û��й�
struct CMD_C_Trustee
{
	bool							bTrustee;							//�Ƿ��й�	
};

//����С��
struct CMD_C_XiaoHu
{
	DWORD							cbOperateCode;						//��������
	BYTE							cbOperateCard;						//�����˿�
};


struct MaterCheckCard
{
	BYTE							cbCheakCard;						//��������
};

struct MaterNiaoCout
{
	BYTE							cbNiaoCout;							//��������
};

struct MasterLeftCard
{
	BYTE      kMasterLeftIndex[MAX_INDEX];
	BYTE      kMasterCheakCard;
};
//////////////////////////////////////////////////////////////////////////
#pragma pack()
#endif
