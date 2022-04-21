//=============================================================================
//
// 背景処理 [bg.h]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "bg.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CBg::CBg(CObject::PRIORITY Priority) : CObject3D(Priority)
{

}


//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CBg::~CBg()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CBg::Init(void)
{	
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CBg::Uninit(void)
{

}

//=============================================================================
// 更新
//=============================================================================
void CBg::Update(void)
{
	SetTex(m_uv_move_speed.x, m_uv_move_speed.y);
}

//=============================================================================
// 描画
//=============================================================================
void CBg::Draw(void)
{

}

//=============================================================================
// 生成
//=============================================================================
CBg *CBg::Create(const D3DXVECTOR3 & pos, const D3DXVECTOR3 & size, const D3DXVECTOR3 & rot, D3DXVECTOR2 uv_move_speed)
{
	CBg *bg = nullptr;

	if (bg == nullptr)
	{
		bg = new CBg;
		if (bg != nullptr)
		{
			bg->m_pos = pos;
			bg->m_size = size;
			bg->m_rot = rot;
			bg->m_uv_move_speed = uv_move_speed;
		}
	}

	return bg;
}
