#include "UDPClient.h"
#include <boost/asio.hpp>
// issue with or without &

using namespace std;

int main() {
  boost::asio::io_service io;
  string host = "localhost";
  int port = 80;
  UDPClient* test = new UDPClient(io, host, port);
  delete test;
  test = NULL;
  return 0;
}
