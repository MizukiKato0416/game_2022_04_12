//===========================================
//メニュー処理
//Authore:加藤瑞葵
//===========================================
#ifndef _MENU_H_
#define _MENU_H_
#include "object.h"
#include "main.h"

//前方宣言
class CObject2D;

//================================================
//マクロ定義
//================================================
#define MENU_UI_START_SIZE_X			(304.0f)	//STARTのUIのサイズX
#define MENU_UI_START_SIZE_Y			(84.0f)		//STARTのUIのサイズY
#define MENU_UI_EXIT_SIZE_X				(304.0f)	//EXITのUIのサイズX
#define MENU_UI_EXIT_SIZE_Y				(84.0f)		//EXITのUIのサイズY
#define MENU_UI_NOT_SELECT_COLOR_ALPHA	(0.4f)		//選択されていないときのUIのα値

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMenu : public CObject
{
public:
	CMenu();				//コンストラクタ
	~CMenu();				//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	//選択肢
	typedef enum
	{
		SELECT_MENU_TYPE_NONE = 0,
		SELECT_MENU_TYPE_TUTORIAL,		//Tutorial
		SELECT_MENU_TYPE_GAME_START,	//GameStart
		SELECT_MENU_TYPE_EXIT,			//Exit
		SELECT_MENU_TYPE_MAX			//選択肢最大値
	} SELECT_MENU_TYPE;

	int m_nSelect;										//選択肢
	CObject2D *m_apObject2D[SELECT_MENU_TYPE_MAX];		//UI
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_MENU_H_