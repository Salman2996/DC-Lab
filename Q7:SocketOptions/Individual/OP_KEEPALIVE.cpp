#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char **argv) {
  int sockfd, sendbuff;
  socklen_t optlen;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  int res = 0;

  // Get flag
  optlen = sizeof(sendbuff);
  res = getsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &sendbuff, &optlen);

  printf("SO_KEEPALIVE is %s\n", (sendbuff ? "ON" : "OFF"));

  // Set flag
  sendbuff = 1;

  printf("set SO_KEEPALIVE to %d\n", sendbuff);
  res =
      setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &sendbuff, sizeof(sendbuff));

  // Get flag
  optlen = sizeof(sendbuff);
  res = getsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &sendbuff, &optlen);

  printf("SO_KEEPALIVE is %s\n", (sendbuff ? "ON" : "OFF"));
  return 0;
}
