//================================================
//���̒e�̏���
//Author:KatoMizuki
//================================================
#include "sparkle.h"
#include "effect3D.h"
#include "manager.h"
#include "texture.h"

//================================================
//�}�N����`
//================================================
#define SPARKLE_POS_X_RAND			(float (rand() % 100))			//�G�t�F�N�g���o���ʒuX�̃����_���l
#define SPARKLE_POS_Y_RAND			(float (rand() % 40))			//�G�t�F�N�g���o���ʒuY�̃����_���l
#define SPARKLE_SIZE_SUBTRACTION	(2.0f)							//�T�C�Y���Z��

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CSparkle::CSparkle(CObject::PRIORITY Priority) :CObject(Priority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pEffect3D.clear();
	m_nNumEffect = 0;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CSparkle::~CSparkle()
{

}

//================================================
//����������
//================================================
HRESULT CSparkle::Init()
{
	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::SPARKLE);
	
	//�G�t�F�N�g�̐���
	for (int nCnt = 0; nCnt < m_nNumEffect; nCnt++)
	{
		m_pEffect3D.push_back(CEffect3D::Create(D3DXVECTOR3(m_pos.x - SPARKLE_POS_X_RAND, m_pos.y + SPARKLE_POS_Y_RAND, m_pos.z),
			                                    m_size, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), CEffect3D::EFFECT3D_TYPE::TRAJECTORY_PLAYER));
		//�e�N�X�`���ݒ�
		m_pEffect3D[nCnt]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_SPARKLE"));
	}

	//�ʒu�ƃT�C�Y��ݒ�
	SetPos(m_pos);
	SetSize(m_size);

	return S_OK;
}

//================================================
//�I������
//================================================
void CSparkle::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CSparkle::Update(void)
{
	for (int nCnt = 0; nCnt < (int)m_pEffect3D.size(); nCnt++)
	{
		if (m_pEffect3D[nCnt] != nullptr)
		{
			//�ʒu�ƃT�C�Y���擾
			D3DXVECTOR3 pos = m_pEffect3D[nCnt]->GetPos();
			D3DXVECTOR3 size = m_pEffect3D[nCnt]->GetSize();

			//�ړ��ʂ����Z
			pos += m_move;

			//�T�C�Y������������
			size = D3DXVECTOR3(size.x - SPARKLE_SIZE_SUBTRACTION, size.y - SPARKLE_SIZE_SUBTRACTION, size.z);

			//�T�C�Y��0�ȉ��ɂȂ�����
			if (size.x <= 0.0f || size.y <= 0.0f)
			{
				if (m_pEffect3D[nCnt] != nullptr)
				{
					//����
					m_pEffect3D[nCnt]->Uninit();
					m_pEffect3D[nCnt] = nullptr;
				}
			}
			else
			{
				//�ʒu�ƃT�C�Y��ݒ�
				m_pEffect3D[nCnt]->SetPos(pos, size);
			}
		}
	}
}

//================================================
//�`�揈��
//================================================
void CSparkle::Draw(void)
{
	
}

//================================================
//��������
//================================================
CSparkle* CSparkle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, int nNumEffect)
{
	//�C���X�^���X�̐���
	CSparkle *pSparkle = nullptr;
	if (pSparkle == nullptr)
	{
		pSparkle = new CSparkle();
		if (pSparkle != nullptr)
		{
			pSparkle->m_pos = pos;
			pSparkle->m_size = size;
			pSparkle->m_move = move;
			pSparkle->m_nNumEffect = nNumEffect;
			pSparkle->Init();
		}
	}
	return pSparkle;
}
