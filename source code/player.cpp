//================================================
//�v���C���[����
//Author:��������
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_d.h"
#include "input_mouse.h"
#include "player.h"
#include "motion_player.h"
#include "renderer.h"
#include "model.h"
#include "x_load.h"
#include "floor.h"
#include "model_single.h"
#include "texture.h"
#include "camera.h"
#include "play_data.h"
#include "meshfield.h"
#include "billboard.h"
#include "ui.h"
#include "shadow.h"
#include "sparkle.h"
#include "wind.h"
#include "game01.h"
#include "happening.h"
#include "sound.h"
#include "trophy.h"
#include "history_letter.h"

//================================================
//�}�N����`
//================================================
#define PLAYER_JUMP							(12.0f)		//�W�����v��
#define PLAYER_JUMP_BALANCE_BALL			(12.0f)		//�o�����X�{�[���̃W�����v��
#define PLAYER_JUMP_GIRL					(17.0f)		//���L�R�����̃W�����v��
#define PLAYER_JUMP_MIN						(5.0f)		//�W�����v�͍ŏ��l
#define PLAYER_JUMP_MAX						(30.0f)		//�W�����v�͍ő�l
#define PLAYER_BOUND						(0.8f)		//�o�E���h��
#define PLAYER_MOVE_FORWARD_TRAMPOLINE		(15.0f)		//�g�����|�����̑O�ɐi�ޗ�
#define PLAYER_MOVE_FORWARD_GIRL			(30.0f)		//���L�R�����̑O�ɐi�ޗ�
#define PLAYER_MOVE_FORWARD_SUBTRACTION		(0.985f)	//�O�ɐi�ޗ͂̌��Z��
#define PLAYER_MOVE_FORWARD_MIN				(4.0f)		//�O�ɐi�ޗ͂̍ŏ��l
#define PLAYER_MOVE_FORWARD_MIN_NOT_JUMP	(1.5f)		//�W�����v���Ă��Ȃ��Ƃ��̑O�ɐi�ޗ͂̍ŏ��l
#define PLAYER_MOVE_FORWARD_MAX				(50.0f)		//�O�ɐi�ޗ͂̍ő�l
#define PLAYER_GRAVITY						(0.4f)		//�d�͂̑傫��
#define PLAYER_MOVE_SPEED					(4.0f)		//�ʏ�ړ��̈ړ���
#define PLAYER_SIZE							(10.0f)		//�v���C���[�̃T�C�Y�����l
#define PLAYER_SPARKLE_NUM					(3)			//�O���G�t�F�N�g�̐�

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CPlayer::CPlayer(CObject::PRIORITY Priority):CObject(Priority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_offsetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = nullptr;
	memset(&m_apModel, NULL, sizeof(m_apModel));
	m_pMotionPlayer = nullptr;
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_bShot = false;
	m_fJump = 0.0f;
	m_fMoveForward = 0.0f;
	m_fBoundMove = 0.0f;
	m_fRotSpeed = 0.0f;
	m_pSparkle = nullptr;
	m_bObjParent = false;
	m_bSparkle = false;
	m_state = PLAYER_STATE::NONE;
	m_nStateCounter = 0;
	m_pWind = nullptr;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CPlayer::~CPlayer()
{

}

//================================================
//����������
//================================================
HRESULT CPlayer::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_offsetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_bShot = false;
	m_fJump = 0.0f;
	m_fMoveForward = 0.0f;
	m_fBoundMove = 0.0f;
	m_pSparkle = nullptr;
	m_bObjParent = false;
	m_bSparkle = true;
	m_fRotSpeed = PLAYER_ROTATE;
	m_state = PLAYER_STATE::NORMAL;
	m_nStateCounter = 0;
	m_pWind = nullptr;

	//���f���̐���
	//text�t�@�C���ǂݍ���
	FILE *pFile = fopen("data/MOTION/motion_player.txt", "r");
	if (pFile != nullptr)
	{
		char cString[128];
		//��s���ۑ�
		while (fgets(cString, 128, pFile) != NULL)
		{
			//�������ۑ�
			fscanf(pFile, "%s", cString);
			//������̒���PARTSSET����������
			if (strncmp("PARTSSET", cString, 9) == 0)
			{
				//�C���f�b�N�X�ǂݍ���
				int nIndex = 0;
				fscanf(pFile, "%*s%*s%d", &nIndex);
				fscanf(pFile, "%*s%*s");

				//�e�ǂݍ���
				int nParent = 0;
				fscanf(pFile, "%*s%*s%d", &nParent);
				fscanf(pFile, "%*s%*s");

				//�ʒu�ǂݍ���
				D3DXVECTOR3 modelPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				fscanf(pFile, "%*s%*s%f%f%f", &modelPos.x, &modelPos.y, &modelPos.z);

				//�����ǂݍ���
				D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				fscanf(pFile, "%*s%*s%f%f%f", &rot.x, &rot.y, &rot.z);

				//���f������
				int nModelType = 0;

				//�����t�擾
				if (strncmp("695", CManager::GetInstance()->GetPlayData()->GetPasword().c_str(), 4) == 0)
				{
					//�g���t�B�[�̃t���O��Ԃ��擾
					vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
					//�g���t�B�[���擾�������Ƃ��Ȃ�������
					if (flag[(int)CTrophy::TROPHY::GIRL] == false)
					{
						//�擾������
						flag[(int)CTrophy::TROPHY::GIRL] = true;

						CManager::GetInstance()->GetPlayData()->SetFlag(flag);
						CHistory::Create(CTrophy::TROPHY::GIRL);
					}
					nModelType = CXload::X_TYPE_PLAYER_GIRL_BODY;
				}
				else
				{
					nModelType = CXload::X_TYPE_PLAYER_BODY;
				}
				
				m_apModel[nIndex] = CModel::Create(modelPos, rot, CManager::GetInstance()->GetXload()->GetType(nModelType + nIndex));


				//�e�̐ݒ�
				if (nParent == -1)
				{
					m_apModel[nIndex]->SetParent(nullptr);
				}
				else
				{
					m_apModel[nIndex]->SetParent(m_apModel[nParent]);
				}

				if (nIndex == MAX_PLAYER_MODEL - 1)
				{
					break;
				}
			}
		}
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���\n");
	}
	fclose(pFile);

	//�ʒu�̐ݒ�
	SetPos(m_pos);
	SetPosOld(m_posOld);

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CObject::OBJTYPE::PLAYER);

	//���[�V�����̐���
	m_pMotionPlayer = CMotionPlayer::Create(this);
	m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL, this);

	//�T�C�Y���擾
	D3DXVECTOR3 modelSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelSize = m_apModel[0]->GetSize();

	//�T�C�Y��X��Z���ׂđ傫���ق���X��Z���ꂼ��Ɋ��蓖�Ă�
	if (modelSize.x >= modelSize.z)
	{
		m_size = D3DXVECTOR3(modelSize.x + PLAYER_SIZE, modelSize.y, modelSize.x + PLAYER_SIZE);
	}
	else
	{
		m_size = D3DXVECTOR3(modelSize.z + PLAYER_SIZE, modelSize.y, modelSize.z + PLAYER_SIZE);
	}

	//�T�C�Y�̐ݒ�
	SetSize(m_size);

	//�e�̐ݒ�
	CShadow::Create(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z), D3DXVECTOR3(m_size.x, 0.0f, m_size.z), this);

	return S_OK;
}

//================================================
//�I������
//================================================
void CPlayer::Uninit(void)
{
	Release();
}

//================================================
//�X�V����
//================================================
void CPlayer::Update(void)
{
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	m_pos = pos;
	m_posOld = pos;

	//1�t���[���O�̈ʒu�ݒ�
	SetPosOld(m_posOld);

	//�d��
	m_move.y -= PLAYER_GRAVITY;

	m_pos += m_move;		//�ړ��ʔ��f

	//��]�̊���
	Rotate();

	//���[�V����
	m_pMotionPlayer->Update(this);

	//�ʒu���f
	SetPos(m_pos);

	//��Ԃɂ�鏈������
	State();

	//���˂��Ă����ԂȂ�
	if (m_bShot == true)
	{
		//�W�����v�͂�����̒l�ȉ��ɂȂ����Ƃ�
		if (m_fJump <= PLAYER_JUMP)
		{
			//�O�ɐi�ޗ͂����Ȃ�����
			m_fMoveForward *= PLAYER_MOVE_FORWARD_SUBTRACTION;
		}
		
		//�O�ɐi�ޗ͂����̐��Ŋ���̒l��菬�����Ȃ�����
		if (m_fMoveForward < PLAYER_MOVE_FORWARD_MIN && m_fMoveForward > 0.0f)
		{
			//�܂��W�����v���Ă����ԂȂ�
			if (m_fJump > 0.0f)
			{
				//���������O�ɓ�����
				m_fMoveForward = PLAYER_MOVE_FORWARD_MIN;
			}
			else
			{
				//�O�ɐi�ޗ͂�����̒l��菬�����Ȃ�����
				if (m_fMoveForward < PLAYER_MOVE_FORWARD_MIN_NOT_JUMP)
				{
					//0�ɂ���
					m_fMoveForward = 0.0f;

					//���[�V���������n�ł͂Ȃ�������
					if (m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_DIVE_LAND)
					{
						//���n���[�V�����ɂ���
						m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_DIVE_LAND, this);
					}
				}
			}
		}
		else if (m_fMoveForward > -PLAYER_MOVE_FORWARD_MIN && m_fMoveForward < 0.0f)
		{//�O�ɐi�ޗ͂����̐��Ŋ���̒l���傫���Ȃ�����
		 //�܂��W�����v���Ă����ԂȂ�
			if (m_fJump > 0.0f)
			{
				//�����������ɓ�����
				m_fMoveForward = -PLAYER_MOVE_FORWARD_MIN;
			}
			else
			{
				//�O�ɐi�ޗ͂�����̒l���傫���Ȃ�����
				if (m_fMoveForward > -PLAYER_MOVE_FORWARD_MIN_NOT_JUMP)
				{
					//0�ɂ���
					m_fMoveForward = 0.0f;

					//���[�V���������n�ł͂Ȃ�������
					if (m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_DIVE_LAND)
					{
						//���n���[�V�����ɂ���
						m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_DIVE_LAND, this);
					}
				}
			}
		}

		//�~�܂��Ă��Ȃ�������
		if (m_fMoveForward != 0.0f)
		{
			//�W�����v�͂�0���傫��������
			if (m_fJump > 0.0f)
			{
				//�v���C���[����]������
				m_rot.x += m_fRotSpeed;
			}
			else
			{
				//��]�l��0����Ȃ�������
				if (m_rot.x != 0.0f)
				{
					//��]�l��0�ɂ���
					m_rot.x = 0.0f;
				}

				//���[�V�������_�C�u�ł͂Ȃ�������
				if (m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_DIVE)
				{
					if (strncmp("KIYO", CManager::GetInstance()->GetPlayData()->GetPasword().c_str(), 5) == 0)
					{
						vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
						if (flag[(int)CTrophy::TROPHY::KIYO] == false)
						{
							flag[(int)CTrophy::TROPHY::KIYO] = true;

							CManager::GetInstance()->GetPlayData()->SetFlag(flag);
							CHistory::Create(CTrophy::TROPHY::KIYO);
						}
						sound->ControllVoice(CSound::SOUND_LABEL::KIYO_BREAK_SE, 0.8f);
						sound->Play(CSound::SOUND_LABEL::KIYO_BREAK_SE);
					}
					else
					{
						sound->ControllVoice(CSound::SOUND_LABEL::BREAK_SE, 1.4f);
						sound->Play(CSound::SOUND_LABEL::BREAK_SE);
					}

					//���n���[�V�����ɂ���
					m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_DIVE, this);
				}
			}

			//�O���G�t�F�N�g���o����ԂȂ�
			if (m_bSparkle == true)
			{
				//�O���G�t�F�N�g�̐���
				m_pSparkle = CSparkle::Create(m_pos, D3DXVECTOR3(SPARKLE_SIZE_RAND, SPARKLE_SIZE_RAND, 0.0f), D3DXVECTOR3(-m_fMoveForward, 0.0f, 0.0f),
				                              PLAYER_SPARKLE_NUM);
				m_pSparkle->SetMove(D3DXVECTOR3(-m_fMoveForward, 0.0f, 0.0f));
			}
		}
		else
		{//�~�܂��Ă�����
			//�W�����v�͂�0�ŕ��ɓ������Ă��Ȃ��Ƃ�
			if (m_fJump == 0.0f && CHappenig::GetHit() == false)
			{
				//�Q�[���V�[���Ȃ�
				if (CManager::GetInstance()->GetMode() == CManager::MODE::GAME01)
				{
					//�I����ԂłȂ��Ȃ�
					if (CManager::GetInstance()->GetGame01()->GetFinish() == false)
					{
						//�I����Ԃɐݒ肷��
						CManager::GetInstance()->GetGame01()->SetFinish(true);
					}
				}
			}
		}
	}

	//���Ƃ̓����蔻��
	if (CFloor::Collision(this) == true)
	{
		//�d�͂�0�ɂ���
		m_move.y = 0.0f;
		//���˂��Ă����ԂȂ�
		if (m_bShot == true)
		{
			//�W�����v�͂�����������
			m_fJump *= PLAYER_BOUND;
			//�W�����v�͂�����̒l��菬�����Ȃ�����
			if (m_fJump < PLAYER_JUMP_MIN)
			{
				m_fJump = 0.0f;
			}
			//�o�E���h������
			m_move.y = m_fJump;

			if (m_fJump > 0.0f)
			{
				sound->ControllVoice(CSound::SOUND_LABEL::JUMP_SE, 1.4f);
				sound->Play(CSound::SOUND_LABEL::JUMP_SE);
			}

			//�o�E���h����u�Ԃ̈ړ��ʂ�ݒ�
			m_fBoundMove = m_move.y;
		}
	}

	//�ʒu�擾
	pos = GetPos();
	m_pos = pos;
}

//================================================
//�`�揈��
//================================================
void CPlayer::Draw(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X

	D3DXMatrixIdentity(&m_mtxWorld);		//�v���C���[�̃��[���h�}�g���b�N�X�̏�����

	D3DXVECTOR3 pos, rot;

	//�e�q�֌W�������Ă�����
	if (m_bObjParent == true)
	{
		pos = m_offsetPos;
		rot = m_rot;
	}
	else
	{//�����Ă��Ȃ�������
		pos = m_pos;
		rot = m_rot;
	}

	//�v���C���[�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_bObjParent == true)
	{
		D3DXMATRIX mtxParent = *m_mtxWorldParent;

		//�Z�o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);
	}

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���f���̕`��
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		m_apModel[nCntModel]->Draw();
	}
}

//================================================
//��������
//================================================
CPlayer *CPlayer::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	//�C���X�^���X�̐���
	CPlayer *pPlayer = nullptr;
	if (pPlayer == nullptr)
	{
		pPlayer = new CPlayer;
		if (pPlayer != nullptr)
		{
			pPlayer->m_pos = pos;
			pPlayer->m_posOld = pos;
			pPlayer->m_rot = rot;
			pPlayer->Init();
		}
	}
	return pPlayer;
}

//================================================
//���f���̈ʒu�ݒ菈��
//================================================
void CPlayer::SetModelPos(const int &nCntModel, const D3DXVECTOR3 &pos)
{
	m_apModel[nCntModel]->SetPos(pos);
}

//================================================
//���f���̈ʒu�擾����
//================================================
D3DXVECTOR3 CPlayer::GetModelPos(const int &nCntModel)
{
	return m_apModel[nCntModel]->GetPos();
}

//================================================
//���f���̌����ݒ菈��
//================================================
void CPlayer::SetModelRot(const int &nCntModel, const D3DXVECTOR3 &rot)
{
	m_apModel[nCntModel]->SetRot(rot);
}

//================================================
//���f���̌����擾����
//================================================
D3DXVECTOR3 CPlayer::GetModelRot(const int &nCntModel)
{
	return m_apModel[nCntModel]->GetRot();
}

//================================================
//���f���̓�������
//================================================
void CPlayer::Move(void)
{
	//�p�b�hD�擾����
	CInputPadD *pInputPadD = CManager::GetInstance()->GetInputPadD();
	DIJOYSTATE2 JoyStick = pInputPadD->GetGamepad();

	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�p�b�hX�擾����
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInstance()->GetInputPadX();

	D3DXVECTOR3 rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//camera�̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
	CCamera **pCameraAddress = CManager::GetInstance()->GetCamera();

	for (int nCntCamera = 0; nCntCamera < MAX_MAIN_CAMERA; nCntCamera++, pCameraAddress++)
	{
		//camera�̎擾
		CCamera *pCamera = &**pCameraAddress;
		if (pCamera != nullptr)
		{
			//camera�̌����擾
			rotCamera = pCamera->GetRotV();
		}
	}

	//�ړ��ʐݒ�p�ϐ�
	float fSpeed = PLAYER_MOVE_SPEED;

	//�X�e�B�b�N�̌X������������܂���WASD����������
	if ((float)JoyStick.lX != 0.0f || (float)JoyStick.lY != 0.0f || 
		pInputKeyboard->GetPress(DIK_W) == true || pInputKeyboard->GetPress(DIK_A) == true ||
		pInputKeyboard->GetPress(DIK_S) == true || pInputKeyboard->GetPress(DIK_D) == true)
	{
		//�ړI�̌�����ݒ�
		if ((float)JoyStick.lX != 0.0f || (float)JoyStick.lY != 0.0f)
		{
			m_fObjectiveRot = rotCamera.y + atan2f((float)JoyStick.lY, (float)JoyStick.lX) + D3DX_PI / 2.0f;
		}
		else if (pInputKeyboard->GetPress(DIK_W) == true)
		{
			if (pInputKeyboard->GetPress(DIK_A) == true)
			{
				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y - D3DX_PI / 4.0f;
			}
			else if (pInputKeyboard->GetPress(DIK_D) == true)
			{
				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y + D3DX_PI / 4.0f;
			}
			else
			{
				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{
			if (pInputKeyboard->GetPress(DIK_A) == true)
			{
				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y - D3DX_PI / 4.0f * 3.0f;
			}
			else if (pInputKeyboard->GetPress(DIK_D) == true)
			{
				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y + D3DX_PI / 4.0f * 3.0f;
			}
			else
			{
				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y + D3DX_PI;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			//�ړI�̌�����ݒ�
			m_fObjectiveRot = rotCamera.y - D3DX_PI / 2.0f;
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			//�ړI�̌�����ݒ�
			m_fObjectiveRot = rotCamera.y + D3DX_PI / 2.0f;
		}

		//�ړ��ʉ��Z
		m_move.x = sinf(m_fObjectiveRot + D3DX_PI) * fSpeed;
		m_move.z = cosf(m_fObjectiveRot + D3DX_PI) * fSpeed;
		//��]��������
		m_bRotate = true;

		if (m_pMotionPlayer->GetMotion() != CMotionRoad::MOTION_PLAYER_TYPE_MOVE)		//�ړ����[�V�����łȂ�
		{
			//�ړ����[�V�����ɂ���
			m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_MOVE, this);
		}
	}
	else
	{//�X�e�B�b�N�ɌX�����Ȃ�������

		//�ړ��ʂ��[���ɂ���
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		//�ړ����[�V������������
		if (m_pMotionPlayer->GetMotion() == CMotionRoad::MOTION_PLAYER_TYPE_MOVE)
		{
			//�j���[�g�������[�V�����ɂ���
			m_pMotionPlayer->SetMotion(CMotionRoad::MOTION_PLAYER_TYPE_NEUTRAL, this);
		}
	}
}

//================================================
//��]����
//================================================
void CPlayer::Rotate(void)
{
	//��]�������ԂȂ�
	if (m_bRotate == true)
	{
		//�ړI�̌������v�Z
		if (m_fObjectiveRot > D3DX_PI)
		{
			m_fObjectiveRot = -D3DX_PI - (D3DX_PI - m_fObjectiveRot);
		}
		else if (m_fObjectiveRot < -D3DX_PI)
		{
			m_fObjectiveRot = D3DX_PI - (-D3DX_PI - m_fObjectiveRot);
		}

		//�v���C���[�̌��݂̌������Ƃɂ��ꂼ�������ς���ʂ��v�Z
		if (m_rot.y < 0.0f && -m_rot.y + m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (-D3DX_PI - m_rot.y) + -(D3DX_PI - m_fObjectiveRot);
		}
		else if (m_rot.y >= D3DX_PI / 2.0f && m_rot.y - m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (D3DX_PI - m_rot.y) - (-D3DX_PI - m_fObjectiveRot);
		}
		else
		{
			m_fNumRot = (m_fObjectiveRot - m_rot.y);
		}

		//�v���C���[�̌����ɉ��Z
		m_rot.y += m_fNumRot * 0.2f;

		//����̒l�ɒB�������]����߂�
		if (m_rot.y - m_fObjectiveRot < 0.001f && m_rot.y - m_fObjectiveRot > -0.001f)
		{
			m_bRotate = false;
		}
	}

	//�΂��傫���Ȃ�����-2�΂���
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{	//-�΂�菬�����Ȃ�����+2�΂���
		m_rot.y += D3DX_PI * 2.0f;
	}
}

//================================================
//��ԏ���
//================================================
void CPlayer::State(void)
{
	switch (m_state)
	{
	case CPlayer::PLAYER_STATE::NORMAL:
		break;
	case CPlayer::PLAYER_STATE::WIND:
		//�J�E���^�[�𑝂₷
		m_nStateCounter++;

		//����̒l���傫���Ȃ�����
		if (m_nStateCounter > 120)
		{
			//0�ɂ���
			m_nStateCounter = 0;
			//��Ԃ�ʏ�ɂ���
			m_state = PLAYER_STATE::NORMAL;

			//���G�t�F�N�g����������Ă�����
			if (m_pWind != nullptr)
			{
				//����
				m_pWind->Uninit();
				m_pWind = nullptr;
				break;
			}
		}
		else
		{
			//���G�t�F�N�g����������Ă��Ȃ�������
			if (m_pWind == nullptr)
			{
				m_pWind = CWind::Create(m_pos, D3DXVECTOR3(100.0f, 200.0f, 0.0f), 0);
			}

			//�ʒu���擾
			D3DXVECTOR3 pos = m_pWind->GetPos();
			//�ʒu���v���C���[�Ɠ����ɂ���
			pos = m_pos;
			//�ʒu��ݒ�
			m_pWind->SetPos(pos, m_pWind->GetSize());
		}
		break;
	case CPlayer::PLAYER_STATE::WING:
		break;
	case CPlayer::PLAYER_STATE::MAX:
		break;
	default:
		break;
	}
}

//================================================
//�v���C���[�Ƃ̓����蔻��
//================================================
void CPlayer::Collision(CObject *&pSubjectObject, const float &fObjRadius)
{
	//�I�u�W�F�N�g��������|�C���^
	vector<CObject*> object;

	//�擪�̃|�C���^����
	object = CObject::GetObject(static_cast<int>(CObject::PRIORITY::PLAYER));
	int nProprty_Size = object.size();

	for (int nCnt = 0; nCnt < nProprty_Size; nCnt++)
	{
		//�I�u�W�F�N�g�̎�ނ��v���C���[��������
		if (object[nCnt]->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//�v���C���[�ɃL���X�g
			CPlayer *pPlayerObj = nullptr;
			pPlayerObj = (CPlayer*)object[nCnt];

			//�I�u�W�F�N�g�̈ʒu���擾
			D3DXVECTOR3 posObj = pSubjectObject->GetPos();

			//�v���C���[����Ώۂ̃I�u�W�F�N�g�܂ł̋��������߂�
			float fRadius = sqrtf((posObj.x - pPlayerObj->m_pos.x) * (posObj.x - pPlayerObj->m_pos.x) +
				(posObj.z - pPlayerObj->m_pos.z) * (posObj.z - pPlayerObj->m_pos.z));
			//�v���C���[�ƑΏۂ̃I�u�W�F�N�g�̊p�x�����߂�
			float fRot = atan2((posObj.x - pPlayerObj->m_pos.x), (posObj.z - pPlayerObj->m_pos.z)) - D3DX_PI;

			//���߂��������v���C���[�̔��a�ƑΏۂ̃I�u�W�F�N�g�̔��a�𑫂������l�ȉ���������
			if (fRadius <= pPlayerObj->m_size.x / 2.0f + fObjRadius)
			{
				//�v���C���[�̈ʒu�������o��
				pPlayerObj->m_pos.x = posObj.x + (sinf(fRot) * (pPlayerObj->m_size.x / 2.0f + fObjRadius));
				pPlayerObj->m_pos.z = posObj.z + (cosf(fRot) * (pPlayerObj->m_size.x / 2.0f + fObjRadius));

				//�ʒu�ݒ�
				pPlayerObj->SetPos(pPlayerObj->m_pos);

				//���f���Ƃ̓����蔻��
				CModelSingle::Collision(pPlayerObj);
			}
		}
	}
}

//================================================
//�v���C���[�Ƃ̏Փ˔���݂̂̏���
//================================================
bool CPlayer::CollisionOnly(CObject *&pSubjectObject, const float &fObjRadius)
{
	//�I�u�W�F�N�g�̈ʒu���擾
	D3DXVECTOR3 posObj = pSubjectObject->GetPos();

	//�v���C���[����Ώۂ̃I�u�W�F�N�g�܂ł̋��������߂�
	float fRadius = sqrtf((posObj.x - m_pos.x) * (posObj.x - m_pos.x) +
		(posObj.z - m_pos.z) * (posObj.z - m_pos.z));

	//���߂��������v���C���[�̔��a�ƑΏۂ̃I�u�W�F�N�g�̔��a�𑫂������l�ȉ���������
	if (fRadius <= m_size.x / 2.0f + fObjRadius)
	{
		//�������Ă���
		return true;
	}

	return false;
}

//================================================
//�O�ɐi�ޗ͐ݒ菈��
//================================================
void CPlayer::SetMoveForward(const float & fMoveForward)
{
	m_fMoveForward = fMoveForward;
	//�O�ɐi�ޗ͂�����̒l���傫���Ȃ�����
	if (m_fMoveForward >= PLAYER_MOVE_FORWARD_MAX)
	{
		//�ő�l�ɂ���
		m_fMoveForward = PLAYER_MOVE_FORWARD_MAX;
	}
}

//================================================
//�W�����v�͐ݒ菈��
//================================================
void CPlayer::SetJump(const float & fJump)
{
	m_fJump = fJump;
	//�W�����v�ʂ�����̒l���傫���Ȃ�����
	if (m_fJump > PLAYER_JUMP_MAX)
	{
		//�ő�l�ɐݒ肷��
		m_fJump = PLAYER_JUMP_MAX;
	}
}
