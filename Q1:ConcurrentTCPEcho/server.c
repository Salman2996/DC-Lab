#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

main(){
    int sockfd, len, cs;
    char buf[50];
    struct sockaddr_in server, client;
    pid_t pid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    puts("Socket created sucessfully\n");
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port        = htons(5000);
    bind(sockfd, (struct sockaddr *) &server, sizeof(server));
    puts("Binding done\n");
    puts("listening\n");
    listen(sockfd, 5);
    while (1) {
        len = sizeof(client);
        cs  = accept(sockfd, (struct sockaddr *) &client, &len);
        puts("Connected to client\n");
        if ((pid = fork()) == 0) {
            puts("child created\n");
            close(sockfd);
            recv(cs, buf, 50, 0);
            puts("message from client\n");
            fputs(buf, stdout);
            send(cs, buf, 50, 0);
            close(cs);
            exit(0);
        }
        close(cs);
    }
    return 0;
}
