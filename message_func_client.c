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

void  err_internal_servers(char *code){

    if(strcmp("0",code)==0){
        write(1,"UNKNOW_ERR_FROM_SERVER\n",strlen("UNKNOW_ERR_FROM_SERVER\n"));
    }

    if(strcmp("-1",code)==0){
        write(1,"SERVER_CRASH_CONNECT\n",strlen("SERVER_CRASH_CONNECT\n"));
    }

    if(strcmp("-2",code)==0){
        write(1,"ERR_WRITE_SYNC_STORE\n",strlen("ERR_WRITE_SYNC_STORE\n"));
    }

    if(strcmp("-3",code)==0){
        write(1,"ERR_PASSING_KEY",strlen("ERR_PASSING_KEY"));
    }

    if(strcmp("-4",code)==0){
        write(1,"ERR_PASSING_VALUE\n",strlen("ERR_PASSING_VALUE\n"));
    }

    if(strcmp("-5",code)==0){
        write(1,"ERR_WAIT\n",strlen("ERR_WAIT\n"));
    }

    exit(-1);
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
    sprintf(buf,"Established connection\n");
    write(1,buf,strlen(buf));
    bzero(buf,sizeof(*buf));
}