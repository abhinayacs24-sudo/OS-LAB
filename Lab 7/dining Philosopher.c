#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];
sem_t room;

void *philosopher(void *num) {
    int id = *(int *)num;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        sem_wait(&room);

        // pick left fork
        sem_wait(&forks[id]);
        printf("Philosopher %d picked up left fork %d.\n", id, id);

        // pick right fork
        sem_wait(&forks[(id + 1) % N]);
        printf("Philosopher %d picked up right fork %d.\n", id, (id + 1) % N);

        printf("Philosopher %d is eating.\n", id);
        sleep(1);

        // put forks down
        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);

        printf("Philosopher %d put down forks %d and %d.\n",
               id, id, (id + 1) % N);

        sem_post(&room);
    }
}

int main() {
    pthread_t ph[N];
    int ids[N];

    sem_init(&room, 0, N - 1);

    for (int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&ph[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(ph[i], NULL);

    return 0;
}
