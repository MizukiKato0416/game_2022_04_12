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

//=============================================================================
// �}�N����`
//=============================================================================
#define FAN_JUMP_POW			(25.0f)		// �W�����v��
#define FAN_FORWORD_POW			(20.0f)		// �i��
#define FAN_PLAYER_ROTATION_X	(-0.1f)		// �v���C���[�̉�]
#define FAN_SLOW_PLAYER_MOVE_Y	(0.2f)		// �X���[���̈ړ���Y
#define FAN_SLOW_FORWORD_POW	(0.3f)		// �X���[���̐i��
#define FAN_SLOW_COUNT			(30)		// �X���[�ɂ��鎞��

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CFan::CFan(CObject::PRIORITY Priority) : CHappenig(Priority)
{
	m_bHitPlayer = false;
	m_nCntSlow = 0;
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
	CHappenig::Init();
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_FAN, NULL, true));
	CObject::SetObjType(CObject::OBJTYPE::FAN);

	//�ϐ�������
	m_bHitPlayer = false;
	m_nCntSlow = 0;

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CFan::Uninit(void)
{
	CHappenig::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CFan::Update(void)
{
	CHappenig::Update();
	if (CHappenig::HitPlayer() == true)
	{
		if (m_bHitPlayer == false)
		{
			m_bHitPlayer = true;
		}
	}


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