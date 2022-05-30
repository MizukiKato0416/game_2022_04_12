//================================================
//���P�b�g�̏���
//Author:KatoMizuki
//================================================
#include "rocket.h"
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
#define ROCKET_SMOKE_ROT_RAND		(float (rand() % 629 + -314) / 100)	//��]����ۂ̕��������߂邽�߂̃����_���l
#define ROCKET_SMOKE_POS_X_RAND		(float (rand() % 20 + -10))			//���P�b�g�_�̈ʒuX�̃����_���l
#define ROCKET_SMOKE_POS_Y_RAND		(30.0f)								//���P�b�g�_�̈ʒuY�̃����_���l
#define ROCKET_SMOKE_SIZE			(D3DXVECTOR3 (20.0f, 20.0f, 0.0f))	//���P�b�g�_�̃T�C�Y
#define ROCKET_SMOKE_ADD_ROTATE		(0.2f)								//���P�b�g�_�̉�]���Z�l
#define ROCKET_SMOKE_ADD_SIZE		(D3DXVECTOR3 (0.7f, 0.7f, 0.0f))	//���P�b�g�_�̃T�C�Y���Z�l
#define ROCKET_SMOKE_SUBTRACT_ALPHA	(0.004f)							//���P�b�g�_�̃��l���Z�l
#define ROCKET_MOVE_Y				(6.0f)								//���P�b�g�̈ړ���

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CRocket::CRocket(CObject::PRIORITY Priority) :CHappenig(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bHitPlayer = false;
	m_pSmoke.clear();
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CRocket::~CRocket()
{

}

//================================================
//����������
//================================================
HRESULT CRocket::Init()
{
	//�ϐ�������
	m_bHitPlayer = false;
	m_pSmoke.clear();

	//���f���̐���
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_ROCKET, NULL, true));

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
void CRocket::Uninit(void)
{
	CHappenig::Uninit();
}

//================================================
//�X�V����
//================================================
void CRocket::Update(void)
{
	//�T�E���h�擾
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();

	CHappenig::Update();

	if (m_bHitPlayer == false)
	{
		//�v���C���[�Ɠ���������
		if (HitPlayer() == true)
		{
			//SE�ݒ�
			sound->ControllVoice(CSound::SOUND_LABEL::ROCKET_SE, 1.4f);
			sound->Play(CSound::SOUND_LABEL::ROCKET_SE);

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
						if (flag[(int)CTrophy::TROPHY::ROCKET] == false)
						{
							//�擾������
							flag[(int)CTrophy::TROPHY::ROCKET] = true;
							CManager::GetInstance()->GetPlayData()->SetFlag(flag);
							CHistory::Create(CTrophy::TROPHY::ROCKET);
						}
						//�g���t�B�[���擾�������Ƃ��Ȃ�������
						if (flag[(int)CTrophy::TROPHY::MEASUREMENT_IMPOSSIBLE] == false)
						{
							//�擾������
							flag[(int)CTrophy::TROPHY::MEASUREMENT_IMPOSSIBLE] = true;
							CManager::GetInstance()->GetPlayData()->SetFlag(flag);
							CHistory::Create(CTrophy::TROPHY::MEASUREMENT_IMPOSSIBLE);
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

						//���f���̈ʒu��0�ɂ���
						modelPos = { 0.0f, 0.0f, 0.0f };

						//���f���̈ʒu��ݒ�
						GetModel()->GetModel()->SetPos(modelPos);

						//�O�ɐi�ޗ͂�ݒ�
						pPlayer->SetMoveForward(0.0f);
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

				//�O�ɐi�ޗ͂�ݒ�
				pPlayer->SetMoveForward(0.0f);

				//���f���̈ʒu���擾
				D3DXMATRIX modelMtx = GetModel()->GetModel()->GetMtx();

				//�����o��
				for (int nCnt = 0; nCnt < ROCKET_SMOKE_NUM; nCnt++)
				{
					m_pSmoke.push_back(CSmoke::Create(D3DXVECTOR3(modelMtx._41 + ROCKET_SMOKE_POS_X_RAND, modelMtx._42 + ROCKET_SMOKE_POS_Y_RAND, modelMtx._43),
						                              ROCKET_SMOKE_SIZE, D3DXVECTOR3(0.0f, 0.0f, ROCKET_SMOKE_ROT_RAND),
						                              D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						                              D3DXVECTOR3(0.0f, 0.0f, ROCKET_SMOKE_ADD_ROTATE),
						                              ROCKET_SMOKE_ADD_SIZE, ROCKET_SMOKE_SUBTRACT_ALPHA));
				}

				//�v���C���[�̈ړ��ʂ�ݒ�
				pPlayer->SetMove(D3DXVECTOR3(0.0f, ROCKET_MOVE_Y, 0.0f));

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
				}
			}
		}
	}
}

//================================================
//�`�揈��
//================================================
void CRocket::Draw(void)
{
	CHappenig::Draw();
}

//================================================
//��������
//================================================
CRocket* CRocket::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	//�C���X�^���X�̐���
	CRocket *pRocket = nullptr;
	if (pRocket == nullptr)
	{
		pRocket = new CRocket();
		if (pRocket != nullptr)
		{
			pRocket->m_pos = pos;
			pRocket->m_rot = rot;
			pRocket->Init();
		}
	}
	return pRocket;
}
