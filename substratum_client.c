#include "substratum_client.h"


int connect_to_server(char *ip,char *port){

    int     dim_buf_err      = 128;
    char    *buf_err;

    int     check            =-1;

    int     sockfd           =-1;
    int     result_aton      =-1;
    int     converted_port   =-1;
    struct  sockaddr_in      server_addr;

    buf_err = malloc(dim_buf_err * sizeof(char));

    server_addr.sin_family = AF_INET;

    //converto da char ad int e controllo che la porta abbia 4 cifre
    converted_port= atoi(port);
    if((converted_port<1000) ||(converted_port>9999)){
        sprintf(buf_err, "ERR_DIGIT_PORT");
        write(2, buf_err, strlen(buf_err));
        free(buf_err);
        exit(-1);
    }
    server_addr.sin_port = htons((uint16_t )converted_port);

    //conversione da dot a binary
    result_aton = inet_aton(ip, &server_addr.sin_addr);
    if (result_aton==0) {
        sprintf(buf_err, "ERR_CONV_ADDR_ATON");
        write(2, buf_err, strlen(buf_err));
        free(buf_err);
        exit(-1);
    }

    //server_addr.sin_addr= htons(&server_addr.sin_addr);

    //creazione socket
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        sprintf(buf_err, "ERR_SOCKET");
        write(2, buf_err, strlen(buf_err));
        free(buf_err);
        exit(-1);
    }

    //richiesta connessione al server
    check=connect(sockfd,(struct sockaddr*) &server_addr,sizeof (server_addr));
    if(check<0){
        sprintf(buf_err, "ERR_CONN_TO_SERVER");
        write(2, buf_err, strlen(buf_err));
        free(buf_err);
        exit(-1);
    }


   return (sockfd);
}

void command_store(int sockfd, char *arg1,char *arg2){



}