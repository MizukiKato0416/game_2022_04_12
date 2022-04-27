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
#define REDBULL_JUMP_POW		(12.5f)		// �W�����v��
#define REDBULL_FORWORD_POW		(15.0f)		// �i��

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CRedbull::CRedbull(CObject::PRIORITY Priority) : CHappenig(Priority)
{

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

				player->SetJump(REDBULL_JUMP_POW);
				player->SetMoveForward(REDBULL_FORWORD_POW);
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