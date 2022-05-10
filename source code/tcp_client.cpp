//====================================================
//
// �v���C���[�̃w�b�_�[�t�@�C��(tcp_client.cpp)
// Author : �H�� ����
//
//====================================================
//-------------------------------
// �C���N���[�h
//-------------------------------
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include "tcp_client.h"

//-------------------------------
// �f�t�H���g�R���X�g���N�^
//-------------------------------
CTcpClient::CTcpClient()
{
	m_socket = INVALID_SOCKET;
}

//-------------------------------
// �f�t�H���g�f�X�g���N�^
//-------------------------------
CTcpClient::~CTcpClient()
{

}

//-------------------------------
// ������
//-------------------------------
bool CTcpClient::Init(void)
{
	FILE *pFile;
	char aFile[2][64];

	//------------------------
	// ������
	//------------------------
	WSADATA  wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);

	if (nErr != 0)
	{
		cout << "�������Ɏ��s���܂���" << endl;
	}

	pFile = fopen("data/Txtdata/severdata.txt", "r");

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(aFile[0], "PORT_NUM") == 0) // PORT_NUM�̕��������������
			{
				fscanf(pFile, "%s", &aFile[1]);
				fscanf(pFile, "%d", &m_nPort);
			}
			if (strcmp(aFile[0], "IP_NUM") == 0) // MAX_WAIT�̕��������������
			{
				fscanf(pFile, "%s", &aFile[1]);
				fscanf(pFile, "%s", m_Ip.c_str());
			}
			if (strcmp(aFile[0], "END_SCRIPT") == 0) //END_SCRIPT�̕��������������
			{
				break;
			}
		}
	}
	else
	{
		printf("�T�[�o�[�f�[�^���ǂݎ��܂���ł����B");
	}

	fclose(pFile);

	//------------------------
	// �\�P�b�g�쐬
	//------------------------
	m_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (m_socket == INVALID_SOCKET)
	{
		printf("�ڑ��҂��\�P�b�g�����܂���ł����B");
		return false;
	}

	return true;
}

//-------------------------------
// �ʐM
//-------------------------------
bool CTcpClient::Connect(void)
{
	//------------------------
	// �ڑ��ݒ�
	//------------------------
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;	// �ǂ̒ʐM��
	addr.sin_port = htons(m_nPort);	// �|�[�g�ԍ�
	addr.sin_addr.S_un.S_addr = inet_addr(m_Ip.c_str());

	//------------------------
	// �ڑ�
	//------------------------
	if (connect(m_socket, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{
		printf("�ڑ��ł��܂���ł����B\n");
		return false;
	}
	else
	{
		printf("�ڑ��o���܂����B\n");
		return true;
	}
}

//-------------------------------
// ���M
//-------------------------------
int CTcpClient::Send(char *pSendData, int nSendDataSize)
{
	int nRecvSize = send(m_socket, pSendData, nSendDataSize, 0);	// �ǂ̃\�P�b�g, ����, ���o�C�g, �ʐM�̎��
	if (nRecvSize < 0)
	{
		Uninit();
	}

	return nRecvSize;
}

//-------------------------------
// ��M
//-------------------------------
int CTcpClient::Recv(char *pRecvData, int nRecvDataSize)
{
	memset(pRecvData, 0, sizeof(pRecvData));
	int nRecvSize = recv(m_socket, pRecvData, nRecvDataSize, 0);	// �ǂ̃\�P�b�g, �ǂ���, �ő�e��, �ʐM�̎��

	return nRecvSize;
}

//-------------------------------
// �I��
//-------------------------------
void CTcpClient::Uninit(void)
{
	if (m_socket == INVALID_SOCKET)
	{
		return;
	}

	//------------------------
	// �ڑ��ؒf
	//------------------------
	// ��ʏ���
	system("cls");

	printf("�ڑ���ؒf���܂��B\n");
	closesocket(m_socket);	// �ڑ���t�p�\�P�b�g
	m_socket = INVALID_SOCKET;
}