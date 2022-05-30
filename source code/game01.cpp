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
#include "rocket.h"
#include "model.h"
#include "trophy.h"
#include "sound.h"
#include "letter.h"
#include "next_dialog_ui.h"
#include "dialog.h"
#include "history_letter.h"

//================================================
//�}�N����`
//================================================
#define GAME01_MOUSE_VEC_ADJUSTMENT_0			(0.4f)				//�����������Ƃ��̃x�N�g�������������銄��0
#define GAME01_MOUSE_VEC_ADJUSTMENT_1			(0.5f)				//�����������Ƃ��̃x�N�g�������������銄��1
#define GAME01_MOUSE_VEC_ADJUSTMENT_2			(0.6f)				//�����������Ƃ��̃x�N�g�������������銄��2
#define GAME01_MOUSE_VEC_ADJUSTMENT_3			(0.7f)				//�����������Ƃ��̃x�N�g�������������銄��3
#define GAME01_MOUSE_VEC_ADJUSTMENT_4			(0.8f)				//�����������Ƃ��̃x�N�g�������������銄��4
#define GAME01_MOUSE_VEC_ADJUSTMENT_5			(0.9f)				//�����������Ƃ��̃x�N�g�������������銄��5
#define GAME01_MOUSE_VEC_ADJUSTMENT_6			(1.0f)				//�����������Ƃ��̃x�N�g�������������銄��6
#define GAME01_CAMERA_ADD_POS					(10.0f)				//�J�����̈ʒu�����Z�����
#define GAME01_CAMERA_ADD_DIFFER				(10.0f)				//�J�����̎��_�ƒ����_�̋��������Z�����
#define GAME01_CAMERA_VIEW_CHANGE_MOVE			(20.0f)				//�J�����������DEFAULT����ő�ɕς��鋫�E���̃v���C���[�̃o�E���h����u�Ԃ̈ړ���
#define GAME01_SCORE_MAGNIFICATION				(10.0f)				//�v���C���[���O�ɐi�ޗ͂��X�R�A�ɂ���ۂ̔{��
#define GAME01_SHOT_GAUGE_MAX					(100)				//�V���b�g�Q�[�W�̍ő�l
#define GAME01_SHOT_GAUGE_ADD					(2)					//�V���b�g�Q�[�W�𑝂₷��
#define GAME01_SHOT_GAUGE_COUNTER_MAX			(10)				//�V���b�g�Q�[�W���ő�܂ł��܂��Ă����Ԃ̎���
#define GAME01_SHOT_GAUGE_CASE_1				(20)				//�V���b�g�Q�[�W�̒i�K1
#define GAME01_SHOT_GAUGE_CASE_2				(40)				//�V���b�g�Q�[�W�̒i�K2
#define GAME01_SHOT_GAUGE_CASE_3				(60)				//�V���b�g�Q�[�W�̒i�K3
#define GAME01_SHOT_GAUGE_CASE_4				(80)				//�V���b�g�Q�[�W�̒i�K4
#define GAME01_SHOT_GAUGE_SUBTRACT_ALPHA		(0.02f)				//�V���b�g�Q�[�W�𔖂������
#define GAME01_BG_SIZE_ADJUSTMENT				(3.0f)				//�w�i�̑傫�����銄��
#define GAME01_BG_POS_Z							(1000.0f)			//�w�i�̈ʒuZ
#define GAME01_BG_POS_Y							(300.0f)			//�w�i�̈ʒuY
#define GAME01_BG_1_MAGNIFICATION				(0.00004f)			//�w�i1���O�ɐi�ޗ͂�w�i�̈ړ��ɂ���ۂ̔{��
#define GAME01_BG_2_MAGNIFICATION				(0.00006f)			//�w�i2���O�ɐi�ޗ͂�w�i�̈ړ��ɂ���ۂ̔{��
#define GAME01_BG_3_MAGNIFICATION				(0.00008f)			//�w�i3���O�ɐi�ޗ͂�w�i�̈ړ��ɂ���ۂ̔{��
#define GAME01_BG_1_MOVE_INIT					(0.00006f)			//�w�i1�̏����ړ���
#define GAME01_BG_2_MOVE_INIT					(0.00008f)			//�w�i2�̏����ړ���
#define GAME01_BG_3_MOVE_INIT					(0.0001f)			//�w�i3�̏����ړ���
#define GAME01_SHOT_UI_ADD_SIZE_COUNTER			(9)					//���˗pUI�̃T�C�Y��傫�����鎞��
#define GAME01_SHOT_UI_ADD_SIZE					(1.02f)				//���˗pUI�̃T�C�Y��傫�����銄��
#define GAME01_SHOT_UI_SUBTRACT_SIZE_COUNTER	(18)				//���˗pUI�̃T�C�Y�����������鎞��
#define GAME01_SHOT_UI_SUBTRACT_SIZE			(0.98f)				//���˗pUI�̃T�C�Y�����������銄��
#define GAME01_SHOT_UI_UNINIT_COUNTER			(30)				//���˗pUI�������n�߂鎞��
#define GAME01_SHOT_UI_SUBTRACT_ALPHA			(0.06f)				//���˗pUI�̃��l���Z��
#define GAME01_SHOT_UI_MOVE_Y					(-0.8f)				//���˗pUI�̈ړ���Y
#define GAME01_ARROW_UI_SUBTRACT_ALPHA			(0.06f)				//���UI�̃��l���Z��
#define GAME01_FINISH_COUNTER					(180)				//�Q�[���N���A�\������
#define GAME01_SHOT_JUDGE_UI_SIZE_X				(400.0f)			//���ˎ��R��UI�T�C�YX
#define GAME01_SHOT_JUDGE_UI_SIZE_Y				(80.0f)				//���ˎ��R��UI�T�C�Y
#define GAME01_SHOT_JUDGE_UI_POS_Y				(200.0f)			//���ˎ��R��UI�ʒu
#define GAME01_FLYING_DISTANCE_1000				(100000)			//�򋗗�1000
#define GAME01_FLYING_DISTANCE_5000				(500000)			//�򋗗�5000
#define GAME01_FLYING_DISTANCE_10000			(1000000)			//�򋗗�10000
#define GAME01_ROCKET_POS_X						(-800.0f)			//���P�b�g�̈ʒu
#define GAME01_START_CLOUD_POS_Y				(-1500.0f)			//�X�^�[�g�̉_�̈ʒuY
#define GAME01_START_CLOUD_POS_Z				(500.0f)			//�X�^�[�g�̉_�̈ʒuZ
#define GAME01_MASK_ADD_COL						(0.01f)				//�}�X�N�̃J���[���Z�l
#define GAME01_PLAY_NUM_01						(1)					//�v���C������1
#define GAME01_PLAY_NUM_05						(5)					//�v���C������5
#define GAME01_PLAY_NUM_10						(10)				//�v���C������10
#define GAME01_HARD_MODE_UI_SIZE_X				(1314.0f * 0.3f)	//�n�[�h���[�h��UI�̃T�C�YX
#define GAME01_HARD_MODE_UI_SIZE_Y				(200.0f * 0.3f)		//�n�[�h���[�h��UI�̃T�C�YY
#define GAME01_CHARACTOR_CREATE_SPEED			(3)					//�����𐶐�����X�s�[�h
#define GAME01_CLICK_COUNTER					(120)				//�N���b�N���ł���܂ł̃J�E���^�[
#define GAME01_ROCKY_UI_POS_Y					(260.0f)			//���b�L�[�N��UI�̈ʒuY
#define GAME01_ROCKY_UI_SIZE_X					(222.0f * 1.5f)		//���b�L�[�N��UI�̃T�C�YX
#define GAME01_ROCKY_UI_SIZE_Y					(246.0f * 1.5f)		//���b�L�[�N��UI�̃T�C�YY
#define GAME01_DIALOG_FRAME_POS_Y				(230.0f)			//�Z���t�̃t���[���ʒuY
#define GAME01_CLICK_END_NUM					(20)				//�N���b�N���o�����
#define GAME01_MAX_STRING						(256)				//�������̏��

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
	m_shotMoveVec = { 0.0f, 0.0f, 0.0f };
	m_pGauge = nullptr;
	m_nGaugeCounter = 0;
	m_pGaugeFrame = nullptr;
	m_pRocket = nullptr;
	m_pShotUi = nullptr;
	m_bReleaseMouse = false;
	m_pArrow = nullptr;
	m_bFinish = false;
	m_nFinishCounter = 0;
	m_bPause = false;
	m_pStart = nullptr;
	m_pDengerMask = nullptr;
	m_bAddCol = false;
	m_nClick = 0;
	m_bDialog = false;
	m_pPause = nullptr;
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
	m_shotMoveVec = { 0.0f, 0.0f, 0.0f };
	m_nGaugeCounter = 0;
	m_pShotUi = nullptr;
	m_bReleaseMouse = false;
	m_pArrow = nullptr;
	m_bFinish = false;
	m_nFinishCounter = 0;
	m_bPause = false;
	m_bAddCol = true;
	m_nClick = 0;
	m_bDialog = false;

	//�T�E���h�擾
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();

	sound->Stop();
	//SE�ݒ�
	sound->Play(CSound::SOUND_LABEL::GAME_BGM);
	sound->ControllVoice(CSound::SOUND_LABEL::GAME_BGM, 1.6f);

	//�X�R�A�̐���
	CScore *pSocre = nullptr;
	pSocre = CScore::Create(D3DXVECTOR3(0.0f + (SCORE_POLYGON_WIDTH * MAX_SCORE_POLYGON / 2.0f), SCORE_POLYGON_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(SCORE_POLYGON_WIDTH, SCORE_POLYGON_HEIGHT, 0.0f));
	CManager::GetInstance()->GetPlayData()->SetScorePoint(pSocre);

	//�|�[�Y�̐���
	m_pPause = CPause::Create();

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f));

	//�X�^�[�g�n�_�̐���
	m_pFloor = CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), FLOOR_SIZE, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pFloor->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));

	//�����t��GROUND�̎�
	if (strncmp("GROUND", CManager::GetInstance()->GetPlayData()->GetPasword().c_str(), 7) == 0)
	{
		//�g���t�B�[�̃t���O��Ԃ��擾
		vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
		//�g���t�B�[���擾�������Ƃ��Ȃ�������
		if (flag[(int)CTrophy::TROPHY::GROUND] == false)
		{
			//�擾������
			flag[(int)CTrophy::TROPHY::GROUND] = true;

			CManager::GetInstance()->GetPlayData()->SetFlag(flag);
			CHistory::Create(CTrophy::TROPHY::GROUND);
		}
		m_pStart = CModelSingle::Create(D3DXVECTOR3(0.0f, GAME01_START_CLOUD_POS_Y, GAME01_START_CLOUD_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                            CXload::X_TYPE_GROUND, NULL, false);
	}
	else if (strncmp("HARD", CManager::GetInstance()->GetPlayData()->GetPasword().c_str(), 5) == 0)
	{//�����t��HARD�̎�
		m_pStart = CModelSingle::Create(D3DXVECTOR3(0.0f, GAME01_START_CLOUD_POS_Y, GAME01_START_CLOUD_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                            CXload::X_TYPE_CLOUD_GRAY, NULL, false);
	}
	else
	{
		m_pStart = CModelSingle::Create(D3DXVECTOR3(0.0f, GAME01_START_CLOUD_POS_Y, GAME01_START_CLOUD_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                            CXload::X_TYPE_CLOUD, NULL, false);
	}

	//�ŏ��̓��̐���
	m_apRoad[0] = CRoad::Create(D3DXVECTOR3(FLOOR_SIZE.x, 0.0f, 0.0f), FLOOR_SIZE, 0.0f);

	//�w�i1�̐���
	m_pBg[0] = CBg::Create(D3DXVECTOR3(0.0f, GAME01_BG_POS_Y, GAME01_BG_POS_Z),
		                   D3DXVECTOR3(SCREEN_WIDTH * GAME01_BG_SIZE_ADJUSTMENT, SCREEN_HEIGHT * GAME01_BG_SIZE_ADJUSTMENT, 0.0f),
		                   D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(GAME01_BG_1_MOVE_INIT, 0.0f));
	//�w�i2�̐���
	m_pBg[1] = CBg::Create(D3DXVECTOR3(0.0f, GAME01_BG_POS_Y, GAME01_BG_POS_Z),
		                   D3DXVECTOR3(SCREEN_WIDTH * GAME01_BG_SIZE_ADJUSTMENT, SCREEN_HEIGHT * GAME01_BG_SIZE_ADJUSTMENT, 0.0f),
		                   D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(GAME01_BG_2_MOVE_INIT, 0.0f));
	//�w�i3�̐���
	m_pBg[2] = CBg::Create(D3DXVECTOR3(0.0f, GAME01_BG_POS_Y, GAME01_BG_POS_Z),
		                   D3DXVECTOR3(SCREEN_WIDTH * GAME01_BG_SIZE_ADJUSTMENT, SCREEN_HEIGHT * GAME01_BG_SIZE_ADJUSTMENT, 0.0f),
		                   D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(GAME01_BG_3_MOVE_INIT, 0.0f));
	
	
	//�����t��EVENING�̎�
	if (strncmp("EVENING", CManager::GetInstance()->GetPlayData()->GetPasword().c_str(), 8) == 0)
	{
		//�g���t�B�[�̃t���O��Ԃ��擾
		vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
		//�g���t�B�[���擾�������Ƃ��Ȃ�������
		if (flag[(int)CTrophy::TROPHY::EVENING] == false)
		{
			//�擾������
			flag[(int)CTrophy::TROPHY::EVENING] = true;

			CManager::GetInstance()->GetPlayData()->SetFlag(flag);
			CHistory::Create(CTrophy::TROPHY::EVENING);
		}

		//�w�i�̃e�N�X�`�����蓖��
		m_pBg[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("01_evning.png"));
		m_pBg[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("sky_02.png"));
		m_pBg[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("sky_03.png"));
	}
	else if (strncmp("NIGHT", CManager::GetInstance()->GetPlayData()->GetPasword().c_str(), 6) == 0)
	{//�����t��NIGHT�̎�
		//�g���t�B�[�̃t���O��Ԃ��擾
		vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
		//�g���t�B�[���擾�������Ƃ��Ȃ�������
		if (flag[(int)CTrophy::TROPHY::NIGHT] == false)
		{
			//�擾������
			flag[(int)CTrophy::TROPHY::NIGHT] = true;

			CManager::GetInstance()->GetPlayData()->SetFlag(flag);
			CHistory::Create(CTrophy::TROPHY::NIGHT);
		}

		//�w�i�̃e�N�X�`�����蓖��
		m_pBg[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("04_night.png"));
		m_pBg[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("sky_02.png"));
		m_pBg[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("sky_03.png"));
	}
	else if (strncmp("HARD", CManager::GetInstance()->GetPlayData()->GetPasword().c_str(), 5) == 0)
	{//�����t��HARD�̎�
		//�g���t�B�[�̃t���O��Ԃ��擾
		vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
		//�g���t�B�[���擾�������Ƃ��Ȃ�������
		if (flag[(int)CTrophy::TROPHY::HARD] == false)
		{
			//�擾������
			flag[(int)CTrophy::TROPHY::HARD] = true;

			CManager::GetInstance()->GetPlayData()->SetFlag(flag);
			CHistory::Create(CTrophy::TROPHY::HARD);
		}

		//�w�i�̃e�N�X�`�����蓖��
		m_pBg[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("03_cloudy.png"));
		m_pBg[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("01_cloudy.png"));
		m_pBg[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("02_cloudy.png"));

		//�n�[�h���[�h��UI����
		CObject2D *pHardModeUi = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH -  GAME01_HARD_MODE_UI_SIZE_X / 2.0f,
			                                                   SCREEN_HEIGHT - GAME01_HARD_MODE_UI_SIZE_Y / 2.0f, 0.0f),
			                                       D3DXVECTOR3(GAME01_HARD_MODE_UI_SIZE_X, GAME01_HARD_MODE_UI_SIZE_Y, 0.0f),
			                                       static_cast<int>(CObject::PRIORITY::UI));
		pHardModeUi->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("hardmode.png"));

		//�}�X�N�̐���
		m_pDengerMask = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
			                              static_cast<int>(CObject::PRIORITY::MASK));
		m_pDengerMask->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("denger_mask.png"));
	}
	else
	{
		//�w�i�̃e�N�X�`�����蓖��
		m_pBg[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("sky_01.png"));
		m_pBg[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("sky_02.png"));
		m_pBg[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("sky_03.png"));
	}

	//���P�b�g�̐���
	m_pRocket = CRocket::Create(D3DXVECTOR3(GAME01_ROCKET_POS_X, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//================================================
//�I������
//================================================
void CGame01::Uninit(void)
{
	//�X�R�A��ۑ�
	CManager::GetInstance()->GetPlayData()->SetScore(CManager::GetInstance()->GetPlayData()->GetScorePoint()->GetScore());
	
	//�g���t�B�[�̔򋗗��̃t���O����
	FlyingDistanceFlag();

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CGame01::Update(void)
{
	//�������o���Ă��Ȃ���ԂȂ�
	if (m_bDialog == false)
	{
		if (m_pDengerMask != nullptr)
		{
			//�}�X�N����
			Mask();
		}
	}

	//���˂�����
	if (m_pPlayer->GetShot() == true)
	{
		//�N���b�N����
		Click();

		//�������o���Ă��Ȃ���ԂȂ�
		if (m_bDialog == false)
		{
			if (m_pGaugeFrame != nullptr && m_pGauge != nullptr)
			{
				//�Q�[�W����������
				UninitGauge();
			}

			if (m_pArrow != nullptr)
			{
				//������������
				UninitArrow();
			}

			//�J�����̏���
			Camera();

			//���̏���
			Road();

			//���P�b�g�̏���
			Rocket();

			//�v���C���[���O�ɐi�ޗ͂��擾
			float fScoreMoveForward = m_pPlayer->GetMoveForward();

			//�O�ɐi�ޗ͂����̐���������
			if (fScoreMoveForward < 0.0f)
			{
				//0�ɂ���
				fScoreMoveForward = 0.0f;
			}
			else if (fScoreMoveForward > 0.0f)
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
	}
	else if(m_pPlayer->GetShot() == false && m_bReleaseMouse == false)
	{//���˂��Ă��Ȃ������犎�}�E�X�𗣂��Ă��Ȃ��Ƃ�
		if (m_pGauge != nullptr)
		{
			//�Q�[�W����
			Gauge();
		}
	}

	//�|�[�Y�̃t���O�������Ă��Ȃ�������
	if (m_bPause == false)
	{
		//���ˏ���
		Shot();
	}

	//�t�B�j�b�V������
	Finish();

	//�|�[�Y�̃t���O�������Ă�����
	if (m_bPause == true)
	{
		//�t���O�����낷
		m_bPause = false;
	}

#ifdef _DEBUG
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
#endif // !_DEBUG
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

		//�_�̈ʒu���擾
		D3DXVECTOR3 pos = m_pStart->GetModel()->GetPos();
		//�ʒu���ړ�������
		pos.x += -m_pPlayer->GetMoveForward();
		//�ʒu�ݒ�
		m_pStart->GetModel()->SetPos(pos);
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
			m_apRoad[0]->DeleteRoad();
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

				m_pStart->Uninit();
				m_pStart = nullptr;
			}
		}
	}

	if (m_apRoad[0] != nullptr)
	{
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
}

//================================================
//�Q�[�W����
//================================================
void CGame01::Gauge(void)
{
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();

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
//������������
//================================================
void CGame01::UninitArrow(void)
{
	//�F�擾
	D3DXCOLOR arrowCol = m_pArrow->GetCol();

	//���X�ɔ�������
	arrowCol.a -= GAME01_ARROW_UI_SUBTRACT_ALPHA;

	//�����Ȃ��Ȃ�����
	if (arrowCol.a <= 0.0f)
	{
		//0�ɂ���
		arrowCol.a = 0.0f;

		//����
		m_pArrow->Uninit();
		m_pArrow = nullptr;
	}
	else
	{
		//�F�̐ݒ�
		m_pArrow->SetCol(arrowCol);
	}
}

//================================================
//���ˏ���
//================================================
void CGame01::Shot(void)
{
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();
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

	if (m_pPlayer->GetShot() == false && m_bReleaseMouse == false)
	{//���˂��Ă��Ȃ���ԂȂ�
		//�}�E�X�擾����
		CInputMouse *pInputMouse;
		pInputMouse = CManager::GetInstance()->GetInputMouse();

		//�}�E�X���������u��
		if (pInputMouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			//�Q�[�W�̃t���[������
			m_pGaugeFrame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
				                              static_cast<int>(CObject::PRIORITY::UI));
			m_pGaugeFrame->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("gauge_frame.png"));

			//�V���b�g�Q�[�W�̐���
			m_pGauge = CGauge::Create(D3DXVECTOR3(GAUGE_SHOT_POS_X, GAUGE_SHOT_POS_Y, 0.0f),
				                      D3DXVECTOR3(GAUGE_SHOT_SIZE_X, GAUGE_SHOT_SIZE_Y, 0.0f), GAME01_SHOT_GAUGE_MAX, 0);
			m_pGauge->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("gauge.png"));

			sound->Play(CSound::SOUND_LABEL::GAGE_SE);
			sound->ControllVoice(CSound::SOUND_LABEL::GAGE_SE, 1.4f);

			//�}�E�X�̈ʒu�擾
			POINT mouseTriggerPos;
			GetCursorPos(&mouseTriggerPos);
			ScreenToClient(CManager::GetWindowHandle(), &mouseTriggerPos);

			//�}�E�X�̈ʒu��ۑ�
			m_mouseTriggerPos.x = (float)mouseTriggerPos.x;
			m_mouseTriggerPos.y = (float)mouseTriggerPos.y;

			//���UI�𐶐�
			m_pArrow = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f),
				                         static_cast<int>(CObject::PRIORITY::UI));
			m_pArrow->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("arrow02.png"));
			m_pArrow->SetOriginType(CObject2D::ORIGIN_TYPE::LEFT);

			m_pGaugeFrame->SetPriority(static_cast<int>(CObject::PRIORITY::UI));
			m_pGauge->SetPriority(static_cast<int>(CObject::PRIORITY::UI));
		}

		//��󂪐�������Ă�����
		if (m_pArrow != nullptr)
		{
			//�}�E�X�̈ʒu�擾
			POINT mousePos;
			GetCursorPos(&mousePos);
			ScreenToClient(CManager::GetWindowHandle(), &mousePos);

			//�T�C�Y���擾
			D3DXVECTOR3 size = D3DXVECTOR3(200.0f, 200.0f, 0.0f);

			//�}�E�X���N���b�N�����ꏊ���猻�݂̏ꏊ�̋��������߂�
			D3DXVECTOR2 differ = D3DXVECTOR3(mousePos.x - m_mouseTriggerPos.x, mousePos.y - m_mouseTriggerPos.y, 0.0f);

			//�T�C�YX�������ɂ���đ���������
			size.x += sqrtf(differ.x * differ.x + differ.y * differ.y);

			//����̒l�ȉ��ɂȂ�����
			if (size.x <= 100.0f)
			{
				//����̒l�ɂ���
				size.x = 100.0f;
			}

			//�}�E�X���N���b�N�����ꏊ���痣�����ꏊ�̊p�x���Z�o
			float fRot = atan2f(differ.y, differ.x);

			//�������u�Ԃ̎�
			if (differ.y == 0.0f && differ.x == 0.0f)
			{
				fRot = D3DX_PI;
			}

			//�p�x�ɂ���Ė�����]������
			m_pArrow->SetPos(m_pArrow->GetPos(), size, -fRot + D3DX_PI);
		}



		//�}�E�X�𗣂����u�Ԋ���󂪐�������Ă�����
		if (pInputMouse->GetRelease(CInputMouse::MOUSE_TYPE_LEFT) == true && m_pArrow!= nullptr)
		{
			sound->Stop(CSound::SOUND_LABEL::GAGE_SE);
			//�}�E�X�𗣂�����Ԃ̃t���O�𗧂Ă�
			m_bReleaseMouse = true;

			//�}�E�X�̈ʒu�擾
			POINT mouseReleasePos;
			GetCursorPos(&mouseReleasePos);
			ScreenToClient(CManager::GetWindowHandle(), &mouseReleasePos);

			//�}�E�X���N���b�N�����ꏊ���痣�����ꏊ�̊p�x���Z�o
			float fRot = atan2f(m_mouseTriggerPos.y - mouseReleasePos.y, m_mouseTriggerPos.x - mouseReleasePos.x);
			//�v���C���[�̈ړ��x�N�g�������߂�
			m_shotMoveVec = D3DXVECTOR3(cosf(fRot) * PLAYER_SHOT_MOVE, sinf(fRot) * PLAYER_SHOT_MOVE, 0.0f);
			//�x�N�g����y���t�����ɂ���
			m_shotMoveVec.y *= -1.0f;

			float fmoseVecAdjustment = 0.0f;

			//UI�̐���
			m_pShotUi = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, GAME01_SHOT_JUDGE_UI_POS_Y, 0.0f),
				                          D3DXVECTOR3(GAME01_SHOT_JUDGE_UI_SIZE_X, GAME01_SHOT_JUDGE_UI_SIZE_Y, 0.0f),
				                          static_cast<int>(CObject::PRIORITY::UI));

			//�Q�[�W�̗ʂɂ���ăx�N�g�������������銄����ς���
			if (m_pGauge->GetGauge() == 0)
			{//0�̎�
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_0;
				m_pShotUi->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("bad.png"));
				sound->ControllVoice(CSound::SOUND_LABEL::BAD_SE, 1.2f);
				sound->Play(CSound::SOUND_LABEL::BAD_SE);
			}
			else if (m_pGauge->GetGauge() > 0 && m_pGauge->GetGauge() <= GAME01_SHOT_GAUGE_CASE_1)
			{//0���傫���Ċ���̒l�ȉ��̎�
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_1;
				m_pShotUi->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("bad.png"));
				sound->ControllVoice(CSound::SOUND_LABEL::BAD_SE, 1.2f);
				sound->Play(CSound::SOUND_LABEL::BAD_SE);
			}
			else if (m_pGauge->GetGauge() > GAME01_SHOT_GAUGE_CASE_1 && m_pGauge->GetGauge() <= GAME01_SHOT_GAUGE_CASE_2)
			{//����̒l���傫���Ċ���̒l�ȉ��̎�
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_2;
				m_pShotUi->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("bad.png"));
				sound->ControllVoice(CSound::SOUND_LABEL::BAD_SE, 1.2f);
				sound->Play(CSound::SOUND_LABEL::BAD_SE);
			}
			else if (m_pGauge->GetGauge() > GAME01_SHOT_GAUGE_CASE_2 && m_pGauge->GetGauge() <= GAME01_SHOT_GAUGE_CASE_3)
			{//����̒l���傫���Ċ���̒l�ȉ��̎�
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_3;
				m_pShotUi->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("good.png"));
				sound->ControllVoice(CSound::SOUND_LABEL::GOOD_SE, 1.2f);
				sound->Play(CSound::SOUND_LABEL::GOOD_SE);
			}
			else if (m_pGauge->GetGauge() > GAME01_SHOT_GAUGE_CASE_3 && m_pGauge->GetGauge() <= GAME01_SHOT_GAUGE_CASE_4)
			{//����̒l���傫���Ċ���̒l�ȉ��̎�
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_4;
				m_pShotUi->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("good.png"));
				sound->ControllVoice(CSound::SOUND_LABEL::GOOD_SE, 1.2f);
				sound->Play(CSound::SOUND_LABEL::GOOD_SE);
			}
			else if (m_pGauge->GetGauge() > GAME01_SHOT_GAUGE_CASE_4 && m_pGauge->GetGauge() < m_pGauge->GetMaxNum())
			{//����̒l���傫���čő��菬�����̎�
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_5;
				m_pShotUi->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("great.png"));
				sound->ControllVoice(CSound::SOUND_LABEL::GREAT_SE, 1.2f);
				sound->Play(CSound::SOUND_LABEL::GREAT_SE);
			}
			else if (m_pGauge->GetGauge() == m_pGauge->GetMaxNum())
			{//�ő�l�̎�
				fmoseVecAdjustment = GAME01_MOUSE_VEC_ADJUSTMENT_6;
				m_pShotUi->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("perfect.png"));
				sound->ControllVoice(CSound::SOUND_LABEL::PARFECT_SE, 1.2f);
				sound->Play(CSound::SOUND_LABEL::PARFECT_SE);
			}

			//�x�N�g��������̊�������������
			m_shotMoveVec *= fmoseVecAdjustment;
		}
	}
	else if (m_bReleaseMouse == true && m_pShotUi != nullptr)
	{//�}�E�X�𗣂�����Ԋ����˗pUI�������Ă��Ȃ�������
		//����UI����
		ShotUi();
	}
}

//================================================
//����UI����
//================================================
void CGame01::ShotUi(void)
{
	//�J�E���^�[�����Z
	m_nShotUiCounter++;

	//�T�C�Y���擾
	D3DXVECTOR3 size = m_pShotUi->GetSize();
	//�ʒu���擾
	D3DXVECTOR3 pos = m_pShotUi->GetPos();

	//����̒l���傫���Ȃ�����
	if (m_nShotUiCounter > GAME01_SHOT_UI_UNINIT_COUNTER)
	{
		//�F���擾
		D3DXCOLOR col = m_pShotUi->GetCol();
		//��������
		col.a -= GAME01_SHOT_UI_SUBTRACT_ALPHA;
		//�����Ȃ��Ȃ�����
		if (col.a <= 0.0f)
		{
			//���˂��Ă����Ԃɂ���
			m_pPlayer->SetShot(true);

			//�O�ɐi�ޗ͂��}�C�i�X�̏ꍇ�̓W�����v���Ȃ��悤�ɂ���
			if (m_shotMoveVec.x < 0.0f)
			{
				m_shotMoveVec.y = 0.0f;
			}
			//�W�����v�ʐݒ�
			m_pPlayer->SetJump(m_shotMoveVec.y);
			//�O�ɐi�ޗ͂�ݒ�
			m_pPlayer->SetMoveForward(m_shotMoveVec.x);

			if (m_pShotUi != nullptr)
			{
				//����
				m_pShotUi->Uninit();
				m_pShotUi = nullptr;
				return;
			}
		}
		else
		{
			//�F��ݒ�
			m_pShotUi->SetCol(col);
		}
		//�ʒuY������̒l������
		pos.y += GAME01_SHOT_UI_MOVE_Y;
	}
	else if(m_nShotUiCounter <= GAME01_SHOT_UI_ADD_SIZE_COUNTER)
	{
		//�T�C�Y������̊������傫������
		size *= GAME01_SHOT_UI_ADD_SIZE;
	}
	else if (m_nShotUiCounter > GAME01_SHOT_UI_ADD_SIZE_COUNTER && m_nShotUiCounter <= GAME01_SHOT_UI_SUBTRACT_SIZE_COUNTER)
	{
		//�T�C�Y������̊���������������
		size *= GAME01_SHOT_UI_SUBTRACT_SIZE;
	}

	//�ʒu�ƃT�C�Y��ݒ�
	m_pShotUi->SetPos(pos, size);
}

//================================================
//���P�b�g�̏���
//================================================
void CGame01::Rocket(void)
{
	//���P�b�g�������Ă��Ȃ�������
	if (m_pRocket != nullptr)
	{
		//���������ĂȂ������犎�v���C���[�Ɠ������Ă��Ȃ�������
		if (m_pFloor != nullptr && m_pRocket->GetHitPlayer() == false)
		{
			//�ʒu���擾
			D3DXVECTOR3 rocketPos = m_pRocket->GetModel()->GetModel()->GetPos();
			//�ʒuX���ړ�������
			rocketPos.x += -m_pPlayer->GetMoveForward();
			//�ʒu�ݒ�
			m_pRocket->GetModel()->GetModel()->SetPos(rocketPos);
		}
		else if (m_pFloor == nullptr)
		{//���������Ă���
			//���P�b�g������
			m_pRocket->Uninit();
			m_pRocket = nullptr;
		}
	}
}

//================================================
//�Q�[���I������
//================================================
void CGame01::Finish(void)
{
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();

	//�I��������
	if (m_bFinish == true && m_pPlayer->GetMoveForward() == 0.0f)
	{
		if (m_nFinishCounter == 0)
		{
			CObject2D *pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
				                                     D3DXVECTOR3(600.0f, 100.0f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
			pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("finish.png"));
			sound->Play(CSound::SOUND_LABEL::GOAL_SE);
			sound->ControllVoice(CSound::SOUND_LABEL::GOAL_SE, 1.4f);
		}
		else if (m_nFinishCounter > GAME01_FINISH_COUNTER)
		{
			//�t�F�[�h�擾����
			CFade *pFade;
			pFade = CManager::GetInstance()->GetFade();

			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				if (m_pRocket != nullptr)
				{
					if (m_pRocket->GetHitPlayer() == true)
					{
						//���P�b�g�V�[���ɑJ��
						pFade->SetFade(CManager::MODE::ROCKET_SCENE);
					}
					else
					{
						//���U���g�V�[���ɑJ��
						pFade->SetFade(CManager::MODE::RESULT);
					}
				}
				else
				{
					//���U���g�V�[���ɑJ��
					pFade->SetFade(CManager::MODE::RESULT);
				}

				//�v���C�񐔂�1���₷
				CManager::GetInstance()->GetPlayData()->AddPlayNum(1);

				//�v���C�񐔂�1�Ȃ�
				if (CManager::GetInstance()->GetPlayData()->GetPlayNum() == GAME01_PLAY_NUM_01)
				{
					//�g���t�B�[�̃t���O��Ԃ��擾
					vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
					//�g���t�B�[���擾�������Ƃ��Ȃ�������
					if (flag[(int)CTrophy::TROPHY::PLAY_00] == false)
					{
						//�擾������
						flag[(int)CTrophy::TROPHY::PLAY_00] = true;

						CManager::GetInstance()->GetPlayData()->SetFlag(flag);
						CHistory::Create(CTrophy::TROPHY::PLAY_00);
					}
				}
				else if (CManager::GetInstance()->GetPlayData()->GetPlayNum() == GAME01_PLAY_NUM_05)
				{//�v���C�񐔂�5�Ȃ�
					//�g���t�B�[�̃t���O��Ԃ��擾
					vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
					//�g���t�B�[���擾�������Ƃ��Ȃ�������
					if (flag[(int)CTrophy::TROPHY::PLAY_05] == false)
					{
						//�擾������
						flag[(int)CTrophy::TROPHY::PLAY_05] = true;

						CManager::GetInstance()->GetPlayData()->SetFlag(flag);
						CHistory::Create(CTrophy::TROPHY::PLAY_05);
					}
				}
				else if (CManager::GetInstance()->GetPlayData()->GetPlayNum() == GAME01_PLAY_NUM_10)
				{//�v���C�񐔂�10�Ȃ�
					//�g���t�B�[�̃t���O��Ԃ��擾
					vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
					//�g���t�B�[���擾�������Ƃ��Ȃ�������
					if (flag[(int)CTrophy::TROPHY::PLAY_10] == false)
					{
						//�擾������
						flag[(int)CTrophy::TROPHY::PLAY_10] = true;

						CManager::GetInstance()->GetPlayData()->SetFlag(flag);
						CHistory::Create(CTrophy::TROPHY::PLAY_10);
					}
				}
			}
		}
		//�J�E���^�[�𑝂₷
		m_nFinishCounter++;
	}
}

//================================================
//�g���t�B�[�̔򋗗��̃t���O����
//================================================
void CGame01::FlyingDistanceFlag(void)
{
	//�X�R�A�̎擾
	int nScore = CManager::GetInstance()->GetPlayData()->GetScore();

	//�g���t�B�[�̃t���O��Ԃ��擾
	vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();

	if (nScore >= GAME01_FLYING_DISTANCE_1000)
	{
		//�g���t�B�[���擾�������Ƃ��Ȃ�������
		if (flag[(int)CTrophy::TROPHY::M_1000] == false)
		{
			//�擾������
			flag[(int)CTrophy::TROPHY::M_1000] = true;
			//�t���O�𗧂Ă�
			CManager::GetInstance()->GetPlayData()->SetFlag(flag);
			CHistory::Create(CTrophy::TROPHY::M_1000);
		}

		if (nScore >= GAME01_FLYING_DISTANCE_5000)
		{
			//�g���t�B�[���擾�������Ƃ��Ȃ�������
			if (flag[(int)CTrophy::TROPHY::M_5000] == false)
			{
				//�擾������
				flag[(int)CTrophy::TROPHY::M_5000] = true;
				//�t���O�𗧂Ă�
				CManager::GetInstance()->GetPlayData()->SetFlag(flag);
				CHistory::Create(CTrophy::TROPHY::M_5000);
			}

			if (nScore >= GAME01_FLYING_DISTANCE_10000)
			{
				//�g���t�B�[���擾�������Ƃ��Ȃ�������
				if (flag[(int)CTrophy::TROPHY::M_10000] == false)
				{
					//�擾������
					flag[(int)CTrophy::TROPHY::M_10000] = true;
					//�t���O�𗧂Ă�
					CManager::GetInstance()->GetPlayData()->SetFlag(flag);
					CHistory::Create(CTrophy::TROPHY::M_10000);
				}
			}
		}
	}
}

//================================================
//�}�X�N����
//================================================
void CGame01::Mask(void)
{
	//�F���擾
	D3DXCOLOR col = m_pDengerMask->GetCol();

	//���Z�����ԂȂ�
	if (m_bAddCol == true)
	{
		//���Z
		col.a += GAME01_MASK_ADD_COL;
		//1�ȏ�ɂȂ�����
		if (col.a >= 1.0f)
		{
			//1�ɂ���
			col.a = 1.0f;
			//���Z�����Ԃɂ���
			m_bAddCol = false;
		}
	}
	else
	{
		//���Z
		col.a -= GAME01_MASK_ADD_COL;
		//0�ȉ��ɂȂ�����
		if (col.a <= 0.0f)
		{
			//0�ɂ���
			col.a = 0.0f;
			//���Z�����Ԃɂ���
			m_bAddCol = true;
		}
	}
	//�F�ݒ�
	m_pDengerMask->SetCol(col);
}

//================================================
//�N���b�N����
//================================================
void CGame01::Click(void)
{
	//�}�E�X�擾����
	CInputMouse *pInputMouse;
	pInputMouse = CManager::GetInstance()->GetInputMouse();

	//�}�E�X���������u��
	if (pInputMouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
	{
		//�J�E���^�[�����Z
		m_nClick++;

		//����̒l�ɂȂ�����
		if (m_nClick == GAME01_CLICK_END_NUM)
		{
			//�T�E���h�擾
			CSound *sound;
			sound = CManager::GetInstance()->GetSound();
			//�Đ�����
			sound->Play(CSound::SOUND_LABEL::ANGRY_SE);
			sound->ControllVoice(CSound::SOUND_LABEL::ANGRY_SE, 1.4f);

			//�Z���t�N���X�̐���
			CDialog::Create(CDialog::SCENE_TYPE::CLICK_SCENE);

			//�g���t�B�[�̃t���O��Ԃ��擾
			vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
			//�g���t�B�[���擾�������Ƃ��Ȃ�������
			if (flag[(int)CTrophy::TROPHY::ROCKY_ANGRY] == false)
			{
				//�擾������
				flag[(int)CTrophy::TROPHY::ROCKY_ANGRY] = true;
				//�t���O�𗧂Ă�
				CManager::GetInstance()->GetPlayData()->SetFlag(flag);
				CHistory::Create(CTrophy::TROPHY::ROCKY_ANGRY);
			}

			//�|�[�Y����������Ă���̂Ȃ�
			if (m_pPause != nullptr)
			{
				//����
				m_pPause->Uninit();
				m_pPause = nullptr;
			}

			//���b�Z�[�W���o����Ԃɂ���
			m_bDialog = true;
		}
	}
}