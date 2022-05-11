//===========================================
//風エフェクトの処理
//Author:KatoMizuki
//===========================================
#ifndef _WIND_H_
#define _WIND_H_

#include "object.h"
#include "effect3D.h"

//前方宣言

//================================================
//マクロ定義
//================================================
#define WIND_MAX_PATTERN	(8)		//風のアニメーションの数

//================================================
//クラスの定義
//================================================
//クラスの定義
class CWind : public CEffect3D
{
public:
	CWind(CObject::PRIORITY Priority = CObject::PRIORITY::EFFECT3D);		//コンストラクタ
	~CWind();																//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CWind *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const int &nInitTexAnimNum);

private:
	int m_nInitTexAnimNum;					//初期テクスチャアニメーションの番号
	int m_nTexAnimCounter;					//アニメーションカウンター
};

#endif // !_WIND_H_