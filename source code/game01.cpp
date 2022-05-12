//================================================
//�Q�[��01����
//Author: ��������
//================================================
#include "game01.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_mouse.h"
#include "player.h"
#include "meshsphere.h"
#include "meshfield.h"
#include "texture.h"
#include "object3D.h"
#include "object2D.h"
#include "fade.h"
#include "model_single.h"
#include "play_data.h"
#include "ui.h"
#include "pause.h"
#include "score.h"
#include "time.h"
#include "road.h"
#include "floor.h"
#include "camera.h"
#include "gauge.h"
#include "bg.h"

//================================================
//�}�N����`
//================================================
#define GAME01_MOUSE_VEC_ADJUSTMENT_0		(0.4f)		//�����������Ƃ��̃x�N�g�������������銄��0
#define GAME01_MOUSE_VEC_ADJUSTMENT_1		(0.5f)		//�����������Ƃ��̃x�N�g�������������銄��1
#define GAME01_MOUSE_VEC_ADJUSTMENT_2		(0.6f)		//�����������Ƃ��̃x�N�g�������������銄��2
#define GAME01_MOUSE_VEC_ADJUSTMENT_3		(0.7f)		//�����������Ƃ��̃x�N�g�������������銄��3
#define GAME01_MOUSE_VEC_ADJUSTMENT_4		(0.8f)		//�����������Ƃ��̃x�N�g�������������銄��4
#define GAME01_MOUSE_VEC_ADJUSTMENT_5		(0.9f)		//�����������Ƃ��̃x�N�g�������������銄��5
#define GAME01_MOUSE_VEC_ADJUSTMENT_6		(1.0f)		//�����������Ƃ��̃x�N�g�������������銄��6
#define GAME01_CAMERA_ADD_POS				(10.0f)		//�J�����̈ʒu�����Z�����
#define GAME01_CAMERA_ADD_DIFFER			(10.0f)		//�J�����̎��_�ƒ����_�̋��������Z�����
#define GAME01_CAMERA_VIEW_CHANGE_MOVE		(20.0f)		//�J�����������DEFAULT����ő�ɕς��鋫�E���̃v���C���[�̃o�E���h����u�Ԃ̈ړ���
#define GAME01_SCORE_MAGNIFICATION			(10.0f)		//�v���C���[���O�ɐi�ޗ͂��X�R�A�ɂ���ۂ̔{��
#define GAME01_SHOT_GAUGE_MAX				(100)		//�V���b�g�Q�[�W�̍ő�l
#define GAME01_SHOT_GAUGE_ADD				(2)			//�V���b�g�Q�[�W�𑝂₷��
#define GAME01_SHOT_GAUGE_COUNTER_MAX		(10)		//�V���b�g�Q�[�W���ő�܂ł��܂��Ă����Ԃ̎���
#define GAME01_SHOT_GAUGE_CASE_1			(20)		//�V���b�g�Q�[�W�̒i�K1
#define GAME01_SHOT_GAUGE_CASE_2			(40)		//�V���b�g�Q�[�W�̒i�K2
#define GAME01_SHOT_GAUGE_CASE_3			(60)		//�V���b�g�Q�[�W�̒i�K3
#define GAME01_SHOT_GAUGE_CASE_4			(80)		//�V���b�g�Q�[�W�̒i�K4
#define GAME01_SHOT_GAUGE_SUBTRACT_ALPHA	(0.02f)		//�V���b�g�Q�[�W�𔖂������
#define GAME01_BG_SIZE_ADJUSTMENT			(3.0f)		//�w�i�̑傫�����銄��
#define GAME01_BG_POS_Z						(1000.0f)	//�w�i�̈ʒuZ
#define GAME01_BG_POS_Y						(300.0f)	//�w�i�̈ʒuY
#define GAME01_BG_1_MAGNIFICATION			(0.00004f)	//�w�i1���O�ɐi�ޗ͂�w�i�̈ړ��ɂ���ۂ̔{��
#define GAME01_BG_2_MAGNIFICATION			(0.00006f)	//�w�i2���O�ɐi�ޗ͂�w�i�̈ړ��ɂ���ۂ̔{��
#define GAME01_BG_3_MAGNIFICATION			(0.00008f)	//�w�i3���O�ɐi�ޗ͂�w�i�̈ړ��ɂ���ۂ̔{��
#define GAME01_BG_1_MOVE_INIT				(0.00006f)	//�w�i1�̏����ړ���
#define GAME01_BG_2_MOVE_INIT				(0.00008f)	//�w�i2�̏����ړ���
#define GAME01_BG_3_MOVE_INIT				(0.0001f)	//�w�i3�̏����ړ���


#ifdef _DEBUG
#define GAME01_MOUSE_VEC_ADJUSTMENT_DEBUG	(0.08f)		//�����������Ƃ��̃x�N�g�������������銄���f�o�b�O�p
#endif // !_DEBUG


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
	memset(m_pBg, NULL, sizeof(m_pBg[GAME01_MAX_BG]));
	m_mouseTriggerPos = { 0.0f, 0.0f, 0.0f };
	m_pGauge = nullptr;
	m_nGaugeCounter = 0;
	m_pGaugeFrame = nullptr;
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
	//�ϐ��̏�����
	m_mouseTriggerPos = { 0.0f, 0.0f, 0.0f };
	m_nGaugeCounter = 0;

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
	m_pFloor = CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), FLOOR_SIZE, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pFloor->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	//�ŏ��̓��̐���
	m_apRoad[0] = CRoad::Create(D3DXVECTOR3(FLOOR_SIZE.x, 0.0f, 0.0f), FLOOR_SIZE, 0.0f);

	//�Q�[�W�̃t���[������
	m_pGaugeFrame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
		                              static_cast<int>(CObject::PRIORITY::UI));
	m_pGaugeFrame->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_GAUGE_FRAME"));

	//�V���b�g�Q�[�W�̐���
	m_pGauge = CGauge::Create(D3DXVECTOR3(GAUGE_SHOT_POS_X, GAUGE_SHOT_POS_Y, 0.0f),
		                      D3DXVECTOR3(GAUGE_SHOT_SIZE_X, GAUGE_SHOT_SIZE_Y, 0.0f), GAME01_SHOT_GAUGE_MAX, 0);
	m_pGauge->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_GAUGE"));

	//�w�i1�̐���
	m_pBg[0] = CBg::Create(D3DXVECTOR3(0.0f, GAME01_BG_POS_Y, GAME01_BG_POS_Z),
		                   D3DXVECTOR3(SCREEN_WIDTH * GAME01_BG_SIZE_ADJUSTMENT, SCREEN_HEIGHT * GAME01_BG_SIZE_ADJUSTMENT, 0.0f),
		                   D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(GAME01_BG_1_MOVE_INIT, 0.0f));
	m_pBg[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_SKY_01"));

	//�w�i2�̐���
	m_pBg[1] = CBg::Create(D3DXVECTOR3(0.0f, GAME01_BG_POS_Y, GAME01_BG_POS_Z),
		                   D3DXVECTOR3(SCREEN_WIDTH * GAME01_BG_SIZE_ADJUSTMENT, SCREEN_HEIGHT * GAME01_BG_SIZE_ADJUSTMENT, 0.0f),
		                   D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(GAME01_BG_2_MOVE_INIT, 0.0f));
	m_pBg[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_SKY_02"));

	//�w�i3�̐���
	m_pBg[2] = CBg::Create(D3DXVECTOR3(0.0f, GAME01_BG_POS_Y, GAME01_BG_POS_Z),
		                   D3DXVECTOR3(SCREEN_WIDTH * GAME01_BG_SIZE_ADJUSTMENT, SCREEN_HEIGHT * GAME01_BG_SIZE_ADJUSTMENT, 0.0f),
		                   D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(GAME01_BG_3_MOVE_INIT, 0.0f));
	m_pBg[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_SKY_03"));
	

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
		if (m_pGaugeFrame != nullptr && m_pGauge != nullptr)
		{
			//�Q�[�W����������
			UninitGauge();
		}

		//�J�����̏���
		Camera();

		//���̏���
		Road();

		//�v���C���[���O�ɐi�ޗ͂��擾
		float fScoreMoveForward = m_pPlayer->GetMoveForward();

		//�O�ɐi�ޗ͂����̐���������
		if (fScoreMoveForward < 0.0f)
		{
			//0�ɂ���
			fScoreMoveForward = 0.0f;
		}
		else if(fScoreMoveForward > 0.0f)
		{//�O�ɐi�ޗ͂����̐���������
			//�O�ɐi�ޗ͂�����̔{���傫������
			fScoreMoveForward *= GAME01_SCORE_MAGNIFICATION;
		}

		//�w�i��UV���W���v���C���[���O�ɐi�ޗ͕��ړ�������
		m_pBg[0]->SetUvMove(D3DXVECTOR2(GAME01_BG_1_MOVE_INIT + m_pPlayer->GetMoveForward() * GAME01_BG_1_MAGNIFICATION, 0.0f));
		m_pBg[1]->SetUvMove(D3DXVECTOR2(GAME01_BG_2_MOVE_INIT + m_pPlayer->GetMoveForward() * GAME01_BG_2_MAGNIFICATION, 0.0f));
		m_pBg[2]->SetUvMove(D3DXVECTOR2(GAME01_BG_3_MOVE_INIT + m_pPlayer->GetMoveForward() * GAME01_BG_3_MAGNIFICATION, 0.0f));
		

		//�X�R�A���v���C���[���O�ɐi�ޗ͕����Z
		CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore((int)fScoreMoveForward);
	}
	else
	{//���˂��Ă��Ȃ�������
		//�Q�[�W����
		Gauge();
	}

	//���ˏ���
	Shot();

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

//================================================
//�J�����̏���
//================================================
void CGame01::Camera(void)
{
	//�J�����̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
	CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
	//camera�̎擾
	CCamera* pCamera = &**pCameraAddress;

	//�v���C���[�̒��˂�ʂɂ���ăJ�����̈ʒu�Ǝ����ς���
	if (m_pPlayer->GetBoundMove() > GAME01_CAMERA_VIEW_CHANGE_MOVE)
	{
		//����̒l�����������Ƃ�
		if (pCamera->GetDiffer() < CAMERA_DISTANCE_MAX)
		{
			//�J�����̎��_�ƒ����_�̋������L������
			pCamera->AddDiffer(GAME01_CAMERA_ADD_DIFFER);
			//�K��l�����傫���Ȃ�����
			if (pCamera->GetDiffer() > CAMERA_DISTANCE_MAX)
			{
				//�J�����̎��_�ƒ����_�̋�����ݒ�
				pCamera->SetDiffer(CAMERA_DISTANCE_MAX);
			}
		}

		//����̒l�����������Ƃ�
		if (pCamera->GetPosR().y < CAMERA_MAX_POS.y)
		{
			//�J�����̒����_�̈ʒu���擾
			D3DXVECTOR3 posR = pCamera->GetPosR();
			//�����_�̈ʒu���ړ�
			posR.y += GAME01_CAMERA_ADD_POS;
			//�K��l�����傫���Ȃ�����
			if (posR.y > CAMERA_MAX_POS.y)
			{
				//����̒l�ɂ���
				posR.y = CAMERA_MAX_POS.y;
			}
			//�����_�̈ʒu��ݒ�
			pCamera->SetPosR(posR);
		}
	}
	else if (m_pPlayer->GetBoundMove() <= GAME01_CAMERA_VIEW_CHANGE_MOVE)
	{
		//����̒l�����傫���Ƃ�
		if (pCamera->GetDiffer() > CAMERA_DISTANCE_DEFAULT)
		{
			//�J�����̎��_�ƒ����_�̋�������������
			pCamera->AddDiffer(-GAME01_CAMERA_ADD_DIFFER);
			//�K��l�����������Ȃ�����
			if (pCamera->GetDiffer() < CAMERA_DISTANCE_DEFAULT)
			{
				//�J�����̎��_�ƒ����_�̋�����ݒ�
				pCamera->SetDiffer(CAMERA_DISTANCE_DEFAULT);
			}
		}
		else if (pCamera->GetDiffer() < CAMERA_DISTANCE_DEFAULT)
		{//����̒l�����������Ƃ�
		 //�J�����̎��_�ƒ����_�̋������L������
			pCamera->AddDiffer(GAME01_CAMERA_ADD_DIFFER);
			//�K��l�����傫���Ȃ�����
			if (pCamera->GetDiffer() > CAMERA_DISTANCE_DEFAULT)
			{
				//�J�����̎��_�ƒ����_�̋�����ݒ�
				pCamera->SetDiffer(CAMERA_DISTANCE_DEFAULT);
			}
		}

		//����̒l�����傫���Ƃ�
		if (pCamera->GetPosR().y > CAMERA_DEFAULT_POS.y)
		{
			//�J�����̒����_�̈ʒu���擾
			D3DXVECTOR3 posR = pCamera->GetPosR();
			//�����_�̈ʒu���ړ�
			posR.y -= GAME01_CAMERA_ADD_POS;
			//�K��l�����������Ȃ�����
			if (posR.y < CAMERA_DEFAULT_POS.y)
			{
				//����̒l�ɂ���
				posR.y = CAMERA_DEFAULT_POS.y;
			}
			//�����_�̈ʒu��ݒ�
			pCamera->SetPosR(posR);
		}
		else if (pCamera->GetPosR().y < CAMERA_DEFAULT_POS.y)
		{//����̒l�����������Ƃ�
		 //�J�����̒����_�̈ʒu���擾
			D3DXVECTOR3 posR = pCamera->GetPosR();
			//�����_�̈ʒu���ړ�
			posR.y += GAME01_CAMERA_ADD_POS;
			//�K��l�����傫���Ȃ�����
			if (posR.y > CAMERA_DEFAULT_POS.y)
			{
				//����̒l�ɂ���
				posR.y = CAMERA_DEFAULT_POS.y;
			}
			//�����_�̈ʒu��ݒ�
			pCamera->SetPosR(posR);
		}
	}
}

//================================================
//���̏���
//================================================
void CGame01::Road(void)
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
			m_apRoad[1] = CRoad::Create(D3DXVECTOR3(FLOOR_SIZE.x - pos.x, 0.0f, 0.0f), FLOOR_SIZE, -m_pPlayer->GetMoveForward());
		}
	}
}

//================================================
//�Q�[�W����
//================================================
void CGame01::Gauge(void)
{
	//�Q�[�W�𑝂₷
	m_pGauge->AddGauge(GAME01_SHOT_GAUGE_ADD);

	//�Q�[�W���ő�܂ł��܂�����
	if (m_pGauge->GetGauge() == m_pGauge->GetMaxNum())
	{
		//�J�E���^�[�����Z
		m_nGaugeCounter++;
		//����̒l���傫���Ȃ�����
		if (m_nGaugeCounter > GAME01_SHOT_GAUGE_COUNTER_MAX)
		{
			//0�ɂ���
			m_nGaugeCounter = 0;
			//�Q�[�W��0�ɂ���
			m_pGauge->SetGauge(0);
		}
	}
}

//================================================
//�Q�[�W����������
//================================================
void CGame01::UninitGauge(void)
{
	//�Q�[�W�Ƃ��̃t���[���̐F�擾
	D3DXCOLOR gaugeFrameCol = m_pGaugeFrame->GetCol();
	D3DXCOLOR gaugeCol = m_pGauge->GetCol();

	//�Q�[�W�Ƃ��̃t���[�������X�ɔ�������
	gaugeFrameCol.a -= GAME01_SHOT_GAUGE_SUBTRACT_ALPHA;
	gaugeCol.a -= GAME01_SHOT_GAUGE_SUBTRACT_ALPHA;

	//�����Ȃ��Ȃ�����
	if (gaugeFrameCol.a <= 0.0f || gaugeCol.a <= 0.0f)
	{
		//0�ɂ���
		gaugeFrameCol.a = 0.0f;
		gaugeCol.a = 0.0f;

		//����
		m_pGaugeFrame->Uninit();
		m_pGauge->Uninit();

		m_pGaugeFrame = nullptr;
		m_pGauge = nullptr;
	}
	else
	{
		//�F�̐ݒ�
		m_pGaugeFrame->SetCol(gaugeFrameCol);
		m_pGauge->SetCol(gaugeCol);
	}
}

//================================================
//���ˏ���
//================================================
void CGame01::Shot(void)
{
#ifdef _DEBUG
	if (m_pPlayer->GetShot() == true)
	{
		//�}�E�X�擾����
		CInputMouse *pInputMouse;
		pInputMouse = CManager::GetInstance()->GetInputMouse();

		//�}�E�X���������u��
		if (pInputMouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			//�}�E�X�̈ʒu�擾
			POINT mouseTriggerPos;
			GetCursorPos(&mouseTriggerPos);
			ScreenToClient(CManager::GetWindowHandle(), &mouseTriggerPos);

			//�}�E�X�̈ʒu��ۑ�
			m_mouseTriggerPos.x = (float)mouseTriggerPos.x;
			m_mouseTriggerPos.y = (float)mouseTriggerPos.y;
		}

		//�}�E�X�𗣂����u��
		if (pInputMouse->GetRelease(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			//�}�E�X�̈ʒu�擾
			POINT mouseReleasePos;
			GetCursorPos(&mouseReleasePos);
			ScreenToClient(CManager::GetWindowHandle(), &mouseReleasePos);

			//�}�E�X���N���b�N�����ʒu���痣�����ʒu�܂ł̃x�N�g�����Z�o
			D3DXVECTOR3 mousePosVec = D3DXVECTOR3(m_mouseTriggerPos.x - mouseReleasePos.x, m_mouseTriggerPos.y - mouseReleasePos.y, 0.0f);
			//�x�N�g����y���t�����ɂ���
			mousePosVec.y *= -1.0f;
			//�x�N�g��������̊�������������
			mousePosVec *= GAME01_MOUSE_VEC_ADJUSTMENT_DEBUG;

			//���˂��Ă����Ԃɂ���
			m_pPlayer->SetShot(true);
			//�W�����v�ʐݒ�
			m_pPlayer->SetJump(mousePosVec.y);
			//�O�ɐi�ޗ͂�ݒ�
			m_pPlayer->SetMoveForward(mousePosVec.x);
			//�o�E���h����u�Ԃ̈ړ��ʂɐݒ�
			m_pPlayer->SetBoundMove(mousePosVec.y);
		}
	}
#endif // !_DEBUG

	if (m_pPlayer->GetShot() == false)
	{//���˂��Ă��Ȃ���ԂȂ�
		//�}�E�X�擾����
		CInputMouse *pInputMouse;
		pInputMouse = CManager::GetInstance()->GetInputMouse();

		//�}�E�X���������u��
		if (pInputMouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			//�}�E�X�̈ʒu�擾
			POINT mouseTriggerPos;
			GetCursorPos(&mouseTriggerPos);
			ScreenToClient(CManager::GetWindowHandle(), &mouseTriggerPos);

			//�}�E�X�̈ʒu��ۑ�
			m_mouseTriggerPos.x = (float)mouseTriggerPos.x;
			m_mouseTriggerPos.y = (float)mouseTriggerPos.y;
		}

		//�}�E�X�𗣂����u��
		if (pInputMouse->GetRelease(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			//�}�E�X�̈ʒu�擾
			POINT mouseReleasePos;
			GetCursorPos(&mouseReleasePos);
			ScreenToClient(CManager::GetWindowHandle(), &mouseReleasePos);

			//�}�E�X���N���b�N�����ꏊ���痣�����ꏊ�̊p�x���Z�o
			float fRot = atan2f(m_mouseTriggerPos.y - mouseReleasePos.y, m_mouseTriggerPos.x - mouseReleasePos.x);
			//�v���C���[�̈ړ��x�N�g�������߂�
			D3DXVECTOR3 moveVec = D3DXVECTOR3(cosf(fRot) * PLAYER_SHOT_MOVE, sinf(fRot) * PLAYER_SHOT_MOVE, 0.0f);
			//�x�N�g����y���t�����ɂ���
			moveVec.y *= -1.0f;

			float fmoseVecAdjustment = 0.0f;
			//�Q�[�W�̗ʂɂ���ăx�N�g�������������銄����ς���
			if (m_pGauge->GetGauge() == 0)
			{//0�̎�
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_0;
			}
			else if (m_pGauge->GetGauge() > 0 && m_pGauge->GetGauge() <= GAME01_SHOT_GAUGE_CASE_1)
			{//0���傫���Ċ���̒l�ȉ��̎�
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_1;
			}
			else if (m_pGauge->GetGauge() > GAME01_SHOT_GAUGE_CASE_1 && m_pGauge->GetGauge() <= GAME01_SHOT_GAUGE_CASE_2)
			{//����̒l���傫���Ċ���̒l�ȉ��̎�
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_2;
			}
			else if (m_pGauge->GetGauge() > GAME01_SHOT_GAUGE_CASE_2 && m_pGauge->GetGauge() <= GAME01_SHOT_GAUGE_CASE_3)
			{//����̒l���傫���Ċ���̒l�ȉ��̎�
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_3;
			}
			else if (m_pGauge->GetGauge() > GAME01_SHOT_GAUGE_CASE_3 && m_pGauge->GetGauge() <= GAME01_SHOT_GAUGE_CASE_4)
			{//����̒l���傫���Ċ���̒l�ȉ��̎�
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_4;
			}
			else if (m_pGauge->GetGauge() > GAME01_SHOT_GAUGE_CASE_4 && m_pGauge->GetGauge() < m_pGauge->GetMaxNum())
			{//����̒l���傫���čő��菬�����̎�
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_5;
			}
			else if (m_pGauge->GetGauge() == m_pGauge->GetMaxNum())
			{//�ő�l�̎�
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_6;
			}

			//�x�N�g��������̊�������������
			moveVec *= fmoseVecAdjustment;

			//���˂��Ă����Ԃɂ���
			m_pPlayer->SetShot(true);
			//�W�����v�ʐݒ�
			m_pPlayer->SetJump(moveVec.y);
			//�O�ɐi�ޗ͂�ݒ�
			m_pPlayer->SetMoveForward(moveVec.x);
		}
	}
}
