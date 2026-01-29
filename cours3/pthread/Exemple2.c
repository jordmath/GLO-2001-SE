#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


#define N_THREADS 10

void *print_hello(void *tnum) {
    printf("Bonjour je suis le thread %d\n", *(int*)tnum);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t threads[N_THREADS];
    int Arg[N_THREADS];
    int status, i;

    for (i = 0; i < N_THREADS; i++) {
        Arg[i] = i;
        printf("Main(): en train de creer thread %d\n", i);
        status = pthread_create(&threads[i], NULL, print_hello, (void *)&Arg[i]);
        // pthread_join(threads[i], NULL); // il n y aura pas vraiment de multithreading
    }

    //usleep(500); // sleep mauvaise pratique car latence
    //sleep(1);
    // Attendre que tous les threads terminent
    // for (i = 0; i < N_THREADS; i++) {
    //     pthread_join(threads[i], NULL);
    
    // }
    printf("Tous les threads ont termine.\n");
    
    exit(0);//return 0;
}

