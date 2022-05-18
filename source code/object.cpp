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
#include "pause.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
vector<CObject*> CObject::m_object[(int)PRIORITY::MAX];

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CObject::CObject(PRIORITY priolty)
{
	m_obj_type = OBJTYPE::NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_priority = (int)priolty;
	m_deth = false;

	m_object[m_priority].push_back(this);
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
		if (object_size > 0)
		{
			for (int count_object = object_size - 1; count_object >= 0; count_object--)
			{
				if (m_object[count_priolty][count_object]->m_priority != static_cast<int>(PRIORITY::FADE))
				{
					m_object[count_priolty][count_object]->Uninit();
					if (m_object[count_priolty][count_object]->m_deth == true)
					{
						
					}
					delete m_object[count_priolty][count_object];
					m_object[count_priolty].pop_back();
				}
			}
		}
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
			if (m_object[count_priolty][count_object]->m_deth == true)
			{
				delete m_object[count_priolty][count_object];
				m_object[count_priolty][count_object] = NULL;
				m_object[count_priolty].erase(m_object[count_priolty].begin() + count_object);
				object_size = m_object[count_priolty].size();
				count_object--;
			}
			else
			{
				m_object[count_priolty][count_object]->m_update_count++;
				if (m_object[count_priolty][count_object]->m_update_count >= m_object[count_priolty][count_object]->m_update_frame)
				{
					if (CManager::GetMode() == CManager::MODE::GAME01)
					{
						if (CPause::GetPause() == false)
						{
							m_object[count_priolty][count_object]->Update();
							m_object[count_priolty][count_object]->m_update_count = 0;
						}
						else
						{
							if (count_priolty == (int)PRIORITY::PAUSE || count_priolty == (int)PRIORITY::FADE)
							{
								m_object[count_priolty][count_object]->Update();
								m_object[count_priolty][count_object]->m_update_count = 0;
							}
						}
					}
					else
					{
						m_object[count_priolty][count_object]->Update();
						m_object[count_priolty][count_object]->m_update_count = 0;
					}
				}
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
			if (m_object[count_priolty][count_object]->m_deth == false)
			{
				m_object[count_priolty][count_object]->Draw();
			}
		}
	}
}

//================================================
//�v���C�I���e�B�ݒ菈��
//================================================
void CObject::SetPriority(const int &nPriority)
{
	//���̃I�u�W�F�N�g��������|�C���^
	CObject *pObject = nullptr;
	pObject = this;

	m_object[nPriority].push_back(this);

	int object_size = m_object[nPriority].size();
	for (int count_object = 0; count_object < object_size; count_object++)
	{
		if (m_object[nPriority][count_object] == this)
		{
			m_object[nPriority].erase(m_object[nPriority].begin() + count_object);
			object_size = m_object[nPriority].size();
			break;
		}
	}
}
