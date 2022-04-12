//===========================================
//パッド入力処理
//Author:加藤瑞葵
//===========================================
#ifndef _INPUT_PAD_X_H_
#define _INPUT_PAD_X_H_
#include "input.h"

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
class CInputPadX : public CInput
{
public:
	typedef enum
	{
		TRIGGERTYPE_RIGHT = 0,
		TRIGGERTYPE_LEFT,
		TRIGGERTYPE_MAX
	} TRIGGERTYPE;
	typedef enum
	{
		STICKTYPE_UP = 0,
		STICKTYPE_RIGHT,
		STICKTYPE_LEFT,
		STICKTYPE_DOWN,
		STICKTYPE_MAX
	} STICKTYPE;

	CInputPadX();			//コンストラクタ
	~CInputPadX();			//デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetButtonPress(int nButton, int nCntPad);
	bool GetButtonTrigger(int nButton, int nCntPad);
	bool GetTriggerPress(int nTrigger, int nCntPad);
	bool GetTriggerTrigger(int nTrigger, int nCntPad);
	bool GetLeftStick(int nLstick, int nCntPad);
	bool GetLeftStickTrigger(int nLstick, int nCntPad);
	bool GetLeftStickRelease(int nLstick, int nCntPad);
	bool GetRightStick(int nRstick, int nCntPad);
	void SetVibration(int nLeftSpeed, int nRightSpeed, int nCntEnd, int nCntPad);

private:
	XINPUT_STATE m_astate[XUSER_MAX_COUNT];
	XINPUT_STATE m_astateLast[XUSER_MAX_COUNT];
	XINPUT_VIBRATION m_avibration[XUSER_MAX_COUNT];
	bool m_aConnect[XUSER_MAX_COUNT];
	int m_aCntVibration[XUSER_MAX_COUNT];
	bool m_aVibration[XUSER_MAX_COUNT];
};

#endif // !_INPUT_PAD_X_H_