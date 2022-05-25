//=============================================================================
//
// トロフィールーム処理 [trophy.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _TROPHY_H_
#define _TROPHY_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTrophy : public CObject
{
public:
	//---------------------------
	// 列挙型
	//---------------------------
	enum class TROPHY
	{
		AIRPLANE = 0,
		FAN,
		REDBULL,
		STARRING,
		THORN,
		ROCKET,
		BANANA,
		TRAMPOLINE,
		M_1000,
		M_5000,
		M_10000,
		MEASUREMENT_IMPOSSIBLE,
		EVENING,
		NIGHT,
		GIRL,
		HARD,
		GROUND,
		PLAY_00,
		PLAY_05,
		PLAY_10,
		STAFFROLL,
		ROCKY_ANGRY,
		KIYO,
		COMPLETE,
		MAX
	};

	CTrophy(PRIORITY priorty = PRIORITY::NONE);	// デフォルトコンストラクタ
	~CTrophy();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画

private:
	CObject2D* m_buck;	// 戻るボタン
	CObject2D *m_letter;	// 説明ポリゴン
	vector<CObject2D*> m_icon;	// アイコン
	vector<TROPHY> m_type;	// 何のトロフィーか
	int m_count_get_trophy;	// trueのトロフィー数
};

#endif // !_TROPHY_H_