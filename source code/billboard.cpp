//================================================
//3Dポリゴン処理
//Author:加藤瑞葵
//================================================
#include "renderer.h"
#include "billboard.h"
#include "manager.h"
#include "player.h"
#include "camera.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CBillboard::CBillboard(CObject::PRIORITY Priority) : CObject(static_cast<CObject::PRIORITY>(Priority))
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCntVtx = 0; nCntVtx < VERTEX_3D_NUM; nCntVtx++)
	{
		m_vtxPos[nCntVtx] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vtxRot[nCntVtx] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mode = BILLBOARD_MODE::NONE;
	SetObjType(CObject::OBJTYPE::POLYGON_3D);
	m_bCulling = false;
	m_bAlphaBlend = false;
	m_bAlphaTest = false;
	m_bLighting = false;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CBillboard::~CBillboard()
{

}

//================================================
//初期化処理
//================================================
HRESULT CBillboard::Init(void)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//変数初期化
	m_mode = BILLBOARD_MODE::NORMAL;
	m_bCulling = true;
	m_bAlphaBlend = false;
	m_bAlphaTest = false;
	m_bLighting = true;

	//位置・サイズ設定処理
	CObject::SetPos(m_pos);
	CObject::SetSize(m_size);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	VERTEX_3D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(- m_size.x / 2.0f, + m_size.y / 2.0f, + m_size.z / 2.0f);
	pVtx[1].pos = D3DXVECTOR3(+ m_size.x / 2.0f, + m_size.y / 2.0f, + m_size.z / 2.0f);
	pVtx[2].pos = D3DXVECTOR3(- m_size.x / 2.0f, - m_size.y / 2.0f, - m_size.z / 2.0f);
	pVtx[3].pos = D3DXVECTOR3(+ m_size.x / 2.0f, - m_size.y / 2.0f, - m_size.z / 2.0f);

	for (int nCntVtx = 0; nCntVtx < VERTEX_3D_NUM; nCntVtx++)
	{
		m_vtxPos[nCntVtx] = pVtx[nCntVtx].pos;
		m_vtxRot[nCntVtx] = m_vtxRot[nCntVtx];
	}

	//法線ベクトルを求める
	D3DXVECTOR3 vec[2];		//外積計算用ベクトル
	D3DXVECTOR3 vecNor;		//法線ベクトル

	//外積計算のためのベクトルを求める
	vec[0] = D3DXVECTOR3(pVtx[1].pos.x - pVtx[0].pos.x, pVtx[1].pos.y - pVtx[0].pos.y, pVtx[1].pos.z - pVtx[0].pos.z);
	vec[1] = D3DXVECTOR3(pVtx[2].pos.x - pVtx[0].pos.x, pVtx[2].pos.y - pVtx[0].pos.y, pVtx[2].pos.z - pVtx[0].pos.z);

	//外積計算
	D3DXVec3Cross(&vecNor, &vec[0], &vec[1]);

	//ベクトルを正規化する(ベクトルの大きさを1にする)
	D3DXVec3Normalize(&vecNor, &vecNor);

	//法線
	pVtx[0].nor = D3DXVECTOR3(vecNor.x, vecNor.y, vecNor.z);
	pVtx[1].nor = D3DXVECTOR3(vecNor.x, vecNor.y, vecNor.z);
	pVtx[2].nor = D3DXVECTOR3(vecNor.x, vecNor.y, vecNor.z);
	pVtx[3].nor = D3DXVECTOR3(vecNor.x, vecNor.y, vecNor.z);

	//カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//終了処理
//================================================
void CBillboard::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CBillboard::Update(void)
{
	
}

//================================================
//描画処理
//================================================
void CBillboard::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxView;						//ビューマトリックス
	D3DXMATRIX mtxTrans;					//計算用マトリックス
	D3DXMatrixIdentity(&m_mtxWorld);		//ワールドマトリックスの初期化

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	switch (m_mode)
	{
	case BILLBOARD_MODE::NORMAL:		//普通のビルボード
		//ポリゴンをカメラに対して正面に向ける
		D3DXMatrixInverse(&m_mtxWorld, nullptr, &mtxView);
		break;
	case BILLBOARD_MODE::BESIDE_ONLY:	//横にしか動かないビルボード
		//ポリゴンをカメラに対して正面に向ける
		m_mtxWorld._11 = mtxView._11;
		m_mtxWorld._12 = mtxView._21;
		m_mtxWorld._13 = mtxView._31;
		//m_mtxWorld._21 = mtxView._12;
		m_mtxWorld._22 = mtxView._22;
		//m_mtxWorld._23 = mtxView._32;
		m_mtxWorld._31 = mtxView._13;
		m_mtxWorld._32 = mtxView._23;
		m_mtxWorld._33 = mtxView._33;
		break;
	default:
		break;
	}
	
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//カリングを行わない設定なら
	if (m_bCulling == false)
	{
		// カリングを行わない
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}

	//加算合成を行う設定なら
	if (m_bAlphaBlend == true)
	{
		//アルファテスト
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 50);

		//αブレンディングを加算合成に設定
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		//Zバッファの書き込み
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	}

	//αテストを行う設定なら
	if (m_bAlphaTest == true)
	{
		//アルファテスト
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
	}

	//ライティングを行わない設定なら
	if (m_bAlphaTest == true)
	{
		//ライティングを無効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);					//頂点フォーマットの設定

	pDevice->SetTexture(0, m_pTexture);				//テクスチャの設定

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,											//開始する頂点のインデックス
		2);											//描画するプリミティブ数

													//ライティングを行わない設定なら
	if (m_bAlphaTest == true)
	{
		//ライティングを有効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}

	//αテストを行う設定なら
	if (m_bAlphaTest == true)
	{
		//アルファテスト元に戻す
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
	}

	//加算合成を行う設定なら
	if (m_bAlphaBlend == true)
	{
		//Zテストを元に戻す
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		//aブレンディングを通常に戻す
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//アルファテスト元に戻す
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
	}

	//カリングを行わない設定なら
	if (m_bCulling == false)
	{
		// カリングを行う
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}

	//4頂点の設定
	for (int nCntVtx = 0; nCntVtx < VERTEX_3D_NUM; nCntVtx++)
	{
		D3DXMatrixIdentity(&m_vtxMtxWorld[nCntVtx]);		//ワールドマトリックスの初期化

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_vtxPos[nCntVtx].x, m_vtxPos[nCntVtx].y, m_vtxPos[nCntVtx].z);
		D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxTrans);

		D3DXMATRIX mtxParent;		//親のマトリックス
		mtxParent = m_mtxWorld;

		//算出した各パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
		D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxParent);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_vtxMtxWorld[nCntVtx]);
	}
}

//================================================
//生成処理
//================================================
CBillboard* CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンスの生成
	CBillboard *pBillboard = nullptr;
	if (pBillboard == nullptr)
	{
		pBillboard = new CBillboard();
		if (pBillboard != nullptr)
		{
			pBillboard->m_pos = pos;
			pBillboard->m_size = size;
			pBillboard->Init();
		}
	}
	return pBillboard;
}

//================================================
//位置取得処理
//================================================
D3DXVECTOR3 CBillboard::GetPos(void)
{
	return m_pos;
}

//================================================
//位置設定処理
//================================================
void CBillboard::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;

	//位置・サイズ設定処理
	CObject::SetPos(m_pos);
	CObject::SetSize(m_size);

	VERTEX_3D *pVtx;	// 頂点情報
						//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3( - m_size.x / 2.0f, + m_size.y / 2.0f,  + m_size.z / 2.0f);
	pVtx[1].pos = D3DXVECTOR3( + m_size.x / 2.0f, + m_size.y / 2.0f,  + m_size.z / 2.0f);
	pVtx[2].pos = D3DXVECTOR3( - m_size.x / 2.0f, - m_size.y / 2.0f,  - m_size.z / 2.0f);
	pVtx[3].pos = D3DXVECTOR3( + m_size.x / 2.0f, - m_size.y / 2.0f,  - m_size.z / 2.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================
//テクスチャ設定処理
//================================================
void CBillboard::SetTex(int nPattern, int nMaxPattern)
{
	VERTEX_3D *pVtx;	// 頂点情報
	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2((1.0f / nMaxPattern) * nPattern, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / nMaxPattern) + (1.0f / nMaxPattern) * nPattern, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f / nMaxPattern) * nPattern, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / nMaxPattern) + (1.0f / nMaxPattern) * nPattern, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================
//テクスチャ設定処理
//================================================
void CBillboard::SetTex(float fMoveTexU, float fMoveTexV)
{
	VERTEX_3D *pVtx;	// 頂点情報
	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + fMoveTexU, 0.0f + fMoveTexV);
	pVtx[1].tex = D3DXVECTOR2(1.0f + fMoveTexU, 0.0f + fMoveTexV);
	pVtx[2].tex = D3DXVECTOR2(0.0f + fMoveTexU, 1.0f + fMoveTexV);
	pVtx[3].tex = D3DXVECTOR2(1.0f + fMoveTexU, 1.0f + fMoveTexV);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================
//カラー設定処理
//================================================
void CBillboard::SetCol(D3DCOLORVALUE col)
{
	VERTEX_3D *pVtx;	// 頂点情報
						//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[1].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[2].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[3].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================
//カラー設定処理
//================================================
void CBillboard::SetCol(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;	// 頂点情報
						//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================
//カラー取得処理
//================================================
D3DXCOLOR CBillboard::GetCol(void)
{
	VERTEX_3D *pVtx;	// 頂点情報
						//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXCOLOR col;
	col = pVtx[0].col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return col;
}

//================================================
//テクスチャ割り当て処理
//================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//================================================
//カリング設定処理
//================================================
void CBillboard::SetCulling(bool bCulling)
{
	m_bCulling = bCulling;
}

//================================================
//加算合成設定処理
//================================================
void CBillboard::SetAlphaBlend(bool bAlphaBlend)
{
	m_bAlphaBlend = bAlphaBlend;
}

//================================================
//αテスト設定処理
//================================================
void CBillboard::SetAlphaTest(bool bAlphaTest)
{
	m_bAlphaTest = bAlphaTest;
}

//================================================
//ライティング設定処理
//================================================
void CBillboard::SetLighting(bool bLighting)
{
	m_bLighting = bLighting;
}