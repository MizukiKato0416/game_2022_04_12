//================================================
//キラキラエフェクトの処理
//Author:KatoMizuki
//================================================
#include "sparkle.h"
#include "effect3D.h"
#include "manager.h"
#include "texture.h"
#include "game01.h"
#include "player.h"

//================================================
//マクロ定義
//================================================
#define SPARKLE_POS_X_RAND			(float (rand() % 60 + -30))		//エフェクトを出す位置Xのランダム値
#define SPARKLE_POS_Y_RAND			(float (rand() % 10))			//エフェクトを出す位置Yのランダム値
#define SPARKLE_SIZE_SUBTRACTION	(0.6f)							//サイズ減算量

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
		m_pEffect3D[nCnt]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("effect_sparkle.png"));
		//減算合成か加算合成かをランダムで選択
		m_pEffect3D[nCnt]->SetAlphaBlendSubtraction((bool)(rand() % 2));
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

			//オブジェクト情報を入れるポインタ
			vector<CObject*> object;

			//先頭のポインタを代入
			object = CObject::GetObject(static_cast<int>(CObject::PRIORITY::PLAYER));
			int object_size = object.size();

			for (int count_object = 0; count_object < object_size; count_object++)
			{
				if (object[count_object]->GetObjType() == CObject::OBJTYPE::PLAYER)
				{
					//プレイヤーの型にキャスト
					CPlayer *pPlayer = (CPlayer*)object[count_object];

					//プレイヤーが前に進む力を取得
					m_move.x = -pPlayer->GetMoveForward();
				}
			}

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
					m_pEffect3D.erase(m_pEffect3D.begin() + nCnt);
				}
			}
			else
			{
				//位置とサイズを設定
				m_pEffect3D[nCnt]->SetPos(pos, size);
			}
		}
	}

	//サイズが0になったら
	if ((int)m_pEffect3D.size() == 0)
	{
		//消す
		Uninit();
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
CSparkle* CSparkle::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &move, const int &nNumEffect)
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
