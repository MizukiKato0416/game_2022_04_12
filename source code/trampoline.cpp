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

//=============================================================================
// �}�N����`
//=============================================================================
#define TRAMPOLINE_JUMP_POW		(20.0f)		// �W�����v��
#define TRAMPOLINE_FORWORD_POW	(17.5f)		// �i��

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTrampoline::CTrampoline(CObject::PRIORITY Priority) : CHappenig(Priority)
{

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

				player->SetJump(TRAMPOLINE_JUMP_POW);
				player->SetMoveForward(TRAMPOLINE_FORWORD_POW);
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