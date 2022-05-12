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
#include "happening.h"
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
	pObject2D[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_BG"));
	pObject2D[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_TROPHY_FRAME"));
	pObject2D[2] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f + 70.0f, 0.0f), D3DXVECTOR3(500.0f, 70.0f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_TROPHY"));

	for (int count_trophy_size = 0; count_trophy_size < (int)CHappenig::HAPPENING_TYPE::MAX - 1; count_trophy_size++)
	{
		vector<bool> trophy_flag = CManager::GetPlayData()->GetFlag();

		if (trophy_flag[count_trophy_size])
		{
			CObject2D *pIcon;

			switch (count_trophy_size)
			{
			case 0:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT, 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_ICON_SIRPLANE_00"));
				break;
			case 1:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT, 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_ICON_FAN_00"));
				break;
			case 2:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT, 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_ICON_REDBULL_00"));
				break;
			case 3:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT, 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_ICON_STARRING_00"));
				break;
			case 4:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT, 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_ICON_THORN_00"));
				break;
			case 5:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT, 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_ICON_TRAMPOLINE_00"));
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
			case 0:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT, 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_ICON_SIRPLANE_01"));
				break;
			case 1:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT, 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_ICON_FAN_01"));
				break;
			case 2:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT, 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_ICON_REDBULL_01"));
				break;
			case 3:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT, 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_ICON_STARRING_01"));
				break;
			case 4:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT, 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_ICON_THORN_01"));
				break;
			case 5:
				pIcon = CObject2D::Create(D3DXVECTOR3((SCREEN_WIDTH / (float)SCREEN_DIVISION_X_COUNT) + (TROPHY_ICON_X_FEELING * count_trophy_size), SCREEN_HEIGHT / (float)SCREEN_DIVISION_Y_COUNT, 0.0f),
					D3DXVECTOR3(TROPHY_ICON_SIZE, TROPHY_ICON_SIZE, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
				pIcon->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_ICON_TRAMPOLINE_01"));
				break;
			default:
				break;
			}
		}
	}

	m_buck = CObject2D::Create(D3DXVECTOR3(0.0f + 80.0f, 0.0f + 80.0f, 0.0f), D3DXVECTOR3(80.0f, 80.0f, 70.0f), static_cast<int>(CObject::PRIORITY::UI));
	m_buck->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_BUCK"));

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CTrophy::Uninit(void)
{
	
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