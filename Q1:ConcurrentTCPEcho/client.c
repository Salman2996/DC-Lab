#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

main()
{
    int sockfd, len, cs;
    struct sockaddr_in client;
    char buf[50], buf1[50];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    client.sin_family      = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port        = htons(5000);

    connect(sockfd, (struct sockaddr *) &client, sizeof(client));
    puts("Connected with server\n");
    puts("Enter message\n");
    fgets(buf, 50, stdin);
    send(sockfd, buf, 50, 0);
    recv(sockfd, buf1, 50, 0);
    puts("Message from server\n");
    fputs(buf, stdout);
    close(sockfd);
    return 0;
}
