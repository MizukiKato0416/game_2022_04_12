//=============================================================================
//
// ファン処理 [fan.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "fan.h"
#include "player.h"
#include "model_single.h"
#include "wind.h"
#include "model.h"
#include "play_data.h"
#include "manager.h"
#include "trophy.h"
#include "sound.h"
#include "history_letter.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FAN_JUMP_POW					(22.0f)									// ジャンプ力
#define FAN_FORWORD_POW					(23.0f)									// 進力
#define FAN_PLAYER_ROTATION_X			(-0.1f)									// プレイヤーの回転
#define FAN_SLOW_PLAYER_MOVE_Y			(0.2f)									// スロー時の移動量Y
#define FAN_SLOW_FORWORD_POW			(0.3f)									// スロー時の進力
#define FAN_SLOW_COUNT					(30)									// スローにする時間
#define FAN_WIND_EFFECT_SIZE			(D3DXVECTOR3(200.0f, 300.0f, 0.0f))		// 風エフェクトのサイズ
#define FAN_ROTATE_SPEED				(0.5f)									// ファンの回転速度

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CFan::CFan(CObject::PRIORITY Priority) : CHappenig(Priority)
{
	m_bHitPlayer = false;
	m_nCntSlow = 0;
	memset(m_apWind, NULL, sizeof(m_apWind[FAN_MAX_WIND_EFFECT]));
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CFan::~CFan()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CFan::Init(void)
{
	//モデルの生成
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_FAN, NULL, true));
	CHappenig::Init();
	
	CObject::SetObjType(CObject::OBJTYPE::FAN);

	//風の生成
	for (int nCntWind = 0; nCntWind < FAN_MAX_WIND_EFFECT; nCntWind++)
	{
		m_apWind[nCntWind] = CWind::Create(D3DXVECTOR3(m_pos.x, m_pos.y + FAN_WIND_EFFECT_SIZE.y / 2.0f, m_pos.z),
			                               FAN_WIND_EFFECT_SIZE, int(0 + WIND_MAX_PATTERN / 2.0f * nCntWind));
	}

	//変数初期化
	m_bHitPlayer = false;
	m_nCntSlow = 0;

	

	//モデルの上頂点の位置を取得
	D3DXVECTOR3 vtxPos[4];
	vtxPos[0] = GetModel()->GetModel()->GetVtxPos(0);
	vtxPos[1] = GetModel()->GetModel()->GetVtxPos(1);
	vtxPos[2] = GetModel()->GetModel()->GetVtxPos(4);
	vtxPos[3] = GetModel()->GetModel()->GetVtxPos(5);
	
	//モデルのサイズYを風のエフェクトのサイズの3分の2引き延ばす
	vtxPos[0].y += FAN_WIND_EFFECT_SIZE.y / 3.0f * 2.0f;
	vtxPos[1].y += FAN_WIND_EFFECT_SIZE.y / 3.0f * 2.0f;
	vtxPos[2].y += FAN_WIND_EFFECT_SIZE.y / 3.0f * 2.0f;
	vtxPos[3].y += FAN_WIND_EFFECT_SIZE.y / 3.0f * 2.0f;

	//サイズを設定
	GetModel()->GetModel()->SetVtxPos(0, vtxPos[0]);
	GetModel()->GetModel()->SetVtxPos(1, vtxPos[1]);
	GetModel()->GetModel()->SetVtxPos(4, vtxPos[2]);
	GetModel()->GetModel()->SetVtxPos(5, vtxPos[3]);

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CFan::Uninit(void)
{
	CHappenig::Uninit();

	for (int nCntWind = 0; nCntWind < FAN_MAX_WIND_EFFECT; nCntWind++)
	{
		if (m_apWind[nCntWind] != nullptr)
		{
			m_apWind[nCntWind]->Uninit();
			m_apWind[nCntWind] = nullptr;
		}
	}
}

//=============================================================================
// 更新
//=============================================================================
void CFan::Update(void)
{
	//サウンド取得
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();

	CHappenig::Update();

	for (int nCntWind = 0; nCntWind < FAN_MAX_WIND_EFFECT; nCntWind++)
	{
		//風エフェクトの位置とサイズを取得
		D3DXVECTOR3 windPos = m_apWind[nCntWind]->GetPos();
		D3DXVECTOR3 windSize = m_apWind[nCntWind]->GetSize();

		//風エフェクトの位置をファンの位置と同じにする
		windPos.x = GetModel()->GetPos().x;

		//風の位置を設定
		m_apWind[nCntWind]->SetPos(windPos, windSize);
	}

	//向きを取得
	m_rot = GetModel()->GetRot();
	//回転させる
	m_rot.y += FAN_ROTATE_SPEED;
	//向きを設定
	GetModel()->SetRot(m_rot);

	//プレイヤーに当たったら
	if (CHappenig::HitPlayer() == true)
	{
		//プレイヤーに当たった状態にする
		if (m_bHitPlayer == false)
		{
			//トロフィーのフラグ状態を取得
			vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
			//トロフィーを取得したことがなかったら
			if (flag[(int)CTrophy::TROPHY::FAN] == false)
			{
				//取得させる
				flag[(int)CTrophy::TROPHY::FAN] = true;

				CManager::GetInstance()->GetPlayData()->SetFlag(flag);
				CHistory::Create(CTrophy::TROPHY::FAN);
			}

			//SE設定
			sound->ControllVoice(CSound::SOUND_LABEL::FAN_SE, 1.4f);
			sound->Play(CSound::SOUND_LABEL::FAN_SE);

			m_bHitPlayer = true;
			//当たっている状態にする
			CHappenig::SetHit(true);
		}
	}

	//プレイヤーに当たった状態なら
	if (m_bHitPlayer == true)
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

				if (m_nCntSlow < FAN_SLOW_COUNT)
				{
					//カメラズーム処理
					SetCameraZoom();

					//移動量設定
					player->SetMove(D3DXVECTOR3(0.0f, FAN_SLOW_PLAYER_MOVE_Y, 0.0f));
					//前に進む力設定
					player->SetMoveForward(FAN_SLOW_FORWORD_POW);
					//回る量設定
					player->SetRotSpeed(FAN_PLAYER_ROTATION_X);

					//軌道エフェクトが出ているなら
					if (player->GetSparkle() == true)
					{
						//軌道エフェクトを消す
						player->SetSparkle(false);
					}
				}
				else if (m_nCntSlow == FAN_SLOW_COUNT)
				{
					//当たっていない状態にする
					CHappenig::SetHit(false);
					//ジャンプ量設定
					player->SetJump(FAN_JUMP_POW);
					//前に進む力を設定
					player->SetMoveForward(FAN_FORWORD_POW);
					//移動量設定
					player->SetMove(D3DXVECTOR3(0.0f, player->GetJump(), 0.0f));
					//バウンドする瞬間の移動量を設定
					player->SetBoundMove(player->GetJump());
					//回転のスピードを設定
					player->SetRotSpeed(PLAYER_ROTATE);

					//軌道エフェクトが出てないなら
					if (player->GetSparkle() == false)
					{
						//軌道エフェクトを出す
						player->SetSparkle(true);
					}
				}
			}
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void CFan::Draw(void)
{
	CHappenig::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CFan *CFan::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	CFan *fan = nullptr;
	if (fan == nullptr)
	{
		fan = new CFan;
		if (fan != nullptr)
		{
			fan->m_pos = pos;
			fan->m_rot = rot;
			fan->Init();
		}
	}
	return fan;
}