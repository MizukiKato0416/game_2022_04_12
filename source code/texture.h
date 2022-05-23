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
	static LPDIRECT3DTEXTURE9 GetTexture(const string &texType) { return m_texture[m_tex_type[texType]]; }	// �e�N�X�`���̊��蓖��
	static LPDIRECT3DTEXTURE9 GetTexture(const int &nCnt) { return m_texture[nCnt]; }	// �e�N�X�`���̊��蓖��
	static string GetPas(const int &nCntTex) { return m_pas[nCntTex]; }				// �e�N�X�`���̃p�X�擾����
	static int GetNum(void) { return m_num_tex; }									// �e�N�X�`���̑����擾����
	static bool GetLoadFinish(void) { m_bLoadFinish; }			//�ǂݍ��ݏI���������擾����

private:
	static vector<LPDIRECT3DTEXTURE9> m_texture;		// �e�N�X�`��
	static vector<string> m_pas;						// �e�N�X�`���̃p�X
	static pair<vector<string>, vector<string>> m_file_name_pas;	// �p�X�Ɩ��O�̓ǂݍ���
	static map<string, int> m_tex_type;					// �e�N�X�`���̎��
	static int m_num_tex;								// �e�N�X�`���̑���
	static bool m_bLoadFinish;							//�ǂݍ��݂��Ă��邩�ǂ���
};

#endif