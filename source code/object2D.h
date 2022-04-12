//===========================================
//2Dポリゴン処理
//Author:加藤瑞葵
//===========================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_
#include "object.h"
#include "main.h"

//================================================
//マクロ定義
//================================================
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//頂点フォーマット
#define VERTEX_NUM (4)												//頂点数

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標
	float rhw;				//1.0fで固定
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//テクスチャ座標
} VERTEX_2D;

//================================================
//クラスの定義
//================================================
//クラスの定義
class CObject2D : public CObject
{
public:
	//ポリゴンの原点の種類
	enum class ORIGIN_TYPE
	{
		CENTER = 0,			//中央
		LEFT,				//左端
		MAX
	};

	CObject2D(CObject::PRIORITY Priority = CObject::PRIORITY::NONE);	//コンストラクタ
	~CObject2D();								//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CObject2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriolty);
	D3DXVECTOR3 GetPos(void);
	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size);					//位置設定処理
	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fRot);		//位置設定処理
	void SetTex(int nPattern, int nMaxPattern);						//テクスチャアニメーション設定処理
	void SetTex(float fMoveTexU, float fMoveTexV);					//テクスチャ移動処理
	void SetCol(D3DCOLORVALUE col);									//カラー設定処理
	void SetCol(D3DXCOLOR col);										//カラー設定処理
	D3DXCOLOR GetCol(void);											//カラー取得処理
	void SetVtx(D3DXVECTOR3 pos, D3DXVECTOR3 vtx0, D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2, D3DXVECTOR3 vtx3);		//頂点設定処理
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);									//テクスチャ設定処理
	void SetOriginType(ORIGIN_TYPE originType) { m_OriginType = originType; }		//原点の種類設定処理

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;						//ポリゴンの位置
	D3DXVECTOR3	m_size;						//サイズ
	ORIGIN_TYPE m_OriginType;				//原点の種類
};

#endif // !_OBJECT2D_H_