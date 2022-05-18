//================================================
//クリックエフェクトの処理
//Author:KatoMizuki
//================================================
#include "effect_click.h"
#include "effect2D.h"
#include "manager.h"
#include "texture.h"
#include "object.h"

//================================================
//マクロ定義
//================================================
#define EFFECT_CLICK_SPARKLE_COL				(D3DXCOLOR(0.6f, 0.6f, 1.0f, 1.0f))								//キラキラエフェクトの色
#define EFFECT_CLICK_SPARKLE_ADD_SIZE			(1.63f)															//キラキラエフェクトのサイズを増加する割合
#define EFFECT_CLICK_SPARKLE_SUBTRACT_SIZE		(0.82f)															//キラキラエフェクトのサイズを減少する割合
#define EFFECT_CLICK_SPARKLE_ADD_SIZE_TIME		(10)															//キラキラエフェクトのサイズを増加する時間
#define EFFECT_CLICK_STAR_INIT_ALPHA			(0.0f)															//スターフェクトの初期α値
#define EFFECT_CLICK_STAR_01_COL				(D3DXCOLOR(1.0f, 1.0f, 0.0f, EFFECT_CLICK_STAR_INIT_ALPHA))		//スターフェクト01の色
#define EFFECT_CLICK_STAR_02_COL				(D3DXCOLOR(1.0f, 0.0f, 0.0f, EFFECT_CLICK_STAR_INIT_ALPHA))		//スターフェクト02の色
#define EFFECT_CLICK_STAR_03_COL				(D3DXCOLOR(0.0f, 0.0f, 1.0f, EFFECT_CLICK_STAR_INIT_ALPHA))		//スターフェクト03の色
#define EFFECT_CLICK_STAR_INIT_DIFFER			(25.0f)															//スターフェクトの中心からの初期距離
#define EFFECT_CLICK_STAR_ADD_DIFFER			(0.9f)															//スターフェクトの中心からの距離加算値
#define EFFECT_CLICK_STAR_INIT_SIZE				(40.0f)															//スターフェクトのサイズ
#define EFFECT_CLICK_STAR_SUBTRACT_ALPHA_TIME	(10)															//スターエフェクトの色を薄くし始める時間
#define EFFECT_CLICK_STAR_ADD_ALPHA				(0.15f)															//スターエフェクトのα値を増加する割合
#define EFFECT_CLICK_STAR_SUBTRACT_ALPHA		(0.05f)															//スターエフェクトのα値を減少する割合
#define EFFECT_CLICK_STAR_ADD_ROT				(0.1f)															//スターエフェクトの回転量
#define EFFECT_CLICK_RING_COL					(D3DXCOLOR(0.6f, 0.6f, 1.0f, 1.0f))								//リングフェクトの色
#define EFFECT_CLICK_RING_INIT_ADD_SIZE			(D3DXVECTOR3(5.0f, 5.0f, 0.0f))									//リングフェクトのサイズ加算量
#define EFFECT_CLICK_RING_01_SUBTRACT_SIZE		(0.9f)															//リングフェクトのサイズ減算量
#define EFFECT_CLICK_RING_02_SUBTRACT_SIZE		(0.878f)														//リングフェクトのサイズ減算量
#define EFFECT_CLICK_RING_01_SUBTRACT_SIZE_TIME	(8)																//リングフェクトのサイズ減算する時間
#define EFFECT_CLICK_RING_02_SUBTRACT_SIZE_TIME	(16)															//リングフェクトのサイズ減算する時間
#define EFFECT_CLICK_RING_01_SUBTRACT_ALPHA		(0.06f)															//リングフェクトのα値を減少する量
#define EFFECT_CLICK_RING_02_SUBTRACT_ALPHA		(0.056f)														//リングフェクトのα値を減少する量
#define EFFECT_CLICK_RING_02_CREATE_TIME		(8)																//リングフェクト2を生成するタイミング


//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CEffectClick::CEffectClick(CObject::PRIORITY Priority) :CObject(Priority)
{
	memset(m_pRing, NULL, sizeof(m_pRing[EFFECT_CLICK_RING_NUM]));
	memset(m_pStar, NULL, sizeof(m_pStar[EFFECT_CLICK_STAR_NUM]));
	memset(m_pStarBg, NULL, sizeof(m_pStarBg[EFFECT_CLICK_STAR_NUM]));
	m_pSparkle = nullptr;
	m_nCounter = 0;
	m_fStarDiffer = 0.0f;
	memset(m_fStarRot, NULL, sizeof(m_fStarRot[EFFECT_CLICK_STAR_NUM]));
	for (int nCntRing = 0; nCntRing < EFFECT_CLICK_RING_NUM; nCntRing++)
	{
		m_ringAddSize[nCntRing] = { 0.0f, 0.0f, 0.0f };
	}
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CEffectClick::~CEffectClick()
{

}

//================================================
//初期化処理
//================================================
HRESULT CEffectClick::Init()
{
	//変数初期化
	m_nCounter = 0;
	m_fStarDiffer = EFFECT_CLICK_STAR_INIT_DIFFER;
	memset(m_fStarRot, NULL, sizeof(m_fStarRot[EFFECT_CLICK_STAR_NUM]));
	for (int nCntRing = 0; nCntRing < EFFECT_CLICK_RING_NUM; nCntRing++)
	{
		m_ringAddSize[nCntRing] = EFFECT_CLICK_RING_INIT_ADD_SIZE;
	}
	

	//キラキラエフェクトの生成
	m_pSparkle = CEffect2D::Create(m_pos, D3DXVECTOR3(1.0f, 1.0f, 0.0f), EFFECT_CLICK_SPARKLE_COL, CEffect2D::EFFECT2D_TYPE::NONE);
	m_pSparkle->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("effect_sparkle.png"));
	m_pSparkle->SetPriority((int)(CObject::PRIORITY::CLICK_EFFECT));

	//星エフェクトの生成
	for (int nCntStar = 0; nCntStar < EFFECT_CLICK_STAR_NUM; nCntStar++)
	{
		m_pStarBg[nCntStar] = CEffect2D::Create(D3DXVECTOR3(m_pos.x + cosf(D3DX_PI * 2.0f / EFFECT_CLICK_STAR_NUM * nCntStar) * m_fStarDiffer,
														    m_pos.y + sinf(D3DX_PI * 2.0f / EFFECT_CLICK_STAR_NUM * nCntStar) * m_fStarDiffer, 0.0f),
														    D3DXVECTOR3(EFFECT_CLICK_STAR_INIT_SIZE, EFFECT_CLICK_STAR_INIT_SIZE, 0.0f),
														    D3DXCOLOR(1.0f, 1.0f, 1.0f, EFFECT_CLICK_STAR_INIT_ALPHA),
														    CEffect2D::EFFECT2D_TYPE::NONE);
		m_pStarBg[nCntStar]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("effect000.jpg"));
		m_pStarBg[nCntStar]->SetPriority((int)(CObject::PRIORITY::CLICK_EFFECT));

		m_pStar[nCntStar] = CObject2D::Create(D3DXVECTOR3(m_pos.x + cosf(D3DX_PI * 2.0f / EFFECT_CLICK_STAR_NUM * nCntStar) * m_fStarDiffer,
			                                              m_pos.y + sinf(D3DX_PI * 2.0f / EFFECT_CLICK_STAR_NUM * nCntStar) * m_fStarDiffer, 0.0f),
			                                              D3DXVECTOR3(EFFECT_CLICK_STAR_INIT_SIZE, EFFECT_CLICK_STAR_INIT_SIZE, 0.0f),
			                                              (int)(CObject::PRIORITY::CLICK_EFFECT));
		m_pStar[nCntStar]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("effect_star.png"));
		m_pStar[nCntStar]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, EFFECT_CLICK_STAR_INIT_ALPHA));
	}
	m_pStarBg[0]->SetCol(EFFECT_CLICK_STAR_01_COL);
	m_pStarBg[1]->SetCol(EFFECT_CLICK_STAR_02_COL);
	m_pStarBg[2]->SetCol(EFFECT_CLICK_STAR_03_COL);

	//円エフェクトの生成
	m_pRing[0] = CEffect2D::Create(m_pos, D3DXVECTOR3(1.0f, 1.0f, 0.0f), EFFECT_CLICK_RING_COL, CEffect2D::EFFECT2D_TYPE::NONE);
	m_pRing[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("effect_ring.jpg"));
	m_pRing[0]->SetPriority((int)(CObject::PRIORITY::CLICK_EFFECT));

	return S_OK;
}

//================================================
//終了処理
//================================================
void CEffectClick::Uninit(void)
{
	Release();
}

//================================================
//更新処理
//================================================
void CEffectClick::Update(void)
{
	//カウンターを加算
	m_nCounter++;

	//キラキラエフェクトの処理
	Sparkle();

	//星エフェクトの処理
	Star();

	//円エフェクトの処理
	Ring();
}

//================================================
//描画処理
//================================================
void CEffectClick::Draw(void)
{
	
}

//================================================
//生成処理
//================================================
CEffectClick *CEffectClick::Create(const D3DXVECTOR3 &pos)
{
	//インスタンスの生成
	CEffectClick *pEffectClick = nullptr;
	if (pEffectClick == nullptr)
	{
		pEffectClick = new CEffectClick();
		if (pEffectClick != nullptr)
		{
			pEffectClick->m_pos = pos;
			pEffectClick->Init();
		}
	}
	return pEffectClick;
}

//================================================
//キラキラエフェクトの処理
//================================================
void CEffectClick::Sparkle(void)
{
	if (m_pSparkle != nullptr)
	{
		//キラキラエフェクトのサイズを取得
		D3DXVECTOR3 SparkleSize = m_pSparkle->GetSize();
		//既定の値以下の時
		if (m_nCounter <= EFFECT_CLICK_SPARKLE_ADD_SIZE_TIME)
		{
			//サイズを既定の値ずつ大きくする
			SparkleSize *= EFFECT_CLICK_SPARKLE_ADD_SIZE;
		}
		else
		{//既定の値より大きいとき
		 //サイズを既定の値ずつ小さくする
			SparkleSize *= EFFECT_CLICK_SPARKLE_SUBTRACT_SIZE;
		}

		//既定の値より小さくなったら
		if (SparkleSize.x < 1.0f || SparkleSize.y < 1.0f)
		{
			//消す
			m_pSparkle->Uninit();
			m_pSparkle = nullptr;
		}
		else
		{
			//位置とサイズを設定
			m_pSparkle->SetPos(m_pSparkle->GetPos(), SparkleSize);
		}
	}
}

//================================================
//リングエフェクトの処理
//================================================
void CEffectClick::Ring(void)
{
	if (m_nCounter == EFFECT_CLICK_RING_02_CREATE_TIME)
	{
		//円エフェクトの生成
		m_pRing[1] = CEffect2D::Create(m_pos, D3DXVECTOR3(1.0f, 1.0f, 0.0f), EFFECT_CLICK_RING_COL, CEffect2D::EFFECT2D_TYPE::NONE);
		m_pRing[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("effect_ring.jpg"));
		m_pRing[1]->SetPriority((int)(CObject::PRIORITY::CLICK_EFFECT));
	}

	if (m_pRing[0] != nullptr)
	{
		//既定の値より大きくなったら
		if (m_nCounter > EFFECT_CLICK_RING_01_SUBTRACT_SIZE_TIME)
		{
			//サイズ加算量を減らしていく
			m_ringAddSize[0] *= EFFECT_CLICK_RING_01_SUBTRACT_SIZE;

			//カラー取得
			D3DXCOLOR ringCol = m_pRing[0]->GetCol();
			//薄くする
			ringCol.a -= EFFECT_CLICK_RING_01_SUBTRACT_ALPHA;
			//見えなくなったら
			if (ringCol.a <= 0.0f)
			{
				//消す
				m_pRing[0]->Uninit();
				m_pRing[0] = nullptr;
			}
			else
			{
				m_pRing[0]->SetCol(ringCol);
			}
		}
	}

	if (m_pRing[1] != nullptr)
	{
		//既定の値より大きくなったら
		if (m_nCounter > EFFECT_CLICK_RING_02_SUBTRACT_SIZE_TIME)
		{
			//サイズ加算量を減らしていく
			m_ringAddSize[1] *= EFFECT_CLICK_RING_02_SUBTRACT_SIZE;

			//カラー取得
			D3DXCOLOR ringCol = m_pRing[1]->GetCol();
			//薄くする
			ringCol.a -= EFFECT_CLICK_RING_02_SUBTRACT_ALPHA;
			//見えなくなったら
			if (ringCol.a <= 0.0f)
			{
				//消す
				m_pRing[1]->Uninit();
				m_pRing[1] = nullptr;
				Uninit();
			}
			else
			{
				m_pRing[1]->SetCol(ringCol);
			}
		}
	}

	for (int nCntRing = 0; nCntRing < EFFECT_CLICK_RING_NUM; nCntRing++)
	{
		if (m_pRing[nCntRing] != nullptr)
		{
			//サイズを取得
			D3DXVECTOR3 lingSize = m_pRing[nCntRing]->GetSize();
			//サイズを大きくする
			lingSize += m_ringAddSize[nCntRing];
			//サイズを設定
			m_pRing[nCntRing]->SetPos(m_pRing[nCntRing]->GetPos(), lingSize);
		}
	}
}

//================================================
//星エフェクトの処理
//================================================
void CEffectClick::Star(void)
{
	//位置を少しずつ中心から離す
	m_fStarDiffer += EFFECT_CLICK_STAR_ADD_DIFFER;
	//向きを少しずつ加算する
	m_fStarRot[0] += EFFECT_CLICK_STAR_ADD_ROT;
	m_fStarRot[1] += EFFECT_CLICK_STAR_ADD_ROT;
	m_fStarRot[2] -= EFFECT_CLICK_STAR_ADD_ROT;

	for (int nCntStar = 0; nCntStar < EFFECT_CLICK_STAR_NUM; nCntStar++)
	{
		if (m_pStar[nCntStar] != nullptr)
		{
			//位置取得
			D3DXVECTOR3 starPos = m_pStar[nCntStar]->GetPos();
			//位置を移動させる
			starPos = D3DXVECTOR3(m_pos.x + cosf(D3DX_PI * 2.0f / EFFECT_CLICK_STAR_NUM * nCntStar) * m_fStarDiffer,
				m_pos.y + sinf(D3DX_PI * 2.0f / EFFECT_CLICK_STAR_NUM * nCntStar) * m_fStarDiffer, 0.0f);
			//位置設定
			m_pStar[nCntStar]->SetPos(starPos, m_pStar[nCntStar]->GetSize(), m_fStarRot[nCntStar]);

			//色取得
			D3DXCOLOR starCol = m_pStar[nCntStar]->GetCol();
			//既定の値以下だったら
			if (m_nCounter <= EFFECT_CLICK_STAR_SUBTRACT_ALPHA_TIME)
			{
				//1.0fより小さかったら
				if (starCol.a < 1.0f)
				{
					//色を濃くする
					starCol.a += EFFECT_CLICK_STAR_ADD_ALPHA;
					//1.0fより大きくなったら
					if (starCol.a > 1.0f)
					{
						//1.0にする
						starCol.a = 1.0f;
					}
					//色を設定
					m_pStar[nCntStar]->SetCol(starCol);
				}
			}
			else
			{//既定の値より大きかったら
			 //色を薄くする
				starCol.a -= EFFECT_CLICK_STAR_SUBTRACT_ALPHA;
				//見えなくなったら
				if (starCol.a <= 0.0f)
				{
					//消す
					m_pStar[nCntStar]->Uninit();
					m_pStar[nCntStar] = nullptr;
				}
				else
				{
					//色を設定
					m_pStar[nCntStar]->SetCol(starCol);
				}
			}
		}
	}

	for (int nCntStarBg = 0; nCntStarBg < EFFECT_CLICK_STAR_NUM; nCntStarBg++)
	{
		if (m_pStarBg[nCntStarBg] != nullptr)
		{
			//位置取得
			D3DXVECTOR3 starPos = m_pStarBg[nCntStarBg]->GetPos();
			//位置を移動させる
			starPos = D3DXVECTOR3(m_pos.x + cosf(D3DX_PI * 2.0f / EFFECT_CLICK_STAR_NUM * nCntStarBg) * m_fStarDiffer,
				                  m_pos.y + sinf(D3DX_PI * 2.0f / EFFECT_CLICK_STAR_NUM * nCntStarBg) * m_fStarDiffer, 0.0f);
			//位置設定
			m_pStarBg[nCntStarBg]->SetPos(starPos, m_pStarBg[nCntStarBg]->GetSize(), m_fStarRot[nCntStarBg]);

			//色取得
			D3DXCOLOR starCol = m_pStarBg[nCntStarBg]->GetCol();
			//既定の値以下だったら
			if (m_nCounter <= EFFECT_CLICK_STAR_SUBTRACT_ALPHA_TIME)
			{
				//1.0fより小さかったら
				if (starCol.a < 1.0f)
				{
					//色を濃くする
					starCol.a += EFFECT_CLICK_STAR_ADD_ALPHA;
					//1.0fより大きくなったら
					if (starCol.a > 1.0f)
					{
						//1.0にする
						starCol.a = 1.0f;
					}
					//色を設定
					m_pStarBg[nCntStarBg]->SetCol(starCol);
				}
			}
			else
			{//既定の値より大きかったら
			 //色を薄くする
				starCol.a -= EFFECT_CLICK_STAR_SUBTRACT_ALPHA;
				//見えなくなったら
				if (starCol.a <= 0.0f)
				{
					//消す
					m_pStarBg[nCntStarBg]->Uninit();
					m_pStarBg[nCntStarBg] = nullptr;
				}
				else
				{
					//色を設定
					m_pStarBg[nCntStarBg]->SetCol(starCol);
				}
			}
		}
	}
}
