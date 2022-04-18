//=============================================================================
//
// road処理 [road.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include <random>
#include "road.h"
#include "floor.h"
#include "model_single.h"
#include "manager.h"
#include "texture.h"

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
	m_floor = CFloor::Create(m_pos, m_size, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_floor->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_DUNGEON_WALL"));

	for (int count_candidate = 0; count_candidate < (int)CANDIDATES_PLACE::MAX; count_candidate++)
	{
		random_device randomdev;
		mt19937 mt(randomdev());
		uniform_int_distribution<> randomangle(0, 9);
		int happening_type = randomangle(mt);

		switch ((CANDIDATES_PLACE)count_candidate)
		{
		case CANDIDATES_PLACE::CANDIDATES_00:
			GroundInstallation(happening_type, CANDIDATES_POS_00);
			break;
		case CANDIDATES_PLACE::CANDIDATES_01:
			GroundInstallation(happening_type, CANDIDATES_POS_01);
			break;
		case CANDIDATES_PLACE::CANDIDATES_02:
			SkyInstallation(happening_type);
			break;
		default:
			break;
		}
	}

	SetPos(m_pos);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRoad::Uninit(void)
{
	int model_size = m_happening_model.size();
	if (m_floor != nullptr)
	{
		m_floor->Uninit();
	}
	for (int model_count = 0; model_count < model_size; model_count++)
	{
		if (m_happening_model[model_count] != nullptr)
		{
			m_happening_model[model_count]->Uninit();
			m_happening_model[model_count] = NULL;
			m_happening_model.erase(m_happening_model.begin() + model_count);
			model_size = m_happening_model.size();
			model_count--;
		}
	}
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CRoad::Update(void)
{
	int model_size = m_happening_model.size();

	m_pos = m_floor->GetPos();
	m_size = m_floor->GetSize();

	m_pos.x += m_move_speed;

	m_floor->SetPos(m_pos, m_size);
	SetPos(m_pos);

	for (int mdoel_sount = 0; mdoel_sount < model_size; mdoel_sount++)
	{
		D3DXVECTOR3 pos = m_happening_model[mdoel_sount]->GetPos();
		D3DXVECTOR3 size = m_happening_model[mdoel_sount]->GetSize();

		pos.x += m_move_speed;

		m_happening_model[mdoel_sount]->SetPos(pos);
	}
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
CRoad *CRoad::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const float &move_speed)
{
	//インスタンスの生成
	CRoad *load = nullptr;
	if (load == nullptr)
	{
		load = new CRoad();
		if (load != nullptr)
		{
			load->m_pos = pos;
			load->m_size = size;
			load->m_move_speed = move_speed;
			load->Init();
		}
	}
	return load;
}

//================================================
//設置処理
//================================================
void CRoad::SkyInstallation(const int &happening_type)
{
	switch ((CModelSingle::HAPPENING_TYPE)happening_type)
	{
	default:
		break;
	}
}

void CRoad::GroundInstallation(const int &happening_type, const int &installation_position)
{
	switch ((CModelSingle::HAPPENING_TYPE)happening_type)
	{
	case CModelSingle::HAPPENING_TYPE::TRAMPOLINE:
		m_happening_model.push_back(CModelSingle::Create(D3DXVECTOR3(m_pos.x + installation_position, m_pos.y, m_pos.z),
			                        D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_A, NULL, true, (CModelSingle::HAPPENING_TYPE)happening_type));
		break;
	case CModelSingle::HAPPENING_TYPE::FAN:
		m_happening_model.push_back(CModelSingle::Create(D3DXVECTOR3(m_pos.x + installation_position, m_pos.y, m_pos.z),
			                        D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_A, NULL, true, (CModelSingle::HAPPENING_TYPE)happening_type));
		break;
	case CModelSingle::HAPPENING_TYPE::BALANCE_BALL:
		m_happening_model.push_back(CModelSingle::Create(D3DXVECTOR3(m_pos.x + installation_position, m_pos.y, m_pos.z),
			                        D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_A, NULL, true, (CModelSingle::HAPPENING_TYPE)happening_type));
		break;
	case CModelSingle::HAPPENING_TYPE::GIRL:
		m_happening_model.push_back(CModelSingle::Create(D3DXVECTOR3(m_pos.x + installation_position, m_pos.y, m_pos.z),
			                        D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_A, NULL, true, (CModelSingle::HAPPENING_TYPE)happening_type));
		break;
	default:
		break;
	}
}