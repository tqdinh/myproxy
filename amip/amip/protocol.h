#include<stdint.h>
#include<stdio.h>
#include<Windows.h>

#define DATALEN  255
#pragma pack(1)
struct client_request_server
{
	byte field1;
	byte field2;
	WORD field3;
	DWORD field4;
	byte field5[256];
};

struct server_request_client
{
	byte field1;
	byte field2;
	WORD field3;
	DWORD field4;
	server_request_client()
	{
		ZeroMemory(&field1, sizeof(byte));
		field2 = 0x05a;
	}
};

struct verify_user
{
	char username[DATALEN];
	char password[DATALEN];

};
/*sock 5*/
enum authen_method
{
	no_authen = 0x00,
	GSSAP = 0x01,
	uname_pw = 0x02,
	IANA = 0x03,
	private_use = 0x08
};
enum command
{
	go_home = 0x0111,
	ping_rcv = 0x0222,
	ping_rep = 0x0333
};

////-------------------socks5-------------------------
/**/

/**/struct client_greating_message
{
	byte field1;
	byte field2;
	byte field3;
};
/**/
/**/struct server_choise_communication
{
	uint8_t field1;
	uint8_t  field2;
};
/**/
/**/struct client_authen_Request
{
	WORD field1;
	uint8_t  field2;
	uint8_t  field3;
	uint8_t  field4;
	uint8_t  field5;
};
/**/
/**/struct server_authen_Response
{
	uint8_t      field1;
	uint8_t      field2;
};
/**/
/**/struct client_connect_Request
{
	uint8_t field1;
	uint8_t field2;
	uint8_t field3;
	uint8_t field4;
	uint32_t field5;//ip
	uint16_t field6;//port
};
/**/
/**/struct server_connect_Response
{
	uint8_t field1;
	uint8_t field2;
	uint8_t field3;
	uint8_t field4;
	uint32_t field5;
	uint16_t field6;
};
/**/
struct own_info
{
	WCHAR computer_name[DATALEN];
	WCHAR current_user[DATALEN];
	DWORD LANIP;
	DWORD PID;
	void collect_info()
	{

	}
};

struct proto_message
{
	// use to maping command from attacker , server communication or client execute message
	uint16_t cmd;
	byte reverse[DATALEN];
	DWORD vic_ip;
	DWORD att_ip;
	DWORD req;
	DWORD res;
	sockaddr_in remote_add_connect_to;

};
#pragma pack()

