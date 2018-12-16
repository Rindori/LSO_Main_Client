#include "substratum_client.h"




int main(int argc, char *argv[])
{
    int         sockfd                      =-1;
    int         err_buf_dim                 = 128;
    char       *err_buf                     = malloc(err_buf_dim * sizeof(char));



    //controllo che i parametri non siano troppi o pochi
    if(argc < 4 ||argc > 6){
        sprintf(err_buf, "Invalid Command or number of parameters\n");
        write(2,err_buf,strlen(err_buf));
        exit(-1);
    }


       sockfd=connect_to_server(argv[1],argv[2]);

    if(strcmp("store",argv[3])==0 && (argc==6)){
        command_store(sockfd,argv[4],argv[5]);
        return 0;
    }

    if(strcmp("corrupt",argv[3])==0 && (argc==6)){
        command_corrupt(sockfd,argv[4],argv[5]);
        return 0;
    }

    if(strcmp("search",argv[3])==0 && (argc==5)){
        command_search(sockfd,argv[4]);
        return 0;
    }

    if(strcmp("list",argv[3])==0 && (argc==4)){
        command_list(sockfd);
        return 0;
    }

    //se non trova nessun "pattern" significa che il comando non è valido o non ha i parametri giusti
    sprintf(err_buf, "Invalid Command or number of parameters\n");
    write(2,err_buf,strlen(err_buf));
    exit(-1);



}
