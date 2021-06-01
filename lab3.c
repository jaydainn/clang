#include <stdlib.h>

int aleatoire(){
    return (rand()%101 - 50) * 2;
}

int main(){
srand(getpid());
printf("%d \n \n" , aleatoire());
    

    int pid1 , pid2 , pid3 ; 

    
        if(fork() == 0){
srand(getpid());
printf("%d \n \n" , aleatoire());
        }else{
            if(fork() == 0){
srand(getpid());
printf("%d \n \n" , aleatoire());
            }else{
                if(fork() == 0){
srand(getpid());
printf("%d \n \n" , aleatoire());
                }else{

                }
            }
        }
    

    return 0 ;
}