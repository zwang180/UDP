#include "UDPClient.h"
#include "DataPack.h"
#include <iostream>
#include <boost/asio.hpp>
// Examine Received Data Structure

using namespace std;

int main() {
  // Start an I/O Service
  boost::asio::io_service io;
  // Declare host and ports
  string host = "192.168.10.130";
  int port = 25000;
  int loc_port = port;

  // Start a client & init it
  // UDPClient(boost::asio::io_service& io_service, const string dest_host, const int dest_port, const int loc_port)
  UDPClient* client = new UDPClient(io, host, port, loc_port);
  client->Init();

  // Send & Receive
  // int i = 1000000;
  // size_t sent, recv;

  // while(i-- > 0) {

  DataPack* d_send = new DataPack(7, 2, 4, 100, 7.625);
  // sent =
  client->Send(d_send);

  DataPack* d_recv = new DataPack();
  // recv =
  client->Receive(d_recv);
  // }
  cout << d_recv->s1 << d_recv->s2 << d_recv->s3 << d_recv->s4 << d_recv->d1 << endl;
  // Clean up after use
  delete client;
  client = NULL;

  return 0;
}
