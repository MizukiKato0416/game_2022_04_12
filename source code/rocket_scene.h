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
class CBg;
class CScore;

//================================================
//マクロ定義
//================================================
#define ROCKET_SCENE_BG_NUM		(4)			//背景の数

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
	void Score(void);			//スコア処理
	void Camera(void);			//カメラ処理

	CPlayer *m_pPlayer;						//プレイヤーのポインタ
	CModelSingle *m_pRocket;				//ロケットのポインタ
	CBg *m_apBg[ROCKET_SCENE_BG_NUM];		//背景のポインタ
	CScore *m_pScore;						//スコアのポインタ
	bool m_bResult;							//リザルトに行くかどうか
	int m_nCounter;							//リザルトに行くカウンター
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_ROCKET_SCENE_H_