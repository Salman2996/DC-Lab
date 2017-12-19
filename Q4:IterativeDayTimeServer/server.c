#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <time.h>

main()
{
    struct sockaddr_in client, server;
    int sockfd, cs, len;
    time_t t;
    char buf[50];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port        = htons(5000);
    bind(sockfd, (struct sockaddr *) &server, sizeof(server));
    listen(sockfd, 3);
    for (;;) {
        len = sizeof(client);
        cs  = accept(sockfd, (struct sockaddr *) &client, &len);
        puts("client accepted\n");
        sleep(10);
        time(&t);
        send(cs, ctime(&t), 50, 0);
        close(cs);
    }
    close(sockfd);
}
