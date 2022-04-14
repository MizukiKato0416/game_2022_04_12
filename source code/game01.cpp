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
#define GAME01_ROAD_SPEED		(-10.0f)		//�����i�ރX�s�[�h

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

	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f));

	m_pFloor = CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2000.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pFloor->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_apRoad[0] = CRoad::Create(D3DXVECTOR3(2000.0f, 0.0f, 0.0f), CRoad::HAPPENING_TYPE::NONE, 0.0f);

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
		//�ʒu�T�C�Y���擾
		D3DXVECTOR3 floorPos = m_pFloor->GetPos();
		D3DXVECTOR3 floorSize = m_pFloor->GetSize();
		//�ʒuX���ړ�������
		floorPos.x += GAME01_ROAD_SPEED;
		//�ʒu�ݒ�
		m_pFloor->SetPos(floorPos, floorSize);

		//���̈ړ��ʂ�0��������ړ�������
		if (m_apRoad[0]->GetSpeed() == 0.0f)
		{
			m_apRoad[0]->SetSpeed(GAME01_ROAD_SPEED);
		}

		//��0�̈ʒu���v���C���[�̈ʒu�����������Ȃ�����
		if (m_apRoad[0]->GetPos() <= m_pPlayer->GetPos)
		{
			if (m_apRoad[1] == nullptr)
			{
				m_apRoad[1] = CRoad::Create(D3DXVECTOR3(2000.0f, 0.0f, 0.0f), CRoad::HAPPENING_TYPE::NONE, 0.0f);
			}
		}



	}











	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//Enter�L�[�A�X�^�[�g�{�^������������
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
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