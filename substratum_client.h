#ifndef LSO_MAIN_CLIENT_SUBSTRATUM_CLIENT_H
#define LSO_MAIN_CLIENT_SUBSTRATUM_CLIENT_H


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int connect_to_server(char *ip,char *port);
void command_store(int sockfd,char *arg1,char *argv2);


#endif //LSO_MAIN_CLIENT_SUBSTRATUM_CLIENT_H
