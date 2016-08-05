#include "UDPClient.h"
// Debug only, maybe error detection mechanism future
// on both boost code and our function
// Remove cout print statement as you need

using namespace std;
using boost::asio::ip::udp;

// Constructor
UDPClient::UDPClient(boost::asio::io_service& io_service, const string dest_host, const int dest_port, const int loc_port)
    : io_serv(io_service), sock(io_serv) {
  size = sizeof(DataPack);
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
  Prepare();
}

// Destructor, when sock is open, close it
UDPClient::~UDPClient() {
  if(sock.is_open()) {
    sock.close();
    cout << "Close an open socket" << endl;
  }
  cout << "end of the whole world" << endl;
}

// Send data structures to remote server
size_t UDPClient::Send(short s1, short s2, short s3, short s4, double d1) {
  DataPack* msg = new DataPack(s1, s2, s3, s4, d1);
  return sock.send_to(boost::asio::buffer(msg, size), dest);
}

// Receive message from remote server
size_t UDPClient::Receive() {
  DataPack* recv = new DataPack();
  size_t len = sock.receive_from(boost::asio::buffer(recv, size), sender);
  cout << "Receive: " << len << " bytes" << endl;
  cout << recv->s1 << typeid(recv->s1).name() << endl;
  cout << recv->s2 << typeid(recv->s2).name() << endl;
  cout << recv->s3 << typeid(recv->s3).name() << endl;
  cout << recv->s4 << typeid(recv->s4).name() << endl;
  cout << recv->d1 << typeid(recv->d1).name() << endl;
  return len;
}

// Private helper methods
// General Init Method
void UDPClient::Prepare() {
  dest = *FindRemote();
  sender = FindLocal();
  cout << "Send point found "
    << dest
    << "Local point found "
    << sender
    << endl;
  InitSocket();
}

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
  cout << "Socket is Ready :)"
      << sock.local_endpoint()
      << endl;
}
