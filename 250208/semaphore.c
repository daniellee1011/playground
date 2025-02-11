#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_ITMES 5

sem_t empty_slots;
sem_t full_slots;

void *producer(void *arg) {
    for (int i = 0; i < NUM_ITMES; i++) {
        sem_wait(&empty_slots); // Wait for an empty slot
        printf("Produced item %d\n", i);
        sem_post(&full_slots); // Signal that an item is produced
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < NUM_ITMES; i++) {
        sem_wait(&full_slots); // Wait for an available item
        printf("Consumed item %d\n", i);
        sem_post(&empty_slots); // Signal that a slot is free
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    sem_init(&empty_slots, 0, NUM_ITMES); // Initialize semaphore with NUM_ITEMS empty slots
    sem_init(&full_slots, 0, 0); // Initially, no items are produced

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destory(&empty_slots);
    sem_destory(&full_slots);

    return 0;
}