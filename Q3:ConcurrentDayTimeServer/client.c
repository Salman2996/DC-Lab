#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

main()
{
    int cs, len;
    struct sockaddr_in client;
    char buf[50];

    cs = socket(AF_INET, SOCK_STREAM, 0);
    client.sin_family      = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port        = htons(5000);
    connect(cs, (struct sockaddr *) &client, sizeof(client));
    recv(cs, buf, 50, 0);
    fputs(buf, stdout);
    close(cs);
}
