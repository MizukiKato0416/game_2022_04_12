//=============================================================================
// ヒットエフェクトの動きの処理
// Author : 加藤瑞葵
//=============================================================================
#include "control_ui_subtract_alpha.h"
#include "ui.h"

//================================================
//マクロ定義
//================================================	

//=============================================================================
// コンストラクタ
//=============================================================================
CControlUiSubtractAlpha::CControlUiSubtractAlpha()
{
	m_fSubtractAlpha = 0.0f;
	m_nDelay = 0;
	m_nDelayCounter = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CControlUiSubtractAlpha::~CControlUiSubtractAlpha()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlUiSubtractAlpha::Init(const CObject *pObject)
{
	m_nDelayCounter = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlUiSubtractAlpha::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CControlUiSubtractAlpha::Update(const CObject *pObject)
{
	//カウンターを加算
	m_nDelayCounter++;

	//既定の値以上になったら
	if (m_nDelayCounter >= m_nDelay)
	{
		//オブジェクトのポインタをエフェクトのポインタにキャスト
		CUi *pUi = NULL;
		pUi = (CUi*)pObject;

		//カラーの取得
		D3DXCOLOR col = pUi->GetCol();
		//薄くする
		col.a -= m_fSubtractAlpha;
		//見えなくなったら
		if (col.a <= 0.0f)
		{
			//消す
			pUi->Uninit();
			return;
		}
		pUi->SetCol(col);
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CControlUiSubtractAlpha *CControlUiSubtractAlpha::Create(const CObject *pObject, const float &fSubtractAlpha, const int &nDelay)
{
	//インスタンスの生成
	CControlUiSubtractAlpha *pControlUiSubtractAlpha = NULL;
	if (pControlUiSubtractAlpha == NULL)
	{
		pControlUiSubtractAlpha = new CControlUiSubtractAlpha;
		if (pControlUiSubtractAlpha != NULL)
		{
			pControlUiSubtractAlpha->m_fSubtractAlpha = fSubtractAlpha;
			pControlUiSubtractAlpha->m_nDelay = nDelay;
			pControlUiSubtractAlpha->Init(pObject);
		}
	}
	return pControlUiSubtractAlpha;
}