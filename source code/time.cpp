//================================================
//�^�C������
//Author:��������
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "renderer.h"
#include "time.h"
#include "manager.h"
#include "number.h"
#include "ui.h"
#include "play_data.h"
#include "texture.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CTime::CTime(CObject::PRIORITY Priority) : CObject(Priority)
{
	m_nTime = 0;
	m_nCounter = 0;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CTime::~CTime()
{

}

//================================================
//����������
//================================================
HRESULT CTime::Init(void)
{
	m_nCounter = 0;

	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
	{
		m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x - (m_size.x * MAX_TIME_POLYGON / 2) + (m_size.x * nCntNumber) + (m_size.x / 2.0f), m_pos.y, 0.0f), m_size);
		m_apNumber[nCntNumber]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("number.png"));
	}
	return S_OK;
}

//================================================
//�I������
//================================================
void CTime::Uninit(void)
{
	//���Ԃ�ۑ�
	CManager::GetInstance()->GetPlayData()->SetTime(m_nTime);

	//�i���o�[�̔j��
	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
	{
		if (m_apNumber[nCntNumber] != NULL)
		{
			m_apNumber[nCntNumber]->Uninit();
			delete m_apNumber[nCntNumber];
			m_apNumber[nCntNumber] = NULL;
		}
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CTime::Update(void)
{
	//�J�E���^�[�����Z
	m_nCounter++;

	//�J�E���^�[60����1�b�o�߂�����
	if (m_nCounter % 60 == 0)
	{
		AddTime(1);
	}
}

//================================================
//�`�揈��
//================================================
void CTime::Draw(void)
{
	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
	{
		m_apNumber[nCntNumber]->Draw();
	}
}

//================================================
//��������
//================================================
CTime* CTime::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const int &nStartTime)
{
	//�C���X�^���X�̐���
	CTime *pTime = NULL;
	if (pTime == NULL)
	{
		pTime = new CTime;
		if (pTime != NULL)
		{
			pTime->m_nTime = nStartTime;
			pTime->m_pos = pos;
			pTime->m_size = size;
			pTime->Init();
			pTime->SetTime(pTime->m_nTime);
		}
	}
	return pTime;
}

//================================================
//�X�R�A�擾����
//================================================
int CTime::GetTime(void)
{
	return m_nTime;
}

//================================================
//�X�R�A�ݒ菈��
//================================================
void CTime::SetTime(const int &nTime)
{
	m_nTime = nTime;

	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
	{
		if (nCntNumber == 0)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nTime / (int)powf(10, MAX_TIME_POLYGON - 1));
		}
		else if (nCntNumber == MAX_TIME_POLYGON - 1)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nTime % 10);
		}
		else
		{
			m_apNumber[nCntNumber]->SetNumber(m_nTime % (int)powf(10, MAX_TIME_POLYGON - (float)nCntNumber) / (int)powf(10, MAX_TIME_POLYGON - 1 - (float)nCntNumber));
		}
	}
}

//================================================
//�X�R�A���Z����
//================================================
void CTime::AddTime(const int &nValue)
{
	m_nTime += nValue;

	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
	{
		if (nCntNumber == 0)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nTime / (int)powf(10, MAX_TIME_POLYGON - 1));
		}
		else if (nCntNumber == MAX_TIME_POLYGON - 1)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nTime % 10);
		}
		else
		{
			m_apNumber[nCntNumber]->SetNumber(m_nTime % (int)powf(10, MAX_TIME_POLYGON - (float)nCntNumber) / (int)powf(10, MAX_TIME_POLYGON - 1 - (float)nCntNumber));
		}
	}
}

//=============================================================================
// number�擾����
//=============================================================================
CNumber* CTime::GetNumber(int nNumber)
{
	return m_apNumber[nNumber];
}