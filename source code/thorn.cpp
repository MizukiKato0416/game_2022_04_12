//=============================================================================
//
// 棘処理 [thorn.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "thorn.h"
#include "player.h"
#include "model_single.h"
#include "play_data.h"
#include "manager.h"
#include "trophy.h"
#include "sound.h"
#include "model.h"
#include "history_letter.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define THORN_JUMP_POW				(10.0f)		// ジャンプ力
#define THORN_FORWORD_POW			(20.0f)		// 進力
#define THORN_PLAYER_ROTATION_X		(-0.1f)		// プレイヤーの回転
#define THORN_SLOW_PLAYER_MOVE_Y	(0.2f)		// スロー時の移動量Y
#define THORN_SLOW_FORWORD_POW		(0.3f)		// スロー時の進力
#define THORN_SLOW_COUNT			(5)			// スローにする時間

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CThorn::CThorn(CObject::PRIORITY Priority) : CHappenig(Priority)
{
	m_bHitPlayer = false;
	m_nCntSlow = 0;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CThorn::~CThorn()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CThorn::Init(void)
{
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_THORN, NULL, true));
	CHappenig::Init();
	CObject::SetObjType(CObject::OBJTYPE::THORN);

	//モデルの上頂点の位置を取得
	D3DXVECTOR3 vtxPos[8];
	for (int nCntVtx = 0; nCntVtx < 8; nCntVtx++)
	{
		vtxPos[nCntVtx] = GetModel()->GetModel()->GetVtxPos(nCntVtx);
	}

	//モデルのサイズYを風のエフェクトのサイズの3分の2引き延ばす
	vtxPos[0].y -= HAPPENING_ADD_SIZE_Y;
	vtxPos[1].y -= HAPPENING_ADD_SIZE_Y;
	vtxPos[4].y -= HAPPENING_ADD_SIZE_Y;
	vtxPos[5].y -= HAPPENING_ADD_SIZE_Y;

	vtxPos[0].x += HAPPENING_ADD_SIZE_X;
	vtxPos[2].x += HAPPENING_ADD_SIZE_X;
	vtxPos[4].x += HAPPENING_ADD_SIZE_X;
	vtxPos[6].x += HAPPENING_ADD_SIZE_X;

	vtxPos[1].x -= HAPPENING_ADD_SIZE_X;
	vtxPos[3].x -= HAPPENING_ADD_SIZE_X;
	vtxPos[5].x -= HAPPENING_ADD_SIZE_X;
	vtxPos[7].x -= HAPPENING_ADD_SIZE_X;

	//サイズを設定
	for (int nCntVtx = 0; nCntVtx < 8; nCntVtx++)
	{
		GetModel()->GetModel()->SetVtxPos(nCntVtx, vtxPos[nCntVtx]);
	}


	//変数初期化
	m_bHitPlayer = false;
	m_nCntSlow = 0;

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CThorn::Uninit(void)
{
	CHappenig::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CThorn::Update(void)
{
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();
	CHappenig::Update();
	if (CHappenig::HitPlayer() == true)
	{
		sound->ControllVoice(CSound::SOUND_LABEL::THORN_SE, 1.8f);
		sound->Play(CSound::SOUND_LABEL::THORN_SE);
		if (m_bHitPlayer == false)
		{
			//トロフィーのフラグ状態を取得
			vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
			//トロフィーを取得したことがなかったら
			if (flag[(int)CTrophy::TROPHY::THORN] == false)
			{
				//取得させる
				flag[(int)CTrophy::TROPHY::THORN] = true;

				CManager::GetInstance()->GetPlayData()->SetFlag(flag);
				CHistory::Create(CTrophy::TROPHY::THORN);
			}

			m_bHitPlayer = true;
			//当たっている状態にする
			CHappenig::SetHit(true);
		}
	}

	
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

				if (m_nCntSlow < THORN_SLOW_COUNT)
				{
					//移動量設定
					player->SetMove(D3DXVECTOR3(0.0f, THORN_SLOW_PLAYER_MOVE_Y, 0.0f));
					//前に進む力設定
					player->SetMoveForward(THORN_SLOW_FORWORD_POW);
				}
				else if (m_nCntSlow == THORN_SLOW_COUNT)
				{
					//当たっていない状態にする
					CHappenig::SetHit(false);
					//ジャンプ量設定
					player->SetJump(THORN_JUMP_POW);
					//前に進む力を設定
					player->SetMoveForward(THORN_FORWORD_POW);
					//バウンドする瞬間の移動量を設定
					player->SetBoundMove(player->GetJump());
				}
			}
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void CThorn::Draw(void)
{
	CHappenig::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CThorn *CThorn::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	CThorn *trampo_line = nullptr;
	if (trampo_line == nullptr)
	{
		trampo_line = new CThorn;
		if (trampo_line != nullptr)
		{
			trampo_line->m_pos = pos;
			trampo_line->m_rot = rot;
			trampo_line->Init();
		}
	}
	return trampo_line;
}