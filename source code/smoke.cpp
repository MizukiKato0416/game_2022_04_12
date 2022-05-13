//================================================
//���G�t�F�N�g�̏���
//Author:KatoMizuki
//================================================
#include "smoke.h"
#include "effect3D.h"
#include "manager.h"
#include "texture.h"

//================================================
//�}�N����`
//================================================

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CSmoke::CSmoke(CObject::PRIORITY Priority) :CObject(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_addRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_addSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pEffect3D = nullptr;
	m_fSubtractAlpha = 0.0f;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CSmoke::~CSmoke()
{

}

//================================================
//����������
//================================================
HRESULT CSmoke::Init()
{
	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::SMOKE);
	
	//�G�t�F�N�g�̐���
	m_pEffect3D = CEffect3D::Create(m_pos, m_size, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CEffect3D::EFFECT3D_TYPE::SMOKE);
	m_pEffect3D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("effect_smoke.jpg"));
	m_pEffect3D->SetRot(m_rot);

	//�ʒu�ƃT�C�Y��ݒ�
	SetPos(m_pos);
	SetSize(m_size);

	return S_OK;
}

//================================================
//�I������
//================================================
void CSmoke::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CSmoke::Update(void)
{
	//�J���[���擾
	D3DXCOLOR col = m_pEffect3D->GetCol();
	//���l������̒l�����炷
	col.a -= m_fSubtractAlpha;
	//col = D3DXCOLOR(0.5f, 0.5f, 0.5f, col.a);
	//0�ȉ��ɂȂ�����
	if (col.a <= 0.0f)
	{
		//����
		m_pEffect3D->Uninit();
		m_pEffect3D = nullptr;
		Uninit();
		return;
	}
	else
	{
		//�F��ݒ�
		m_pEffect3D->SetCol(col);
	}

	//�T�C�Y���擾
	m_size = m_pEffect3D->GetSize();
	//����̒l�T�C�Y�𑝂₷
	m_size += m_addSize;

	//�ʒu���擾
	m_pos = m_pEffect3D->GetPos();
	//����̒l�ʒu�𑝂₷
	m_pos += m_move;
	//�ʒu�ƃT�C�Y��ݒ肷��
	m_pEffect3D->SetPos(m_pos, m_size);

	//�������擾
	m_rot = m_pEffect3D->GetRot();
	//����̒l�����𑝂₷
	m_rot += m_addRot;
	//�΂��傫���Ȃ�����-2�΂���
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{	//-�΂�菬�����Ȃ�����+2�΂���
		m_rot.y += D3DX_PI * 2.0f;
	}
	//������ݒ肷��
	m_pEffect3D->SetRot(m_rot);
}

//================================================
//�`�揈��
//================================================
void CSmoke::Draw(void)
{
	
}

//================================================
//��������
//================================================
CSmoke* CSmoke::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, const D3DXVECTOR3 &move, const D3DXVECTOR3 &addRot,
	                   const D3DXVECTOR3 &addSize, const float &fSubtractAlpha)
{
	//�C���X�^���X�̐���
	CSmoke *pSmoke = nullptr;
	if (pSmoke == nullptr)
	{
		pSmoke = new CSmoke();
		if (pSmoke != nullptr)
		{
			pSmoke->m_pos = pos;
			pSmoke->m_move = move;
			pSmoke->m_size = size;
			pSmoke->m_rot = rot;
			pSmoke->m_addRot = addRot;
			pSmoke->m_addSize = addSize;
			pSmoke->m_fSubtractAlpha = fSubtractAlpha;
			pSmoke->Init();
		}
	}
	return pSmoke;
}
