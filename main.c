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

    //effettuo la connessione qui perchè se va storto qualcosa non mi preoccupo di controllare ulteriormente la riga di comando
    //il controllo se la connessione fallisce viene fatta nella funzione quindi è impossibile che ritorni valori sbagliati
       sockfd=connect_to_server(argv[1],argv[2]);

    if(strcmp("store",argv[3])==0 && (argc==6)){
        write(1,"esecuzione 1",strlen("esecuzione 1"));
        return 0;
    }

    if(strcmp("corrupt",argv[3])==0 && (argc==6)){
        write(1,"esecuzione 2",strlen("esecuzione 2"));
        return 0;
    }

    if(strcmp("search",argv[3])==0 && (argc==5)){
        write(1,"esecuzione 3",strlen("esecuzione 3"));
        return 0;
    }

    if(strcmp("list",argv[3])==0 && (argc==4)){
        write(1,"esecuzione 4",strlen("esecuzione 4"));
        return 0;
    }

    //se non trova nessun "pattern" significa che il comando non è valido o non ha i parametri giusti
    sprintf(err_buf, "Invalid Command or number of parameters\n");
    write(2,err_buf,strlen(err_buf));
    exit(-1);



}
