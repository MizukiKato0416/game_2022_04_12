//=============================================================================
//
// �X�^�[�����O���� [starring.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �}�N����`
//=============================================================================
#define STARRING_ROTATION_X (0.01f)	// ��]
#define STARRING_JUMP_POW (2.0f)	// �W�����v��
#define STARRING_FORWORD_POW (35.0f)	// �i��

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "starring.h"
#include "player.h"
#include "model_single.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CStarring::CStarring(CObject::PRIORITY Priority) : CHappenig(Priority)
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CStarring::~CStarring()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CStarring::Init(void)
{
	CHappenig::Init();
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_STARRING, NULL, true));
	CObject::SetObjType(CObject::OBJTYPE::STAR_RING);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CStarring::Uninit(void)
{
	CHappenig::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CStarring::Update(void)
{
	CHappenig::Update();
	if (CHappenig::HitPlayer() == true)
	{
		m_rot.x += STARRING_ROTATION_X;
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

				player->SetJump(STARRING_JUMP_POW);
				player->SetMoveForward(STARRING_FORWORD_POW);
			}
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void CStarring::Draw(void)
{
	CHappenig::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CStarring *CStarring::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	CStarring *star_ring = nullptr;
	if (star_ring == nullptr)
	{
		star_ring = new CStarring;
		if (star_ring != nullptr)
		{
			star_ring->m_pos = pos;
			star_ring->m_rot = rot;
			star_ring->Init();
		}
	}
	return star_ring;
}