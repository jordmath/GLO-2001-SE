#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  
#include <sys/types.h> 
#include <sys/wait.h> 
int main ( int argc, char *argv[ ] )  { 
  int LePid;
  int Toto =3; 
  printf("Toto = %d\n",Toto);
  LePid=fork(); 
  if (LePid==0) { /* fils */  
    printf("  Fils %d\n",getpid());
    Toto = 5;
    printf("  Toto = %d\n",Toto);
    exit(0); // sans le exit le dernier printf va donner 5. 
  } 
  else { /* le parent seulement */
    printf("  Parent %d\n",getpid());
    Toto = 6; 
    printf("  Toto = %d\n",Toto);
    wait(0); 
  }
  printf("Toto = %d\n",Toto);
}
