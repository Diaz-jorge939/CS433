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


Buffer::Buffer(int size){
    /* the buffer */
    arr_buffer = new int[size];

}
Buffer::~Buffer(){
    del arr_buffer[];
}

bool Buffer::insert_item(buffer_item item){
    /* insert item into buffer
   return 0 if successful, otherwise
   return -1 indicating an error condition */
   while (true) {
        . . .
    /* produce an item in next_produced */
        . . .
    wait(empty);
    wait(mutex);
        . . .
    /* add next_produced to the buffer */
        . . .
    signal(mutex);
    signal(full);
    }
    
}
bool Buffer::remove_item(buffer_item *item){
    /* remove an object from buffer
   placing it in item
   return 0 if successful, otherwise
   return -1 indicating an error condition */
   while (true) {
        wait(full);
        wait(mutex);
            . . .
        /* remove an item from buffer to next_consumed */
            . . .
        signal(mutex);
        signal(empty);
            . . .
        /* consume the item in next_consumed */
            . . .
    }

}
int Buffer::get_size(){
    
    
}
int Buffer::get_count(){

}
bool Buffer::is_empty(){

}

void Buffer::print_buffer(){

}