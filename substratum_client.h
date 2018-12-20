#ifndef LSO_MAIN_CLIENT_SUBSTRATUM_CLIENT_H
#define LSO_MAIN_CLIENT_SUBSTRATUM_CLIENT_H


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "message_func_client.h"

int connect_to_server(char *ip,char *port);

void command_store(int sockfd,char *arg1,char *arg2);

void command_corrupt(int sockfd,char *arg1,char *arg2);

void command_search(int sockfd,char *arg1);

void command_list(int sockfd);

void hand_alarm(int num_sig);

#endif //LSO_MAIN_CLIENT_SUBSTRATUM_CLIENT_H
