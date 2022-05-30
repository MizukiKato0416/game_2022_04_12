//=============================================================================
//
// �X�^�[�����O���� [starring.cpp]
// Author : ��������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "starring.h"
#include "player.h"
#include "model_single.h"
#include "play_data.h"
#include "manager.h"
#include "trophy.h"
#include "sound.h"
#include "history_letter.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define STARRING_ROTATION_X			(0.1f)		// ��]
#define STARRING_PLAYER_ROTATION_X	(-0.1f)		// �v���C���[�̉�]
#define STARRING_ROTATION_X_SLOW	(0.02f)		// �X���[���̉�]
#define STARRING_JUMP_POW			(20.0f)		// �W�����v��
#define STARRING_FORWORD_POW		(40.0f)		// �i��
#define STARRING_SLOW_PLAYER_MOVE_Y	(0.2f)		// �X���[���̈ړ���Y
#define STARRING_PLAYER_MOVE_Y		(8.0f)		// ��΂��Ƃ��̈ړ���Y
#define STARRING_SLOW_FORWORD_POW	(0.3f)		// �X���[���̐i��
#define STARRING_SLOW_COUNT			(30)		// �X���[�ɂ��鎞��

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CStarring::CStarring(CObject::PRIORITY Priority) : CHappenig(Priority)
{
	m_bRot = false;
	m_nCntSlow = 0;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CStarring::~CStarring()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CStarring::Init(void)
{
	//���f���̐���
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_STARRING, NULL, true));

	CHappenig::Init();
	
	//��ނ̐ݒ�
	CObject::SetObjType(CObject::OBJTYPE::STAR_RING);

	//�ϐ�������
	m_bRot = false;
	m_nCntSlow = 0;

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CStarring::Uninit(void)
{
	CHappenig::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CStarring::Update(void)
{
	//�T�E���h�擾
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();

	CHappenig::Update();

	//�v���C���[�ɓ���������
	if (CHappenig::HitPlayer() == true)
	{
		//SE�ݒ�
		sound->ControllVoice(CSound::SOUND_LABEL::STAR_RING_SE, 1.4f);
		sound->Play(CSound::SOUND_LABEL::STAR_RING_SE);

		//��]���Ă��Ȃ���ԂȂ�
		if (m_bRot == false)
		{
			//�g���t�B�[�̃t���O��Ԃ��擾
			vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
			//�g���t�B�[���擾�������Ƃ��Ȃ�������
			if (flag[(int)CTrophy::TROPHY::STARRING] == false)
			{
				//�擾������
				flag[(int)CTrophy::TROPHY::STARRING] = true;
				CManager::GetInstance()->GetPlayData()->SetFlag(flag);
				CHistory::Create(CTrophy::TROPHY::STARRING);
			}

			//��]������
			m_bRot = true;
			//�������Ă����Ԃɂ���
			CHappenig::SetHit(true);
		}
	}

	//��]���Ă����ԂȂ�
	if (m_bRot == true)
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

				if (m_nCntSlow < STARRING_SLOW_COUNT)
				{
					//�J�����Y�[������
					SetCameraZoom();

					//�ړ��ʐݒ�
					player->SetMove(D3DXVECTOR3(0.0f, STARRING_SLOW_PLAYER_MOVE_Y, 0.0f));
					//�O�ɐi�ޗ͐ݒ�
					player->SetMoveForward(STARRING_SLOW_FORWORD_POW);
					//���ʐݒ�
					player->SetRotSpeed(STARRING_PLAYER_ROTATION_X);

					//�O���G�t�F�N�g���o�Ă���Ȃ�
					if (player->GetSparkle() == true)
					{
						//�O���G�t�F�N�g������
						player->SetSparkle(false);
					}

					//��]������
					m_rot.x += STARRING_ROTATION_X_SLOW;
				}
				else if(m_nCntSlow == STARRING_SLOW_COUNT)
				{
					//��]������
					m_rot.x += STARRING_ROTATION_X;
					//�������Ă��Ȃ���Ԃɂ���
					CHappenig::SetHit(false);
					//�W�����v�ʐݒ�
					player->SetJump(STARRING_JUMP_POW);
					//�O�ɐi�ޗ͂�ݒ�
					player->SetMoveForward(STARRING_FORWORD_POW);
					//�ړ��ʐݒ�
					player->SetMove(D3DXVECTOR3(0.0f, STARRING_PLAYER_MOVE_Y, 0.0f));
					//��]�̃X�s�[�h��ݒ�
					player->SetRotSpeed(PLAYER_ROTATE);

					//�O���G�t�F�N�g���o�ĂȂ��Ȃ�
					if (player->GetSparkle() == false)
					{
						//�O���G�t�F�N�g���o��
						player->SetSparkle(true);
					}
				}
				else
				{
					//��]������
					m_rot.x += STARRING_ROTATION_X;
				}
			}
		}
		//������ݒ�
		GetModel()->SetRot(m_rot);
	}
}

//=============================================================================
// �`��
//=============================================================================
void CStarring::Draw(void)
{
	CHappenig::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CStarring *CStarring::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	CStarring *star_ring = nullptr;
	if (star_ring == nullptr)
	{
		star_ring = new CStarring;
		if (star_ring != nullptr)
		{
			star_ring->m_pos = pos;
			star_ring->m_rot = rot;
			star_ring->Init();
		}
	}
	return star_ring;
}