//================================================
//フェード処理
//Author:加藤瑞葵
//================================================
#include "fade.h"
#include "object.h"
#include "manager.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CFade::CFade(int nPriority) :CObject2D(nPriority)
{
	m_fade = FADE_NONE;								//フェードの状態
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//フェードの色
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CFade::~CFade()
{

}

//================================================
//初期化処理
//================================================
HRESULT CFade::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_fade = FADE_IN;
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	CObject2D::Init(pos, size);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CFade::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================
//更新処理
//================================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			m_color.a -= 0.05f;
			if (m_color.a <= 0.0f)
			{
				m_color.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{
			m_color.a += 0.05f;
			if (m_color.a >= 1.0f)
			{
				m_color.a = 1.0f;
				m_fade = FADE_IN;

				//モードの設定
				CManager::SetMode(m_modeNext);
			}
		}
		CObject2D::SetCol(m_color);
	}
}

//================================================
//描画処理
//================================================
void CFade::Draw(void)
{
	CObject2D::Draw();
}

//================================================
//生成処理
//================================================
CFade *CFade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CManager::MODE modeNext)
{
	//インスタンスの生成
	CFade *pFade = nullptr;
	if (pFade == nullptr)
	{
		pFade = new CFade;
		if (pFade != nullptr)
		{
			pFade->Init(pos, size);
			pFade->m_fade = FADE_OUT;
			pFade->m_modeNext = modeNext;				//次の画面(モード)
			pFade->m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		}
	}

	return pFade;
}

//================================================
//設定処理
//================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	m_fade = FADE_OUT;
	m_modeNext = modeNext;
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//================================================
//取得処理
//================================================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}