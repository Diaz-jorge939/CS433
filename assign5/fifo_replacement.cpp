/**
* Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author Jorge Diaz
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */

#include "fifo_replacement.h"
#include <queue>

FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames){
}

FIFOReplacement::~FIFOReplacement() {
}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    

    //getpage entry - update valid bit and frame number
    PageEntry* entry_ptr = getPageEntryaddress(page_num);

    entry_ptr->valid = true;
    entry_ptr->frame_num = frame_counter;

    // push the page into the queue
    queue.push(entry_ptr);

    

    //increment frame number
    frame_counter++;
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    // Update your data structure FIFO replacement and pagetable

    // before removing, update valid bit to 0 
    PageEntry* replaced_page = queue.front();
    replaced_page->valid = false;
    replaced_page->frame_num = 0;


    //removing first page entry from FIFO replacement data structure
    queue.pop();

    //update pagetable
    PageEntry* entry = getPageEntryaddress(page_num);

    entry->frame_num = frame_counter;
    entry->valid = true;

    frame_counter--;

    return 0;
}
