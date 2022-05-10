//==================================================
//
// メインCPP(main.cpp)
// Author：羽鳥太一
//
//==================================================
//------------------------
// インクルード
//------------------------
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <thread>
#include "main.h"
#include "tcp_listener.h"
#include "communication.h"
#include "communicationdata.h"

//------------------------
// グローバル変数
//------------------------
int g_accept_count = 0;
int g_stop = 1;

//------------------------
// メイン関数
//------------------------
void main(void)
{
#ifdef _DEBUG
	int size = sizeof(CCommunicationData::COMMUNICATION_DATA);
#endif // _DEBUG
	//------------------------
	// 初期化
	//------------------------
	WSADATA  wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);

	if (nErr != 0)
	{
		cout << "初期化に失敗しました" << endl;
	}

	CTcpListener *pListenner = new CTcpListener;

	if (pListenner != NULL && pListenner->Init() == true)
	{
		thread th(StopOrSurver);

		th.detach();
		while (pListenner != NULL)
		{
			if (g_accept_count <= 4)
			{
				thread th(Accept, pListenner);

				th.detach();
			}
			if (g_stop == 0)
			{
				break;
			}
		}
	}
	if (pListenner != NULL)
	{
		pListenner->Uninit();
		delete pListenner;
		pListenner = NULL;
	}

	//------------------------
	// 終了
	//------------------------
	cout << "終了します。"<< endl;
	cout << "何かキーを押してください。"<< endl;
	KeyWait();
	WSACleanup();
}

//------------------------
// 接続待ち
//------------------------
void Accept(CTcpListener *listener)
{
	CCommunication *communication;

	g_accept_count++;
	communication = listener->Accept();
	cout << "g_accept_count->" << g_accept_count << endl;

	thread th(RankCommunication, communication);

	th.detach();
}

//------------------------
// ランキング送信受信
//------------------------
void RankCommunication(CCommunication *communication)
{
	CCommunicationData commu_data;
	CCommunicationData::COMMUNICATION_DATA *data = commu_data.GetCommuData();
	char recv_data[MAX_COMMUDATA];
	char send_data[MAX_COMMUDATA];
	int my_score;

	communication->Recv(&recv_data[0], sizeof(int));

	memcpy(&my_score, recv_data, sizeof(int));
	commu_data.RankingSort(my_score);
	memcpy(&send_data, &data->ranking, sizeof(CCommunicationData::COMMUNICATION_DATA::ranking));

	communication->Send(&send_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA::ranking));

	commu_data.Save();
	communication->Uninit();
	g_accept_count--;
	cout << "g_accept_count->" << g_accept_count << endl;
}

//------------------------
// 選択処理
//------------------------
void StopOrSurver(void)
{
	cin >> g_stop;
}

//------------------------
// キー入力待ち
//------------------------
void KeyWait(void)
{
	rewind(stdin);
	getchar();
}