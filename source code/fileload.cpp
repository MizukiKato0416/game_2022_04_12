//=============================================================================
//
// �t�@�C�����[�h���� [fileload.cpp]
// Author : �H������
//
//=============================================================================
#pragma warning( disable : 4592)
#include <stdio.h>
#include "fileload.h"

namespace file = experimental::filesystem;
using file::recursive_directory_iterator;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFileLoad::CFileLoad()
{
	
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFileLoad::~CFileLoad()
{

}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
pair<vector<string>, vector<string>> CFileLoad::Load(string load_file)
{
	pair<vector<string>, vector<string>> pas_name_buf;	// �p�X�Ɩ��O�̃o�b�t�@
	int count_element = 0;			// �v�f�J�E���g�l
	int pas_size = load_file.size();	// �p�X�̕������T�C�Y

	// �p�X�̃t�@�C������ǂݍ���
	for (const auto &file : recursive_directory_iterator(load_file))
	{
		// �p�X�̕ۑ�
		pas_name_buf.first.push_back(file.path().string());
		pas_name_buf.second.push_back(file.path().string());

		// �p�X���������Ă���
		if (pas_name_buf.second[count_element].find(load_file) != string::npos)
		{
			for (int count_erase = 0; count_erase < pas_size; count_erase++)
			{
				// �v��Ȃ��Ƃ�����폜
				pas_name_buf.second[count_element].erase(pas_name_buf.second[count_element].begin());
			}
		}
		count_element++;
	}

	return pas_name_buf;
}