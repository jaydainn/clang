#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>


void handler(){
    
}

int main()
{
    int *a;
    int num_mema;
    num_mema = shmget(600, sizeof(int), IPC_CREAT | 0666);
    a = (int *)shmat(num_mema, 0, 0);
    *a = 17877472;

    if (fork() == 0)
    {
        num_mema = shmget(600, sizeof(int), IPC_CREAT | 0666);
        a = (int *)shmat(num_mema, 0, 0);
        while (*a != 1)
        {
            while (*a % 2 == 0)
            {
                printf("even a : %d \n", *a);
                *a = *a / 2;
            }
        }

        exit(0);
    }
    else
    {

        while (*a != 1)
        {
            if (*a % 2 == 1)
            {
                printf("odd a: %d \n", *a);
                *a = 3 * *a + 1;
            }
        }
    }
    printf("res : %d \n " , *a);


    return 0;
}