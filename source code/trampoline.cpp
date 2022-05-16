//=============================================================================
//
// �g�����|�������� [trampoline.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "trampoline.h"
#include "player.h"
#include "model_single.h"
#include "play_data.h"
#include "manager.h"
#include "trophy.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TRAMPOLINE_JUMP_POW				(21.0f)		// �W�����v��
#define TRAMPOLINE_FORWORD_POW			(25.0f)		// �i��
#define TRAMPOLINE_PLAYER_ROTATION_X	(-0.1f)		// �v���C���[�̉�]
#define TRAMPOLINE_SLOW_PLAYER_MOVE_Y	(0.2f)		// �X���[���̈ړ���Y
#define TRAMPOLINE_SLOW_FORWORD_POW		(0.3f)		// �X���[���̐i��
#define TRAMPOLINE_SLOW_COUNT			(30)		// �X���[�ɂ��鎞��

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTrampoline::CTrampoline(CObject::PRIORITY Priority) : CHappenig(Priority)
{
	m_bHitPlayer = false;
	m_nCntSlow = 0;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CTrampoline::~CTrampoline()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CTrampoline::Init(void)
{
	CHappenig::Init();
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_TRAMPLINE, NULL, true));
	CObject::SetObjType(CObject::OBJTYPE::TRAMPOLINE);

	//�ϐ�������
	m_bHitPlayer = false;
	m_nCntSlow = 0;

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CTrampoline::Uninit(void)
{
	CHappenig::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CTrampoline::Update(void)
{
	CHappenig::Update();
	if (CHappenig::HitPlayer() == true)
	{
		if (m_bHitPlayer == false)
		{
			//�g���t�B�[�̃t���O��Ԃ��擾
			vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
			//�g���t�B�[���擾�������Ƃ��Ȃ�������
			if (flag[(int)CTrophy::TROPHY::TRAMPOLINE] == false)
			{
				//�擾������
				flag[(int)CTrophy::TROPHY::TRAMPOLINE] = true;

				CManager::GetInstance()->GetPlayData()->SetFlag(flag);
			}

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

				if (m_nCntSlow < TRAMPOLINE_SLOW_COUNT)
				{
					//�J�����Y�[������
					SetCameraZoom();

					//�ړ��ʐݒ�
					player->SetMove(D3DXVECTOR3(0.0f, TRAMPOLINE_SLOW_PLAYER_MOVE_Y, 0.0f));
					//�O�ɐi�ޗ͐ݒ�
					player->SetMoveForward(TRAMPOLINE_SLOW_FORWORD_POW);
					//���ʐݒ�
					player->SetRotSpeed(TRAMPOLINE_PLAYER_ROTATION_X);

					//�O���G�t�F�N�g���o�Ă���Ȃ�
					if (player->GetSparkle() == true)
					{
						//�O���G�t�F�N�g������
						player->SetSparkle(false);
					}
				}
				else if (m_nCntSlow == TRAMPOLINE_SLOW_COUNT)
				{
					//�W�����v�ʐݒ�
					player->SetJump(TRAMPOLINE_JUMP_POW);
					//�O�ɐi�ޗ͂�ݒ�
					player->SetMoveForward(TRAMPOLINE_FORWORD_POW);
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
void CTrampoline::Draw(void)
{
	CHappenig::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CTrampoline *CTrampoline::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	CTrampoline *trampo_line = nullptr;
	if (trampo_line == nullptr)
	{
		trampo_line = new CTrampoline;
		if (trampo_line != nullptr)
		{
			trampo_line->m_pos = pos;
			trampo_line->m_rot = rot;
			trampo_line->Init();
		}
	}
	return trampo_line;
}