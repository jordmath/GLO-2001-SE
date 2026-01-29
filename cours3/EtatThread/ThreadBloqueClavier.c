#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* keyboard_thread(void* arg) {
    char c;
    printf("Appuyez sur une touche...\n");
    read(STDIN_FILENO, &c, 1);   // bloquant jusqu’à une touche + Enter
    printf("Touche appuyée : %c\n", c);
    return NULL;
}

int main() {
    pthread_t t;

    pthread_create(&t, NULL, keyboard_thread, NULL);
    pthread_join(t, NULL);  // attend que le thread se termine

    return 0;
}
