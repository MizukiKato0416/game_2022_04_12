//=============================================================================
//�e�N�X�`������
//Author:��������
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
//�ÓI�����o�ϐ��錾
//================================================
vector<LPDIRECT3DTEXTURE9> CTexture::m_apTexture = {};
vector<string> CTexture::m_aPas;
pair<vector<string>, vector<string>> CTexture::m_File_Name_Pas;
map<string, int> CTexture::m_texType;
int CTexture::m_nNumTex = 0;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
	m_texType.clear();
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
//�e�N�X�`���̐���
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X���擾����

	/*//text�t�@�C���ǂݍ���
	FILE *pFile = fopen("data/TEXTURE/texPas/texPas.txt", "r");
	if (pFile != NULL)
	{
		char cString[128];
		//��s���ۑ�
		while (fgets(cString, 128, pFile) != NULL)
		{
			//�������ۑ�
			fscanf(pFile, "%s", cString);
			//������̒���TEX_NUM����������
			if (strncmp("TEX_NUM", cString, 8) == 0)
			{
				//�e�N�X�`���ő吔�ǂݍ���
				fscanf(pFile, "%*s%d", &m_nNumTex);

				int nNum = 0;
				//��s���ۑ�
				while (fgets(cString, 128, pFile) != NULL)
				{
					//�������ۑ�
					fscanf(pFile, "%s", cString);
					//������̒���PAS����������
					if (strncmp("PAS", cString, 4) == 0)
					{
						//�p�X�̎擾
						fscanf(pFile, "%*s%s", &cString[0]);
						m_aPas.push_back(&cString[0]);

						//���O�̎擾
						fscanf(pFile, "%*s%*s%s", cString);
						//���O�Ɛ��̊��蓖��
						m_texType[cString] = nNum;
						nNum++;
					}
				}
			}
		}
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���\n");
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
		//�e�N�X�`���̐���
		D3DXCreateTextureFromFile(pDevice,
			m_aPas[nCntTex].c_str(),
			&pTexBuffer);

		m_apTexture.push_back(pTexBuffer);
	}
}

//=============================================================================
//�I��
//=============================================================================
void CTexture::Uninit(void)
{
	int nNumTex = m_File_Name_Pas.first.size();
	for (int nCntTexture = 0; nCntTexture < nNumTex; nCntTexture++)
	{
		//�e�N�X�`���̔j��
		if (m_apTexture[nCntTexture] != NULL)
		{
			m_apTexture[nCntTexture]->Release();
			m_apTexture[nCntTexture] = NULL;
		}
	}
}

//=============================================================================
//�e�N�X�`�����蓖��
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(const std::string &texType)
{
	return m_apTexture[m_texType[texType]];
}