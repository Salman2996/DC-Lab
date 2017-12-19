#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char **argv) {
  int sockfd, sendbuff;
  socklen_t optlen;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  int res = 0;

  // Get buffer size
  optlen = sizeof(sendbuff);
  res = getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sendbuff, &optlen);

  printf("send buffer size = %d\n", sendbuff);

  // Set buffer size
  sendbuff = 40480;

  printf("sets the send buffer to %d\n", sendbuff);
  res = setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sendbuff, sizeof(sendbuff));

  // Get buffer size
  optlen = sizeof(sendbuff);
  res = getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sendbuff, &optlen);

  printf("send buffer size = %d\n", sendbuff);
  return 0;
}
