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
#define FAN_JUMP_POW		(30.0f)		// �W�����v��
#define FAN_FORWORD_POW		(10.0f)		// �i��

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CFan::CFan(CObject::PRIORITY Priority) : CHappenig(Priority)
{

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
				CPlayer *player = static_cast<CPlayer*>(object[count_object]);

				player->SetJump(FAN_JUMP_POW);
				player->SetMoveForward(FAN_FORWORD_POW);
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