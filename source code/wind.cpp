//================================================
//���G�t�F�N�g�̏���
//Author:KatoMizuki
//================================================
#include "wind.h"
#include "effect3D.h"
#include "manager.h"
#include "texture.h"

//================================================
//�}�N����`
//================================================
#define WIND_MAX_COUNTER	(3)									//�A�j���[�V�������؂�ւ��܂ł̃J�E���^�[
#define WIND_COLOR			(D3DXCOLOR(0.2f, 1.0f, 0.4f, 1.0f))	//�F

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CWind::CWind(CObject::PRIORITY Priority) :CEffect3D(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nInitTexAnimNum = 0;
	m_nTexAnimCounter = 0;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CWind::~CWind()
{

}

//================================================
//����������
//================================================
HRESULT CWind::Init()
{
	CEffect3D::Init();

	//�ϐ�������
	m_nTexAnimCounter = 0;

	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::WIND);


	//�A�j���[�V�������Ō�܂ōs������
	if (m_nInitTexAnimNum >= WIND_MAX_PATTERN)
	{
		//�ŏ��ɖ߂�
		m_nInitTexAnimNum = 0;
	}

	//�A�j���[�V������ݒ�
	SetTex(m_nInitTexAnimNum, WIND_MAX_PATTERN);

	//�F��ݒ�
	SetCol(WIND_COLOR);

	return S_OK;
}

//================================================
//�I������
//================================================
void CWind::Uninit(void)
{
	CEffect3D::Uninit();
}

//================================================
//�X�V����
//================================================
void CWind::Update(void)
{
	//�e�N�X�`���A�j���[�V�����̏���

	//�J�E���^�[�𑝂₷
	m_nTexAnimCounter++;

	//����̒l���傫���Ȃ�����
	if (m_nTexAnimCounter > WIND_MAX_COUNTER)
	{
		//0�ɂ���
		m_nTexAnimCounter = 0;
		
		//�A�j���[�V���������ɂ���
		m_nInitTexAnimNum++;

		//�A�j���[�V�������Ō�܂ōs������
		if (m_nInitTexAnimNum >= WIND_MAX_PATTERN)
		{
			//�ŏ��ɖ߂�
			m_nInitTexAnimNum = 0;
		}

		//�A�j���[�V������ݒ�
		SetTex(m_nInitTexAnimNum, WIND_MAX_PATTERN);
	}
}

//================================================
//�`�揈��
//================================================
void CWind::Draw(void)
{
	CEffect3D::Draw();
}

//================================================
//��������
//================================================
CWind* CWind::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const int &nInitTexAnimNum)
{
	//�C���X�^���X�̐���
	CWind *pWind = nullptr;
	if (pWind == nullptr)
	{
		pWind = new CWind();
		if (pWind != nullptr)
		{
			pWind->m_pos = pos;
			pWind->m_size = size;
			pWind->m_nInitTexAnimNum = nInitTexAnimNum;
			pWind->Init();
			pWind->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("effect_wind.png"));
		}
	}
	return pWind;
}
