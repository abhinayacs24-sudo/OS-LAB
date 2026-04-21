#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 3
#define ITEMS 8

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty, full, mutex;

void *producer(void *arg) {
    for (int i = 0; i < ITEMS; i++) {

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = i;
        printf("Produced: %d at buffer[%d]\n", i, in);

        in = (in + 1) % SIZE;

        sem_post(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg) {
    int item;

    for (int i = 0; i < ITEMS; i++) {

        sem_wait(&full);
        sem_wait(&mutex);

        item = buffer[out];
        printf("Consumed: %d from buffer[%d]\n", item, out);

        out = (out + 1) % SIZE;

        sem_post(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main() {
    pthread_t p, c;

    sem_init(&empty, 0, SIZE); // 3 empty slots
    sem_init(&full, 0, 0);     // 0 full slots
    sem_init(&mutex, 0, 1);    // lock

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    return 0;
}
