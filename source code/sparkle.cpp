//================================================
//炎の弾の処理
//Author:KatoMizuki
//================================================
#include "sparkle.h"
#include "effect3D.h"
#include "manager.h"
#include "texture.h"

//================================================
//マクロ定義
//================================================
#define SPARKLE_POS_X_RAND			(float (rand() % 100))			//エフェクトを出す位置Xのランダム値
#define SPARKLE_POS_Y_RAND			(float (rand() % 40))			//エフェクトを出す位置Yのランダム値
#define SPARKLE_SIZE_SUBTRACTION	(2.0f)							//サイズ減算量

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CSparkle::CSparkle(CObject::PRIORITY Priority) :CObject(Priority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pEffect3D.clear();
	m_nNumEffect = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CSparkle::~CSparkle()
{

}

//================================================
//初期化処理
//================================================
HRESULT CSparkle::Init()
{
	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::SPARKLE);
	
	//エフェクトの生成
	for (int nCnt = 0; nCnt < m_nNumEffect; nCnt++)
	{
		m_pEffect3D.push_back(CEffect3D::Create(D3DXVECTOR3(m_pos.x - SPARKLE_POS_X_RAND, m_pos.y + SPARKLE_POS_Y_RAND, m_pos.z),
			                                    m_size, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), CEffect3D::EFFECT3D_TYPE::TRAJECTORY_PLAYER));
		//テクスチャ設定
		m_pEffect3D[nCnt]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_SPARKLE"));
	}

	//位置とサイズを設定
	SetPos(m_pos);
	SetSize(m_size);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CSparkle::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CSparkle::Update(void)
{
	for (int nCnt = 0; nCnt < (int)m_pEffect3D.size(); nCnt++)
	{
		if (m_pEffect3D[nCnt] != nullptr)
		{
			//位置とサイズを取得
			D3DXVECTOR3 pos = m_pEffect3D[nCnt]->GetPos();
			D3DXVECTOR3 size = m_pEffect3D[nCnt]->GetSize();

			//移動量を加算
			pos += m_move;

			//サイズを小さくする
			size = D3DXVECTOR3(size.x - SPARKLE_SIZE_SUBTRACTION, size.y - SPARKLE_SIZE_SUBTRACTION, size.z);

			//サイズが0以下になったら
			if (size.x <= 0.0f || size.y <= 0.0f)
			{
				if (m_pEffect3D[nCnt] != nullptr)
				{
					//消す
					m_pEffect3D[nCnt]->Uninit();
					m_pEffect3D[nCnt] = nullptr;
				}
			}
			else
			{
				//位置とサイズを設定
				m_pEffect3D[nCnt]->SetPos(pos, size);
			}
		}
	}
}

//================================================
//描画処理
//================================================
void CSparkle::Draw(void)
{
	
}

//================================================
//生成処理
//================================================
CSparkle* CSparkle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, int nNumEffect)
{
	//インスタンスの生成
	CSparkle *pSparkle = nullptr;
	if (pSparkle == nullptr)
	{
		pSparkle = new CSparkle();
		if (pSparkle != nullptr)
		{
			pSparkle->m_pos = pos;
			pSparkle->m_size = size;
			pSparkle->m_move = move;
			pSparkle->m_nNumEffect = nNumEffect;
			pSparkle->Init();
		}
	}
	return pSparkle;
}
