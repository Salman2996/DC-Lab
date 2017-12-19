#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <time.h>


main()
{
    int sockfd, cs, len;
    struct sockaddr_in client, server;
    char buf[50];
    pid_t pid;
    time_t curtime;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port        = htons(5000);
    bind(sockfd, (struct sockaddr *) &server, sizeof(server));
    puts("Socket bind sucessful\n");
    puts("Listening\n");
    listen(sockfd, 3);
    while (1) {
        len = sizeof(client);
        cs  = accept(sockfd, (struct sockaddr *) &client, &len);
        puts("Client Connected");
        if ((pid = fork()) == 0) {
            puts("Connected to client\n");
            sleep(15);
            time(&curtime);
            send(cs, ctime(&curtime), 50, 0);
            close(cs);
            exit(0);
        }
        close(cs);
    }
    close(sockfd);
}
