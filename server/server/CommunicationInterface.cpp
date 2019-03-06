#include"CommunicationInterface.h"

#pragma once

ConnectionInterface::~ConnectionInterface() {
}

uint32_t TCPTransfer::WriteData(stream_data *pStream, int flg)
{
	int dataSizeRemain = pStream->szData;
	int currentPointer = 0;
	int sentByte = 0;
	while (dataSizeRemain > 0)
	{
		sentByte = send(this->s, (char*)pStream->pData + currentPointer, dataSizeRemain, 0);
		dataSizeRemain -= sentByte;
		currentPointer += sentByte;
	}
	return 0;
}
uint32_t TCPTransfer::ReadData(stream_data *pStream, int flg)
{
	int ret = recv(this->s, (char*)&pStream->pData, pStream->szData, flag);
	return ret;
}
boolean TCPTransfer::CloseConnection() {
	return 0;
}
TCPTransfer::TCPTransfer(SOCKET outGoingSocket, sockaddr_in outGoingAddress) {
	this->s = outGoingSocket;
	this->addr = outGoingAddress;
}
/*-----------------------------------------------*/

int TCPListenAccept::Listen()
{
	int result = 0;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(listeningPort);
	if (0 == bind(_socket , (sockaddr*)&(addr ), sizeof(sockaddr)))
	{
		if (0 != listen(_socket, MAXLOOPBACK))
		{
			result = GetLastError();
			printf("\nError %d while Listen port %d  ", result, listeningPort);
		}

		else {
			hostent* roc = gethostbyname("localhost");
			roc = gethostbyname(roc->h_name);
			char*myIP = inet_ntoa(*(in_addr*)roc->h_addr_list[0]);
			printf("\nCreate %s : %d successfully", myIP, listeningPort);
		}
	}
	else
	{
		GetLastError();
	}
	return result;
}

TransferDataInterface *TCPListenAccept::Accept()
{
	int len = sizeof(sockaddr_in);
	TransferDataInterface*tmp = new TCPTransfer(accept(_socket, (sockaddr*)&addr, &len), addr);
	return NULL;
}


TransferDataInterface *TCPListenAccept::Connect(char ip[25], unsigned int port)
{
	SOCKET outGoingSocket = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in outGoingAddress;
	memset(&outGoingAddress, '\0', sizeof(sockaddr_in));
	outGoingAddress.sin_family = AF_INET;
	outGoingAddress.sin_addr.s_addr = inet_addr(ip);
	outGoingAddress.sin_port = htons(port);

	TransferDataInterface * p = new TCPTransfer(outGoingSocket, outGoingAddress);
	if (0 != connect(outGoingSocket, (sockaddr*)&outGoingAddress, sizeof(sockaddr)))
	{
		p = NULL;
		printf("Connect Error %d", GetLastError());
	}

	return p;
}


InitInvironment*InitInvironment::instance;
WSADATA InitInvironment::wsa;



