#include "Client.h"
// Remove DataPack include if you change the way of sending data
#include "DataPack.h"
// #include <iostream>
/** Note that my code do not offer error checking, manually add print or
 * error throw statement AND uncomment the above include statement if you
 * need to debug
 */

using namespace std;

/** Constructor, use information provided by the user to create the object that represents the client
 * Put all initialize code here, i.e. those code that should only run once when you create this Client
 */
Client::Client(string dest_host, int dest_port, int loc_port) {
  // Initializes winsock2 stuff
  WSAStartup(MAKEWORD(2, 2), &wsaData);

  // If you would like to store information inside the class for future
  // tar_host = dest_host;
  // tar_port = dest_port;
  // local_port = loc_port;

  // Initializes UDP IPv4 socket
  sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  // Initializes the sockaddr_in struct represents the remote sever
  InitSockaddr(dest, dest_host, dest_port);

  // Initializes the sockaddr_in struct represents the local port
  InitSockaddr(local, "127.0.0.1", loc_port); // 127.0.0.1 refer to localhost

  // Bind the socket to local port
  bind(sock, (SOCKADDR *) &local, sizeof(local));
}

// Put all cleans-up code here, memory to free, clean-up function to call and etc. No need to call this manually
Client::~Client() {
  // Close the socket
  closesocket(sock);
  // Clean-up winsock2 stuff
  WSACleanup();
}

// Send data, modifiy this function however you like to make the buffer work
size_t Client::Send(DataPack* send) {
  // Don't think this will work, all other paramters are correct, except the buff and its size
  // Change it to your way
  return sendto(sock, (char *) send, sizeof(send), 0, (SOCKADDR *) &dest, sizeof(dest));
}

// Receive data, modifiy this function however you like to make the buffer work
size_t Client::Receive(DataPack* recv) {
  // Don't think this will work, all other paramters are correct, except the buff and its size
  // Change it to your way
  return recvfrom(sock, (char *) recv, sizeof(recv), 0, (SOCKADDR *) &local, sizeof(local));
}

// Private methods, you can not and do not need to call this function directly
/* Use this to initialize IPv4 sockaddr_in sturct
 * @param sockaddr_in sockAddr, the sockaddr_in struct you would like to initialize
 * @param string host, host name/IP address as string
 * @param int port, host port as int
 **/
// Remove this function and put these code twice (for both local and remote sockaddr_in
// struct the Constructor will do the same thing, you can do this if you would prefer
// that way or this function is not working
void Client::InitSockaddr(sockaddr_in & sockAddr, string host, int port) {
  sockAddr.sin_family = AF_INET; // Set address family to IPv4
  sockAddr.sin_addr.s_addr = inet_addr(host); // Set IP address
  sockAddr.sin_port = htons(Port); // Set port
}
