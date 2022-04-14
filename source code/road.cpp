//=============================================================================
//
// road処理 [road.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "road.h"
#include "floor.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CRoad::CRoad(CObject::PRIORITY priorty) : CObject(priorty)
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CRoad::~CRoad()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRoad::Init(void)
{
	m_floor = CFloor::Create(m_pos, D3DXVECTOR3(2000.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	switch (m_happening_type)
	{
	case HAPPENING_TYPE::NONE:
		break;
	default:
		break;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRoad::Uninit(void)
{
	m_floor->Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CRoad::Update(void)
{
	D3DXVECTOR3 pos = m_floor->GetPos();
	D3DXVECTOR3 size = m_floor->GetSize();
	pos.x += m_move_speed;
	m_floor->SetPos(pos, size);
}

//=============================================================================
// 描画処理
//=============================================================================
void CRoad::Draw(void)
{

}

//================================================
//生成処理
//================================================
CRoad *CRoad::Create(const D3DXVECTOR3 &pos, const HAPPENING_TYPE &type, const float &move_speed)
{
	//インスタンスの生成
	CRoad *load = nullptr;
	if (load == nullptr)
	{
		load = new CRoad();
		if (load != nullptr)
		{
			load->m_pos = pos;
			load->m_move_speed = move_speed;
			load->m_happening_type = type;
			load->Init();
		}
	}
	return load;
}