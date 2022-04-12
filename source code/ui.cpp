//================================================
//UI処理
//Authore:加藤瑞葵
//================================================
#include "Object2D.h"
#include "manager.h"
#include "ui.h"
#include "texture.h"
#include "control.h"
#include "control_ui_subtract_alpha.h"

//================================================
//マクロ定義
//================================================
#define UI_PRESS_START_SUBTRACT_ALPHA	(0.015f)		//PRESS START UIのα値減算値
#define UI_PRESS_START_DELAY			(10)			//PRESS START UIの表示時間

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CUi::CUi(CObject::PRIORITY Priority) :CObject2D(Priority)
{
	m_pControl = nullptr;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CUi::~CUi()
{

}

//================================================
//初期化処理
//================================================
HRESULT CUi::Init(void)
{
	CObject2D::Init();

	//位置とサイズを設定
	SetPos(pos, size);

	SetObjType(CObject::OBJTYPE::UI);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CUi::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================
//更新処理
//================================================
void CUi::Update(void)
{
	if (m_pControl != nullptr)
	{
		//各UIの更新処理を呼び出す
		m_pControl->Update(this);
	}
}

//================================================
//描画処理
//================================================
void CUi::Draw(void)
{
	CObject2D::Draw();
}

//================================================
//生成処理
//================================================
CUi* CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriolity, TYPE type)
{
	//インスタンスの生成
	CUi *pUi = nullptr;
	if (pUi == nullptr)
	{
		pUi = new CUi(static_cast<CObject::PRIORITY>(nPriolity));
		if (pUi != nullptr)
		{
			pUi->m_type = type;
			pUi->Init();
			// 指定したUIの種類でテクスチャを変える
			switch (type)
			{
			case TYPE::PRESS_START:
				pUi->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_PRESS_START");
				pUi->m_pControl = CControlUiSubtractAlpha::Create(pUi, UI_PRESS_START_SUBTRACT_ALPHA, UI_PRESS_START_DELAY);
			default:
				break;
			}
			pUi->BindTexture(pUi->m_pTexture);
		}
	}
	return pUi;
}
