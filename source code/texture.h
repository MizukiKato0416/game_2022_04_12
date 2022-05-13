//=============================================================================
//テクスチャ処理
//Author:加藤瑞葵
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "main.h"

//=============================================================================
// クラス定義
//=============================================================================
class CTexture
{
public:
	//メンバ関数
	CTexture();						//コンストラクタ
	~CTexture();					//デストラクタ

	static void Init(void);																// テクスチャの生成
	static void Uninit(void);															// 終了
	static LPDIRECT3DTEXTURE9 GetTexture(const string &texType);					// テクスチャの割り当て
	static LPDIRECT3DTEXTURE9 GetTexture(const int &nCnt) { return m_apTexture[nCnt]; }	// テクスチャの割り当て
	static string GetPas(const int &nCntTex) { return m_aPas[nCntTex]; }			// テクスチャのパス取得処理
	static int GetNum(void) { return m_nNumTex; }										// テクスチャの総数取得処理

private:
	static vector<LPDIRECT3DTEXTURE9> m_apTexture;		//テクスチャ
	static vector<string>	m_aPas;					//テクスチャのパス
	static pair<vector<string>, vector<string>> m_File_Name_Pas;
	static map<string, int> m_texType;					//テクスチャの種類
	static int m_nNumTex;									//テクスチャの総数
};

#endif