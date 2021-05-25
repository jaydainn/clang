#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define LECTURE 0
#define ECRITURE 1
char message_ecrit[] = "Bonjour ! c'est moi";
char message_lu[50];
int p[2];
int pid;
int nb_char;
int main(void)
{
pipe(p) ;
pid = fork();
if (pid == 0)
{
sleep(4);
nb_char = write(p[ECRITURE], message_ecrit, strlen(message_ecrit));
printf("Fils : %d caractères ont été écrits dans le tube.\n" ,nb_char);
}
else
{
printf("Père : Femeture du tube en écriture\n");
close(p[ECRITURE]);
printf("Père : lecture dans le tube...\n");
nb_char = read(p[LECTURE], message_lu, 50);
printf("Père : nb_char = %d\n", nb_char);
printf("Père : message = %s\n",message_lu);
}
wait(NULL); 
printf("\n");

exit(0); }