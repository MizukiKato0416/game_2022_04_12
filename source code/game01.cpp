//================================================
//�Q�[��01����
//Author: ��������
//================================================
#include "game01.h"
#include "manager.h"
#include "input_keyboard.h"
#include "player.h"
#include "meshsphere.h"
#include "meshfield.h"
#include "texture.h"
#include "object3D.h"
#include "fade.h"
#include "model_single.h"
#include "play_data.h"
#include "ui.h"
#include "pause.h"
#include "score.h"
#include "time.h"
#include "road.h"
#include "floor.h"

//================================================
//�}�N����`
//================================================

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CGame01::CGame01(CObject::PRIORITY Priority):CObject(Priority)
{
	m_pPlayer = nullptr;
	m_pFloor = nullptr;
	memset(m_apRoad, NULL, sizeof(m_apRoad[GAME01_MAX_ROAD]));
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CGame01::~CGame01()
{
	
}

//================================================
//����������
//================================================
HRESULT CGame01::Init(void)
{
	//�^�C���̐���
	CTime::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, TIME_POLIGON_POSY, 0.0f), D3DXVECTOR3(TIME_POLYGON_WIDTH, TIME_POLYGON_HEIGHT, 0.0f), 0);

	//�X�R�A�̐���
	CScore *pSocre = nullptr;
	pSocre = CScore::Create(D3DXVECTOR3(0.0f + (SCORE_POLYGON_WIDTH * MAX_SCORE_POLYGON / 2.0f), SCORE_POLYGON_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(SCORE_POLYGON_WIDTH, SCORE_POLYGON_HEIGHT, 0.0f));
	CManager::GetInstance()->GetPlayData()->SetScorePoint(pSocre);

	//�|�[�Y�̐���
	CPause::Create();

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f));

	//�X�^�[�g�n�_�̐���
	m_pFloor = CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(FLOOR_SIZE.x, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pFloor->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	//�ŏ��̓��̐���
	m_apRoad[0] = CRoad::Create(D3DXVECTOR3(FLOOR_SIZE.x, 0.0f, 0.0f), FLOOR_SIZE, CModelSingle::HAPPENING_TYPE::NONE, 0.0f);

	return S_OK;
}

//================================================
//�I������
//================================================
void CGame01::Uninit(void)
{
	//�X�R�A��ۑ�
	CManager::GetInstance()->GetPlayData()->SetScore(CManager::GetInstance()->GetPlayData()->GetScorePoint()->GetScore());
	
	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CGame01::Update(void)
{
	//���˂�����
	if (m_pPlayer->GetShot() == true)
	{
		//�X�^�[�g�n�_�̏��������Ă��Ȃ�������
		if (m_pFloor != nullptr)
		{
			//�ʒu�T�C�Y���擾
			D3DXVECTOR3 floorPos = m_pFloor->GetPos();
			D3DXVECTOR3 floorSize = m_pFloor->GetSize();
			//�ʒuX���ړ�������
			floorPos.x += -m_pPlayer->GetMoveForward();
			//�ʒu�ݒ�
			m_pFloor->SetPos(floorPos, floorSize);
		}

		//��Ƀv���C���[���O�ɐi�ޗ͕��t�̕����Ɉړ�������
		for (int nCntRoad = 0; nCntRoad < GAME01_MAX_ROAD; nCntRoad++)
		{
			if (m_apRoad[nCntRoad] != nullptr)
			{
				m_apRoad[nCntRoad]->SetSpeed(-m_pPlayer->GetMoveForward());
			}
		}

		if (m_apRoad[1] != nullptr)
		{
			//��1�̈ʒu���v���C���[�̈ʒu�����������Ȃ�����
			if (m_apRoad[1]->GetPos().x <= m_pPlayer->GetPos().x)
			{
				//��0������
				m_apRoad[0]->Uninit();
				m_apRoad[0] = nullptr;
				//�z������ւ���
				std::swap(m_apRoad[1], m_apRoad[0]);

				//�X�^�[�g�n�_�̏��������Ă��Ȃ�������
				if (m_pFloor != nullptr)
				{
					//����
					m_pFloor->Uninit();
					m_pFloor = nullptr;
				}
			}
		}

		//��0�̈ʒu���v���C���[�̈ʒu�����������Ȃ�����
		if (m_apRoad[0]->GetPos().x <= m_pPlayer->GetPos().x)
		{
			if (m_apRoad[1] == nullptr)
			{
				//�v���C���[�̌��ݒn�����瓹�̌��ݒn������
				D3DXVECTOR3 pos = m_pPlayer->GetPos() - m_apRoad[0]->GetPos();
				//�����ďo��������X�̈ʒu�����炵�ē��𐶐�
				m_apRoad[1] = CRoad::Create(D3DXVECTOR3(FLOOR_SIZE.x - pos.x, 0.0f, 0.0f), FLOOR_SIZE, CModelSingle::HAPPENING_TYPE::NONE, -m_pPlayer->GetMoveForward());
			}
		}
	}

	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//Enter�L�[�A�X�^�[�g�{�^������������
	if (pInputKeyboard->GetTrigger(DIK_LSHIFT) == true)
	{
		//�t�F�[�h�擾����
		CFade *pFade;
		pFade = CManager::GetInstance()->GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE::RESULT);
		}
	}
}

//================================================
//�`�揈��
//================================================
void CGame01::Draw(void)
{

}