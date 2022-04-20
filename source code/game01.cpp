//================================================
//ゲーム01処理
//Author: 加藤瑞葵
//================================================
#include "game01.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_mouse.h"
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
#define GAME01_MOUSE_VEC_ADJUSTMENT_X		(0.08f)		//引っ張ったときのベクトルを小さくする割合X
#define GAME01_MOUSE_VEC_ADJUSTMENT_Y		(0.1f)		//引っ張ったときのベクトルを小さくする割合Y

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
	m_mouseTriggerPos = { 0.0f, 0.0f, 0.0f };
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
	//変数の初期化
	m_mouseTriggerPos = { 0.0f, 0.0f, 0.0f };

	CObject3D *pObject3D = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR3(4000.0f, 2000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pObject3D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_SKY"));

	//タイムの生成
	CTime::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, TIME_POLIGON_POSY, 0.0f), D3DXVECTOR3(TIME_POLYGON_WIDTH, TIME_POLYGON_HEIGHT, 0.0f), 0);

	//スコアの生成
	CScore *pSocre = nullptr;
	pSocre = CScore::Create(D3DXVECTOR3(0.0f + (SCORE_POLYGON_WIDTH * MAX_SCORE_POLYGON / 2.0f), SCORE_POLYGON_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(SCORE_POLYGON_WIDTH, SCORE_POLYGON_HEIGHT, 0.0f));
	CManager::GetInstance()->GetPlayData()->SetScorePoint(pSocre);

	//ポーズの生成
	CPause::Create();

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f));

	//スタート地点の生成
	m_pFloor = CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(FLOOR_SIZE.x, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pFloor->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	//最初の道の生成
	m_apRoad[0] = CRoad::Create(D3DXVECTOR3(FLOOR_SIZE.x, 0.0f, 0.0f), FLOOR_SIZE, 0.0f);

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
		//スタート地点の床が消えていなかったら
		if (m_pFloor != nullptr)
		{
			//位置サイズを取得
			D3DXVECTOR3 floorPos = m_pFloor->GetPos();
			D3DXVECTOR3 floorSize = m_pFloor->GetSize();
			//位置Xを移動させる
			floorPos.x += -m_pPlayer->GetMoveForward();
			//位置設定
			m_pFloor->SetPos(floorPos, floorSize);
		}

		//常にプレイヤーが前に進む力分逆の方向に移動させる
		for (int nCntRoad = 0; nCntRoad < GAME01_MAX_ROAD; nCntRoad++)
		{
			if (m_apRoad[nCntRoad] != nullptr)
			{
				m_apRoad[nCntRoad]->SetSpeed(-m_pPlayer->GetMoveForward());
			}
		}

		if (m_apRoad[1] != nullptr)
		{
			//道1の位置がプレイヤーの位置よりも小さくなったら
			if (m_apRoad[1]->GetPos().x <= m_pPlayer->GetPos().x)
			{
				//道0を消す
				m_apRoad[0]->Uninit();
				m_apRoad[0] = nullptr;
				//配列を入れ替える
				std::swap(m_apRoad[1], m_apRoad[0]);

				//スタート地点の床が消えていなかったら
				if (m_pFloor != nullptr)
				{
					//消す
					m_pFloor->Uninit();
					m_pFloor = nullptr;
				}
			}
		}

		//道0の位置がプレイヤーの位置よりも小さくなったら
		if (m_apRoad[0]->GetPos().x <= m_pPlayer->GetPos().x)
		{
			if (m_apRoad[1] == nullptr)
			{
				//プレイヤーの現在地化から道の現在地を引く
				D3DXVECTOR3 pos = m_pPlayer->GetPos() - m_apRoad[0]->GetPos();
				//引いて出た分だけXの位置をずらして道を生成
				m_apRoad[1] = CRoad::Create(D3DXVECTOR3(FLOOR_SIZE.x - pos.x, 0.0f, 0.0f), FLOOR_SIZE, -m_pPlayer->GetMoveForward());
			}
		}
	}
	else
	{//発射していない状態なら
		//マウス取得処理
		CInputMouse *pInputMouse;
		pInputMouse = CManager::GetInstance()->GetInputMouse();

		//マウスを押した瞬間
		if (pInputMouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			//マウスの位置取得
			POINT mouseTriggerPos;
			GetCursorPos(&mouseTriggerPos);
			ScreenToClient(CManager::GetWindowHandle(), &mouseTriggerPos);

			//マウスの位置を保存
			m_mouseTriggerPos.x = (float)mouseTriggerPos.x;
			m_mouseTriggerPos.y = (float)mouseTriggerPos.y;
		}

		//マウスを離した瞬間
		if (pInputMouse->GetRelease(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			//マウスの位置取得
			POINT mouseReleasePos;
			GetCursorPos(&mouseReleasePos);
			ScreenToClient(CManager::GetWindowHandle(), &mouseReleasePos);

			//マウスをクリックした位置から離した位置までのベクトルを算出
			D3DXVECTOR3 mousePosVec = D3DXVECTOR3(m_mouseTriggerPos.x - mouseReleasePos.x, m_mouseTriggerPos.y - mouseReleasePos.y, 0.0f);
			//ベクトルのyを逆向きにする
			mousePosVec.y *= -1.0f;
			//ベクトルを既定の割合小さくする
			mousePosVec.x *= GAME01_MOUSE_VEC_ADJUSTMENT_X;
			mousePosVec.y *= GAME01_MOUSE_VEC_ADJUSTMENT_Y;

			//発射している状態にする
			m_pPlayer->SetShot(true);
			//ジャンプ量設定
			m_pPlayer->SetJump(mousePosVec.y);
			//前に進む力を設定
			m_pPlayer->SetMoveForward(mousePosVec.x);
		}
	}

#ifdef _DEBUG
	//マウス取得処理
	CInputMouse *pInputMouse;
	pInputMouse = CManager::GetInstance()->GetInputMouse();

	//マウスを押した瞬間
	if (pInputMouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
	{
		//マウスの位置取得
		POINT mouseTriggerPos;
		GetCursorPos(&mouseTriggerPos);
		ScreenToClient(CManager::GetWindowHandle(), &mouseTriggerPos);

		//マウスの位置を保存
		m_mouseTriggerPos.x = (float)mouseTriggerPos.x;
		m_mouseTriggerPos.y = (float)mouseTriggerPos.y;
	}

	//マウスを離した瞬間
	if (pInputMouse->GetRelease(CInputMouse::MOUSE_TYPE_LEFT) == true)
	{
		//マウスの位置取得
		POINT mouseReleasePos;
		GetCursorPos(&mouseReleasePos);
		ScreenToClient(CManager::GetWindowHandle(), &mouseReleasePos);

		//マウスをクリックした位置から離した位置までのベクトルを算出
		D3DXVECTOR3 mousePosVec = D3DXVECTOR3(m_mouseTriggerPos.x - mouseReleasePos.x, m_mouseTriggerPos.y - mouseReleasePos.y, 0.0f);
		//ベクトルのyを逆向きにする
		mousePosVec.y *= -1.0f;
		//ベクトルを既定の割合小さくする
		mousePosVec.x *= GAME01_MOUSE_VEC_ADJUSTMENT_X;
		mousePosVec.y *= GAME01_MOUSE_VEC_ADJUSTMENT_Y;

		//発射している状態にする
		m_pPlayer->SetShot(true);
		//ジャンプ量設定
		m_pPlayer->SetJump(mousePosVec.y);
		//前に進む力を設定
		m_pPlayer->SetMoveForward(mousePosVec.x);
	}
#endif // _DEBUG


	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//Enterキー、スタートボタンを押したら
	if (pInputKeyboard->GetTrigger(DIK_LSHIFT) == true)
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