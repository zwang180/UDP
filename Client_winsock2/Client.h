#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#define WIN32_LEAN_AND_MEAN // Copy from documentation, said could reduce compilation time

#include <winsock2.h>
#include <Windows.h>
#include "DataPack.h"

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

class Client {

  public:
		// Constructor & User Interface
    // Constructor
		Client(string dest_host, int dest_port, int loc_port);
    // Destructor
		~Client();
    // Send data
		size_t Send(DataPack* send);
		// Receive data
		size_t Receive(DataPack* recv);

  private:
		// Class Attributes
    // String tar_host; // Address for remote server
    // int tar_port; // Port for remote server
    // int local_port; // Port for local machine
    WSADATA wsadata; // Stuff for WSA initialization to use winsock2
    SOCKET sock; // Socket
    sockaddr_in dest; // Struct stores information of our destination
    sockaddr_in local; // Struct stores information of our local machine

		// Private helper methods
    void InitSockaddr(sockaddr_in & sockAddr, string host, int port);
};

#endif
