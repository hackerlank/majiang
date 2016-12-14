#ifndef TABLE_FRAME_SINK_HEAD_FILE
#define TABLE_FRAME_SINK_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "GameLogic.h"

//////////////////////////////////////////////////////////////////////////
//ö�ٶ���

//Ч������
enum enEstimatKind
{
	EstimatKind_OutCard,			//����Ч��
	EstimatKind_GangCard,			//����Ч��
};

//���Ƶ÷�
struct tagGangScore
{
	BYTE		cbGangCount;							//�ܸ���
	LONGLONG	lScore[MAX_WEAVE][GAME_PLAYER];			//ÿ���ܵ÷�
};

//////////////////////////////////////////////////////////////////////////

struct  HNMJGameRecordPlayer
{
	DWORD dwUserID;
	std::string kHead;
	std::string kNickName;
	std::vector<BYTE> cbCardData;
	void StreamValue(datastream& kData,bool bSend)
	{
		Stream_VALUE(dwUserID);
		Stream_VALUE(kHead);
		Stream_VALUE(kNickName);
		Stream_VECTOR(cbCardData);
	}
};

struct  HNMJGameRecordOperateResult
{
	enum Type
	{
		TYPE_NULL,
		TYPE_OperateResult,
		TYPE_SendCard,
		TYPE_OutCard,
		TYPE_ChiHu,
	};
	HNMJGameRecordOperateResult()
	{
		cbActionType = 0;
		wOperateUser = 0;
		wProvideUser = 0;
		cbOperateCode = 0;
		cbOperateCard = 0;
	}
	BYTE							cbActionType;
	WORD							wOperateUser;						//�����û�
	WORD							wProvideUser;						//��Ӧ�û�
	DWORD							cbOperateCode;						//��������
	BYTE							cbOperateCard;						//�����˿�
	void StreamValue(datastream& kData,bool bSend)
	{
		Stream_VALUE(cbActionType);
		Stream_VALUE(wOperateUser);
		Stream_VALUE(wProvideUser);
		Stream_VALUE(cbOperateCode);
		Stream_VALUE(cbOperateCard);
	}
};
struct  HNMJGameRecord
{
	DWORD dwKindID;
	DWORD dwVersion;
	std::vector<HNMJGameRecordPlayer> kPlayers;
	std::vector<HNMJGameRecordOperateResult> kAction;
	void StreamValue(datastream& kData,bool bSend)
	{
		StructVecotrMember(HNMJGameRecordPlayer,kPlayers);
		StructVecotrMember(HNMJGameRecordOperateResult,kAction);
		Stream_VALUE(dwKindID);
		Stream_VALUE(dwVersion);
	}

};

struct MasterHandCardInfo
{
	int nChairId;
	std::vector<BYTE>    kMasterHandCard;

	void StreamValue(datastream& kData,bool bSend)
	{
		Stream_VALUE(nChairId);
		Stream_VECTOR(kMasterHandCard);
	}
};

struct MasterHandCard
{
	std::vector<MasterHandCardInfo>    kMasterHandCardList;
	void StreamValue(datastream& kData,bool bSend)
	{
		StructVecotrMember(MasterHandCardInfo,kMasterHandCardList);
	}
};

//////////////////////////////////////////////////////////////////////////
//��Ϸ������
class CTableFrameSink : public ITableFrameSink, public ITableUserAction
{
public:
	HNMJGameRecord					m_kGameRecord;
	BYTE							m_cbGameTypeIdex;	//��Ϸ����
	DWORD							m_dwGameRuleIdex;	//��Ϸ����
public:
	BYTE                            m_cbMasterCheckCard[GAME_PLAYER];
	BYTE                            m_cbMasterZhaNiao[GAME_PLAYER];

	//��Ϸ����
protected:
	WORD							m_wBankerUser;							//ׯ���û�
	LONGLONG						m_lGameScore[GAME_PLAYER];				//��Ϸ�÷�
	BYTE							m_cbCardIndex[GAME_PLAYER][MAX_INDEX];	//�û��˿�
	tagGangScore					m_GangScore[GAME_PLAYER];				//
	bool							m_bTrustee[GAME_PLAYER];				//�Ƿ��й�
	WORD							m_wLostFanShu[GAME_PLAYER][GAME_PLAYER];//


	BYTE							m_cbCardDataNiao[MAX_NIAO_CARD];	// ����
	BYTE							m_cbNiaoCount;						//���Ƹ���
	BYTE							m_cbNiaoPick;						//�������

	BYTE							m_cbCanHu[GAME_PLAYER];//�Ƿ��ܺ���  ��ׯ���ܺ�
	bool                           m_bHasCSGang[GAME_PLAYER];//�Ƿ��Ѿ���ɳ��
	//������Ϣ
protected:
	WORD							m_wOutCardUser;							//�����û�
	BYTE							m_cbOutCardData;						//�����˿�
	BYTE							m_cbOutCardData_EX;						//�����˿�
	BYTE							m_cbOutCardCount;						//������Ŀ
	BYTE							m_cbDiscardCount[GAME_PLAYER];			//������Ŀ
	BYTE							m_cbDiscardCard[GAME_PLAYER][55];		//������¼

	//������Ϣ
protected:
	BYTE							m_cbSendCardData;						//�����˿�
	BYTE							m_cbSendCardData_EX;					//
	WORD							m_wHaiDiCout;							//��������ѯ�ʴ���
	WORD							m_wHaiDiUser;							//�������û�
	BYTE							m_cbHaiDiSendCardData;					//����Ϊ������
	BYTE							m_cbSendCardCount;						//������Ŀ
	BYTE							m_cbLeftCardCount;						//ʣ����Ŀ
	BYTE							m_cbRepertoryCard[MAX_REPERTORY];		//����˿�
	BYTE							m_cbRepertoryCard_HZ[MAX_REPERTORY_HZ];		//����˿�


	//���б���
protected:
	WORD							m_wResumeUser;							//��ԭ�û�
	WORD							m_wCurrentUser;							//��ǰ�û�
	WORD							m_wProvideUser;							//��Ӧ�û�
	BYTE							m_cbProvideCard;						//��Ӧ�˿�

	WORD							m_wCSGangHuUser;						//��ɳ�����

	//״̬����
protected:
	bool							m_bSendStatus;							//����״̬
	bool							m_bGangStatus;							//����״̬
	bool							m_bGangOutStatus;						//

	bool							m_bGangStatus_CS;						//��ɳ�ܵ�״̬
	BYTE							m_bCSGangStatusHuCout;						//��ɳ����״̬

	//�û�״̬
public:
	bool							m_bResponse[GAME_PLAYER];				//��Ӧ��־
	DWORD							m_cbUserAction[GAME_PLAYER];			//�û�����
	BYTE							m_cbOperateCard[GAME_PLAYER];			//�����˿�
	DWORD							m_cbPerformAction[GAME_PLAYER];			//ִ�ж���

	LONGLONG						m_lStartHuScore[GAME_PLAYER];	//���ֺ�����	
	CChiHuRight						m_StartHuRight[GAME_PLAYER];	//���ֺ�Ȩλ

	//����˿�
protected:
	BYTE							m_cbWeaveItemCount[GAME_PLAYER];		//�����Ŀ
	tagWeaveItem					m_WeaveItemArray[GAME_PLAYER][MAX_WEAVE];//����˿�

	//������Ϣ
protected:
	BYTE							m_cbChiHuCard;							//�Ժ��˿�
	DWORD							m_dwChiHuKind[GAME_PLAYER];				//�Ժ����
	CChiHuRight						m_ChiHuRight[GAME_PLAYER];				//
	WORD							m_wProvider[GAME_PLAYER];				//

	//�������
protected:
	CGameLogic						m_GameLogic;							//��Ϸ�߼�
	ITableFrame						* m_pITableFrame;						//��ܽӿ�
	const tagGameServiceOption		* m_pGameServiceOption;					//���ò���

	//��������
public:
	//���캯��
	CTableFrameSink();
	//��������
	virtual ~CTableFrameSink();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID Release() { }
	//�ӿڲ�ѯ
	virtual void * QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//����ӿ�
public:
	//��ʼ��
	virtual bool Initialization(IUnknownEx * pIUnknownEx);
	//��λ����
	virtual VOID RepositionSink();

	//��ѯ�ӿ�
public:
	//��ѯ�޶�
	virtual SCORE QueryConsumeQuota(IServerUserItem * pIServerUserItem){  return 0; };
	//���ٻ���
	virtual SCORE QueryLessEnterScore(WORD wChairID, IServerUserItem * pIServerUserItem){ return 0; };
	//��ѯ�Ƿ�۷����
	virtual bool QueryBuckleServiceCharge(WORD wChairID){return true;}

	//�����ӿ�
public:
	//���û���
	virtual void SetGameBaseScore(LONG lBaseScore){};

	//��Ϸ�¼�
public:
	//��Ϸ��ʼ
	virtual bool OnEventGameStart();
	//��Ϸ����
	virtual bool OnEventGameConclude(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason);
	//���ͳ���
	virtual bool OnEventSendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE cbGameStatus, bool bSendSecret);

	void Shuffle(BYTE* RepertoryCard,int nCardCount); //ϴ��
	void GameStart_ZZ();
	void GameStart_CS();

	//�¼��ӿ�
public:
	bool isUseTuoGuan();
	void setActionTimeStart(bool bStart,bool Trustee);
	//��ʱ���¼�
	virtual bool OnTimerMessage(DWORD wTimerID, WPARAM wBindParam);
	//�����¼�
	virtual bool OnDataBaseMessage(WORD wRequestID, VOID * pData, WORD wDataSize) { return false; }
	//�����¼�
	virtual bool OnUserScroeNotify(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason) { return false; }

	//����ӿ�
public:
	//��Ϸ��Ϣ����
	virtual bool OnGameMessage(WORD wSubCmdID, VOID * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem);
	//�����Ϣ����
	virtual bool OnFrameMessage(WORD wSubCmdID, VOID * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem);

	//�û��¼�
public:
	//�û�����
	virtual bool OnActionUserOffLine(WORD wChairID,IServerUserItem * pIServerUserItem);
	//�û�����
	virtual bool OnActionUserConnect(WORD wChairID,IServerUserItem * pIServerUserItem);
	//�û�����
	virtual bool OnActionUserSitDown(WORD wChairID,IServerUserItem * pIServerUserItem, bool bLookonUser);
	//�û�����
	virtual bool OnActionUserStandUp(WORD wChairID,IServerUserItem * pIServerUserItem, bool bLookonUser);
	//�û�ͬ��
	virtual bool OnActionUserOnReady(WORD wChairID,IServerUserItem * pIServerUserItem, void * pData, WORD wDataSize) { return true; }

	virtual void SetPrivateInfo(BYTE bGameTypeIdex,DWORD bGameRuleIdex);
	virtual void SetCreateUserID(DWORD	dwUserID);

	//��Ϸ�¼�
protected:
	//�û�����
	bool OnUserOutCard(WORD wChairID, BYTE cbCardData);
	//�û�����
	bool OnUseHaiDiCard(WORD wChairID, BYTE cbUseHaiDi);
	//�û�����
	bool OnUserOutCardCSGang(WORD wChairID, BYTE cbCardData1,BYTE cbCardData2);
	//�û�����
	bool OnUserOperateCard(WORD wChairID, DWORD cbOperateCode, BYTE cbOperateCard);

public:
	bool hasRule(BYTE cbRule);
	bool isHZGuiZe();
	DWORD AnalyseChiHuCard(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, BYTE cbCurrentCard, CChiHuRight &ChiHuRight);
	DWORD AnalyseChiHuCardZZ(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, BYTE cbCurrentCard, CChiHuRight &ChiHuRight,bool bSelfSendCard);
	DWORD AnalyseChiHuCardCS(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, BYTE cbCurrentCard, CChiHuRight &ChiHuRight,bool bSelfSendCard);
	DWORD AnalyseChiHuCardCS_XIAOHU(const BYTE cbCardIndex[MAX_INDEX], CChiHuRight &ChiHuRight);
	
	//��������
protected:
	//���Ͳ���
	bool SendOperateNotify(WORD wChairID = INVALID_CHAIR);
	//�����й�
	void setChairTrustee(WORD iChairID,bool bTrustee);
	//�ɷ��˿�
	void NoticeGangState(WORD iChairID,bool bSendNotice);
	void SendUseHaiDi(WORD wCurrentUser);
	bool DispatchCardData(WORD wCurrentUser,bool bHaiDi=false);
	bool DispatchCardData_CSGang(WORD wCurrentUser);
	//��Ӧ�ж�
	bool EstimateUserRespond(WORD wCenterUser, BYTE cbCenterCard, enEstimatKind EstimatKind);
	bool EstimateUserRespondCSGang(WORD wCenterUser, BYTE cbCenterCard1,BYTE cbCenterCard2);

	//
	void ProcessChiHuUser( WORD wChairId, bool bGiveUp );
	//
	void FiltrateRight( WORD wChairId,CChiHuRight &chr );
	void checkGangScore(WORD wChairId,const CChiHuRight &chr);
	bool checkSelfGang(WORD wChairID,BYTE cbOperateCard,bool& bPublic);

	BYTE GetNiaoCardNum();
	int setNiaoCard(CChiHuRight chr,BYTE iChairID);

public:
	void starGameRecord();
	void addGameRecordAction(CMD_S_OperateResult kNetInfo);
	void addGameRecordAction(CMD_S_SendCard kNetInfo);
	void addGameRecordAction(CMD_S_OutCard kNetInfo);
	void addGameRecordAction(CMD_S_ChiHu kNetInfo);
public:
	void sendMasterHandCard();
	void sendMasterLeftCard(int nChairldID);
	BYTE getSendCardData(WORD dwSendUser);
public:
	void OnUserXiaoHu(WORD wChairID,DWORD dwCode);
	void getXiaoHuCard(WORD nChairldID,CMD_S_XiaoHu& kXiaoHu);
	int  getLeftCardNum();
};

//////////////////////////////////////////////////////////////////////////

#endif
