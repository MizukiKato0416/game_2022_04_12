//================================================
//���j���[����
//Authore:��������
//================================================
#include "renderer.h"
#include "menu.h"
#include "manager.h"
#include "texture.h"
#include "object2D.h"
#include "input_keyboard.h"
#include "input_pad_d.h"
#include "fade.h"

//================================================
//�}�N����`
//================================================
#define MENU_UI_TUTORIAL_SIZE_X			(438.0f)	//TUTORIAL��UI�̃T�C�YX
#define MENU_UI_TUTORIAL_SIZE_Y			(84.0f)		//TUTORIAL��UI�̃T�C�YY
#define MENU_UI_START_SIZE_X			(304.0f)	//START��UI�̃T�C�YX
#define MENU_UI_START_SIZE_Y			(84.0f)		//START��UI�̃T�C�YY
#define MENU_UI_EXIT_SIZE_X				(304.0f)	//EXIT��UI�̃T�C�YX
#define MENU_UI_EXIT_SIZE_Y				(84.0f)		//EXIT��UI�̃T�C�YY
#define MENU_UI_NOT_SELECT_COLOR_ALPHA	(0.4f)		//�I������Ă��Ȃ��Ƃ���UI�̃��l

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMenu::CMenu()
{
	m_nSelect = CMenu::SELECT_MENU_TYPE::SELECT_MENU_TYPE_NONE;
	memset(&m_apObject2D, NULL, sizeof(m_apObject2D));
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CMenu::~CMenu()
{

}

//================================================
//����������
//================================================
HRESULT CMenu::Init(void)
{
	m_nSelect = CMenu::SELECT_MENU_TYPE::SELECT_MENU_TYPE_GAME_START;

	//�w�i�̐���
	CObject2D *pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 
											 D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("menu.jpg"));

	//UI�̐���
	m_apObject2D[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / (float)CMenu::SELECT_MENU_TYPE::SELECT_MENU_TYPE_MAX, 0.0f),
		                                     D3DXVECTOR3(MENU_UI_TUTORIAL_SIZE_X, MENU_UI_TUTORIAL_SIZE_Y, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	m_apObject2D[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial.png"));

	m_apObject2D[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / (float)CMenu::SELECT_MENU_TYPE::SELECT_MENU_TYPE_MAX * 2.0f, 0.0f),
		                                     D3DXVECTOR3(MENU_UI_START_SIZE_X, MENU_UI_START_SIZE_Y, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	m_apObject2D[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("start.png"));

	m_apObject2D[2] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / (float)CMenu::SELECT_MENU_TYPE::SELECT_MENU_TYPE_MAX * 3.0f, 0.0f),
		                                     D3DXVECTOR3(MENU_UI_EXIT_SIZE_X, MENU_UI_EXIT_SIZE_Y, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	m_apObject2D[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("exit.png"));

	//�I������Ă���Ƃ��͐F��Z�����đI������Ă��Ȃ��Ƃ��͔�������
	if (m_nSelect == SELECT_MENU_TYPE_TUTORIAL)
	{
		m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
		m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
	}
	else if (m_nSelect == SELECT_MENU_TYPE_GAME_START)
	{
		m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
		m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
	}
	else if (m_nSelect == SELECT_MENU_TYPE_EXIT)
	{
		m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
		m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
		m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	return S_OK;
}

//================================================
//�I������
//================================================
void CMenu::Uninit(void)
{
	////�T�E���h�擾����
	//CSound *pSound;
	//pSound = CManager::GetSound();
	////BGM�̒�~
	//pSound->Stop(CSound::SOUND_LABEL_MENU_BGM);

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CMenu::Update(void)
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

	////�T�E���h�擾����
	//CSound *pSound;
	//pSound = CManager::GetSound();

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		//�I������
		if (pInputKeyboard->GetTrigger(DIK_UP) == true ||
			((float)JoyStick.lY < 0.0f && (float)JoyStickOld.lY == 0.0f))
		{
			m_nSelect--;
			if (m_nSelect < SELECT_MENU_TYPE_TUTORIAL)
			{
				m_nSelect = SELECT_MENU_TYPE_TUTORIAL;
			}
			else
			{
				////BGM�̍Đ�
				//pSound->Play(CSound::SOUND_LABEL_CURSOR_SE);
				////�T�E���h�̉��ʒ���
				//pSound->ControllVoice(CSound::SOUND_LABEL_CURSOR_SE, 0.8f);
			}

			//�I������Ă���Ƃ��͐F��Z�����đI������Ă��Ȃ��Ƃ��͔�������
			if (m_nSelect == SELECT_MENU_TYPE_TUTORIAL)
			{
				m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
				m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
			}
			else if (m_nSelect == SELECT_MENU_TYPE_GAME_START)
			{
				m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
				m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
			}
			else if (m_nSelect == SELECT_MENU_TYPE_EXIT)
			{
				m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
				m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
				m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
		else if (pInputKeyboard->GetTrigger(DIK_DOWN) == true ||
			     ((float)JoyStick.lY > 0.0f && (float)JoyStickOld.lY == 0.0f))
		{
			m_nSelect++;
			if (m_nSelect > SELECT_MENU_TYPE_EXIT)
			{
				m_nSelect = SELECT_MENU_TYPE_EXIT;
			}
			else
			{
				////SE�̍Đ�
				//pSound->Play(CSound::SOUND_LABEL_CURSOR_SE);
				////�T�E���h�̉��ʒ���
				//pSound->ControllVoice(CSound::SOUND_LABEL_CURSOR_SE, 0.8f);
			}

			//�I������Ă���Ƃ��͐F��Z�����đI������Ă��Ȃ��Ƃ��͔�������
			if (m_nSelect == SELECT_MENU_TYPE_TUTORIAL)
			{
				m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
				m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
			}
			else if (m_nSelect == SELECT_MENU_TYPE_GAME_START)
			{
				m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
				m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
			}
			else if (m_nSelect == SELECT_MENU_TYPE_EXIT)
			{
				m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
				m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
				m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}

		//���菈��
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputPadD->GetTrigger(CInputPadD::B) == true ||
			pInputPadD->GetTrigger(CInputPadD::START) == true)
		{
			pFade->SetFade(CManager::MODE::TITLE);
		}
	}
}

//================================================
//�`�揈��
//================================================
void CMenu::Draw(void)
{
	
}