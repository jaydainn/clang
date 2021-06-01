#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define CLE_MEM 60

int main()

{
    int *a;
    int *b;
    int num_mema, num_memb, n;
    num_mema = shmget(CLE_MEM, sizeof(int), IPC_CREAT | 0666);
    a = (int *)shmat(num_mema, 0, 0);
    num_memb = shmget(100, sizeof(int), IPC_CREAT | 0666);
    b = (int *)shmat(num_memb, 0, 0);
    *a = 0;
    *b = 0;

    if (fork() == 0)
    {
        num_mema = shmget(CLE_MEM, sizeof(int), IPC_CREAT | 0666);
        a = (int *)shmat(num_mema, 0, 0);
        num_memb = shmget(100, sizeof(int), IPC_CREAT | 0666);
        b = (int *)shmat(num_memb, 0, 0);
        *a = *a + 1;
        *b = *b + 1;
        printf("p2 : %d , %d \n \n", *a, *b);
    }
    else
    {
        wait(NULL);
        *b = *b * 2;
        *a = *a * 2;
        printf("p2 : %d , %d \n \n", *a, *b);
    }
    return 0;
}