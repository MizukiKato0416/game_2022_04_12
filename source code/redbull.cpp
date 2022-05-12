//=============================================================================
//
// redbull���� [redbull.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "redbull.h"
#include "player.h"
#include "model_single.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define REDBULL_JUMP_POW			(15.0f)		// �W�����v��
#define REDBULL_FORWORD_POW			(40.0f)		// �i��
#define REDBULL_PLAYER_ROTATION_X	(-0.1f)		// �v���C���[�̉�]
#define REDBULL_SLOW_PLAYER_MOVE_Y	(0.2f)		// �X���[���̈ړ���Y
#define REDBULL_SLOW_FORWORD_POW	(0.3f)		// �X���[���̐i��
#define REDBULL_SLOW_COUNT			(30)		// �X���[�ɂ��鎞��

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CRedbull::CRedbull(CObject::PRIORITY Priority) : CHappenig(Priority)
{
	m_bHitPlayer = false;
	m_nCntSlow = 0;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CRedbull::~CRedbull()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CRedbull::Init(void)
{
	CHappenig::Init();
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_REDBULL, NULL, true));
	CObject::SetObjType(CObject::OBJTYPE::REDBULL);

	//�ϐ�������
	m_bHitPlayer = false;
	m_nCntSlow = 0;

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CRedbull::Uninit(void)
{
	CHappenig::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CRedbull::Update(void)
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

				if (m_nCntSlow < REDBULL_SLOW_COUNT)
				{
					//�J�����Y�[������
					SetCameraZoom();

					//�ړ��ʐݒ�
					player->SetMove(D3DXVECTOR3(0.0f, REDBULL_SLOW_PLAYER_MOVE_Y, 0.0f));
					//�O�ɐi�ޗ͐ݒ�
					player->SetMoveForward(REDBULL_SLOW_FORWORD_POW);
					//���ʐݒ�
					player->SetRotSpeed(REDBULL_PLAYER_ROTATION_X);

					//�O���G�t�F�N�g���o�Ă���Ȃ�
					if (player->GetSparkle() == true)
					{
						//�O���G�t�F�N�g������
						player->SetSparkle(false);
					}
				}
				else if (m_nCntSlow == REDBULL_SLOW_COUNT)
				{
					//�W�����v�ʐݒ�
					player->SetJump(REDBULL_JUMP_POW);
					//�O�ɐi�ޗ͂�ݒ�
					player->SetMoveForward(REDBULL_FORWORD_POW);
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
void CRedbull::Draw(void)
{
	CHappenig::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CRedbull *CRedbull::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	CRedbull *redbull = nullptr;
	if (redbull == nullptr)
	{
		redbull = new CRedbull;
		if (redbull != nullptr)
		{
			redbull->m_pos = pos;
			redbull->m_rot = rot;
			redbull->Init();
		}
	}
	return redbull;
}