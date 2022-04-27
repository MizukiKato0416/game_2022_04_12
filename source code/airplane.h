//===========================================
//飛行機の処理
//Author:KatoMizuki
//===========================================
#ifndef _AIRPLANE_H_
#define _AIRPLANE_H_

#include "happening.h"

//前方宣言
class CEffect3D;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CAirplane : public CHappenig
{
public:
	CAirplane(CObject::PRIORITY Priority = CObject::PRIORITY::HAPPENING);		//コンストラクタ
	~CAirplane();																//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CAirplane *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);



private:
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_rot;						//向き
};

#endif // !_AIRPLANE_H_