//=============================================================================
//
// スターリング処理 [starring.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "starring.h"
#include "player.h"
#include "model_single.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define STARRING_ROTATION_X		(0.1f)		// 回転
#define STARRING_JUMP_POW		(15.0f)		// ジャンプ力
#define STARRING_FORWORD_POW	(35.0f)		// 進力

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CStarring::CStarring(CObject::PRIORITY Priority) : CHappenig(Priority)
{
	m_bRot = false;
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
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_STARRING, NULL, true));
	CObject::SetObjType(CObject::OBJTYPE::STAR_RING);
	m_bRot = false;

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
	CHappenig::Update();
	if (CHappenig::HitPlayer() == true)
	{
		m_bRot = true;

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
				CPlayer *player = static_cast<CPlayer*>(object[count_object]);

				player->SetJump(STARRING_JUMP_POW);
				player->SetMoveForward(STARRING_FORWORD_POW);
			}
		}
	}

	if (m_bRot == true)
	{
		m_rot = GetModel()->GetRot();
		m_rot.x += STARRING_ROTATION_X;
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