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
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

Buffer::Buffer(int size){
    /* the buffer */
    this->buffer_size = size;
    //arr_buffer = new buffer_item[size];
}
Buffer::~Buffer(){
}

bool Buffer::insert_item(buffer_item item){
    /* insert item into buffer
   return 0 if successful, otherwise
   return -1 indicating an error condition */
   
//     // Insert the item into the buffer
//    if(count == 0){
//     int insert_index = (in) % buffer_size;
//    }
//    else{
//     int insert_index = (in + 1) % buffer_size;
//    }
    
//     arr_buffer[insert_index] = item;
//     in = insert_index;
//     count++;

    while(arr_buffer.size() == buffer_size); // do nothing. buffer is full
    if(arr_buffer.size() < buffer_size) {
        arr_buffer.push_back(item);
        return true;
    } else {
        return false;
    }

    
}
bool Buffer::remove_item(buffer_item *item){
    /* remove an object from buffer
   placing it in item
   return 0 if successful, otherwise
   return -1 indicating an error condition */
    // get item from buffer
    // *item = arr_buffer[out];
    // out = (out+ 1) % buffer_size;
    // count--;
    while(arr_buffer.empty()); //do nothing buffer is empty
    if (arr_buffer.empty()) {
        return false;
    }

    *item = arr_buffer.back();
    arr_buffer.pop_back();

    return true;

}
int Buffer::get_size(){
    return buffer_size;
    
}
int Buffer::get_count(){
    return arr_buffer.size();
}
bool Buffer::is_empty(){
    if(arr_buffer.empty()){
        return true;
    }

    return false;
}

void Buffer::print_buffer(){
    
    if(arr_buffer.size() <= 1){
        cout << "Buffer: ["<< arr_buffer[0] << "]" << endl;
        return;
    }
    
    
    cout << "Buffer: [";
    for (int i = 0; i < arr_buffer.size(); i++) {
        if(i == arr_buffer.size()-1){
            cout << arr_buffer[i] << "]"<< endl;
            break;
        }
        cout << arr_buffer[i] << ", ";
    }
}