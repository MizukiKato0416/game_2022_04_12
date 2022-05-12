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
#include "starring.h"
#include "trampoline.h"
#include "fan.h"
#include "redbull.h"
#include "airplane.h"
#include "thorn.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ROAD_GROUND_HAPPEN_PROBABILITY	(9)			// �ݒu���f���̊m��
#define ROAD_SKY_HAPPEN_PROBABILITY		(6)			// �ݒu���f���̊m��
#define ROAD_AIRPLANE_PROBABILITY		(6)			// ��s�@�̊m��
#define GRONUD_CANDIDATES_POSX_00		(-500)		// �n�ʃ��f��X���ʒu
#define GRONUD_CANDIDATES_POSX_01		(500)		// �n�ʃ��f��X���ʒu
#define GRONUD_CANDIDATES_POSX_02		(0)			// �n�ʃ��f��X���ʒu
#define SKY_CANDIDATES_POS_X_00			(250)		// �󃂃f��X���ʒu
#define SKY_CANDIDATES_POS_Y_00			(350)		// �󃂃f��Y���ʒu
#define SKY_CANDIDATES_POS_X_01			(-250)		// �󃂃f��X���ʒu
#define SKY_CANDIDATES_POS_Y_01			(350)		// �󃂃f��Y���ʒu
#define SKY_CANDIDATES_POS_X_02			(0)		// �󃂃f��X���ʒu
#define SKY_CANDIDATES_POS_Y_02			(250)		// �󃂃f��Y���ʒu

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
	m_floor->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_cloud = CModelSingle::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 1500.0f, m_pos.z + 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                           CXload::X_TYPE_CLOUD, NULL, false);

	for (int count_candidate = 0; count_candidate < (int)CANDIDATES_PLACE::MAX; count_candidate++)
	{
		random_device ground_randomdev;
		mt19937 ground_mt(ground_randomdev());
		uniform_int_distribution<> ground_randomangle(0, ROAD_GROUND_HAPPEN_PROBABILITY);
		int groind_happening_type = ground_randomangle(ground_mt);

		random_device sky_randomdev;
		mt19937 sky_mt(sky_randomdev());
		uniform_int_distribution<> sky_randomangle(0, ROAD_SKY_HAPPEN_PROBABILITY);
		int sky_happening_type = sky_randomangle(sky_mt);

		switch ((CANDIDATES_PLACE)count_candidate)
		{
		case CANDIDATES_PLACE::CANDIDATES_00:
			GroundInstallation(groind_happening_type, GRONUD_CANDIDATES_POSX_00);
			break;
		case CANDIDATES_PLACE::CANDIDATES_01:
			GroundInstallation(groind_happening_type, GRONUD_CANDIDATES_POSX_01);
			break;
		case CANDIDATES_PLACE::CANDIDATES_02:
			GroundInstallation(groind_happening_type, GRONUD_CANDIDATES_POSX_02);
			break;
		case CANDIDATES_PLACE::CANDIDATES_03:
			SkyInstallation(sky_happening_type, SKY_CANDIDATES_POS_X_00, SKY_CANDIDATES_POS_Y_00);
			break;
		case CANDIDATES_PLACE::CANDIDATES_04:
			SkyInstallation(sky_happening_type, SKY_CANDIDATES_POS_X_01, SKY_CANDIDATES_POS_Y_01);
			break;
		case CANDIDATES_PLACE::CANDIDATES_05:
			SkyInstallation(sky_happening_type, SKY_CANDIDATES_POS_X_02, SKY_CANDIDATES_POS_Y_02);
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
			//�I�u�W�F�N�g�^�C�v����s�@�̎�
			if (m_happening_model[model_count]->GetObjType() == CObject::OBJTYPE::AIR_PLANE)
			{
				//��s�@�^�ɃL���X�g
				CAirplane *pAirplane = (CAirplane*)m_happening_model[model_count];

				//�v���C���[�ɓ������Ă��Ȃ���ԂȂ�
				if (pAirplane->GetHitPlayer() == false)
				{
					m_happening_model[model_count]->Uninit();
					m_happening_model[model_count] = NULL;
					m_happening_model.erase(m_happening_model.begin() + model_count);
					model_size = m_happening_model.size();
					model_count--;
				}
			}
			else
			{
				m_happening_model[model_count]->Uninit();
				m_happening_model[model_count] = NULL;
				m_happening_model.erase(m_happening_model.begin() + model_count);
				model_size = m_happening_model.size();
				model_count--;
			}
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
	

	for (int model_count = 0; model_count < model_size; model_count++)
	{

		//�I�u�W�F�N�g�^�C�v����s�@�̎�
		if (m_happening_model[model_count]->GetObjType() == CObject::OBJTYPE::AIR_PLANE)
		{
			//��s�@�^�ɃL���X�g
			CAirplane *pAirplane = (CAirplane*)m_happening_model[model_count];

			//�v���C���[�ɓ������Ă��Ȃ���ԂȂ�
			if (pAirplane->GetHitPlayer() == false)
			{
				D3DXVECTOR3 pos = m_happening_model[model_count]->GetModel()->GetPos();

				pos.x += m_move_speed;

				m_happening_model[model_count]->GetModel()->SetPos(pos);
			}
		}
		else
		{
			D3DXVECTOR3 pos = m_happening_model[model_count]->GetModel()->GetPos();

			pos.x += m_move_speed;

			m_happening_model[model_count]->GetModel()->SetPos(pos);
		}
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
void CRoad::SkyInstallation(const int &happening_type, const int &installation_position_x, const int &installation_position_y)
{
	random_device sky_randomdev;
	mt19937 sky_mt(sky_randomdev());
	uniform_int_distribution<> sky_randomangle(0, ROAD_AIRPLANE_PROBABILITY);
	int airplane_probability = sky_randomangle(sky_mt);

	switch ((CHappenig::HAPPENING_TYPE)happening_type)
	{
	case CHappenig::HAPPENING_TYPE::STARRING:
		m_happening_model.push_back(CStarring::Create(D3DXVECTOR3(m_pos.x + installation_position_x, m_pos.y + installation_position_y, m_pos.z),
													  D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
		break;
	case CHappenig::HAPPENING_TYPE::AIRPLANE:
		switch (airplane_probability)
		{
		case 0:
			m_happening_model.push_back(CAirplane::Create(D3DXVECTOR3(m_pos.x + installation_position_x, m_pos.y + installation_position_y, m_pos.z),
														  D3DXVECTOR3(0.0f, AIRPLANE_INIT_ROT_Y, 0.0f)));
		default:
			break;
		}
		break;
	case CHappenig::HAPPENING_TYPE::THORN:
		m_happening_model.push_back(CThorn::Create(D3DXVECTOR3(m_pos.x + installation_position_x, m_pos.y + installation_position_y, m_pos.z),
			                        D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
		break;
	default:
		break;
	}
}

void CRoad::GroundInstallation(const int &happening_type, const int &installation_position)
{
	switch ((CHappenig::HAPPENING_TYPE)happening_type)
	{
	case CHappenig::HAPPENING_TYPE::TRAMPOLINE:
		m_happening_model.push_back(CTrampoline::Create(D3DXVECTOR3(m_pos.x + installation_position, m_pos.y - 1.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
		break;
	case CHappenig::HAPPENING_TYPE::FAN:
		m_happening_model.push_back(CFan::Create(D3DXVECTOR3(m_pos.x + installation_position, m_pos.y - 1.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
		break;
	case CHappenig::HAPPENING_TYPE::REDBULL:
		m_happening_model.push_back(CRedbull::Create(D3DXVECTOR3(m_pos.x + installation_position, m_pos.y - 1.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
		break;
	/*case CHappenig::HAPPENING_TYPE::GIRL:
		m_happening_model.push_back(CModelSingle::Create(D3DXVECTOR3(m_pos.x + installation_position, m_pos.y - 1.0f, m_pos.z),
			                        D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_A, NULL, true, (CModelSingle::HAPPENING_TYPE)happening_type));
		break;*/
	default:
		break;
	}
}