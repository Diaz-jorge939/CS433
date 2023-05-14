/**
* Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author Jorge Diaz
 * @brief A class implementing the LIFO page replacement algorithms
 * @version 0.1
 */

#include "lifo_replacement.h"

LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
}

// TODO: Add your implementations for desctructor, load_page, replace_page here
LIFOReplacement::~LIFOReplacement() {

}

// Access an invalid page, but free frames are available
void LIFOReplacement::load_page(int page_num) {
    //getpage entry - update valid bit and frame number
    PageEntry* entry_ptr = getPageEntryaddress(page_num);

    entry_ptr->valid = true;
    entry_ptr->frame_num = frame_counter;

    // push the page into the queue
    stack.push_back(entry_ptr);

    //increment frame number
    frame_counter++;
}

// Access an invalid page and no free frames are available
int LIFOReplacement::replace_page(int page_num) {
    // Update your data structure FIFO replacement and pagetable

    // before removing, update valid bit to 0 
    PageEntry* replaced_page = stack.back();
    replaced_page->valid = false;
    replaced_page->frame_num = 0;

    //removing first page entry from FIFO replacement data structure
    stack.pop_back();

    //update pagetable
    PageEntry* entry = getPageEntryaddress(page_num);

    entry->frame_num = frame_counter;
    entry->valid = true;

    frame_counter--;

    return 0;
}