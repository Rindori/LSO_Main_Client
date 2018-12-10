#include "substratum_client.h"


int connect_to_server(char *ip,char *port){

    int     dim_buf_err      = 128;
    char    *buf_err;

    int     check            =-1;

    int     sockfd           =-1;

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
    check = inet_aton(ip, &server_addr.sin_addr);
    if (check==0) {
        sprintf(buf_err, "ERR_CONV_ADDR_ATON");
        write(2, buf_err, strlen(buf_err));
        free(buf_err);
        exit(-1);
    }

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
     int      byte             =-1;
     int      dim_buf_err      = 128;

     char    *str;
     char    *buf_err;

    buf_err = malloc(dim_buf_err * sizeof(char));
    str=malloc(15*sizeof(char));


     //invio al server il comando "store"
     //con un solo carattere non devo sincronizzare
     write(sockfd,"s",1);

     write(sockfd,arg1,15);

     //ricevo token
     byte=read(sockfd,str,1);
     if(byte<0){
        sprintf(buf_err, "ERR_READ_TOKEN");
        write(2, buf_err, strlen(buf_err));
        free(buf_err);
        exit(-1);

      }

     write(sockfd,arg2,15);

    //funziona sia da token di ritorno che come esito per il server
     byte=read(sockfd,str,1);
     if(byte<0){
         sprintf(buf_err, "ERR_READ");
         write(2, buf_err, strlen(buf_err));
         free(buf_err);
         exit(-1);

     }

    if(strcmp("1",str)==0){
       write(1,"Store success\n",strlen("Store success\n"));
    }else{
        write(1,"Key already exists\n",strlen("Key already exists\n"));
    }

    free(buf_err);
    free(str);
    close(sockfd);

}

void command_corrupt(int sockfd, char *arg1,char *arg2){
    int      byte             =-1;
    int      dim_buf_err      = 128;

    char    *str;
    char    *buf_err;

    buf_err = malloc(dim_buf_err * sizeof(char));
    str=malloc(15*sizeof(char));


    //invio al server il comando "corrupt"
    //stessa logica di store
    write(sockfd,"c",1);

    write(sockfd,arg1,15);

    //ricevo token
    byte=read(sockfd,str,1);
    if(byte<0){
        sprintf(buf_err, "ERR_READ_TOKEN");
        write(2, buf_err, strlen(buf_err));
        free(buf_err);
        exit(-1);

    }

    write(sockfd,arg2,15);

    //funziona sia da token di ritorno che come esito per il server
    byte=read(sockfd,str,1);
    if(byte<0){
        sprintf(buf_err, "ERR_READ");
        write(2, buf_err, strlen(buf_err));
        free(buf_err);
        exit(-1);

    }

    if(strcmp("1",str)==0){
        write(1,"Corrupt success\n",strlen("Corrupt success\n"));
    }else{
        write(1,"Key not exists\n",strlen("Key not exists\n"));
    }

    free(buf_err);
    free(str);
    close(sockfd);

}

void command_search(int sockfd, char *arg1){
    int      byte             =-1;
    int      dim_buf_err      = 128;

    char    *str;
    char    *buf_err;

    buf_err = malloc(dim_buf_err * sizeof(char));
    str=malloc(sizeof(char));

    //search
    write(sockfd,"S",1);

    write(sockfd,arg1,15);

    //funziona sia da token di ritorno che come esito per il server
    byte=read(sockfd,str,1);
    if(byte<0){
        sprintf(buf_err, "ERR_READ_TOKEN");
        write(2, buf_err, strlen(buf_err));
        free(buf_err);
        exit(-1);

    }

    //1 tutte le coppie uguali 2 Ledger corrotto 0 chiave non esiste
    if(strcmp("1",str)==0){
        write(1,"Search success\n",strlen("Search success\n"));
    }else if(strcmp("2",str)==0){
        write(1,"Ledger corrupt\n",strlen("Ledger corrupt\n"));
       }else{
        write(1,"Key not exists\n",strlen("Key not exists\n"));
        }

    free(buf_err);
    free(str);
    close(sockfd);
}

void command_list(int sockfd){

    int      byte             =-1;
    int      dim_buf_err      = 128;

    char    *str;
    char    *output;
    char    *buf_err;

    buf_err = malloc(dim_buf_err * sizeof(char));
    str=malloc(15*sizeof(char));
    output=malloc(15*sizeof(char));

    //search
    write(sockfd,"l",1);

     do {
         byte = read(sockfd, str, 15);
         write(sockfd,"1",1);
         if (byte < 0) {
             sprintf(buf_err, "ERR_READ");
             write(2, buf_err, strlen(buf_err));
             free(buf_err);
             exit(-1);
         }else if(byte!=0){
             write(1, str, byte);
             write(1, " ", 1);

         }



        }while(byte !=0);


    free(buf_err);
    free(str);
    close(sockfd);

}