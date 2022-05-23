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
	static LPDIRECT3DTEXTURE9 GetTexture(const string &texType) { return m_texture[m_tex_type[texType]]; }	// テクスチャの割り当て
	static LPDIRECT3DTEXTURE9 GetTexture(const int &nCnt) { return m_texture[nCnt]; }	// テクスチャの割り当て
	static string GetPas(const int &nCntTex) { return m_pas[nCntTex]; }				// テクスチャのパス取得処理
	static int GetNum(void) { return m_num_tex; }									// テクスチャの総数取得処理
	static bool GetLoadFinish(void) { m_bLoadFinish; }			//読み込み終了したか取得処理

private:
	static vector<LPDIRECT3DTEXTURE9> m_texture;		// テクスチャ
	static vector<string> m_pas;						// テクスチャのパス
	static pair<vector<string>, vector<string>> m_file_name_pas;	// パスと名前の読み込み
	static map<string, int> m_tex_type;					// テクスチャの種類
	static int m_num_tex;								// テクスチャの総数
	static bool m_bLoadFinish;							//読み込みしているかどうか
};

#endif