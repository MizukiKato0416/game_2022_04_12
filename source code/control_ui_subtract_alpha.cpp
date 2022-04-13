//=============================================================================
// �q�b�g�G�t�F�N�g�̓����̏���
// Author : ��������
//=============================================================================
#include "control_ui_subtract_alpha.h"
#include "ui.h"

//================================================
//�}�N����`
//================================================	

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlUiSubtractAlpha::CControlUiSubtractAlpha()
{
	m_fSubtractAlpha = 0.0f;
	m_nDelay = 0;
	m_nDelayCounter = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlUiSubtractAlpha::~CControlUiSubtractAlpha()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CControlUiSubtractAlpha::Init(const CObject *pObject)
{
	m_nDelayCounter = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlUiSubtractAlpha::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CControlUiSubtractAlpha::Update(const CObject *pObject)
{
	//�J�E���^�[�����Z
	m_nDelayCounter++;

	//����̒l�ȏ�ɂȂ�����
	if (m_nDelayCounter >= m_nDelay)
	{
		//�I�u�W�F�N�g�̃|�C���^���G�t�F�N�g�̃|�C���^�ɃL���X�g
		CUi *pUi = NULL;
		pUi = (CUi*)pObject;

		//�J���[�̎擾
		D3DXCOLOR col = pUi->GetCol();
		//��������
		col.a -= m_fSubtractAlpha;
		//�����Ȃ��Ȃ�����
		if (col.a <= 0.0f)
		{
			//����
			pUi->Uninit();
			return;
		}
		pUi->SetCol(col);
	}
}

//=============================================================================
// ��������
//=============================================================================
CControlUiSubtractAlpha *CControlUiSubtractAlpha::Create(const CObject *pObject, const float &fSubtractAlpha, const int &nDelay)
{
	//�C���X�^���X�̐���
	CControlUiSubtractAlpha *pControlUiSubtractAlpha = NULL;
	if (pControlUiSubtractAlpha == NULL)
	{
		pControlUiSubtractAlpha = new CControlUiSubtractAlpha;
		if (pControlUiSubtractAlpha != NULL)
		{
			pControlUiSubtractAlpha->m_fSubtractAlpha = fSubtractAlpha;
			pControlUiSubtractAlpha->m_nDelay = nDelay;
			pControlUiSubtractAlpha->Init(pObject);
		}
	}
	return pControlUiSubtractAlpha;
}