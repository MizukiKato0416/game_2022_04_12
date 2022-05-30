//================================================
//��b�̏���
//Author:KatoMizuki
//================================================
#include "object.h"
#include "dialog.h"
#include "letter.h"
#include "sound.h"
#include "next_dialog_ui.h"
#include "input_mouse.h"
#include "fade.h"
#include "trophy.h"
#include "play_data.h"
#include "history_letter.h"

//================================================
//�}�N����`
//================================================
#define DIALOG_MAX_STRING				(256)									//�����̍ő��
#define DIALOG_LETTER_CREATE_COUNT		(3)										//1�����o���܂ł̎���
#define DIALOG_ROCKY_UI_POS_Y			(260.0f)								//���b�L�[�N��UI�̈ʒuY
#define DIALOG_ROCKY_UI_SIZE_X			(545.0f * 1.0f)							//���b�L�[�N��UI�̃T�C�YX
#define DIALOG_ROCKY_UI_SIZE_Y			(566.0f * 1.0f)							//���b�L�[�N��UI�̃T�C�YY
#define DIALOG_ROCKY_FACE_UI_SIZE_X		(545.0f * 0.7f)							//���b�L�[�N�̊�UI�̃T�C�YX
#define DIALOG_ROCKY_FACE_UI_SIZE_Y		(566.0f * 0.7f)							//���b�L�[�N�̊�UI�̃T�C�YY
#define DIALOG_ROCKY_FACE_UI_POS_X		(SCREEN_WIDTH / 2.0f - 10.0f)			//���b�L�[�N�̊�UI�̈ʒuX
#define DIALOG_ROCKY_FACE_UI_POS_Y		(230.0f)								//���b�L�[�N�̊�UI�̈ʒuY
#define DIALOG_FRAME_POS_Y				(230.0f)								//�Z���t�̃t���[���ʒuY

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CDialog::CDialog(CObject::PRIORITY Priority) :CObject(Priority)
{
	m_dialogBody.clear();
	m_pLetter.clear();
	m_dialog.clear();
	m_nDialogDelay = 0;
	m_nDialogCntX = 0;
	m_nDialogCntY = 0;
	m_nLetterCreateCounter = 0;
	m_pPersonPose = nullptr;
	m_pPersonFace = nullptr;
	m_pFrame = nullptr;
	m_poseType = POSE::NORMAL;
	m_faceType = FACE::SMILE;
	m_frameType = FRAME::NORMAL;
	m_bCreateFinish = false;
	m_nDialogNum = 0;
	m_pNextDialogUI = nullptr;
	m_nCountFrame = 0;
	m_bDialogFinish = false;
	m_nMaxDialog = 0;
	m_sceneType = SCENE_TYPE::NONE;
	m_bRead = false;
	m_nextScene = CManager::MODE::TITLE;
	m_bUninit = false;
	m_pBg = nullptr;
	m_bShake = false;
	m_createPosePos = { 0.0f, 0.0f, 0.0f };
	m_createFacePos = { 0.0f, 0.0f, 0.0f };
	m_move = { 0.0f, 0.0f, 0.0f };
	m_nCounterShake = 0;
	m_bShakeReturn = false;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CDialog::~CDialog()
{
	
}

//================================================
//����������
//================================================
HRESULT CDialog::Init()
{
	//�ϐ�������
	m_nLetterCreateCounter = DIALOG_LETTER_CREATE_COUNT;
	m_pPersonPose = nullptr;
	m_pPersonFace = nullptr;
	m_pFrame = nullptr;
	m_poseType = POSE::NORMAL;
	m_faceType = FACE::SMILE;
	m_frameType = FRAME::NORMAL;
	m_bCreateFinish = false;
	m_nDialogNum = 0;
	m_pNextDialogUI = nullptr;
	m_nCountFrame = 0;
	m_bDialogFinish = false;
	m_bRead = false;
	m_bUninit = false;
	m_pBg = nullptr;
	m_bShake = false;
	m_createPosePos = { 0.0f, 0.0f, 0.0f };
	m_createFacePos = { 0.0f, 0.0f, 0.0f };
	m_move = { 0.0f, 0.0f, 0.0f };
	m_nCounterShake = 0;
	m_bShakeReturn = false;

	//�e�L�X�g�t�@�C�����[�h����
	LoadTxt();

	//�Z���t����
	SetDialog(0);

	return S_OK;
}

//================================================
//�I������
//================================================
void CDialog::Uninit(void)
{
	Release();
}

//================================================
//�X�V����
//================================================
void CDialog::Update(void)
{
	//�w�i�A�t���[���A�L�����𐶐����I�������
	if (m_bCreateFinish == true)
	{
		//�h����ԂɂȂ��Ă���Ȃ�
		if (m_bShake == true)
		{
			//�h��鏈��
			Shake();
		}

		//�����ȉ���������
		if (m_nDialogNum < m_nMaxDialog)
		{
			//�Z���t�̐����ƑS�����\�����ꂽ���ǂ������擾
			m_bDialogFinish = Dialog(m_nDialogNum);
		}
		//�S�����\�����ꂽ��
		if (m_bDialogFinish == true)
		{
			if (m_pNextDialogUI == nullptr)
			{
				//���̃Z���t�ɍs��UI�𐶐�
				m_pNextDialogUI = CNextDialogUI::Create(D3DXVECTOR3(NEXT_DILOG_UI_POS_X, NEXT_DILOG_UI_POS_Y, 0.0f),
					                                    D3DXVECTOR3(NEXT_DILOG_UI_SIZE, NEXT_DILOG_UI_SIZE, 0.0f));
				m_pNextDialogUI->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("click_ui.png"));
			}

			//�}�E�X�擾����
			CInputMouse *pInputMouse;
			pInputMouse = CManager::GetInstance()->GetInputMouse();

			//�}�E�X���������u��
			if (pInputMouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
			{
				//���̃Z���t�ɂ���
				m_nDialogNum++;

				//�����ȉ���������
				if (m_nDialogNum < m_nMaxDialog)
				{
					//�Z���t����
					SetDialog(m_nDialogNum);
				}
				else
				{
					//�T�E���h�擾
					CSound *sound;
					sound = CManager::GetInstance()->GetSound();
					//�Đ�����
					sound->Play(CSound::SOUND_LABEL::DECISION_SE);

					//�����ݒ�ɂȂ��Ă�����
					if (m_bUninit == true)
					{
						//����
						UninitDialog();
						//�w�i�̍폜
						if (m_pBg != nullptr)
						{
							m_pBg->Uninit();
							m_pBg = nullptr;
						}
						//�t���[���̍폜
						if (m_pFrame != nullptr)
						{
							m_pFrame->Uninit();
							m_pFrame = nullptr;
						}
						//��̍폜
						if (m_pPersonFace != nullptr)
						{
							m_pPersonFace->Uninit();
							m_pPersonFace = nullptr;
						}
						//�|�[�Y�̍폜
						if (m_pPersonPose != nullptr)
						{
							m_pPersonPose->Uninit();
							m_pPersonPose = nullptr;
						}
						Uninit();
						return;
					}
					else
					{
						//�t�F�[�h�擾����
						CFade *pFade;
						pFade = CManager::GetInstance()->GetFade();
						if (pFade->GetFade() == CFade::FADE_NONE)
						{
							//�^�C�g���V�[���ɑJ��
							pFade->SetFade(m_nextScene);
							//����
							UninitDialog();
							//�w�i�̍폜
							if (m_pBg != nullptr)
							{
								m_pBg->Uninit();
								m_pBg = nullptr;
							}
							//�t���[���̍폜
							if (m_pFrame != nullptr)
							{
								m_pFrame->Uninit();
								m_pFrame = nullptr;
							}
							//��̍폜
							if (m_pPersonFace != nullptr)
							{
								m_pPersonFace->Uninit();
								m_pPersonFace = nullptr;
							}
							//�|�[�Y�̍폜
							if (m_pPersonPose != nullptr)
							{
								m_pPersonPose->Uninit();
								m_pPersonPose = nullptr;
							}
						}
					}
					
				}
			}
		}
	}
}

//================================================
//�`�揈��
//================================================
void CDialog::Draw(void)
{
	
}

//================================================
//��������
//================================================
CDialog *CDialog::Create(const SCENE_TYPE &sceneType)
{
	//�C���X�^���X�̐���
	CDialog *pDialog = nullptr;
	if (pDialog == nullptr)
	{
		pDialog = new CDialog();
		if (pDialog != nullptr)
		{
			pDialog->m_sceneType = sceneType;
			pDialog->Init();
		}
	}
	return pDialog;
}


//================================================
//�Z���t����
//================================================
bool CDialog::Dialog(const int &nCntDialog)
{
	//#���������s�����ɐݒ�
	wchar_t cReturn[] = L"#";
	//���͂̃T�C�Y���擾
	int nDialogSize = m_dialog[nCntDialog].size();
	//�S�Ă̕�������������Ă��Ȃ�������
	if (m_nDialogDelay < nDialogSize)
	{
		//�t���[���̃J�E���^�[�����Z
		m_nCountFrame++;
		//����̒l���傫���Ȃ�����
		if (m_nCountFrame > m_nLetterCreateCounter)
		{
			//���s��������������
			if (m_dialog[nCntDialog][m_nDialogDelay] == *cReturn)
			{
				//���s����̂�0�ɂ���
				m_nDialogCntX = 0;
				m_nDialogCntY++;

				//����
				m_dialog[nCntDialog].erase(m_dialog[nCntDialog].begin() + m_nDialogDelay);
				nDialogSize--;
				m_nDialogDelay--;
			}
			else
			{//���s�������Ȃ�������
				//�����𐶐�
				m_pLetter.push_back(new CLetter);

				m_pLetter[m_nDialogDelay]->SetPos(D3DXVECTOR3(200.0f + (15.0f * 2.0f) * m_nDialogCntX, 600.0f + (15.0f * 2.0f) * m_nDialogCntY, 0.0f));
				m_pLetter[m_nDialogDelay]->SetSize(D3DXVECTOR3(15.0f, 15.0f, 0.0f));
				m_pLetter[m_nDialogDelay]->SetText(m_dialog[nCntDialog][m_nDialogDelay]);
				m_pLetter[m_nDialogDelay]->SetFontSize(300);
				m_pLetter[m_nDialogDelay]->SetFontWeight(500);
				m_pLetter[m_nDialogDelay]->Init();

				//�T�E���h�擾
				CSound *sound;
				sound = CManager::GetInstance()->GetSound();
				//�Đ�����
				sound->Play(CSound::SOUND_LABEL::DIALOG_SE);
				sound->ControllVoice(CSound::SOUND_LABEL::DIALOG_SE, 3.4f);

				//�J�E���^�[�����Z
				m_nDialogCntX++;
			}

			//�J�E���^�[�����Z
			m_nDialogDelay++;

			//0�ɂ���
			m_nCountFrame = 0;
		}
	}
	else
	{//�S�Ă̕����𐶐����Ă�����true��Ԃ�
		return true;
	}
	return false;
}

//================================================
//�Z���t�j������
//================================================
void CDialog::UninitDialog(void)
{
	if (m_pPersonPose != nullptr && m_pPersonFace != nullptr)
	{
		//�ʒu�ݒ�
		m_pPersonPose->SetPos(m_createPosePos, m_pPersonPose->GetSize());
		m_pPersonFace->SetPos(m_createFacePos, m_pPersonFace->GetSize());
	}
	//�ϐ�������
	m_nDialogCntX = 0;
	m_nDialogCntY = 0;
	m_nDialogDelay = 0;
	m_bShake = false;
	m_move = { 0.0f, 0.0f, 0.0f };
	m_nCounterShake = 0;
	m_bShakeReturn = false;

	int nSize = m_pLetter.size();
	//����������
	for (int nCnt = 0; nCnt < nSize; nCnt++)
	{
		m_pLetter[nCnt]->Uninit();
		m_pLetter[nCnt] = nullptr;
	}
	m_pLetter.clear();

	if (m_pNextDialogUI != nullptr)
	{
		//���̃Z���t�ɍs��UI������
		m_pNextDialogUI->Uninit();
		m_pNextDialogUI = nullptr;
	}

	m_bCreateFinish = false;
	m_bDialogFinish = false;
}

//================================================
//�Z���t�ݒ菈��
//================================================
void CDialog::SetDialog(const int &nNumDialog)
{
	//�Z���t�j������
	UninitDialog();

	m_nDialogNum = nNumDialog;

	//�|�[�Y�^�C�v�ɑ��
	m_poseType = (CDialog::POSE)m_dialogBody[nNumDialog].nPersonPose;
	//��^�C�v�ɑ��
	m_faceType = (CDialog::FACE)m_dialogBody[nNumDialog].nPersonFace;
	//�t���[���^�C�v�ɑ��
	m_faceType = (CDialog::FACE)m_dialogBody[nNumDialog].nPersonFace;

	//��������Ă��Ȃ������犎�w�i�e�N�X�`���̃p�X�������Ă�����
	if (m_pBg == nullptr && m_dialogBody[nNumDialog].sBgTexturePas.size() > 0)
	{
		//�w�i�̐���
		m_pBg = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
			                      D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
			                      static_cast<int>(CObject::PRIORITY::DIALOG));
		//�w�肵���e�N�X�`����ݒ�
		m_pBg->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture(m_dialogBody[nNumDialog].sBgTexturePas));
	}
	else if (m_pBg != nullptr  && m_dialogBody[nNumDialog].sBgTexturePas.size() > 0)
	{//���łɐ�������Ă���ꍇ
		//�w�肵���e�N�X�`����ݒ�
		m_pBg->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture(m_dialogBody[nNumDialog].sBgTexturePas));
	}
	//��������Ă��Ȃ�������
	if (m_pPersonPose == nullptr)
	{
		//�|�[�Y�̐���
		m_pPersonPose = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, DIALOG_ROCKY_UI_POS_Y, 0.0f),
			                              D3DXVECTOR3(DIALOG_ROCKY_UI_SIZE_X, DIALOG_ROCKY_UI_SIZE_Y, 0.0f),
			                              static_cast<int>(CObject::PRIORITY::DIALOG));
		m_pPersonPose->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("rocky_pose.png"));
	}
	//��������Ă��Ȃ�������
	if (m_pPersonFace == nullptr)
	{
		//��̐���
		m_pPersonFace = CObject2D::Create(D3DXVECTOR3(DIALOG_ROCKY_FACE_UI_POS_X, DIALOG_ROCKY_FACE_UI_POS_Y, 0.0f),
			                              D3DXVECTOR3(DIALOG_ROCKY_FACE_UI_SIZE_X, DIALOG_ROCKY_FACE_UI_SIZE_Y, 0.0f),
			                              static_cast<int>(CObject::PRIORITY::DIALOG));
		m_pPersonFace->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("rocky_face.png"));
	}
	//��������Ă��Ȃ�������
	if (m_pFrame == nullptr)
	{
		//�t���[���̐���
		m_pFrame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - DIALOG_FRAME_POS_Y / 2.0f, 0.0f),
			                         D3DXVECTOR3(SCREEN_WIDTH, DIALOG_FRAME_POS_Y, 0.0f),
			                         static_cast<int>(CObject::PRIORITY::DIALOG));
		m_pFrame->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("comment_frame.png"));
	}

	if (nNumDialog == 0)
	{
		//�e�N�X�`���̐ݒ�
		m_pPersonPose->SetTex((int)m_poseType, (int)POSE::MAX);
		//�e�N�X�`���̐ݒ�
		m_pPersonFace->SetTex((int)m_faceType, (int)FACE::MAX);
	}
	else
	{
		//�O�Ɏw�肵���|�[�Y�ƍ���w�肵�Ă���|�[�Y���Ⴄ�ꍇ
		if (m_dialogBody[nNumDialog - 1].nPersonPose != m_dialogBody[nNumDialog].nPersonPose)
		{
			//�e�N�X�`���̐ݒ�
			m_pPersonPose->SetTex((int)m_poseType, (int)POSE::MAX);
		}
		//�O�Ɏw�肵����ƍ���w�肵�Ă���炪�Ⴄ�ꍇ
		if (m_dialogBody[nNumDialog - 1].nPersonFace != m_dialogBody[nNumDialog].nPersonFace)
		{
			//�e�N�X�`���̐ݒ�
			m_pPersonFace->SetTex((int)m_faceType, (int)FACE::MAX);
		}
	}
	//�������I��������Ԃɂ���
	m_bCreateFinish = true;

	//�h��̃^�C�v��NONE�ł͂Ȃ��Ƃ�
	if (m_dialogBody[nNumDialog].shakeType != SHAKE_TYPE::NONE)
	{
		//�h����Ԃɂ���
		m_bShake = true;
		//�������̈ʒu��ۑ�
		m_createPosePos = m_pPersonPose->GetPos();
		m_createFacePos = m_pPersonFace->GetPos();

		//�ړ��ʂ�ݒ�
		m_move = m_dialogBody[nNumDialog].shakeSpeed;

	}

}

//================================================
//�e�L�X�g�t�@�C�����[�h����
//================================================
void CDialog::LoadTxt(void)
{
	char cString[DIALOG_MAX_STRING];
	FILE *file;
	file = fopen("data/dialog_ss.txt", "r");

	//�^�C�v�ɂ���ēǂݍ��ݎn�߂�ʒu��ς���
	string sBeginSceneType;
	string sEndSceneType;
	switch (m_sceneType)
	{
	case CDialog::SCENE_TYPE::CLICK_SCENE:
		sBeginSceneType = "BEGIN_CLICK_SCENE_DIALOG\n";
		sEndSceneType = "END_CLICK_SCENE_DIALOG\n";
		break;
	case CDialog::SCENE_TYPE::ENDROLL_SCENE:
		sBeginSceneType = "BEGIN_ENDROLL_SCENE_DIALOG\n";
		sEndSceneType = "END_ENDROLL_SCENE_DIALOG\n";
		break;
	default:
		break;
	}

	if (file != NULL)
	{
		//��s���ۑ�
		while (fgets(cString, DIALOG_MAX_STRING, file) != NULL)
		{
			//END_SCRIPT�Ə�����Ă�����
			if (strncmp("END_SCRIPT", cString, 11) == 0)
			{
				//��������߂�
				break;
			}

			//�ǂݍ���ł��Ȃ��ԂȂ�
			if (m_bRead == false)
			{
				//����̕�����������Ă�����
				if (strncmp(sBeginSceneType.c_str(), cString, sBeginSceneType.size()) == 0)
				{
					//�ǂݍ��ݎn�߂�
					m_bRead = true;
				}
			}

			//�ǂݍ��ݎn�߂��ԂȂ�
			if (m_bRead == true)
			{
				if (strncmp("BEGIN_DIALOG\n", cString, 14) == 0)
				{//BEGIN_DIALOG�Ə�����Ă�����
					//������
					DIALOG_BODY dialogBody;
					dialogBody.nPersonPose = 0;
					dialogBody.nPersonFace = 0;
					dialogBody.nFrame = 0;
					dialogBody.sBgTexturePas.clear();
					dialogBody.shakeType = SHAKE_TYPE::NONE;
					dialogBody.nNumShake = 0;
					dialogBody.shakeSpeed = {0.0f, 0.0f, 0.0f};
					dialogBody.shakeMinusSpeed = {0.0f, 0.0f, 0.0f};
					dialogBody.fShakeWidth = 0.0f;

					//�z��𑝂₷
					m_dialogBody.push_back(dialogBody);

					//�|�[�Y��ǂݍ���
					fscanf(file, "%*s%*s%d", &m_dialogBody[m_nMaxDialog].nPersonPose);
					//���ǂݍ���
					fscanf(file, "%*s%*s%d", &m_dialogBody[m_nMaxDialog].nPersonFace);
					//�t���[����ǂݍ���
					fscanf(file, "%*s%*s%d", &m_dialogBody[m_nMaxDialog].nFrame);

					char name_buf[1][DIALOG_MAX_STRING];
					string name;

					fscanf(file, "%s", name_buf[0]);

					name = name_buf[0];

					// SJIS �� wstring
					int iBufferSize = MultiByteToWideChar(CP_ACP,
						0,
						name.c_str(),
						-1,
						(wchar_t*)NULL,
						0);

					// �o�b�t�@�̎擾
					wchar_t* cpUCS2 = new wchar_t[iBufferSize];

					// SJIS �� wstring
					MultiByteToWideChar(CP_ACP,
						0,
						name.c_str(),
						-1,
						cpUCS2,
						iBufferSize);

					// string�̐���
					wstring utextbuf(cpUCS2, cpUCS2 + iBufferSize - 1);

					// �o�b�t�@�̔j��
					delete[] cpUCS2;

					m_dialog.push_back(utextbuf);
				}
				else if (strncmp("SET_NEXT_SCENE\n", cString, 16) == 0)
				{//SET_NEXT_SCENE�Ə�����Ă�����
					//���̃V�[����ǂݍ���
					fscanf(file, "%*s%*s%d", &m_nextScene);
				}
				else if (strncmp(sEndSceneType.c_str(), cString, sEndSceneType.size()) == 0)
				{//����̕�����������Ă�����
					//��������߂�
					m_bRead = false;
					break;
				}
				else if (strncmp("UNINIT_DIALOG\n", cString, 15) == 0)
				{//UNINIT_DIALOG�Ə�����Ă�����
					//�Ō�ɃN���b�N���������Ƃ��ɂ��̃N���X������
					m_bUninit = true;
				}
				else if (strncmp("SET_BG\n", cString, 8) == 0)
				{//SET_BG�Ə�����Ă�����
					//����p�ϐ���p��
					string sPas = "";
					//�e�N�X�`���̃p�X��ǂݍ���
					fscanf(file, "%s", m_dialogBody[m_nMaxDialog].sBgTexturePas.c_str());
					//���
					sPas = m_dialogBody[m_nMaxDialog].sBgTexturePas.c_str();
					//�z��̐����w��
					m_dialogBody[m_nMaxDialog].sBgTexturePas.resize(m_dialogBody[m_nMaxDialog].sBgTexturePas.size());
					//���
					m_dialogBody[m_nMaxDialog].sBgTexturePas = sPas;
				}
				else if (strncmp("SET_SHAKE\n", cString, 11) == 0)
				{//SET_SHAKE�Ə�����Ă�����
					//�^�C�v��ǂݍ���
					fscanf(file, "%*s%*s%d", &m_dialogBody[m_nMaxDialog].shakeType);
					//�񐔂�ǂݍ���
					fscanf(file, "%*s%*s%d", &m_dialogBody[m_nMaxDialog].nNumShake);
					//�X�s�[�h��ǂݍ���
					fscanf(file, "%*s%*s%f%f%f", &m_dialogBody[m_nMaxDialog].shakeSpeed.x, &m_dialogBody[m_nMaxDialog].shakeSpeed.y, &m_dialogBody[m_nMaxDialog].shakeSpeed.z);
					//�X�s�[�h���}�C�i�X����ʂ�ǂݍ���
					fscanf(file, "%*s%*s%f%f%f", &m_dialogBody[m_nMaxDialog].shakeMinusSpeed.x, &m_dialogBody[m_nMaxDialog].shakeMinusSpeed.y , &m_dialogBody[m_nMaxDialog].shakeMinusSpeed.z);
					//����ǂݍ���
					fscanf(file, "%*s%*s%f", &m_dialogBody[m_nMaxDialog].fShakeWidth);
				}
				else if (strncmp("END_DIALOG\n", cString, 12) == 0)
				{//END_DIALOG�Ə�����Ă�����
					//�����𑝂₷
					m_nMaxDialog++;
				}
			}
		}
	}
	fclose(file);
}

//================================================
//�h�ꏈ��
//================================================
void CDialog::Shake(void)
{
	if (m_pPersonPose != nullptr && m_pPersonFace != nullptr)
	{
		//�����G�Ɗ�̈ʒu���擾
		D3DXVECTOR3 posePos = m_pPersonPose->GetPos();
		D3DXVECTOR3 facePos = m_pPersonFace->GetPos();

		//�ʒu�����炷
		posePos += m_move;
		facePos += m_move;

		//�ʒu�ݒ�
		m_pPersonPose->SetPos(posePos, m_pPersonPose->GetSize());
		m_pPersonFace->SetPos(facePos, m_pPersonFace->GetSize());

		//�ړ��ʂ����炵�Ă���
		m_move += m_dialogBody[m_nDialogNum].shakeMinusSpeed;

		//�܂�Ԃ��Ă��Ȃ�������
		if (m_bShakeReturn == false)
		{
			if ((m_dialogBody[m_nDialogNum].shakeType == SHAKE_TYPE::UP_TO_DOWN && posePos.y < m_createPosePos.y - m_dialogBody[m_nDialogNum].fShakeWidth) ||
				(m_dialogBody[m_nDialogNum].shakeType == SHAKE_TYPE::DOWN_TO_UP && posePos.y > m_createPosePos.y + m_dialogBody[m_nDialogNum].fShakeWidth) ||
				(m_dialogBody[m_nDialogNum].shakeType == SHAKE_TYPE::RIGHT_AND_LEFT && posePos.x > m_createPosePos.x + m_dialogBody[m_nDialogNum].fShakeWidth))
			{
				//�܂�Ԃ�
				m_bShakeReturn = true;
				//�t�����ɂ���
				m_dialogBody[m_nDialogNum].shakeSpeed *= -1.0f;
				m_dialogBody[m_nDialogNum].shakeMinusSpeed *= -1.0f;
				//�ړ��ʂ�ݒ�
				m_move = m_dialogBody[m_nDialogNum].shakeSpeed;
				//�܂�Ԃ����񐔂�1���₷
				m_nCounterShake++;
			}
		}
		else
		{
			if ((m_dialogBody[m_nDialogNum].shakeType == SHAKE_TYPE::UP_TO_DOWN && posePos.y > m_createPosePos.y + m_dialogBody[m_nDialogNum].fShakeWidth) ||
				(m_dialogBody[m_nDialogNum].shakeType == SHAKE_TYPE::DOWN_TO_UP && posePos.y < m_createPosePos.y - m_dialogBody[m_nDialogNum].fShakeWidth) ||
				(m_dialogBody[m_nDialogNum].shakeType == SHAKE_TYPE::RIGHT_AND_LEFT && posePos.x < m_createPosePos.x - m_dialogBody[m_nDialogNum].fShakeWidth))
			{
				//�܂�Ԃ�
				m_bShakeReturn = false;
				//�t�����ɂ���
				m_dialogBody[m_nDialogNum].shakeSpeed *= -1.0f;
				m_dialogBody[m_nDialogNum].shakeMinusSpeed *= -1.0f;
				//�ړ��ʂ�ݒ�
				m_move = m_dialogBody[m_nDialogNum].shakeSpeed;
				//�܂�Ԃ����񐔂�1���₷
				m_nCounterShake++;
			}
		}


		//�w�肵���񐔕��I�����Ƃ�
		if (m_nCounterShake == m_dialogBody[m_nDialogNum].nNumShake * 2)
		{
			if ((m_move.y < 0.0f && posePos.y < m_createPosePos.y) || (m_move.y > 0.0f && posePos.y > m_createPosePos.y))
			{
				posePos.y = m_createPosePos.y;
				facePos.y = m_createFacePos.y;
				m_bShake = false;
				//�ʒu�ݒ�
				m_pPersonPose->SetPos(posePos, m_pPersonPose->GetSize());
				m_pPersonFace->SetPos(facePos, m_pPersonFace->GetSize());
			}
			else if (m_move.x > 0.0f && posePos.x > m_createPosePos.x)
			{
				posePos.x = m_createPosePos.x;
				facePos.x = m_createFacePos.x;
				m_bShake = false;
				//�ʒu�ݒ�
				m_pPersonPose->SetPos(posePos, m_pPersonPose->GetSize());
				m_pPersonFace->SetPos(facePos, m_pPersonFace->GetSize());
			}
		}
	}
}
