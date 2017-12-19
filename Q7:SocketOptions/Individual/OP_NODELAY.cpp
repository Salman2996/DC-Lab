#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char **argv) {
  int sockfd;
  int flag;
  socklen_t optlen;
  int res = 0;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  optlen = sizeof(flag);
  res = getsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &flag, &optlen);
  printf("Nagle's algo is %s\n", (flag ? "ON" : "OFF"));

  // Set Nagle's
  flag = 1;
  printf("sets the TCP_NODELAY\n");
  res = setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(int));
  // test now
  flag = 0;
  optlen = sizeof(flag);
  res = getsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &flag, &optlen);
  printf("Nagle's algo is %s\n", (flag ? "ON" : "OFF"));
  return 0;
}
