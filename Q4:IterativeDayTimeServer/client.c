#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <time.h>

main()
{
    int n, len, sockfd, cs;
    struct sockaddr_in client;
    struct timeval start, stop;
    char buf[50];

    cs = socket(AF_INET, SOCK_STREAM, 0);
    client.sin_family      = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port        = htons(5000);
    connect(cs, (struct sockaddr *) &client, sizeof(client));
    gettimeofday(&start, NULL);
    recv(cs, buf, 50, 0);
    gettimeofday(&stop, NULL);
    printf("The roundtrip time is %lu micro second", stop.tv_usec - start.tv_usec);
    puts(buf);
    close(cs);
}
