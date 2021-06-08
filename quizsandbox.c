#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>

#define n 10

#define CLE_MEM 60
#define CLE_MEM2 128

#define CLE_SM1 567
#define CLE_SM2 432
#define CLE_SM3 323

int *ptr, *ptr2;
int num_mem, num_mem2;
void Init(key_t cle, int V);
void Detruire(key_t cle);
void P(key_t cle);
void V(key_t cle);

void Init(key_t cle, int V)
{
    int Num = semget(cle, 0, 0);

    if (Num == -1)
        Num = semget(cle, 1, 0777 | IPC_CREAT);
    semctl(Num, 0, SETVAL, V);
}

void Detruire(key_t cle)
{
    int Num = semget(cle, 0, 0);

    semctl(Num, 0, IPC_RMID, 0);
}

void P(key_t cle)
{
    int Num = semget(cle, 0, 0);

    struct sembuf TabOp;
    TabOp.sem_num = 0;
    TabOp.sem_op = -1;
    TabOp.sem_flg = SEM_UNDO; // bloquant

    int R = semop(Num, &TabOp, 1);
    if (R == -1)
        perror("P");
}

void V(key_t cle)
{
    int Num = semget(cle, 0, 0);

    struct sembuf TabOp;
    TabOp.sem_num = 0;
    TabOp.sem_op = 1;
    TabOp.sem_flg = SEM_UNDO;

    int R = semop(Num, &TabOp, 1);
    if (R == -1)
        perror("V");
}

int aleatoire()
{

    return (rand() % 10 + 1);
}

int *creerTabPartager()
{
    num_mem = shmget(CLE_MEM, sizeof(int) * n, IPC_CREAT | 0666);
    ptr = (int *)shmat(num_mem, 0, 0);
    return ptr;
}

int somme(int *ptr)
{
    int s = 0;
    for (int i = 0; i < n; i++)
    {
        s += ptr[i];
    }
    return s;
}

int produit(int *ptr)
{
    int s = 1;
    for (int i = 0; i < n; i++)
    {
        s *= ptr[i];
    }
    return s;
}

void initTab()
{
    int *ptr = creerTabPartager();
    for (int i = 0; i < n; i++)
    {
        ptr[i] = aleatoire();
    }
}

int main()
{
    Init(CLE_SM1, 0);
    Init(CLE_SM2, 0);
    Init(CLE_SM3, 0);


    
    srand(getpid());
    initTab();

    //ptr2[0] = somme , ptr2[1] = produit
    num_mem2 = shmget(CLE_MEM2, sizeof(int) * 2, IPC_CREAT | 0666);
    ptr2 = (int *)shmat(num_mem2, 0, 0);
    if (fork() == 0)
    {
       while(1){
        P(CLE_SM1);
        ptr2[0] = somme(ptr);
        V(CLE_SM3);
       }
        //
    }
    else
    {
        if (fork() == 0)
        {
            while(1){
            P(CLE_SM2);
            ptr2[1] = produit(ptr);
            V(CLE_SM3);
            }
        }
        else
        {
            for(int i = 0 ; i < 10 ; i++){
            V(CLE_SM1);V(CLE_SM2);P(CLE_SM3);P(CLE_SM3);
            for (int i = 0; i < n; i++)
            {
                printf("arr[%d] = %d \n", i, ptr[i]);
            }
            printf("Produit: %d \n", ptr2[0]);
            printf("Somme: %d \n", ptr2[1]);
            printf("Resultat: %d \n" , 14 + n*ptr2[0] + ptr2[1]/n);
            }
        }
    }
    

    return 0;
}