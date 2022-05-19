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
#include "object2D.h"
#include "fade.h"
#include "model_single.h"
#include "play_data.h"
#include "ui.h"
#include "pause.h"
#include "score.h"
#include "time.h"
#include "road.h"
#include "floor.h"
#include "camera.h"
#include "gauge.h"
#include "bg.h"
#include "rocket.h"
#include "model.h"
#include "trophy.h"
#include "sound.h"

//================================================
//マクロ定義
//================================================
#define GAME01_MOUSE_VEC_ADJUSTMENT_0			(0.4f)		//引っ張ったときのベクトルを小さくする割合0
#define GAME01_MOUSE_VEC_ADJUSTMENT_1			(0.5f)		//引っ張ったときのベクトルを小さくする割合1
#define GAME01_MOUSE_VEC_ADJUSTMENT_2			(0.6f)		//引っ張ったときのベクトルを小さくする割合2
#define GAME01_MOUSE_VEC_ADJUSTMENT_3			(0.7f)		//引っ張ったときのベクトルを小さくする割合3
#define GAME01_MOUSE_VEC_ADJUSTMENT_4			(0.8f)		//引っ張ったときのベクトルを小さくする割合4
#define GAME01_MOUSE_VEC_ADJUSTMENT_5			(0.9f)		//引っ張ったときのベクトルを小さくする割合5
#define GAME01_MOUSE_VEC_ADJUSTMENT_6			(1.0f)		//引っ張ったときのベクトルを小さくする割合6
#define GAME01_CAMERA_ADD_POS					(10.0f)		//カメラの位置を加算する量
#define GAME01_CAMERA_ADD_DIFFER				(10.0f)		//カメラの視点と注視点の距離を加算する量
#define GAME01_CAMERA_VIEW_CHANGE_MOVE			(20.0f)		//カメラを視野をDEFAULTから最大に変える境界線のプレイヤーのバウンドする瞬間の移動量
#define GAME01_SCORE_MAGNIFICATION				(10.0f)		//プレイヤーが前に進む力をスコアにする際の倍率
#define GAME01_SHOT_GAUGE_MAX					(100)		//ショットゲージの最大値
#define GAME01_SHOT_GAUGE_ADD					(2)			//ショットゲージを増やす量
#define GAME01_SHOT_GAUGE_COUNTER_MAX			(10)		//ショットゲージが最大までたまっている状態の時間
#define GAME01_SHOT_GAUGE_CASE_1				(20)		//ショットゲージの段階1
#define GAME01_SHOT_GAUGE_CASE_2				(40)		//ショットゲージの段階2
#define GAME01_SHOT_GAUGE_CASE_3				(60)		//ショットゲージの段階3
#define GAME01_SHOT_GAUGE_CASE_4				(80)		//ショットゲージの段階4
#define GAME01_SHOT_GAUGE_SUBTRACT_ALPHA		(0.02f)		//ショットゲージを薄くする量
#define GAME01_BG_SIZE_ADJUSTMENT				(3.0f)		//背景の大きくする割合
#define GAME01_BG_POS_Z							(1000.0f)	//背景の位置Z
#define GAME01_BG_POS_Y							(300.0f)	//背景の位置Y
#define GAME01_BG_1_MAGNIFICATION				(0.00004f)	//背景1が前に進む力を背景の移動にする際の倍率
#define GAME01_BG_2_MAGNIFICATION				(0.00006f)	//背景2が前に進む力を背景の移動にする際の倍率
#define GAME01_BG_3_MAGNIFICATION				(0.00008f)	//背景3が前に進む力を背景の移動にする際の倍率
#define GAME01_BG_1_MOVE_INIT					(0.00006f)	//背景1の初期移動量
#define GAME01_BG_2_MOVE_INIT					(0.00008f)	//背景2の初期移動量
#define GAME01_BG_3_MOVE_INIT					(0.0001f)	//背景3の初期移動量
#define GAME01_SHOT_UI_ADD_SIZE_COUNTER			(9)			//発射用UIのサイズを大きくする時間
#define GAME01_SHOT_UI_ADD_SIZE					(1.02f)		//発射用UIのサイズを大きくする割合
#define GAME01_SHOT_UI_SUBTRACT_SIZE_COUNTER	(18)		//発射用UIのサイズを小さくする時間
#define GAME01_SHOT_UI_SUBTRACT_SIZE			(0.98f)		//発射用UIのサイズを小さくする割合
#define GAME01_SHOT_UI_UNINIT_COUNTER			(30)		//発射用UIを消し始める時間
#define GAME01_SHOT_UI_SUBTRACT_ALPHA			(0.06f)		//発射用UIのα値減算量
#define GAME01_SHOT_UI_MOVE_Y					(-0.8f)		//発射用UIの移動量Y
#define GAME01_ARROW_UI_SUBTRACT_ALPHA			(0.06f)		//矢印UIのα値減算量
#define GAME01_FINISH_COUNTER					(180)		//ゲームクリア表示時間
#define GAME01_SHOT_JUDGE_UI_SIZE_X				(400.0f)	//発射時審査UIサイズX
#define GAME01_SHOT_JUDGE_UI_SIZE_Y				(80.0f)		//発射時審査UIサイズ
#define GAME01_SHOT_JUDGE_UI_POS_Y				(200.0f)	//発射時審査UI位置
#define GAME01_FLYING_DISTANCE_1000				(100000)	//飛距離1000
#define GAME01_FLYING_DISTANCE_5000				(500000)	//飛距離5000
#define GAME01_FLYING_DISTANCE_10000			(1000000)	//飛距離10000
#define GAME01_ROCKET_POS_X						(-800.0f)	//ロケットの位置
#define GAME01_START_CLOUD_POS_Y				(-1500.0f)	//スタートの雲の位置Y
#define GAME01_START_CLOUD_POS_Z				(500.0f)	//スタートの雲の位置Z


#ifdef _DEBUG
#define GAME01_MOUSE_VEC_ADJUSTMENT_DEBUG	(0.08f)		//引っ張ったときのベクトルを小さくする割合デバッグ用
#endif // !_DEBUG


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
	memset(m_pBg, NULL, sizeof(m_pBg[GAME01_MAX_BG]));
	m_mouseTriggerPos = { 0.0f, 0.0f, 0.0f };
	m_shotMoveVec = { 0.0f, 0.0f, 0.0f };
	m_pGauge = nullptr;
	m_nGaugeCounter = 0;
	m_pGaugeFrame = nullptr;
	m_pRocket = nullptr;
	m_pShotUi = nullptr;
	m_bReleaseMouse = false;
	m_pArrow = nullptr;
	m_bFinish = false;
	m_nFinishCounter = 0;
	m_bPause = false;
	m_pStart = nullptr;
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
	m_shotMoveVec = { 0.0f, 0.0f, 0.0f };
	m_nGaugeCounter = 0;
	m_pShotUi = nullptr;
	m_bReleaseMouse = false;
	m_pArrow = nullptr;
	m_bFinish = false;
	m_nFinishCounter = 0;
	m_bPause = false;
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();

	sound->Stop();
	sound->Play(CSound::SOUND_LABEL::GAME_BGM);
	sound->ControllVoice(CSound::SOUND_LABEL::GAME_BGM, 1.6f);

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
	m_pFloor = CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), FLOOR_SIZE, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pFloor->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));
	m_pStart = CModelSingle::Create(D3DXVECTOR3(0.0f, GAME01_START_CLOUD_POS_Y, GAME01_START_CLOUD_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                            CXload::X_TYPE_CLOUD, NULL, false);

	//最初の道の生成
	m_apRoad[0] = CRoad::Create(D3DXVECTOR3(FLOOR_SIZE.x, 0.0f, 0.0f), FLOOR_SIZE, 0.0f);

	//ゲージのフレーム生成
	m_pGaugeFrame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
		                              static_cast<int>(CObject::PRIORITY::UI));
	m_pGaugeFrame->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("gauge_frame.png"));

	//ショットゲージの生成
	m_pGauge = CGauge::Create(D3DXVECTOR3(GAUGE_SHOT_POS_X, GAUGE_SHOT_POS_Y, 0.0f),
		                      D3DXVECTOR3(GAUGE_SHOT_SIZE_X, GAUGE_SHOT_SIZE_Y, 0.0f), GAME01_SHOT_GAUGE_MAX, 0);
	m_pGauge->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("gauge.png"));

	//背景1の生成
	m_pBg[0] = CBg::Create(D3DXVECTOR3(0.0f, GAME01_BG_POS_Y, GAME01_BG_POS_Z),
		                   D3DXVECTOR3(SCREEN_WIDTH * GAME01_BG_SIZE_ADJUSTMENT, SCREEN_HEIGHT * GAME01_BG_SIZE_ADJUSTMENT, 0.0f),
		                   D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(GAME01_BG_1_MOVE_INIT, 0.0f));
	m_pBg[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("sky_01.png"));

	//背景2の生成
	m_pBg[1] = CBg::Create(D3DXVECTOR3(0.0f, GAME01_BG_POS_Y, GAME01_BG_POS_Z),
		                   D3DXVECTOR3(SCREEN_WIDTH * GAME01_BG_SIZE_ADJUSTMENT, SCREEN_HEIGHT * GAME01_BG_SIZE_ADJUSTMENT, 0.0f),
		                   D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(GAME01_BG_2_MOVE_INIT, 0.0f));
	m_pBg[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("sky_02.png"));

	//背景3の生成
	m_pBg[2] = CBg::Create(D3DXVECTOR3(0.0f, GAME01_BG_POS_Y, GAME01_BG_POS_Z),
		                   D3DXVECTOR3(SCREEN_WIDTH * GAME01_BG_SIZE_ADJUSTMENT, SCREEN_HEIGHT * GAME01_BG_SIZE_ADJUSTMENT, 0.0f),
		                   D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(GAME01_BG_3_MOVE_INIT, 0.0f));
	m_pBg[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("sky_03.png"));
	
	//ロケットの生成
	m_pRocket = CRocket::Create(D3DXVECTOR3(GAME01_ROCKET_POS_X, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//================================================
//終了処理
//================================================
void CGame01::Uninit(void)
{
	//スコアを保存
	CManager::GetInstance()->GetPlayData()->SetScore(CManager::GetInstance()->GetPlayData()->GetScorePoint()->GetScore());
	
	//トロフィーの飛距離のフラグ処理
	FlyingDistanceFlag();

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
		if (m_pGaugeFrame != nullptr && m_pGauge != nullptr)
		{
			//ゲージを消す処理
			UninitGauge();
		}

		if (m_pArrow != nullptr)
		{
			//矢印を消す処理
			UninitArrow();
		}

		//カメラの処理
		Camera();

		//道の処理
		Road();

		//ロケットの処理
		Rocket();

		//プレイヤーが前に進む力を取得
		float fScoreMoveForward = m_pPlayer->GetMoveForward();

		//前に進む力が負の数だったら
		if (fScoreMoveForward < 0.0f)
		{
			//0にする
			fScoreMoveForward = 0.0f;
		}
		else if(fScoreMoveForward > 0.0f)
		{//前に進む力が正の数だったら
			//前に進む力を既定の倍率大きくする
			fScoreMoveForward *= GAME01_SCORE_MAGNIFICATION;
		}

		//背景のUV座標をプレイヤーが前に進む力分移動させる
		m_pBg[0]->SetUvMove(D3DXVECTOR2(GAME01_BG_1_MOVE_INIT + m_pPlayer->GetMoveForward() * GAME01_BG_1_MAGNIFICATION, 0.0f));
		m_pBg[1]->SetUvMove(D3DXVECTOR2(GAME01_BG_2_MOVE_INIT + m_pPlayer->GetMoveForward() * GAME01_BG_2_MAGNIFICATION, 0.0f));
		m_pBg[2]->SetUvMove(D3DXVECTOR2(GAME01_BG_3_MOVE_INIT + m_pPlayer->GetMoveForward() * GAME01_BG_3_MAGNIFICATION, 0.0f));
		

		//スコアをプレイヤーが前に進む力分加算
		CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore((int)fScoreMoveForward);
	}
	else if(m_pPlayer->GetShot() == false && m_bReleaseMouse == false)
	{//発射していなかったら且つマウスを離していないとき
		//ゲージ処理
		Gauge();
	}

	//ポーズのフラグが立っていなかったら
	if (m_bPause == false)
	{
		//発射処理
		Shot();
	}

	//フィニッシュ処理
	Finish();

	//ポーズのフラグが立っていたら
	if (m_bPause == true)
	{
		//フラグをおろす
		m_bPause = false;
	}

#ifdef _DEBUG
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
#endif // !_DEBUG
}

//================================================
//描画処理
//================================================
void CGame01::Draw(void)
{

}

//================================================
//カメラの処理
//================================================
void CGame01::Camera(void)
{
	//カメラのポインタ配列1番目のアドレス取得
	CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
	//cameraの取得
	CCamera* pCamera = &**pCameraAddress;

	//プレイヤーの跳ねる量によってカメラの位置と視野を変える
	if (m_pPlayer->GetBoundMove() > GAME01_CAMERA_VIEW_CHANGE_MOVE)
	{
		//既定の値よりも小さいとき
		if (pCamera->GetDiffer() < CAMERA_DISTANCE_MAX)
		{
			//カメラの視点と注視点の距離を広くする
			pCamera->AddDiffer(GAME01_CAMERA_ADD_DIFFER);
			//規定値よりも大きくなったら
			if (pCamera->GetDiffer() > CAMERA_DISTANCE_MAX)
			{
				//カメラの視点と注視点の距離を設定
				pCamera->SetDiffer(CAMERA_DISTANCE_MAX);
			}
		}

		//既定の値よりも小さいとき
		if (pCamera->GetPosR().y < CAMERA_MAX_POS.y)
		{
			//カメラの注視点の位置を取得
			D3DXVECTOR3 posR = pCamera->GetPosR();
			//注視点の位置を移動
			posR.y += GAME01_CAMERA_ADD_POS;
			//規定値よりも大きくなったら
			if (posR.y > CAMERA_MAX_POS.y)
			{
				//既定の値にする
				posR.y = CAMERA_MAX_POS.y;
			}
			//注視点の位置を設定
			pCamera->SetPosR(posR);
		}
	}
	else if (m_pPlayer->GetBoundMove() <= GAME01_CAMERA_VIEW_CHANGE_MOVE)
	{
		//既定の値よりも大きいとき
		if (pCamera->GetDiffer() > CAMERA_DISTANCE_DEFAULT)
		{
			//カメラの視点と注視点の距離を狭くする
			pCamera->AddDiffer(-GAME01_CAMERA_ADD_DIFFER);
			//規定値よりも小さくなったら
			if (pCamera->GetDiffer() < CAMERA_DISTANCE_DEFAULT)
			{
				//カメラの視点と注視点の距離を設定
				pCamera->SetDiffer(CAMERA_DISTANCE_DEFAULT);
			}
		}
		else if (pCamera->GetDiffer() < CAMERA_DISTANCE_DEFAULT)
		{//既定の値よりも小さいとき
		 //カメラの視点と注視点の距離を広くする
			pCamera->AddDiffer(GAME01_CAMERA_ADD_DIFFER);
			//規定値よりも大きくなったら
			if (pCamera->GetDiffer() > CAMERA_DISTANCE_DEFAULT)
			{
				//カメラの視点と注視点の距離を設定
				pCamera->SetDiffer(CAMERA_DISTANCE_DEFAULT);
			}
		}

		//既定の値よりも大きいとき
		if (pCamera->GetPosR().y > CAMERA_DEFAULT_POS.y)
		{
			//カメラの注視点の位置を取得
			D3DXVECTOR3 posR = pCamera->GetPosR();
			//注視点の位置を移動
			posR.y -= GAME01_CAMERA_ADD_POS;
			//規定値よりも小さくなったら
			if (posR.y < CAMERA_DEFAULT_POS.y)
			{
				//既定の値にする
				posR.y = CAMERA_DEFAULT_POS.y;
			}
			//注視点の位置を設定
			pCamera->SetPosR(posR);
		}
		else if (pCamera->GetPosR().y < CAMERA_DEFAULT_POS.y)
		{//既定の値よりも小さいとき
		 //カメラの注視点の位置を取得
			D3DXVECTOR3 posR = pCamera->GetPosR();
			//注視点の位置を移動
			posR.y += GAME01_CAMERA_ADD_POS;
			//規定値よりも大きくなったら
			if (posR.y > CAMERA_DEFAULT_POS.y)
			{
				//既定の値にする
				posR.y = CAMERA_DEFAULT_POS.y;
			}
			//注視点の位置を設定
			pCamera->SetPosR(posR);
		}
	}
}

//================================================
//道の処理
//================================================
void CGame01::Road(void)
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

		//雲の位置を取得
		D3DXVECTOR3 pos = m_pStart->GetModel()->GetPos();
		//位置を移動させる
		pos.x += -m_pPlayer->GetMoveForward();
		//位置設定
		m_pStart->GetModel()->SetPos(pos);
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
			m_apRoad[0]->DeleteRoad();
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

				m_pStart->Uninit();
				m_pStart = nullptr;
			}
		}
	}

	if (m_apRoad[0] != nullptr)
	{
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
}

//================================================
//ゲージ処理
//================================================
void CGame01::Gauge(void)
{
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();

	//ゲージを増やす
	m_pGauge->AddGauge(GAME01_SHOT_GAUGE_ADD);

	//ゲージが最大までたまったら
	if (m_pGauge->GetGauge() == m_pGauge->GetMaxNum())
	{
		//カウンターを加算
		m_nGaugeCounter++;
		//既定の値より大きくなったら
		if (m_nGaugeCounter > GAME01_SHOT_GAUGE_COUNTER_MAX)
		{
			//0にする
			m_nGaugeCounter = 0;
			//ゲージを0にする
			m_pGauge->SetGauge(0);
		}
	}
}

//================================================
//ゲージを消す処理
//================================================
void CGame01::UninitGauge(void)
{
	//ゲージとそのフレームの色取得
	D3DXCOLOR gaugeFrameCol = m_pGaugeFrame->GetCol();
	D3DXCOLOR gaugeCol = m_pGauge->GetCol();

	//ゲージとそのフレームを徐々に薄くする
	gaugeFrameCol.a -= GAME01_SHOT_GAUGE_SUBTRACT_ALPHA;
	gaugeCol.a -= GAME01_SHOT_GAUGE_SUBTRACT_ALPHA;

	//見えなくなったら
	if (gaugeFrameCol.a <= 0.0f || gaugeCol.a <= 0.0f)
	{
		//0にする
		gaugeFrameCol.a = 0.0f;
		gaugeCol.a = 0.0f;

		//消す
		m_pGaugeFrame->Uninit();
		m_pGauge->Uninit();

		m_pGaugeFrame = nullptr;
		m_pGauge = nullptr;
	}
	else
	{
		//色の設定
		m_pGaugeFrame->SetCol(gaugeFrameCol);
		m_pGauge->SetCol(gaugeCol);
	}
}

//================================================
//矢印を消す処理
//================================================
void CGame01::UninitArrow(void)
{
	//色取得
	D3DXCOLOR arrowCol = m_pArrow->GetCol();

	//徐々に薄くする
	arrowCol.a -= GAME01_ARROW_UI_SUBTRACT_ALPHA;

	//見えなくなったら
	if (arrowCol.a <= 0.0f)
	{
		//0にする
		arrowCol.a = 0.0f;

		//消す
		m_pArrow->Uninit();
		m_pArrow = nullptr;
	}
	else
	{
		//色の設定
		m_pArrow->SetCol(arrowCol);
	}
}

//================================================
//発射処理
//================================================
void CGame01::Shot(void)
{
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();
#ifdef _DEBUG
	if (m_pPlayer->GetShot() == true)
	{
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
			mousePosVec *= GAME01_MOUSE_VEC_ADJUSTMENT_DEBUG;

			//発射している状態にする
			m_pPlayer->SetShot(true);
			//ジャンプ量設定
			m_pPlayer->SetJump(mousePosVec.y);
			//前に進む力を設定
			m_pPlayer->SetMoveForward(mousePosVec.x);
			//バウンドする瞬間の移動量に設定
			m_pPlayer->SetBoundMove(mousePosVec.y);
		}
	}
#endif // !_DEBUG

	if (m_pPlayer->GetShot() == false && m_bReleaseMouse == false)
	{//発射していない状態なら
		//マウス取得処理
		CInputMouse *pInputMouse;
		pInputMouse = CManager::GetInstance()->GetInputMouse();

		//マウスを押した瞬間
		if (pInputMouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			sound->Play(CSound::SOUND_LABEL::GAGE_SE);
			sound->ControllVoice(CSound::SOUND_LABEL::GAGE_SE, 1.4f);

			//マウスの位置取得
			POINT mouseTriggerPos;
			GetCursorPos(&mouseTriggerPos);
			ScreenToClient(CManager::GetWindowHandle(), &mouseTriggerPos);

			//マウスの位置を保存
			m_mouseTriggerPos.x = (float)mouseTriggerPos.x;
			m_mouseTriggerPos.y = (float)mouseTriggerPos.y;

			//矢印UIを生成
			m_pArrow = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f),
				                         static_cast<int>(CObject::PRIORITY::UI));
			m_pArrow->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("arrow02.png"));

			m_pGaugeFrame->SetPriority(static_cast<int>(CObject::PRIORITY::UI));
			m_pGauge->SetPriority(static_cast<int>(CObject::PRIORITY::UI));
		}

		//矢印が生成されていたら
		if (m_pArrow != nullptr)
		{
			//マウスの位置取得
			POINT mousePos;
			GetCursorPos(&mousePos);
			ScreenToClient(CManager::GetWindowHandle(), &mousePos);

			//サイズを取得
			D3DXVECTOR3 size = D3DXVECTOR3(200.0f, 200.0f, 0.0f);

			//マウスをクリックした場所から現在の場所の距離を求める
			D3DXVECTOR2 differ = D3DXVECTOR3(mousePos.x - m_mouseTriggerPos.x, mousePos.y - m_mouseTriggerPos.y, 0.0f);

			//サイズXを距離によって増減させる
			size.x += sqrtf(differ.x * differ.x + differ.y * differ.y);

			//既定の値以下になったら
			if (size.x <= 100.0f)
			{
				//既定の値にする
				size.x = 100.0f;
			}

			//マウスをクリックした場所から離した場所の角度を算出
			float fRot = atan2f(differ.y, differ.x);

			//押した瞬間の時
			if (differ.y == 0.0f && differ.x == 0.0f)
			{
				fRot = D3DX_PI;
			}

			//角度によって矢印を回転させる
			m_pArrow->SetPos(m_pArrow->GetPos(), size, -fRot + D3DX_PI);
		}



		//マウスを離した瞬間且つ矢印が生成されていたら
		if (pInputMouse->GetRelease(CInputMouse::MOUSE_TYPE_LEFT) == true && m_pArrow!= nullptr)
		{
			sound->Stop(CSound::SOUND_LABEL::GAGE_SE);
			//マウスを離した状態のフラグを立てる
			m_bReleaseMouse = true;

			//マウスの位置取得
			POINT mouseReleasePos;
			GetCursorPos(&mouseReleasePos);
			ScreenToClient(CManager::GetWindowHandle(), &mouseReleasePos);

			//マウスをクリックした場所から離した場所の角度を算出
			float fRot = atan2f(m_mouseTriggerPos.y - mouseReleasePos.y, m_mouseTriggerPos.x - mouseReleasePos.x);
			//プレイヤーの移動ベクトルを求める
			m_shotMoveVec = D3DXVECTOR3(cosf(fRot) * PLAYER_SHOT_MOVE, sinf(fRot) * PLAYER_SHOT_MOVE, 0.0f);
			//ベクトルのyを逆向きにする
			m_shotMoveVec.y *= -1.0f;

			float fmoseVecAdjustment = 0.0f;

			//UIの生成
			m_pShotUi = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, GAME01_SHOT_JUDGE_UI_POS_Y, 0.0f),
				                          D3DXVECTOR3(GAME01_SHOT_JUDGE_UI_SIZE_X, GAME01_SHOT_JUDGE_UI_SIZE_Y, 0.0f),
				                          static_cast<int>(CObject::PRIORITY::UI));

			//ゲージの量によってベクトルを小さくする割合を変える
			if (m_pGauge->GetGauge() == 0)
			{//0の時
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_0;
				m_pShotUi->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("bad.png"));
				sound->ControllVoice(CSound::SOUND_LABEL::BAD_SE, 1.2f);
				sound->Play(CSound::SOUND_LABEL::BAD_SE);
			}
			else if (m_pGauge->GetGauge() > 0 && m_pGauge->GetGauge() <= GAME01_SHOT_GAUGE_CASE_1)
			{//0より大きくて既定の値以下の時
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_1;
				m_pShotUi->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("bad.png"));
				sound->ControllVoice(CSound::SOUND_LABEL::BAD_SE, 1.2f);
				sound->Play(CSound::SOUND_LABEL::BAD_SE);
			}
			else if (m_pGauge->GetGauge() > GAME01_SHOT_GAUGE_CASE_1 && m_pGauge->GetGauge() <= GAME01_SHOT_GAUGE_CASE_2)
			{//既定の値より大きくて既定の値以下の時
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_2;
				m_pShotUi->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("bad.png"));
				sound->ControllVoice(CSound::SOUND_LABEL::BAD_SE, 1.2f);
				sound->Play(CSound::SOUND_LABEL::BAD_SE);
			}
			else if (m_pGauge->GetGauge() > GAME01_SHOT_GAUGE_CASE_2 && m_pGauge->GetGauge() <= GAME01_SHOT_GAUGE_CASE_3)
			{//既定の値より大きくて既定の値以下の時
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_3;
				m_pShotUi->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("good.png"));
				sound->ControllVoice(CSound::SOUND_LABEL::GOOD_SE, 1.2f);
				sound->Play(CSound::SOUND_LABEL::GOOD_SE);
			}
			else if (m_pGauge->GetGauge() > GAME01_SHOT_GAUGE_CASE_3 && m_pGauge->GetGauge() <= GAME01_SHOT_GAUGE_CASE_4)
			{//既定の値より大きくて既定の値以下の時
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_4;
				m_pShotUi->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("good.png"));
				sound->ControllVoice(CSound::SOUND_LABEL::GOOD_SE, 1.2f);
				sound->Play(CSound::SOUND_LABEL::GOOD_SE);
			}
			else if (m_pGauge->GetGauge() > GAME01_SHOT_GAUGE_CASE_4 && m_pGauge->GetGauge() < m_pGauge->GetMaxNum())
			{//既定の値より大きくて最大より小さいの時
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_5;
				m_pShotUi->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("great.png"));
				sound->ControllVoice(CSound::SOUND_LABEL::GREAT_SE, 1.2f);
				sound->Play(CSound::SOUND_LABEL::GREAT_SE);
			}
			else if (m_pGauge->GetGauge() == m_pGauge->GetMaxNum())
			{//最大値の時
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_6;
				m_pShotUi->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("perfect.png"));
				sound->ControllVoice(CSound::SOUND_LABEL::PARFECT_SE, 1.2f);
				sound->Play(CSound::SOUND_LABEL::PARFECT_SE);
			}

			//ベクトルを既定の割合小さくする
			m_shotMoveVec *= fmoseVecAdjustment;
		}
	}
	else if (m_bReleaseMouse == true && m_pShotUi != nullptr)
	{//マウスを離した状態且つ発射用UIが消えていなかったら
		//発射UI処理
		ShotUi();
	}
}

//================================================
//発射UI処理
//================================================
void CGame01::ShotUi(void)
{
	//カウンターを加算
	m_nShotUiCounter++;

	//サイズを取得
	D3DXVECTOR3 size = m_pShotUi->GetSize();
	//位置を取得
	D3DXVECTOR3 pos = m_pShotUi->GetPos();

	//既定の値より大きくなったら
	if (m_nShotUiCounter > GAME01_SHOT_UI_UNINIT_COUNTER)
	{
		//色を取得
		D3DXCOLOR col = m_pShotUi->GetCol();
		//薄くする
		col.a -= GAME01_SHOT_UI_SUBTRACT_ALPHA;
		//見えなくなったら
		if (col.a <= 0.0f)
		{
			//発射している状態にする
			m_pPlayer->SetShot(true);

			//前に進む力がマイナスの場合はジャンプしないようにする
			if (m_shotMoveVec.x < 0.0f)
			{
				m_shotMoveVec.y = 0.0f;
			}
			//ジャンプ量設定
			m_pPlayer->SetJump(m_shotMoveVec.y);
			//前に進む力を設定
			m_pPlayer->SetMoveForward(m_shotMoveVec.x);

			if (m_pShotUi != nullptr)
			{
				//消す
				m_pShotUi->Uninit();
				m_pShotUi = nullptr;
				return;
			}
		}
		else
		{
			//色を設定
			m_pShotUi->SetCol(col);
		}
		
		//位置Yを既定の値動かす
		pos.y += GAME01_SHOT_UI_MOVE_Y;
	}
	else if(m_nShotUiCounter <= GAME01_SHOT_UI_ADD_SIZE_COUNTER)
	{
		//サイズを既定の割合ずつ大きくする
		size *= GAME01_SHOT_UI_ADD_SIZE;

	}
	else if (m_nShotUiCounter > GAME01_SHOT_UI_ADD_SIZE_COUNTER && m_nShotUiCounter <= GAME01_SHOT_UI_SUBTRACT_SIZE_COUNTER)
	{
		//サイズを既定の割合ずつ小さくする
		size *= GAME01_SHOT_UI_SUBTRACT_SIZE;
	}

	//位置とサイズを設定
	m_pShotUi->SetPos(pos, size);
}

//================================================
//ロケットの処理
//================================================
void CGame01::Rocket(void)
{
	//ロケットが消えていなかったら
	if (m_pRocket != nullptr)
	{
		//床が消えてなかったら且つプレイヤーと当たっていなかったら
		if (m_pFloor != nullptr && m_pRocket->GetHitPlayer() == false)
		{
			//位置を取得
			D3DXVECTOR3 rocketPos = m_pRocket->GetModel()->GetModel()->GetPos();
			//位置Xを移動させる
			rocketPos.x += -m_pPlayer->GetMoveForward();
			//位置設定
			m_pRocket->GetModel()->GetModel()->SetPos(rocketPos);
		}
		else if (m_pFloor == nullptr)
		{//床が消えてたら
			//ロケットを消す
			m_pRocket->Uninit();
			m_pRocket = nullptr;
		}
	}
}

//================================================
//ゲーム終了処理
//================================================
void CGame01::Finish(void)
{
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();

	//終了したら
	if (m_bFinish == true)
	{
		if (m_nFinishCounter == 0)
		{
			CObject2D *pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
				                                     D3DXVECTOR3(600.0f, 100.0f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
			pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("finish.png"));
			sound->Play(CSound::SOUND_LABEL::GOAL_SE);
			sound->ControllVoice(CSound::SOUND_LABEL::GOAL_SE, 1.4f);
		}
		else if (m_nFinishCounter > GAME01_FINISH_COUNTER)
		{
			//フェード取得処理
			CFade *pFade;
			pFade = CManager::GetInstance()->GetFade();

			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				pFade->SetFade(CManager::MODE::RESULT);
			}
		}
		//カウンターを増やす
		m_nFinishCounter++;
	}
}

//================================================
//トロフィーの飛距離のフラグ処理
//================================================
void CGame01::FlyingDistanceFlag(void)
{
	//スコアの取得
	int nScore = CManager::GetInstance()->GetPlayData()->GetScore();

	//トロフィーのフラグ状態を取得
	vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();

	if (nScore >= GAME01_FLYING_DISTANCE_1000)
	{
		//トロフィーを取得したことがなかったら
		if (flag[(int)CTrophy::TROPHY::M_1000] == false)
		{
			//取得させる
			flag[(int)CTrophy::TROPHY::M_1000] = true;
			//フラグを立てる
			CManager::GetInstance()->GetPlayData()->SetFlag(flag);
		}

		if (nScore >= GAME01_FLYING_DISTANCE_5000)
		{
			//トロフィーを取得したことがなかったら
			if (flag[(int)CTrophy::TROPHY::M_5000] == false)
			{
				//取得させる
				flag[(int)CTrophy::TROPHY::M_5000] = true;
				//フラグを立てる
				CManager::GetInstance()->GetPlayData()->SetFlag(flag);
			}

			if (nScore >= GAME01_FLYING_DISTANCE_10000)
			{
				//トロフィーを取得したことがなかったら
				if (flag[(int)CTrophy::TROPHY::M_10000] == false)
				{
					//取得させる
					flag[(int)CTrophy::TROPHY::M_10000] = true;
					//フラグを立てる
					CManager::GetInstance()->GetPlayData()->SetFlag(flag);
				}
			}
		}
	}
}
