//================================================
//�N���b�N�G�t�F�N�g�̏���
//Author:KatoMizuki
//================================================
#include "effect_click.h"
#include "effect2D.h"
#include "manager.h"
#include "texture.h"
#include "object.h"

//================================================
//�}�N����`
//================================================
#define EFFECT_CLICK_SPARKLE_COL				(D3DXCOLOR(0.6f, 0.6f, 1.0f, 1.0f))								//�L���L���G�t�F�N�g�̐F
#define EFFECT_CLICK_SPARKLE_ADD_SIZE			(1.63f)															//�L���L���G�t�F�N�g�̃T�C�Y�𑝉����銄��
#define EFFECT_CLICK_SPARKLE_SUBTRACT_SIZE		(0.82f)															//�L���L���G�t�F�N�g�̃T�C�Y���������銄��
#define EFFECT_CLICK_SPARKLE_ADD_SIZE_TIME		(10)															//�L���L���G�t�F�N�g�̃T�C�Y�𑝉����鎞��
#define EFFECT_CLICK_STAR_INIT_ALPHA			(0.0f)															//�X�^�[�t�F�N�g�̏������l
#define EFFECT_CLICK_STAR_01_COL				(D3DXCOLOR(0.2f, 0.2f, 0.0f, EFFECT_CLICK_STAR_INIT_ALPHA))		//�X�^�[�t�F�N�g01�̐F
#define EFFECT_CLICK_STAR_02_COL				(D3DXCOLOR(1.0f, 0.2f, 0.2f, EFFECT_CLICK_STAR_INIT_ALPHA))		//�X�^�[�t�F�N�g02�̐F
#define EFFECT_CLICK_STAR_03_COL				(D3DXCOLOR(0.2f, 0.2f, 1.0f, EFFECT_CLICK_STAR_INIT_ALPHA))		//�X�^�[�t�F�N�g03�̐F
#define EFFECT_CLICK_STAR_INIT_DIFFER			(25.0f)															//�X�^�[�t�F�N�g�̒��S����̏�������
#define EFFECT_CLICK_STAR_ADD_DIFFER			(0.9f)															//�X�^�[�t�F�N�g�̒��S����̋������Z�l
#define EFFECT_CLICK_STAR_INIT_SIZE				(40.0f)															//�X�^�[�t�F�N�g�̃T�C�Y
#define EFFECT_CLICK_STAR_SUBTRACT_ALPHA_TIME	(10)															//�X�^�[�G�t�F�N�g�̐F�𔖂����n�߂鎞��
#define EFFECT_CLICK_STAR_ADD_ALPHA				(0.15f)															//�X�^�[�G�t�F�N�g�̃��l�𑝉����銄��
#define EFFECT_CLICK_STAR_SUBTRACT_ALPHA		(0.05f)															//�X�^�[�G�t�F�N�g�̃��l���������銄��
#define EFFECT_CLICK_STAR_ADD_ROT				(0.25f)															//�X�^�[�G�t�F�N�g�̉�]��
#define EFFECT_CLICK_RING_COL					(D3DXCOLOR(0.6f, 0.6f, 1.0f, 1.0f))								//�����O�t�F�N�g�̐F
#define EFFECT_CLICK_RING_INIT_ADD_SIZE			(D3DXVECTOR3(5.0f, 5.0f, 0.0f))									//�����O�t�F�N�g�̃T�C�Y���Z��
#define EFFECT_CLICK_RING_01_SUBTRACT_SIZE		(0.9f)															//�����O�t�F�N�g�̃T�C�Y���Z��
#define EFFECT_CLICK_RING_02_SUBTRACT_SIZE		(0.878f)														//�����O�t�F�N�g�̃T�C�Y���Z��
#define EFFECT_CLICK_RING_01_SUBTRACT_SIZE_TIME	(8)																//�����O�t�F�N�g�̃T�C�Y���Z���鎞��
#define EFFECT_CLICK_RING_02_SUBTRACT_SIZE_TIME	(16)															//�����O�t�F�N�g�̃T�C�Y���Z���鎞��
#define EFFECT_CLICK_RING_01_SUBTRACT_ALPHA		(0.06f)															//�����O�t�F�N�g�̃��l�����������
#define EFFECT_CLICK_RING_02_SUBTRACT_ALPHA		(0.056f)														//�����O�t�F�N�g�̃��l�����������
#define EFFECT_CLICK_RING_02_CREATE_TIME		(8)																//�����O�t�F�N�g2�𐶐�����^�C�~���O


//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CEffectClick::CEffectClick(CObject::PRIORITY Priority) :CObject(Priority)
{
	memset(m_pRing, NULL, sizeof(m_pRing[EFFECT_CLICK_RING_NUM]));
	memset(m_pStar, NULL, sizeof(m_pStar[EFFECT_CLICK_STAR_NUM]));
	memset(m_pStarBg, NULL, sizeof(m_pStarBg[EFFECT_CLICK_STAR_NUM]));
	m_pSparkle = nullptr;
	m_nCounter = 0;
	m_fStarDiffer = 0.0f;
	memset(m_fStarRot, NULL, sizeof(m_fStarRot[EFFECT_CLICK_STAR_NUM]));
	for (int nCntRing = 0; nCntRing < EFFECT_CLICK_RING_NUM; nCntRing++)
	{
		m_ringAddSize[nCntRing] = { 0.0f, 0.0f, 0.0f };
	}
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CEffectClick::~CEffectClick()
{

}

//================================================
//����������
//================================================
HRESULT CEffectClick::Init()
{
	//�ϐ�������
	m_nCounter = 0;
	m_fStarDiffer = EFFECT_CLICK_STAR_INIT_DIFFER;
	memset(m_fStarRot, NULL, sizeof(m_fStarRot[EFFECT_CLICK_STAR_NUM]));
	for (int nCntRing = 0; nCntRing < EFFECT_CLICK_RING_NUM; nCntRing++)
	{
		m_ringAddSize[nCntRing] = EFFECT_CLICK_RING_INIT_ADD_SIZE;
	}
	

	//�L���L���G�t�F�N�g�̐���
	m_pSparkle = CEffect2D::Create(m_pos, D3DXVECTOR3(1.0f, 1.0f, 0.0f), EFFECT_CLICK_SPARKLE_COL, CEffect2D::EFFECT2D_TYPE::NONE);
	m_pSparkle->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("effect_sparkle.png"));
	m_pSparkle->SetPriority((int)(CObject::PRIORITY::CLICK_EFFECT));

	//���G�t�F�N�g�̐���
	for (int nCntStar = 0; nCntStar < EFFECT_CLICK_STAR_NUM; nCntStar++)
	{
		m_pStarBg[nCntStar] = CEffect2D::Create(D3DXVECTOR3(m_pos.x + cosf(D3DX_PI * 2.0f / EFFECT_CLICK_STAR_NUM * nCntStar) * m_fStarDiffer,
														    m_pos.y + sinf(D3DX_PI * 2.0f / EFFECT_CLICK_STAR_NUM * nCntStar) * m_fStarDiffer, 0.0f),
														    D3DXVECTOR3(EFFECT_CLICK_STAR_INIT_SIZE, EFFECT_CLICK_STAR_INIT_SIZE, 0.0f),
														    D3DXCOLOR(1.0f, 1.0f, 1.0f, EFFECT_CLICK_STAR_INIT_ALPHA),
														    CEffect2D::EFFECT2D_TYPE::NONE);
		m_pStarBg[nCntStar]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("effect000.jpg"));
		m_pStarBg[nCntStar]->SetPriority((int)(CObject::PRIORITY::CLICK_EFFECT));

		m_pStar[nCntStar] = CObject2D::Create(D3DXVECTOR3(m_pos.x + cosf(D3DX_PI * 2.0f / EFFECT_CLICK_STAR_NUM * nCntStar) * m_fStarDiffer,
			                                              m_pos.y + sinf(D3DX_PI * 2.0f / EFFECT_CLICK_STAR_NUM * nCntStar) * m_fStarDiffer, 0.0f),
			                                              D3DXVECTOR3(EFFECT_CLICK_STAR_INIT_SIZE, EFFECT_CLICK_STAR_INIT_SIZE, 0.0f),
			                                              (int)(CObject::PRIORITY::CLICK_EFFECT));
		m_pStar[nCntStar]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("effect_star.png"));
		m_pStar[nCntStar]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, EFFECT_CLICK_STAR_INIT_ALPHA));
	}
	m_pStarBg[0]->SetCol(EFFECT_CLICK_STAR_01_COL);
	m_pStarBg[1]->SetCol(EFFECT_CLICK_STAR_02_COL);
	m_pStarBg[2]->SetCol(EFFECT_CLICK_STAR_03_COL);

	//�~�G�t�F�N�g�̐���
	m_pRing[0] = CEffect2D::Create(m_pos, D3DXVECTOR3(1.0f, 1.0f, 0.0f), EFFECT_CLICK_RING_COL, CEffect2D::EFFECT2D_TYPE::NONE);
	m_pRing[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("effect_ring.jpg"));
	m_pRing[0]->SetPriority((int)(CObject::PRIORITY::CLICK_EFFECT));

	return S_OK;
}

//================================================
//�I������
//================================================
void CEffectClick::Uninit(void)
{
	Release();
}

//================================================
//�X�V����
//================================================
void CEffectClick::Update(void)
{
	//�J�E���^�[�����Z
	m_nCounter++;

	//�L���L���G�t�F�N�g�̏���
	Sparkle();

	//���G�t�F�N�g�̏���
	Star();

	//�~�G�t�F�N�g�̏���
	Ring();
}

//================================================
//�`�揈��
//================================================
void CEffectClick::Draw(void)
{
	
}

//================================================
//��������
//================================================
CEffectClick *CEffectClick::Create(const D3DXVECTOR3 &pos)
{
	//�C���X�^���X�̐���
	CEffectClick *pEffectClick = nullptr;
	if (pEffectClick == nullptr)
	{
		pEffectClick = new CEffectClick();
		if (pEffectClick != nullptr)
		{
			pEffectClick->m_pos = pos;
			pEffectClick->Init();
		}
	}
	return pEffectClick;
}

//================================================
//�L���L���G�t�F�N�g�̏���
//================================================
void CEffectClick::Sparkle(void)
{
	if (m_pSparkle != nullptr)
	{
		//�L���L���G�t�F�N�g�̃T�C�Y���擾
		D3DXVECTOR3 SparkleSize = m_pSparkle->GetSize();
		//����̒l�ȉ��̎�
		if (m_nCounter <= EFFECT_CLICK_SPARKLE_ADD_SIZE_TIME)
		{
			//�T�C�Y������̒l���傫������
			SparkleSize *= EFFECT_CLICK_SPARKLE_ADD_SIZE;
		}
		else
		{//����̒l���傫���Ƃ�
		 //�T�C�Y������̒l������������
			SparkleSize *= EFFECT_CLICK_SPARKLE_SUBTRACT_SIZE;
		}

		//����̒l��菬�����Ȃ�����
		if (SparkleSize.x < 1.0f || SparkleSize.y < 1.0f)
		{
			//����
			m_pSparkle->Uninit();
			m_pSparkle = nullptr;
		}
		else
		{
			//�ʒu�ƃT�C�Y��ݒ�
			m_pSparkle->SetPos(m_pSparkle->GetPos(), SparkleSize);
		}
	}
}

//================================================
//�����O�G�t�F�N�g�̏���
//================================================
void CEffectClick::Ring(void)
{
	if (m_nCounter == EFFECT_CLICK_RING_02_CREATE_TIME)
	{
		//�~�G�t�F�N�g�̐���
		m_pRing[1] = CEffect2D::Create(m_pos, D3DXVECTOR3(1.0f, 1.0f, 0.0f), EFFECT_CLICK_RING_COL, CEffect2D::EFFECT2D_TYPE::NONE);
		m_pRing[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("effect_ring.jpg"));
		m_pRing[1]->SetPriority((int)(CObject::PRIORITY::CLICK_EFFECT));
	}

	if (m_pRing[0] != nullptr)
	{
		//����̒l���傫���Ȃ�����
		if (m_nCounter > EFFECT_CLICK_RING_01_SUBTRACT_SIZE_TIME)
		{
			//�T�C�Y���Z�ʂ����炵�Ă���
			m_ringAddSize[0] *= EFFECT_CLICK_RING_01_SUBTRACT_SIZE;

			//�J���[�擾
			D3DXCOLOR ringCol = m_pRing[0]->GetCol();
			//��������
			ringCol.a -= EFFECT_CLICK_RING_01_SUBTRACT_ALPHA;
			//�����Ȃ��Ȃ�����
			if (ringCol.a <= 0.0f)
			{
				//����
				m_pRing[0]->Uninit();
				m_pRing[0] = nullptr;
			}
			else
			{
				//�J���[�ݒ�
				m_pRing[0]->SetCol(ringCol);
			}
		}
	}

	if (m_pRing[1] != nullptr)
	{
		//����̒l���傫���Ȃ�����
		if (m_nCounter > EFFECT_CLICK_RING_02_SUBTRACT_SIZE_TIME)
		{
			//�T�C�Y���Z�ʂ����炵�Ă���
			m_ringAddSize[1] *= EFFECT_CLICK_RING_02_SUBTRACT_SIZE;

			//�J���[�擾
			D3DXCOLOR ringCol = m_pRing[1]->GetCol();
			//��������
			ringCol.a -= EFFECT_CLICK_RING_02_SUBTRACT_ALPHA;
			//�����Ȃ��Ȃ�����
			if (ringCol.a <= 0.0f)
			{
				//����
				m_pRing[1]->Uninit();
				m_pRing[1] = nullptr;
				Uninit();
			}
			else
			{
				//�J���[�ݒ�
				m_pRing[1]->SetCol(ringCol);
			}
		}
	}

	for (int nCntRing = 0; nCntRing < EFFECT_CLICK_RING_NUM; nCntRing++)
	{
		if (m_pRing[nCntRing] != nullptr)
		{
			//�T�C�Y���擾
			D3DXVECTOR3 lingSize = m_pRing[nCntRing]->GetSize();
			//�T�C�Y��傫������
			lingSize += m_ringAddSize[nCntRing];
			//�T�C�Y��ݒ�
			m_pRing[nCntRing]->SetPos(m_pRing[nCntRing]->GetPos(), lingSize);
		}
	}
}

//================================================
//���G�t�F�N�g�̏���
//================================================
void CEffectClick::Star(void)
{
	//�ʒu�����������S���痣��
	m_fStarDiffer += EFFECT_CLICK_STAR_ADD_DIFFER;
	//���������������Z����
	m_fStarRot[0] += EFFECT_CLICK_STAR_ADD_ROT;
	m_fStarRot[1] += EFFECT_CLICK_STAR_ADD_ROT;
	m_fStarRot[2] -= EFFECT_CLICK_STAR_ADD_ROT;

	for (int nCntStar = 0; nCntStar < EFFECT_CLICK_STAR_NUM; nCntStar++)
	{
		if (m_pStar[nCntStar] != nullptr)
		{
			//�ʒu�擾
			D3DXVECTOR3 starPos = m_pStar[nCntStar]->GetPos();
			//�ʒu���ړ�������
			starPos = D3DXVECTOR3(m_pos.x + cosf(D3DX_PI * 2.0f / EFFECT_CLICK_STAR_NUM * nCntStar) * m_fStarDiffer,
				m_pos.y + sinf(D3DX_PI * 2.0f / EFFECT_CLICK_STAR_NUM * nCntStar) * m_fStarDiffer, 0.0f);
			//�ʒu�ݒ�
			m_pStar[nCntStar]->SetPos(starPos, m_pStar[nCntStar]->GetSize(), m_fStarRot[nCntStar]);

			//�F�擾
			D3DXCOLOR starCol = m_pStar[nCntStar]->GetCol();
			//����̒l�ȉ���������
			if (m_nCounter <= EFFECT_CLICK_STAR_SUBTRACT_ALPHA_TIME)
			{
				//1.0f��菬����������
				if (starCol.a < 1.0f)
				{
					//�F��Z������
					starCol.a += EFFECT_CLICK_STAR_ADD_ALPHA;
					//1.0f���傫���Ȃ�����
					if (starCol.a > 1.0f)
					{
						//1.0�ɂ���
						starCol.a = 1.0f;
					}
					//�F��ݒ�
					m_pStar[nCntStar]->SetCol(starCol);
				}
			}
			else
			{//����̒l���傫��������
			 //�F�𔖂�����
				starCol.a -= EFFECT_CLICK_STAR_SUBTRACT_ALPHA;
				//�����Ȃ��Ȃ�����
				if (starCol.a <= 0.0f)
				{
					//����
					m_pStar[nCntStar]->Uninit();
					m_pStar[nCntStar] = nullptr;
				}
				else
				{
					//�F��ݒ�
					m_pStar[nCntStar]->SetCol(starCol);
				}
			}
		}
	}

	for (int nCntStarBg = 0; nCntStarBg < EFFECT_CLICK_STAR_NUM; nCntStarBg++)
	{
		if (m_pStarBg[nCntStarBg] != nullptr)
		{
			//�ʒu�擾
			D3DXVECTOR3 starPos = m_pStarBg[nCntStarBg]->GetPos();
			//�ʒu���ړ�������
			starPos = D3DXVECTOR3(m_pos.x + cosf(D3DX_PI * 2.0f / EFFECT_CLICK_STAR_NUM * nCntStarBg) * m_fStarDiffer,
				                  m_pos.y + sinf(D3DX_PI * 2.0f / EFFECT_CLICK_STAR_NUM * nCntStarBg) * m_fStarDiffer, 0.0f);
			//�ʒu�ݒ�
			m_pStarBg[nCntStarBg]->SetPos(starPos, m_pStarBg[nCntStarBg]->GetSize(), m_fStarRot[nCntStarBg]);

			//�F�擾
			D3DXCOLOR starCol = m_pStarBg[nCntStarBg]->GetCol();
			//����̒l�ȉ���������
			if (m_nCounter <= EFFECT_CLICK_STAR_SUBTRACT_ALPHA_TIME)
			{
				//1.0f��菬����������
				if (starCol.a < 1.0f)
				{
					//�F��Z������
					starCol.a += EFFECT_CLICK_STAR_ADD_ALPHA;
					//1.0f���傫���Ȃ�����
					if (starCol.a > 1.0f)
					{
						//1.0�ɂ���
						starCol.a = 1.0f;
					}
					//�F��ݒ�
					m_pStarBg[nCntStarBg]->SetCol(starCol);
				}
			}
			else
			{//����̒l���傫��������
			 //�F�𔖂�����
				starCol.a -= EFFECT_CLICK_STAR_SUBTRACT_ALPHA;
				//�����Ȃ��Ȃ�����
				if (starCol.a <= 0.0f)
				{
					//����
					m_pStarBg[nCntStarBg]->Uninit();
					m_pStarBg[nCntStarBg] = nullptr;
				}
				else
				{
					//�F��ݒ�
					m_pStarBg[nCntStarBg]->SetCol(starCol);
				}
			}
		}
	}
}
