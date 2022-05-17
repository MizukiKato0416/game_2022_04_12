//=============================================================================
//
// トロフィールー処理 [trophy.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "title.h"
#include "manager.h"
#include "object2D.h"
#include "play_data.h"
#include "input_mouse.h"
#include "fade.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TITLE_TO_RESULT_COUNT		(600)				//リザルトに行くまでの時間
#define TITLE_LOGO_SIZE_X			(366.0f)			//タイトルロゴのサイズX
#define TITLE_LOGO_SIZE_Y			(420.0f)			//タイトルロゴのサイズY
#define TITLE_PRESS_START_SIZE_X	(594.0f)			//PRESS START UIのサイズX
#define TITLE_PRESS_START_SIZE_Y	(84.0f)				//PRESS START UIのサイズY
#define TITLE_PRESS_START_POS_Y		(600.0f)			//PRESS START UIの位置Y

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTitle::CTitle(CObject::PRIORITY Priority):CObject(Priority)
{
	
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	CObject2D *pObject2D[2];
	pObject2D[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Bg.png"));
	pObject2D[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f + 200.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.9, SCREEN_HEIGHT * 0.3, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Title.png"));
	m_click = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - (SCREEN_WIDTH / 3) / 2, SCREEN_HEIGHT - (SCREEN_HEIGHT * 0.10) / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT * 0.10, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	m_click->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Click.png"));
	m_button.push_back(CObject2D::Create(D3DXVECTOR3(0.0f + 300.0f, SCREEN_HEIGHT - 300.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2.2, SCREEN_HEIGHT * 0.15, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
	m_button.push_back(CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, SCREEN_HEIGHT - 300.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2.2, SCREEN_HEIGHT * 0.15, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
	m_button.push_back(CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 150.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2.2, SCREEN_HEIGHT * 0.15, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
	m_button.push_back(CObject2D::Create(D3DXVECTOR3(0.0f + 300.0f, SCREEN_HEIGHT - 300.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2.2, SCREEN_HEIGHT * 0.15, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
	m_button.push_back(CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, SCREEN_HEIGHT - 300.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2.2, SCREEN_HEIGHT * 0.15, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
	m_button.push_back(CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 150.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2.2, SCREEN_HEIGHT * 0.15, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
	m_button[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("frame.png"));
	m_button[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("frame.png"));
	m_button[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("frame.png"));
	m_button[3]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("start.png"));
	m_button[4]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy.png"));
	m_button[5]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial.png"));
	m_fade_flag = true;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	SeletMode();
	Tutorial();
	ColUpdate();
	ResultTimer();
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{
	
}

//=============================================================================
// 選択処理
//=============================================================================
void CTitle::SeletMode(void)
{
	CFade *fade;
	CInputMouse *mouse;
	D3DXVECTOR3 pos[3];
	D3DXVECTOR3 size[3];
	POINT point;
	HWND hwnd;
	pos[0] = m_button[0]->GetPos();
	size[0] = m_button[0]->GetSize();
	pos[1] = m_button[1]->GetPos();
	size[1] = m_button[1]->GetSize();
	pos[2] = m_button[2]->GetPos();
	size[2] = m_button[2]->GetSize();
	hwnd = CManager::GetInstance()->GetWindowHandle();
	fade = CManager::GetInstance()->GetFade();
	mouse = CManager::GetInstance()->GetInputMouse();
	GetCursorPos(&point);
	ScreenToClient(hwnd, &point);

	if (pos[0].x - size[0].x / 2.0f <= point.x &&
		pos[0].x + size[0].x / 2.0f >= point.x &&
		pos[0].y - size[0].y / 2.0f <= point.y &&
		pos[0].y + size[0].y / 2.0f >= point.y &&
		m_tutorial_flag == false)
	{
		m_button[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_button[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true && fade->GetFade() == CFade::FADE_NONE)
		{
			fade->SetFade(CManager::MODE::GAME01);
		}
	}
	else
	{
		m_button[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_button[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (pos[1].x - size[1].x / 2.0f <= point.x &&
		pos[1].x + size[1].x / 2.0f >= point.x &&
		pos[1].y - size[1].y / 2.0f <= point.y &&
		pos[1].y + size[1].y / 2.0f >= point.y &&
		m_tutorial_flag == false)
	{
		m_button[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_button[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true && fade->GetFade() == CFade::FADE_NONE)
		{
			fade->SetFade(CManager::MODE::TROPHY);
		}
	}
	else
	{
		m_button[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_button[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (pos[2].x - size[2].x / 2.0f <= point.x &&
		pos[2].x + size[2].x / 2.0f >= point.x &&
		pos[2].y - size[2].y / 2.0f <= point.y &&
		pos[2].y + size[2].y / 2.0f >= point.y &&
		m_tutorial_flag == false)
	{
		m_button[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_button[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			for (int count_tutorial = 0; count_tutorial < 5; count_tutorial++)
			{
				m_tutorial.push_back(CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
			}
			m_tutorial.push_back(CObject2D::Create(D3DXVECTOR3(0.0f + 80.0f, 0.0f + 50.0f, 0.0f), D3DXVECTOR3(80.0f, 80.0f, 70.0f), static_cast<int>(CObject::PRIORITY::UI)));
			m_tutorial[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial_up.png"));
			m_tutorial[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial_arrow.png"));
			m_tutorial[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial_picture_left.png"));
			m_tutorial[3]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial_picture_light.png"));
			m_tutorial[4]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial_under.png"));
			m_tutorial[5]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("arrow.png"));
			m_tutorial_flag = true;
		}
	}
	else
	{
		m_button[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_button[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

//=============================================================================
// チュートリアル
//=============================================================================
void CTitle::Tutorial(void)
{
	CInputMouse *mouse;
	POINT point;
	HWND hwnd;
	hwnd = CManager::GetInstance()->GetWindowHandle();
	mouse = CManager::GetInstance()->GetInputMouse();
	GetCursorPos(&point);
	ScreenToClient(hwnd, &point);

	if (m_tutorial_flag == true)
	{
		D3DXVECTOR3 pos_buck;
		D3DXVECTOR3 size_buck;

		pos_buck = m_tutorial[5]->GetPos();
		size_buck = m_tutorial[5]->GetSize();

		if (pos_buck.x - size_buck.x / 2.0f <= point.x &&
			pos_buck.x + size_buck.x / 2.0f >= point.x &&
			pos_buck.y - size_buck.y / 2.0f <= point.y &&
			pos_buck.y + size_buck.y / 2.0f >= point.y)
		{
			m_tutorial[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
			{
				int tutorial_size = m_tutorial.size();
				for (int count_tutorial = tutorial_size - 1; count_tutorial >= 0; count_tutorial--)
				{
					m_tutorial[count_tutorial]->Uninit();
					m_tutorial[count_tutorial] = nullptr;
					m_tutorial.pop_back();
				}
				m_tutorial_flag = false;
			}
		}
		else
		{
			m_tutorial[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}

//=============================================================================
// カラー変更
//=============================================================================
void CTitle::ColUpdate(void)
{
	D3DXCOLOR col_click = m_click->GetCol();

	if (col_click.a >= 1.0f)
	{
		m_fade_flag = true;
	}
	else if (col_click.a <= 0.0f)
	{
		m_fade_flag = false;
	}

	if (m_fade_flag == true)
	{
		col_click.a -= 0.01f;
		m_click->SetCol(col_click);
	}
	else
	{
		col_click.a += 0.01f;
		m_click->SetCol(col_click);
	}
}

//=============================================================================
// リザルトタイマー
//=============================================================================
void CTitle::ResultTimer(void)
{
	CFade *fade;
	CInputMouse *mouse;
	fade = CManager::GetInstance()->GetFade();
	mouse = CManager::GetInstance()->GetInputMouse();

	m_result_timer++;
	if (m_result_timer >= 600 &&
		mouse->GetMouseState().lX == 0 &&
		mouse->GetMouseState().lY == 0)
	{
		m_result_timer = 0;
		if (fade->GetFade() == CFade::FADE_NONE)
		{
			fade->SetFade(CManager::MODE::RESULT);
		}
	}
}