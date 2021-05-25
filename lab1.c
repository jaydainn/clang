#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define LECTURE 0
#define ECRITURE 1
int p[2];

int main(){
    pipe(p);
    char car = 'a';
    int pid;
    pid = fork();
    if(pid == 0){
        close(p[LECTURE]);
        while((car = getchar() )!= '$' ){
            if(isalpha(car)){
            write(p[ECRITURE] , &car , sizeof(char));
            }
        }
        close(p[ECRITURE]);

        
        

    }else{
        close(p[ECRITURE]);
        while(read(p[LECTURE] , &car , sizeof(char)) != 0){
            putchar(toupper(car));
        }
        close(p[LECTURE]);
    
    }

    return 0 ; 
}