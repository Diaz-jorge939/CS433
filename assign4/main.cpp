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
using namespace std;

// global buffer object
Buffer buffer;

// Declare a semaphore and a mutex
pthread_mutex_t mutex;
int empty = 10;
int full = 0;

// Function that waits for the semaphore to become available
void wait_for_semaphore() {
    // Acquire the mutex
    pthread_mutex_lock(&mutex);
    while (semaphore == 0) {
        // Wait for the condition variable to be signaled
        pthread_cond_wait(&cond, &mutex);
    }
    // Decrement the semaphore
    semaphore--;
    // Release the mutex
    pthread_mutex_unlock(&mutex);
}

// Function that signals that the semaphore is now available
void signal_semaphore() {
    // Acquire the mutex
    pthread_mutex_lock(&mutex);
    // Increment the semaphore
    semaphore++;
    // Signal the condition variable
    pthread_cond_signal(&cond);
    // Release the mutex
    pthread_mutex_unlock(&mutex);
}


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
        while (count == BUFFER_SIZE) {}     // busy waiting, do nothing

        if (buffer.insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Producer error condition"  << endl;    // shouldn't come here
        }
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
        if (buffer.remove_item(&item)) {
            cout << "Consumer " << item << ": Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer error condition" << endl;    // shouldn't come here
        }
    }
}

int main(int argc, char *argv[]) {
    /* TODO: 1. Get command line arguments argv[1],argv[2],argv[3] */
    // How long does the main thread sleep before terminating (in seconds)
    // he number of producer threads
    // The number of consumer threads 
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        exit(1);
    }

    int sleep_time = std::stoi(argv[1]);
    int producer_threads = stoi(argv[2]);
    int consumer_threads = stoi(argv[3]);

    /* TODO: 2. Initialize buffer and synchronization primitives */
    /* TODO: 3. Create producer thread(s).
     * You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
    /* TODO: 4. Create consumer thread(s) */
    /* TODO: 5. Main thread sleep */
    /* TODO: 6. Exit */
}
