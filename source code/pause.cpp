//================================================
//�|�[�Y����
//Authore:��������
//================================================
#include "renderer.h"
#include "pause.h"
#include "manager.h"
#include "texture.h"
#include "object2D.h"
#include "input_mouse.h"
#include "input_keyboard.h"
#include "pause.h"
#include "fade.h"
#include "game01.h"
#include "sound.h"

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
CPause::CPause(CObject::PRIORITY Priority) :CObject(Priority)
{
	memset(&m_apObject2D, NULL, sizeof(m_apObject2D));
	m_bPause = false;
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
HRESULT CPause::Init(void)
{
	m_bPause = false;
	m_pPauseButton = CObject2D::Create(D3DXVECTOR3(0.0f + (250.0f / 2), SCREEN_HEIGHT - (75.0f / 2), 0.0f),
									   D3DXVECTOR3(250.0f, 75.0f, 0.0f), static_cast<int>(CObject::PRIORITY::PAUSE));
	m_pPauseButton->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("pause_button.png"));

	return S_OK;
}

//================================================
//�I������
//================================================
void CPause::Uninit(void)
{
	m_bPause = false;
	
	if (m_pPauseButton != nullptr)
	{
		m_pPauseButton->Uninit();
		m_pPauseButton = nullptr;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CPause::Update(void)
{
	D3DXVECTOR3 button_pos = m_pPauseButton->GetPos();
	D3DXVECTOR3 button_size = m_pPauseButton->GetSize();
	POINT point;
	HWND hwnd;
	CInputMouse *mouse;
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();
	hwnd = CManager::GetWindowHandle();
	GetCursorPos(&point);
	ScreenToClient(hwnd, &point);
	mouse = CManager::GetInstance()->GetInputMouse();

	//�t�F�[�h�擾����
	CFade *pFade;
	pFade = CManager::GetFade();

	//P�L�[���X�^�[�g�{�^���Ń|�[�Y
	if (m_bPause == false)
	{
		m_pPauseButton->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		if (button_pos.x - button_size.x / 2.0f <= point.x &&
			button_pos.x + button_size.x / 2.0f >= point.x &&
			button_pos.y - button_size.y / 2.0f <= point.y &&
			button_pos.y + button_size.y / 2.0f >= point.y)
		{
			if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
			{
				sound->ControllVoice(CSound::SOUND_LABEL::DECISION_SE, 1.2f);
				sound->Play(CSound::SOUND_LABEL::DECISION_SE);
				//�Q�[�����Ƀ|�[�Y�̃t���O�������Ă��Ȃ�������
				if (CManager::GetInstance()->GetGame01()->GetPause() == false)
				{
					//�t���O�𗧂Ă�
					CManager::GetInstance()->GetGame01()->SetPause(true);
				}

				m_bPause = true;

				//�t���[�����쐬
				m_pObject2D[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::PAUSE));
				m_pObject2D[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("pause_frame.png"));

				m_pObject2D[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 0.0f + 70.0f, 0.0f),
					D3DXVECTOR3(500.0f, 70.0f, 0.0f), static_cast<int>(CObject::PRIORITY::PAUSE));
				m_pObject2D[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("pause.png"));

				//UI���쐬
				m_apObject2D[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, (SCREEN_HEIGHT / 2.0f) - 100.0f, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 5.0f, 0.0f), static_cast<int>(CObject::PRIORITY::PAUSE));
				m_apObject2D[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("start.png"));

				m_apObject2D[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, (SCREEN_HEIGHT / 2.0f) + 100.0f, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH / 1.3f, SCREEN_HEIGHT / 3.8f, 0.0f), static_cast<int>(CObject::PRIORITY::PAUSE));
				m_apObject2D[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("exit.png"));
			}
		}
		else
		{
			m_pPauseButton->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	if (m_bPause == true)
	{
		sound->ControllVoice(CSound::SOUND_LABEL::GAME_BGM, 0.4f);
		for (int count = 0; count < SELECT_MAX; count++)
		{
			if (m_apObject2D[count] != nullptr)
			{
				D3DXVECTOR3 pos = m_apObject2D[count]->GetPos();
				D3DXVECTOR3 size = m_apObject2D[count]->GetSize();

				if (pos.x - size.x / 2.0f <= point.x &&
					pos.x + size.x / 2.0f >= point.x &&
					pos.y - size.y / 2.0f <= point.y &&
					pos.y + size.y / 2.0f >= point.y)
				{
					m_apObject2D[count]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
					if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
					{
						//�Q�[�����Ƀ|�[�Y�̃t���O�������Ă��Ȃ�������
						if (CManager::GetInstance()->GetGame01()->GetPause() == false)
						{
							//�t���O�𗧂Ă�
							CManager::GetInstance()->GetGame01()->SetPause(true);
						}

						m_bPause = false;
						switch (count)
						{
						case SELECT_START:
							sound->ControllVoice(CSound::SOUND_LABEL::DECISION_SE, 1.2f);
							sound->Play(CSound::SOUND_LABEL::DECISION_SE);
							m_pObject2D[0]->Uninit();
							m_pObject2D[0] = nullptr;
							m_pObject2D[1]->Uninit();
							m_pObject2D[1] = nullptr;

							for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
							{
								m_apObject2D[nCnt]->Uninit();
								m_apObject2D[nCnt] = nullptr;
							}
							break;
						case SELECT_EXIT:
							if (pFade->GetFade() == CFade::FADE_NONE)
							{
								sound->ControllVoice(CSound::SOUND_LABEL::DECISION_SE, 1.2f);
								sound->Play(CSound::SOUND_LABEL::DECISION_SE);
								pFade->SetFade(CManager::MODE::TITLE);
							}
							break;
						default:
							break;
						}
					}
				}
				else
				{
					m_apObject2D[count]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}
		}
	}
	else
	{
		sound->ControllVoice(CSound::SOUND_LABEL::GAME_BGM, 1.6f);
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
bool CPause::SetPause(const bool &bPause)
{
	m_bPause = bPause;
	return m_bPause;
}
//================================================
//��������
//================================================
CPause* CPause::Create(void)
{
	//�C���X�^���X�̐���
	CPause *pPause = nullptr;
	if (pPause == nullptr)
	{
		pPause = new CPause;
		if (pPause != nullptr)
		{
			pPause->Init();
		}
	}
	return pPause;
}