//===========================================
//3Dポリゴンの床処理
//Author:加藤瑞葵
//===========================================
#ifndef _FLOOR_H_
#define _FLOOR_H_
#include "object3D.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CFloor : public CObject3D
{
public:
	CFloor(int nPriority = PRIORITY_POLYGON_3D);	//コンストラクタ
	~CFloor();										//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CFloor *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);
	static bool Collision(CObject *pObject);			//当たり判定

private:
};

#endif // !_FLOOR_H_