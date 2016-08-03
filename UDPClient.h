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
		UDPClient(boost::asio::io_service& io_service, const string host, const int port);
		~UDPClient();
		// size_t Sned(struct data, boost::asio::buffer send_buffer);
		size_t Send(short s1, short s2, short s3, short s4, double d1);
		// size_t Receive(boost::asio::buff recv_buffer)
		size_t Receive();

  private:
		// Attributes
		string tar_host;
		string tar_port;
		boost::asio::io_service& io_serv;
		// IPv4
		udp::socket sock;
		udp::endpoint sender;
		udp::endpoint dest;
		// Buffer
		// boost::asio::buffer send_buffer;
		// boost::asio::buffer recv_buffer;

		// Private helper methods
		void InitConnection();
		void InitSocket();
		void InitBuffer(); // Need to figure out actual data structure
		udp::resolver::iterator FindEndPoint();

		// Data Structure
		struct PackData {
			short s1, s2, s3, s4;
			double d1;

			// Constructor
			PackData(short a, short b, short c, short d, double e) {
				s1 = a;
				s2 = b;
				s3 = c;
				s4 = d;
				d1 = e;
			}
		};

};

#endif
