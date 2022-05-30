//================================================
//�L���L���G�t�F�N�g�̏���
//Author:KatoMizuki
//================================================
#include "sparkle.h"
#include "effect3D.h"
#include "manager.h"
#include "texture.h"
#include "game01.h"
#include "player.h"

//================================================
//�}�N����`
//================================================
#define SPARKLE_POS_X_RAND			(float (rand() % 60 + -30))		//�G�t�F�N�g���o���ʒuX�̃����_���l
#define SPARKLE_POS_Y_RAND			(float (rand() % 10))			//�G�t�F�N�g���o���ʒuY�̃����_���l
#define SPARKLE_SIZE_SUBTRACTION	(0.6f)							//�T�C�Y���Z��

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
		m_pEffect3D[nCnt]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("effect_sparkle.png"));
		//���Z���������Z�������������_���őI��
		m_pEffect3D[nCnt]->SetAlphaBlendSubtraction((bool)(rand() % 2));
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

			//�I�u�W�F�N�g��������|�C���^
			vector<CObject*> object;

			//�擪�̃|�C���^����
			object = CObject::GetObject(static_cast<int>(CObject::PRIORITY::PLAYER));
			int object_size = object.size();

			for (int count_object = 0; count_object < object_size; count_object++)
			{
				if (object[count_object]->GetObjType() == CObject::OBJTYPE::PLAYER)
				{
					//�v���C���[�̌^�ɃL���X�g
					CPlayer *pPlayer = (CPlayer*)object[count_object];

					//�v���C���[���O�ɐi�ޗ͂��擾
					m_move.x = -pPlayer->GetMoveForward();
				}
			}

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
					m_pEffect3D.erase(m_pEffect3D.begin() + nCnt);
				}
			}
			else
			{
				//�ʒu�ƃT�C�Y��ݒ�
				m_pEffect3D[nCnt]->SetPos(pos, size);
			}
		}
	}

	//�T�C�Y��0�ɂȂ�����
	if ((int)m_pEffect3D.size() == 0)
	{
		//����
		Uninit();
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
CSparkle* CSparkle::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &move, const int &nNumEffect)
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
