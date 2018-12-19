#include "message_func_client.h"


int size_buf = 128;
char *buf = NULL;

char *pool_be_err[] = {
        "Invalid command or args",                //0
        "ERR_CONV_ADDR_ATON",                    //1
        "ERR_DIGIT_PORT" ,                      //2
        "ERR_CONV_ADDR_ATON",                  //3
        "ERR_SOCKET",                         //4
        "ERR_CONN_TO_SERVER",                //5
        "ERR_READ" ,                        //6
        "ERR_READ_TOKEN",                  //7
        NULL
};



void            init_buf(){
    buf = malloc(size_buf * sizeof(char));
}


void breaking_exec_err (int code){
    if(!buf){init_buf();}
    sprintf(buf, "%s\n", pool_be_err[code]);
    write(2, buf, strlen(buf));
    free(buf);
    exit(-1);
}

void ok_conn(){
    if(!buf){init_buf();}
    sprintf(buf, "\n\nEstablished connection\n\n");
    write(0,buf,strlen(buf));
    bzero(buf,sizeof(*buf));
}