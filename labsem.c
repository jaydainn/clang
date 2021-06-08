#include<sys/sem.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>


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



int main(){

  int val = 0 ; 
 Init(700 , 0 );
 Init(800, 0);
    
    if(fork() == 0){
     
      P(700);
      while(val < 100){
        val +=3;
        printf("fils : %d " , val);
        if(val%5 == 0){
          printf("\n");
          V(800);
          P(700);
        }
        
      }
      V(800);
      V(800);
      V(800);


    }else{
      
      while(val < 100){
        val += 2;
        printf("pere : %d " , val);
        if(val % 5 == 0){
          printf("\n");
          V(700);
          P(800);
        }

      }
      wait(NULL);
      
        
    }
    

    return 0 ; 
}