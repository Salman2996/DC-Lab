#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>

main()
{
    int cs, len;
    char buf[50], buf1[50];
    struct sockaddr_in client;

    cs = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    client.sin_family      = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port        = htons(5000);
    // bind(cs,(struct sockaddr *)&client,sizeof(client));
    printf("Enter the message\n");
    scanf("%s", buf);
    len = sizeof(client);
    sendto(cs, buf, 50, 0, (struct sockaddr *) &client, len);
    recvfrom(cs, buf1, 50, 0, (struct sockaddr *) &client, &len);
    puts(buf1);
    close(cs);
    return 0;
}
