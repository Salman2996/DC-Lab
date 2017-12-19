#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char **argv) {
  int sockfd;
  struct linger {
    int l_onoff;
    int l_linger;
  } l;
  socklen_t optlen;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  int res = 0;

  // Get buffer size
  optlen = sizeof(l);
  res = getsockopt(sockfd, SOL_SOCKET, SO_LINGER, &l, &optlen);

  // printf("send buffer size = %d\n", sendbuff);
  printf("SO_LINGER is %d for time %d\n", l.l_onoff, l.l_linger);

  // Set buffer size
  l.l_onoff = 1;
  l.l_linger = 10;
  printf("SO_LINGER is set to %d for time %d\n", l.l_onoff, l.l_linger);
  res = setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &l, sizeof(l));

  // Get buffer size
  optlen = sizeof(l);
  res = getsockopt(sockfd, SOL_SOCKET, SO_LINGER, &l, &optlen);

  // printf("send buffer size = %d\n", sendbuff);
  printf("SO_LINGER is %d for time %d\n", l.l_onoff, l.l_linger);
  return 0;
}
