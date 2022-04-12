//================================================
//�����L���O����
//Authore:��������
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "renderer.h"
#include "score.h"
#include "manager.h"
#include "ranking.h"
#include "object.h"
#include "play_data.h"
#include "number.h"
#include "result.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CRanking::CRanking(CObject::PRIORITY Priority) :CObject(Priority)
{
	for (int nCntRanking = 0; nCntRanking < MAX_SCORE_DATA; nCntRanking++)
	{
		m_nScore[nCntRanking] = 0;
	}
	memset(m_apScore, NULL, sizeof(m_apScore[MAX_RANKING]));
	m_nNowScore = 0;
	m_col = { 0.0f, 0.0f, 0.0f, 0.0f };
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CRanking::~CRanking()
{

}

//================================================
//����������
//================================================
HRESULT CRanking::Init(void)
{
	//�X�R�A�̐���
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_apScore[nCntRanking] = CScore::Create(D3DXVECTOR3((m_pos.x), (float)(SCREEN_HEIGHT / (MAX_RANKING + 1)) * nCntRanking + (float)(SCREEN_HEIGHT / (MAX_RANKING + 1)), 0.0f),
											    m_size);
	}

	//���[�h����
	FILE *pFile;
	pFile = fopen("data/ranking.txt", "r");
	if (pFile != NULL)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			fscanf(pFile, "%d", &m_nScore[nCntRanking]);
		}
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���\n");
	}
	fclose(pFile);

	//�v���C�f�[�^�ɕۑ����Ă��鍡��̃X�R�A��ϐ��ɕۑ�
	m_nScore[MAX_SCORE_DATA - 1] = CManager::GetInstance()->GetPlayData()->GetScore() - CManager::GetInstance()->GetPlayData()->GetTime() * 100;
	m_nNowScore = CManager::GetInstance()->GetPlayData()->GetScore() - CManager::GetInstance()->GetPlayData()->GetTime() * 100;


	//�\�[�g
	for (int nCntRanking = 0; nCntRanking < MAX_SCORE_DATA; nCntRanking++)
	{
		for (int nCntRanking2 = 0; nCntRanking2 < MAX_SCORE_DATA - 1; nCntRanking2++)
		{
			//�����ŕ��ׂ�
			if ((m_nScore[nCntRanking2] < m_nScore[nCntRanking2 + 1] && m_nScore[nCntRanking2 + 1] != 0) || m_nScore[nCntRanking2] == 0)
			{
				int nScore = m_nScore[nCntRanking2];
				m_nScore[nCntRanking2] = m_nScore[nCntRanking2 + 1];
				m_nScore[nCntRanking2 + 1] = nScore;
			}
		}
	}

	//�X�R�A�̐ݒ�
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_apScore[nCntRanking]->SetScore(m_nScore[nCntRanking]);
	}

	//�Z�[�u����
	pFile = fopen("data/ranking.txt", "w");
	if (pFile != NULL)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			fprintf(pFile, "%d\n", m_apScore[nCntRanking]->GetScore());
		}
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���\n");
	}
	fclose(pFile);

	//�J���[�̐ݒ�
	m_col = {255.0f, 255.0f, 255.0f, 255.0f};

	return S_OK;
}

//================================================
//�I������
//================================================
void CRanking::Uninit(void)
{
	Release();
}

//================================================
//�X�V����
//================================================
void CRanking::Update(void)
{
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		if (m_nNowScore != 0 && m_nScore[nCntRanking] == m_nNowScore)
		{
			//�J���[�𔖂�����
			m_col.a -= 255.0f;

			if (m_col.a < 0.0f)
			{
				m_col.a = 255.0f;
			}

			for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
			{
				//�i���o�[���擾���ăJ���[��ݒ�
				m_apScore[nCntRanking]->GetNumber(nCntNumber)->SetCol(m_col);
			}
			break;
		}
	}
}

//================================================
//�`�揈��
//================================================
void CRanking::Draw(void)
{
	
}

//================================================
//��������
//================================================
CRanking* CRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X�̐���
	CRanking *pRanking = NULL;
	if (pRanking == NULL)
	{
		pRanking = new CRanking;
		if (pRanking != NULL)
		{
			pRanking->m_pos = pos;
			pRanking->m_size = size;
			pRanking->Init();
		}
	}
	return pRanking;
}

