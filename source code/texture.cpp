//=============================================================================
//テクスチャ処理
//Author:加藤瑞葵
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4592)
#include <stdio.h>
#include "texture.h"
#include "renderer.h"
#include "manager.h"

namespace file = experimental::filesystem;
using file::recursive_directory_iterator;

//================================================
//静的メンバ変数宣言
//================================================
vector<LPDIRECT3DTEXTURE9> CTexture::m_apTexture = {};
vector<string> CTexture::m_aPas;
pair<vector<string>, vector<string>> CTexture::m_File_Name_Pas;
map<string, int> CTexture::m_texType;
int CTexture::m_nNumTex = 0;

//=============================================================================
//コンストラクタ
//=============================================================================
CTexture::CTexture()
{
	m_texType.clear();
}

//=============================================================================
//デストラクタ
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
//テクスチャの生成
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスを取得する

	/*//textファイル読み込み
	FILE *pFile = fopen("data/TEXTURE/texPas/texPas.txt", "r");
	if (pFile != NULL)
	{
		char cString[128];
		//一行ずつ保存
		while (fgets(cString, 128, pFile) != NULL)
		{
			//文字列を保存
			fscanf(pFile, "%s", cString);
			//文字列の中にTEX_NUMがあったら
			if (strncmp("TEX_NUM", cString, 8) == 0)
			{
				//テクスチャ最大数読み込み
				fscanf(pFile, "%*s%d", &m_nNumTex);

				int nNum = 0;
				//一行ずつ保存
				while (fgets(cString, 128, pFile) != NULL)
				{
					//文字列を保存
					fscanf(pFile, "%s", cString);
					//文字列の中にPASがあったら
					if (strncmp("PAS", cString, 4) == 0)
					{
						//パスの取得
						fscanf(pFile, "%*s%s", &cString[0]);
						m_aPas.push_back(&cString[0]);

						//名前の取得
						fscanf(pFile, "%*s%*s%s", cString);
						//名前と数の割り当て
						m_texType[cString] = nNum;
						nNum++;
					}
				}
			}
		}
	}
	else
	{
		printf("ファイルが開けませんでした\n");
	}
	fclose(pFile);*/

	int nCount = 0;

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

	int nNumTex = m_File_Name_Pas.first.size();
	for (int nCntTex = 0; nCntTex < nNumTex; nCntTex++)
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
//終了
//=============================================================================
void CTexture::Uninit(void)
{
	int nNumTex = m_File_Name_Pas.first.size();
	for (int nCntTexture = 0; nCntTexture < nNumTex; nCntTexture++)
	{
		//テクスチャの破棄
		if (m_apTexture[nCntTexture] != NULL)
		{
			m_apTexture[nCntTexture]->Release();
			m_apTexture[nCntTexture] = NULL;
		}
	}
}

//=============================================================================
//テクスチャ割り当て
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(const std::string &texType)
{
	return m_apTexture[m_texType[texType]];
}