//=============================================================================
//
// �e�N�X�`������ [texture.h]
// Author : �H������
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
// �}�N����`
//=============================================================================
#define PAS_NAME ("data\\TEXTURE\\")	// �p�X�̖��O

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
vector<LPDIRECT3DTEXTURE9> CTexture::m_texture = {};
vector<string> CTexture::m_pas;
pair<vector<string>, vector<string>> CTexture::m_file_name_pas;
map<string, int> CTexture::m_tex_type;
int CTexture::m_num_tex;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
	m_tex_type.clear();
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
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̃|�C���^
	int count_tex = 0;			// �e�N�X�`���J�E���g�l
	int pas_size = sizeof(PAS_NAME) - 1;	// �p�X�̕������T�C�Y
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X���擾����

	// �p�X�̃t�@�C������ǂݍ���
	for (const auto &file : recursive_directory_iterator("data/TEXTURE/"))
	{
		// �p�X�̕ۑ�
		m_file_name_pas.first.push_back(file.path().string());
		m_file_name_pas.second.push_back(file.path().string());

		// �p�X���������Ă���
		if (m_file_name_pas.second[count_tex].find(PAS_NAME) != string::npos)
		{
			for (int count_erase = 0; count_erase < pas_size; count_erase++)
			{
				// �v��Ȃ��Ƃ�����폜
				m_file_name_pas.second[count_tex].erase(m_file_name_pas.second[count_tex].begin());
			}
		}
		// �^���񋓌^�����
		m_tex_type[m_file_name_pas.second[count_tex]] = count_tex;
		count_tex++;
	}

	// �p�X�ƃT�C�Y��ۑ�
	m_pas = m_file_name_pas.first;
	m_num_tex = m_file_name_pas.first.size();

	// �T�C�Y����
	for (int nCntTex = 0; nCntTex < m_num_tex; nCntTex++)
	{
		LPDIRECT3DTEXTURE9 pTexBuffer = NULL;	// �e�N�X�`���̃o�b�t�@
		//�e�N�X�`���̐���
		D3DXCreateTextureFromFile(	pDevice,
									m_pas[nCntTex].c_str(),
									&pTexBuffer);
		// vector�Ɋi�[
		m_texture.push_back(pTexBuffer);
	}
}

//=============================================================================
// �I��
//=============================================================================
void CTexture::Uninit(void)
{
	for (int nCntTexture = 0; nCntTexture < m_num_tex; nCntTexture++)
	{
		// �e�N�X�`���̔j��
		if (m_texture[nCntTexture] != NULL)
		{
			m_texture[nCntTexture]->Release();
			m_texture[nCntTexture] = NULL;
		}
	}
}