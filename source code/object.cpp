//=============================================================================
//
// �I�u�W�F�N�g���� [object.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "object.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
vector<CObject*> CObject::m_object[(int)OBJTYPE::MAX];

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CObject::CObject(PRIORITY priolty)
{
	m_object[m_nPriority].push_back(this);

	m_obj_type = OBJTYPE::NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_priority = (int)priolty;
	m_deth = false;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CObject::~CObject()
{
	
}

//=============================================================================
// �S���폜
//=============================================================================
void CObject::ReleaseAll(void)
{
	for (int count_priolty = 0; count_priolty < (int)PRIORITY::MAX; count_priolty++)
	{
		int object_size = m_object[count_priolty].size();
		for (int count_object = 0; count_object < object_size; count_object++)
		{
			delete m_object[count_priolty][count_object];
		}
		m_object[count_priolty].pop_back();
	}
}

//=============================================================================
// �S���X�V
//=============================================================================
void CObject::UpdateAll(void)
{
	for (int count_priolty = 0; count_priolty < (int)PRIORITY::MAX; count_priolty++)
	{
		int object_size = m_object[count_priolty].size();
		for (int count_object = 0; count_object < object_size; count_object++)
		{
			m_object[count_priolty][count_object]->Update();
			if (m_object[count_priolty][count_object]->m_bDeth == true)
			{
				delete m_object[count_priolty][count_object];
				m_object[count_priolty][count_object] = NULL;
				m_object[count_priolty].erase(m_object[count_priolty].begin() + object_size);
			}
		}
	}
}

//=============================================================================
// �S���`��
//=============================================================================
void CObject::DrawAll(void)
{
	for (int count_priolty = 0; count_priolty < (int)PRIORITY::MAX; count_priolty++)
	{
		int object_size = m_object[count_priolty].size();
		for (int count_object = 0; count_object < object_size; count_object++)
		{
			m_object[count_priolty][count_object]->Draw();
		}
	}
}