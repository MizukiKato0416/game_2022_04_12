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
#include "bg.h"
#include "smoke.h"
#include "camera.h"

#ifdef _DEBUG
#include "input_keyboard.h"
#endif // !_DEBUG

//================================================
//マクロ定義
//================================================
#define ROCKET_SCENE_BG_POS_Z				(100.0f)										//背景の位置Z
#define ROCKET_SCENE_BG_POS_Y				(300.0f)										//背景の位置Y調整値
#define ROCKET_SCENE_BG_SIZE				(D3DXVECTOR3(SCREEN_WIDTH, 4971.0f, 0.0f))		//背景のサイズ
#define ROCKET_SCENE_BG_SIZE_ADJUSTMENT		(0.8f)											//背景のサイズ調整値
#define ROCKET_SCENE_BG_01_SPEED			(-0.001f)										//背景1の移動スピード
#define ROCKET_SCENE_BG_02_SPEED			(-0.0001f)										//背景2の移動スピード
#define ROCKET_SCENE_BG_03_SPEED			(-0.00014f)										//背景3の移動スピード
#define ROCKET_SCENE_BG_04_SPEED			(-0.00018f)										//背景4の移動スピード
#define ROCKET_SCENE_ROCKET_SPEED			(6.0f)											//ロケットの速さ
#define ROCKET_SCENE_SMOKE_ROT_RAND			(float (rand() % 629 + -314) / 100)				//回転する際の方向を決めるためのランダム値
#define ROCKET_SCENE_SMOKE_POS_X_RAND		(float (rand() % 20 + -10))						//ロケット雲の位置Xのランダム値
#define ROCKET_SCENE_SMOKE_POS_Y_RAND		(30.0f)											//ロケット雲の位置Yのランダム値
#define ROCKET_SCENE_SMOKE_SIZE				(D3DXVECTOR3 (20.0f, 20.0f, 0.0f))				//ロケット雲のサイズ
#define ROCKET_SCENE_SMOKE_ADD_ROTATE		(0.2f)											//ロケット雲の回転加算値
#define ROCKET_SCENE_SMOKE_ADD_SIZE			(D3DXVECTOR3 (0.7f, 0.7f, 0.0f))				//ロケット雲のサイズ加算値
#define ROCKET_SCENE_SMOKE_SUBTRACT_ALPHA	(0.004f)										//ロケット雲のα値減算値
#define ROCKET_SCENE_SMOKE_NUM				(3)												//煙を出す量
#define ROCKET_SCENE_ADD_SCORE				(333333)										//スコアを加算する量
#define ROCKET_SCENE_PLAYER_POS_Y			(120.0f)										//プレイヤーの位置
#define ROCKET_SCENE_CAMERA_V_POS			(D3DXVECTOR3(0.0f, 0.0f, -500.0f))				//カメラの位置
#define ROCKET_SCENE_CAMERA_SHAKE_POS		(float (rand() % 10 + -5))						//カメラを揺らす量
#define ROCKET_SCENE_RESULT_COUNTER			(180)											//リザルトに行くまでの時間
#define ROCKET_SCENE_ERROR_SIZE				(D3DXVECTOR3(927.0f, 155.0f, 0.0f))				//測定不能UIのサイズ
#define ROCKET_SCENE_MASK_ADD_COL			(0.03f)											//マスクのカラー加算値

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
	m_pScore = nullptr;
	memset(m_apBg, NULL, sizeof(m_apBg[ROCKET_SCENE_BG_NUM]));
	m_nCounter = 0;
	m_bResult = false;
	m_pDengerMask = nullptr;
	m_bAddCol = false;
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
	//変数初期化
	m_nCounter = 0;
	m_bResult = false;
	m_bAddCol = true;

	//サウンドの取得
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();
	//止める
	pSound->Stop();

	//再生
	pSound->ControllVoice(CSound::SOUND_LABEL::ROCKET_SE, 0.8f);
	pSound->Play(CSound::SOUND_LABEL::ROCKET_SE);
	pSound->ControllVoice(CSound::SOUND_LABEL::ERROR_BGM, 1.8f);
	pSound->Play(CSound::SOUND_LABEL::ERROR_BGM);

	//背景の生成
	for(int nCntBg = 0; nCntBg < ROCKET_SCENE_BG_NUM; nCntBg++)
	{ 
		m_apBg[nCntBg] = CBg::Create(D3DXVECTOR3(0.0f, ROCKET_SCENE_BG_SIZE.y * ROCKET_SCENE_BG_SIZE_ADJUSTMENT / 2.0f - ROCKET_SCENE_BG_POS_Y,
								                 ROCKET_SCENE_BG_POS_Z),
								     D3DXVECTOR3(ROCKET_SCENE_BG_SIZE.x * ROCKET_SCENE_BG_SIZE_ADJUSTMENT,
								     	         ROCKET_SCENE_BG_SIZE.y * ROCKET_SCENE_BG_SIZE_ADJUSTMENT, 0.0f),
								     D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	}
	m_apBg[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("bg_universe.png"));
	m_apBg[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("bg_universe_purple.png"));
	m_apBg[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("bg_universe_light blue.png"));
	m_apBg[3]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("bg_universe_yellow.png"));

	m_apBg[0]->SetUvMove(D3DXVECTOR2(0.0f, ROCKET_SCENE_BG_01_SPEED));
	m_apBg[1]->SetUvMove(D3DXVECTOR2(0.0f, ROCKET_SCENE_BG_02_SPEED));
	m_apBg[2]->SetUvMove(D3DXVECTOR2(0.0f, ROCKET_SCENE_BG_03_SPEED));
	m_apBg[3]->SetUvMove(D3DXVECTOR2(0.0f, ROCKET_SCENE_BG_04_SPEED));


	//ロケットの生成
	m_pRocket = CModelSingle::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_ROCKET, NULL, true);

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f));

	//モデルの回転を0にする
	m_pPlayer->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//位置を上げる
	m_pPlayer->SetOffsetPos(D3DXVECTOR3(0.0f, ROCKET_SCENE_PLAYER_POS_Y, 0.0f));
	//ロケットと親子関係をつける
	m_pPlayer->SetObjParent(true);
	m_pPlayer->SetMtxParent(m_pRocket->GetModel()->GetMtxPoint());

	//スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3(0.0f + (SCORE_POLYGON_WIDTH * MAX_SCORE_POLYGON / 2.0f), SCORE_POLYGON_HEIGHT / 2.0f, 0.0f),
							  D3DXVECTOR3(SCORE_POLYGON_WIDTH, SCORE_POLYGON_HEIGHT, 0.0f));
	CManager::GetInstance()->GetPlayData()->SetScorePoint(m_pScore);


	//カメラのポインタ配列1番目のアドレス取得
	CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
	//cameraの取得
	CCamera* pCamera = &**pCameraAddress;
	//カメラの位置設定
	pCamera->SetPosR(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCamera->SetPosV(ROCKET_SCENE_CAMERA_V_POS);

	//マスクの生成
	m_pDengerMask = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
		                              static_cast<int>(CObject::PRIORITY::MASK));
	m_pDengerMask->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("denger_mask.png"));
	m_pDengerMask->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	return S_OK;
}

//================================================
//終了処理
//================================================
void CRocketScene::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CRocketScene::Update(void)
{
	//煙を出す
	for (int nCnt = 0; nCnt < ROCKET_SCENE_SMOKE_NUM; nCnt++)
	{
		CSmoke::Create(D3DXVECTOR3(0.0f + ROCKET_SCENE_SMOKE_POS_X_RAND, 0.0f + ROCKET_SCENE_SMOKE_POS_Y_RAND, 0.0f),
			           ROCKET_SCENE_SMOKE_SIZE, D3DXVECTOR3(0.0f, 0.0f, ROCKET_SCENE_SMOKE_ROT_RAND),
			           D3DXVECTOR3(0.0f, -ROCKET_SCENE_ROCKET_SPEED, 0.0f),
			           D3DXVECTOR3(0.0f, 0.0f, ROCKET_SCENE_SMOKE_ADD_ROTATE),
			           ROCKET_SCENE_SMOKE_ADD_SIZE, ROCKET_SCENE_SMOKE_SUBTRACT_ALPHA);
	}
	
	//スコア処理
	Score();
	
	//カメラ処理
	Camera();

	//マスク処理
	Mask();

	//リザルトに行くようになってたら
	if (m_bResult == true)
	{
		//カウンターを加算
		m_nCounter++;

		//既定の値より大きくなったら
		if (m_nCounter > ROCKET_SCENE_RESULT_COUNTER)
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

//================================================
//スコア処理
//================================================
void CRocketScene::Score(void)
{
	if (m_pScore != nullptr)
	{
		//スコアを加算
		CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore(ROCKET_SCENE_ADD_SCORE);
		//スコアが最大値以上になったら
		if (CManager::GetInstance()->GetPlayData()->GetScorePoint()->GetScore() >= MAX_SCORE)
		{
			//スコアを消す
			m_pScore->Uninit();
			m_pScore = nullptr;

			//リザルトに行くようにする
			m_bResult = true;

			//測定不能UIを生成
			CObject2D *pUi = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
							                   ROCKET_SCENE_ERROR_SIZE, static_cast<int>(CObject::PRIORITY::UI));
			pUi->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("error.png"));
		}
	}
}

//================================================
//カメラ処理
//================================================
void CRocketScene::Camera(void)
{
	//カメラのポインタ配列1番目のアドレス取得
	CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
	//cameraの取得
	CCamera* pCamera = &**pCameraAddress;

	//ずらす量を設定
	D3DXVECTOR3 shakePos = D3DXVECTOR3(ROCKET_SCENE_CAMERA_SHAKE_POS, ROCKET_SCENE_CAMERA_SHAKE_POS, 0.0f);

	//位置をずらす
	D3DXVECTOR3 posR = shakePos;
	D3DXVECTOR3 posV = ROCKET_SCENE_CAMERA_V_POS + shakePos;

	//位置設定
	pCamera->SetPosR(posR);
	pCamera->SetPosV(posV);
}

//================================================
//マスク処理
//================================================
void CRocketScene::Mask(void)
{
	//色を取得
	D3DXCOLOR col = m_pDengerMask->GetCol();

	//加算する状態なら
	if (m_bAddCol == true)
	{
		//加算
		col.a += ROCKET_SCENE_MASK_ADD_COL;
		//1以上になったら
		if (col.a >= 1.0f)
		{
			//1にする
			col.a = 1.0f;
			//減算する状態にする
			m_bAddCol = false;
		}
	}
	else
	{
		//加算
		col.a -= ROCKET_SCENE_MASK_ADD_COL;
		//0以下になったら
		if (col.a <= 0.0f)
		{
			//0にする
			col.a = 0.0f;
			//加算する状態にする
			m_bAddCol = true;
		}
	}
	//色設定
	m_pDengerMask->SetCol(col);
}
