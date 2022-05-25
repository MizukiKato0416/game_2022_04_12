//================================================
//プレイヤー処理
//Author:加藤瑞葵
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_d.h"
#include "input_mouse.h"
#include "player.h"
#include "motion_player.h"
#include "renderer.h"
#include "model.h"
#include "x_load.h"
#include "floor.h"
#include "model_single.h"
#include "texture.h"
#include "camera.h"
#include "play_data.h"
#include "meshfield.h"
#include "billboard.h"
#include "ui.h"
#include "shadow.h"
#include "sparkle.h"
#include "wind.h"
#include "game01.h"
#include "happening.h"
#include "sound.h"
#include "trophy.h"

//================================================
//マクロ定義
//================================================
#define PLAYER_JUMP							(12.0f)		//ジャンプ力
#define PLAYER_JUMP_BALANCE_BALL			(12.0f)		//バランスボールのジャンプ力
#define PLAYER_JUMP_GIRL					(17.0f)		//ロキコちゃんのジャンプ力
#define PLAYER_JUMP_MIN						(5.0f)		//ジャンプ力最小値
#define PLAYER_JUMP_MAX						(30.0f)		//ジャンプ力最大値
#define PLAYER_BOUND						(0.8f)		//バウンド力
#define PLAYER_MOVE_FORWARD_TRAMPOLINE		(15.0f)		//トランポリンの前に進む力
#define PLAYER_MOVE_FORWARD_GIRL			(30.0f)		//ロキコちゃんの前に進む力
#define PLAYER_MOVE_FORWARD_SUBTRACTION		(0.985f)	//前に進む力の減算量
#define PLAYER_MOVE_FORWARD_MIN				(4.0f)		//前に進む力の最小値
#define PLAYER_MOVE_FORWARD_MIN_NOT_JUMP	(1.5f)		//ジャンプしていないときの前に進む力の最小値
#define PLAYER_MOVE_FORWARD_MAX				(40.0f)		//前に進む力の最大値
#define PLAYER_GRAVITY						(0.4f)		//重力の大きさ
#define PLAYER_MOVE_SPEED					(4.0f)		//通常移動の移動量
#define PLAYER_SIZE							(10.0f)		//プレイヤーのサイズ調整値
#define PLAYER_SPARKLE_NUM					(3)			//軌道エフェクトの数

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CPlayer::CPlayer(CObject::PRIORITY Priority):CObject(Priority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_offsetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = nullptr;
	memset(&m_apModel, NULL, sizeof(m_apModel));
	m_pMotionPlayer = nullptr;
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_bShot = false;
	m_fJump = 0.0f;
	m_fMoveForward = 0.0f;
	m_fBoundMove = 0.0f;
	m_fRotSpeed = 0.0f;
	m_pSparkle = nullptr;
	m_bObjParent = false;
	m_bSparkle = false;
	m_state = PLAYER_STATE::NONE;
	m_nStateCounter = 0;
	m_pWind = nullptr;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CPlayer::~CPlayer()
{

}

//================================================
//初期化処理
//================================================
HRESULT CPlayer::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_offsetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_bShot = false;
	m_fJump = 0.0f;
	m_fMoveForward = 0.0f;
	m_fBoundMove = 0.0f;
	m_pSparkle = nullptr;
	m_bObjParent = false;
	m_bSparkle = true;
	m_fRotSpeed = PLAYER_ROTATE;
	m_state = PLAYER_STATE::NORMAL;
	m_nStateCounter = 0;
	m_pWind = nullptr;

	//モデルの生成
	//textファイル読み込み
	FILE *pFile = fopen("data/MOTION/motion_player.txt", "r");
	if (pFile != nullptr)
	{
		char cString[128];
		//一行ずつ保存
		while (fgets(cString, 128, pFile) != NULL)
		{
			//文字列を保存
			fscanf(pFile, "%s", cString);
			//文字列の中にPARTSSETがあったら
			if (strncmp("PARTSSET", cString, 9) == 0)
			{
				//インデックス読み込み
				int nIndex = 0;
				fscanf(pFile, "%*s%*s%d", &nIndex);
				fscanf(pFile, "%*s%*s");

				//親読み込み
				int nParent = 0;
				fscanf(pFile, "%*s%*s%d", &nParent);
				fscanf(pFile, "%*s%*s");

				//位置読み込み
				D3DXVECTOR3 modelPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				fscanf(pFile, "%*s%*s%f%f%f", &modelPos.x, &modelPos.y, &modelPos.z);

				//向き読み込み
				D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				fscanf(pFile, "%*s%*s%f%f%f", &rot.x, &rot.y, &rot.z);

				//モデル生成
				int nModelType = 0;

				//合言葉取得
				if (strncmp("695", CManager::GetInstance()->GetPlayData()->GetPasword().c_str(), 4) == 0)
				{
					//トロフィーのフラグ状態を取得
					vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
					//トロフィーを取得したことがなかったら
					if (flag[(int)CTrophy::TROPHY::GIRL] == false)
					{
						//取得させる
						flag[(int)CTrophy::TROPHY::GIRL] = true;

						CManager::GetInstance()->GetPlayData()->SetFlag(flag);
					}
					nModelType = CXload::X_TYPE_PLAYER_GIRL_BODY;
				}
				else
				{
					nModelType = CXload::X_TYPE_PLAYER_BODY;
				}
				
				m_apModel[nIndex] = CModel::Create(modelPos, rot, CManager::GetInstance()->GetXload()->GetType(nModelType + nIndex));


				//親の設定
				if (nParent == -1)
				{
					m_apModel[nIndex]->SetParent(nullptr);
				}
				else
				{
					m_apModel[nIndex]->SetParent(m_apModel[nParent]);
				}

				if (nIndex == MAX_PLAYER_MODEL - 1)
				{
					break;
				}
			}
		}
	}
	else
	{
		printf("ファイルが開けませんでした\n");
	}
	fclose(pFile);

	//位置の設定
	SetPos(m_pos);
	SetPosOld(m_posOld);

	//オブジェクトの種類の設定
	SetObjType(CObject::OBJTYPE::PLAYER);

	//モーションの生成
	m_pMotionPlayer = CMotionPlayer::Create(this);
	m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL, this);

	//サイズを取得
	D3DXVECTOR3 modelSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelSize = m_apModel[0]->GetSize();

	//サイズのXとZを比べて大きいほうをXとZそれぞれに割り当てる
	if (modelSize.x >= modelSize.z)
	{
		m_size = D3DXVECTOR3(modelSize.x + PLAYER_SIZE, modelSize.y, modelSize.x + PLAYER_SIZE);
	}
	else
	{
		m_size = D3DXVECTOR3(modelSize.z + PLAYER_SIZE, modelSize.y, modelSize.z + PLAYER_SIZE);
	}

	//サイズの設定
	SetSize(m_size);

	//影の設定
	CShadow::Create(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z), D3DXVECTOR3(m_size.x, 0.0f, m_size.z), this);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CPlayer::Uninit(void)
{
	Release();
}

//================================================
//更新処理
//================================================
void CPlayer::Update(void)
{
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();
	//位置取得
	D3DXVECTOR3 pos = GetPos();

	m_pos = pos;
	m_posOld = pos;

	//1フレーム前の位置設定
	SetPosOld(m_posOld);

	//重力
	m_move.y -= PLAYER_GRAVITY;

	m_pos += m_move;		//移動量反映

	//回転の慣性
	Rotate();

	//モーション
	m_pMotionPlayer->Update(this);

	//位置反映
	SetPos(m_pos);

	//状態による処理分け
	State();

	//発射している状態なら
	if (m_bShot == true)
	{
		//ジャンプ力が既定の値以下になったとき
		if (m_fJump <= PLAYER_JUMP)
		{
			//前に進む力を少なくする
			m_fMoveForward *= PLAYER_MOVE_FORWARD_SUBTRACTION;
		}
		
		//前に進む力が正の数で既定の値より小さくなったら
		if (m_fMoveForward < PLAYER_MOVE_FORWARD_MIN && m_fMoveForward > 0.0f)
		{
			//まだジャンプしている状態なら
			if (m_fJump > 0.0f)
			{
				//少しだけ前に動かす
				m_fMoveForward = PLAYER_MOVE_FORWARD_MIN;
			}
			else
			{
				//前に進む力が既定の値より小さくなったら
				if (m_fMoveForward < PLAYER_MOVE_FORWARD_MIN_NOT_JUMP)
				{
					//0にする
					m_fMoveForward = 0.0f;

					//モーションが着地ではなかったら
					if (m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_DIVE_LAND)
					{
						//着地モーションにする
						m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_DIVE_LAND, this);
					}
				}
			}
		}
		else if (m_fMoveForward > -PLAYER_MOVE_FORWARD_MIN && m_fMoveForward < 0.0f)
		{//前に進む力が正の数で既定の値より大きくなったら
		 //まだジャンプしている状態なら
			if (m_fJump > 0.0f)
			{
				//少しだけ後ろに動かす
				m_fMoveForward = -PLAYER_MOVE_FORWARD_MIN;
			}
			else
			{
				//前に進む力が既定の値より大きくなったら
				if (m_fMoveForward > -PLAYER_MOVE_FORWARD_MIN_NOT_JUMP)
				{
					//0にする
					m_fMoveForward = 0.0f;

					//モーションが着地ではなかったら
					if (m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_DIVE_LAND)
					{
						//着地モーションにする
						m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_DIVE_LAND, this);
					}
				}
			}
		}

		//止まっていなかったら
		if (m_fMoveForward != 0.0f)
		{
			//ジャンプ力が0より大きかったら
			if (m_fJump > 0.0f)
			{
				//プレイヤーを回転させる
				m_rot.x += m_fRotSpeed;
			}
			else
			{
				//回転値が0じゃなかったら
				if (m_rot.x != 0.0f)
				{
					//回転値を0にする
					m_rot.x = 0.0f;
				}

				//モーションがダイブではなかったら
				if (m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_DIVE)
				{
					if (strncmp("KIYO", CManager::GetInstance()->GetPlayData()->GetPasword().c_str(), 5) == 0)
					{
						vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
						if (flag[(int)CTrophy::TROPHY::KIYO] == false)
						{
							flag[(int)CTrophy::TROPHY::KIYO] = true;

							CManager::GetInstance()->GetPlayData()->SetFlag(flag);
						}
						sound->ControllVoice(CSound::SOUND_LABEL::KIYO_BREAK_SE, 0.8f);
						sound->Play(CSound::SOUND_LABEL::KIYO_BREAK_SE);
					}
					else
					{
						sound->ControllVoice(CSound::SOUND_LABEL::BREAK_SE, 1.4f);
						sound->Play(CSound::SOUND_LABEL::BREAK_SE);
					}

					//着地モーションにする
					m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_DIVE, this);
				}
			}

			//軌道エフェクトを出す状態なら
			if (m_bSparkle == true)
			{
				//軌道エフェクトの生成
				m_pSparkle = CSparkle::Create(m_pos, D3DXVECTOR3(SPARKLE_SIZE_RAND, SPARKLE_SIZE_RAND, 0.0f), D3DXVECTOR3(-m_fMoveForward, 0.0f, 0.0f),
				                              PLAYER_SPARKLE_NUM);
				m_pSparkle->SetMove(D3DXVECTOR3(-m_fMoveForward, 0.0f, 0.0f));
			}
		}
		else
		{//止まっていたら
			//ジャンプ力が0で物に当たっていないとき
			if (m_fJump == 0.0f && CHappenig::GetHit() == false)
			{
				//ゲームシーンなら
				if (CManager::GetInstance()->GetMode() == CManager::MODE::GAME01)
				{
					//終了状態でないなら
					if (CManager::GetInstance()->GetGame01()->GetFinish() == false)
					{
						//終了状態に設定する
						CManager::GetInstance()->GetGame01()->SetFinish(true);
					}
				}
			}
		}
	}

	//床との当たり判定
	if (CFloor::Collision(this) == true)
	{
		//重力を0にする
		m_move.y = 0.0f;
		//発射している状態なら
		if (m_bShot == true)
		{
			//ジャンプ力を小さくする
			m_fJump *= PLAYER_BOUND;
			//ジャンプ力が既定の値より小さくなったら
			if (m_fJump < PLAYER_JUMP_MIN)
			{
				m_fJump = 0.0f;
			}
			//バウンドさせる
			m_move.y = m_fJump;

			if (m_fJump > 0.0f)
			{
				sound->ControllVoice(CSound::SOUND_LABEL::JUMP_SE, 1.4f);
				sound->Play(CSound::SOUND_LABEL::JUMP_SE);
			}

			//バウンドする瞬間の移動量を設定
			m_fBoundMove = m_move.y;
		}
	}

	//位置取得
	pos = GetPos();
	m_pos = pos;
}

//================================================
//描画処理
//================================================
void CPlayer::Draw(void)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;			//計算用マトリックス

	D3DXMatrixIdentity(&m_mtxWorld);		//プレイヤーのワールドマトリックスの初期化

	D3DXVECTOR3 pos, rot;

	//親子関係がつけられていたら
	if (m_bObjParent == true)
	{
		pos = m_offsetPos;
		rot = m_rot;
	}
	else
	{//つけられていなかったら
		pos = m_pos;
		rot = m_rot;
	}

	//プレイヤーの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//プレイヤーの位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_bObjParent == true)
	{
		D3DXMATRIX mtxParent = *m_mtxWorldParent;

		//算出したパーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);
	}

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//モデルの描画
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		m_apModel[nCntModel]->Draw();
	}
}

//================================================
//生成処理
//================================================
CPlayer *CPlayer::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	//インスタンスの生成
	CPlayer *pPlayer = nullptr;
	if (pPlayer == nullptr)
	{
		pPlayer = new CPlayer;
		if (pPlayer != nullptr)
		{
			pPlayer->m_pos = pos;
			pPlayer->m_posOld = pos;
			pPlayer->m_rot = rot;
			pPlayer->Init();
		}
	}
	return pPlayer;
}

//================================================
//モデルの位置設定処理
//================================================
void CPlayer::SetModelPos(const int &nCntModel, const D3DXVECTOR3 &pos)
{
	m_apModel[nCntModel]->SetPos(pos);
}

//================================================
//モデルの位置取得処理
//================================================
D3DXVECTOR3 CPlayer::GetModelPos(const int &nCntModel)
{
	return m_apModel[nCntModel]->GetPos();
}

//================================================
//モデルの向き設定処理
//================================================
void CPlayer::SetModelRot(const int &nCntModel, const D3DXVECTOR3 &rot)
{
	m_apModel[nCntModel]->SetRot(rot);
}

//================================================
//モデルの向き取得処理
//================================================
D3DXVECTOR3 CPlayer::GetModelRot(const int &nCntModel)
{
	return m_apModel[nCntModel]->GetRot();
}

//================================================
//モデルの動き処理
//================================================
void CPlayer::Move(void)
{
	//パッドD取得処理
	CInputPadD *pInputPadD = CManager::GetInstance()->GetInputPadD();
	DIJOYSTATE2 JoyStick = pInputPadD->GetGamepad();

	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//パッドX取得処理
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInstance()->GetInputPadX();

	D3DXVECTOR3 rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//cameraのポインタ配列1番目のアドレス取得
	CCamera **pCameraAddress = CManager::GetInstance()->GetCamera();

	for (int nCntCamera = 0; nCntCamera < MAX_MAIN_CAMERA; nCntCamera++, pCameraAddress++)
	{
		//cameraの取得
		CCamera *pCamera = &**pCameraAddress;
		if (pCamera != nullptr)
		{
			//cameraの向き取得
			rotCamera = pCamera->GetRotV();
		}
	}

	//移動量設定用変数
	float fSpeed = PLAYER_MOVE_SPEED;

	//スティックの傾きがあったらまたはWASDを押したら
	if ((float)JoyStick.lX != 0.0f || (float)JoyStick.lY != 0.0f || 
		pInputKeyboard->GetPress(DIK_W) == true || pInputKeyboard->GetPress(DIK_A) == true ||
		pInputKeyboard->GetPress(DIK_S) == true || pInputKeyboard->GetPress(DIK_D) == true)
	{
		//目的の向きを設定
		if ((float)JoyStick.lX != 0.0f || (float)JoyStick.lY != 0.0f)
		{
			m_fObjectiveRot = rotCamera.y + atan2f((float)JoyStick.lY, (float)JoyStick.lX) + D3DX_PI / 2.0f;
		}
		else if (pInputKeyboard->GetPress(DIK_W) == true)
		{
			if (pInputKeyboard->GetPress(DIK_A) == true)
			{
				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y - D3DX_PI / 4.0f;
			}
			else if (pInputKeyboard->GetPress(DIK_D) == true)
			{
				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y + D3DX_PI / 4.0f;
			}
			else
			{
				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{
			if (pInputKeyboard->GetPress(DIK_A) == true)
			{
				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y - D3DX_PI / 4.0f * 3.0f;
			}
			else if (pInputKeyboard->GetPress(DIK_D) == true)
			{
				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y + D3DX_PI / 4.0f * 3.0f;
			}
			else
			{
				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y + D3DX_PI;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			//目的の向きを設定
			m_fObjectiveRot = rotCamera.y - D3DX_PI / 2.0f;
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			//目的の向きを設定
			m_fObjectiveRot = rotCamera.y + D3DX_PI / 2.0f;
		}

		//移動量加算
		m_move.x = sinf(m_fObjectiveRot + D3DX_PI) * fSpeed;
		m_move.z = cosf(m_fObjectiveRot + D3DX_PI) * fSpeed;
		//回転をさせる
		m_bRotate = true;

		if (m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_MOVE)		//移動モーションでない
		{
			//移動モーションにする
			m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_MOVE, this);
		}
	}
	else
	{//スティックに傾きがなかったら

		//移動量をゼロにする
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		//移動モーションだったら
		if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MOVE)
		{
			//ニュートラルモーションにする
			m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL, this);
		}
	}
}

//================================================
//回転処理
//================================================
void CPlayer::Rotate(void)
{
	//回転させる状態なら
	if (m_bRotate == true)
	{
		//目的の向きを計算
		if (m_fObjectiveRot > D3DX_PI)
		{
			m_fObjectiveRot = -D3DX_PI - (D3DX_PI - m_fObjectiveRot);
		}
		else if (m_fObjectiveRot < -D3DX_PI)
		{
			m_fObjectiveRot = D3DX_PI - (-D3DX_PI - m_fObjectiveRot);
		}

		//プレイヤーの現在の向きごとにそれぞれ向きを変える量を計算
		if (m_rot.y < 0.0f && -m_rot.y + m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (-D3DX_PI - m_rot.y) + -(D3DX_PI - m_fObjectiveRot);
		}
		else if (m_rot.y >= D3DX_PI / 2.0f && m_rot.y - m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (D3DX_PI - m_rot.y) - (-D3DX_PI - m_fObjectiveRot);
		}
		else
		{
			m_fNumRot = (m_fObjectiveRot - m_rot.y);
		}

		//プレイヤーの向きに加算
		m_rot.y += m_fNumRot * 0.2f;

		//既定の値に達したら回転をやめる
		if (m_rot.y - m_fObjectiveRot < 0.001f && m_rot.y - m_fObjectiveRot > -0.001f)
		{
			m_bRotate = false;
		}
	}

	//πより大きくなったら-2πする
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{	//-πより小さくなったら+2πする
		m_rot.y += D3DX_PI * 2.0f;
	}
}

//================================================
//状態処理
//================================================
void CPlayer::State(void)
{
	switch (m_state)
	{
	case CPlayer::PLAYER_STATE::NORMAL:
		break;
	case CPlayer::PLAYER_STATE::WIND:
		//カウンターを増やす
		m_nStateCounter++;

		//既定の値より大きくなったら
		if (m_nStateCounter > 120)
		{
			//0にする
			m_nStateCounter = 0;
			//状態を通常にする
			m_state = PLAYER_STATE::NORMAL;

			//風エフェクトが生成されていたら
			if (m_pWind != nullptr)
			{
				//消す
				m_pWind->Uninit();
				m_pWind = nullptr;
				break;
			}
		}
		else
		{
			//風エフェクトが生成されていなかったら
			if (m_pWind == nullptr)
			{
				m_pWind = CWind::Create(m_pos, D3DXVECTOR3(100.0f, 200.0f, 0.0f), 0);
			}

			//位置を取得
			D3DXVECTOR3 pos = m_pWind->GetPos();
			//位置をプレイヤーと同じにする
			pos = m_pos;
			//位置を設定
			m_pWind->SetPos(pos, m_pWind->GetSize());
		}
		break;
	case CPlayer::PLAYER_STATE::WING:
		break;
	case CPlayer::PLAYER_STATE::MAX:
		break;
	default:
		break;
	}
}

//================================================
//プレイヤーとの当たり判定
//================================================
void CPlayer::Collision(CObject *&pSubjectObject, const float &fObjRadius)
{
	//オブジェクト情報を入れるポインタ
	vector<CObject*> object;

	//先頭のポインタを代入
	object = CObject::GetObject(static_cast<int>(CObject::PRIORITY::PLAYER));
	int nProprty_Size = object.size();

	for (int nCnt = 0; nCnt < nProprty_Size; nCnt++)
	{
		//オブジェクトの種類がプレイヤーだったら
		if (object[nCnt]->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//プレイヤーにキャスト
			CPlayer *pPlayerObj = nullptr;
			pPlayerObj = (CPlayer*)object[nCnt];

			//オブジェクトの位置を取得
			D3DXVECTOR3 posObj = pSubjectObject->GetPos();

			//プレイヤーから対象のオブジェクトまでの距離を求める
			float fRadius = sqrtf((posObj.x - pPlayerObj->m_pos.x) * (posObj.x - pPlayerObj->m_pos.x) +
				(posObj.z - pPlayerObj->m_pos.z) * (posObj.z - pPlayerObj->m_pos.z));
			//プレイヤーと対象のオブジェクトの角度を求める
			float fRot = atan2((posObj.x - pPlayerObj->m_pos.x), (posObj.z - pPlayerObj->m_pos.z)) - D3DX_PI;

			//求めた距離がプレイヤーの半径と対象のオブジェクトの半径を足した数値以下だったら
			if (fRadius <= pPlayerObj->m_size.x / 2.0f + fObjRadius)
			{
				//プレイヤーの位置を押し出す
				pPlayerObj->m_pos.x = posObj.x + (sinf(fRot) * (pPlayerObj->m_size.x / 2.0f + fObjRadius));
				pPlayerObj->m_pos.z = posObj.z + (cosf(fRot) * (pPlayerObj->m_size.x / 2.0f + fObjRadius));

				//位置設定
				pPlayerObj->SetPos(pPlayerObj->m_pos);

				//モデルとの当たり判定
				CModelSingle::Collision(pPlayerObj);
			}
		}
	}
}

//================================================
//プレイヤーとの衝突判定のみの処理
//================================================
bool CPlayer::CollisionOnly(CObject *&pSubjectObject, const float &fObjRadius)
{
	//オブジェクトの位置を取得
	D3DXVECTOR3 posObj = pSubjectObject->GetPos();

	//プレイヤーから対象のオブジェクトまでの距離を求める
	float fRadius = sqrtf((posObj.x - m_pos.x) * (posObj.x - m_pos.x) +
		(posObj.z - m_pos.z) * (posObj.z - m_pos.z));

	//求めた距離がプレイヤーの半径と対象のオブジェクトの半径を足した数値以下だったら
	if (fRadius <= m_size.x / 2.0f + fObjRadius)
	{
		//当たっている
		return true;
	}

	return false;
}

//================================================
//前に進む力設定処理
//================================================
void CPlayer::SetMoveForward(const float & fMoveForward)
{
	m_fMoveForward = fMoveForward;
	//前に進む力が既定の値より大きくなったら
	if (m_fMoveForward >= PLAYER_MOVE_FORWARD_MAX)
	{
		//最大値にする
		m_fMoveForward = PLAYER_MOVE_FORWARD_MAX;
	}
}

//================================================
//ジャンプ力設定処理
//================================================
void CPlayer::SetJump(const float & fJump)
{
	m_fJump = fJump;
	//ジャンプ量が既定の値より大きくなったら
	if (m_fJump > PLAYER_JUMP_MAX)
	{
		//最大値に設定する
		m_fJump = PLAYER_JUMP_MAX;
	}
}
