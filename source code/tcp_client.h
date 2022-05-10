//====================================================
//
// �v���C���[�̃w�b�_�[�t�@�C��(tcp_client.h)
// Author : �H�� ����
//
//====================================================
#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "main.h"

#pragma comment(lib, "ws2_32.lib")

//-------------------------------
// Class�̒�`
//-------------------------------
class CTcpClient
{
public:
	CTcpClient();	// �f�t�H���g�R���X�g���N�^
	~CTcpClient();	// �f�t�H���g�f�X�g���N�^
	bool Init(void);	// ������(IP�A�h���X, �|�[�g�ԍ�)
	bool Connect(void);	// �ڑ�
	int Send(char *pSendData, int nSendDataSize);	// ���M(���M�f�[�^�i�[��, ���M�f�[�^�T�C�Y)
	int Recv(char *pRecvData, int nRecvDataSize);	// ��M(��M�f�[�^�i�[��, ��M�f�[�^�i�[��ő�T�C�Y)
	void Uninit(void);	// �I��
private:
	SOCKET m_socket;	// �\�P�b�g
	string m_Ip;	// IP�A�h���X
	int m_nPort;	// �|�[�g�ԍ�
};

#endif // _TCP_CLIENT_H_