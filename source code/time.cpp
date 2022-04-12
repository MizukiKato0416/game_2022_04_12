//================================================
//タイム処理
//Author:加藤瑞葵
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "renderer.h"
#include "time.h"
#include "manager.h"
#include "number.h"
#include "ui.h"
#include "play_data.h"
#include "texture.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CTime::CTime(CObject::PRIORITY Priority) : CObject(Priority)
{
	m_nTime = 0;
	m_nCounter = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CTime::~CTime()
{

}

//================================================
//初期化処理
//================================================
HRESULT CTime::Init(void)
{
	m_nCounter = 0;

	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
	{
		m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x - (m_size.x * MAX_TIME_POLYGON / 2) + (m_size.x * nCntNumber) + (m_size.x / 2.0f), m_pos.y, 0.0f), m_size);
		m_apNumber[nCntNumber]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_NUMBER"));
	}
	return S_OK;
}

//================================================
//終了処理
//================================================
void CTime::Uninit(void)
{
	//時間を保存
	CManager::GetInstance()->GetPlayData()->SetTime(m_nTime);

	//ナンバーの破棄
	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
	{
		if (m_apNumber[nCntNumber] != NULL)
		{
			m_apNumber[nCntNumber]->Uninit();
			delete m_apNumber[nCntNumber];
			m_apNumber[nCntNumber] = NULL;
		}
	}

	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CTime::Update(void)
{
	//カウンターを加算
	m_nCounter++;

	//カウンター60毎に1秒経過させる
	if (m_nCounter % 60 == 0)
	{
		AddTime(1);
	}
}

//================================================
//描画処理
//================================================
void CTime::Draw(void)
{
	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
	{
		m_apNumber[nCntNumber]->Draw();
	}
}

//================================================
//生成処理
//================================================
CTime* CTime::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nStartTime)
{
	//インスタンスの生成
	CTime *pTime = NULL;
	if (pTime == NULL)
	{
		pTime = new CTime;
		if (pTime != NULL)
		{
			pTime->m_nTime = nStartTime;
			pTime->m_pos = pos;
			pTime->m_size = size;
			pTime->Init();
			pTime->SetTime(pTime->m_nTime);
		}
	}
	return pTime;
}

//================================================
//スコア取得処理
//================================================
int CTime::GetTime(void)
{
	return m_nTime;
}

//================================================
//スコア設定処理
//================================================
void CTime::SetTime(int nTime)
{
	m_nTime = nTime;

	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
	{
		if (nCntNumber == 0)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nTime / (int)powf(10, MAX_TIME_POLYGON - 1));
		}
		else if (nCntNumber == MAX_TIME_POLYGON - 1)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nTime % 10);
		}
		else
		{
			m_apNumber[nCntNumber]->SetNumber(m_nTime % (int)powf(10, MAX_TIME_POLYGON - (float)nCntNumber) / (int)powf(10, MAX_TIME_POLYGON - 1 - (float)nCntNumber));
		}
	}
}

//================================================
//スコア加算処理
//================================================
void CTime::AddTime(int nValue)
{
	m_nTime += nValue;

	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
	{
		if (nCntNumber == 0)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nTime / (int)powf(10, MAX_TIME_POLYGON - 1));
		}
		else if (nCntNumber == MAX_TIME_POLYGON - 1)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nTime % 10);
		}
		else
		{
			m_apNumber[nCntNumber]->SetNumber(m_nTime % (int)powf(10, MAX_TIME_POLYGON - (float)nCntNumber) / (int)powf(10, MAX_TIME_POLYGON - 1 - (float)nCntNumber));
		}
	}
}

//=============================================================================
// number取得処理
//=============================================================================
CNumber* CTime::GetNumber(int nNumber)
{
	return m_apNumber[nNumber];
}