//=============================================================================
//
// �t�@������ [fan.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "fan.h"
#include "player.h"
#include "model_single.h"
#include "wind.h"
#include "model.h"
#include "play_data.h"
#include "manager.h"
#include "trophy.h"
#include "sound.h"
#include "history_letter.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FAN_JUMP_POW					(22.0f)									// �W�����v��
#define FAN_FORWORD_POW					(23.0f)									// �i��
#define FAN_PLAYER_ROTATION_X			(-0.1f)									// �v���C���[�̉�]
#define FAN_SLOW_PLAYER_MOVE_Y			(0.2f)									// �X���[���̈ړ���Y
#define FAN_SLOW_FORWORD_POW			(0.3f)									// �X���[���̐i��
#define FAN_SLOW_COUNT					(30)									// �X���[�ɂ��鎞��
#define FAN_WIND_EFFECT_SIZE			(D3DXVECTOR3(200.0f, 300.0f, 0.0f))		// ���G�t�F�N�g�̃T�C�Y
#define FAN_ROTATE_SPEED				(0.5f)									// �t�@���̉�]���x

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CFan::CFan(CObject::PRIORITY Priority) : CHappenig(Priority)
{
	m_bHitPlayer = false;
	m_nCntSlow = 0;
	memset(m_apWind, NULL, sizeof(m_apWind[FAN_MAX_WIND_EFFECT]));
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CFan::~CFan()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CFan::Init(void)
{
	//���f���̐���
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_FAN, NULL, true));
	CHappenig::Init();
	
	CObject::SetObjType(CObject::OBJTYPE::FAN);

	//���̐���
	for (int nCntWind = 0; nCntWind < FAN_MAX_WIND_EFFECT; nCntWind++)
	{
		m_apWind[nCntWind] = CWind::Create(D3DXVECTOR3(m_pos.x, m_pos.y + FAN_WIND_EFFECT_SIZE.y / 2.0f, m_pos.z),
			                               FAN_WIND_EFFECT_SIZE, int(0 + WIND_MAX_PATTERN / 2.0f * nCntWind));
	}

	//�ϐ�������
	m_bHitPlayer = false;
	m_nCntSlow = 0;

	

	//���f���̏㒸�_�̈ʒu���擾
	D3DXVECTOR3 vtxPos[4];
	vtxPos[0] = GetModel()->GetModel()->GetVtxPos(0);
	vtxPos[1] = GetModel()->GetModel()->GetVtxPos(1);
	vtxPos[2] = GetModel()->GetModel()->GetVtxPos(4);
	vtxPos[3] = GetModel()->GetModel()->GetVtxPos(5);
	
	//���f���̃T�C�YY�𕗂̃G�t�F�N�g�̃T�C�Y��3����2�������΂�
	vtxPos[0].y += FAN_WIND_EFFECT_SIZE.y / 3.0f * 2.0f;
	vtxPos[1].y += FAN_WIND_EFFECT_SIZE.y / 3.0f * 2.0f;
	vtxPos[2].y += FAN_WIND_EFFECT_SIZE.y / 3.0f * 2.0f;
	vtxPos[3].y += FAN_WIND_EFFECT_SIZE.y / 3.0f * 2.0f;

	//�T�C�Y��ݒ�
	GetModel()->GetModel()->SetVtxPos(0, vtxPos[0]);
	GetModel()->GetModel()->SetVtxPos(1, vtxPos[1]);
	GetModel()->GetModel()->SetVtxPos(4, vtxPos[2]);
	GetModel()->GetModel()->SetVtxPos(5, vtxPos[3]);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CFan::Uninit(void)
{
	CHappenig::Uninit();

	for (int nCntWind = 0; nCntWind < FAN_MAX_WIND_EFFECT; nCntWind++)
	{
		if (m_apWind[nCntWind] != nullptr)
		{
			m_apWind[nCntWind]->Uninit();
			m_apWind[nCntWind] = nullptr;
		}
	}
}

//=============================================================================
// �X�V
//=============================================================================
void CFan::Update(void)
{
	//�T�E���h�擾
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();

	CHappenig::Update();

	for (int nCntWind = 0; nCntWind < FAN_MAX_WIND_EFFECT; nCntWind++)
	{
		//���G�t�F�N�g�̈ʒu�ƃT�C�Y���擾
		D3DXVECTOR3 windPos = m_apWind[nCntWind]->GetPos();
		D3DXVECTOR3 windSize = m_apWind[nCntWind]->GetSize();

		//���G�t�F�N�g�̈ʒu���t�@���̈ʒu�Ɠ����ɂ���
		windPos.x = GetModel()->GetPos().x;

		//���̈ʒu��ݒ�
		m_apWind[nCntWind]->SetPos(windPos, windSize);
	}

	//�������擾
	m_rot = GetModel()->GetRot();
	//��]������
	m_rot.y += FAN_ROTATE_SPEED;
	//������ݒ�
	GetModel()->SetRot(m_rot);

	//�v���C���[�ɓ���������
	if (CHappenig::HitPlayer() == true)
	{
		//�v���C���[�ɓ���������Ԃɂ���
		if (m_bHitPlayer == false)
		{
			//�g���t�B�[�̃t���O��Ԃ��擾
			vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
			//�g���t�B�[���擾�������Ƃ��Ȃ�������
			if (flag[(int)CTrophy::TROPHY::FAN] == false)
			{
				//�擾������
				flag[(int)CTrophy::TROPHY::FAN] = true;

				CManager::GetInstance()->GetPlayData()->SetFlag(flag);
				CHistory::Create(CTrophy::TROPHY::FAN);
			}

			//SE�ݒ�
			sound->ControllVoice(CSound::SOUND_LABEL::FAN_SE, 1.4f);
			sound->Play(CSound::SOUND_LABEL::FAN_SE);

			m_bHitPlayer = true;
			//�������Ă����Ԃɂ���
			CHappenig::SetHit(true);
		}
	}

	//�v���C���[�ɓ���������ԂȂ�
	if (m_bHitPlayer == true)
	{
		//�J�E���^�[�����Z
		m_nCntSlow++;

		//�������擾
		m_rot = GetModel()->GetRot();

		//�I�u�W�F�N�g��������|�C���^
		vector<CObject*> object;

		//�擪�̃|�C���^����
		object = CObject::GetObject(static_cast<int>(CObject::PRIORITY::PLAYER));
		int object_size = object.size();

		for (int count_object = 0; count_object < object_size; count_object++)
		{
			//�v���C���[��������
			if (object[count_object]->GetObjType() == CObject::OBJTYPE::PLAYER)
			{
				//�v���C���[�ɃL���X�g
				CPlayer *player = static_cast<CPlayer*>(object[count_object]);

				if (m_nCntSlow < FAN_SLOW_COUNT)
				{
					//�J�����Y�[������
					SetCameraZoom();

					//�ړ��ʐݒ�
					player->SetMove(D3DXVECTOR3(0.0f, FAN_SLOW_PLAYER_MOVE_Y, 0.0f));
					//�O�ɐi�ޗ͐ݒ�
					player->SetMoveForward(FAN_SLOW_FORWORD_POW);
					//���ʐݒ�
					player->SetRotSpeed(FAN_PLAYER_ROTATION_X);

					//�O���G�t�F�N�g���o�Ă���Ȃ�
					if (player->GetSparkle() == true)
					{
						//�O���G�t�F�N�g������
						player->SetSparkle(false);
					}
				}
				else if (m_nCntSlow == FAN_SLOW_COUNT)
				{
					//�������Ă��Ȃ���Ԃɂ���
					CHappenig::SetHit(false);
					//�W�����v�ʐݒ�
					player->SetJump(FAN_JUMP_POW);
					//�O�ɐi�ޗ͂�ݒ�
					player->SetMoveForward(FAN_FORWORD_POW);
					//�ړ��ʐݒ�
					player->SetMove(D3DXVECTOR3(0.0f, player->GetJump(), 0.0f));
					//�o�E���h����u�Ԃ̈ړ��ʂ�ݒ�
					player->SetBoundMove(player->GetJump());
					//��]�̃X�s�[�h��ݒ�
					player->SetRotSpeed(PLAYER_ROTATE);

					//�O���G�t�F�N�g���o�ĂȂ��Ȃ�
					if (player->GetSparkle() == false)
					{
						//�O���G�t�F�N�g���o��
						player->SetSparkle(true);
					}
				}
			}
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void CFan::Draw(void)
{
	CHappenig::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CFan *CFan::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	CFan *fan = nullptr;
	if (fan == nullptr)
	{
		fan = new CFan;
		if (fan != nullptr)
		{
			fan->m_pos = pos;
			fan->m_rot = rot;
			fan->Init();
		}
	}
	return fan;
}