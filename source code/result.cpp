//================================================
//リザルト処理
//Author: 加藤瑞葵
//================================================
#include "result.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_d.h"
#include "fade.h"
#include "texture.h"
#include "ranking.h"

//================================================
//マクロ定義
//================================================
#define RESULT_TO_TITLE_COUNT			(900)				//タイトルに行くまでの間隔

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CResult::CResult()
{
	m_nResultCounter = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CResult::~CResult()
{

}

//================================================
//初期化処理
//================================================
HRESULT CResult::Init(void)
{
	CObject2D *pObject2D;
	pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
											 D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Bg.png"));
	pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
											 D3DXVECTOR3(SCREEN_WIDTH / 2.4, SCREEN_HEIGHT / 1.1, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("frame_Trophy.png"));
	pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 0.0f + 70.0f, 0.0f),
											 D3DXVECTOR3(500.0f, 70.0f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Ranking.png"));

	//ランキングの生成
	CRanking::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 0.0f, 0.0f), D3DXVECTOR3(RANKING_POLYGON_WIDTH, RANKING_POLYGON_HEIGHT, 0.0f));

	m_nResultCounter = 0;
	return S_OK;
}

//================================================
//終了処理
//================================================
void CResult::Uninit(void)
{	
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CResult::Update(void)
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
			pFade->SetFade(CManager::MODE::TITLE);
		}
	}

	//カウンターを加算
	m_nResultCounter++;

	if (m_nResultCounter >= RESULT_TO_TITLE_COUNT)
	{
		m_nResultCounter = 0;

		//フェード取得処理
		CFade *pFade;
		pFade = CManager::GetInstance()->GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			//タイトルに行く
			pFade->SetFade(CManager::MODE::TITLE);
		}
	}
}

//================================================
//描画処理
//================================================
void CResult::Draw(void)
{
	
}
