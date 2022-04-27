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
#define REDBULL_JUMP_POW		(12.5f)		// ジャンプ力
#define REDBULL_FORWORD_POW		(15.0f)		// 進力

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CRedbull::CRedbull(CObject::PRIORITY Priority) : CHappenig(Priority)
{

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

				player->SetJump(REDBULL_JUMP_POW);
				player->SetMoveForward(REDBULL_FORWORD_POW);
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