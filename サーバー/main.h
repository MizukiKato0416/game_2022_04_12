//==================================================
//
// ���C���w�b�_�[(main.h)
// Author�F�H������
//
//==================================================
#ifndef _MAIN_H_
#define _MAIN_H_
//------------------------
// �C���N���[�h
//------------------------
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

using namespace std;

//------------------------
// �O���錾
//------------------------
class CCommunication;
class CTcpListener;

//------------------------
// �}�N����`
//------------------------
#define MAX_IP_NUM (16)
#define MAX_COMMUDATA (64)

#pragma comment(lib, "ws2_32.lib")

//------------------------
// �v���g�^�C�v�錾
//------------------------
void KeyWait(void);	// �L�[���͑҂�
void Accept(CTcpListener *listener);	// �ڑ��҂�
void RankCommunication(CCommunication *communication);	// �����L���O�ʐM����
void StopOrSurver(void);

#endif // !_MAIN_H_