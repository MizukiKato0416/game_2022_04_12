//================================================
//煙エフェクトの処理
//Author:KatoMizuki
//================================================
#include "smoke.h"
#include "effect3D.h"
#include "manager.h"
#include "texture.h"

//================================================
//マクロ定義
//================================================

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CSmoke::CSmoke(CObject::PRIORITY Priority) :CObject(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_addRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_addSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pEffect3D = nullptr;
	m_fSubtractAlpha = 0.0f;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CSmoke::~CSmoke()
{

}

//================================================
//初期化処理
//================================================
HRESULT CSmoke::Init()
{
	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::SMOKE);
	
	//エフェクトの生成
	m_pEffect3D = CEffect3D::Create(m_pos, m_size, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CEffect3D::EFFECT3D_TYPE::SMOKE);
	m_pEffect3D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EFFECT_SMOKE"));
	m_pEffect3D->SetRot(m_rot);

	//位置とサイズを設定
	SetPos(m_pos);
	SetSize(m_size);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CSmoke::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CSmoke::Update(void)
{
	//カラーを取得
	D3DXCOLOR col = m_pEffect3D->GetCol();
	//α値を既定の値ずつ減らす
	col.a -= m_fSubtractAlpha;
	//col = D3DXCOLOR(0.5f, 0.5f, 0.5f, col.a);
	//0以下になったら
	if (col.a <= 0.0f)
	{
		//消す
		m_pEffect3D->Uninit();
		m_pEffect3D = nullptr;
		Uninit();
		return;
	}
	else
	{
		//色を設定
		m_pEffect3D->SetCol(col);
	}

	//サイズを取得
	m_size = m_pEffect3D->GetSize();
	//既定の値サイズを増やす
	m_size += m_addSize;

	//位置を取得
	m_pos = m_pEffect3D->GetPos();
	//既定の値位置を増やす
	m_pos += m_move;
	//位置とサイズを設定する
	m_pEffect3D->SetPos(m_pos, m_size);

	//向きを取得
	m_rot = m_pEffect3D->GetRot();
	//既定の値向きを増やす
	m_rot += m_addRot;
	//πより大きくなったら-2πする
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{	//-πより小さくなったら+2πする
		m_rot.y += D3DX_PI * 2.0f;
	}
	//向きを設定する
	m_pEffect3D->SetRot(m_rot);
}

//================================================
//描画処理
//================================================
void CSmoke::Draw(void)
{
	
}

//================================================
//生成処理
//================================================
CSmoke* CSmoke::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, const D3DXVECTOR3 move, const D3DXVECTOR3 addRot,
	                   const D3DXVECTOR3 addSize, const float fSubtractAlpha)
{
	//インスタンスの生成
	CSmoke *pSmoke = nullptr;
	if (pSmoke == nullptr)
	{
		pSmoke = new CSmoke();
		if (pSmoke != nullptr)
		{
			pSmoke->m_pos = pos;
			pSmoke->m_move = move;
			pSmoke->m_size = size;
			pSmoke->m_rot = rot;
			pSmoke->m_addRot = addRot;
			pSmoke->m_addSize = addSize;
			pSmoke->m_fSubtractAlpha = fSubtractAlpha;
			pSmoke->Init();
		}
	}
	return pSmoke;
}
