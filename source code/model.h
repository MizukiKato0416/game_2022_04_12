//=======================================================================
//モデル(xファイル)に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"
#include "x_load.h"
#include "object.h"

//========================================================
//マクロ定義
//========================================================
#define MODEL_MAX_TEXTURE (128)
#define MODEL_VTX		  (8)

//================================================
//クラスの定義
//================================================
//クラスの定義
class CModel
{
public:
	//メンバ関数
	CModel();								//コンストラクタ
	~CModel();								//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXload::X_TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXload::X_TYPE type);
	void SetParent(CModel *pModel);							//親設定処理
	D3DXMATRIX GetMtx(void);								//ワールドマトリックス取得処理
	D3DXMATRIX *GetMtxPoint(void) { return &m_mtxWorld; }	//ワールドマトリックス取得処理
	D3DXVECTOR3 GetSize(void);								//サイズ取得処理
	void SetPos(D3DXVECTOR3 pos);							//モデルの位置設定処理
	D3DXVECTOR3 GetPos(void);								//モデルの位置取得処理
	D3DXVECTOR3 GetVtxPos(int nCntVtx);						//モデルの頂点位置取得処理
	void SetRot(D3DXVECTOR3 rot);							//モデルの向き設定処理
	D3DXVECTOR3 GetRot(void);								//モデルの向き取得処理
	D3DXMATRIX *GetVtxMtxWorld(void);						//ワールドマトリックス取得処理
	void SetVtxMtxWorld(D3DXVECTOR3 vtxPos, int nCntVtx);	//ワールドマトリックス設定処理

private:
	//メンバ関数
	void Collision(void);								//当たり判定

	LPD3DXMESH m_pMesh;									//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER m_pBuffMat;							//マテリアル(材質情報)へのポインタ
	DWORD m_nNumMat;									//マテリアル数
	LPDIRECT3DTEXTURE9 m_pTexture[MODEL_MAX_TEXTURE];	//テクスチャへのポインタ
	D3DXVECTOR3 m_pos;									//ポリゴンの位置
	D3DXVECTOR3	m_size;									//サイズ
	D3DXVECTOR3 m_rot;									//向き
	D3DXMATRIX m_mtxWorld;								//ワールドマトリックス
	D3DXVECTOR3 m_vtxMin;								//モデルの頂点の最小値
	D3DXVECTOR3 m_vtxMax;								//モデルの頂点の最大値
	CModel *m_pParent;									//親のモデル
	D3DXVECTOR3 m_vtxPos[MODEL_VTX];					//8頂点の位置保存用変数
	D3DXVECTOR3 m_vtxRot[MODEL_VTX];					//8頂点の回転保存用変数
	D3DXMATRIX m_vtxMtxWorld[MODEL_VTX];				//8頂点のワールドマトリックス保存用変数
};

#endif // !_MODEL_H_