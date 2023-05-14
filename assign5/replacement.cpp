/**
* Assignment 5: Page replacement algorithms
 * @file replacement.cpp
 * @author Jorge Diaz
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */

#include <iostream>
#include "replacement.h"

// Constructor
Replacement::Replacement(int num_pages, int num_frames)
: page_table(num_pages)
{
	pagefaults_count = 0;
    pageReplacements_count = 0;
    num_references = 0;
    frames_limit = num_frames;
    frame_counter = 0;
}

// Destructor
Replacement::~Replacement()
{}

// Simulate a single page access 
// @return true if it's a page fault
bool Replacement::access_page(int page_num, bool is_write)
{
    // track number of references
    num_references++;

  if (!page_table[page_num].valid) 
  {
    // If the page is not valid but free frames are available, it calls the load_page function 
	  if (frame_counter < frames_limit) {
      		load_page(page_num);
      		frame_counter++;
	  } 
	  // If the page is not valid and there is no free frame, it calls the replace_page function.
	  else {
		  pageReplacements_count++;
		  replace_page(page_num);
	  }
	  pagefaults_count++;
	  return true;
  }
	// If the page is valid, it calls the touch_page function.
	touch_page(page_num);
	return false;
}

// Print out statistics of simulation
void Replacement::print_statistics() const {
        // print out the number of references, number of page faults and number of page replacements
		std::cout << "Number of references: "  << num_references << std::endl;
		std::cout << "Number of page faults: " << pagefaults_count << std::endl;
		std::cout << "Number of page replacements: " << pageReplacements_count << std::endl;
}
