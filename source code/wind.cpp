//================================================
//風エフェクトの処理
//Author:KatoMizuki
//================================================
#include "wind.h"
#include "effect3D.h"
#include "manager.h"
#include "texture.h"

//================================================
//マクロ定義
//================================================
#define WIND_MAX_COUNTER	(5)	//アニメーションが切り替わるまでのカウンター

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CWind::CWind(CObject::PRIORITY Priority) :CEffect3D(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nInitTexAnimNum = 0;
	m_nTexAnimCounter = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CWind::~CWind()
{

}

//================================================
//初期化処理
//================================================
HRESULT CWind::Init()
{
	CEffect3D::Init();

	//変数初期化
	m_nTexAnimCounter = 0;

	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::WIND);

	//アニメーションを設定
	SetTex(m_nInitTexAnimNum, WIND_MAX_PATTERN);
	//SetAlphaBlendSubtraction(true);
	SetAlphaBlend(false);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CWind::Uninit(void)
{
	CEffect3D::Uninit();
}

//================================================
//更新処理
//================================================
void CWind::Update(void)
{
	//テクスチャアニメーションの処理

	//カウンターを増やす
	m_nTexAnimCounter++;

	//既定の値より大きくなったら
	if (m_nTexAnimCounter > WIND_MAX_COUNTER)
	{
		//0にする
		m_nTexAnimCounter = 0;
		
		//アニメーションを次にする
		m_nInitTexAnimNum++;

		//アニメーションが最後まで行ったら
		if (m_nInitTexAnimNum >= WIND_MAX_PATTERN)
		{
			//最初に戻す
			m_nInitTexAnimNum = 0;
		}

		//アニメーションを設定
		SetTex(m_nInitTexAnimNum, WIND_MAX_PATTERN);
	}
}

//================================================
//描画処理
//================================================
void CWind::Draw(void)
{
	CEffect3D::Draw();

}

//================================================
//生成処理
//================================================
CWind* CWind::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const int &nInitTexAnimNum)
{
	//インスタンスの生成
	CWind *pWind = nullptr;
	if (pWind == nullptr)
	{
		pWind = new CWind();
		if (pWind != nullptr)
		{
			pWind->m_pos = pos;
			pWind->m_size = size;
			pWind->m_nInitTexAnimNum = nInitTexAnimNum;
			pWind->Init();
			pWind->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_WIND"));
		}
	}
	return pWind;
}
