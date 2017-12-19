// g++ server.cpp -lpthread -o server
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

using namespace std;

struct thread_data {
  int sockfd;
  int cs;
  bool status;
};

void *responseFunction(void *threaddata) {
  thread_data *data = (thread_data *)threaddata;
  int sockfd = data->sockfd;
  int cs = data->cs;
  char buf[50];
  if (!data->status) {
    char statusBuffer[50] = "UNLOCKED";
    send(cs, statusBuffer, 50, 0);
    data->status = true;
    cout << "Mutex: "
         << "LOCKED\n";
    cout << "Client Connected\n";
    recv(cs, buf, 50, 0);
    cout << "Message Received: " << buf;
    cout << "Enter message to send: ";
    fgets(buf, 50, stdin);
    send(cs, buf, 50, 0);
    close(cs);
    data->status = false;
    cout << "Mutex: "
         << "UNLOCKED\n\n";
  } else {
    char statusBuffer[50] = "LOCKED";
    send(cs, statusBuffer, 50, 0);
    close(cs);
  }
  pthread_exit(NULL);
}

int main() {
  int sockfd, cs;
  socklen_t len;
  bool status = false;
  struct sockaddr_in server, client;
  vector<pthread_t> threads;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  cout << "Socket created sucessfully" << endl;
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(5005);
  bind(sockfd, (sockaddr *)&server, sizeof(server));
  cout << "Binding done" << endl;
  listen(sockfd, 5);
  cout << "listening\n\n";
  thread_data td;
  td.sockfd = sockfd;
  td.status = status;
  while (1) {
    len = sizeof(client);
    cs = accept(sockfd, (struct sockaddr *)&client, &len);
    td.cs = cs;
    pthread_t temp;
    pthread_create(&temp, NULL, responseFunction, (void *)&td);
    threads.push_back(temp);
  }
  pthread_exit(NULL);
}
