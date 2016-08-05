#ifndef UDPCLIENT_H
#define UDPCLIENT_H
#include <iostream>
#include <boost/array.hpp>
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
    // Send data
		size_t Send(short s1, short s2, short s3, short s4, double d1);
		// Receive data
		size_t Receive();

  private:
		// Attributes
    size_t size;
		string tar_host;
		string tar_port;
    int local_port;
    // I/O Service
		boost::asio::io_service& io_serv;
		// IPv4
		udp::socket sock;
		udp::endpoint sender;
		udp::endpoint dest;

		// Private helper methods
		void Prepare();
		void InitSocket();
		udp::resolver::iterator FindRemote();
    udp::endpoint FindLocal();

		// Data Structure
		struct DataPack {
			short s1, s2, s3, s4;
			double d1;

      // Constructor 1
      DataPack() {
        // Nothing here
      };
			// Constructor 2
			DataPack(short a, short b, short c, short d, double e) {
				s1 = a;
				s2 = b;
				s3 = c;
				s4 = d;
				d1 = e;
			};
		};

};

#endif
