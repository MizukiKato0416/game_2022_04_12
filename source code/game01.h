//===========================================
//ゲーム処理
//Author:加藤瑞葵
//===========================================
#ifndef _GAME01_H_
#define _GAME01_H_
#include "object.h"
#include "main.h"

//前方宣言
class CPlayer;
class CFloor;
class CRoad;

//================================================
//マクロ定義
//================================================
#define GAME01_MAX_ROAD		(2)		//道の最大数

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
class CGame01 : public CObject
{
public:
	CGame01(CObject::PRIORITY Priority = CObject::PRIORITY::NONE);		//コンストラクタ
	~CGame01();									//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	//メンバ変数
	CPlayer *m_pPlayer;					//プレイヤーのポインタ
	CFloor *m_pFloor;					//床のポインタ
	CRoad *m_apRoad[GAME01_MAX_ROAD];	//道のポインタ
};

#endif // !_GAME01_H_