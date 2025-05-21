#include "kernel/types.h"
#include "user/user.h"

int main(void){
    int p1[2],p2[2];
    if(pipe(p1) < 0){
        LOG_ERROR("pipe failed!\n");
        exit(1);
    }
    if(pipe(p2) < 0){
        LOG_ERROR("pipe failed!\n");
        exit(1);
    }
    int pid = fork();
    // child
    if(pid == 0){
        int pid = getpid();
        char data = 'b';
        close(p1[1]);
        close(p2[0]);
        if(read(p1[0],&data, 1) < 0){
            close(p1[0]);
            close(p2[1]);
            LOG_ERROR("read failed!\n");
            exit(1);
        }else{
            close(p1[0]);
            close(p2[1]);
            printf("%d: received ping\n",pid);
            exit(0);
        }
        if(write(p2[1],&data,1) < 0){
            close(p1[0]);
            close(p2[1]);
            LOG_ERROR("write failed!\n");
            exit(1);
        }
    //parent
    }else if(pid > 0){
        int pid = getpid();
        char data = 'b';
        close(p1[0]);
        close(p2[1]);
        if(write(p1[1],&data,1) < 0){
            close(p1[1]);
            close(p2[0]);
            LOG_ERROR("write failed!\n");
            exit(1);
        }
        if(read(p2[0],&data, 1) < 0){
            close(p1[1]);
            close(p2[0]);
            LOG_ERROR("read failed!\n");
            exit(1);
        }else{
            wait(0);
            printf("%d: received pong\n",pid);
            close(p1[1]);
            close(p2[0]);
            exit(0);
        }
        
    }else{
        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);
        LOG_ERROR("fork failed\n");
        exit(1);
    }
}