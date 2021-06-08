#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define n 10


int main(){
    int *a;
    int num_mema;
    num_mema = shmget(600, sizeof(int), IPC_CREAT | 0666);
    a = (int *)shmat(num_mema, 0, 0);
    *a = 3;

    if(fork() == 0 ){
         num_mema = shmget(600, sizeof(int), IPC_CREAT | 0666);
        a = (int *)shmat(num_mema, 0, 0);
        for(int i = 0 ; i < n ; i++){
            (*a)--;
           // printf("p1 %d \n" , *a);
        }
    


    }else{
        wait(NULL);
        for(int i = 0 ; i < n ; i++){
            (*a)++;
           // printf("p2 %d \n" , *a);
        }

        printf("\nRes: %d \n\n" , *a);
        


    }

    return 0;
}