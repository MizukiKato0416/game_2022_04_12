//================================================
//��b�̏���
//Author:KatoMizuki
//================================================
#include "object.h"
#include "dialog.h"
#include "letter.h"
#include "sound.h"
#include "manager.h"
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

	char cString[DIALOG_MAX_STRING];
	FILE *file;
	file = fopen("data/dialog_ss.txt", "r");

	if (file != NULL)
	{
		//��s���ۑ�
		while (fgets(cString, DIALOG_MAX_STRING, file) != NULL)
		{
			//BEGIN_DIALOG�Ə�����Ă�����
			if (strncmp("BEGIN_DIALOG\n", cString, 14) == 0)
			{
				//������
				DIALOG_BODY dialogBody;
				dialogBody.nPersonPose = 0;
				dialogBody.nPersonFace = 0;
				dialogBody.nFrame = 0;

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

				//�����𑝂₷
				m_nMaxDialog++;
			}
			else if (strncmp("END_SCRIPT", cString, 11) == 0)
			{//END_SCRIPT�Ə�����Ă�����
				break;
			}
		}
	}
	fclose(file);
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
	if (m_bCreateFinish == true)
	{
		//�����ȉ���������
		if (m_nDialogNum < m_nMaxDialog)
		{
			//�Z���t�̐����ƑS�����\�����ꂽ���ǂ������擾
			m_bDialogFinish = Dialog(m_nDialogNum);
		}
		//�S�����\�����ꂽ��
		if (m_bDialogFinish)
		{
			if (m_pNextDialogUI == nullptr)
			{
				//���̃Z���t�ɍs��UI�𐶐�
				m_pNextDialogUI = CNextDialogUI::Create(D3DXVECTOR3(NEXT_DILOG_UI_POS_X, NEXT_DILOG_UI_POS_Y, 0.0f),
					                                    D3DXVECTOR3(NEXT_DILOG_UI_SIZE, NEXT_DILOG_UI_SIZE, 0.0f));
				m_pNextDialogUI->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("click_ui.png"));
				//�S����\��������Ԃɂ���
				m_bDialogFinish = true;
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

					//�t�F�[�h�擾����
					CFade *pFade;
					pFade = CManager::GetInstance()->GetFade();

					if (pFade->GetFade() == CFade::FADE_NONE)
					{
						//�^�C�g���V�[���ɑJ��
						pFade->SetFade(CManager::MODE::TITLE);

						//�g���t�B�[�̃t���O��Ԃ��擾
						vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
						//�g���t�B�[���擾�������Ƃ��Ȃ�������
						if (flag[(int)CTrophy::TROPHY::ROCKY_ANGRY] == false)
						{
							//�擾������
							flag[(int)CTrophy::TROPHY::ROCKY_ANGRY] = true;
							//�t���O�𗧂Ă�
							CManager::GetInstance()->GetPlayData()->SetFlag(flag);
							CHistory::Create(CTrophy::TROPHY::ROCKY_ANGRY);
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
CDialog *CDialog::Create(void)
{
	//�C���X�^���X�̐���
	CDialog *pDialog = nullptr;
	if (pDialog == nullptr)
	{
		pDialog = new CDialog();
		if (pDialog != nullptr)
		{
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
	wchar_t cReturn[] = L"#";
	int nDialogSize = m_dialog[nCntDialog].size();

	if (m_nDialogDelay < nDialogSize)
	{
		//�t���[���̃J�E���^�[�����Z
		m_nCountFrame++;
		//����̒l���傫���Ȃ�����
		if (m_nCountFrame > m_nLetterCreateCounter)
		{
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
			{
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
	{
		return true;
	}
	return false;
}

//================================================
//�Z���t�j������
//================================================
void CDialog::UninitDialog(void)
{
	m_nDialogCntX = 0;
	m_nDialogCntY = 0;
	m_nDialogDelay = 0;

	int nSize = m_pLetter.size();

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
	m_bCreateFinish = true;
}
