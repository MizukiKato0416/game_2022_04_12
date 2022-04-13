//===========================================
//モデル単体を出す処理
//Author:加藤瑞葵
//===========================================
#ifndef _MODEL_SINGLE_H_
#define _MODEL_SINGLE_H_
#include "object.h"
#include "x_load.h"

//前方宣言
class CModel;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CModelSingle : public CObject
{
public:
	//メンバ関数
	CModelSingle(CObject::PRIORITY Priority = CObject::PRIORITY::MODEL);				//コンストラクタ
	~CModelSingle();											//デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CModelSingle *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const CXload::X_TYPE &type, CModel *&pParent, const bool &Collision);
	static bool SimpleCollision(CObject *&pObject);	//回転させたらダメな当たり判定
	static bool Collision(CObject *pObject);		//y軸を回転させていい当たり判定
	static bool CollisionAny(CObject *&pObject);		//ただの衝突判定

private:
	//メンバ変数
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3	m_size;					//サイズ
	D3DXVECTOR3 m_rot;					//向き
	D3DXVECTOR3 m_move;					//移動量
	CModel *m_pModel;					//モデルのポインタ
	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
	CModel *m_pParent;					//親モデルへのポインタ
	CXload::X_TYPE m_type;				//出すモデルの種類
	bool m_bCollision;					//当たり判定をするかどうか
};

#endif // !_MODEL_SINGLE_H_