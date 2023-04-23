/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author Jorge Diaz
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include "buffer.h"
#include <semaphore.h>
#include <pthread.h>

Buffer::Buffer(int size){
    /* the buffer */
    this->buffer_size = size;
    arr_buffer = new buffer_item[size];

}
Buffer::~Buffer(){
    delete arr_buffer[];
}

bool Buffer::insert_item(buffer_item item){
    /* insert item into buffer
   return 0 if successful, otherwise
   return -1 indicating an error condition */
   // Insert the item into the buffer

    // Wait on the empty semaphore to ensure there is space in the buffer
    if (sem_wait(&empty) == -1) {
        perror("sem_wait");
        exit(1);
    }

    // Acquire the mutex lock to ensure mutual exclusion
    if (pthread_mutex_lock(&mutex) != 0) {
        perror("pthread_mutex_lock");
        exit(1);
    }

    // Insert the item into the buffer
    int insert_index = (in + 1) % buffer_size;
    buffer[insert_index] = item;
    in = insert_index;
    count++;

    // Release the mutex lock
    if (pthread_mutex_unlock(&mutex) != 0) {
        perror("pthread_mutex_unlock");
        exit(1);
    }

    // Signal the full semaphore to indicate that there is one more item in the buffer
    if (sem_post(&full) == -1) {
        perror("sem_post");
        exit(1);
    }

    return true;

    
}
bool Buffer::remove_item(buffer_item *item){
    /* remove an object from buffer
   placing it in item
   return 0 if successful, otherwise
   return -1 indicating an error condition */

}
int Buffer::get_size(){
    
    
}
int Buffer::get_count(){

}
bool Buffer::is_empty(){

}

void Buffer::print_buffer(){

}