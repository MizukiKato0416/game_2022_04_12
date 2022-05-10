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

//=============================================================================
// マクロ定義
//=============================================================================
#define FAN_JUMP_POW			(25.0f)		// ジャンプ力
#define FAN_FORWORD_POW			(20.0f)		// 進力
#define FAN_PLAYER_ROTATION_X	(-0.1f)		// プレイヤーの回転
#define FAN_SLOW_PLAYER_MOVE_Y	(0.2f)		// スロー時の移動量Y
#define FAN_SLOW_FORWORD_POW	(0.3f)		// スロー時の進力
#define FAN_SLOW_COUNT			(30)		// スローにする時間

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CFan::CFan(CObject::PRIORITY Priority) : CHappenig(Priority)
{
	m_bHitPlayer = false;
	m_nCntSlow = 0;
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
	CHappenig::Init();
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_FAN, NULL, true));
	CObject::SetObjType(CObject::OBJTYPE::FAN);

	//変数初期化
	m_bHitPlayer = false;
	m_nCntSlow = 0;

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CFan::Uninit(void)
{
	CHappenig::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CFan::Update(void)
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