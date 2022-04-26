//=============================================================================
//
// road���� [road.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include <random>
#include "road.h"
#include "floor.h"
#include "model_single.h"
#include "manager.h"
#include "texture.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CRoad::CRoad(CObject::PRIORITY priorty) : CObject(priorty)
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CRoad::~CRoad()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRoad::Init(void)
{
	m_floor = CFloor::Create(m_pos, m_size, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_cloud = CModelSingle::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 1500.0f, m_pos.z + 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                           CXload::X_TYPE_CLOUD, NULL, false, CModelSingle::HAPPENING_TYPE::NONE);

	for (int count_candidate = 0; count_candidate < (int)CANDIDATES_PLACE::MAX; count_candidate++)
	{
		random_device randomdev;
		mt19937 mt(randomdev());
		uniform_int_distribution<> randomangle(0, 9);
		int happening_type = randomangle(mt);

		switch ((CANDIDATES_PLACE)count_candidate)
		{
		case CANDIDATES_PLACE::CANDIDATES_00:
			GroundInstallation(happening_type, DRONUD_CANDIDATES_POSX_00);
			break;
		case CANDIDATES_PLACE::CANDIDATES_01:
			GroundInstallation(happening_type, DRONUD_CANDIDATES_POSX_01);
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
// �I������
//=============================================================================
void CRoad::Uninit(void)
{
	int model_size = m_happening_model.size();
	if (m_floor != nullptr)
	{
		m_floor->Uninit();
	}
	if (m_cloud != nullptr)
	{
		m_cloud->Uninit();
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
// �X�V����
//=============================================================================
void CRoad::Update(void)
{
	int model_size = m_happening_model.size();

	m_pos = m_floor->GetPos();
	m_size = m_floor->GetSize();

	m_pos.x += m_move_speed;
	
	m_floor->SetPos(m_pos, m_size);

	SetPos(m_pos);

	D3DXVECTOR3 cloudPos = m_cloud->GetPos();
	cloudPos.x += m_move_speed;
	m_cloud->SetPos(cloudPos);
	

	for (int mdoel_sount = 0; mdoel_sount < model_size; mdoel_sount++)
	{
		D3DXVECTOR3 pos = m_happening_model[mdoel_sount]->GetPos();
		D3DXVECTOR3 size = m_happening_model[mdoel_sount]->GetSize();

		pos.x += m_move_speed;

		m_happening_model[mdoel_sount]->SetPos(pos);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CRoad::Draw(void)
{

}

//================================================
//��������
//================================================
CRoad *CRoad::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const float &move_speed)
{
	//�C���X�^���X�̐���
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
//�ݒu����
//================================================
void CRoad::SkyInstallation(const int &happening_type)
{
	switch ((CModelSingle::HAPPENING_TYPE)happening_type)
	{
	case CModelSingle::HAPPENING_TYPE::STARRING:
		m_happening_model.push_back(CModelSingle::Create(D3DXVECTOR3(m_pos.x + SKY_CANDIDATES_POS_X, m_pos.y + DRONUD_CANDIDATES_POSX_01, m_pos.z),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_STARRING, NULL, true, (CModelSingle::HAPPENING_TYPE)happening_type));
		break;
	default:
		break;
	}
}

void CRoad::GroundInstallation(const int &happening_type, const int &installation_position)
{
	switch ((CModelSingle::HAPPENING_TYPE)happening_type)
	{
	case CModelSingle::HAPPENING_TYPE::TRAMPOLINE:
		m_happening_model.push_back(CModelSingle::Create(D3DXVECTOR3(m_pos.x + installation_position, m_pos.y - 1.0f, m_pos.z),
			                        D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_TRAMPLINE, NULL, true, (CModelSingle::HAPPENING_TYPE)happening_type));
		break;
	case CModelSingle::HAPPENING_TYPE::FAN:
		m_happening_model.push_back(CModelSingle::Create(D3DXVECTOR3(m_pos.x + installation_position, m_pos.y - 1.0f, m_pos.z),
			                        D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_FAN, NULL, true, (CModelSingle::HAPPENING_TYPE)happening_type));
		break;
	case CModelSingle::HAPPENING_TYPE::REDBULL:
		m_happening_model.push_back(CModelSingle::Create(D3DXVECTOR3(m_pos.x + installation_position, m_pos.y - 1.0f, m_pos.z),
			                        D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_REDBULL, NULL, true, (CModelSingle::HAPPENING_TYPE)happening_type));
		break;
	case CModelSingle::HAPPENING_TYPE::GIRL:
		m_happening_model.push_back(CModelSingle::Create(D3DXVECTOR3(m_pos.x + installation_position, m_pos.y - 1.0f, m_pos.z),
			                        D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_A, NULL, true, (CModelSingle::HAPPENING_TYPE)happening_type));
		break;
	default:
		break;
	}
}