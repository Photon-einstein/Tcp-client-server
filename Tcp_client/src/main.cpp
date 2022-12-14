// Client side implementation of UDP client-server model
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
#include <bits/stdc++.h>
#include <string>

#define PORT     8080
#define MAXLINE 1024

int sendDataToServer(const std::string &pathCleanInput);

int main() {
  int statusUdpClient, statusReadFile;
  std::string pathInput = "./../input/input_file.csv", pathCleanOutput = "./../input/input_file_clean.csv";
  statusUdpClient = sendDataToServer(pathCleanOutput);
  if (statusUdpClient != 0) {
    std::cout<<"There was an error in the function \'receiveDataFromServer\'"<<std::endl;
  }
  return 0;
}
/******************************************************************************/
int sendDataToServer(const std::string &pathCleanInput) {
  int client_sockfd, client_fd, valread;
  char bufferIn[MAXLINE+10], bufferOut[MAXLINE], endConnection[35]="End Connection";
  std::string lineRead;
  std::ifstream inputFileStream(pathCleanInput, std::ios_base::in);
  struct sockaddr_in     servaddr;
  if (inputFileStream.is_open() == false) {
    std::cout<<"File \'"<<pathCleanInput<<"\' failed to be opened"<<std::endl;
    return 1;
  }
  // Creating socket file descriptor
  if ( (client_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
      perror("socket creation failed");
      exit(EXIT_FAILURE);
  }
  memset(&servaddr, 0, sizeof(servaddr));
  // Filling server information
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  // Convert IPv4 and IPv6 addresses from text to binary form
  if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0) {
      perror("\nInvalid address/ Address not supported \n");
      return -1;
  }
  if ((client_fd = connect(client_sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) < 0) {
    perror("\nConnection Failed \n");
    return -1;
  }
  while(inputFileStream.good()) {
    memset(&bufferOut, 0, sizeof(bufferOut));
    std::getline(inputFileStream, lineRead);
    if (lineRead.size() == 0) {
      continue;
    }
    strcpy(bufferOut, lineRead.c_str());
    send(client_sockfd, bufferOut, strlen(bufferOut), 0);
    printf("Send message: \t\'%s\'\n", bufferOut);
    valread = read(client_sockfd, bufferIn, MAXLINE+10);
    bufferIn[valread] = '\0';
    printf("\t\'%s\'\n", bufferIn);
  }
  /* end connection with server */
  send(client_sockfd, endConnection, strlen(endConnection), 0);
  printf("Send message: \t\'%s\'\n", endConnection);
  close(client_sockfd);
  return 0;
}
/******************************************************************************/
