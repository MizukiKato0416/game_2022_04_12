//================================================
//��s�@�̏���
//Author:KatoMizuki
//================================================
#include "airplane.h"
#include "model_single.h"
#include "model.h"
#include "player.h"
#include "smoke.h"
#include "play_data.h"
#include "manager.h"
#include "trophy.h"
#include "sound.h"
#include "history_letter.h"

//================================================
//�}�N����`
//================================================
#define AIRPLANE_MOVE_COUNT				(240)								//�O�ɐi�ގ���
#define AIRPLANE_MOVE_FORWARD			(30.0f)								//�O�ɐi�ޗ�
#define AIRPLANE_PLAYER_MOVE_FORWARD	(20.0f)								//�v���C���[�̑O�ɐi�ޗ�
#define AIRPLANE_PLAYER_JUMP			(20.0f)								//�W�����v��
#define AIRPLANE_MOVE					(10.0f)								//��s�@�����ł����Ƃ��̈ړ���
#define AIRPLANE_UNINIT_POS				(1000.0f)							//��s�@�������ʒu
#define AIRPLANE_SMOKE_ROT_RAND			(float (rand() % 629 + -314) / 100)	//��]����ۂ̕��������߂邽�߂̃����_���l
#define AIRPLANE_SMOKE_POS_X_RAND		(-5.0f)								//��s�@�_�̈ʒuX
#define AIRPLANE_SMOKE_POS_Y_RAND		(float (rand() % 20 + -10))			//��s�@�_�̈ʒuY�̃����_���l
#define AIRPLANE_SMOKE_SIZE				(D3DXVECTOR3 (20.0f, 20.0f, 0.0f))	//��s�@�_�̃T�C�Y
#define AIRPLANE_SMOKE_MOVE_1			(0.2f)								//��s�@�_�̈ړ�����ۂ̊���
#define AIRPLANE_SMOKE_MOVE_2			(0.8f)								//��s�@�_�̈ړ�����ۂ̊���
#define AIRPLANE_SMOKE_ADD_ROTATE		(0.2f)								//��s�@�_�̉�]���Z�l
#define AIRPLANE_SMOKE_ADD_SIZE			(D3DXVECTOR3 (0.4f, 0.4f, 0.0f))	//��s�@�_�̃T�C�Y���Z�l
#define AIRPLANE_SMOKE_SUBTRACT_ALPHA	(0.0055f)							//��s�@�_�̃��l���Z�l

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CAirplane::CAirplane(CObject::PRIORITY Priority) :CHappenig(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bHitPlayer = false;
	m_nMoveCounter = 0;
	m_pSmoke.clear();
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CAirplane::~CAirplane()
{

}

//================================================
//����������
//================================================
HRESULT CAirplane::Init()
{
	//�ϐ�������
	m_bHitPlayer = false;
	m_nMoveCounter = 0;
	m_pSmoke.clear();

	//���f���̐���
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_AIRPLANE, NULL, true));

	CHappenig::Init();

	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::AIR_PLANE);

	//�ʒu��ݒ�
	SetPos(m_pos);

	return S_OK;
}

//================================================
//�I������
//================================================
void CAirplane::Uninit(void)
{
	CHappenig::Uninit();
}

//================================================
//�X�V����
//================================================
void CAirplane::Update(void)
{
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();
	CHappenig::Update();

	if (m_bHitPlayer == false)
	{
		//�v���C���[�Ɠ���������
		if (HitPlayer() == true)
		{
			//SE��ݒ�
			sound->ControllVoice(CSound::SOUND_LABEL::AIRPLANE_SE, 1.4f);
			sound->Play(CSound::SOUND_LABEL::AIRPLANE_SE);

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
					if (GetModel()->GetModel()->GetParent() == nullptr)
					{
						//�g���t�B�[�̃t���O��Ԃ��擾
						vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
						//�g���t�B�[���擾�������Ƃ��Ȃ�������
						if (flag[(int)CTrophy::TROPHY::AIRPLANE] == false)
						{
							//�擾������
							flag[(int)CTrophy::TROPHY::AIRPLANE] = true;
							//�t���O�𗧂Ă�
							CManager::GetInstance()->GetPlayData()->SetFlag(flag);
							CHistory::Create(CTrophy::TROPHY::AIRPLANE);
						}

						//�v���C���[�̌^�ɃL���X�g
						CPlayer *pPlayer = static_cast<CPlayer*>(object[count_object]);

						//���f���̉�]��0�ɂ���
						GetModel()->GetModel()->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

						//�e�q�֌W������
						GetModel()->GetModel()->SetObjParent(true);
						GetModel()->GetModel()->SetMtxParent(pPlayer->GetMtx());

						//�������Ă���t���O�𗧂Ă�
						m_bHitPlayer = true;
						//�������Ă����Ԃɂ���
						CHappenig::SetHit(true);
						//���f���̈ʒu���擾
						D3DXVECTOR3 modelPos = GetModel()->GetPos();
						//�v���C���[�̈ʒu���擾
						D3DXVECTOR3 playerPos = pPlayer->GetPos();
						//�v���C���[�̌������擾
						D3DXVECTOR3 playerRot = pPlayer->GetRot();

						//�v���C���[�̍��������f���̍����ɂ���
						playerPos.y = modelPos.y;
						//�ʒu��ݒ�
						pPlayer->SetPos(playerPos);

						//��]���Ă�����
						if (playerRot.x != 0.0f)
						{
							//0�ɂ���
							playerRot.x = 0.0f;
							//������ݒ�
							pPlayer->SetRot(playerRot);
						}

						//�O�ɐi�ޗ͂�ݒ�
						pPlayer->SetMoveForward(AIRPLANE_MOVE_FORWARD);
					}
				}
			}
		}
	}
	else
	{
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
				//�v���C���[�̌^�ɃL���X�g
				CPlayer *pPlayer = static_cast<CPlayer*>(object[count_object]);

				//�J�E���^�[�����Z
				m_nMoveCounter++;

				//�O�ɐi�ޗ͂�ݒ�
				pPlayer->SetMoveForward(AIRPLANE_MOVE_FORWARD);

				//���f���̈ʒu���擾
				D3DXVECTOR3 modelPos = GetModel()->GetPos();

				//��s�@�_���o��
				for (int nCnt = 0; nCnt < AIRPLANE_SMOKE_NUM; nCnt++)
				{
					m_pSmoke.push_back(CSmoke::Create(D3DXVECTOR3(modelPos.x + AIRPLANE_SMOKE_POS_X_RAND, modelPos.y + AIRPLANE_SMOKE_POS_Y_RAND, modelPos.z),
						                              AIRPLANE_SMOKE_SIZE, D3DXVECTOR3(0.0f, 0.0f, AIRPLANE_SMOKE_ROT_RAND),
						                              D3DXVECTOR3(-pPlayer->GetMoveForward() * AIRPLANE_SMOKE_MOVE_1, 0.0f, 0.0f),
						                              D3DXVECTOR3(0.0f, 0.0f, AIRPLANE_SMOKE_ADD_ROTATE),
						                              AIRPLANE_SMOKE_ADD_SIZE, AIRPLANE_SMOKE_SUBTRACT_ALPHA));
					
				}

				int nSize = m_pSmoke.size();
				for (int nCntSmoke = 0; nCntSmoke < nSize; nCntSmoke++)
				{
					//�j������t���O�������Ă�����
					if (m_pSmoke[nCntSmoke]->GetDeath() == true)
					{
						//�z�������
						m_pSmoke.erase(m_pSmoke.begin() + nCntSmoke);
						nCntSmoke--;
						nSize--;
					}
					else
					{//�j������t���O�������Ă��Ȃ�������
						//��s�@�_�̈ړ��ʂ�ݒ�
						m_pSmoke[nCntSmoke]->SetMove(D3DXVECTOR3(-pPlayer->GetMoveForward() * AIRPLANE_SMOKE_MOVE_1, 0.0f, 0.0f));
					}
				}

				//����̒l���傫���Ȃ�����
				if (m_nMoveCounter > AIRPLANE_MOVE_COUNT)
				{
					for (int nCntSmoke = 0; nCntSmoke < nSize; nCntSmoke++)
					{
						//��s�@�_�̈ړ��ʂ�ݒ�
						m_pSmoke[nCntSmoke]->SetMove(D3DXVECTOR3(-pPlayer->GetMoveForward() * AIRPLANE_SMOKE_MOVE_2, 0.0f, 0.0f));
					}


					//�e�q�֌W�����Ă���Ȃ�
					if (GetModel()->GetModel()->GetObjParent() == true)
					{
						//�e�q�֌W�𗣂�
						GetModel()->GetModel()->SetObjParent(false);

						//�������Ă��Ȃ���Ԃɂ���
						CHappenig::SetHit(false);

						//�W�����v�͂�ݒ�
						pPlayer->SetJump(AIRPLANE_PLAYER_JUMP);

						//���f���̉�]�����ɖ߂�
						GetModel()->GetModel()->SetRot(D3DXVECTOR3(0.0f, AIRPLANE_INIT_ROT_Y, 0.0f));

						//�O���G�t�F�N�g������
						pPlayer->SetSparkle(true);

						//�O�ɐi�ޗ͂�ݒ�
						pPlayer->SetMoveForward(AIRPLANE_PLAYER_MOVE_FORWARD);
					}
					
					//����̒l���O�ɐi�܂���
					modelPos.x += AIRPLANE_MOVE;
					modelPos.y += 3.0f;

					//����̒l���傫���Ȃ�����
					if (modelPos.x > AIRPLANE_UNINIT_POS)
					{
						//����
						Uninit();
						return;
					}
					else
					{
						//���f���̈ʒu��ݒ�
						GetModel()->SetPos(modelPos);
					}
				}
				else
				{
					//�v���C���[�̈ʒu���擾
					D3DXVECTOR3 playerPos = pPlayer->GetPos();
					//�v���C���[�̌������擾
					D3DXVECTOR3 playerRot = pPlayer->GetRot();
					//�v���C���[�̈ړ��ʂ��擾
					D3DXVECTOR3 playerMove = pPlayer->GetMove();

					//�v���C���[�̍��������f���̍����ɂ���
					playerPos.y = modelPos.y;
					//�ʒu��ݒ�
					pPlayer->SetPos(playerPos);

					//��]���Ă�����
					if (playerRot.x != 0.0f)
					{
						//0�ɂ���
						playerRot.x = 0.0f;
						//������ݒ�
						pPlayer->SetRot(playerRot);
					}

					//�d�͂�0�ɂ���
					playerMove.y = 0.0f;
					//�ړ��ʂ�ݒ�
					pPlayer->SetMove(playerMove);

					//�O���G�t�F�N�g���o�Ă���Ȃ�
					if (pPlayer->GetSparkle() == true)
					{
						//�O���G�t�F�N�g������
						pPlayer->SetSparkle(false);
					}
					
				}
			}
		}
	}
}

//================================================
//�`�揈��
//================================================
void CAirplane::Draw(void)
{
	CHappenig::Draw();
}

//================================================
//��������
//================================================
CAirplane* CAirplane::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	//�C���X�^���X�̐���
	CAirplane *pAirplane = nullptr;
	if (pAirplane == nullptr)
	{
		pAirplane = new CAirplane();
		if (pAirplane != nullptr)
		{
			pAirplane->m_pos = pos;
			pAirplane->m_rot = rot;
			pAirplane->Init();
		}
	}
	return pAirplane;
}
