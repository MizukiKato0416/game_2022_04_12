//================================================
//メニュー処理
//Authore:加藤瑞葵
//================================================
#include "renderer.h"
#include "menu.h"
#include "manager.h"
#include "texture.h"
#include "object2D.h"
#include "input_keyboard.h"
#include "input_pad_d.h"
#include "fade.h"

//================================================
//マクロ定義
//================================================
#define MENU_UI_TUTORIAL_SIZE_X			(438.0f)	//TUTORIALのUIのサイズX
#define MENU_UI_TUTORIAL_SIZE_Y			(84.0f)		//TUTORIALのUIのサイズY
#define MENU_UI_START_SIZE_X			(304.0f)	//STARTのUIのサイズX
#define MENU_UI_START_SIZE_Y			(84.0f)		//STARTのUIのサイズY
#define MENU_UI_EXIT_SIZE_X				(304.0f)	//EXITのUIのサイズX
#define MENU_UI_EXIT_SIZE_Y				(84.0f)		//EXITのUIのサイズY
#define MENU_UI_NOT_SELECT_COLOR_ALPHA	(0.4f)		//選択されていないときのUIのα値

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CMenu::CMenu()
{
	m_nSelect = CMenu::SELECT_MENU_TYPE::SELECT_MENU_TYPE_NONE;
	memset(&m_apObject2D, NULL, sizeof(m_apObject2D));
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CMenu::~CMenu()
{

}

//================================================
//初期化処理
//================================================
HRESULT CMenu::Init(void)
{
	m_nSelect = CMenu::SELECT_MENU_TYPE::SELECT_MENU_TYPE_GAME_START;

	//背景の生成
	CObject2D *pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 
											 D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("menu.jpg"));

	//UIの生成
	m_apObject2D[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / (float)CMenu::SELECT_MENU_TYPE::SELECT_MENU_TYPE_MAX, 0.0f),
		                                     D3DXVECTOR3(MENU_UI_TUTORIAL_SIZE_X, MENU_UI_TUTORIAL_SIZE_Y, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	m_apObject2D[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial.png"));

	m_apObject2D[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / (float)CMenu::SELECT_MENU_TYPE::SELECT_MENU_TYPE_MAX * 2.0f, 0.0f),
		                                     D3DXVECTOR3(MENU_UI_START_SIZE_X, MENU_UI_START_SIZE_Y, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	m_apObject2D[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("start.png"));

	m_apObject2D[2] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / (float)CMenu::SELECT_MENU_TYPE::SELECT_MENU_TYPE_MAX * 3.0f, 0.0f),
		                                     D3DXVECTOR3(MENU_UI_EXIT_SIZE_X, MENU_UI_EXIT_SIZE_Y, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	m_apObject2D[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("exit.png"));

	//選択されているときは色を濃くして選択されていないときは薄くする
	if (m_nSelect == SELECT_MENU_TYPE_TUTORIAL)
	{
		m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
		m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
	}
	else if (m_nSelect == SELECT_MENU_TYPE_GAME_START)
	{
		m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
		m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
	}
	else if (m_nSelect == SELECT_MENU_TYPE_EXIT)
	{
		m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
		m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
		m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	return S_OK;
}

//================================================
//終了処理
//================================================
void CMenu::Uninit(void)
{
	////サウンド取得処理
	//CSound *pSound;
	//pSound = CManager::GetSound();
	////BGMの停止
	//pSound->Stop(CSound::SOUND_LABEL_MENU_BGM);

	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CMenu::Update(void)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//フェード取得処理
	CFade *pFade;
	pFade = CManager::GetFade();

	//パッド取得処理
	CInputPadD *pInputPadD;
	pInputPadD = CManager::GetInputPadD();
	DIJOYSTATE2 JoyStick = pInputPadD->GetGamepad();
	DIJOYSTATE2 JoyStickOld = pInputPadD->GetGamepadOld();

	////サウンド取得処理
	//CSound *pSound;
	//pSound = CManager::GetSound();

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		//選択処理
		if (pInputKeyboard->GetTrigger(DIK_UP) == true ||
			((float)JoyStick.lY < 0.0f && (float)JoyStickOld.lY == 0.0f))
		{
			m_nSelect--;
			if (m_nSelect < SELECT_MENU_TYPE_TUTORIAL)
			{
				m_nSelect = SELECT_MENU_TYPE_TUTORIAL;
			}
			else
			{
				////BGMの再生
				//pSound->Play(CSound::SOUND_LABEL_CURSOR_SE);
				////サウンドの音量調整
				//pSound->ControllVoice(CSound::SOUND_LABEL_CURSOR_SE, 0.8f);
			}

			//選択されているときは色を濃くして選択されていないときは薄くする
			if (m_nSelect == SELECT_MENU_TYPE_TUTORIAL)
			{
				m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
				m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
			}
			else if (m_nSelect == SELECT_MENU_TYPE_GAME_START)
			{
				m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
				m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
			}
			else if (m_nSelect == SELECT_MENU_TYPE_EXIT)
			{
				m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
				m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
				m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
		else if (pInputKeyboard->GetTrigger(DIK_DOWN) == true ||
			     ((float)JoyStick.lY > 0.0f && (float)JoyStickOld.lY == 0.0f))
		{
			m_nSelect++;
			if (m_nSelect > SELECT_MENU_TYPE_EXIT)
			{
				m_nSelect = SELECT_MENU_TYPE_EXIT;
			}
			else
			{
				////SEの再生
				//pSound->Play(CSound::SOUND_LABEL_CURSOR_SE);
				////サウンドの音量調整
				//pSound->ControllVoice(CSound::SOUND_LABEL_CURSOR_SE, 0.8f);
			}

			//選択されているときは色を濃くして選択されていないときは薄くする
			if (m_nSelect == SELECT_MENU_TYPE_TUTORIAL)
			{
				m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
				m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
			}
			else if (m_nSelect == SELECT_MENU_TYPE_GAME_START)
			{
				m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
				m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
			}
			else if (m_nSelect == SELECT_MENU_TYPE_EXIT)
			{
				m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
				m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
				m_apObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}

		//決定処理
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputPadD->GetTrigger(CInputPadD::B) == true ||
			pInputPadD->GetTrigger(CInputPadD::START) == true)
		{
			pFade->SetFade(CManager::MODE::TITLE);
		}
	}
}

//================================================
//描画処理
//================================================
void CMenu::Draw(void)
{
	
}