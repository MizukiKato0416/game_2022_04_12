//=============================================================================
//
// road���� [road.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
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
	m_floor->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_DUNGEON_WALL"));
	int n = 19;

	switch (m_happening_type)
	{
	case CModelSingle::HAPPENING_TYPE::NONE:
		//m_happening_model = CModelSingle::Create(D3DXVECTOR3(m_pos.x + 500.0f, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_PLAYER_BODY, );
		break;
	default:
		break;
	}

	SetPos(m_pos);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRoad::Uninit(void)
{
	m_floor->Uninit();
	m_happening_model->Uninit();
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CRoad::Update(void)
{
	m_pos = m_floor->GetPos();
	m_size = m_floor->GetSize();

	m_pos.x += m_move_speed;

	m_floor->SetPos(m_pos, m_size);
	SetPos(m_pos);
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
CRoad *CRoad::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const CModelSingle::HAPPENING_TYPE &type, const float &move_speed)
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
			load->m_happening_type = type;
			load->Init();
		}
	}
	return load;
}