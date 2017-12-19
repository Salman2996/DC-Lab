#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <cstring>
using namespace std;

int main(int argc, char const *argv[])
{
	int sockfd, cs, optionSocket, res = 0, flag;
	struct sockaddr_in server, client;
	socklen_t optlen, len;
	char buf[5], buf1[200] = {0};
	char temp[10];	// to store integer converted to string
	pid_t pid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(5000);

	bind(sockfd, (struct sockaddr *) &server, sizeof(server));
	listen(sockfd, 3);

	while(1){
		len = sizeof(client);
		cs = accept(sockfd, (struct sockaddr *) &client, &len);
		cout<<"\nClient accepted";
		if((pid = fork()) == 0){
			cout<<"\nChild created";
			close(sockfd);
			recv(cs, buf, 5, 0);
			switch(buf[0]){
				case '1': // KEEPALIVE
					cout<<"\nSO_KEEPALIVE\n";
					optionSocket = socket(AF_INET, SOCK_DGRAM, 0);

  					optlen = sizeof(flag);
  					res = getsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &flag, &optlen);
  					strcat(buf1, "SO_KEEPALIVE is ");
  					strcat(buf1, (flag ? "ON\n" : "OFF\n"));
				  	
				  	flag = 1;
				  	strcat(buf1, "\nSet SO_KEEPALIVE to 1\n");
				  	res = setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &flag, sizeof(flag));

				  	optlen = sizeof(flag);
  					res = getsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &flag, &optlen);
				  	strcat(buf1, "\nSO_KEEPALIVE is ");
  					strcat(buf1, (flag ? "ON\n" : "OFF\n"));

				  	break;

				case '2': // LINGER
					cout<<"\nSO_LINGER\n";
					struct linger {
    					int l_onoff, l_linger;
  					} l;

  					sockfd = socket(AF_INET, SOCK_DGRAM, 0);

					optlen = sizeof(l);
  					res = getsockopt(sockfd, SOL_SOCKET, SO_LINGER, &l, &optlen);
  					// convert the integers to string for reply message
  					char onoff[10], lingertime[10];
  					strcat(buf1, "SO_LINGER is ");
  					sprintf(onoff, "%d", l.l_onoff);
  					strcat(buf1, onoff);
  					strcat(buf1, " for time ");
  					sprintf(lingertime, "%d", l.l_linger);
  					strcat(buf1, lingertime);

  					l.l_onoff = 1;
  					l.l_linger = 10;
  					strcat(buf1, "\nSO_LINGER is set to 1 for time 10\n");
  					res = setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &l, sizeof(l));

  					optlen = sizeof(l);
  					res = getsockopt(sockfd, SOL_SOCKET, SO_LINGER, &l, &optlen);
  					strcat(buf1, "\nSO_LINGER is ");
  					sprintf(onoff, "%d", l.l_onoff);
  					strcat(buf1, onoff);
  					strcat(buf1, " for time ");
  					sprintf(lingertime, "%d", l.l_linger);
  					strcat(buf1, lingertime);

					break;

				case '3': // SNDBUF
					cout<<"\nSO_SNDBUF\n";
					optionSocket = socket(AF_INET, SOCK_DGRAM, 0);

  					optlen = sizeof(flag);
  					res = getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &flag, &optlen);
  					strcat(buf1, "Send buffer size is ");
  					// convert the flag to string and then add it to reply message
  					sprintf(temp, "%d", flag);
  					strcat(buf1, temp);
				  	
				  	flag = 40480;
				  	strcat(buf1, "\nSet send buffer size to 80960\n");
				  	res = setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &flag, sizeof(flag));

				  	optlen = sizeof(flag);
  					res = getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &flag, &optlen);
				  	strcat(buf1, "\nSend buffer size is ");
				  	// convert the flag to string and then add it to reply message
  					sprintf(temp, "%d", flag);
  					strcat(buf1, temp);

				  	break;

				case '4': // RCVBUF
					cout<<"\nSO_RCVBUF\n";
					optionSocket = socket(AF_INET, SOCK_DGRAM, 0);

  					optlen = sizeof(flag);
  					res = getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &flag, &optlen);
  					strcat(buf1, "Receive buffer size is ");
  					// convert the flag to string and then add it to reply message
  					sprintf(temp, "%d", flag);
  					strcat(buf1, temp);
				  	
				  	flag = 40480;
				  	strcat(buf1, "\nSet receive buffer size to 80960\n");
				  	res = setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &flag, sizeof(flag));

				  	optlen = sizeof(flag);
  					res = getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &flag, &optlen);
				  	strcat(buf1, "\nReceive buffer size is ");
				  	// convert the flag to string and then add it to reply message
  					sprintf(temp, "%d", flag);
  					strcat(buf1, temp);

				  	break;

				case '5': // TCP_NODELAY
					cout<<"\nTCP_NODELAY\n";
					sockfd = socket(AF_INET, SOCK_STREAM, 0);
  					
  					optlen = sizeof(flag);
  					res = getsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &flag, &optlen);
  					strcat(buf1, "Nagle's algo is ");
  					strcat(buf1, (flag ? "ON\n" : "OFF\n"));
					
					flag = 1;
  					strcat(buf1, "\nSet the TCP_NODELAY to 1\n");
  					res = setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(int));
  					
  					optlen = sizeof(flag);
  					res = getsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &flag, &optlen);
  					strcat(buf1, "\nNagle's algo is ");
  					strcat(buf1, (flag ? "ON\n" : "OFF\n"));
					
					break;
			}

			// reply message
			send(cs, buf1, 200, 0);
			close(cs);
			exit(0);
		}
	}
	return 0;
}