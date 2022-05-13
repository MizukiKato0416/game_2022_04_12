//================================================
//UI����
//Authore:��������
//================================================
#include "Object2D.h"
#include "manager.h"
#include "ui.h"
#include "texture.h"
#include "control.h"
#include "control_ui_subtract_alpha.h"

//================================================
//�}�N����`
//================================================
#define UI_PRESS_START_SUBTRACT_ALPHA	(0.015f)		//PRESS START UI�̃��l���Z�l
#define UI_PRESS_START_DELAY			(10)			//PRESS START UI�̕\������

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CUi::CUi(CObject::PRIORITY Priority) :CObject2D(Priority)
{
	m_pControl = nullptr;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CUi::~CUi()
{

}

//================================================
//����������
//================================================
HRESULT CUi::Init(void)
{
	CObject2D::Init();

	//�ʒu�ƃT�C�Y��ݒ�
	SetPos(m_pos, m_size);

	SetObjType(CObject::OBJTYPE::UI);

	return S_OK;
}

//================================================
//�I������
//================================================
void CUi::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================
//�X�V����
//================================================
void CUi::Update(void)
{
	if (m_pControl != nullptr)
	{
		//�eUI�̍X�V�������Ăяo��
		m_pControl->Update(this);
	}
}

//================================================
//�`�揈��
//================================================
void CUi::Draw(void)
{
	CObject2D::Draw();
}

//================================================
//��������
//================================================
CUi* CUi::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const int &nPriolity, const TYPE &type)
{
	//�C���X�^���X�̐���
	CUi *pUi = nullptr;
	if (pUi == nullptr)
	{
		pUi = new CUi(static_cast<CObject::PRIORITY>(nPriolity));
		if (pUi != nullptr)
		{
			pUi->m_type = type;
			pUi->m_pos = pos;
			pUi->m_size = size;
			pUi->Init();
			// �w�肵��UI�̎�ނŃe�N�X�`����ς���
			switch (type)
			{
			case TYPE::PRESS_START:
				pUi->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("press_start.png");
				pUi->m_pControl = CControlUiSubtractAlpha::Create(pUi, UI_PRESS_START_SUBTRACT_ALPHA, UI_PRESS_START_DELAY);
			default:
				break;
			}
			pUi->BindTexture(pUi->m_pTexture);
		}
	}
	return pUi;
}
