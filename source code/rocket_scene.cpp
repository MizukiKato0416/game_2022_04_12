//================================================
//���P�b�g�V�[������
//Authore:��������
//================================================
#include "rocket_scene.h"
#include "manager.h"
#include "texture.h"
#include "fade.h"
#include "sound.h"
#include "model_single.h"
#include "model.h"
#include "player.h"
#include "score.h"
#include "play_data.h"

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
CRocketScene::CRocketScene()
{
	m_pPlayer = nullptr;
	m_pRocket = nullptr;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CRocketScene::~CRocketScene()
{

}

//================================================
//����������
//================================================
HRESULT CRocketScene::Init(void)
{
	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();
	//�~�߂�
	pSound->Stop();

	//���P�b�g�̐���
	m_pRocket = CModelSingle::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CXload::X_TYPE_ROCKET, NULL, true);

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f));

	//�X�R�A�̐���
	CScore *pSocre = nullptr;
	pSocre = CScore::Create(D3DXVECTOR3(0.0f + (SCORE_POLYGON_WIDTH * MAX_SCORE_POLYGON / 2.0f), SCORE_POLYGON_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(SCORE_POLYGON_WIDTH, SCORE_POLYGON_HEIGHT, 0.0f));
	CManager::GetInstance()->GetPlayData()->SetScorePoint(pSocre);


	return S_OK;
}

//================================================
//�I������
//================================================
void CRocketScene::Uninit(void)
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
void CRocketScene::Update(void)
{

	//���f���̉�]��0�ɂ���
	m_pPlayer->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//���P�b�g�Ɛe�q�֌W������
	m_pPlayer->SetObjParent(true);
	m_pPlayer->SetMtxParent(m_pRocket->GetModel()->GetMtxPoint());

	m_pPlayer->SetPos(D3DXVECTOR3(0.0f, 50.0f, 0.0f));

	//�X�R�A�����Z
	CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore(333333);

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
void CRocketScene::Draw(void)
{
	
}