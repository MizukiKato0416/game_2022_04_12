//=============================================================================
//
// �g���t�B�[���[���� [trophy.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "trophy.h"
#include "manager.h"
#include "object2D.h"
#include "play_data.h"
#include "input_mouse.h"
#include "fade.h"
#include "sound.h"
#include "history_letter.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TROPHY_ICON_SIZE (100)			// �A�C�R���T�C�Y
#define TROPHY_ICON_X_FEELING (200)		// �A�C�R���̐ݒu���o
#define TROPHY_ICON_Y_FEELING (120)		// �A�C�R���̐ݒu���o
#define TROPHY_COMMENT_X_SIZE (425)		// �����̃T�C�Y
#define TROPHY_COMMENT_Y_SIZE (70)		// �����̃T�C�Y
#define TROPHY_X_LINE (6)				// �g���t�B�[�̉��T�C�Y
#define TROPHY_Y_LINE (4)				// �g���t�B�[�̉��T�C�Y
#define SCREEN_DIVISION_X_COUNT (9)		// ����������{�ɂ��邩
#define SCREEN_DIVISION_Y_COUNT (3)		// ����������{�ɂ��邩
#define MAX_ROOM_UI_FACTOR (3)			// �g���t�B�[���[���̓����Ȃ�UI��

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTrophy::CTrophy(PRIORITY priolty) : CObject(priolty)
{
	m_count_get_trophy = 0;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CTrophy::~CTrophy()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTrophy::Init(void)
{
	// �T�E���h�N���X���擾
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();

	// �O�̃V�[���ł̉����~�߂ĕʂ̉����o��
	sound->Stop();
	sound->Play(CSound::SOUND_LABEL::TROPHY_BGM);
	sound->ControllVoice(CSound::SOUND_LABEL::TROPHY_BGM, 1.4f);

	// �g���t�B�[���[���̐���
	CObject2D *pObject2D[MAX_ROOM_UI_FACTOR];
	pObject2D[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Bg.png"));
	pObject2D[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("frame_Trophy.png"));
	pObject2D[2] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f + 70.0f, 0.0f), D3DXVECTOR3(500.0f, 70.0f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy.png"));

	// �g���t�B�[�t���O�̎擾
	vector<bool> trophy_flag = CManager::GetPlayData()->GetFlag();
	// �g���t�B�[�̃T�C�Y���擾
	int size = trophy_flag.size();
	for (int count_flag = 0; count_flag < size - 1; count_flag++)
	{
		// ����Ă�������Ȃ�
		if (trophy_flag[count_flag] == true)
		{
			// ����Ă鐔��+
			m_count_get_trophy++;
		}
	}
	// �S������Ă���
	if (m_count_get_trophy == size - 1)
	{
		// �t���O�������ĂȂ�������
		if (trophy_flag[(int)TROPHY::COMPLETE] == false)
		{
			// �R���v���[�g�t���O�𗧂Ă�
			trophy_flag[(int)TROPHY::COMPLETE] = true;

			// �t���O��ۑ�
			CManager::GetPlayData()->SetFlag(trophy_flag);
			CHistory::Create(CTrophy::TROPHY::COMPLETE);
		}
	}

	// �g���t�B�[����ׂ�
	int trophy_count = 0;
	for (int count_y = 0; count_y < TROPHY_Y_LINE; count_y++)
	{
		for (int count_x = 0; count_x < TROPHY_X_LINE; count_x++)
		{
			// �t���O�������Ă���
			if (trophy_flag[trophy_count])
			{
				switch (trophy_count)
				{
				case (int)TROPHY::AIRPLANE:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_Airplane.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::FAN:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_fan.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::REDBULL:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_redbull.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::STARRING:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_starring.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::THORN:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_thorn.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::TRAMPOLINE:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_trampoline.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::BANANA:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_banana.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::ROCKET:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_rocket.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::M_1000:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_1000.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::M_5000:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_5000.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::M_10000:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_10000.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::MEASUREMENT_IMPOSSIBLE:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_error.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::EVENING:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_evning.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::NIGHT:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_night.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::GIRL:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_rokiko.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::HARD:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("hard.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::GROUND:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_ground.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::PLAY_00:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_frame.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::PLAY_05:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("play_5.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::PLAY_10:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("play_10.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::ENDROLL:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("trophy_end.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::ROCKY_ANGRY:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("trophy_rokki-.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::KIYO:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_kiyo.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::COMPLETE:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("trophy_trophy.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				default:
					break;
				}
			}
			// �t���O�������ĂȂ�������
			else
			{
				m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
				m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("trophy_question.png"));
				m_type.push_back((TROPHY)trophy_count);
			}
			// �g���t�B�[�J�E���g�̉��Z
			trophy_count++;
			// �g���t�B�[�J�E���g���Ō�܂ōs������
			if (trophy_count >= (int)TROPHY::MAX)
			{
				// �ʂ���
				break;
			}
		}
	}

	// �߂�{�^���̐���
	m_buck = CObject2D::Create(D3DXVECTOR3(0.0f + 80.0f, 0.0f + 80.0f, 0.0f), D3DXVECTOR3(80.0f, 80.0f, 70.0f), static_cast<int>(CObject::PRIORITY::UI));
	m_buck->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("arrow.png"));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTrophy::Uninit(void)
{
	Release();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTrophy::Update(void)
{
	CFade *fade;	// �t�F�[�h�N���X
	CInputMouse *mouse;	// �}�E�X�N���X
	D3DXVECTOR3 button_pos = m_buck->GetPos();	// �߂�{�^����pos
	D3DXVECTOR3 button_size = m_buck->GetSize();// �߂�{�^����size
	POINT point;	// �}�E�X�̈ʒu
	HWND hwnd;	// �E�B���h�E�n���h��
	CSound *sound;	// �T�E���h�N���X
	vector<bool> trophy_flag = CManager::GetPlayData()->GetFlag();	// �g���t�B�[�t���O
	int max_icon = m_icon.size();	//�g���t�B�[�A�C�R���̃T�C�Y
	sound = CManager::GetInstance()->GetSound();	// �T�E���h�N���X�̎擾
	hwnd = CManager::GetWindowHandle();	// �E�B���h�E�n���h���̎擾
	fade = CManager::GetFade();	// �t�F�[�h�N���X�̎擾
	mouse = CManager::GetInputMouse();	// �}�E�X�N���X�̎擾
	GetCursorPos(&point);	// �}�E�X�ʒu�̎擾
	ScreenToClient(hwnd, &point);	// �X�N���[�����W���N���C�A���g���W�ɕϊ�

	for (int icon = 0; icon < max_icon; icon++)
	{
		D3DXVECTOR3 pos = m_icon[icon]->GetPos();	// �A�C�R����pos
		D3DXVECTOR3 size = m_icon[icon]->GetSize();	// �A�C�R����size
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �|���S���̃J���[

		// �}�E�X���g���t�B�[�A�C�R���ɐG��Ă�����
		if (pos.x - size.x / 2.0f <= point.x &&
			pos.x + size.x / 2.0f >= point.x &&
			pos.y - size.y / 2.0f <= point.y &&
			pos.y + size.y / 2.0f >= point.y)
		{
			// ���l�𔖂�
			col.a = 0.5f;
			// �A�C�R���ɍ������|���S���̐���
			if (m_type[icon] == TROPHY::AIRPLANE)
			{
				if (m_letter != nullptr)
				{
					m_letter->Uninit();
				}
				m_icon[icon]->SetCol(col);
				m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
					D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_Airplane.png"));
			}
			else if (m_type[icon] == TROPHY::FAN)
			{
				if (m_letter != nullptr)
				{
					m_letter->Uninit();
				}
				m_icon[icon]->SetCol(col);
				m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
					D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_fan.png"));
			}
			else if (m_type[icon] == TROPHY::TRAMPOLINE)
			{
				if (m_letter != nullptr)
				{
					m_letter->Uninit();
				}
				m_icon[icon]->SetCol(col);
				m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
					D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_trampoline.png"));
			}
			else if (m_type[icon] == TROPHY::BANANA)
			{
				if (m_letter != nullptr)
				{
					m_letter->Uninit();
				}
				m_icon[icon]->SetCol(col);
				m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
					D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_banana.png"));
			}
			else if (m_type[icon] == TROPHY::STARRING)
			{
				if (m_letter != nullptr)
				{
					m_letter->Uninit();
				}
				m_icon[icon]->SetCol(col);
				m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
					D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_sterling.png"));
			}
			else if (m_type[icon] == TROPHY::ROCKET)
			{
				if (m_letter != nullptr)
				{
					m_letter->Uninit();
				}
				m_icon[icon]->SetCol(col);
				m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
					D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_rocket.png"));
			}
			else if (m_type[icon] == TROPHY::REDBULL)
			{
				if (m_letter != nullptr)
				{
					m_letter->Uninit();
				}
				m_icon[icon]->SetCol(col);
				m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
					D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_redbull.png"));
			}
			else if (m_type[icon] == TROPHY::THORN)
			{
				if (m_letter != nullptr)
				{
					m_letter->Uninit();
				}
				m_icon[icon]->SetCol(col);
				m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
					D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_thorn.png"));
			}
			else if (m_type[icon] == TROPHY::M_1000)
			{
				if (m_letter != nullptr)
				{
					m_letter->Uninit();
				}
				m_icon[icon]->SetCol(col);
				m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
					D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_1000.png"));
			}
			else if (m_type[icon] == TROPHY::M_5000)
			{
				if (m_letter != nullptr)
				{
					m_letter->Uninit();
				}
				m_icon[icon]->SetCol(col);
				m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
					D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_5000.png"));
			}
			else if (m_type[icon] == TROPHY::M_10000)
			{
				if (m_letter != nullptr)
				{
					m_letter->Uninit();
				}
				m_icon[icon]->SetCol(col);
				m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
					D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_10000.png"));
			}
			else if (m_type[icon] == TROPHY::MEASUREMENT_IMPOSSIBLE)
			{
				if (m_letter != nullptr)
				{
					m_letter->Uninit();
				}
				m_icon[icon]->SetCol(col);
				m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
					D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("ettererror.png"));
			}
			else if (m_type[icon] == TROPHY::EVENING)
			{
				if (trophy_flag[(int)m_type[icon]] == true)
				{
					if (m_letter != nullptr)
					{
						m_letter->Uninit();
					}
					m_icon[icon]->SetCol(col);
					m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
						D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
					m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("password_evening.png"));
				}
				else if (trophy_flag[(int)m_type[icon]] == false)
				{
					if (m_letter != nullptr)
					{
						m_letter->Uninit();
					}
					m_icon[icon]->SetCol(col);
					m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
						D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
					m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_play_evening.png"));
				}
			}
			else if (m_type[icon] == TROPHY::NIGHT)
			{
				if (trophy_flag[(int)m_type[icon]] == true)
				{
					if (m_letter != nullptr)
					{
						m_letter->Uninit();
					}
					m_icon[icon]->SetCol(col);
					m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
						D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
					m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("password_night.png"));
				}
				else if (trophy_flag[(int)m_type[icon]] == false)
				{
					if (m_letter != nullptr)
					{
						m_letter->Uninit();
					}
					m_icon[icon]->SetCol(col);
					m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
						D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
					m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_play_night.png"));
				}
			}
			else if (m_type[icon] == TROPHY::GIRL)
			{
				if (trophy_flag[(int)m_type[icon]] == true)
				{
					if (m_letter != nullptr)
					{
						m_letter->Uninit();
					}
					m_icon[icon]->SetCol(col);
					m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
						D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
					m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("password_695.png"));
				}
				else if (trophy_flag[(int)m_type[icon]] == false)
				{
					if (m_letter != nullptr)
					{
						m_letter->Uninit();
					}
					m_icon[icon]->SetCol(col);
					m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
						D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
					m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_play_rokiko.png"));
				}
			}
			else if (m_type[icon] == TROPHY::HARD)
			{
				if (m_letter != nullptr)
				{
					m_letter->Uninit();
				}
				m_icon[icon]->SetCol(col);
				m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
					D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("play_hard.png"));
			}
			else if (m_type[icon] == TROPHY::GROUND)
			{
				if (trophy_flag[(int)m_type[icon]] == true)
				{
					if (m_letter != nullptr)
					{
						m_letter->Uninit();
					}
					m_icon[icon]->SetCol(col);
					m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
						D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
					m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("password_ground.png"));
				}
				else if (trophy_flag[(int)m_type[icon]] == false)
				{
					if (m_letter != nullptr)
					{
						m_letter->Uninit();
					}
					m_icon[icon]->SetCol(col);
					m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
						D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
					m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_play_ground.png"));
				}
			}
			else if (m_type[icon] == TROPHY::PLAY_00)
			{
				if (m_letter != nullptr)
				{
					m_letter->Uninit();
				}
				m_icon[icon]->SetCol(col);
				m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
					D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("fastplay.png"));
			}
			else if (m_type[icon] == TROPHY::PLAY_05)
			{
				if (m_letter != nullptr)
				{
					m_letter->Uninit();
				}
				m_icon[icon]->SetCol(col);
				m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
					D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("lettr_play_5.png"));
			}
			else if (m_type[icon] == TROPHY::PLAY_10)
			{
				if (m_letter != nullptr)
				{
					m_letter->Uninit();
				}
				m_icon[icon]->SetCol(col);
				m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
					D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_play_10.png"));
			}
			else if (m_type[icon] == TROPHY::ENDROLL)
			{
				if (trophy_flag[(int)m_type[icon]] == true)
				{
					if (m_letter != nullptr)
					{
						m_letter->Uninit();
					}
					m_icon[icon]->SetCol(col);
					m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
						D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
					m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("password_staffroll.png"));
				}
				else if (trophy_flag[(int)m_type[icon]] == false)
				{
					if (m_letter != nullptr)
					{
						m_letter->Uninit();
					}
					m_icon[icon]->SetCol(col);
					m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
						D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
					m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_staffroll.png"));
				}
			}
			else if (m_type[icon] == TROPHY::ROCKY_ANGRY)
			{
				if (trophy_flag[(int)m_type[icon]] == true)
				{
					if (m_letter != nullptr)
					{
						m_letter->Uninit();
					}
					m_icon[icon]->SetCol(col);
					m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
						D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
					m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_20click.png"));
				}
				else if (trophy_flag[(int)m_type[icon]] == false)
				{
					if (m_letter != nullptr)
					{
						m_letter->Uninit();
					}
					m_icon[icon]->SetCol(col);
					m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
						D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
					m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_rocky.png"));
				}
			}
			else if (m_type[icon] == TROPHY::KIYO)
			{
				if (trophy_flag[(int)m_type[icon]] == true)
				{
					if (m_letter != nullptr)
					{
						m_letter->Uninit();
					}
					m_icon[icon]->SetCol(col);
					m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
						D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
					m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("password_kiyo.png"));
				}
				else if (trophy_flag[(int)m_type[icon]] == false)
				{
					if (m_letter != nullptr)
					{
						m_letter->Uninit();
					}
					m_icon[icon]->SetCol(col);
					m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
						D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
					m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_kiyo.png"));
				}
			}
			else if (m_type[icon] == TROPHY::COMPLETE)
			{
				if (m_letter != nullptr)
				{
					m_letter->Uninit();
				}
				m_icon[icon]->SetCol(col);
				m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
					D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_complete.png"));
			}
		}
		// �}�E�X���G��ĂȂ�������
		else
		{
			// ���l��Z��
			col.a = 1.0f;
			m_icon[icon]->SetCol(col);
		}
	}

	// �߂�{�^���ɐG��Ă�����
	if (button_pos.x - button_size.x / 2.0f <= point.x &&
		button_pos.x + button_size.x / 2.0f >= point.x &&
		button_pos.y - button_size.y / 2.0f <= point.y &&
		button_pos.y + button_size.y / 2.0f >= point.y)
	{
		// �߂�{�^���𔖂�
		m_buck->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		// ���N���b�N���Ă�����
		if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			// ����炵�ă^�C�g����
			sound->ControllVoice(CSound::SOUND_LABEL::CANSEL_SE, 1.2f);
			sound->Play(CSound::SOUND_LABEL::CANSEL_SE);
			fade->SetFade(CManager::MODE::TITLE);
		}
	}
	// �G��Ă��Ȃ�������
	else
	{
		// �߂�{�^����Z��
		m_buck->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTrophy::Draw(void)
{

}