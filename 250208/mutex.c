#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

pthread_mutex_t mutex;
int shared_counter = 0;

void *increment_counter(void *arg) {
    int thread_id = *(int *)arg;
    pthread_mutex_lock(&mutex);

    printf("Thread %d: Entering critical section.\n", thread_id);
    int temp = shared_counter;
    sleep(1); // Simulate work
    shared_counter = temp + 1;
    printf("Thread %d: Updated counter to %d\n", thread_id, shared_counter);

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        threads_ids[i] = i;
        pthread_create(&threads[i], NULL, increment_counter, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i+++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value: %d\n", shared_counter);
    pthread_mutex_destroy(&mutex);

    return 0;
}