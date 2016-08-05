#include "UDPClient.h"
#include <iostream>
#include <boost/asio.hpp>
// Examine Received Data Structure

using namespace std;

int main() {
  boost::asio::io_service io;
  string host = "192.168.10.130";
  int port = 25000;
  UDPClient* test = new UDPClient(io, host, port, port);
  int i = 1000000;
  size_t sent, recv;
  while(i-- > 0) {
    sent = test->Send(1, 2, 3, 4, 5.0);
    recv = test->Receive();
  }
  cout << sent
      << " bytes sent to destination"
      << endl
      << recv
      << " bytes received"
      << endl;

  delete test;
  test = NULL;
  return 0;
}
