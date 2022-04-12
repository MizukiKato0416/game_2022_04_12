//================================================
//タイトル処理
//Author:加藤瑞葵
//================================================
#include "title.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_d.h"
#include "fade.h"
#include "manager.h"
#include "texture.h"
#include "ui.h"

//================================================
//マクロ定義
//================================================
#define TITLE_TO_RESULT_COUNT		(600)				//リザルトに行くまでの時間
#define TITLE_LOGO_SIZE_X			(366.0f)			//タイトルロゴのサイズX
#define TITLE_LOGO_SIZE_Y			(420.0f)			//タイトルロゴのサイズY
#define TITLE_PRESS_START_SIZE_X	(594.0f)			//PRESS START UIのサイズX
#define TITLE_PRESS_START_SIZE_Y	(84.0f)				//PRESS START UIのサイズY
#define TITLE_PRESS_START_POS_Y		(600.0f)			//PRESS START UIの位置Y

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CTitle::CTitle(int nPriority):CObject(nPriority)
{
	m_nTitleCounter = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CTitle::~CTitle()
{

}

//================================================
//初期化処理
//================================================
HRESULT CTitle::Init(void)
{
	//タイトル背景の生成
	CObject2D *pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 
											 D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_UI);
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_TITLE"));

	//タイトルロゴの生成
	CObject2D *pObject2DTitleLogo = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
													  D3DXVECTOR3(TITLE_LOGO_SIZE_X, TITLE_LOGO_SIZE_Y, 0.0f), CObject::PRIORITY_UI);
	pObject2DTitleLogo->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_TITLE_LOGO"));

	m_nTitleCounter = 0;
	return S_OK;
}

//================================================
//終了処理
//================================================
void CTitle::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CTitle::Update(void)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//パッドD取得処理
	CInputPadD *pInputPadD;
	pInputPadD = CManager::GetInstance()->GetInputPadD();

	//Enterキー、スタートボタンを押したら
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputPadD->GetPress(CInputPadD::START) == true)
	{
		//フェード取得処理
		CFade *pFade;
		pFade = CManager::GetInstance()->GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE::MENU);
		}
	}

	if (m_nTitleCounter % 90 == 0 || m_nTitleCounter == 0)
	{
		CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, TITLE_PRESS_START_POS_Y, 0.0f),
			        D3DXVECTOR3(TITLE_PRESS_START_SIZE_X, TITLE_PRESS_START_SIZE_Y, 0.0f), CObject::PRIORITY_UI, CUi::TYPE::PRESS_START);
	}

	//カウンターを増やす
	m_nTitleCounter++;
	

	if (m_nTitleCounter >= TITLE_TO_RESULT_COUNT)
	{
		m_nTitleCounter = 0;
		//フェード取得処理
		CFade *pFade;
		pFade = CManager::GetInstance()->GetFade();

		//リザルトに遷移
		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE::RESULT);
		}
	}
}

//================================================
//描画処理
//================================================
void CTitle::Draw(void)
{
	
}
