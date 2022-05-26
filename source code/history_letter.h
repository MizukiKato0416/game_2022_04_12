//=============================================================================
//
// 実績文字処理 [trophy.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _HISTORY_LETTER_H_
#define _HISTORY_LETTER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "object.h"
#include "input_keyboard.h"
#include "trophy.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CHistory : public CObject
{
public:
	CHistory(PRIORITY priorty = PRIORITY::HISTORY_LETTER);	// デフォルトコンストラクタ
	~CHistory();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	static CHistory *Create(CTrophy::TROPHY type);

private:
	CObject2D *m_history;// 実績
	CTrophy::TROPHY m_type;	// 実績の種類
	static bool m_in_object;	// でてきてる実績があるか
	int m_cout_stop;		// 止まる秒数
	bool m_stop;		// 止まってるか
	bool m_in_or_out;	// でてきてるか消えてるか
	bool m_history_in;	// 自分がでてきてるか

};

#endif // !_HISTORY_LETTER_H_