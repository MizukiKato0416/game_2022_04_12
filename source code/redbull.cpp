//=============================================================================
//
// redbull処理 [redbull.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "redbull.h"
#include "player.h"
#include "model_single.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define REDBULL_JUMP_POW			(15.0f)		// ジャンプ力
#define REDBULL_FORWORD_POW			(40.0f)		// 進力
#define REDBULL_PLAYER_ROTATION_X	(-0.1f)		// プレイヤーの回転
#define REDBULL_SLOW_PLAYER_MOVE_Y	(0.2f)		// スロー時の移動量Y
#define REDBULL_SLOW_FORWORD_POW	(0.3f)		// スロー時の進力
#define REDBULL_SLOW_COUNT			(30)		// スローにする時間

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CRedbull::CRedbull(CObject::PRIORITY Priority) : CHappenig(Priority)
{
	m_bHitPlayer = false;
	m_nCntSlow = 0;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CRedbull::~CRedbull()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CRedbull::Init(void)
{
	CHappenig::Init();
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_REDBULL, NULL, true));
	CObject::SetObjType(CObject::OBJTYPE::REDBULL);

	//変数初期化
	m_bHitPlayer = false;
	m_nCntSlow = 0;

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CRedbull::Uninit(void)
{
	CHappenig::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CRedbull::Update(void)
{
	CHappenig::Update();
	if (CHappenig::HitPlayer() == true)
	{
		if (m_bHitPlayer == false)
		{
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

				if (m_nCntSlow < REDBULL_SLOW_COUNT)
				{
					//カメラズーム処理
					SetCameraZoom();

					//移動量設定
					player->SetMove(D3DXVECTOR3(0.0f, REDBULL_SLOW_PLAYER_MOVE_Y, 0.0f));
					//前に進む力設定
					player->SetMoveForward(REDBULL_SLOW_FORWORD_POW);
					//回る量設定
					player->SetRotSpeed(REDBULL_PLAYER_ROTATION_X);

					//軌道エフェクトが出ているなら
					if (player->GetSparkle() == true)
					{
						//軌道エフェクトを消す
						player->SetSparkle(false);
					}
				}
				else if (m_nCntSlow == REDBULL_SLOW_COUNT)
				{
					//ジャンプ量設定
					player->SetJump(REDBULL_JUMP_POW);
					//前に進む力を設定
					player->SetMoveForward(REDBULL_FORWORD_POW);
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
void CRedbull::Draw(void)
{
	CHappenig::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CRedbull *CRedbull::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	CRedbull *redbull = nullptr;
	if (redbull == nullptr)
	{
		redbull = new CRedbull;
		if (redbull != nullptr)
		{
			redbull->m_pos = pos;
			redbull->m_rot = rot;
			redbull->Init();
		}
	}
	return redbull;
}