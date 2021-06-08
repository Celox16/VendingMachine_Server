#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERPORT	9000
#define BUFSIZE		1024

#define DRINK_SIZE	5
#define MONEY_SIZE	5

//////////define variables and functions///////////
struct drinkInfo {
	char name[20];
	int price;
	int count;
};

struct moneyInfo {
	int value;
	int count;
};

extern void SetInitial(drinkInfo initialDrink[], moneyInfo initialMoney[]);
extern void ModifyDrinkInfo(drinkInfo originDrink[], drinkInfo modifyDrink[]);
extern void ModifyMoneyInfo(moneyInfo originMoney[], moneyInfo modifyMoney[]);



drinkInfo originDrink[DRINK_SIZE];
moneyInfo originMoney[MONEY_SIZE];
///////////////////////////////////////////////////

// 소켓 함수 오류 출력후 종료
void err_quit(char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

//소켓 함수 오류 출력
void err_display(char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[ % s] % s", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// 클라이언트와 데이터 통신
DWORD WINAPI ProcessClient(LPVOID arg)
{
	SOCKET client_sock = (SOCKET)arg; // drink socket
	int retval; // drink retval
	SOCKADDR_IN clientaddr;
	int addrlen;
	int buf[BUFSIZE + 1];

	////// from client data /////////
	drinkInfo fromClientDrink[DRINK_SIZE];
	moneyInfo fromClientMoney[MONEY_SIZE];

	SetInitial(originDrink, originMoney);

	// 클라이언트 정보 얻기
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen); // getpeername - drink

	while (1) {
		// data receive drink array data
		retval = recv(client_sock, (char*)&fromClientDrink, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("drink receive");
			break;
		}
		else if (retval == 0)
			break;
		printf("recv\n");

		// send drink array data to client
		retval = send(client_sock, (char*)&fromClientDrink, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("money data send");
			break;
		}
		printf("send\n");

		// data receive money array data
		retval = recv(client_sock, (char*)&fromClientMoney, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("money receive");
			break;
		}
		else if (retval == 0)
			break;
		printf("recv2\n");
		
		// origin data를 client 정보에서 받아온 데이터에 대입해주기
		ModifyDrinkInfo(fromClientDrink, originDrink);
		ModifyMoneyInfo(fromClientMoney, originMoney);

		// 받은 데이터 출력
		buf[retval] = '\0';
		printf("[TCP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port), fromClientDrink);

		// send money array data to client
		retval = send(client_sock, (char*)&fromClientMoney, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("money data send");
			break;
		}
		printf("send2\n");
	}

	//closesocket
	closesocket(client_sock);
	printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	return 0;
}

int main(int argc, char* argv[])
{
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// 데이터 통신에 사용할 변수
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread;

	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		// 접속한 클라이언트 정보 출력
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		// 스레드 생성
		hThread = CreateThread(NULL, 0, ProcessClient,
			(LPVOID)client_sock, 0, NULL);
		if (hThread == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread); }
	}

	//closesocket
	closesocket(listen_sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}