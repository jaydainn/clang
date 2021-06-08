#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define n 10 

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

int main (){

    int *a ;
    int num_mema;
    num_mema = shmget(600, sizeof(int) * n, IPC_CREAT | 0666);
    a = (int *) shmat(num_mema, 0, 0);
    for(int i = 0 ; i < n ; i++){
        if( i %2 == 0){
            a[i] = 23 + i ; 
        }else{
            a[i] = 23 - i;
        }
    }
    if(fork() == 0){
    num_mema = shmget(600, sizeof(int) * n, IPC_CREAT | 0666);
    a = (int *) shmat(num_mema, 0, 0);
    //printf(" max : %d \n" , max(a));
    //printf(" index 16 : %d \n" , findIndex(a , 16));
    // first 5 elems 

    int b [n/2] ;
    for(int i = 0 ; i < n/2 ; i++){
        b[i] = a[i];
    }
    printf("min b : %d \n" , min(b));
    printf( "max b : %d \n" , max(b));


    }else{
        int c [n/2] ;
    for(int i = (n/2) ; i < n ; i++){
        c[i] = a[i];
    }
    printf("min c : %d \n" , min(c));
    printf( "max c : %d \n" , max(c));

    }

    
}