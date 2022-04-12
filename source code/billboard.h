//===========================================
//3Dポリゴン(ビルボード)処理
//Author:加藤瑞葵
//===========================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "object3D.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CBillboard : public CObject
{
public:
	//ビルボードの処理の種類
	enum class BILLBOARD_MODE
	{
		NONE = 0,
		NORMAL,			//普通のビルボード
		BESIDE_ONLY,	//横にしか動かないビルボード
		MAX
	};

	CBillboard(int nPriority = PRIORITY_POLYGON_3D);	//コンストラクタ
	~CBillboard();										//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillboard *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	D3DXVECTOR3 GetPos(void);								//位置取得処理
	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size);			//位置設定処理
	void SetTex(int nPattern, int nMaxPattern);				//テクスチャアニメーション設定処理
	void SetTex(float fMoveTexU, float fMoveTexV);			//テクスチャ移動設定処理
	void SetCol(D3DCOLORVALUE col);							//カラーバリュー設定処理
	void SetCol(D3DXCOLOR col);								//カラー設定処理
	D3DXCOLOR GetCol(void);									//カラー取得処理
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);			//テクスチャ設定処理
	void SetMode(BILLBOARD_MODE mode) { m_mode = mode; }	//モード設定処理
	BILLBOARD_MODE GetMode(void) { return m_mode; }			//モード取得処理
	void SetCulling(bool bCulling);							//カリング設定処理
	void SetAlphaBlend(bool bAlphaBlend);					//加算合成設定処理
	void SetAlphaTest(bool bAlphaTest);						//αアテスト設定処理
	void SetLighting(bool bLighting);						//ライティング設定処理

private:

protected:
	D3DXVECTOR3 m_pos;							//ポリゴンの位置
	D3DXVECTOR3 m_vtxPos[VERTEX_3D_NUM];		//頂点の位置
	D3DXVECTOR3	m_size;							//サイズ
	D3DXVECTOR3 m_rot;							//向き
	D3DXVECTOR3 m_vtxRot[VERTEX_3D_NUM];		//頂点の向き
	LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;						//ワールドマトリックス
	D3DXMATRIX m_vtxMtxWorld[VERTEX_3D_NUM];	//頂点のワールドマトリックス
	BILLBOARD_MODE m_mode;						//ビルボードの処理の種類
	bool m_bCulling;							//カリングを行うか行わないか
	bool m_bAlphaBlend;							//加算合成するかどうか
	bool m_bAlphaTest;							//αテストするかどうか
	bool m_bLighting;							//ライティング有効かどうか
};

#endif // !_BILLBOARD_H_