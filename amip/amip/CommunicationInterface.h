
#define DATALEN  255
#define SOL_SOCKET      0xffff          /* options for socket level */

#include<Windows.h>
#include<stdint.h>
#include<stdio.h>

#pragma comment(lib,"Ws2_32.lib")
using namespace std;
extern CRITICAL_SECTION server_cs;
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
	virtual uint32_t WriteData(stream_data *pStream,int flag=0) = 0;
	virtual uint32_t ReadData(stream_data *pStream,int flag= 0x8) = 0;
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
	uint32_t ReadData(stream_data *pStream, int flag =0x8);
	boolean CloseConnection();
};
/*-----------------------Transfer-----------------------*/


static class InitInvironment
{
private :
	static InitInvironment * instance;
	static WSADATA wsa;
	InitInvironment(){
		WSAStartup(MAKEWORD(2, 2),&wsa);
	}
	~InitInvironment()
	{
		WSACleanup();
	}
public :
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
	virtual ConnectionInterface*Listen(int port) = 0;
	virtual TransferDataInterface *Accept(char ip[25], unsigned int port) = 0;
	virtual TransferDataInterface *Connect(char ip[25], unsigned int port) = 0;
	
};
static class TCPListenAccept:public ConnectionInterface
{
private:
	 SOCKET s;
	 sockaddr_in addr;
	 static TCPListenAccept *instance;
	 TCPListenAccept()
	 {
	 }
public:
	ConnectionInterface*Listen(int port);
	TransferDataInterface *Accept(char ip[25], unsigned int port);
	TransferDataInterface *Connect(char ip[25], unsigned  int port)
	{
		return 0;
	}

	static TCPListenAccept *getInstance()
	{
		if (instance == nullptr)
		{
			EnterCriticalSection(&server_cs);
			if (nullptr == instance)
			{
				instance = new TCPListenAccept();
			}
			LeaveCriticalSection(&server_cs);
		}
		return instance;
	}
	
};



class TCPConnect
{
public:
	TransferDataInterface *Connect(char ip[25], unsigned int port);
};
/*-----------------------Communication-----------------------*/

