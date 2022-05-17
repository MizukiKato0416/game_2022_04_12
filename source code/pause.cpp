//================================================
//ポーズ処理
//Authore:加藤瑞葵
//================================================
#include "renderer.h"
#include "pause.h"
#include "manager.h"
#include "texture.h"
#include "object2D.h"
#include "input_mouse.h"
#include "input_keyboard.h"
#include "pause.h"
#include "fade.h"
#include "game01.h"

//================================================
//マクロ定義
//================================================
#define PAUSE_START_POS_Y		(340.0f)		//STARTUIの位置Y
#define PAUSE_EXIT_POS_Y		(460.0f)		//EXITUIの位置Y

//================================================
//静的メンバ変数宣言
//================================================
bool CPause::m_bPause = false;			//ポーズ画面かどうか

//================================================
//デフォルトコンストラクタ
//================================================
CPause::CPause(CObject::PRIORITY Priority) :CObject(Priority)
{
	memset(&m_apObject2D, NULL, sizeof(m_apObject2D));
	m_bPause = false;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CPause::~CPause()
{

}

//================================================
//初期化処理
//================================================
HRESULT CPause::Init(void)
{
	m_bPause = false;
	m_pPauseButton = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - (250.0f / 2), 0.0f + (75.0f / 2), 0.0f),
									   D3DXVECTOR3(250.0f, 75.0f, 0.0f), static_cast<int>(CObject::PRIORITY::PAUSE));
	m_pPauseButton->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("pause_button.png"));

	return S_OK;
}

//================================================
//終了処理
//================================================
void CPause::Uninit(void)
{
	m_bPause = false;
	
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CPause::Update(void)
{
	D3DXVECTOR3 button_pos = m_pPauseButton->GetPos();
	D3DXVECTOR3 button_size = m_pPauseButton->GetSize();
	POINT point;
	HWND hwnd;
	CInputMouse *mouse;
	hwnd = CManager::GetWindowHandle();
	GetCursorPos(&point);
	ScreenToClient(hwnd, &point);
	mouse = CManager::GetInstance()->GetInputMouse();

	//フェード取得処理
	CFade *pFade;
	pFade = CManager::GetFade();

	//Pキーかスタートボタンでポーズ
	if (button_pos.x - button_size.x / 2.0f <= point.x &&
		button_pos.x + button_size.x / 2.0f >= point.x &&
		button_pos.y - button_size.y / 2.0f <= point.y &&
		button_pos.y + button_size.y / 2.0f >= point.y)
	{
		m_pPauseButton->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			if (m_bPause == false)
			{
				//ゲーム中にポーズのフラグが立っていなかったら
				if (CManager::GetInstance()->GetGame01()->GetPause() == false)
				{
					//フラグを立てる
					CManager::GetInstance()->GetGame01()->SetPause(true);
				}

				m_bPause = true;

				//フレームを作成
				m_pObject2D[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::PAUSE));
				m_pObject2D[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("pause_frame.png"));

				m_pObject2D[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 0.0f + 70.0f, 0.0f),
					D3DXVECTOR3(500.0f, 70.0f, 0.0f), static_cast<int>(CObject::PRIORITY::PAUSE));
				m_pObject2D[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("pause.png"));

				//UIを作成
				m_apObject2D[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, (SCREEN_HEIGHT / 2.0f) - 100.0f, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 5.0f, 0.0f), static_cast<int>(CObject::PRIORITY::PAUSE));
				m_apObject2D[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("start.png"));

				m_apObject2D[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, (SCREEN_HEIGHT / 2.0f) + 100.0f, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH / 1.3f, SCREEN_HEIGHT / 3.8f, 0.0f), static_cast<int>(CObject::PRIORITY::PAUSE));
				m_apObject2D[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("exit.png"));
			}
			else
			{
				//ゲーム中にポーズのフラグが立っていなかったら
				if (CManager::GetInstance()->GetGame01()->GetPause() == false)
				{
					//フラグを立てる
					CManager::GetInstance()->GetGame01()->SetPause(true);
				}

				m_bPause = false;

				m_pObject2D[0]->Uninit();
				m_pObject2D[0] = nullptr;
				m_pObject2D[1]->Uninit();
				m_pObject2D[1] = nullptr;

				for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
				{
					m_apObject2D[nCnt]->Uninit();
					m_apObject2D[nCnt] = nullptr;
				}
			}
		}
	}
	else
	{
		m_pPauseButton->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (m_bPause == true)
	{
		for (int count = 0; count < SELECT_MAX; count++)
		{
			if (m_apObject2D[count] != nullptr)
			{
				D3DXVECTOR3 pos = m_apObject2D[count]->GetPos();
				D3DXVECTOR3 size = m_apObject2D[count]->GetSize();

				if (pos.x - size.x / 2.0f <= point.x &&
					pos.x + size.x / 2.0f >= point.x &&
					pos.y - size.y / 2.0f <= point.y &&
					pos.y + size.y / 2.0f >= point.y)
				{
					m_apObject2D[count]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
					if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
					{
						//ゲーム中にポーズのフラグが立っていなかったら
						if (CManager::GetInstance()->GetGame01()->GetPause() == false)
						{
							//フラグを立てる
							CManager::GetInstance()->GetGame01()->SetPause(true);
						}

						m_bPause = false;
						switch (count)
						{
						case SELECT_START:
							m_pObject2D[0]->Uninit();
							m_pObject2D[0] = nullptr;
							m_pObject2D[1]->Uninit();
							m_pObject2D[1] = nullptr;

							for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
							{
								m_apObject2D[nCnt]->Uninit();
								m_apObject2D[nCnt] = nullptr;
							}
							break;
						case SELECT_EXIT:
							if (pFade->GetFade() == CFade::FADE_NONE)
							{
								pFade->SetFade(CManager::MODE::TITLE);
							}
							break;
						default:
							break;
						}
					}
				}
				else
				{
					m_apObject2D[count]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}
		}
	}
}

//================================================
//描画処理
//================================================
void CPause::Draw(void)
{

}

//================================================
//ポーズ取得処理
//================================================
bool CPause::GetPause(void)
{
	return m_bPause;
}

//================================================
//ポーズ設定処理
//================================================
bool CPause::SetPause(const bool &bPause)
{
	m_bPause = bPause;
	return m_bPause;
}
//================================================
//生成処理
//================================================
CPause* CPause::Create(void)
{
	//インスタンスの生成
	CPause *pPause = nullptr;
	if (pPause == nullptr)
	{
		pPause = new CPause;
		if (pPause != nullptr)
		{
			pPause->Init();
		}
	}
	return pPause;
}