//=============================================================================
//
// �e�N�X�`������ [texture.h]
// Author : �H������
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
// �ÓI�����o�ϐ��錾
//=============================================================================
vector<LPDIRECT3DTEXTURE9> CTexture::m_apTexture = {};
vector<string> CTexture::m_aPas;
pair<vector<string>, vector<string>> CTexture::m_File_Name_Pas;
map<string, int> CTexture::m_texType;
int CTexture::m_nNumTex;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
	m_texType.clear();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	int nCount = 0;
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X���擾����

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
		//�e�N�X�`���̐���
		D3DXCreateTextureFromFile(pDevice,
			m_aPas[nCntTex].c_str(),
			&pTexBuffer);

		m_apTexture.push_back(pTexBuffer);
	}
}

//=============================================================================
// �I��
//=============================================================================
void CTexture::Uninit(void)
{
	for (int nCntTexture = 0; nCntTexture < m_nNumTex; nCntTexture++)
	{
		//�e�N�X�`���̔j��
		if (m_apTexture[nCntTexture] != NULL)
		{
			m_apTexture[nCntTexture]->Release();
			m_apTexture[nCntTexture] = NULL;
		}
	}
}