//====================================================
//
// コミュニケーションデータのヘッダーファイル(communicationdata.cpp)
// Author : 羽鳥 太一
//
//====================================================
//-------------------------------
// インクルード
//-------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include "communicationdata.h"

//-------------------------------
// デフォルトコンストラクタ
//-------------------------------
CCommunicationData::CCommunicationData()
{
	FILE *file;

	for (int count = 0; count < MAX_RANKING + 1; count++)
	{
		m_CommuData.ranking[count] = 0;
	}

	file = fopen("data/ranking.txt", "r");

	for (int count = 0; count < MAX_RANKING; count++)
	{
		fscanf(file, "%d\n", &m_CommuData.ranking[count]);
	}
	fclose(file);
}

//-------------------------------
// デフォルトデストラクタ
//-------------------------------
CCommunicationData::~CCommunicationData()
{

}

//-------------------------------
// ソート
//-------------------------------
void CCommunicationData::RankingSort(int my_score)
{
	vector<int> ranking;
	m_CommuData.ranking[MAX_RANKING] = my_score;

	for (int count = 0; count < MAX_RANKING + 1; count++)
	{
		ranking.push_back(m_CommuData.ranking[count]);
	}

	sort(ranking.begin(), ranking.end(), std::greater<int>{});

	for (int count = 0; count < MAX_RANKING + 1; count++)
	{
		m_CommuData.ranking[count] = ranking[count];
	}
}

//-------------------------------
// データのセーブ
//-------------------------------
void CCommunicationData::Save(void)
{
	FILE *file;

	file = fopen("data/ranking.txt", "w");

	for (int count = 0; count < MAX_RANKING; count++)
	{
		fprintf(file, "%d\n", m_CommuData.ranking[count]);
	}
	fclose(file);
}