#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>

main()
{
    pid_t pid;
    int sockfd, cs, len, recv_len;
    struct sockaddr_in client, server;
    char buf[50];

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port        = htons(5000);
    bind(sockfd, (struct sockaddr *) &server, sizeof(server));
    for (;;) {
        len = sizeof(client);
        if ((recv_len = recvfrom(sockfd, buf, 50, 0, (struct sockaddr *) &client, &len)) != -1) {
            puts("Client accepted\n");
            if ((pid = fork()) == 0) {
                puts("Child process created\n");
                puts(buf);
                sendto(sockfd, buf, 50, 0, (struct sockaddr *) &client, len);
                close(sockfd);
                exit(0);
            }
        }
    }
    close(sockfd);
}
