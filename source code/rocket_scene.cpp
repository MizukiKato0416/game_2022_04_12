//================================================
//���P�b�g�V�[������
//Authore:��������
//================================================
#include "rocket_scene.h"
#include "manager.h"
#include "texture.h"
#include "fade.h"
#include "sound.h"
#include "model_single.h"
#include "model.h"
#include "player.h"
#include "score.h"
#include "play_data.h"
#include "bg.h"
#include "smoke.h"
#include "camera.h"

#ifdef _DEBUG
#include "input_keyboard.h"
#endif // !_DEBUG

//================================================
//�}�N����`
//================================================
#define ROCKET_SCENE_BG_POS_Z				(100.0f)										//�w�i�̈ʒuZ
#define ROCKET_SCENE_BG_POS_Y				(300.0f)										//�w�i�̈ʒuY�����l
#define ROCKET_SCENE_BG_SIZE				(D3DXVECTOR3(SCREEN_WIDTH, 4971.0f, 0.0f))		//�w�i�̃T�C�Y
#define ROCKET_SCENE_BG_SIZE_ADJUSTMENT		(0.8f)											//�w�i�̃T�C�Y�����l
#define ROCKET_SCENE_BG_01_SPEED			(-0.001f)										//�w�i1�̈ړ��X�s�[�h
#define ROCKET_SCENE_BG_02_SPEED			(-0.0001f)										//�w�i2�̈ړ��X�s�[�h
#define ROCKET_SCENE_BG_03_SPEED			(-0.00014f)										//�w�i3�̈ړ��X�s�[�h
#define ROCKET_SCENE_BG_04_SPEED			(-0.00018f)										//�w�i4�̈ړ��X�s�[�h
#define ROCKET_SCENE_ROCKET_SPEED			(6.0f)											//���P�b�g�̑���
#define ROCKET_SCENE_SMOKE_ROT_RAND			(float (rand() % 629 + -314) / 100)				//��]����ۂ̕��������߂邽�߂̃����_���l
#define ROCKET_SCENE_SMOKE_POS_X_RAND		(float (rand() % 20 + -10))						//���P�b�g�_�̈ʒuX�̃����_���l
#define ROCKET_SCENE_SMOKE_POS_Y_RAND		(30.0f)											//���P�b�g�_�̈ʒuY�̃����_���l
#define ROCKET_SCENE_SMOKE_SIZE				(D3DXVECTOR3 (20.0f, 20.0f, 0.0f))				//���P�b�g�_�̃T�C�Y
#define ROCKET_SCENE_SMOKE_ADD_ROTATE		(0.2f)											//���P�b�g�_�̉�]���Z�l
#define ROCKET_SCENE_SMOKE_ADD_SIZE			(D3DXVECTOR3 (0.7f, 0.7f, 0.0f))				//���P�b�g�_�̃T�C�Y���Z�l
#define ROCKET_SCENE_SMOKE_SUBTRACT_ALPHA	(0.004f)										//���P�b�g�_�̃��l���Z�l
#define ROCKET_SCENE_SMOKE_NUM				(3)												//�����o����
#define ROCKET_SCENE_ADD_SCORE				(333333)										//�X�R�A�����Z�����
#define ROCKET_SCENE_PLAYER_POS_Y			(120.0f)										//�v���C���[�̈ʒu
#define ROCKET_SCENE_CAMERA_V_POS			(D3DXVECTOR3(0.0f, 0.0f, -500.0f))				//�J�����̈ʒu
#define ROCKET_SCENE_CAMERA_SHAKE_POS		(float (rand() % 10 + -5))						//�J������h�炷��
#define ROCKET_SCENE_RESULT_COUNTER			(180)											//���U���g�ɍs���܂ł̎���
#define ROCKET_SCENE_ERROR_SIZE				(D3DXVECTOR3(927.0f, 155.0f, 0.0f))				//����s�\UI�̃T�C�Y
#define ROCKET_SCENE_MASK_ADD_COL			(0.03f)											//�}�X�N�̃J���[���Z�l

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CRocketScene::CRocketScene()
{
	m_pPlayer = nullptr;
	m_pRocket = nullptr;
	m_pScore = nullptr;
	memset(m_apBg, NULL, sizeof(m_apBg[ROCKET_SCENE_BG_NUM]));
	m_nCounter = 0;
	m_bResult = false;
	m_pDengerMask = nullptr;
	m_bAddCol = false;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CRocketScene::~CRocketScene()
{

}

//================================================
//����������
//================================================
HRESULT CRocketScene::Init(void)
{
	//�ϐ�������
	m_nCounter = 0;
	m_bResult = false;
	m_bAddCol = true;

	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();
	//�~�߂�
	pSound->Stop();

	//�Đ�
	pSound->ControllVoice(CSound::SOUND_LABEL::ROCKET_SE, 0.8f);
	pSound->Play(CSound::SOUND_LABEL::ROCKET_SE);
	pSound->ControllVoice(CSound::SOUND_LABEL::ERROR_SE, 1.8f);
	pSound->Play(CSound::SOUND_LABEL::ERROR_SE);

	//�w�i�̐���
	for(int nCntBg = 0; nCntBg < ROCKET_SCENE_BG_NUM; nCntBg++)
	{ 
		m_apBg[nCntBg] = CBg::Create(D3DXVECTOR3(0.0f, ROCKET_SCENE_BG_SIZE.y * ROCKET_SCENE_BG_SIZE_ADJUSTMENT / 2.0f - ROCKET_SCENE_BG_POS_Y,
								                 ROCKET_SCENE_BG_POS_Z),
								     D3DXVECTOR3(ROCKET_SCENE_BG_SIZE.x * ROCKET_SCENE_BG_SIZE_ADJUSTMENT,
								     	         ROCKET_SCENE_BG_SIZE.y * ROCKET_SCENE_BG_SIZE_ADJUSTMENT, 0.0f),
								     D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	}
	m_apBg[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("bg_universe.png"));
	m_apBg[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("bg_universe_purple.png"));
	m_apBg[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("bg_universe_light blue.png"));
	m_apBg[3]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("bg_universe_yellow.png"));

	m_apBg[0]->SetUvMove(D3DXVECTOR2(0.0f, ROCKET_SCENE_BG_01_SPEED));
	m_apBg[1]->SetUvMove(D3DXVECTOR2(0.0f, ROCKET_SCENE_BG_02_SPEED));
	m_apBg[2]->SetUvMove(D3DXVECTOR2(0.0f, ROCKET_SCENE_BG_03_SPEED));
	m_apBg[3]->SetUvMove(D3DXVECTOR2(0.0f, ROCKET_SCENE_BG_04_SPEED));


	//���P�b�g�̐���
	m_pRocket = CModelSingle::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_ROCKET, NULL, true);

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f));

	//���f���̉�]��0�ɂ���
	m_pPlayer->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�ʒu���グ��
	m_pPlayer->SetOffsetPos(D3DXVECTOR3(0.0f, ROCKET_SCENE_PLAYER_POS_Y, 0.0f));
	//���P�b�g�Ɛe�q�֌W������
	m_pPlayer->SetObjParent(true);
	m_pPlayer->SetMtxParent(m_pRocket->GetModel()->GetMtxPoint());

	//�X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(0.0f + (SCORE_POLYGON_WIDTH * MAX_SCORE_POLYGON / 2.0f), SCORE_POLYGON_HEIGHT / 2.0f, 0.0f),
							  D3DXVECTOR3(SCORE_POLYGON_WIDTH, SCORE_POLYGON_HEIGHT, 0.0f));
	CManager::GetInstance()->GetPlayData()->SetScorePoint(m_pScore);


	//�J�����̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
	CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
	//camera�̎擾
	CCamera* pCamera = &**pCameraAddress;
	//�J�����̈ʒu�ݒ�
	pCamera->SetPosR(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCamera->SetPosV(ROCKET_SCENE_CAMERA_V_POS);

	//�}�X�N�̐���
	m_pDengerMask = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
		                              static_cast<int>(CObject::PRIORITY::MASK));
	m_pDengerMask->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("denger_mask.png"));
	m_pDengerMask->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	return S_OK;
}

//================================================
//�I������
//================================================
void CRocketScene::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CRocketScene::Update(void)
{
	//�����o��
	for (int nCnt = 0; nCnt < ROCKET_SCENE_SMOKE_NUM; nCnt++)
	{
		CSmoke::Create(D3DXVECTOR3(0.0f + ROCKET_SCENE_SMOKE_POS_X_RAND, 0.0f + ROCKET_SCENE_SMOKE_POS_Y_RAND, 0.0f),
			           ROCKET_SCENE_SMOKE_SIZE, D3DXVECTOR3(0.0f, 0.0f, ROCKET_SCENE_SMOKE_ROT_RAND),
			           D3DXVECTOR3(0.0f, -ROCKET_SCENE_ROCKET_SPEED, 0.0f),
			           D3DXVECTOR3(0.0f, 0.0f, ROCKET_SCENE_SMOKE_ADD_ROTATE),
			           ROCKET_SCENE_SMOKE_ADD_SIZE, ROCKET_SCENE_SMOKE_SUBTRACT_ALPHA);
	}
	
	//�X�R�A����
	Score();
	
	//�J��������
	Camera();

	//�}�X�N����
	Mask();

	//���U���g�ɍs���悤�ɂȂ��Ă���
	if (m_bResult == true)
	{
		//�J�E���^�[�����Z
		m_nCounter++;

		//����̒l���傫���Ȃ�����
		if (m_nCounter > ROCKET_SCENE_RESULT_COUNTER)
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

#ifdef _DEBUG
	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//Enter�L�[����������
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
#endif // !_DEBUG
}

//================================================
//�`�揈��
//================================================
void CRocketScene::Draw(void)
{
	
}

//================================================
//�X�R�A����
//================================================
void CRocketScene::Score(void)
{
	if (m_pScore != nullptr)
	{
		//�X�R�A�����Z
		CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore(ROCKET_SCENE_ADD_SCORE);
		//�X�R�A���ő�l�ȏ�ɂȂ�����
		if (CManager::GetInstance()->GetPlayData()->GetScorePoint()->GetScore() >= MAX_SCORE)
		{
			CManager::GetInstance()->GetPlayData()->SetScorePoint(m_pScore);
			//�X�R�A�����Z
			CManager::GetInstance()->GetPlayData()->GetScorePoint()->SetScore(0);
			//�X�R�A��ۑ�
			CManager::GetInstance()->GetPlayData()->SetScore(CManager::GetInstance()->GetPlayData()->GetScorePoint()->GetScore());

			//�X�R�A������
			m_pScore->Uninit();
			m_pScore = nullptr;

			//���U���g�ɍs���悤�ɂ���
			m_bResult = true;

			//����s�\UI�𐶐�
			CObject2D *pUi = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
							                   ROCKET_SCENE_ERROR_SIZE, static_cast<int>(CObject::PRIORITY::UI));
			pUi->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("error.png"));
		}
	}
}

//================================================
//�J��������
//================================================
void CRocketScene::Camera(void)
{
	//�J�����̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
	CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
	//camera�̎擾
	CCamera* pCamera = &**pCameraAddress;

	//���炷�ʂ�ݒ�
	D3DXVECTOR3 shakePos = D3DXVECTOR3(ROCKET_SCENE_CAMERA_SHAKE_POS, ROCKET_SCENE_CAMERA_SHAKE_POS, 0.0f);

	//�ʒu�����炷
	D3DXVECTOR3 posR = shakePos;
	D3DXVECTOR3 posV = ROCKET_SCENE_CAMERA_V_POS + shakePos;

	//�ʒu�ݒ�
	pCamera->SetPosR(posR);
	pCamera->SetPosV(posV);
}

//================================================
//�}�X�N����
//================================================
void CRocketScene::Mask(void)
{
	//�F���擾
	D3DXCOLOR col = m_pDengerMask->GetCol();

	//���Z�����ԂȂ�
	if (m_bAddCol == true)
	{
		//���Z
		col.a += ROCKET_SCENE_MASK_ADD_COL;
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
		col.a -= ROCKET_SCENE_MASK_ADD_COL;
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
