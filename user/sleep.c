#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int 
main(int argc, char*argv[]){
    if(argc != 2){
        LOG_ERROR("Usage: sleep NUMBER(centisecond)\n");
        exit(1);
    }
    int centiSecond = atoi(argv[1]);
    sleep(centiSecond);
    exit(0);
}