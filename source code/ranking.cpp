//================================================
//ランキング処理
//Authore:加藤瑞葵
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "renderer.h"
#include "score.h"
#include "manager.h"
#include "ranking.h"
#include "object.h"
#include "play_data.h"
#include "number.h"
#include "result.h"
#include "tcp_client.h"
#include "communicationdata.h"
#include "object2D.h"

//================================================
//マクロ定義
//================================================
#define MAX_COMMUDATA	(64)		//文字列の最大値
#define RANKING_SIZE_Y	(500.0f)	//ランキングの幅Y

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CRanking::CRanking(CObject::PRIORITY Priority) :CObject(Priority)
{
	m_pCommu = new CTcpClient;
	m_pCommuData = new CCommunicationData;
	for (int nCntRanking = 0; nCntRanking < MAX_SCORE_DATA; nCntRanking++)
	{
		m_nScore[nCntRanking] = 0;
	}
	memset(m_apScore, NULL, sizeof(m_apScore[MAX_RANKING]));
	m_nNowScore = 0;
	m_col = { 0.0f, 0.0f, 0.0f, 0.0f };
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CRanking::~CRanking()
{

}

//================================================
//初期化処理
//================================================
HRESULT CRanking::Init(void)
{
	//スコアの生成
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		CObject2D *pNumber;

		m_apScore[nCntRanking] = CScore::Create(D3DXVECTOR3((m_pos.x), m_pos.y + ((float)(RANKING_SIZE_Y / (MAX_RANKING + 1)) * nCntRanking + (float)(RANKING_SIZE_Y / (MAX_RANKING + 1))), 0.0f),
											    m_size);
		switch (nCntRanking)
		{
		case 0:
			pNumber = CObject2D::Create(D3DXVECTOR3(((m_pos.x - ((MAX_SCORE_POLYGON / 2) * m_size.x) - 50.0f)), m_pos.y + ((float)(RANKING_SIZE_Y / (MAX_RANKING + 1)) * nCntRanking + (float)(RANKING_SIZE_Y / (MAX_RANKING + 1))), 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), static_cast<int>(CObject::PRIORITY::RANKING));
			pNumber->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("1st.png"));
			break;
		case 1:
			pNumber = CObject2D::Create(D3DXVECTOR3(((m_pos.x - ((MAX_SCORE_POLYGON / 2) * m_size.x) - 50.0f)), m_pos.y + ((float)(RANKING_SIZE_Y / (MAX_RANKING + 1)) * nCntRanking + (float)(RANKING_SIZE_Y / (MAX_RANKING + 1))), 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), static_cast<int>(CObject::PRIORITY::RANKING));
			pNumber->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("2nd.png"));
			break;
		case 2:
			pNumber = CObject2D::Create(D3DXVECTOR3(((m_pos.x - ((MAX_SCORE_POLYGON / 2) * m_size.x) - 50.0f)), m_pos.y + ((float)(RANKING_SIZE_Y / (MAX_RANKING + 1)) * nCntRanking + (float)(RANKING_SIZE_Y / (MAX_RANKING + 1))), 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), static_cast<int>(CObject::PRIORITY::RANKING));
			pNumber->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("3rd.png"));
			break;
		case 3:
			pNumber = CObject2D::Create(D3DXVECTOR3(((m_pos.x - ((MAX_SCORE_POLYGON / 2) * m_size.x) - 50.0f)), m_pos.y + ((float)(RANKING_SIZE_Y / (MAX_RANKING + 1)) * nCntRanking + (float)(RANKING_SIZE_Y / (MAX_RANKING + 1))), 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), static_cast<int>(CObject::PRIORITY::RANKING));
			pNumber->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("4th.png"));
			break;
		case 4:
			pNumber = CObject2D::Create(D3DXVECTOR3(((m_pos.x - ((MAX_SCORE_POLYGON / 2) * m_size.x) - 50.0f)), m_pos.y + ((float)(RANKING_SIZE_Y / (MAX_RANKING + 1)) * nCntRanking + (float)(RANKING_SIZE_Y / (MAX_RANKING + 1))), 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), static_cast<int>(CObject::PRIORITY::RANKING));
			pNumber->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("5th.png"));
			break;
		case 5:
			pNumber = CObject2D::Create(D3DXVECTOR3(((m_pos.x - ((MAX_SCORE_POLYGON / 2) * m_size.x) - 50.0f)), m_pos.y + ((float)(RANKING_SIZE_Y / (MAX_RANKING + 1)) * nCntRanking + (float)(RANKING_SIZE_Y / (MAX_RANKING + 1))), 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), static_cast<int>(CObject::PRIORITY::RANKING));
			pNumber->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("6th.png"));
			break;
		default:
			break;
		}
	}
	CCommunicationData::COMMUNICATION_DATA *pData = m_pCommuData->GetCommuData();
	int nScore = CManager::GetPlayData()->GetScore();
	char Send_Data[MAX_COMMUDATA];
	char recv_data[MAX_COMMUDATA];

	m_pCommu->Init();

	if (m_pCommu->Connect())
	{
		memcpy(&Send_Data, &nScore, sizeof(nScore));
		m_pCommu->Send(&Send_Data[0], sizeof(int));

		m_pCommu->Recv(&recv_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA::ranking));
		memcpy(&pData->ranking, recv_data, sizeof(CCommunicationData::COMMUNICATION_DATA::ranking));

		//スコアの設定
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			m_apScore[nCntRanking]->SetScore(pData->ranking[nCntRanking]);
		}
	}
	else
	{
		//スコアの設定
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			m_apScore[nCntRanking]->SetScore(0);
		}
	}

	m_pCommu->Uninit();

	//カラーの設定
	m_col = {255.0f, 255.0f, 255.0f, 255.0f};

	return S_OK;
}

//================================================
//終了処理
//================================================
void CRanking::Uninit(void)
{
	m_pCommu->Uninit();
	Release();
}

//================================================
//更新処理
//================================================
void CRanking::Update(void)
{
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		if (m_nNowScore != 0 && m_nScore[nCntRanking] == m_nNowScore)
		{
			//カラーを薄くする
			m_col.a -= 255.0f;

			if (m_col.a < 0.0f)
			{
				m_col.a = 255.0f;
			}

			for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
			{
				//ナンバーを取得してカラーを設定
				m_apScore[nCntRanking]->GetNumber(nCntNumber)->SetCol(m_col);
			}
			break;
		}
	}
}

//================================================
//描画処理
//================================================
void CRanking::Draw(void)
{
	
}

//================================================
//生成処理
//================================================
CRanking* CRanking::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	//インスタンスの生成
	CRanking *pRanking = NULL;
	if (pRanking == NULL)
	{
		pRanking = new CRanking;
		if (pRanking != NULL)
		{
			pRanking->m_pos = pos;
			pRanking->m_size = size;
			pRanking->Init();
		}
	}
	return pRanking;
}

