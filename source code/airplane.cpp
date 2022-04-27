//================================================
//��s�@�̏���
//Author:KatoMizuki
//================================================
#include "airplane.h"
#include "model_single.h"

//================================================
//�}�N����`
//================================================

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
	CHappenig::Init();

	//���f���̐���
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_AIRPLANE, NULL, true));

	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::SPARKLE);

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
				if (GetModel()->GetParent() == nullptr)
				{
					//���f���̌^�ɃL���X�g
					CModel *pModel = (CModel*)object[count_object];
					//�e�q�֌W������
					GetModel()->SetParent(pModel);
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
