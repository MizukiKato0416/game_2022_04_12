//====================================================
//
// �v���C���[�̃w�b�_�[�t�@�C��(tcp_server.h)
// Author : �H�� ����
//
//====================================================
#ifndef _TCP_LISTENER_H_
#define _TCP_LISTENER_H_

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "main.h"
#include "communication.h"

//-------------------------------
// Class�̒�`
//-------------------------------
class CTcpListener
{
public:
	CTcpListener();	// �f�t�H���g�R���X�g���N�^
	~CTcpListener();	// �f�t�H���g�f�X�g���N�^
	bool Init(void);	// ������
	CCommunication *Accept(void);	// �ڑ��҂�
	void Uninit(void);	// �I��
private:
	SOCKET m_sockServer;	// �\�P�b�g
};

#endif // _TCP_CLIENT_H_