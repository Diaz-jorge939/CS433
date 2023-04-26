/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Jorge Diaz
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */

#include <iostream>
#include "buffer.h"
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

using namespace std;

// global buffer object
Buffer buffer;

// Declare a semaphore and a mutex
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

// Producer thread function
// TODO: Add your implementation of the producer thread here
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *) param);

    while (true) {
        /* sleep for a random period of time */
        usleep(rand()%1000000);

        // TODO: Add synchronization code here
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        if (buffer.insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Producer error condition"  << endl;    // shouldn't come here
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

// Consumer thread function
// TODO: Add your implementation of the consumer thread here
void *consumer(void *param) {
    buffer_item item;

    while (true) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);
        // TODO: Add synchronization code here

        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        if (buffer.remove_item(&item)) {
            cout << "Consumer " << item << ": Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer error condition" << endl;    // shouldn't come here
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main(int argc, char *argv[]) {
    /* TODO: 1. Get command line arguments argv[1],argv[2],argv[3] */

    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        exit(1);
    }

    int sleep_time = stoi(argv[1]);
    int num_producer_threads = stoi(argv[2]);
    int num_consumer_threads = stoi(argv[3]);

    int arr [num_producer_threads];

    /* TODO: 2. Initialize buffer and synchronization primitives */
    buffer = Buffer(5);
    
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);

    //TODO: 3. Create producer thread(s).
    // Create a set of threads
    // declare an array of thread IDs
    pthread_t producer_threads[num_producer_threads];

    for (int i = 0; i < num_producer_threads; i++)
    {
        arr[i] = i+1; 
    }

    // loop to create threads
    for (int i = 0; i < num_producer_threads; i++) {
        // create the thread
        int result = pthread_create(&producer_threads[i], NULL, producer, &arr[i]);
        if (result != 0) {
            // handle error
            fprintf(stderr, "Error creating thread %d: %s\n", i, strerror(result));
            exit(1);
        }

    }
    /* You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
    /* TODO: 4. Create consumer thread(s) */
    pthread_t consumer_threads[num_producer_threads];

    // loop to create threads
    for (int i = 0; i < num_consumer_threads; i++) {
        // create the thread
        int result = pthread_create(&consumer_threads[i], NULL, consumer, NULL);
        if (result != 0) {
            // handle error
            fprintf(stderr, "Error creating thread %d: %s\n", i, strerror(result));
            exit(EXIT_FAILURE);
        }
    }
    /* TODO: 5. Main thread sleep */
    sleep(sleep_time); 
    /* TODO: 6. Exit */
    exit(0);
}
