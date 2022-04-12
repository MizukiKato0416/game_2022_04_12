//================================================
//�|�[�Y����
//Authore:��������
//================================================
#include "renderer.h"
#include "pause.h"
#include "manager.h"
#include "texture.h"
#include "object2D.h"
#include "input_keyboard.h"
#include "input_pad_d.h"
#include "fade.h"
#include "menu.h"

//================================================
//�}�N����`
//================================================
#define PAUSE_START_POS_Y		(340.0f)		//STARTUI�̈ʒuY
#define PAUSE_EXIT_POS_Y		(460.0f)		//EXITUI�̈ʒuY

//================================================
//�ÓI�����o�ϐ��錾
//================================================
bool CPause::m_bPause = false;			//�|�[�Y��ʂ��ǂ���

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CPause::CPause(int nPriority) :CObject(nPriority)
{
	memset(&m_apObject2D, NULL, sizeof(m_apObject2D));
	m_bPause = false;
	m_pObject2D = nullptr;
	m_nSelect = SELECT::SELECT_START;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CPause::~CPause()
{

}

//================================================
//����������
//================================================
HRESULT CPause::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_bPause = false;
	m_nSelect = SELECT::SELECT_START;

	return S_OK;
}

//================================================
//�I������
//================================================
void CPause::Uninit(void)
{
	m_bPause = false;
	
	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CPause::Update(void)
{
	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�t�F�[�h�擾����
	CFade *pFade;
	pFade = CManager::GetFade();

	//�p�b�h�擾����
	CInputPadD *pInputPadD;
	pInputPadD = CManager::GetInputPadD();
	DIJOYSTATE2 JoyStick = pInputPadD->GetGamepad();
	DIJOYSTATE2 JoyStickOld = pInputPadD->GetGamepadOld();

	//P�L�[���X�^�[�g�{�^���Ń|�[�Y
	if (pInputKeyboard->GetTrigger(DIK_P) == true || pInputPadD->GetTrigger(CInputPadD::START) == true)
	{
		if (m_bPause == false)
		{
			m_bPause = true;

			//�t���[�����쐬
			m_pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
										    D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_PAUSE);
			m_pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_PAUSE"));

			//UI���쐬
			m_apObject2D[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, PAUSE_START_POS_Y, 0.0f),
		                                        D3DXVECTOR3(MENU_UI_START_SIZE_X * 0.8f, MENU_UI_START_SIZE_Y * 0.8f, 0.0f), CObject::PRIORITY_PAUSE);
			m_apObject2D[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_START"));

			m_apObject2D[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, PAUSE_EXIT_POS_Y, 0.0f),
		                                     D3DXVECTOR3(MENU_UI_EXIT_SIZE_X* 0.8f, MENU_UI_EXIT_SIZE_Y * 0.8f, 0.0f), CObject::PRIORITY_PAUSE);
			m_apObject2D[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EXIT"));

			//�F�̐ݒ�
			m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));

			m_nSelect = SELECT_START;			//�ŏ��͍ĊJ��I�𒆂ɂ���
		}
		else
		{
			m_bPause = false;

			m_pObject2D->Uninit();
			m_pObject2D = nullptr;

			for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
			{
				m_apObject2D[nCnt]->Uninit();
				m_apObject2D[nCnt] = nullptr;
			}
		}
	}

	if (m_bPause == true)
	{
		//�I������Ă���Ƃ��͐F��Z�����đI������Ă��Ȃ��Ƃ��͔�������
		if (m_nSelect == SELECT_START)
		{
			m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
		}
		else if (m_nSelect == SELECT_EXIT)
		{
			m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
			m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		//�e�I������I�𒆂�ENTER�L�[�AB�{�^������������
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputPadD->GetTrigger(CInputPadD::B) == true)
		{
			switch (m_nSelect)
			{
			case SELECT_START:
				////����SE�Đ�
				//pSound->Play(CSound::SOUND_LABEL_DECISION_SE);
				////���ʒ���
				//pSound->ControllVoice(CSound::SOUND_LABEL_DECISION_SE, 2.0f);
				break;
			case SELECT_EXIT:
				////����SE�Đ�
				//pSound->Play(CSound::SOUND_LABEL_DECISION_SE);
				////���ʒ���
				//pSound->ControllVoice(CSound::SOUND_LABEL_DECISION_SE, 2.0f);
				//���j���[��ʂɖ߂�
				if (pFade->GetFade() == CFade::FADE_NONE)
				{
					pFade->SetFade(CManager::MODE::MENU);
				}
				break;
			default:
				break;
			}

			////�T�E���h����
			//pSound->ControllVoice(CSound::SOUND_LABEL_GAME_BGM, 0.5f);
			//pSound->ControllVoice(CSound::SOUND_LABEL_TUTORIAL_BGM, 0.5f);

			m_bPause = false;

			m_pObject2D->Uninit();
			m_pObject2D = nullptr;

			for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
			{
				m_apObject2D[nCnt]->Uninit();
				m_apObject2D[nCnt] = nullptr;
			}
		}

	


		//W�L�[�A���L�[�������A���X�e�B�b�N����ɓ|�����Ƃ�
		if (pInputKeyboard->GetTrigger(DIK_W) == true || pInputKeyboard->GetTrigger(DIK_UP) == true ||
			((float)JoyStick.lY < 0.0f && (float)JoyStickOld.lY == 0.0f))
		{
			//���݂̑I�����؂�ւ�
			if (m_nSelect != SELECT_START)
			{
				////�I��SE�Đ�
				//pSound->Play(CSound::SOUND_LABEL_CHOICE_SE);
				
				m_nSelect--;
				//�I������Ă�����̂�Z������Ă��Ȃ����̂𔖂��ݒ�
				m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
			}
		}
		//S�L�[�A���L�[�������܂��͍��X�e�B�b�N�����ɓ|�����Ƃ�
		if (pInputKeyboard->GetTrigger(DIK_S) == true || pInputKeyboard->GetTrigger(DIK_DOWN) == true ||
			((float)JoyStick.lY > 0.0f && (float)JoyStickOld.lY == 0.0f))
		{
			//���݂̑I�����؂�ւ�
			if (m_nSelect != SELECT_EXIT)
			{
				////�I��SE�Đ�
				//pSound->Play(CSound::SOUND_LABEL_CHOICE_SE);

				m_nSelect++;
				//�I������Ă�����̂�Z������Ă��Ȃ����̂𔖂��ݒ�
				m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
				m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
	}
}

//================================================
//�`�揈��
//================================================
void CPause::Draw(void)
{

}

//================================================
//�|�[�Y�擾����
//================================================
bool CPause::GetPause(void)
{
	return m_bPause;
}

//================================================
//�|�[�Y�ݒ菈��
//================================================
bool CPause::SetPause(bool bPause)
{
	m_bPause = bPause;
	return m_bPause;
}
//================================================
//��������
//================================================
CPause* CPause::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X�̐���
	CPause *pPause = nullptr;
	if (pPause == nullptr)
	{
		pPause = new CPause;
		if (pPause != nullptr)
		{
			pPause->Init(pos, size);
		}
	}
	return pPause;
}