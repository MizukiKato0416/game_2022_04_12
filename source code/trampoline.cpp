//=============================================================================
//
// トランポリン処理 [trampoline.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "trampoline.h"
#include "player.h"
#include "model_single.h"
#include "play_data.h"
#include "manager.h"
#include "trophy.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TRAMPOLINE_JUMP_POW				(21.0f)		// ジャンプ力
#define TRAMPOLINE_FORWORD_POW			(25.0f)		// 進力
#define TRAMPOLINE_PLAYER_ROTATION_X	(-0.1f)		// プレイヤーの回転
#define TRAMPOLINE_SLOW_PLAYER_MOVE_Y	(0.2f)		// スロー時の移動量Y
#define TRAMPOLINE_SLOW_FORWORD_POW		(0.3f)		// スロー時の進力
#define TRAMPOLINE_SLOW_COUNT			(30)		// スローにする時間

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTrampoline::CTrampoline(CObject::PRIORITY Priority) : CHappenig(Priority)
{
	m_bHitPlayer = false;
	m_nCntSlow = 0;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CTrampoline::~CTrampoline()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CTrampoline::Init(void)
{
	CHappenig::Init();
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_TRAMPLINE, NULL, true));
	CObject::SetObjType(CObject::OBJTYPE::TRAMPOLINE);

	//変数初期化
	m_bHitPlayer = false;
	m_nCntSlow = 0;

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CTrampoline::Uninit(void)
{
	CHappenig::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CTrampoline::Update(void)
{
	CHappenig::Update();
	if (CHappenig::HitPlayer() == true)
	{
		if (m_bHitPlayer == false)
		{
			//トロフィーのフラグ状態を取得
			vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
			//トロフィーを取得したことがなかったら
			if (flag[(int)CTrophy::TROPHY::TRAMPOLINE] == false)
			{
				//取得させる
				flag[(int)CTrophy::TROPHY::TRAMPOLINE] = true;

				CManager::GetInstance()->GetPlayData()->SetFlag(flag);
			}

			m_bHitPlayer = true;
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

				if (m_nCntSlow < TRAMPOLINE_SLOW_COUNT)
				{
					//カメラズーム処理
					SetCameraZoom();

					//移動量設定
					player->SetMove(D3DXVECTOR3(0.0f, TRAMPOLINE_SLOW_PLAYER_MOVE_Y, 0.0f));
					//前に進む力設定
					player->SetMoveForward(TRAMPOLINE_SLOW_FORWORD_POW);
					//回る量設定
					player->SetRotSpeed(TRAMPOLINE_PLAYER_ROTATION_X);

					//軌道エフェクトが出ているなら
					if (player->GetSparkle() == true)
					{
						//軌道エフェクトを消す
						player->SetSparkle(false);
					}
				}
				else if (m_nCntSlow == TRAMPOLINE_SLOW_COUNT)
				{
					//ジャンプ量設定
					player->SetJump(TRAMPOLINE_JUMP_POW);
					//前に進む力を設定
					player->SetMoveForward(TRAMPOLINE_FORWORD_POW);
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
void CTrampoline::Draw(void)
{
	CHappenig::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CTrampoline *CTrampoline::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	CTrampoline *trampo_line = nullptr;
	if (trampo_line == nullptr)
	{
		trampo_line = new CTrampoline;
		if (trampo_line != nullptr)
		{
			trampo_line->m_pos = pos;
			trampo_line->m_rot = rot;
			trampo_line->Init();
		}
	}
	return trampo_line;
}