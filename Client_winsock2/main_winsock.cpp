#include "Client.h"
// #include <iostream>
/** Note that my code do not offer error checking, manually add print or
 * error throw statement AND uncomment the above include statement if you
 * need to debug
 **/

using namespace std;

int main() {
  // This is just a demo to show you how to use Client class, don't think it will
  // actually work if you don't figure out the buffer to send or receive data

  // Declare host and ports
  string host = "192.168.10.130";
  int port = 25000;
  int loc_port = port;

  // Start a client
  Client* client = new Client(host, port, loc_port);

  // Send & Receive
  // Send buffer, change the size depend on your need, dynamic array can be done
  char send_buffer[256];
  // Send data, it will return how many bytes you have sent if succeed
  client->Send(send_buffer);

  // Receive buffer, change the size depend on your need, dynamic array can be done
  char recv_buffer[256];
  // Receive data, it will return how many bytes you have received if succeed
  client->Receive(recv_buffer);

  // Print out the data you receive, change it according to your buffer design
  // cout << d_recv->s1 << d_recv->s2 << d_recv->s3 << d_recv->s4 << d_recv->d1 << endl;
  // Clean up the object and the pointer, delete statement will automatically
  // call the Destructor to close the socket and clean-up winsock2 stuff
  delete client;
  client = NULL;

  return 0;
}
