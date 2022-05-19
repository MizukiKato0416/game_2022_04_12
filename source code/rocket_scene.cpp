//================================================
//ロケットシーン処理
//Authore:加藤瑞葵
//================================================
#include "rocket_scene.h"
#include "manager.h"
#include "texture.h"
#include "fade.h"
#include "sound.h"
#include "model_single.h"
#include "model.h"
#include "player.h"
#include "score.h"
#include "play_data.h"

#ifdef _DEBUG
#include "input_keyboard.h"
#endif // !_DEBUG

//================================================
//マクロ定義
//================================================

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CRocketScene::CRocketScene()
{
	m_pPlayer = nullptr;
	m_pRocket = nullptr;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CRocketScene::~CRocketScene()
{

}

//================================================
//初期化処理
//================================================
HRESULT CRocketScene::Init(void)
{
	//サウンドの取得
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();
	//止める
	pSound->Stop();

	//ロケットの生成
	m_pRocket = CModelSingle::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_ROCKET, NULL, true);

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f));

	//スコアの生成
	CScore *pSocre = nullptr;
	pSocre = CScore::Create(D3DXVECTOR3(0.0f + (SCORE_POLYGON_WIDTH * MAX_SCORE_POLYGON / 2.0f), SCORE_POLYGON_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(SCORE_POLYGON_WIDTH, SCORE_POLYGON_HEIGHT, 0.0f));
	CManager::GetInstance()->GetPlayData()->SetScorePoint(pSocre);


	return S_OK;
}

//================================================
//終了処理
//================================================
void CRocketScene::Uninit(void)
{
	////サウンド取得処理
	//CSound *pSound;
	//pSound = CManager::GetSound();
	////BGMの停止
	//pSound->Stop(CSound::SOUND_LABEL_MENU_BGM);

	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CRocketScene::Update(void)
{

	//モデルの回転を0にする
	m_pPlayer->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//ロケットと親子関係をつける
	m_pPlayer->SetObjParent(true);
	m_pPlayer->SetMtxParent(m_pRocket->GetModel()->GetMtxPoint());

	m_pPlayer->SetPos(D3DXVECTOR3(0.0f, 50.0f, 0.0f));

	//スコアを加算
	CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore(333333);

#ifdef _DEBUG
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//Enterキーを押したら
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
#endif // !_DEBUG
}

//================================================
//描画処理
//================================================
void CRocketScene::Draw(void)
{
	
}