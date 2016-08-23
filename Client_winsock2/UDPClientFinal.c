//#include "stdafx.h"
//----- Include files ---------------------------------------------------------
#include <stdio.h>          // Needed for printf()
#include <string.h>         // Needed for memcpy() and strcpy()
#include <stdlib.h>         // Needed for exit()
#include <winsock.h>      // Needed for all Winsock stuff
#pragma comment(lib, "Ws2_32.lib")
//----- Defines ---------------------------------------------------------------
#define  PORT_NUM           25000  // Port number used
#define  IP_ADDR      "192.168.10.130" // IP address of server1

//===== Main program ==========================================================
int main()
{
	WORD wVersionRequested = MAKEWORD(1, 1);       // Stuff for WSA functions
	WSADATA wsaData;                              // Stuff for WSA functions
	int                  client_s;        // Client socket descriptor
	struct sockaddr_in   server_addr,local_port;     // Server Internet address
	int                  addr_len;        // Internet address length
	char                 out_buf[256];   // Output buffer for data
	char                 in_buf[256];    // Input buffer for data
	int                  retcode;         // Return code

						 // This stuff initializes winsock
	WSAStartup(wVersionRequested, &wsaData);

	// >>> Step #1 <<<
	// Create a socket
	//   - AF_INET is Address Family Internet and SOCK_DGRAM is datagram
	client_s = socket(AF_INET, SOCK_DGRAM, 0);
	if (client_s < 0)
	{
		printf("*** ERROR - socket() failed \n");
		exit(-1);
	}

	// >>> Step #2 <<<
	// Fill-in server1 socket's address information
	server_addr.sin_family = AF_INET;                 // Address family to use
	server_addr.sin_port = htons(PORT_NUM);           // Port num to use
	server_addr.sin_addr.s_addr = inet_addr(IP_ADDR); // IP address to use
													  // Assign a message to buffer out_buf
	memset(&local_port, 0, sizeof(struct sockaddr_in));
	local_port.sin_family = AF_INET;
	local_port.sin_port = htons(PORT_NUM);

	//strcpy(out_buf, "Test message from CLIENT to SERVER");
	out_buf[0] = 0xff;
	// >>> Step #2.5 <<
	// Bind the socket to the port 25000
	if (bind(client_s, (struct sockaddr *)&local_port, sizeof(local_port)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
	}
	// >>> Step #3 <<<
	// Now send the message to server.  The "+ 1" is for the end-of-string
	// delimiter
	retcode = sendto(client_s, out_buf, (strlen(out_buf) + 1), 0,
		(struct sockaddr *)&server_addr, sizeof(server_addr));
	if (retcode < 0)
	{
		printf("*** ERROR - sendto() failed \n");
		exit(-1);
	}

	// >>> Step #4 <<<
	// Wait to receive a message
	addr_len = sizeof(server_addr);
	retcode = recvfrom(client_s, in_buf, sizeof(in_buf), 0,
		(struct sockaddr *)&server_addr, &addr_len);
	if (retcode < 0)
	{
		printf("*** ERROR - recvfrom() failed \n");
		exit(-1);
	}

	// Output the received message
	printf("Received from server: %s \n", in_buf);

	// >>> Step #5 <<<
	// Close all open sockets
	retcode = closesocket(client_s);
	if (retcode < 0)
	{
		printf("*** ERROR - closesocket() failed \n");
		exit(-1);
	}
	// This stuff cleans-up winsock
	WSACleanup();

	// Return zero and terminate
	return(0);
}
