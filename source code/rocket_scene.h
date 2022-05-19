//===========================================
//ロケットシーン処理
//Authore:加藤瑞葵
//===========================================
#ifndef _ROCKET_SCENE_H_
#define _ROCKET_SCENE_H_
#include "object.h"

//前方宣言
class CPlayer;
class CModelSingle;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CRocketScene : public CObject
{
public:
	CRocketScene();				//コンストラクタ
	~CRocketScene();				//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CPlayer *m_pPlayer;			//プレイヤーのポインタ
	CModelSingle *m_pRocket;	//ロケットのポインタ
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_ROCKET_SCENE_H_