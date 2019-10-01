#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <signal.h>
#include "chat.h"

void *get_in_addr(struct sockaddr *sa) {
    if(sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[]) {
    int sockfd;
    struct addrinfo hints, *res;
    int n, n1;
    char s[INET6_ADDRSTRLEN];

    if(argc != 3) {
        fprintf(stderr, "usage: %s <ip> <port>\n", argv[0]);
        return 1;
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;

    n = getaddrinfo(argv[1], argv[2], &hints, &res);
    if(n != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(n));
		return 1;
    }

    n = sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(n == -1) {
        perror("socket");
        exit(1);
    }

    // connect to server

    n = sendto(sockfd, "!", 2, 0, res->ai_addr, res->ai_addrlen);
    if(n == -1) {
        perror("connect");
        exit(1);
    }

    // print connection
    inet_ntop(res->ai_family, get_in_addr((struct sockaddr*)res->ai_addr), s, sizeof s);
    printf("Connected to %s!\n", s);

    freeaddrinfo(res);
  
    char recv[] = "SERVER";
    chat(sockfd, (struct sockaddr*) res->ai_addr, res->ai_addrlen, recv, strlen(recv));

    return 0;
}
