//================================================
//�Q�[�W����
//Author:KatoMizuki
//================================================
#include "gauge.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CGauge::CGauge(CObject::PRIORITY Priority) :CObject2D(Priority)
{
	m_nMaxNum = 0;
	m_nNum = 0;
	m_sizeMax = { 0.0f, 0.0f, 0.0f };
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CGauge::~CGauge()
{

}

//================================================
//����������
//================================================
HRESULT CGauge::Init(void)
{
	//�ϐ�������
	

	//���_�̎�ނ����ɐݒ�
	SetOriginType(CObject2D::ORIGIN_TYPE::LEFT);

	CObject2D::Init();

	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::GAUGE);

	//�Q�[�W�ݒ菈��
	SetGauge(m_nNum);

	return S_OK;
}

//================================================
//�I������
//================================================
void CGauge::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================
//�X�V����
//================================================
void CGauge::Update(void)
{
	
}

//================================================
//�`�揈��
//================================================
void CGauge::Draw(void)
{
	CObject2D::Draw();
}

//================================================
//��������
//================================================
CGauge* CGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nMaxNum, int nNum)
{
	//�C���X�^���X�̐���
	CGauge *pGauge = nullptr;
	if (pGauge == nullptr)
	{
		pGauge = new CGauge();
		if (pGauge != nullptr)
		{
			pGauge->m_nMaxNum = nMaxNum;
			pGauge->m_nNum = nNum;
			pGauge->m_sizeMax = size;
			pGauge->Init();
			pGauge->SetPos(pos, size);
		}
	}
	return pGauge;
}

//================================================
//�Q�[�W��������
//================================================
void CGauge::AddGauge(int nNum)
{
	//�l�����Z
	m_nNum += nNum;

	//���Z�����l���ő�l�����傫��������
	if (m_nNum > m_nMaxNum)
	{
		//�ő�l��ݒ�
		m_nNum = m_nMaxNum;
	}
	else if (m_nNum < 0)
	{//���Z�����l��0����������������
		//0�ɂ���
		m_nNum = 0;
	}

	//�ʒu���擾
	D3DXVECTOR3 pos = GetPos();
	//�T�C�Y���擾
	D3DXVECTOR3 size = GetSize();
	//�T�C�Y���Z�o
	size.x = m_sizeMax.x * (float)(m_nNum) / (float)m_nMaxNum;
	//�ʒu�ƃT�C�Y��ݒ�
	SetPos(pos, size);
}

//================================================
//�Q�[�W�ݒ菈��
//================================================
void CGauge::SetGauge(int nNum)
{
	//�ݒ肵���l���ő�l�����傫��������
	if (nNum > m_nMaxNum)
	{
		//�l��ݒ�
		m_nNum = m_nMaxNum;
	}
	else if (nNum < 0)
	{//�ݒ肵���l��0����������������
		//0�ɂ���
		m_nNum = 0;
	}
	else
	{
		//�l��ݒ�
		m_nNum = nNum;
	}
	
	//�ʒu���擾
	D3DXVECTOR3 pos = GetPos();
	//�T�C�Y���擾
	D3DXVECTOR3 size = GetSize();
	//�T�C�Y���Z�o
	size.x = m_sizeMax.x * (float)m_nNum / (float)m_nMaxNum;
	//�ʒu�ƃT�C�Y��ݒ�
	SetPos(pos, size);
}

//================================================
//�Q�[�W�ő吔�l�ݒ菈��
//================================================
void CGauge::SetMaxNum(int nMaxNum)
{
	m_nMaxNum = nMaxNum;
}

