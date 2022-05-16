//================================================
//飛行機の処理
//Author:KatoMizuki
//================================================
#include "airplane.h"
#include "model_single.h"
#include "model.h"
#include "player.h"
#include "smoke.h"
#include "play_data.h"
#include "manager.h"
#include "trophy.h"

//================================================
//マクロ定義
//================================================
#define AIRPLANE_MOVE_COUNT				(180)								//前に進む時間
#define AIRPLANE_MOVE_FORWARD			(30.0f)								//前に進む力
#define AIRPLANE_PLAYER_MOVE_FORWARD	(20.0f)								//プレイヤーの前に進む力
#define AIRPLANE_PLAYER_JUMP			(20.0f)								//ジャンプ力
#define AIRPLANE_MOVE					(10.0f)								//飛行機が飛んでいくときの移動量
#define AIRPLANE_UNINIT_POS				(1000.0f)							//飛行機を消す位置
#define AIRPLANE_SMOKE_ROT_RAND			(float (rand() % 629 + -314) / 100)	//回転する際の方向を決めるためのランダム値
#define AIRPLANE_SMOKE_POS_X_RAND		(-5.0f)								//飛行機雲の位置X
#define AIRPLANE_SMOKE_POS_Y_RAND		(float (rand() % 20 + -10))			//飛行機雲の位置Yのランダム値
#define AIRPLANE_SMOKE_SIZE				(D3DXVECTOR3 (20.0f, 20.0f, 0.0f))	//飛行機雲のサイズ
#define AIRPLANE_SMOKE_MOVE_1			(0.2f)								//飛行機雲の移動する際の割合
#define AIRPLANE_SMOKE_MOVE_2			(0.8f)								//飛行機雲の移動する際の割合
#define AIRPLANE_SMOKE_ADD_ROTATE		(0.2f)								//飛行機雲の回転加算値
#define AIRPLANE_SMOKE_ADD_SIZE			(D3DXVECTOR3 (0.4f, 0.4f, 0.0f))	//飛行機雲のサイズ加算値
#define AIRPLANE_SMOKE_SUBTRACT_ALPHA	(0.0055f)							//飛行機雲のα値減算値

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CAirplane::CAirplane(CObject::PRIORITY Priority) :CHappenig(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bHitPlayer = false;
	m_nMoveCounter = 0;
	m_pSmoke.clear();
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CAirplane::~CAirplane()
{

}

//================================================
//初期化処理
//================================================
HRESULT CAirplane::Init()
{
	//変数初期化
	m_bHitPlayer = false;
	m_nMoveCounter = 0;
	m_pSmoke.clear();

	CHappenig::Init();

	//モデルの生成
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_AIRPLANE, NULL, true));

	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::AIR_PLANE);

	//位置を設定
	SetPos(m_pos);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CAirplane::Uninit(void)
{
	CHappenig::Uninit();
}

//================================================
//更新処理
//================================================
void CAirplane::Update(void)
{
	CHappenig::Update();

	if (m_bHitPlayer == false)
	{
		//プレイヤーと当たったら
		if (HitPlayer() == true)
		{
			//オブジェクト情報を入れるポインタ
			vector<CObject*> object;

			//先頭のポインタを代入
			object = CObject::GetObject(static_cast<int>(CObject::PRIORITY::PLAYER));
			int object_size = object.size();

			for (int count_object = 0; count_object < object_size; count_object++)
			{
				//プレイヤーだった時
				if (object[count_object]->GetObjType() == CObject::OBJTYPE::PLAYER)
				{
					if (GetModel()->GetModel()->GetParent() == nullptr)
					{
						//トロフィーのフラグ状態を取得
						vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
						//トロフィーを取得したことがなかったら
						if (flag[(int)CTrophy::TROPHY::AIRPLANE] == false)
						{
							//取得させる
							flag[(int)CTrophy::TROPHY::AIRPLANE] = true;

							CManager::GetInstance()->GetPlayData()->SetFlag(flag);
						}

						//プレイヤーの型にキャスト
						CPlayer *pPlayer = static_cast<CPlayer*>(object[count_object]);

						//モデルの回転を0にする
						GetModel()->GetModel()->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

						//親子関係をつける
						GetModel()->GetModel()->SetObjParent(true);
						GetModel()->GetModel()->SetMtxParent(pPlayer->GetMtx());

						//当たっているフラグを立てる
						m_bHitPlayer = true;

						//モデルの位置を取得
						D3DXVECTOR3 modelPos = GetModel()->GetPos();
						//プレイヤーの位置を取得
						D3DXVECTOR3 playerPos = pPlayer->GetPos();
						//プレイヤーの向きを取得
						D3DXVECTOR3 playerRot = pPlayer->GetRot();

						//プレイヤーの高さをモデルの高さにする
						playerPos.y = modelPos.y;
						//位置を設定
						pPlayer->SetPos(playerPos);

						//回転していたら
						if (playerRot.x != 0.0f)
						{
							//0にする
							playerRot.x = 0.0f;
							//向きを設定
							pPlayer->SetRot(playerRot);
						}

						//前に進む力を設定
						pPlayer->SetMoveForward(AIRPLANE_MOVE_FORWARD);
					}
				}
			}
		}
	}
	else
	{
		//オブジェクト情報を入れるポインタ
		vector<CObject*> object;

		//先頭のポインタを代入
		object = CObject::GetObject(static_cast<int>(CObject::PRIORITY::PLAYER));
		int object_size = object.size();

		for (int count_object = 0; count_object < object_size; count_object++)
		{
			//プレイヤーだった時
			if (object[count_object]->GetObjType() == CObject::OBJTYPE::PLAYER)
			{
				//プレイヤーの型にキャスト
				CPlayer *pPlayer = static_cast<CPlayer*>(object[count_object]);

				//カウンターを加算
				m_nMoveCounter++;

				//前に進む力を設定
				pPlayer->SetMoveForward(AIRPLANE_MOVE_FORWARD);

				//モデルの位置を取得
				D3DXVECTOR3 modelPos = GetModel()->GetPos();

				//飛行機雲を出す
				for (int nCnt = 0; nCnt < AIRPLANE_SMOKE_NUM; nCnt++)
				{
					m_pSmoke.push_back(CSmoke::Create(D3DXVECTOR3(modelPos.x + AIRPLANE_SMOKE_POS_X_RAND, modelPos.y + AIRPLANE_SMOKE_POS_Y_RAND, modelPos.z),
						                              AIRPLANE_SMOKE_SIZE, D3DXVECTOR3(0.0f, 0.0f, AIRPLANE_SMOKE_ROT_RAND),
						                              D3DXVECTOR3(-pPlayer->GetMoveForward() * AIRPLANE_SMOKE_MOVE_1, 0.0f, 0.0f),
						                              D3DXVECTOR3(0.0f, 0.0f, AIRPLANE_SMOKE_ADD_ROTATE),
						                              AIRPLANE_SMOKE_ADD_SIZE, AIRPLANE_SMOKE_SUBTRACT_ALPHA));
					
				}

				int nSize = m_pSmoke.size();
				for (int nCntSmoke = 0; nCntSmoke < nSize; nCntSmoke++)
				{
					//破棄するフラグがたっていたら
					if (m_pSmoke[nCntSmoke]->GetDeath() == true)
					{
						//配列を消去
						m_pSmoke.erase(m_pSmoke.begin() + nCntSmoke);
						nCntSmoke--;
						nSize--;
					}
					else
					{//破棄するフラグがたっていなかったら
						//飛行機雲の移動量を設定
						m_pSmoke[nCntSmoke]->SetMove(D3DXVECTOR3(-pPlayer->GetMoveForward() * AIRPLANE_SMOKE_MOVE_1, 0.0f, 0.0f));
					}
				}

				//既定の値より大きくなったら
				if (m_nMoveCounter > AIRPLANE_MOVE_COUNT)
				{
					for (int nCntSmoke = 0; nCntSmoke < nSize; nCntSmoke++)
					{
						//飛行機雲の移動量を設定
						m_pSmoke[nCntSmoke]->SetMove(D3DXVECTOR3(-pPlayer->GetMoveForward() * AIRPLANE_SMOKE_MOVE_2, 0.0f, 0.0f));
					}


					//親子関係がついているなら
					if (GetModel()->GetModel()->GetObjParent() == true)
					{
						//親子関係を離す
						GetModel()->GetModel()->SetObjParent(false);

						//ジャンプ力を設定
						pPlayer->SetJump(AIRPLANE_PLAYER_JUMP);

						//モデルの回転を元に戻す
						GetModel()->GetModel()->SetRot(D3DXVECTOR3(0.0f, AIRPLANE_INIT_ROT_Y, 0.0f));

						//軌道エフェクトをつける
						pPlayer->SetSparkle(true);

						//前に進む力を設定
						pPlayer->SetMoveForward(AIRPLANE_PLAYER_MOVE_FORWARD);
					}
					
					//既定の値分前に進ませる
					modelPos.x += AIRPLANE_MOVE;
					modelPos.y += 3.0f;

					//既定の値より大きくなったら
					if (modelPos.x > AIRPLANE_UNINIT_POS)
					{
						//消す
						Uninit();
						return;
					}
					else
					{
						//モデルの位置を設定
						GetModel()->SetPos(modelPos);
					}
				}
				else
				{
					//プレイヤーの位置を取得
					D3DXVECTOR3 playerPos = pPlayer->GetPos();
					//プレイヤーの向きを取得
					D3DXVECTOR3 playerRot = pPlayer->GetRot();
					//プレイヤーの移動量を取得
					D3DXVECTOR3 playerMove = pPlayer->GetMove();

					//プレイヤーの高さをモデルの高さにする
					playerPos.y = modelPos.y;
					//位置を設定
					pPlayer->SetPos(playerPos);

					//回転していたら
					if (playerRot.x != 0.0f)
					{
						//0にする
						playerRot.x = 0.0f;
						//向きを設定
						pPlayer->SetRot(playerRot);
					}

					//重力を0にする
					playerMove.y = 0.0f;
					//移動量を設定
					pPlayer->SetMove(playerMove);

					//軌道エフェクトが出ているなら
					if (pPlayer->GetSparkle() == true)
					{
						//軌道エフェクトを消す
						pPlayer->SetSparkle(false);
					}
					
				}
			}
		}
	}
}

//================================================
//描画処理
//================================================
void CAirplane::Draw(void)
{
	CHappenig::Draw();
}

//================================================
//生成処理
//================================================
CAirplane* CAirplane::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	//インスタンスの生成
	CAirplane *pAirplane = nullptr;
	if (pAirplane == nullptr)
	{
		pAirplane = new CAirplane();
		if (pAirplane != nullptr)
		{
			pAirplane->m_pos = pos;
			pAirplane->m_rot = rot;
			pAirplane->Init();
		}
	}
	return pAirplane;
}
