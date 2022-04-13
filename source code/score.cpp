//================================================
//�X�R�A����
//Authore:��������
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "renderer.h"
#include "score.h"
#include "manager.h"
#include "number.h"
#include "play_data.h"
#include "texture.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CScore::CScore(CObject::PRIORITY Priority) :CObject(Priority)
{
	m_nScore = 0;
	memset(m_apNumber, NULL, sizeof(m_apNumber[MAX_SCORE_POLYGON]));
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CScore::~CScore()
{

}

//================================================
//����������
//================================================
HRESULT CScore::Init()
{
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x - (m_size.x * MAX_SCORE_POLYGON / 2) + (m_size.x * nCntNumber) + (m_size.x / 2.0f), m_pos.y, 0.0f),
												 m_size);
		m_apNumber[nCntNumber]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_NUMBER"));
	}
	return S_OK;
}

//================================================
//�I������
//================================================
void CScore::Uninit(void)
{
	//�v���C�f�[�^�̎擾
	CPlayData *pPlayData = NULL;
	pPlayData = CManager::GetInstance()->GetPlayData();

	//�X�R�A���v���C�f�[�^�ɕۑ�
	pPlayData->SetScore(m_nScore);

	//�i���o�[�̔j��
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		if (m_apNumber[nCntNumber] != nullptr)
		{
			m_apNumber[nCntNumber]->Uninit();
			delete m_apNumber[nCntNumber];
			m_apNumber[nCntNumber] = nullptr;
		}
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CScore::Update(void)
{
	
}

//================================================
//�`�揈��
//================================================
void CScore::Draw(void)
{
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		m_apNumber[nCntNumber]->Draw();
	}
}

//================================================
//��������
//================================================
CScore* CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X�̐���
	CScore *pScore = NULL;
	if (pScore == NULL)
	{
		pScore = new CScore;
		if (pScore != NULL)
		{
			pScore->m_pos = pos;
			pScore->m_size = size;
			pScore->Init();
		}
	}
	return pScore;
}

//================================================
//�X�R�A�擾����
//================================================
int CScore::GetScore(void)
{
	return m_nScore;
}

//================================================
//�X�R�A�ݒ菈��
//================================================
void CScore::SetScore(const int &nScore)
{
	m_nScore = nScore;

	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		if (nCntNumber == 0)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nScore / (int)powf(10, MAX_SCORE_POLYGON - 1));
		}
		else if (nCntNumber == MAX_SCORE_POLYGON - 1)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nScore % 10);
		}
		else
		{
			m_apNumber[nCntNumber]->SetNumber(m_nScore % (int)powf(10, MAX_SCORE_POLYGON - nCntNumber) / (int)powf(10, MAX_SCORE_POLYGON - 1 - nCntNumber));
		}
	}
}

//================================================
//�X�R�A���Z����
//================================================
void CScore::AddScore(const int &nValue)
{
	m_nScore += nValue;

	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		if (nCntNumber == 0)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nScore / (int)powf(10, MAX_SCORE_POLYGON - 1));
		}
		else if (nCntNumber == MAX_SCORE_POLYGON - 1)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nScore % 10);
		}
		else
		{
			m_apNumber[nCntNumber]->SetNumber(m_nScore % (int)powf(10, MAX_SCORE_POLYGON - nCntNumber) / (int)powf(10, MAX_SCORE_POLYGON - 1 - nCntNumber));
		}
	}
}

//=============================================================================
// number�擾����
//=============================================================================
CNumber* CScore::GetNumber(int nNumber)
{
	return m_apNumber[nNumber];
}