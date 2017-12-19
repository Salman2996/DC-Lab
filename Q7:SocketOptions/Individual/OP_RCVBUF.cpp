#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char **argv) {
  int sockfd, recvbuff;
  socklen_t optlen;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  int res = 0;

  // Get buffer size
  optlen = sizeof(recvbuff);
  res = getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &recvbuff, &optlen);

  printf("receive buffer size = %d\n", recvbuff);

  // Set buffer size
  recvbuff = 40480;

  printf("sets the recv buffer to %d\n", recvbuff);
  res = setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &recvbuff, sizeof(recvbuff));

  // Get buffer size
  optlen = sizeof(recvbuff);
  res = getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &recvbuff, &optlen);

  printf("receive buffer size = %d\n", recvbuff);
  return 0;
}
