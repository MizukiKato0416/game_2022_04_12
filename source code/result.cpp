//================================================
//���U���g����
//Author: ��������
//================================================
#include "result.h"
#include "manager.h"
#include "input_mouse.h"
#include "fade.h"
#include "texture.h"
#include "ranking.h"
#include "sound.h"

//================================================
//�}�N����`
//================================================
#define RESULT_TO_TITLE_COUNT			(900)				//�^�C�g���ɍs���܂ł̊Ԋu
#define RESULT_RANKING_POS_Y			(150.0f)			//�����L���O�̍���

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CResult::CResult(CObject::PRIORITY Priority) :CObject(Priority)
{
	m_nAnim = 1;
	m_nResultCounter = 0;
	m_bCommu = false;
	m_bBg = false;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CResult::~CResult()
{

}

//================================================
//����������
//================================================
HRESULT CResult::Init(void)
{
	//�T�E���h�擾
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();

	sound->Stop();
	//BGM�ݒ�
	sound->Play(CSound::SOUND_LABEL::RESULT_BGM);
	sound->ControllVoice(CSound::SOUND_LABEL::RESULT_BGM, 0.4f);

	//�����L���O�̐���
	m_pRank = CRanking::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, RESULT_RANKING_POS_Y, 0.0f), D3DXVECTOR3(RANKING_POLYGON_WIDTH, RANKING_POLYGON_HEIGHT, 0.0f));

	m_nResultCounter = 0;
	return S_OK;
}

//================================================
//�I������
//================================================
void CResult::Uninit(void)
{	
	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CResult::Update(void)
{
	//�}�E�X�擾
	CInputMouse *pMouse = CManager::GetInstance()->GetInputMouse();
	//�T�E���h�擾
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();

	//�}�E�X���N���b�N������
	if (pMouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
	{
		//�t�F�[�h�擾����
		CFade *pFade;
		pFade = CManager::GetInstance()->GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE &&
			m_pCommu == nullptr &&
			m_pRank->GetOnece() == true)
		{
			//SE�ݒ�
			sound->ControllVoice(CSound::SOUND_LABEL::DECISION_SE, 1.2f);
			sound->Play(CSound::SOUND_LABEL::DECISION_SE);
			//�^�C�g���ɑJ��
			pFade->SetFade(CManager::MODE::TITLE);
		}
	}

	//�ʐM���I�������
	if (m_pCommu == nullptr &&
		m_pRank->GetOnece() == true)
	{
		//�J�E���^�[�����Z
		m_nResultCounter++;
	}

	//����̒l���傫���Ȃ�����
	if (m_nResultCounter >= RESULT_TO_TITLE_COUNT)
	{
		//�t�F�[�h�擾����
		CFade *pFade;
		pFade = CManager::GetInstance()->GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			m_nResultCounter = 0;
			//�^�C�g���ɍs��
			pFade->SetFade(CManager::MODE::TITLE);
		}
	}

	if (m_pRank->GetOnece() == true)
	{
		if (m_bBg == false)
		{
			if (m_pCommu != nullptr)
			{
				m_pCommu->Uninit();
				m_pCommu = nullptr;
			}
			if (m_pRank->GetConnect() == true)
			{
				CObject2D *pObject2D;
				pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Bg.png"));
				pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH / 2.6f, SCREEN_HEIGHT / 1.1f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("frame_Trophy.png"));
				pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 0.0f + 70.0f, 0.0f),
					D3DXVECTOR3(500.0f, 70.0f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Ranking.png"));
			}
			else
			{
				CObject2D *pObject2D;
				pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Bg.png"));
				pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH / 2.6f, SCREEN_HEIGHT / 1.1f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("frame_Trophy.png"));
				pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 0.0f + 70.0f, 0.0f),
					D3DXVECTOR3(500.0f, 70.0f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Ranking.png"));
			}
			m_bBg = true;
		}
	}
	else
	{
		if (m_pCommu == nullptr)
		{
			if (m_bCommu == false)
			{
				m_pCommu = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - 280.0f, SCREEN_HEIGHT - 50.0f, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH / 2.2f, SCREEN_HEIGHT * 0.15f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_pCommu->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("now_loading.png"));
				m_pCommu->SetTex(0, 4);
				m_bCommu = true;
			}
		}
		else
		{
			m_nAnimSpeed++;
			if (m_nAnimSpeed >= 25)
			{
				m_pCommu->SetTex(m_nAnim, 4);
				m_nAnim++;
				if (m_nAnim >= 4)
				{
					m_nAnim = 0;
				}
				m_nAnimSpeed = 0;
			}
		}
	}
}

//================================================
//�`�揈��
//================================================
void CResult::Draw(void)
{
	
}
