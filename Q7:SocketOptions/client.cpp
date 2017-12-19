#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char const *argv[])
{
	int sockfd;
	struct sockaddr_in client;
	char buf[5], buf1[200];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = inet_addr("127.0.0.1");
	client.sin_port = htons(5000);

	connect(sockfd, (struct sockaddr *) &client, sizeof(client));
	cout<<"\nConnected to server";
	cout<<"\nEnter choice: ";
	cout<<"\n1.SO_KEEPALIVE\n2.SO_LINGER\n3.SO_SNDBUF\n4.SO_RCVBUF\n5.TCP_NODELAY\n";
	cin>>buf;
	send(sockfd, buf, 5, 0);
	recv(sockfd, buf1, 200, 0);
	cout<<endl<<buf1<<endl;
	return 0;
}