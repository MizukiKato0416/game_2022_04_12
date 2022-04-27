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

//=============================================================================
// マクロ定義
//=============================================================================
#define TRAMPOLINE_JUMP_POW		(20.0f)		// ジャンプ力
#define TRAMPOLINE_FORWORD_POW	(17.5f)		// 進力

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTrampoline::CTrampoline(CObject::PRIORITY Priority) : CHappenig(Priority)
{

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

				player->SetJump(TRAMPOLINE_JUMP_POW);
				player->SetMoveForward(TRAMPOLINE_FORWORD_POW);
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