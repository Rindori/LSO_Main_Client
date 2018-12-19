#include "substratum_client.h"


char* receive_all(int sockfd){
    ssize_t  byte           = -1;
    int      i              = 0;

    int    dim_str          = 128;
    char   *str             = malloc(dim_str*sizeof(char));

    //il while legge finché non viene restituito un valore minore del buffer,
    //cioè quando si è letto l'ultima parte della stringa, e quindi meno di 64
    //caratteri, oppure è 0.
    //Continua, se si è letto tutti i caratteri al suo interno e potrebbero essercene altri.
    while( (byte = (read(sockfd,str + i,64))) == 64){
        i += 64;
        if(i > 128){return(NULL);}
    }
    if(byte<0){return (NULL);}

    return (str);
}


int connect_to_server(char *ip,char *port){

    int     check            =-1;

    int     sockfd           =-1;

    int     converted_port   =-1;
    struct  sockaddr_in      server_addr;


    server_addr.sin_family = AF_INET;

    //converto da char ad int e controllo che la porta abbia 4 cifre
    converted_port= atoi(port);
    if((converted_port<1000) ||(converted_port>9999)){
        breaking_exec_err(2);
    }
    server_addr.sin_port = htons((uint16_t )converted_port);


    check = inet_aton(ip, &server_addr.sin_addr);
    if (check==0) {
        breaking_exec_err(2);
    }

    //creazione socket
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        breaking_exec_err(4);
    }

    //richiesta connessione al server
    check=connect(sockfd,(struct sockaddr*) &server_addr,sizeof (server_addr));
    if(check<0){
        breaking_exec_err(5);
    }else{
        ok_conn();
    }


   return (sockfd);
}


void command_store(int sockfd, char *arg1,char *arg2){
     char    *token            =malloc(10*sizeof(char));

     if(sockfd) {
         //invio "store"
         write(sockfd, "s", 1);

         //attesa token
         token = receive_all(sockfd);
         if (strcmp(token, "ok") != 0) {
             breaking_exec_err(6);
         }

         //invio arg1
         write(sockfd, arg1, strlen(arg1));

         //attesa token
         token = receive_all(sockfd);
         if (strcmp(token, "ok") != 0) {
             breaking_exec_err(6);
         }

         //invio arg2
         write(sockfd, arg2, strlen(arg2));


         //attesa token
         token = receive_all(sockfd);
         if (strcmp(token, "ok") == 0) {
             write(1, "Store success\n", strlen("Store success\n"));
         }
         if (strcmp(token, "!ok") == 0) {
             write(1, "Store failed\n", strlen("Store failed\n"));

         }
         if (strcmp(token, "?") == 0) {
             write(1, "Inconsistent list\n", strlen("Inconsistent list\n"));

         }
     }else{
         breaking_exec_err(4);
     }

      free(token);
      close(sockfd);

}

void command_corrupt(int sockfd, char *arg1,char *arg2){
    char    *token            =malloc(10*sizeof(char));

    if(sockfd) {
        //invio "corrupt"
        write(sockfd, "c", 1);

        //attesa token
        token = receive_all(sockfd);
        if (strcmp(token, "ok") != 0) {
            breaking_exec_err(6);
        }

        //invio arg1
        write(sockfd, arg1, strlen(arg1));

        //attesa token
        token = receive_all(sockfd);
        if (strcmp(token, "ok") != 0) {
            breaking_exec_err(6);
        }

        //invio arg2
        write(sockfd, arg2, strlen(arg2));


        //attesa token
        token = receive_all(sockfd);
        if (strcmp(token, "ok") == 0) {
            write(1, "Corrupt success\n", strlen("Corrupt success\n"));
        }
        if (strcmp(token, "!ok") == 0) {
            write(1,"Key does not exist\n", strlen("Key does not exist\n"));

        }

    }else{
        breaking_exec_err(4);
    }

    free(token);
    close(sockfd);


}

void command_search(int sockfd, char *arg1){

    char    *token            =malloc(10*sizeof(char));

    if(sockfd) {
        //invio "search"
        write(sockfd, "S", 1);

        //attesa token
        token = receive_all(sockfd);
        if (strcmp(token, "ok") != 0) {
            breaking_exec_err(6);
        }

        //invio arg1
        write(sockfd, arg1, strlen(arg1));


        //attesa token
        token = receive_all(sockfd);
        if (strcmp(token, "ok") == 0) {
            write(1, "Ledger exists\n", strlen("Ledger exists\n"));
        }
        if (strcmp(token, "!ok") == 0) {
            write(1, "Ledger corrupt\n", strlen("Ledger corrupt\n"));

        }
        if (strcmp(token, "?") == 0) {
            write(1, "Key does not exist\n", strlen("Key does not exist\n"));

        }
    }else{
        breaking_exec_err(4);
    }

    free(token);
    close(sockfd);

}

void command_list(int sockfd){

    int      byte             =-1;
    int      dim              =-1;

    char    *str;
    char    *token;

    token=malloc(sizeof(char));
    str=malloc(120*sizeof(char));
    write(1,"Local list:\n",12);

    //search
    write(sockfd,"l",1);
    byte=read(sockfd,token,1);
    if(byte<0 || (strcmp("k",token)!=0)){
        breaking_exec_err(7);
    }


    write(1,"\nlist terminated\n",17);


    free(str);
    close(sockfd);

}


