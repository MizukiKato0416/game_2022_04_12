//=============================================================================
// ヒットエフェクトの動きの処理
// Author:加藤瑞葵
//=============================================================================
#ifndef _CONTROL_UI_SUBTRACT_ALPHA_H_
#define _CONTROL_UI_SUBTRACT_ALPHA_H_
#include "control.h"

//前方宣言
class CObject;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CControlUiSubtractAlpha : public CControl
{
public:
	//メンバ関数
	CControlUiSubtractAlpha();			//コンストラクタ	
	~CControlUiSubtractAlpha();			//デストラクタ	

	HRESULT Init(const CObject *pObject);
	void Uninit(void);					
	void Update(const CObject *pObject);
	static CControlUiSubtractAlpha *Create(const CObject *pObject, const float &fSubtractAlpha, const int &nDelay);

private:
	float m_fSubtractAlpha;		//α値減算値
	int m_nDelay;				//ディレイ
	int m_nDelayCounter;		//ディレイのカウンター
};

#endif	//_CONTROL_UI_SUBTRACT_ALPHA_H_