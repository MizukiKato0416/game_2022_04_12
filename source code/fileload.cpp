//=============================================================================
//
// ファイルロード処理 [fileload.cpp]
// Author : 羽鳥太一
//
//=============================================================================
#pragma warning( disable : 4592)
#include <stdio.h>
#include "fileload.h"

namespace file = experimental::filesystem;
using file::recursive_directory_iterator;

//=============================================================================
// コンストラクタ
//=============================================================================
CFileLoad::CFileLoad()
{
	
}

//=============================================================================
// デストラクタ
//=============================================================================
CFileLoad::~CFileLoad()
{

}

//=============================================================================
// テクスチャの生成
//=============================================================================
pair<vector<string>, vector<string>> CFileLoad::Load(string load_file)
{
	pair<vector<string>, vector<string>> pas_name_buf;	// パスと名前のバッファ
	int count_element = 0;			// 要素カウント様
	int pas_size = load_file.size();	// パスの文字数サイズ

	// パスのファイル名を読み込む
	for (const auto &file : recursive_directory_iterator(load_file))
	{
		// パスの保存
		pas_name_buf.first.push_back(file.path().string());
		pas_name_buf.second.push_back(file.path().string());

		// パスが混ざってたら
		if (pas_name_buf.second[count_element].find(load_file) != string::npos)
		{
			for (int count_erase = 0; count_erase < pas_size; count_erase++)
			{
				// 要らないところを削除
				pas_name_buf.second[count_element].erase(pas_name_buf.second[count_element].begin());
			}
		}
		count_element++;
	}

	return pas_name_buf;
}