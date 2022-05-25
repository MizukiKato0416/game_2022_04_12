//================================================
//���P�b�g�V�[������
//Authore:��������
//================================================
#include "ending_scene.h"
#include "manager.h"
#include "texture.h"
#include "fade.h"
#include "sound.h"
#include "object2D.h"

#ifdef _DEBUG
#include "input_keyboard.h"
#endif // !_DEBUG

//================================================
//�}�N����`
//================================================

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CEndingScene::CEndingScene()
{
	
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
			pFade->SetFade(CManager::MODE::RESULT);
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