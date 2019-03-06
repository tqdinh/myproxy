#include"CommunicationInterface.h"
#include "protocol.h"
CRITICAL_SECTION server_cs;
CRITICAL_SECTION serverInit;
#define TESTIP "10.187.52.240"
#define TESTPORT 8080

bool Sock5CommunicatePostRemote(TransferDataInterface * CI_src, uint32_t &remoteIP, uint16_t &remotePORT)
{
	while (true) {
		client_greating_message greating_message = { 0x05,0x01,0x00 };
		stream_data  streamGreating = { (void*)&greating_message,sizeof(client_greating_message) };
		CI_src->WriteData((stream_data*)&streamGreating);

		server_choise_communication server_choise_communicate = { 0 };
		stream_data  streamChoiseCommunicate = { (void*)&server_choise_communicate,sizeof(server_choise_communication) };
		int ret1 = CI_src->ReadData((stream_data*)&streamChoiseCommunicate);
		if (0 != GetLastError() || ret1 != sizeof(server_choise_communication))
		{
			break;
		}
		client_connect_Request client_connect_ = { 0x05,0x01,0x00,0x01,remoteIP,remotePORT };
		stream_data streamConnectRequest = { (void*)&client_connect_,sizeof(client_connect_Request) };
		CI_src->WriteData((stream_data*)&streamConnectRequest);

		server_connect_Response server_connect_ = { 0 };
		stream_data streamServerConnectResponse = { (void*)&server_connect_,sizeof(server_connect_Response) };
		int ret2 = CI_src->ReadData((stream_data*)&streamServerConnectResponse);
		if (0 != GetLastError() || ret2 != sizeof(server_connect_Response)) {
			break;
		}
		return true;
	}
	return false;
}
void main()
{
	InitializeCriticalSection(&server_cs);
	InitializeCriticalSection(&serverInit);
	InitInvironment::getInstance();
	//TCPListenAccept* server=TCPListenAccept::getInstance();
	hostent* p= gethostbyname("rb-proxy-apac.bosch.com");
	TCPConnect * pConnect = new TCPConnect();	
	TransferDataInterface* data=pConnect->Connect(TESTIP, TESTPORT);
	uint32_t remoteIP = inet_addr(TESTIP);
	uint16_t remotePORT = htons(TESTPORT);
	Sock5CommunicatePostRemote(data, remoteIP, remotePORT);
	stream_data testingData;
//	memset((void*)&testingData, '\0', sizeof(testingData));
//	char *pdata = "1!@#$#@FD";
//	testingData.pData = pdata;
//	testingData.szData = strlen(pdata);
//	data->WriteData((stream_data*)&testingData);
//
//	stream_data testingDataRcv;
//	memset((void*)&testingDataRcv, '\0', sizeof(testingDataRcv));
//	data->ReadData((stream_data*)&testingDataRcv);
//	delete pConnect;
}