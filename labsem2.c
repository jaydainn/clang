#include<sys/sem.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#define n 10

void Init (key_t cle, int V);
void Detruire (key_t cle);
void P (key_t cle);
void V (key_t cle);

 


void Init (key_t cle, int V) {
  int Num = semget (cle, 0, 0);

 

  if (Num==-1) Num = semget (cle, 1, 0777|IPC_CREAT);
  semctl (Num, 0, SETVAL, V);

 

}

 

void Detruire (key_t cle) {
  int Num = semget (cle, 0, 0);

 

  semctl (Num, 0, IPC_RMID, 0);
}

 

void P (key_t cle) {
  int Num = semget (cle, 0, 0);

 

  struct sembuf TabOp;
  TabOp.sem_num = 0;
  TabOp.sem_op  = -1;
  TabOp.sem_flg = SEM_UNDO;     // bloquant

 

  int R = semop (Num, &TabOp, 1);
  if (R==-1) perror ("P");
}

 


void V (key_t cle) {
  int Num = semget (cle, 0, 0);

 

  struct sembuf TabOp;
  TabOp.sem_num = 0;
  TabOp.sem_op  = 1;
  TabOp.sem_flg = SEM_UNDO;

 

  int R = semop (Num, &TabOp, 1);
  if (R==-1) perror ("V");
}


int min(int * arr){
    int res = arr[0];
    for(int i = 0; i <  n ; i++){
        if(arr[i] < res){
            res = arr[i];
        }
    }
    return res;
}

int max(int * arr){
    int res = arr[0];
    for(int i = 0; i <  n ; i++){
        if(arr[i] > res){
            res = arr[i];
        }
    }
    return res;
} 


int findIndex(int * arr , int val){
    int res = -1; 
    for(int i = 0 ; i < n ; i++){
        if( val == arr[i]){
            res = i;
        }
    }
    return res;
}


int main(){
    int arr [] = {2 , 4 , 12 , 18 , 5 , 8 , 14, 22 , 79, 46};
    Init(700 , 0);
    Init(800 , 0);
    if(fork() == 0){
        P(700);
        printf("min index %d\n" , findIndex(arr , min(arr)));
        V(800);
        P(700);

    }else{
        printf("max index %d \n" , findIndex(arr , min(arr)));
        V(700);
        P(800);

    }


    return 0; 
}