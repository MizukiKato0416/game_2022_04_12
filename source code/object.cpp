//================================================
//�V�[������
//Author:��������
//================================================
#include "object.h"
#include "manager.h"
#include "pause.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
CObject *CObject::m_pTop[PRIORITY_MAX] = {};
CObject *CObject::m_pCur[PRIORITY_MAX] = {};

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CObject::CObject(int nPriority)
{
	if (m_pTop[nPriority] == nullptr && m_pCur[nPriority] == nullptr)
	{
		//�O�̃I�u�W�F�N�g��񂪂Ȃ����TOP�ɂ���
		m_pTop[nPriority] = this;
		//���̃I�u�W�F�N�g��񂪂Ȃ����CUR�ɂ���
		m_pCur[nPriority] = this;
		m_pPrev = nullptr;
		m_pNext = nullptr;
	}
	else
	{
		//�O�̃I�u�W�F�N�g��񂪂�������O�̃I�u�W�F�N�g�������Ă�����
		m_pPrev = m_pCur[nPriority];
		//�O�̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g�������̃I�u�W�F�N�g�ɂ���
		m_pCur[nPriority]->m_pNext = this;
		//��ԍŌ�ɂ���
		m_pCur[nPriority] = this;
		m_pNext = nullptr;
	}
	m_objType = OBJTYPE::NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nPriority = nPriority;
	m_bDeath = false;
}

//================================================
//�f�X�g���N�^
//================================================
CObject::~CObject()
{
	//���̃I�u�W�F�N�g��������|�C���^
	CObject *pObject = nullptr;
	pObject = this;

	//�g�b�v�ł��J�����g�ł��Ȃ��ꍇ
	if (pObject != m_pTop[m_nPriority] && pObject != m_pCur[m_nPriority])
	{
		//�����̑O�̃I�u�W�F�N�g�������Ă��鎟�̃I�u�W�F�N�g���������̎��̃I�u�W�F�N�g���ɂ���
		pObject->m_pPrev->m_pNext = pObject->m_pNext;
		//�����̎��̃I�u�W�F�N�g�������Ă���O�̃I�u�W�F�N�g���������̑O�̃I�u�W�F�N�g���ɂ���
		pObject->m_pNext->m_pPrev = pObject->m_pPrev;
	}
	if (pObject == m_pTop[m_nPriority])
	{
		//�g�b�v��������g�b�v�����̃I�u�W�F�N�g�ɂ��炷
		m_pTop[m_nPriority] = pObject->m_pNext;
		//�����̎��̃I�u�W�F�N�g�������Ă���O�̃I�u�W�F�N�g����nullptr�ɂ���
		if (pObject->m_pNext != nullptr)
		{
			pObject->m_pNext->m_pPrev = nullptr;
		}
	}
	if (pObject == m_pCur[m_nPriority])
	{
		//�J�����g��������J�����g��O�̃I�u�W�F�N�g�ɂ��炷
		m_pCur[m_nPriority] = pObject->m_pPrev;
		//�����̑O�̃I�u�W�F�N�g�������Ă��鎟�̃I�u�W�F�N�g����nullptr�ɂ���
		if (pObject->m_pPrev != nullptr)
		{
			pObject->m_pPrev->m_pNext = nullptr;
		}
	}
}

//================================================
//�I������
//================================================
void CObject::ReleaseAll(void)
{
	//���̃I�u�W�F�N�g��������|�C���^
	CObject *pObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CObject *pSaveObject = nullptr;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		if (nCntPriority != PRIORITY_FADE)
		{
			//�擪�̃|�C���^����
			pObject = m_pTop[nCntPriority];
			while (pObject != nullptr)
			{
				//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
				pSaveObject = pObject->m_pNext;
				pObject->Uninit();
				if (pObject->m_bDeath == true)
				{
					//�j��
					delete pObject;
					pObject = nullptr;
				}
				//���̃I�u�W�F�N�g�̃|�C���^�ɂ���
				pObject = pSaveObject;
			}
		}
	}
}

//================================================
//�X�V����
//================================================
void CObject::UpdateAll(void)
{
	//���̃I�u�W�F�N�g��������|�C���^
	CObject *pObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CObject *pSaveObject = nullptr;
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�擪�̃|�C���^����
		pObject = m_pTop[nCntPriority];
		while (pObject != nullptr)
		{
			//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
			pSaveObject = pObject->m_pNext;
			//���S�t���O�`�F�b�N
			if (pObject->m_bDeath == false)
			{
				if (CPause::GetPause() == false)
				{
					pObject->Update();
				}
				else
				{
					if (nCntPriority == PRIORITY_FADE || nCntPriority == PRIORITY_PAUSE)
					{
						pObject->Update();
					}
				}
			}
			pObject = pSaveObject;
		}
	}


	pSaveObject = nullptr;
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�擪�̃|�C���^����
		pObject = m_pTop[nCntPriority];
		while (pObject != nullptr)
		{
			//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
			pSaveObject = pObject->m_pNext;
			//���S�t���O�`�F�b�N
			if (pObject->m_bDeath == true)
			{
				//�j��
				delete pObject;
				pObject = nullptr;
			}
			//���̃I�u�W�F�N�g�̃|�C���^�ɂ���
			pObject = pSaveObject;
		}
	}
}

//================================================
//�`�揈��
//================================================
void CObject::DrawAll(void)
{
	//���̃I�u�W�F�N�g��������|�C���^
	CObject *pObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CObject *pSaveObject = nullptr;
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�擪�̃|�C���^����
		pObject = m_pTop[nCntPriority];
		while (pObject != nullptr)
		{
			//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
			pSaveObject = pObject->m_pNext;
			pObject->Draw();
			pObject = pSaveObject;
		}
	}
}

//================================================
//�P�̂�j�����鏈��
//================================================
void CObject::Release(void)
{
	m_bDeath = true;	
}

//================================================
//�I�u�W�F�N�g�̎�ނ̐ݒ菈��
//================================================
void CObject::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//================================================
//�I�u�W�F�N�g�̎�ނ̐ݒ菈��
//================================================
CObject::OBJTYPE CObject::GetObjType(void)
{
	return m_objType;
}

//================================================
//�����̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���擾����
//================================================
CObject *CObject::GetObjNext(CObject *pObject)
{
	return pObject->m_pNext;
}

//================================================
//�I�u�W�F�N�g�擾����
//================================================
CObject *CObject::GetTopObj(int nPriority)
{
	return m_pTop[nPriority];
}

//================================================
//�ʒu�擾����
//================================================
D3DXVECTOR3 CObject::GetPos(void)
{
	return m_pos;
}

//================================================
//1�t���[���O�̈ʒu�ݒ菈��
//================================================
void CObject::SetPosOld(D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}

//================================================
//1�t���[���O�̈ʒu�擾����
//================================================
D3DXVECTOR3 CObject::GetPosOld(void)
{
	return m_posOld;
}

//================================================
//�ʒu�ݒ菈��
//================================================
void CObject::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//================================================
//�T�C�Y�擾����
//================================================
D3DXVECTOR3 CObject::GetSize(void)
{
	return m_size;
}

//================================================
//�T�C�Y�ݒ菈��
//================================================
void CObject::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//================================================
//�v���C�I���e�B�ݒ菈��
//================================================
void CObject::SetPriority(int nPriority)
{
	//���̃I�u�W�F�N�g��������|�C���^
	CObject *pObject = nullptr;
	pObject = this;

	//�g�b�v�ł��J�����g�ł��Ȃ��ꍇ
	if (pObject != m_pTop[m_nPriority] && pObject != m_pCur[m_nPriority])
	{
		//�����̑O�̃I�u�W�F�N�g�������Ă��鎟�̃I�u�W�F�N�g���������̎��̃I�u�W�F�N�g���ɂ���
		pObject->m_pPrev->m_pNext = pObject->m_pNext;
		//�����̎��̃I�u�W�F�N�g�������Ă���O�̃I�u�W�F�N�g���������̑O�̃I�u�W�F�N�g���ɂ���
		pObject->m_pNext->m_pPrev = pObject->m_pPrev;
	}
	if (pObject == m_pTop[m_nPriority])
	{
		//�g�b�v��������g�b�v�����̃I�u�W�F�N�g�ɂ��炷
		m_pTop[m_nPriority] = pObject->m_pNext;
		//�����̎��̃I�u�W�F�N�g�������Ă���O�̃I�u�W�F�N�g����nullptr�ɂ���
		if (pObject->m_pNext != nullptr)
		{
			pObject->m_pNext->m_pPrev = nullptr;
		}
	}
	if (pObject == m_pCur[m_nPriority])
	{
		//�J�����g��������J�����g��O�̃I�u�W�F�N�g�ɂ��炷
		m_pCur[m_nPriority] = pObject->m_pPrev;
		//�����̑O�̃I�u�W�F�N�g�������Ă��鎟�̃I�u�W�F�N�g����nullptr�ɂ���
		if (pObject->m_pPrev != nullptr)
		{
			pObject->m_pPrev->m_pNext = nullptr;
		}
	}



	if (m_pTop[nPriority] == nullptr && m_pCur[nPriority] == nullptr)
	{
		//�O�̃I�u�W�F�N�g��񂪂Ȃ����TOP�ɂ���
		m_pTop[nPriority] = this;
		//���̃I�u�W�F�N�g��񂪂Ȃ����CUR�ɂ���
		m_pCur[nPriority] = this;
		m_pPrev = nullptr;
		m_pNext = nullptr;
	}
	else
	{
		//�O�̃I�u�W�F�N�g��񂪂�������O�̃I�u�W�F�N�g�������Ă�����
		m_pPrev = m_pCur[nPriority];
		//�O�̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g�������̃I�u�W�F�N�g�ɂ���
		m_pCur[nPriority]->m_pNext = this;
		//��ԍŌ�ɂ���
		m_pCur[nPriority] = this;
		m_pNext = nullptr;
	}

	m_nPriority = nPriority;
}
