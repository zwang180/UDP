#ifndef UDPCLIENT_H
#define UDPCLIENT_H
#include "DataPack.h"
#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::udp;

class UDPClient {

  public:
		// Constructor & User Interface
    // Constructor
		UDPClient(boost::asio::io_service& io_service, const string dest_host, const int dest_port, const int loc_port);
    // Destructor
		~UDPClient();
    // Init all needed staff, call before send & Receive
    void Init();
    // Send data
		size_t Send(DataPack* send);
		// Receive data
		size_t Receive(DataPack* recv);

  private:
		// Attributes
    size_t size;
		string tar_host;
		string tar_port;
    int local_port;
    // I/O Service
		boost::asio::io_service& io_serv;
		// IPv4 Socket & Endpoints
		udp::socket sock;
		udp::endpoint sender;
		udp::endpoint dest;

		// Private helper methods
		void InitSocket();
		udp::resolver::iterator FindRemote();
    udp::endpoint FindLocal();
};

#endif
