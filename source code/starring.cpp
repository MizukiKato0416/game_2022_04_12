//=============================================================================
//
// スターリング処理 [starring.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "starring.h"
#include "player.h"
#include "model_single.h"
#include "play_data.h"
#include "manager.h"
#include "trophy.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define STARRING_ROTATION_X			(0.1f)		// 回転
#define STARRING_PLAYER_ROTATION_X	(-0.1f)		// プレイヤーの回転
#define STARRING_ROTATION_X_SLOW	(0.02f)		// スロー時の回転
#define STARRING_JUMP_POW			(20.0f)		// ジャンプ力
#define STARRING_FORWORD_POW		(35.0f)		// 進力
#define STARRING_SLOW_PLAYER_MOVE_Y	(0.2f)		// スロー時の移動量Y
#define STARRING_PLAYER_MOVE_Y		(8.0f)		// 飛ばすときの移動量Y
#define STARRING_SLOW_FORWORD_POW	(0.3f)		// スロー時の進力
#define STARRING_SLOW_COUNT			(30)		// スローにする時間

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CStarring::CStarring(CObject::PRIORITY Priority) : CHappenig(Priority)
{
	m_bRot = false;
	m_nCntSlow = 0;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CStarring::~CStarring()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CStarring::Init(void)
{
	CHappenig::Init();

	//モデルの生成
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_STARRING, NULL, true));
	//種類の設定
	CObject::SetObjType(CObject::OBJTYPE::STAR_RING);

	//変数初期化
	m_bRot = false;
	m_nCntSlow = 0;

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CStarring::Uninit(void)
{
	CHappenig::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CStarring::Update(void)
{
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();
	CHappenig::Update();

	//プレイヤーに当たったら
	if (CHappenig::HitPlayer() == true)
	{
		sound->ControllVoice(CSound::SOUND_LABEL::STAR_RING_SE, 1.4f);
		sound->Play(CSound::SOUND_LABEL::STAR_RING_SE);
		//回転していない状態なら
		if (m_bRot == false)
		{
			//トロフィーのフラグ状態を取得
			vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
			//トロフィーを取得したことがなかったら
			if (flag[(int)CTrophy::TROPHY::STARRING] == false)
			{
				//取得させる
				flag[(int)CTrophy::TROPHY::STARRING] = true;

				CManager::GetInstance()->GetPlayData()->SetFlag(flag);
			}

			//回転させる
			m_bRot = true;
			//当たっている状態にする
			CHappenig::SetHit(true);
		}
	}

	//回転している状態なら
	if (m_bRot == true)
	{
		//カウンターを加算
		m_nCntSlow++;

		//向きを取得
		m_rot = GetModel()->GetRot();

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
				//プレイヤーにキャスト
				CPlayer *player = static_cast<CPlayer*>(object[count_object]);

				if (m_nCntSlow < STARRING_SLOW_COUNT)
				{
					//カメラズーム処理
					SetCameraZoom();

					//移動量設定
					player->SetMove(D3DXVECTOR3(0.0f, STARRING_SLOW_PLAYER_MOVE_Y, 0.0f));
					//前に進む力設定
					player->SetMoveForward(STARRING_SLOW_FORWORD_POW);
					//回る量設定
					player->SetRotSpeed(STARRING_PLAYER_ROTATION_X);

					//軌道エフェクトが出ているなら
					if (player->GetSparkle() == true)
					{
						//軌道エフェクトを消す
						player->SetSparkle(false);
					}

					//回転させる
					m_rot.x += STARRING_ROTATION_X_SLOW;
				}
				else if(m_nCntSlow == STARRING_SLOW_COUNT)
				{
					//回転させる
					m_rot.x += STARRING_ROTATION_X;
					//当たっていない状態にする
					CHappenig::SetHit(false);
					//ジャンプ量設定
					player->SetJump(STARRING_JUMP_POW);
					//前に進む力を設定
					player->SetMoveForward(STARRING_FORWORD_POW);
					//移動量設定
					player->SetMove(D3DXVECTOR3(0.0f, STARRING_PLAYER_MOVE_Y, 0.0f));
					//回転のスピードを設定
					player->SetRotSpeed(PLAYER_ROTATE);

					//軌道エフェクトが出てないなら
					if (player->GetSparkle() == false)
					{
						//軌道エフェクトを出す
						player->SetSparkle(true);
					}
				}
				else
				{
					//回転させる
					m_rot.x += STARRING_ROTATION_X;
				}
			}
		}
		//向きを設定
		GetModel()->SetRot(m_rot);
	}
}

//=============================================================================
// 描画
//=============================================================================
void CStarring::Draw(void)
{
	CHappenig::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CStarring *CStarring::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	CStarring *star_ring = nullptr;
	if (star_ring == nullptr)
	{
		star_ring = new CStarring;
		if (star_ring != nullptr)
		{
			star_ring->m_pos = pos;
			star_ring->m_rot = rot;
			star_ring->Init();
		}
	}
	return star_ring;
}