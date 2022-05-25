//===========================================
//次のセリフに行くUI処理
//Authore:加藤瑞葵
//===========================================
#ifndef _NEXT_DILOG_UI_H_
#define _NEXT_DILOG_UI_H_
#include "object2D.h"

//前方宣言

//================================================
//マクロ定義
//================================================
#define NEXT_DILOG_UI_SIZE		(36.0f)		//NEXT_DILOG_UIのサイズ
#define NEXT_DILOG_UI_POS_X		(1180.0f)	//NEXT_DILOG_UIの位置X
#define NEXT_DILOG_UI_POS_Y		(680.0f)	//NEXT_DILOG_UIの位置Y

//================================================
//クラスの定義
//================================================
//クラスの定義
class CNextDialogUI : public CObject2D
{
public:
	//NEXT_DILOG_UIの種類
	enum class TYPE
	{
		NONE = 0,
		PRESS_START,	//PRESSSTART
		MAX
	};

	CNextDialogUI(CObject::PRIORITY Priority = CObject::PRIORITY::NEXT_DIALOG_UI);	//コンストラクタ
	~CNextDialogUI();								//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CNextDialogUI *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);

private:
	float m_fRotation;			//回転値
	int m_nCounter;				//消えてから表示させるまでのカウンター
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_NEXT_DILOG_UI_H_