//====================================================
//
// �R�~���j�P�[�V�����f�[�^�̃w�b�_�[�t�@�C��(communicationdata.h)
// Author : �H�� ����
//
//====================================================
#ifndef _COMUNICASION_DATA_H_
#define _COMUNICASION_DATA_H_

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "main.h"
#include "d3dx9.h"

//-------------------------------
// �}�N����`
//-------------------------------
#define MAX_RANKING (6)

//-------------------------------
// Class�̒�`
//-------------------------------
class CCommunicationData
{
public:
	typedef struct
	{
		int ranking[MAX_RANKING + 1];
	} COMMUNICATION_DATA;
	CCommunicationData();	// �f�t�H���g�R���X�g���N�^
	~CCommunicationData();	// �f�t�H���g�f�X�g���N�^
	COMMUNICATION_DATA *GetCommuData(void) { return &m_CommuData; }	// �f�[�^�̃Z�b�^�[
	void SetCommuData(COMMUNICATION_DATA Data) { m_CommuData = Data; }	// �f�[�^�̃Q�b�_�[
	void RankingSort(int my_score);
	void Save(void);	// �f�[�^�̃Z�[�u
private:
	SOCKET m_socket;	// �\�P�b�g
	COMMUNICATION_DATA m_CommuData;	// �f�[�^
};

#endif // _TCP_CLIENT_H_