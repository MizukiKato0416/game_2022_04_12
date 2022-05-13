//=============================================================================
//
// テクスチャ処理 [texture.h]
// Author : 羽鳥太一
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4592)
#include <stdio.h>
#include "texture.h"
#include "renderer.h"
#include "manager.h"

namespace file = experimental::filesystem;
using file::recursive_directory_iterator;

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
vector<LPDIRECT3DTEXTURE9> CTexture::m_apTexture = {};
vector<string> CTexture::m_aPas;
pair<vector<string>, vector<string>> CTexture::m_File_Name_Pas;
map<string, int> CTexture::m_texType;
int CTexture::m_nNumTex;

//=============================================================================
// コンストラクタ
//=============================================================================
CTexture::CTexture()
{
	m_texType.clear();
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
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	int nCount = 0;
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスを取得する

	for (const auto &file : recursive_directory_iterator("data/TEXTURE/"))
	{
		m_File_Name_Pas.first.push_back(file.path().string());
		m_File_Name_Pas.second.push_back(file.path().string());

		if (m_File_Name_Pas.second[nCount].find("data\\TEXTURE\\") != string::npos)
		{
			for (int count_erase = 0; count_erase < 13; count_erase++)
			{
				m_File_Name_Pas.second[nCount].erase(m_File_Name_Pas.second[nCount].begin());
			}
		}
		m_texType[m_File_Name_Pas.second[nCount]] = nCount;
		nCount++;
	}

	m_aPas = m_File_Name_Pas.first;
	m_nNumTex = m_File_Name_Pas.first.size();

	for (int nCntTex = 0; nCntTex < m_nNumTex; nCntTex++)
	{
		LPDIRECT3DTEXTURE9 pTexBuffer = NULL;
		//テクスチャの生成
		D3DXCreateTextureFromFile(pDevice,
			m_aPas[nCntTex].c_str(),
			&pTexBuffer);

		m_apTexture.push_back(pTexBuffer);
	}
}

//=============================================================================
// 終了
//=============================================================================
void CTexture::Uninit(void)
{
	for (int nCntTexture = 0; nCntTexture < m_nNumTex; nCntTexture++)
	{
		//テクスチャの破棄
		if (m_apTexture[nCntTexture] != NULL)
		{
			m_apTexture[nCntTexture]->Release();
			m_apTexture[nCntTexture] = NULL;
		}
	}
}