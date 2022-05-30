//=============================================================================
//
// テクスチャ処理 [texture.h]
// Author : 羽鳥太一
//
//=============================================================================
#pragma warning( disable : 4592)
#include <stdio.h>
#include "texture.h"
#include "renderer.h"
#include "manager.h"

namespace file = experimental::filesystem;
using file::recursive_directory_iterator;

//=============================================================================
// マクロ定義
//=============================================================================
#define PAS_NAME ("data\\TEXTURE\\")	// パスの名前

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
vector<LPDIRECT3DTEXTURE9> CTexture::m_texture = {};
vector<string> CTexture::m_pas;
pair<vector<string>, vector<string>> CTexture::m_file_name_pas;
map<string, int> CTexture::m_tex_type;
int CTexture::m_num_tex;

//=============================================================================
// コンストラクタ
//=============================================================================
CTexture::CTexture()
{
	m_tex_type.clear();
}

//=============================================================================
// デストラクタ
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// テクスチャの生成
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// デバイスのポインタ
	int count_tex = 0;			// テクスチャカウント様
	int pas_size = sizeof(PAS_NAME) - 1;	// パスの文字数サイズ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスを取得する

	// パスのファイル名を読み込む
	for (const auto &file : recursive_directory_iterator("data/TEXTURE/"))
	{
		// パスの保存
		m_file_name_pas.first.push_back(file.path().string());
		m_file_name_pas.second.push_back(file.path().string());

		// パスが混ざってたら
		if (m_file_name_pas.second[count_tex].find(PAS_NAME) != string::npos)
		{
			for (int count_erase = 0; count_erase < pas_size; count_erase++)
			{
				// 要らないところを削除
				m_file_name_pas.second[count_tex].erase(m_file_name_pas.second[count_tex].begin());
			}
		}
		// 疑似列挙型を作る
		m_tex_type[m_file_name_pas.second[count_tex]] = count_tex;
		count_tex++;
	}

	// パスとサイズを保存
	m_pas = m_file_name_pas.first;
	m_num_tex = m_file_name_pas.first.size();

	// サイズ分回す
	for (int nCntTex = 0; nCntTex < m_num_tex; nCntTex++)
	{
		LPDIRECT3DTEXTURE9 pTexBuffer = NULL;	// テクスチャのバッファ
		//テクスチャの生成
		D3DXCreateTextureFromFile(	pDevice,
									m_pas[nCntTex].c_str(),
									&pTexBuffer);
		// vectorに格納
		m_texture.push_back(pTexBuffer);
	}
}

//=============================================================================
// 終了
//=============================================================================
void CTexture::Uninit(void)
{
	for (int nCntTexture = 0; nCntTexture < m_num_tex; nCntTexture++)
	{
		// テクスチャの破棄
		if (m_texture[nCntTexture] != NULL)
		{
			m_texture[nCntTexture]->Release();
			m_texture[nCntTexture] = NULL;
		}
	}
}