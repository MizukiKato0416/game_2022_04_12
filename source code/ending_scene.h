//===========================================
//エンディングシーン処理
//Authore:加藤瑞葵
//===========================================
#ifndef _ENDING_SCENE_H_
#define _ENDING_SCENE_H_
#include "object.h"

//前方宣言
class CObject2D;
class CNextDialogUI;
class CDialog;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CEndingScene : public CObject
{
public:
	CEndingScene();				//コンストラクタ
	~CEndingScene();				//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CObject2D *m_pObject2D;				//object2Dのポインタ
	CNextDialogUI *m_pNextDialogUI;		//次のセリフに行くUIのポインタ
	CDialog *m_pDialog;					//会話のポインタ
	int m_nConter;						//フレームカウンター
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_ENDING_SCENE_H_