#include "kernel/types.h"
#include "user/user.h"


void dealing(int* left_pipe){
    close(left_pipe[1]);
    int prime;
    if(read(left_pipe[0], &prime, 4) < 0){
        LOG_ERROR("Read failed!");
        close(left_pipe[0]);
        exit(1);
    }
    printf("prime %d\n", prime);
    int right_pipe[2];
    int ret = pipe(right_pipe);
    if(ret < 0){
        close(left_pipe[0]);
        LOG_ERROR("Right pipe create failed!, errno: %d", ret);
        exit(1);
    }
    int pid = fork();
    if(pid > 0){
        int n;
        close(right_pipe[0]);
        while(read(left_pipe[0], &n, 4) > 0){
            if(n % prime != 0){
                if(write(right_pipe[1], &n, 4) < 0){
                    LOG_ERROR("Write failed!");
                    close(right_pipe[1]);
                    close(left_pipe[0]);
                }
            }
        }
        close(right_pipe[1]);
        close(left_pipe[0]);
        wait(0);
    }else if(pid == 0){
        dealing(right_pipe);
    }else{
        close(left_pipe[0]);
        close(right_pipe[0]);
        close(right_pipe[1]);
        printf("Fork failed!");
        exit(1);
    }
}




int main(void){
    int left_pipe[2];
    if(pipe(left_pipe) < 0){
        LOG_ERROR("Pipe create failed!");
        exit(1);
    }
    int pid = fork();
    if(pid > 0){
        close(left_pipe[0]);
        for(int i = 2; i <= 280; i++){
            if(write(left_pipe[1], &i, 4) < 0){
                LOG_ERROR("Write failed!");
                close(left_pipe[1]);
                exit(1);
            }
        }
        wait(0);
    }else if(pid == 0){
        dealing(left_pipe);
    }else{
        LOG_ERROR("Fork failed!");
        close(left_pipe[0]);
        close(left_pipe[1]);
        exit(1);
    }
}