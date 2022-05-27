//================================================
//�G���f�B���O�V�[������
//Authore:��������
//================================================
#include "ending_scene.h"
#include "manager.h"
#include "texture.h"
#include "fade.h"
#include "sound.h"
#include "object2D.h"
#include "next_dialog_ui.h"
#include "input_mouse.h"
#include "play_data.h"
#include "trophy.h"
#include "history_letter.h"
#include "dialog.h"

#ifdef _DEBUG
#include "input_keyboard.h"
#endif // !_DEBUG

//================================================
//�}�N����`
//================================================
#define ENDING_SCENE_ENDROLL_SIZE_Y			(5045.0f)		//�G���h���[���̃T�C�YY
#define ENDING_SCENE_ENDROLL_SPEED			(3.0f)			//�G���h���[���̑���
#define ENDING_SCENE_ENDROLL_SPEED_SKIP		(9.0f)			//SKIP����Ƃ��̃G���h���[���̑���
#define ENDING_SCENE_CREATE_DIALOG_TIME		(60)			//��b���o�Ă���܂ł̎���

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CEndingScene::CEndingScene()
{
	m_pObject2D = nullptr;
	m_pNextDialogUI = nullptr;
	m_pDialog = nullptr;
	m_nConter = 0;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CEndingScene::~CEndingScene()
{

}

//================================================
//����������
//================================================
HRESULT CEndingScene::Init(void)
{
	//�T�E���h�擾
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();
	//�~�߂�
	sound->Stop();
	//�Đ�����
	sound->Play(CSound::SOUND_LABEL::ENDROOL_BGM);
	sound->ControllVoice(CSound::SOUND_LABEL::ENDROOL_BGM, 0.7f);

	//�ϐ�������
	m_pNextDialogUI = nullptr;
	m_nConter = 0;

	//�G���h���[���̐���
	m_pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT + ENDING_SCENE_ENDROLL_SIZE_Y / 2.0f, 0.0f),
                                    D3DXVECTOR3(SCREEN_WIDTH, ENDING_SCENE_ENDROLL_SIZE_Y, 0.0f),
		                            static_cast<int>(CObject::PRIORITY::UI));
	m_pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("endroll.png"));

	return S_OK;
}

//================================================
//�I������
//================================================
void CEndingScene::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CEndingScene::Update(void)
{
	//�ʒu���擾
	D3DXVECTOR3 pos = m_pObject2D->GetPos();

	//�ʒuY������̒l����
	pos.y -= ENDING_SCENE_ENDROLL_SPEED;

	//�Ō�܂ōs������
	if (pos.y <= 0.0f - ENDING_SCENE_ENDROLL_SIZE_Y / 2.0f + SCREEN_HEIGHT)
	{
		//�~�߂�
		pos.y = 0.0f - ENDING_SCENE_ENDROLL_SIZE_Y / 2.0f + SCREEN_HEIGHT;

		//�J�E���^�[�����Z
		m_nConter++;

		if (m_nConter > ENDING_SCENE_CREATE_DIALOG_TIME)
		{
			if (m_pDialog == nullptr)
			{
				//��b���̐���
				m_pDialog = CDialog::Create(CDialog::SCENE_TYPE::ENDROLL_SCENE);

				//�g���t�B�[�̃t���O��Ԃ��擾
				vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
				//�g���t�B�[���擾�������Ƃ��Ȃ�������
				if (flag[(int)CTrophy::TROPHY::ENDROLL] == false)
				{
					//�擾������
					flag[(int)CTrophy::TROPHY::ENDROLL] = true;
					//�t���O�𗧂Ă�
					CManager::GetInstance()->GetPlayData()->SetFlag(flag);
					CHistory::Create(CTrophy::TROPHY::ENDROLL);
				}
			}
		}
	}
	else
	{
		//�}�E�X�擾����
		CInputMouse *pInputMouse;
		pInputMouse = CManager::GetInstance()->GetInputMouse();

		//�}�E�X���������u��
		if (pInputMouse->GetPress(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			//����ɈʒuY������̒l����
			pos.y -= ENDING_SCENE_ENDROLL_SPEED_SKIP;
		}
	}

	//�ʒu�ݒ�
	m_pObject2D->SetPos(pos, m_pObject2D->GetSize());

#ifdef _DEBUG
	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//Enter�L�[����������
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		//�t�F�[�h�擾����
		CFade *pFade;
		pFade = CManager::GetInstance()->GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE::TITLE);
		}
	}
#endif // !_DEBUG
}

//================================================
//�`�揈��
//================================================
void CEndingScene::Draw(void)
{
	
}