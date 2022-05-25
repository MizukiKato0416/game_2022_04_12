//================================================
//���̃Z���t�ɍs��UI����
//Authore:��������
//================================================
#include "Object2D.h"
#include "next_dialog_ui.h"

//================================================
//�}�N����`
//================================================
#define NEXT_DIALOG_UI_ADD_ROTATE		(0.05f)		//��]�𑝂₷�l
#define NEXT_DIALOG_UI_SUBTRACTALPHA	(0.012f)	//��������l
#define NEXT_DIALOG_UI_COUNTER			(25)		//������悤�ɂ���܂ł̎���

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CNextDialogUI::CNextDialogUI(CObject::PRIORITY Priority) :CObject2D(Priority)
{
	m_fRotation = 0.0f;
	m_nCounter = 0;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CNextDialogUI::~CNextDialogUI()
{

}

//================================================
//����������
//================================================
HRESULT CNextDialogUI::Init(void)
{
	//�ϐ�������
	m_fRotation = 0.0f;
	m_nCounter = 0;

	CObject2D::Init();

	SetObjType(CObject::OBJTYPE::UI);

	return S_OK;
}

//================================================
//�I������
//================================================
void CNextDialogUI::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================
//�X�V����
//================================================
void CNextDialogUI::Update(void)
{
	//�F�擾
	D3DXCOLOR col = GetCol();
	//��������
	col.a -= NEXT_DIALOG_UI_SUBTRACTALPHA;
	//�����Ȃ��Ȃ�����
	if (col.a <= 0.0f)
	{
		//0�ɂ���
		col.a = 0.0f;

		//�J�E���^�[�𑝂₷
		m_nCounter++;

		if (m_nCounter > NEXT_DIALOG_UI_COUNTER)
		{
			//0�ɂ���
			m_nCounter = 0;

			//������悤�ɂ���
			col.a = 1.0f;
			//�F�ݒ�
			SetCol(col);
		}
	}
	else
	{
		//�F�ݒ�
		SetCol(col);
	}

	//��]�l�𑝂₷
	m_fRotation -= NEXT_DIALOG_UI_ADD_ROTATE;
	if (m_fRotation < -D3DX_PI * 2.0f)
	{
		m_fRotation += D3DX_PI * 2.0f;
	}

	//�ݒ�
	SetPos(GetPos(), GetSize(), m_fRotation);
}

//================================================
//�`�揈��
//================================================
void CNextDialogUI::Draw(void)
{
	CObject2D::Draw();
}

//================================================
//��������
//================================================
CNextDialogUI* CNextDialogUI::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	//�C���X�^���X�̐���
	CNextDialogUI *pNextDialogUI = nullptr;
	if (pNextDialogUI == nullptr)
	{
		pNextDialogUI = new CNextDialogUI();
		if (pNextDialogUI != nullptr)
		{
			pNextDialogUI->Init();
			//�ʒu�ƃT�C�Y��ݒ�
			pNextDialogUI->SetPos(pos, size);
		}
	}
	return pNextDialogUI;
}
