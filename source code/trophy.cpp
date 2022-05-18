//=============================================================================
//
// トロフィールー処理 [trophy.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "trophy.h"
#include "manager.h"
#include "object2D.h"
#include "play_data.h"
#include "input_mouse.h"
#include "fade.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TROPHY_ICON_SIZE (150)			// アイコンサイズ
#define TROPHY_ICON_X_FEELING (200)		// アイコンの設置感覚
#define TROPHY_ICON_Y_FEELING (200)		// アイコンの設置感覚
#define TROPHY_COMMENT_X_SIZE (425)		// 説明のサイズ
#define TROPHY_COMMENT_Y_SIZE (70)		// 説明のサイズ
#define TROPHY_X_LINE (6)				// トロフィーの億サイズ
#define TROPHY_Y_LINE (2)				// トロフィーの億サイズ
#define SCREEN_DIVISION_X_COUNT (9)		// 何分割を基本にするか
#define SCREEN_DIVISION_Y_COUNT (3)		// 何分割を基本にするか

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTrophy::CTrophy(PRIORITY priolty) : CObject(priolty)
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CTrophy::~CTrophy()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTrophy::Init(void)
{
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();

	sound->Stop();
	sound->Play(CSound::SOUND_LABEL::TITLE_BGM);
	sound->ControllVoice(CSound::SOUND_LABEL::TITLE_BGM, 1.4f);

	CObject2D *pObject2D[3];
	pObject2D[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Bg.png"));
	pObject2D[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("frame_Trophy.png"));
	pObject2D[2] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f + 70.0f, 0.0f), D3DXVECTOR3(500.0f, 70.0f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy.png"));

	int trophy_count = 0;
	for (int count_y = 0; count_y < TROPHY_Y_LINE; count_y++)
	{
		for (int count_x = 0; count_x < TROPHY_X_LINE; count_x++)
		{
			vector<bool> trophy_flag = CManager::GetPlayData()->GetFlag();

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
				case (int)TROPHY::M_999999:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("trophy_999999.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				default:
					break;
				}
			}
			else
			{
				switch (trophy_count)
				{
				case (int)TROPHY::AIRPLANE:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_airplane_Black.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::FAN:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_fan_Black.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::REDBULL:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_redbull_Black.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::STARRING:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_starring_Black.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::THORN:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_thorn_Black.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::TRAMPOLINE:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_trampoline_Black.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::BANANA:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_banana_Black.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::ROCKET:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_rocket_Black.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::M_1000:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("trophy_question.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::M_5000:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("trophy_question.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::M_10000:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("trophy_question.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				case (int)TROPHY::M_999999:
					m_icon.push_back(CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_x), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * count_y), 0.0f),
						D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
					m_icon[trophy_count]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("trophy_question.png"));
					m_type.push_back((TROPHY)trophy_count);
					break;
				default:
					break;
				}
			}
			trophy_count++;
			if (trophy_count >= (int)TROPHY::MAX)
			{
				break;
			}
		}
	}

	m_buck = CObject2D::Create(D3DXVECTOR3(0.0f + 80.0f, 0.0f + 80.0f, 0.0f), D3DXVECTOR3(80.0f, 80.0f, 70.0f), static_cast<int>(CObject::PRIORITY::UI));
	m_buck->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("arrow.png"));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTrophy::Uninit(void)
{
	Release();
}

//=============================================================================
// 描画処理
//=============================================================================
void CTrophy::Update(void)
{
	CFade *fade;
	CInputMouse *mouse;
	D3DXVECTOR3 button_pos = m_buck->GetPos();
	D3DXVECTOR3 button_size = m_buck->GetSize();
	POINT point;
	HWND hwnd;
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();
	int max_icon = m_icon.size();
	hwnd = CManager::GetWindowHandle();
	fade = CManager::GetFade();
	mouse = CManager::GetInputMouse();
	GetCursorPos(&point);
	ScreenToClient(hwnd, &point);

	for (int icon = 0; icon < max_icon; icon++)
	{
		D3DXVECTOR3 pos = m_icon[icon]->GetPos();
		D3DXVECTOR3 size = m_icon[icon]->GetSize();
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (pos.x - size.x / 2.0f <= point.x &&
			pos.x + size.x / 2.0f >= point.x &&
			pos.y - size.y / 2.0f <= point.y &&
			pos.y + size.y / 2.0f >= point.y)
		{
			col.a = 0.5f;
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
			else if (m_type[icon] == TROPHY::M_999999)
			{
				if (m_letter != nullptr)
				{
					m_letter->Uninit();
				}
				m_icon[icon]->SetCol(col);
				m_letter = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + TROPHY_COMMENT_X_SIZE, 0.0f + TROPHY_COMMENT_Y_SIZE, 0.0f),
					D3DXVECTOR3(TROPHY_COMMENT_X_SIZE, TROPHY_COMMENT_Y_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				m_letter->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("letter_999999.png"));
			}
		}
		else
		{
			col.a = 1.0f;
			m_icon[icon]->SetCol(col);
		}
	}

	if (button_pos.x - button_size.x / 2.0f <= point.x &&
		button_pos.x + button_size.x / 2.0f >= point.x &&
		button_pos.y - button_size.y / 2.0f <= point.y &&
		button_pos.y + button_size.y / 2.0f >= point.y)
	{
		m_buck->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			sound->Play(CSound::SOUND_LABEL::CANSEL_SE);
			sound->ControllVoice(CSound::SOUND_LABEL::CANSEL_SE, 1.2f);
			fade->SetFade(CManager::MODE::TITLE);
		}
	}
	else
	{
		m_buck->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTrophy::Draw(void)
{

}