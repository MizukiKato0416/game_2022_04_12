//=============================================================================
//
// �g���t�B�[���[���� [trophy.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "trophy.h"
#include "happening.h"
#include "manager.h"
#include "object2D.h"
#include "play_data.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TROPHY_ICON_SIZE (200)			// �A�C�R���T�C�Y
#define TROPHY_ICON_X_FEELING (250)		// �A�C�R���̐ݒu���o
#define TROPHY_ICON_Y_FEELING (250)		// �A�C�R���̐ݒu���o
#define SCREEN_DIVISION_COUNT (4)		// ����������{�ɂ��邩

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTrophy::CTrophy(PRIORITY priolty)
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CTrophy::~CTrophy()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTrophy::Init(void)
{
	//CObject2D::Create(D3DXVECTOR3(), D3DXVECTOR3(), static_cast<int>(CObject::PRIORITY::UI);
	//CObject2D::Create(D3DXVECTOR3(), D3DXVECTOR3(), static_cast<int>(CObject::PRIORITY::UI);
	//CObject2D::Create(D3DXVECTOR3(), D3DXVECTOR3(), static_cast<int>(CObject::PRIORITY::UI);

	for (int count_trophy_size = 0; count_trophy_size < (int)CHappenig::HAPPENING_TYPE::MAX - 1; count_trophy_size++)
	{
		vector<bool> trophy_flag = CManager::GetPlayData()->GetFlag();

		if (trophy_flag[count_trophy_size])
		{
			CObject2D *pObject2D = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / SCREEN_DIVISION_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), SCREEN_HEIGHT / SCREEN_DIVISION_COUNT, 0.0f),
				D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
			pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_TITLE"));
		}
		else
		{
			CObject2D *pObject2D = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / SCREEN_DIVISION_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), SCREEN_HEIGHT / SCREEN_DIVISION_COUNT, 0.0f),
				D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
			pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_TITLE_LOGO"));
		}
	}

	//m_buck = CObject2D::Create(D3DXVECTOR3(), D3DXVECTOR3(), static_cast<int>(CObject::PRIORITY::UI));
}

//=============================================================================
// �X�V����
//=============================================================================
void CTrophy::Uninit(void)
{
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTrophy::Update(void)
{
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTrophy::Draw(void)
{

}