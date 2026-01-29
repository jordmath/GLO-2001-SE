#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *print_hello(void *unused) {
  printf("Bonjour je suis un thread.\n");
  pthread_exit(NULL);
}


int main(int argc, char *argv[]) {


  pthread_t thread;
  // int status = pthread_create(&thread, NULL, print_hello, NULL);
    // if (status != 0) {
    //   printf("oops, code d'erreur pthread: %d\n",status);
    //   exit(-1);
    // }

    // attendre que le thread termine
    //pthread_join(thread, NULL);
    //ou
    //sleep(1);
    
    //appel directe de la fonction qui contient un exit, on ne va pas se rendre a la fin.
    //commenter le create.
    print_hello(NULL);
    
    printf("fin du programme.\n");
    
    return 0;
}

