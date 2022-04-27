//================================================
//��s�@�̏���
//Author:KatoMizuki
//================================================
#include "airplane.h"
#include "model_single.h"
#include "model.h"
#include "player.h"

//================================================
//�}�N����`
//================================================
#define AIRPLANE_MOVE_COUNT		(180)			//�O�ɐi�ގ���

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

	CHappenig::Init();

	//���f���̐���
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_AIRPLANE, NULL, true));

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
	CHappenig::Update();

	if (m_bHitPlayer == false)
	{
		//�v���C���[�Ɠ���������
		if (HitPlayer() == true)
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
					if (GetModel()->GetModel()->GetParent() == nullptr)
					{
						//�v���C���[�̌^�ɃL���X�g
						CPlayer *pPlayer = static_cast<CPlayer*>(object[count_object]);

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

						//�O�ɐi�ޗ͂�ݒ�
						pPlayer->SetMoveForward(40.0f);
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

				//����̒l���傫���Ȃ�����
				if (m_nMoveCounter > AIRPLANE_MOVE_COUNT)
				{
					//�W�����v�͂�ݒ�
					pPlayer->SetJump(30.0f);
					//����
					Uninit();
					return;
				}

				//���f���̈ʒu���擾
				D3DXVECTOR3 modelPos = GetModel()->GetPos();
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
