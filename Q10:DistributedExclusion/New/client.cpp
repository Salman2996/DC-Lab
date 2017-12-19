#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

int main() {
  int sockfd, cs;
  socklen_t len;
  struct sockaddr_in client;
  char buf[50], buf1[50];
  client.sin_family = AF_INET;
  client.sin_addr.s_addr = inet_addr("127.0.0.1");
  client.sin_port = htons(5005);
  while (1) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(sockfd, (struct sockaddr *)&client, sizeof(client));
    cout << "\nConnected to server\n";
    recv(sockfd, buf1, 50, 0);
    if (strcmp(buf1, "LOCKED") == 0) {
      cout << "Could not attain Mutual Exclusion\nStatus:" << buf1 << endl;
      cout << "Going to sleep\n";
      sleep(5);
    } else {
      cout << "Mutual Exlusion\nStatus: " << buf1 << endl;
      cout << "Enter message: ";
      fgets(buf, 50, stdin);
      send(sockfd, buf, 50, 0);
      recv(sockfd, buf1, 50, 0);
      cout << "Message from server: " << buf1;
      break;
    }
    close(sockfd);
  }
  return 0;
}
