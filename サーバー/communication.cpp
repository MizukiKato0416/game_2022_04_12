//====================================================
//
// �v���C���[�̃w�b�_�[�t�@�C��(tcp_client.cpp)
// Author : �H�� ����
//
//====================================================
//-------------------------------
// �C���N���[�h
//-------------------------------
#include "communication.h"

//-------------------------------
// �f�t�H���g�R���X�g���N�^
//-------------------------------
CCommunication::CCommunication()
{
	m_socket = INVALID_SOCKET;
}

//-------------------------------
// �f�t�H���g�f�X�g���N�^
//-------------------------------
CCommunication::~CCommunication()
{

}

//-------------------------------
// �I�[�o�[���[�hInit(�ڑ��ς݃\�P�b�g)
//-------------------------------
bool CCommunication::Init(SOCKET sock)
{
	m_socket = sock;

	return true;
}

//-------------------------------
// ���M
//-------------------------------
int CCommunication::Send(char *pSendData, int nSendDataSize)
{
	int nSize = send(m_socket, pSendData, nSendDataSize, 0);	// ������, ����, ���o�C�g, �ʐM�̎��

	return nSize;
}

//-------------------------------
// ��M
//-------------------------------
int CCommunication::Recv(char *pRecvData, int nRecvDataSize)
{
	memset(pRecvData, 0, sizeof(pRecvData));

	int nSize = recv(m_socket, pRecvData, nRecvDataSize, 0);

	return nSize;
}

//-------------------------------
// �I��
//-------------------------------
void CCommunication::Uninit(void)
{
	if (m_socket == INVALID_SOCKET)
	{
		return;
	}

	//------------------------
	// �ڑ��ؒf
	//------------------------
	closesocket(m_socket);	// �ڑ���t�p�\�P�b�g
	m_socket = INVALID_SOCKET;
}