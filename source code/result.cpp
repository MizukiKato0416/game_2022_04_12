//================================================
//リザルト処理
//Author: 加藤瑞葵
//================================================
#include "result.h"
#include "manager.h"
#include "input_mouse.h"
#include "fade.h"
#include "texture.h"
#include "ranking.h"
#include "sound.h"

//================================================
//マクロ定義
//================================================
#define RESULT_TO_TITLE_COUNT			(900)				//タイトルに行くまでの間隔
#define RESULT_RANKING_POS_Y			(150.0f)			//ランキングの高さ

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CResult::CResult(CObject::PRIORITY Priority) :CObject(Priority)
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
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();

	sound->Stop();
	sound->Play(CSound::SOUND_LABEL::RESULT_BGM);
	sound->ControllVoice(CSound::SOUND_LABEL::RESULT_BGM, 0.4f);

	/*CObject2D *pObject2D;
	pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
											 D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Bg.png"));
	pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
											 D3DXVECTOR3(SCREEN_WIDTH / 2.6f, SCREEN_HEIGHT / 1.1f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("frame_Trophy.png"));
	pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 0.0f + 70.0f, 0.0f),
											 D3DXVECTOR3(500.0f, 70.0f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Ranking.png"));
*/
	//ランキングの生成
	//CRanking::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, RESULT_RANKING_POS_Y, 0.0f), D3DXVECTOR3(RANKING_POLYGON_WIDTH, RANKING_POLYGON_HEIGHT, 0.0f));

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
	CInputMouse *pMouse = CManager::GetInstance()->GetInputMouse();
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();

	//マウス左クリックしたら
	if (pMouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
	{
		//フェード取得処理
		CFade *pFade;
		pFade = CManager::GetInstance()->GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			sound->ControllVoice(CSound::SOUND_LABEL::DECISION_SE, 1.2f);
			sound->Play(CSound::SOUND_LABEL::DECISION_SE);
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
