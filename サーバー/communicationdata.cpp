//====================================================
//
// �R�~���j�P�[�V�����f�[�^�̃w�b�_�[�t�@�C��(communicationdata.cpp)
// Author : �H�� ����
//
//====================================================
//-------------------------------
// �C���N���[�h
//-------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include "communicationdata.h"

//-------------------------------
// �f�t�H���g�R���X�g���N�^
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
// �f�t�H���g�f�X�g���N�^
//-------------------------------
CCommunicationData::~CCommunicationData()
{

}

//-------------------------------
// �\�[�g
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
// �f�[�^�̃Z�[�u
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