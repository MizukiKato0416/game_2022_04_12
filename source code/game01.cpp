//================================================
//ゲーム01処理
//Author: 加藤瑞葵
//================================================
#include "game01.h"
#include "manager.h"
#include "input_keyboard.h"
#include "player.h"
#include "meshsphere.h"
#include "meshfield.h"
#include "texture.h"
#include "object3D.h"
#include "fade.h"
#include "model_single.h"
#include "play_data.h"
#include "ui.h"
#include "pause.h"
#include "score.h"
#include "time.h"
#include "road.h"
#include "floor.h"

//================================================
//マクロ定義
//================================================
#define GAME01_ROAD_SPEED		(-10.0f)		//道が進むスピード

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CGame01::CGame01(CObject::PRIORITY Priority):CObject(Priority)
{
	m_pPlayer = nullptr;
	m_pFloor = nullptr;
	memset(m_apRoad, NULL, sizeof(m_apRoad[GAME01_MAX_ROAD]));
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CGame01::~CGame01()
{
	
}

//================================================
//初期化処理
//================================================
HRESULT CGame01::Init(void)
{
	//タイムの生成
	CTime::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, TIME_POLIGON_POSY, 0.0f), D3DXVECTOR3(TIME_POLYGON_WIDTH, TIME_POLYGON_HEIGHT, 0.0f), 0);

	//スコアの生成
	CScore *pSocre = nullptr;
	pSocre = CScore::Create(D3DXVECTOR3(0.0f + (SCORE_POLYGON_WIDTH * MAX_SCORE_POLYGON / 2.0f), SCORE_POLYGON_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(SCORE_POLYGON_WIDTH, SCORE_POLYGON_HEIGHT, 0.0f));
	CManager::GetInstance()->GetPlayData()->SetScorePoint(pSocre);

	//ポーズの生成
	CPause::Create();

	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f));

	m_pFloor = CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2000.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pFloor->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_apRoad[0] = CRoad::Create(D3DXVECTOR3(2000.0f, 0.0f, 0.0f), CRoad::HAPPENING_TYPE::NONE, 0.0f);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CGame01::Uninit(void)
{
	//スコアを保存
	CManager::GetInstance()->GetPlayData()->SetScore(CManager::GetInstance()->GetPlayData()->GetScorePoint()->GetScore());
	
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CGame01::Update(void)
{
	//発射したら
	if (m_pPlayer->GetShot() == true)
	{
		//位置サイズを取得
		D3DXVECTOR3 floorPos = m_pFloor->GetPos();
		D3DXVECTOR3 floorSize = m_pFloor->GetSize();
		//位置Xを移動させる
		floorPos.x += GAME01_ROAD_SPEED;
		//位置設定
		m_pFloor->SetPos(floorPos, floorSize);

		//道の移動量が0がったら移動させる
		if (m_apRoad[0]->GetSpeed() == 0.0f)
		{
			m_apRoad[0]->SetSpeed(GAME01_ROAD_SPEED);
		}

		//道0の位置がプレイヤーの位置よりも小さくなったら
		if (m_apRoad[0]->GetPos() <= m_pPlayer->GetPos)
		{
			if (m_apRoad[1] == nullptr)
			{
				m_apRoad[1] = CRoad::Create(D3DXVECTOR3(2000.0f, 0.0f, 0.0f), CRoad::HAPPENING_TYPE::NONE, 0.0f);
			}
		}



	}











	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//Enterキー、スタートボタンを押したら
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		//フェード取得処理
		CFade *pFade;
		pFade = CManager::GetInstance()->GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE::RESULT);
		}
	}
}

//================================================
//描画処理
//================================================
void CGame01::Draw(void)
{

}