//================================================
//ポーズ処理
//Authore:加藤瑞葵
//================================================
#include "renderer.h"
#include "pause.h"
#include "manager.h"
#include "texture.h"
#include "object2D.h"
#include "input_keyboard.h"
#include "input_pad_d.h"
#include "fade.h"
#include "menu.h"

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
CPause::CPause(int nPriority) :CObject(nPriority)
{
	memset(&m_apObject2D, NULL, sizeof(m_apObject2D));
	m_bPause = false;
	m_pObject2D = nullptr;
	m_nSelect = SELECT::SELECT_START;
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
HRESULT CPause::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_bPause = false;
	m_nSelect = SELECT::SELECT_START;

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

	//Pキーかスタートボタンでポーズ
	if (pInputKeyboard->GetTrigger(DIK_P) == true || pInputPadD->GetTrigger(CInputPadD::START) == true)
	{
		if (m_bPause == false)
		{
			m_bPause = true;

			//フレームを作成
			m_pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
										    D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_PAUSE);
			m_pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_PAUSE"));

			//UIを作成
			m_apObject2D[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, PAUSE_START_POS_Y, 0.0f),
		                                        D3DXVECTOR3(MENU_UI_START_SIZE_X * 0.8f, MENU_UI_START_SIZE_Y * 0.8f, 0.0f), CObject::PRIORITY_PAUSE);
			m_apObject2D[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_START"));

			m_apObject2D[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, PAUSE_EXIT_POS_Y, 0.0f),
		                                     D3DXVECTOR3(MENU_UI_EXIT_SIZE_X* 0.8f, MENU_UI_EXIT_SIZE_Y * 0.8f, 0.0f), CObject::PRIORITY_PAUSE);
			m_apObject2D[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EXIT"));

			//色の設定
			m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));

			m_nSelect = SELECT_START;			//最初は再開を選択中にする
		}
		else
		{
			m_bPause = false;

			m_pObject2D->Uninit();
			m_pObject2D = nullptr;

			for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
			{
				m_apObject2D[nCnt]->Uninit();
				m_apObject2D[nCnt] = nullptr;
			}
		}
	}

	if (m_bPause == true)
	{
		//選択されているときは色を濃くして選択されていないときは薄くする
		if (m_nSelect == SELECT_START)
		{
			m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
		}
		else if (m_nSelect == SELECT_EXIT)
		{
			m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
			m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		//各選択肢を選択中にENTERキー、Bボタンを押したら
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputPadD->GetTrigger(CInputPadD::B) == true)
		{
			switch (m_nSelect)
			{
			case SELECT_START:
				////決定SE再生
				//pSound->Play(CSound::SOUND_LABEL_DECISION_SE);
				////音量調整
				//pSound->ControllVoice(CSound::SOUND_LABEL_DECISION_SE, 2.0f);
				break;
			case SELECT_EXIT:
				////決定SE再生
				//pSound->Play(CSound::SOUND_LABEL_DECISION_SE);
				////音量調整
				//pSound->ControllVoice(CSound::SOUND_LABEL_DECISION_SE, 2.0f);
				//メニュー画面に戻る
				if (pFade->GetFade() == CFade::FADE_NONE)
				{
					pFade->SetFade(CManager::MODE::MENU);
				}
				break;
			default:
				break;
			}

			////サウンド調整
			//pSound->ControllVoice(CSound::SOUND_LABEL_GAME_BGM, 0.5f);
			//pSound->ControllVoice(CSound::SOUND_LABEL_TUTORIAL_BGM, 0.5f);

			m_bPause = false;

			m_pObject2D->Uninit();
			m_pObject2D = nullptr;

			for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
			{
				m_apObject2D[nCnt]->Uninit();
				m_apObject2D[nCnt] = nullptr;
			}
		}

	


		//Wキー、↑キーを押す、左スティックを上に倒したとき
		if (pInputKeyboard->GetTrigger(DIK_W) == true || pInputKeyboard->GetTrigger(DIK_UP) == true ||
			((float)JoyStick.lY < 0.0f && (float)JoyStickOld.lY == 0.0f))
		{
			//現在の選択肢切り替え
			if (m_nSelect != SELECT_START)
			{
				////選択SE再生
				//pSound->Play(CSound::SOUND_LABEL_CHOICE_SE);
				
				m_nSelect--;
				//選択されているものを濃くされていないものを薄く設定
				m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
			}
		}
		//Sキー、↓キーを押すまたは左スティックを下に倒したとき
		if (pInputKeyboard->GetTrigger(DIK_S) == true || pInputKeyboard->GetTrigger(DIK_DOWN) == true ||
			((float)JoyStick.lY > 0.0f && (float)JoyStickOld.lY == 0.0f))
		{
			//現在の選択肢切り替え
			if (m_nSelect != SELECT_EXIT)
			{
				////選択SE再生
				//pSound->Play(CSound::SOUND_LABEL_CHOICE_SE);

				m_nSelect++;
				//選択されているものを濃くされていないものを薄く設定
				m_apObject2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, MENU_UI_NOT_SELECT_COLOR_ALPHA));
				m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
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
bool CPause::SetPause(bool bPause)
{
	m_bPause = bPause;
	return m_bPause;
}
//================================================
//生成処理
//================================================
CPause* CPause::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンスの生成
	CPause *pPause = nullptr;
	if (pPause == nullptr)
	{
		pPause = new CPause;
		if (pPause != nullptr)
		{
			pPause->Init(pos, size);
		}
	}
	return pPause;
}