#include "UDPClient.h"
// Debug only, maybe error detection mechanism future
// on both boost code and our function
// #include <exception>
using namespace std;
using boost::asio::ip::udp;

// Constructor
UDPClient::UDPClient(boost::asio::io_service& io_service, const string host, const int port) : io_serv(io_service), sock(io_serv) {
  tar_host = host;
  tar_port = to_string(port);
  cout << "Representing Host "
      << host
      << " with port "
      << port
      << endl;
  InitConnection();
}

// Destructor, when sock is open, close it
UDPClient::~UDPClient() {
  if(sock.is_open()) {
    sock.close();
    cout << "Close an open socket" << endl;
  }
  cout << "end of the whole world" << endl;
}

// Send message to server
// size_t UDPClient::Send(short s1, short s2, short s3, short s4, double d1) {
//   boost::array<char, 1> send_buf  = {{ 0 }};
//   return sock.send_to(boost::asio::buffer(send_buf), dest);
// }

// Receive message from server
size_t UDPClient::Receive() {
  boost::array<char, 128> recv_buf;
  size_t len = sock.receive_from(boost::asio::buffer(recv_buf), sender);

  cout.write(recv_buf.data(), len);
  return len;
}

// Private helper methods
// General Init method
void UDPClient::InitConnection() {
  dest = *FindEndPoint();
  // sender will be used later in receive function
  cout << "Send point found "
    << dest
    << endl;
  InitSocket();
  InitBuffer();
}

// Find Endpoint based on host and port
udp::resolver::iterator UDPClient::FindEndPoint() {
  udp::resolver resolver(io_serv);
  udp::resolver::query query(udp::v4(), tar_host, tar_port);
  return resolver.resolve(query);
}

// Open IPv4 socket
void UDPClient::InitSocket() {
  sock.open(udp::v4());
  cout << "Socket is Ready :)" << endl;
}

// Allocate proper sized buff
void UDPClient::InitBuffer() {
  // Need to figure out
  cout << "Buffer is Ready :)" << endl;
}
