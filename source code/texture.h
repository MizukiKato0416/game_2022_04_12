//=============================================================================
//
// �e�N�X�`������ [texture.h]
// Author : �H������
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "fileload.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTexture
{
public:
	CTexture();						//�R���X�g���N�^
	~CTexture();					//�f�X�g���N�^
	static void Init(void);															// �e�N�X�`���̐���
	static void Uninit(void);														// �I��
	static LPDIRECT3DTEXTURE9 GetTexture(const string &texType) { return m_texture[m_file_data.tex_type[texType]]; }	// �e�N�X�`���̊��蓖��
	static LPDIRECT3DTEXTURE9 GetTexture(const int &nCnt) { return m_texture[nCnt]; }	// �e�N�X�`���̊��蓖��
	static string GetPas(const int &nCntTex) { return m_file_data.pas[nCntTex]; }				// �e�N�X�`���̃p�X�擾����
	static int GetNum(void) { return m_num_tex; }									// �e�N�X�`���̑����擾����

private:
	static vector<LPDIRECT3DTEXTURE9> m_texture;		// �e�N�X�`��
	static CFileLoad::FILE_LOAD_DATA m_file_data;
	static int m_num_tex;								// �e�N�X�`���̑���
};

#endif