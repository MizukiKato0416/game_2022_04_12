//=============================================================================
//
// ������ [thorn.cpp]
// Author : ��������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "thorn.h"
#include "player.h"
#include "model_single.h"
#include "play_data.h"
#include "manager.h"
#include "trophy.h"
#include "sound.h"
#include "model.h"
#include "history_letter.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define THORN_JUMP_POW				(10.0f)		// �W�����v��
#define THORN_FORWORD_POW			(20.0f)		// �i��
#define THORN_PLAYER_ROTATION_X		(-0.1f)		// �v���C���[�̉�]
#define THORN_SLOW_PLAYER_MOVE_Y	(0.2f)		// �X���[���̈ړ���Y
#define THORN_SLOW_FORWORD_POW		(0.3f)		// �X���[���̐i��
#define THORN_SLOW_COUNT			(5)			// �X���[�ɂ��鎞��

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CThorn::CThorn(CObject::PRIORITY Priority) : CHappenig(Priority)
{
	m_bHitPlayer = false;
	m_nCntSlow = 0;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CThorn::~CThorn()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CThorn::Init(void)
{
	//���f���̐���
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_THORN, NULL, true));
	CHappenig::Init();
	CObject::SetObjType(CObject::OBJTYPE::THORN);

	//���f���̏㒸�_�̈ʒu���擾
	D3DXVECTOR3 vtxPos[8];
	for (int nCntVtx = 0; nCntVtx < 8; nCntVtx++)
	{
		vtxPos[nCntVtx] = GetModel()->GetModel()->GetVtxPos(nCntVtx);
	}

	//���f���̃T�C�Y������̒l������������
	vtxPos[0].y -= HAPPENING_ADD_SIZE_Y;
	vtxPos[1].y -= HAPPENING_ADD_SIZE_Y;
	vtxPos[4].y -= HAPPENING_ADD_SIZE_Y;
	vtxPos[5].y -= HAPPENING_ADD_SIZE_Y;

	vtxPos[0].x += HAPPENING_ADD_SIZE_X;
	vtxPos[2].x += HAPPENING_ADD_SIZE_X;
	vtxPos[4].x += HAPPENING_ADD_SIZE_X;
	vtxPos[6].x += HAPPENING_ADD_SIZE_X;

	vtxPos[1].x -= HAPPENING_ADD_SIZE_X;
	vtxPos[3].x -= HAPPENING_ADD_SIZE_X;
	vtxPos[5].x -= HAPPENING_ADD_SIZE_X;
	vtxPos[7].x -= HAPPENING_ADD_SIZE_X;

	//�T�C�Y��ݒ�
	for (int nCntVtx = 0; nCntVtx < 8; nCntVtx++)
	{
		GetModel()->GetModel()->SetVtxPos(nCntVtx, vtxPos[nCntVtx]);
	}


	//�ϐ�������
	m_bHitPlayer = false;
	m_nCntSlow = 0;

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CThorn::Uninit(void)
{
	CHappenig::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CThorn::Update(void)
{
	//�T�E���h�擾
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();

	CHappenig::Update();

	//�v���C���[�ɓ���������
	if (CHappenig::HitPlayer() == true)
	{
		//SE�ݒ�
		sound->ControllVoice(CSound::SOUND_LABEL::THORN_SE, 1.8f);
		sound->Play(CSound::SOUND_LABEL::THORN_SE);

		//�v���C���[�ɓ������Ă��Ȃ���ԂȂ�
		if (m_bHitPlayer == false)
		{
			//�g���t�B�[�̃t���O��Ԃ��擾
			vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
			//�g���t�B�[���擾�������Ƃ��Ȃ�������
			if (flag[(int)CTrophy::TROPHY::THORN] == false)
			{
				//�擾������
				flag[(int)CTrophy::TROPHY::THORN] = true;

				CManager::GetInstance()->GetPlayData()->SetFlag(flag);
				CHistory::Create(CTrophy::TROPHY::THORN);
			}

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

				if (m_nCntSlow < THORN_SLOW_COUNT)
				{
					//�ړ��ʐݒ�
					player->SetMove(D3DXVECTOR3(0.0f, THORN_SLOW_PLAYER_MOVE_Y, 0.0f));
					//�O�ɐi�ޗ͐ݒ�
					player->SetMoveForward(THORN_SLOW_FORWORD_POW);
				}
				else if (m_nCntSlow == THORN_SLOW_COUNT)
				{
					//�������Ă��Ȃ���Ԃɂ���
					CHappenig::SetHit(false);
					//�W�����v�ʐݒ�
					player->SetJump(THORN_JUMP_POW);
					//�O�ɐi�ޗ͂�ݒ�
					player->SetMoveForward(THORN_FORWORD_POW);
					//�o�E���h����u�Ԃ̈ړ��ʂ�ݒ�
					player->SetBoundMove(player->GetJump());
				}
			}
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void CThorn::Draw(void)
{
	CHappenig::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CThorn *CThorn::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	CThorn *trampo_line = nullptr;
	if (trampo_line == nullptr)
	{
		trampo_line = new CThorn;
		if (trampo_line != nullptr)
		{
			trampo_line->m_pos = pos;
			trampo_line->m_rot = rot;
			trampo_line->Init();
		}
	}
	return trampo_line;
}