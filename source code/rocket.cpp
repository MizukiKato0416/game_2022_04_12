//================================================
//ロケットの処理
//Author:KatoMizuki
//================================================
#include "rocket.h"
#include "model_single.h"
#include "model.h"
#include "player.h"
#include "smoke.h"
#include "play_data.h"
#include "manager.h"
#include "trophy.h"
#include "sound.h"

//================================================
//マクロ定義
//================================================
#define ROCKET_SMOKE_ROT_RAND		(float (rand() % 629 + -314) / 100)	//回転する際の方向を決めるためのランダム値
#define ROCKET_SMOKE_POS_X_RAND		(float (rand() % 20 + -10))			//ロケット雲の位置Xのランダム値
#define ROCKET_SMOKE_POS_Y_RAND		(30.0f)								//ロケット雲の位置Yのランダム値
#define ROCKET_SMOKE_SIZE			(D3DXVECTOR3 (20.0f, 20.0f, 0.0f))	//ロケット雲のサイズ
#define ROCKET_SMOKE_ADD_ROTATE		(0.2f)								//ロケット雲の回転加算値
#define ROCKET_SMOKE_ADD_SIZE		(D3DXVECTOR3 (0.7f, 0.7f, 0.0f))	//ロケット雲のサイズ加算値
#define ROCKET_SMOKE_SUBTRACT_ALPHA	(0.004f)							//ロケット雲のα値減算値
#define ROCKET_MOVE_Y				(6.0f)								//ロケットの移動量

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CRocket::CRocket(CObject::PRIORITY Priority) :CHappenig(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bHitPlayer = false;
	m_pSmoke.clear();
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CRocket::~CRocket()
{

}

//================================================
//初期化処理
//================================================
HRESULT CRocket::Init()
{
	//変数初期化
	m_bHitPlayer = false;
	m_pSmoke.clear();

	CHappenig::Init();

	//モデルの生成
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_ROCKET, NULL, true));

	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::AIR_PLANE);

	//位置を設定
	SetPos(m_pos);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CRocket::Uninit(void)
{
	CHappenig::Uninit();
}

//================================================
//更新処理
//================================================
void CRocket::Update(void)
{
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();
	CHappenig::Update();

	if (m_bHitPlayer == false)
	{
		//プレイヤーと当たったら
		if (HitPlayer() == true)
		{
			sound->ControllVoice(CSound::SOUND_LABEL::ROCKET_SE, 1.4f);
			sound->Play(CSound::SOUND_LABEL::ROCKET_SE);
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
						if (flag[(int)CTrophy::TROPHY::ROCKET] == false)
						{
							//取得させる
							flag[(int)CTrophy::TROPHY::ROCKET] = true;

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

						//モデルの位置を0にする
						modelPos = { 0.0f, 0.0f, 0.0f };

						//モデルの位置を設定
						GetModel()->GetModel()->SetPos(modelPos);

						//前に進む力を設定
						pPlayer->SetMoveForward(0.0f);
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

				//前に進む力を設定
				pPlayer->SetMoveForward(0.0f);

				//モデルの位置を取得
				D3DXMATRIX modelMtx = GetModel()->GetModel()->GetMtx();

				//煙を出す
				for (int nCnt = 0; nCnt < ROCKET_SMOKE_NUM; nCnt++)
				{
					m_pSmoke.push_back(CSmoke::Create(D3DXVECTOR3(modelMtx._41 + ROCKET_SMOKE_POS_X_RAND, modelMtx._42 + ROCKET_SMOKE_POS_Y_RAND, modelMtx._43),
						                              ROCKET_SMOKE_SIZE, D3DXVECTOR3(0.0f, 0.0f, ROCKET_SMOKE_ROT_RAND),
						                              D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						                              D3DXVECTOR3(0.0f, 0.0f, ROCKET_SMOKE_ADD_ROTATE),
						                              ROCKET_SMOKE_ADD_SIZE, ROCKET_SMOKE_SUBTRACT_ALPHA));
				}

				//プレイヤーの移動量を設定
				pPlayer->SetMove(D3DXVECTOR3(0.0f, ROCKET_MOVE_Y, 0.0f));

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
				}
			}
		}
	}
}

//================================================
//描画処理
//================================================
void CRocket::Draw(void)
{
	CHappenig::Draw();
}

//================================================
//生成処理
//================================================
CRocket* CRocket::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	//インスタンスの生成
	CRocket *pRocket = nullptr;
	if (pRocket == nullptr)
	{
		pRocket = new CRocket();
		if (pRocket != nullptr)
		{
			pRocket->m_pos = pos;
			pRocket->m_rot = rot;
			pRocket->Init();
		}
	}
	return pRocket;
}
