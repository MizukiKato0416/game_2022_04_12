//===========================================
//キーボード入力処理
//Author:加藤瑞葵
//===========================================
#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_
#include "input.h"

//================================================
//マクロ定義
//================================================
#define NUM_KEY_MAX (256)		//キーの最大数


//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();				//コンストラクタ
	~CInputKeyboard();			//デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];			//キーボードの入力情報
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];			//キーボードの入力情報
};

#endif // !_INPUT_KEYBOARD_H_