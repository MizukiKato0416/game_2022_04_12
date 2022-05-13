//=============================================================================
//
// テクスチャ処理 [texture.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTexture
{
public:
	CTexture();						//コンストラクタ
	~CTexture();					//デストラクタ
	static void Init(void);															// テクスチャの生成
	static void Uninit(void);														// 終了
	static LPDIRECT3DTEXTURE9 GetTexture(const string &texType) { m_apTexture[m_texType[texType]]; }	// テクスチャの割り当て
	static LPDIRECT3DTEXTURE9 GetTexture(const int &nCnt) { return m_apTexture[nCnt]; }	// テクスチャの割り当て
	static string GetPas(const int &nCntTex) { return m_aPas[nCntTex]; }			// テクスチャのパス取得処理
	static int GetNum(void) { return m_nNumTex; }									// テクスチャの総数取得処理
private:
	static vector<LPDIRECT3DTEXTURE9> m_apTexture;		// テクスチャ
	static vector<string>	m_aPas;						// テクスチャのパス
	static pair<vector<string>, vector<string>> m_File_Name_Pas;	// パスと名前の読み込み
	static map<string, int> m_texType;					// テクスチャの種類
	static int m_nNumTex;								// テクスチャの総数
};

#endif