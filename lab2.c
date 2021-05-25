#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int p1[2], p2[2];
    if(argc<2)
        exit(0);

    int val= atoi(argv[1]) ;
    int cpt=0;
    pipe(p1);
    pipe(p2);
    if(val%2==0)
        write(p1[1], &val, sizeof(int));
    else
        write(p2[1], &val, sizeof(int));
    if(fork()==0){
        //Fils :s'occupe des valeurs impairs

        close(p2[1]); close(p1[0]);
        while(read(p2[0], &val, sizeof(int))!=0){
            printf("%d\n", val);
            cpt++;
            //sleep(1);
            val = val * 3 + 1;
            write(p1[1], &val, sizeof(int));
        }
        close(p2[0]); close(p1[1]);
        // Envoi du nombre d'iétrations réalisés par le fils
        exit(cpt);
    }
    else{
        //Fils :s'occupe des valeurs impairs
        close(p1[1]); close(p2[0]);
        while(read(p1[0], &val, sizeof(int))!=0){
            while(val%2==0){
                printf("%d\n", val);
                cpt++;
                //sleep(1);
                val = val / 2;
            }
            if(val==1){
                printf("%d\n", val);
                break;
            }
            write(p2[1], &val, sizeof(int));
        }
        close(p2[1]); close(p1[0]);
        // Récupérer le nombre d'iétarions réalisés par le fils
        int status;
        wait(&status);
        status = WEXITSTATUS(status);
        cpt+=status;
        printf("Nombre itérations : %d\n", cpt);
    }
    return 0;
}
