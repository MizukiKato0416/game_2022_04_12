//================================================
//�����L���O����
//Authore:��������
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <thread>
#include "renderer.h"
#include "score.h"
#include "manager.h"
#include "ranking.h"
#include "object.h"
#include "play_data.h"
#include "number.h"
#include "result.h"
#include "tcp_client.h"
#include "communicationdata.h"
#include "object2D.h"

//================================================
//�}�N����`
//================================================
#define MAX_COMMUDATA	(64)		//������̍ő�l
#define RANKING_SIZE_Y	(500.0f)	//�����L���O�̕�Y

//================================================
//�ÓI�����o�ϐ��錾
//================================================
CScore *CRanking::m_apScore[MAX_RANKING] = {nullptr};

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CRanking::CRanking(CObject::PRIORITY Priority) :CObject(Priority)
{
	m_pCommu = new CTcpClient;
	m_pCommuData = new CCommunicationData;
	for (int nCntRanking = 0; nCntRanking < MAX_SCORE_DATA; nCntRanking++)
	{
		m_nScore[nCntRanking] = 0;
	}
	m_nNowScore = 0;
	m_col = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_bConnect = false;
	m_bOnece = false;
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
	thread th(Connect, m_pCommu, m_pCommuData, m_pos, m_size, &m_bConnect, &m_bOnece);

	th.detach();

	m_nNowScore = CManager::GetInstance()->GetPlayData()->GetScore();

	//�J���[�̐ݒ�
	m_col = {255.0f, 255.0f, 255.0f, 255.0f};

	return S_OK;
}

//================================================
//�I������
//================================================
void CRanking::Uninit(void)
{
	m_pCommu->Uninit();
	Release();
}

//================================================
//�X�V����
//================================================
void CRanking::Update(void)
{
	CCommunicationData::COMMUNICATION_DATA *pData = m_pCommuData->GetCommuData();

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		if (m_apScore[nCntRanking] != nullptr && m_bOnece == true)
		{
			m_apScore[nCntRanking]->SetScore(pData->ranking[nCntRanking]);
 			m_nScore[nCntRanking] = pData->ranking[nCntRanking];
			if (m_nNowScore != 0 && m_nScore[nCntRanking] == m_nNowScore)
			{
				//�J���[�𔖂�����
				m_col.a -= 10.0f;

				if (m_col.a < 0.0f)
				{
					m_col.a = 255.0f;
				}

				for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
				{
					//�i���o�[���擾���ăJ���[��ݒ�
					m_apScore[nCntRanking]->GetNumber(nCntNumber)->SetCol(m_col);
					m_apScore[nCntRanking]->GetConma()->SetCol(m_col);
					m_apScore[nCntRanking]->GetMeter()->SetCol(m_col);
				}
				break;
			}
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
//�����L���O��������
//================================================
void CRanking::CreateScore(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�X�R�A�̐���
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		CObject2D *pNumber;

		m_apScore[nCntRanking] = CScore::Create(D3DXVECTOR3((pos.x), pos.y + ((float)(RANKING_SIZE_Y / (MAX_RANKING + 1)) * nCntRanking + (float)(RANKING_SIZE_Y / (MAX_RANKING + 1))), 0.0f),
			size);

		switch (nCntRanking)
		{
		case 0:
			pNumber = CObject2D::Create(D3DXVECTOR3(((pos.x - ((MAX_SCORE_POLYGON / 2) * size.x) - 50.0f)), pos.y + ((float)(RANKING_SIZE_Y / (MAX_RANKING + 1)) * nCntRanking + (float)(RANKING_SIZE_Y / (MAX_RANKING + 1))), 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), static_cast<int>(CObject::PRIORITY::RANKING));
			pNumber->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("1st.png"));
			break;
		case 1:
			pNumber = CObject2D::Create(D3DXVECTOR3(((pos.x - ((MAX_SCORE_POLYGON / 2) * size.x) - 50.0f)), pos.y + ((float)(RANKING_SIZE_Y / (MAX_RANKING + 1)) * nCntRanking + (float)(RANKING_SIZE_Y / (MAX_RANKING + 1))), 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), static_cast<int>(CObject::PRIORITY::RANKING));
			pNumber->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("2nd.png"));
			break;
		case 2:
			pNumber = CObject2D::Create(D3DXVECTOR3(((pos.x - ((MAX_SCORE_POLYGON / 2) * size.x) - 50.0f)), pos.y + ((float)(RANKING_SIZE_Y / (MAX_RANKING + 1)) * nCntRanking + (float)(RANKING_SIZE_Y / (MAX_RANKING + 1))), 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), static_cast<int>(CObject::PRIORITY::RANKING));
			pNumber->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("3rd.png"));
			break;
		case 3:
			pNumber = CObject2D::Create(D3DXVECTOR3(((pos.x - ((MAX_SCORE_POLYGON / 2) * size.x) - 50.0f)), pos.y + ((float)(RANKING_SIZE_Y / (MAX_RANKING + 1)) * nCntRanking + (float)(RANKING_SIZE_Y / (MAX_RANKING + 1))), 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), static_cast<int>(CObject::PRIORITY::RANKING));
			pNumber->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("4th.png"));
			break;
		case 4:
			pNumber = CObject2D::Create(D3DXVECTOR3(((pos.x - ((MAX_SCORE_POLYGON / 2) * size.x) - 50.0f)), pos.y + ((float)(RANKING_SIZE_Y / (MAX_RANKING + 1)) * nCntRanking + (float)(RANKING_SIZE_Y / (MAX_RANKING + 1))), 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), static_cast<int>(CObject::PRIORITY::RANKING));
			pNumber->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("5th.png"));
			break;
		case 5:
			pNumber = CObject2D::Create(D3DXVECTOR3(((pos.x - ((MAX_SCORE_POLYGON / 2) * size.x) - 50.0f)), pos.y + ((float)(RANKING_SIZE_Y / (MAX_RANKING + 1)) * nCntRanking + (float)(RANKING_SIZE_Y / (MAX_RANKING + 1))), 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), static_cast<int>(CObject::PRIORITY::RANKING));
			pNumber->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("6th.png"));
			break;
		default:
			break;
		}
	}
}

//================================================
//��������
//================================================
CRanking* CRanking::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
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

//================================================
//�ʐM����
//================================================
void CRanking::Connect(CTcpClient *pCommu, CCommunicationData *pCommuData, D3DXVECTOR3 pos, D3DXVECTOR3 size, bool *bConnect, bool *bOnece)
{
	CCommunicationData::COMMUNICATION_DATA *pData = pCommuData->GetCommuData();
	int nScore = CManager::GetPlayData()->GetScore();
	char Send_Data[MAX_COMMUDATA];
	char recv_data[MAX_COMMUDATA];
	bool connect = false;

	pCommu->Init();

	connect = pCommu->Connect();

	if (connect == true)
	{
		*bConnect = true;
		CreateScore(pos, size);
		memcpy(&Send_Data, &nScore, sizeof(nScore));
		pCommu->Send(&Send_Data[0], sizeof(int));

		pCommu->Recv(&recv_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA::ranking));
		memcpy(&pData->ranking, recv_data, sizeof(CCommunicationData::COMMUNICATION_DATA::ranking));

		//�X�R�A�̐ݒ�
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			m_apScore[nCntRanking]->SetScore(pData->ranking[nCntRanking]);
		}
	}
	else if (connect == false)
	{
		*bConnect = false;
		CreateScore(pos, size);
		//�X�R�A�̐ݒ�
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			m_apScore[nCntRanking]->SetScore(0);
		}
	}

	*bOnece = true;

	pCommu->Uninit();
}