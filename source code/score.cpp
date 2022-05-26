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
#include "object2D.h"

//================================================
//�}�N����`
//================================================
#define SCORE_CONMA_NUM		(6)		//�R���}���͂��ވʒu
#define SCORE_CONMA_SIZE	(15.0f)	//�R���}�̃T�C�Y
#define SCORE_UNIT_SIZE		(60.0f)	//�P�ʂ̃T�C�Y
#define SCORE_CONMA_POS_X	(5.0f)	//�R���}�̈ʒu�����l
#define SCORE_POS_SHIFT_X	(20.0f)	//�X�R�A�̈ʒu�����炷��

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CScore::CScore(CObject::PRIORITY Priority) :CObject(Priority)
{
	m_nScore = 0;
	memset(m_apNumber, NULL, sizeof(m_apNumber[MAX_SCORE_POLYGON]));
	m_pConma = nullptr;
	m_pUnit = nullptr;
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
		//�����_�����邽�߁ASCORE_COMMA_NUM�ڂ̐������炸�炷
		if (nCntNumber >= SCORE_CONMA_NUM)
		{
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x + SCORE_POS_SHIFT_X - (m_size.x * MAX_SCORE_POLYGON / 2) + (m_size.x * nCntNumber) + (m_size.x / 2.0f), m_pos.y, 0.0f),
												     m_size);
		}
		else
		{
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x - (m_size.x * MAX_SCORE_POLYGON / 2) + (m_size.x * nCntNumber) + (m_size.x / 2.0f), m_pos.y, 0.0f),
												     m_size);
		}
		m_apNumber[nCntNumber]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("number.png"));
	}

	//�R���}�̐���
	m_pConma = CObject2D::Create(D3DXVECTOR3(m_pos.x  - SCORE_CONMA_POS_X - (m_size.x * MAX_SCORE_POLYGON / 2) + (m_size.x * SCORE_CONMA_NUM) + (m_size.x / 2.0f), m_pos.y + m_size.y / 4.0f, 0.0f),
												      D3DXVECTOR3(SCORE_CONMA_SIZE, SCORE_CONMA_SIZE, 0.0f),
		                                              static_cast<int>(CObject::PRIORITY::SCORE));
	m_pConma->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("conma.png"));

	//�P�ʂ̐���
	m_pUnit = CObject2D::Create(D3DXVECTOR3(m_pos.x + SCORE_POS_SHIFT_X - (m_size.x * MAX_SCORE_POLYGON / 2) + (m_size.x * MAX_SCORE_POLYGON) + (m_size.x / 2.0f), m_pos.y, 0.0f),
								     D3DXVECTOR3(SCORE_UNIT_SIZE, SCORE_UNIT_SIZE, 0.0f),
		                                             static_cast<int>(CObject::PRIORITY::SCORE));
	m_pUnit->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("m.png"));

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

	//�R���}�̔j��
	if (m_pConma != nullptr)
	{
		m_pConma->Uninit();
		m_pConma = nullptr;
	}

	//�P�ʂ̔j��
	if (m_pUnit != nullptr)
	{
		m_pUnit->Uninit();
		m_pUnit = nullptr;
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
CScore* CScore::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
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

	//�ő�l�����傫���Ȃ�����
	if (m_nScore > MAX_SCORE)
	{
		//�ő�l�ɂ���
		m_nScore = MAX_SCORE;
	}

	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		if (m_apNumber[nCntNumber] != nullptr)
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
}

//================================================
//�X�R�A���Z����
//================================================
void CScore::AddScore(const int &nValue)
{
	m_nScore += nValue;

	//�ő�l�����傫���Ȃ�����
	if (m_nScore > MAX_SCORE)
	{
		//�ő�l�ɂ���
		m_nScore = MAX_SCORE;
	}

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
CNumber* CScore::GetNumber(const int &nNumber)
{
	return m_apNumber[nNumber];
}