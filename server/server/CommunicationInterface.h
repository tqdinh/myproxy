#define MAXSOCKETLISTEN   1024
#define DATALEN  255
#define SOL_SOCKET      0xffff          /* options for socket level */

#include<Windows.h>
#include<stdint.h>
#include<stdio.h>

#pragma comment(lib,"Ws2_32.lib")
using namespace std;

extern CRITICAL_SECTION serverInit;
struct stream_data
{
	void * pData;
	uint32_t szData;

};

/*-----------------------Transfer-----------------------*/
class TransferDataInterface
{
public:
	virtual uint32_t WriteData(stream_data *pStream, int flag = 0) = 0;
	virtual uint32_t ReadData(stream_data *pStream, int flag = 0x8) = 0;
	virtual boolean CloseConnection() = 0;
};

class TCPTransfer :public TransferDataInterface
{
private:
	uint16_t usec;
	SOCKET s;
	sockaddr_in addr;
	unsigned int flag;
public:
	TCPTransfer(SOCKET outGoingSocket, sockaddr_in outGoingAddress);
	uint32_t WriteData(stream_data *pStream, int flag = 0);
	uint32_t ReadData(stream_data *pStream, int flag = 0x8);
	boolean CloseConnection();
};
/*-----------------------Transfer-----------------------*/


static class InitInvironment
{
private:
	static InitInvironment * instance;
	static WSADATA wsa;
	InitInvironment() {
		WSAStartup(MAKEWORD(2, 2), &wsa);
	}
	~InitInvironment()
	{
		WSACleanup();
	}
public:
	static InitInvironment * getInstance()
	{
		if (instance == nullptr)
		{
			EnterCriticalSection(&serverInit);
			if (nullptr == instance)
			{
				instance = new InitInvironment();
			}
			LeaveCriticalSection(&serverInit);
		}
		return instance;
	}
	
};

/*-----------------------Communication-----------------------*/
class ConnectionInterface
{
public:

	virtual int Listen() = 0;

	virtual TransferDataInterface *Accept() = 0;
	virtual TransferDataInterface *Connect(char ip[25], unsigned int port) = 0;
	virtual ~ConnectionInterface() = 0;


};
class TCPListenAccept :public ConnectionInterface
{
private:
	unsigned int MAXLOOPBACK = 1024;
	 SOCKET _socket ;
	 sockaddr_in addr;
	 int listeningPort;
	
public:
	
	
	int Listen();

	TransferDataInterface *Accept();
	TransferDataInterface *Connect(char ip[25], unsigned int port);
	TCPListenAccept(int listenPort)
	{
		listeningPort = listenPort;
		_socket = socket(AF_INET, SOCK_STREAM, 0);
	}
	~TCPListenAccept()
	{

	}
	
};

/*-----------------------Communication-----------------------*/

