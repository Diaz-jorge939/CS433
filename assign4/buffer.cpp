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
    int insert_index = (in + 1) % BUFFER_SIZE;
    buffer[insert_index] = item;
    in = insert_index;
    count++;
    
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