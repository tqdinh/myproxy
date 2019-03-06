#include"CommunicationInterface.h"

#pragma once
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
uint32_t TCPTransfer::ReadData(stream_data *pStream,int flg)
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
ConnectionInterface*TCPListenAccept::Listen(int port)
{
	
	return NULL;
	
}
TransferDataInterface *TCPListenAccept::Accept(char ip[25], unsigned int port)
{
	return NULL;
}

TransferDataInterface *TCPConnect::Connect(char ip[25], unsigned int port)
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

TCPListenAccept *TCPListenAccept::instance;
InitInvironment*InitInvironment::instance;
WSADATA InitInvironment::wsa;
