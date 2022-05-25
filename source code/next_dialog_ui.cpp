//================================================
//次のセリフに行くUI処理
//Authore:加藤瑞葵
//================================================
#include "Object2D.h"
#include "next_dialog_ui.h"

//================================================
//マクロ定義
//================================================
#define NEXT_DIALOG_UI_ADD_ROTATE		(0.05f)		//回転を増やす値
#define NEXT_DIALOG_UI_SUBTRACTALPHA	(0.01f)		//薄くする値
#define NEXT_DIALOG_UI_COUNTER			(30)		//見えるようにするまでの時間

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CNextDialogUI::CNextDialogUI(CObject::PRIORITY Priority) :CObject2D(Priority)
{
	m_fRotation = 0.0f;
	m_nCounter = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CNextDialogUI::~CNextDialogUI()
{

}

//================================================
//初期化処理
//================================================
HRESULT CNextDialogUI::Init(void)
{
	//変数初期化
	m_fRotation = 0.0f;
	m_nCounter = 0;

	CObject2D::Init();

	SetObjType(CObject::OBJTYPE::UI);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CNextDialogUI::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================
//更新処理
//================================================
void CNextDialogUI::Update(void)
{
	//色取得
	D3DXCOLOR col = GetCol();
	//薄くする
	col.a -= NEXT_DIALOG_UI_SUBTRACTALPHA;
	//見えなくなったら
	if (col.a <= 0.0f)
	{
		//0にする
		col.a = 0.0f;

		//カウンターを増やす
		m_nCounter++;

		if (m_nCounter > NEXT_DIALOG_UI_COUNTER)
		{
			//0にする
			m_nCounter = 0;

			//見えるようにする
			col.a = 1.0f;
			//色設定
			SetCol(col);
		}
	}
	else
	{
		//色設定
		SetCol(col);
	}

	//回転値を増やす
	m_fRotation += NEXT_DIALOG_UI_ADD_ROTATE;
	if (m_fRotation >= D3DX_PI * 2.0f)
	{
		m_fRotation -= D3DX_PI * 2.0f;
	}

	//設定
	SetPos(GetPos(), GetSize(), m_fRotation);
}

//================================================
//描画処理
//================================================
void CNextDialogUI::Draw(void)
{
	CObject2D::Draw();
}

//================================================
//生成処理
//================================================
CNextDialogUI* CNextDialogUI::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	//インスタンスの生成
	CNextDialogUI *pNextDialogUI = nullptr;
	if (pNextDialogUI == nullptr)
	{
		pNextDialogUI = new CNextDialogUI();
		if (pNextDialogUI != nullptr)
		{
			pNextDialogUI->Init();
			//位置とサイズを設定
			pNextDialogUI->SetPos(pos, size);
		}
	}
	return pNextDialogUI;
}
