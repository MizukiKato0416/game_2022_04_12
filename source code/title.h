//===========================================
//タイトル処理
//Author:加藤瑞葵
//===========================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "object.h"

//前方宣言
class CObject2D;

//================================================
//マクロ定義
//================================================

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CTitle : public CObject
{
public:
	explicit CTitle(CObject::PRIORITY Priority = CObject::PRIORITY::NONE);		//コンストラクタ
	~CTitle();									//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nTitleCounter;				//リザルトに行くまでのまでの時間
};

#endif // !_TITLE_H_