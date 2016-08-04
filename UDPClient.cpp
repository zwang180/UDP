#include "UDPClient.h"
// Debug only, maybe error detection mechanism future
// on both boost code and our function
// #include <exception>
using namespace std;
using boost::asio::ip::udp;

// Constructor
UDPClient::UDPClient(boost::asio::io_service& io_service, const string dest_host, const int dest_port, const int loc_port)
    : io_serv(io_service), sock(io_serv) {
  size = sizeof(PackData);
  cout << "Data Sturcture Size: "
      << size
      << " bytes"
      << endl;
  tar_host = dest_host;
  tar_port = to_string(dest_port);
  local_port = loc_port;
  cout << "Representing Host "
      << dest_host
      << " with port "
      << dest_port
      << " and Local Port "
      << local_port
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
size_t UDPClient::Send(short s1, short s2, short s3, short s4, double d1) {
  PackData* msg = new PackData(s1, s2, s3, s4, d1);
  return sock.send_to(boost::asio::buffer(msg, size), dest);
}

// Receive message from server
size_t UDPClient::Receive() {
  PackData* recv = new PackData();
  size_t len = sock.receive_from(boost::asio::buffer(recv, size), sender);
  cout << "Receive: " << len << endl;
  cout << recv->s1 << recv->s2 << recv->s3 << recv->s4 << recv->d1 << endl;
  return len;
}

// Private helper methods
// General Init method
void UDPClient::InitConnection() {
  dest = *FindEndPoint();
  sender = udp::endpoint(udp::v4(), local_port);
  cout << "Send point found "
    << dest
    << "Local point found "
    << sender
    << endl;
  InitSocket();
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
  sock.bind(sender);
  cout << "Socket is Ready :)"
      << sock.local_endpoint()
      << endl;
}
