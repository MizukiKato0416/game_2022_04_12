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
#include "fileload.h"

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
	int element_max;		// テクスチャカウント様
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスを取得する

	// ファイルを読み込む
	m_file_name_pas = CFileLoad::Load("data\\TEXTURE\\");
	element_max = m_file_name_pas.second.size();

	for (int count_element = 0; count_element < element_max; count_element++)
	{
		// 疑似列挙型を作る
		m_tex_type[m_file_name_pas.second[count_element]] = count_element;
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