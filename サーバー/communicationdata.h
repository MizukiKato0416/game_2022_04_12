//====================================================
//
// コミュニケーションデータのヘッダーファイル(communicationdata.h)
// Author : 羽鳥 太一
//
//====================================================
#ifndef _COMUNICASION_DATA_H_
#define _COMUNICASION_DATA_H_

//-------------------------------
// インクルード
//-------------------------------
#include "main.h"
#include "d3dx9.h"

//-------------------------------
// マクロ定義
//-------------------------------
#define MAX_RANKING (6)

//-------------------------------
// Classの定義
//-------------------------------
class CCommunicationData
{
public:
	typedef struct
	{
		int ranking[MAX_RANKING + 1];
	} COMMUNICATION_DATA;
	CCommunicationData();	// デフォルトコンストラクタ
	~CCommunicationData();	// デフォルトデストラクタ
	COMMUNICATION_DATA *GetCommuData(void) { return &m_CommuData; }	// データのセッター
	void SetCommuData(COMMUNICATION_DATA Data) { m_CommuData = Data; }	// データのゲッダー
	void RankingSort(int my_score);
	void Save(void);	// データのセーブ
private:
	SOCKET m_socket;	// ソケット
	COMMUNICATION_DATA m_CommuData;	// データ
};

#endif // _TCP_CLIENT_H_