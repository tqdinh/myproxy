#include"CommunicationInterface.h"
#include "protocol.h"


//static sockaddr_in addr[MAXSOCKETLISTEN];
//static TCPListenAccept *instance;


CRITICAL_SECTION serverInit;
#pragma comment(lib,"Ws2_32.lib")

using namespace std;
void main()
{


	InitializeCriticalSection(&serverInit);
	InitInvironment::getInstance();
	ConnectionInterface * server0 = new TCPListenAccept(9988);
	server0->Listen();
	server0->Accept();
	
	ConnectionInterface * server1 = new TCPListenAccept(9989);
	server1->Listen();
	server1->Accept();

	ConnectionInterface * server2 = new TCPListenAccept(9990);
	server2->Listen();
	server2->Accept();

	ConnectionInterface * server3 = new TCPListenAccept(9991);
	server3->Listen();
	server3->Accept();
	Sleep(-1);
	delete server0;
	delete server1;
	delete server2;
	delete server3;
}