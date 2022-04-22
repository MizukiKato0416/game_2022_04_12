//================================================
//ゲージ処理
//Author:KatoMizuki
//================================================
#include "gauge.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CGauge::CGauge(CObject::PRIORITY Priority) :CObject2D(Priority)
{
	m_nMaxNum = 0;
	m_nNum = 0;
	m_sizeMax = { 0.0f, 0.0f, 0.0f };
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CGauge::~CGauge()
{

}

//================================================
//初期化処理
//================================================
HRESULT CGauge::Init(void)
{
	//変数初期化
	

	//原点の種類を左に設定
	SetOriginType(CObject2D::ORIGIN_TYPE::LEFT);

	CObject2D::Init();

	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::GAUGE);

	//ゲージ設定処理
	SetGauge(m_nNum);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CGauge::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================
//更新処理
//================================================
void CGauge::Update(void)
{
	
}

//================================================
//描画処理
//================================================
void CGauge::Draw(void)
{
	CObject2D::Draw();
}

//================================================
//生成処理
//================================================
CGauge* CGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nMaxNum, int nNum)
{
	//インスタンスの生成
	CGauge *pGauge = nullptr;
	if (pGauge == nullptr)
	{
		pGauge = new CGauge();
		if (pGauge != nullptr)
		{
			pGauge->m_nMaxNum = nMaxNum;
			pGauge->m_nNum = nNum;
			pGauge->m_sizeMax = size;
			pGauge->Init();
			pGauge->SetPos(pos, size);
		}
	}
	return pGauge;
}

//================================================
//ゲージ増減処理
//================================================
void CGauge::AddGauge(int nNum)
{
	//値を加算
	m_nNum += nNum;

	//加算した値が最大値よりも大きかったら
	if (m_nNum > m_nMaxNum)
	{
		//最大値を設定
		m_nNum = m_nMaxNum;
	}
	else if (m_nNum < 0)
	{//加算した値が0よりも小さかったら
		//0にする
		m_nNum = 0;
	}

	//位置を取得
	D3DXVECTOR3 pos = GetPos();
	//サイズを取得
	D3DXVECTOR3 size = GetSize();
	//サイズを算出
	size.x = m_sizeMax.x * (float)(m_nNum) / (float)m_nMaxNum;
	//位置とサイズを設定
	SetPos(pos, size);
}

//================================================
//ゲージ設定処理
//================================================
void CGauge::SetGauge(int nNum)
{
	//設定した値が最大値よりも大きかったら
	if (nNum > m_nMaxNum)
	{
		//値を設定
		m_nNum = m_nMaxNum;
	}
	else if (nNum < 0)
	{//設定した値が0よりも小さかったら
		//0にする
		m_nNum = 0;
	}
	else
	{
		//値を設定
		m_nNum = nNum;
	}
	
	//位置を取得
	D3DXVECTOR3 pos = GetPos();
	//サイズを取得
	D3DXVECTOR3 size = GetSize();
	//サイズを算出
	size.x = m_sizeMax.x * (float)m_nNum / (float)m_nMaxNum;
	//位置とサイズを設定
	SetPos(pos, size);
}

//================================================
//ゲージ最大数値設定処理
//================================================
void CGauge::SetMaxNum(int nMaxNum)
{
	m_nMaxNum = nMaxNum;
}

