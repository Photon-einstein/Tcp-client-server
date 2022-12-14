
// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>

#define PORT     8080
#define MAXLINE 1024


/* this function send the clean data into the client and in the end it returns
0 if no error or other value if error */
int receiveDataFromClient();

int main() {
  int statusUdpServer, statusReadFile;
  std::string pathInput = "./../input/input_file.csv", pathCleanOutput = "./../input/input_file_clean.csv";
  statusUdpServer = receiveDataFromClient();
  return 0;
}
/******************************************************************************/
int receiveDataFromClient() {
  int server_sockfd, new_client_socket, valRead, opt = 1;
  char bufferIn[MAXLINE], bufferOut[MAXLINE+24];
  socklen_t cliLength;
  struct sockaddr_in servaddr, clientaddr;

  // Creating socket file descriptor
  if ( (server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
      perror("socket creation failed");
      exit(EXIT_FAILURE);
  }
  // Forcefully attaching socket to the port 8080
  if (setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
      perror("setsockopt error");
      exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));

  // Filling server information
  servaddr.sin_family    = AF_INET; // IPv4
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(PORT);

  // Bind the socket with the server address
  if ( bind(server_sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) {
      perror("bind failed");
      exit(EXIT_FAILURE);
  }
  if (listen(server_sockfd, 3) < 0) {
      perror("listen failed");
      exit(EXIT_FAILURE);
  }
  cliLength = sizeof(clientaddr);
  if ((new_client_socket = accept(server_sockfd, (struct sockaddr*)&clientaddr, &cliLength)) < 0) {
    perror("accept failed");
    exit(EXIT_FAILURE);
  }
  while(1) {
    valRead = read(new_client_socket, bufferIn, MAXLINE);
    bufferIn[valRead] = '\0';
    printf("Received from Client : %s\n", bufferIn);
    sprintf(bufferOut,"OK from Server: \'%s\'", bufferIn);
    send(new_client_socket, bufferOut, strlen(bufferOut), 0);
    if (strcmp(bufferIn, "End Connection") == 0) {
      break;
    }
  }
  return 0;
}
/******************************************************************************/
