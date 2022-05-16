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

//=============================================================================
// マクロ定義
//=============================================================================
#define TROPHY_ICON_SIZE (150)			// アイコンサイズ
#define TROPHY_ICON_X_FEELING (200)		// アイコンの設置感覚
#define TROPHY_ICON_Y_FEELING (200)		// アイコンの設置感覚
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
	CObject2D *pObject2D[3];
	pObject2D[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Bg.png"));
	pObject2D[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("frame_Trophy.png"));
	pObject2D[2] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f + 70.0f, 0.0f), D3DXVECTOR3(500.0f, 70.0f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy.png"));

	int pos_y = 0;
	for (int count_trophy_size = 0; count_trophy_size < (int)TROPHY::MAX; count_trophy_size++)
	{
		vector<bool> trophy_flag = CManager::GetPlayData()->GetFlag();

		if (trophy_flag[count_trophy_size])
		{
			CObject2D *pIcon;

			switch (count_trophy_size)
			{
			case (int)TROPHY::AIRPLANE:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_Airplane.png"));
				break;
			case (int)TROPHY::FAN:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_fan.png"));
				break;
			case (int)TROPHY::REDBULL:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_redbull.png"));
				break;
			case (int)TROPHY::STARRING:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_starring.png"));
				break;
			case (int)TROPHY::THORN:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_thorn.png"));
				break;
			case (int)TROPHY::TRAMPOLINE:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_trampoline.png"));
				break;
			case (int)TROPHY::BANANA:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_banana.png"));
				break;
			case (int)TROPHY::ROCKET:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_rocket.png"));
				break;
			case (int)TROPHY::M_1000:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_1000.png"));
				break;
			case (int)TROPHY::M_5000:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_5000.png"));
				break;
			case (int)TROPHY::M_10000:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_10000.png"));
				break;
			default:
				break;
			}
		}
		else
		{
			CObject2D *pIcon;

			switch (count_trophy_size)
			{
			case (int)TROPHY::AIRPLANE:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_airplane_Black.png"));
				break;
			case (int)TROPHY::FAN:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_fan_Black.png"));
				break;
			case (int)TROPHY::REDBULL:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_redbull_Black.png"));
				break;
			case (int)TROPHY::STARRING:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_starring_Black.png"));
				break;
			case (int)TROPHY::THORN:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_thorn_Black.png"));
				break;
			case (int)TROPHY::TRAMPOLINE:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_trampoline_Black.png"));
				break;
			case (int)TROPHY::BANANA:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_banana_Black.png"));
				break;
			case (int)TROPHY::ROCKET:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_rocket_Black.png"));
				break;
			case (int)TROPHY::M_1000:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_1000_Black.png"));
				break;
			case (int)TROPHY::M_5000:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_5000_Black.png"));
				break;
			case (int)TROPHY::M_10000:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), (SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT) + (TROPHY_ICON_Y_FEELING * pos_y), 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy_10000_Black.png"));
				break;
			default:
				break;
			}
		}
		if (count_trophy_size >= (6 * (pos_y + 1)))
		{
			pos_y++;
		}
	}

	m_buck = CObject2D::Create(D3DXVECTOR3(0.0f + 80.0f, 0.0f + 80.0f, 0.0f), D3DXVECTOR3(80.0f, 80.0f, 70.0f), static_cast<int>(CObject::PRIORITY::UI));
	m_buck->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("arrow.png"));

	return S_OK;
}

//=============================================================================
// 更新処理
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
	D3DXVECTOR3 pos = m_buck->GetPos();
	D3DXVECTOR3 size = m_buck->GetSize();
	POINT point;
	HWND hwnd;
	hwnd = CManager::GetWindowHandle();
	fade = CManager::GetFade();
	mouse = CManager::GetInputMouse();
	GetCursorPos(&point);
	ScreenToClient(hwnd, &point);

	if (pos.x - size.x / 2.0f <= point.x &&
		pos.x + size.x / 2.0f >= point.x &&
		pos.y - size.y / 2.0f <= point.y &&
		pos.y + size.y / 2.0f >= point.y)
	{
		m_buck->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
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