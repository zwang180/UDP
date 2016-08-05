#include "UDPClient.h"
#include "DataPack.h"
// Maybe error detection mechanism future
// on both boost code and our function

using namespace std;
using boost::asio::ip::udp;

// Constructor
UDPClient::UDPClient(boost::asio::io_service& io_service, const string dest_host, const int dest_port, const int loc_port)
    : io_serv(io_service), sock(io_serv) {
  size = sizeof(DataPack);
  tar_host = dest_host;
  tar_port = to_string(dest_port);
  local_port = loc_port;
}

// Destructor, when sock is open, close it
UDPClient::~UDPClient() {
  if(sock.is_open()) {
    sock.close();
  }
}

// Init all needed staff for client side
void UDPClient::Init() {
  // Find both local & remote endpoints
  dest = *FindRemote();
  sender = FindLocal();
  // Init socket
  InitSocket();
}

// Send data structures to remote server
size_t UDPClient::Send(DataPack* send) {
  return sock.send_to(boost::asio::buffer(send, size), dest);
}

// Receive message from remote server
size_t UDPClient::Receive(DataPack* recv) {
  return sock.receive_from(boost::asio::buffer(recv, size), sender);
}

// Private helper methods
// Find remote endpoint based on host and port
udp::resolver::iterator UDPClient::FindRemote() {
  udp::resolver resolver(io_serv);
  udp::resolver::query query(udp::v4(), tar_host, tar_port);
  return resolver.resolve(query);
}

// Find local endpoint
udp::endpoint UDPClient::FindLocal() {
  return udp::endpoint(udp::v4(), local_port);
}

// Open IPv4 socket
void UDPClient::InitSocket() {
  sock.open(udp::v4());
  sock.bind(sender);
}
