// // /*
// //  * The Buddy Page Allocator
// //  * SKELETON IMPLEMENTATION TO BE FILLED IN FOR TASK 2
// //  */

// // #include <infos/mm/page-allocator.h>
// // #include <infos/mm/mm.h>
// // #include <infos/kernel/kernel.h>
// // #include <infos/kernel/log.h>
// // #include <infos/util/math.h>
// // #include <infos/util/printf.h>



// // using namespace infos::kernel;
// // using namespace infos::mm;
// // using namespace infos::util;

// <<<<<<< HEAD
// // #define MAX_ORDER	18
// // // struct Llist {
// // // 	head;
// // // 	tail;
// // // 	void add_pg(PageDescriptor *pg){
// // // 		pg->next_free = NULL;
// // // 		if(head == NULL)
// // // 		{
// // // 			head = *pg;
// // // 			tail = *pg;
// // // 		}
// // // 		else
// // // 		{
// // // 			tail->next_free = pg;
// // // 			tail = tail->next_free;
// // // 		}
// // // 	}
// // // 	void delete_pg(PageDescriptor *pg){   
// // // 		if (head == pg) //if pg is the head node
// // // 		{
// // // 			head = head->next_free;
// // // 			head->next_free = head.next_free.next_free; 
// // // 		}else{
// // // 			PageDescriptor *temp;
// // // 			*temp = pg->next_free;
// // // 			pg->next_free = temp->next_free;
// // // 		}
// // // 	}
// // // };
// // /**
// //  * A buddy page allocation algorithm.
// //  */
// // class BuddyPageAllocator : public PageAllocatorAlgorithm
// // {
// // private:
// // 	/** Given a page descriptor, and an order, returns the buddy PGD.  The buddy could either be
// // 	 * to the left or the right of PGD, in the given order.
// // 	 * @param pgd The page descriptor to find the buddy for.
// // 	 * @param order The order in which the page descriptor lives.
// // 	 * @return Returns the buddy of the given page descriptor, in the given order.
// // 	 */
// // 	 private:
// // 	PageDescriptor *_free_areas[MAX_ORDER+1];
// // 	PageDescriptor *buddy_of(PageDescriptor *pgd, int order)
// // 	{
// //         // TODO: Implement me!
// // 		PageDescriptor *pg = _free_areas[order];
// // 		int i = 0;
// // 		//fid its index
// // 		PageDescriptor prev = *pg; 
// // 		while(pg){
// // 			if (*pg->next_free == *pgd){
// // 				if(i%2 ==0){
// // 					return pg;
// // 				}else{
// // 					return pgd->next_free;
// // 				}
// // 				break;
// // 			}
// // 			i++;
// // 		}
// // 	}

// // 	/**
// // 	 * Given a pointer to a block of free memory in the order "source_order", this function will
// // 	 * split the block in half, and insert it into the order below.
// // 	 * @param block_pointer A pointer to a pointer containing the beginning of a block of free memory.
// // 	 * @param source_order The order in which the block of free memory exists.  Naturally,
// // 	 * the split will insert the two new blocks into the order below.
// // 	 * @return Returns the left-hand-side of the new block.
// // 	 */
// // 	PageDescriptor *split_block(PageDescriptor **block_pointer, int source_order)
// // 	{
// //         // TODO: Implement me!
// //         //add below
		
// // 		//PageDescriptor b = *block_pointer[0];
// // 		int add = 0;         
// // 		for(int i=0;i<source_order;i++)
// // 		{
// // 			add *=2;
// // 		}
// // 		PageDescriptor half = *block_pointer[add];
// // 		// PageDescriptor *pg = _free_areas[source_order-1];
// // 		//implement add and remov
// // 		PageDescriptor pg = *_free_areas[source_order-1];
// // 		if (pg==NULL){
// // 			pg = **block_pointer;
// // 			pg->next_free = half;
// // 		}else{
// // 			while(pg){
// // 				if(pg->next_free=NULL){
// // 					pg->next_free = **block_pointer;
// // 					pg->next_free->next_free = half;
// // 				}
// // 				pg = pg->next_free;
// // 		}
// // 		//remove 
// // 		*pg = _free_areas[source_order];
// // 		while(pg){
// // 			if(pg == *block_pointer){
// // 				pg = pg->next_free;
// // 			}
// // 			pg = pg->next_free;
// // 		}  
// // 	}

// // 	/**
// // 	 * Takes a block in the given source order, and merges it (and its buddy) into the next order.
// // 	 * @param block_pointer A pointer to a pointer containing a block in the pair to merge.
// // 	 * @param source_order The order in which the pair of blocks live.
// // 	 * @return Returns the new slot that points to the merged block.
// // 	 */
// // 	PageDescriptor **merge_block(PageDescriptor **block_pointer, int source_order){
// //         // TODO: Implement me!
// //          //add above

// //         PageDescriptor *buddy = buddy_of(*block_pointer, source_order);
// // 		//compare the smaller one 
// // 		PageDescriptor nblock;
// // 		if(*buddy<**block_pointer){
// // 			nblock = *buddy;
// // 		}else{
// // 			nblock = block_pointer;
// // 		}
// // 		PageDescriptor *pg = _free_areas[source_order+1];
// // 		if (pg==NULL){
// // 			pg = nblock;
// // 			pg->next_free = NULL;
// // 		}else{
// // 			while(pg){
// // 				if(pg->next_free=NULL){
// // 					pg->next_free = nblock;
// // 					pg->next_free->next_free = NULL;
// // 				}
// // 				pg = pg->next_free;
// // 		}
// // 		//remove 
// // 		*pg = *_free_areas[source_order];
// // 		while(pg){
// // 			if(*pg == **block_pointer){
// // 				pg = pg->next_free;
// // 			}
// // 			pg = pg->next_free;
// // 		}   
// // 	}

// // public:
// // 	/**
// // 	 * Allocates 2^order number of contiguous pages
// // 	 * @param order The power of two, of the number of contiguous pages to allocate.
// // 	 * @return Returns a pointer to the first page descriptor for the newly allocated page range, or NULL if
// // 	 * allocation failed.
// // 	 */
// // 	PageDescriptor *allocate_pages(int order) override
// // 	{
// //         // TODO: Implement me!
// //         //check if block is available 
// //         //starting from that order going up

// //         //available in that order
// //         bool found = false;
// //         if(_free_areas[order].size() > 0){
// //             Llist block = _free_areas[order];
// //             PageDescriptor *pg = block.head;
// //             while(pg!= NULL){
// //                  if(pg.type == PageDescriptorType::AVAILABLE){
// //                     pg.type == PageDescriptorType::ALLOCATED;
// //                     found = true;
// //                     break;
// //                  }
// //                  else{
// //                     pg = pg->next_free
// //                  }
// //             }
// //         }
// //         if (found == false){
// //             for(int i = order+1;i < ARRAY_SIZE(_free_areas); i++){
// //                 if(_free_areas[i]->size() > 0){
// //                     Llist block = _free_areas[i];
// //                     PageDescriptor *pg = block.head;
// //                     int b_order = i;
// //                     while(pg!= NULL){
// //                     if(pg.type == PageDescriptorType::AVAILABLE){

// //                         while(_free_areas[order]->size() == 0){
// //                         split_block(**pg,b_order); //split
// //                         b_order -=1;
// //                         }
// //                         //if no loger equal to 0 exists, should now allocate
// //                         pg.type == PageDescriptorType::ALLOCATED;
// //                         found = true;
// //                         break;
// //                     }else{
// //                     pg = pg->next_free;
// //                     }
// //                     }  
// //                 }
// //                 if(found==true){
// //                     break;
// //                 }
// //             }
// //         }else{
// //             catch{
// //                 mm_log.messagef(LogLevel::DEBUG, "Memory Full:");}     
// //         }
// // 	}

// //     /**
// // 	 * Frees 2^order contiguous pages.
// // 	 * @param pgd A pointer to an array of page descriptors to be freed.
// // 	 * @param order The power of two number of contiguous pages to free.
// // 	 */
// //     void free_pages(PageDescriptor *pgd, int order) override
// //     {
// //         // TODO: Implement me!
// //         //traverse the linked list and look for pgd and then change to available 
// //         PageDescriptor head = _free_area[order].head
// //         while (head =! NULL){
// //             if(pgd = head){
// //                 pgd.type == PageDescriptorType::AVAILABLE;
// //                 //need to merge blocks
// //                 int in_order = order;
// //                 PageDescriptor *buddy = *buddy_of(*pgd,order)
// //                 while (buddy.type == PageDescriptorType::AVAILABLE){
// //                     **merge_block( **pgd, int source_order)
// //                     *pgd = min(*pgd,*buddy);
// //                     in_order +=1;
// //                 }
// //                 break;
// //             }
// //              head = head.next_free;
// //         }
// //     }

// //     /**
// //      * Marks a range of pages as available for allocation.
// //      * @param start A pointer to the first page descriptors to be made available.
// //      * @param count The number of page descriptors to make available.
// //      */
// //     virtual void insert_page_range(PageDescriptor *start, uint64_t count) override
// //     {
// //         // TODO: Implement me!
// //         int req_order = ilog2_ceil(count);
// //         int cur_order = MAX_ORDER;
// //         while (cur_order > req_order){
// //             split_block(**start, cur_order)
// //             cur_order --;
// //         }
// //         if (cur_order==req_order){ //mark available
// //             start->type == PageDescriptorType::AVAILABLE;
// //         }
// //     }
// =======
// #define MAX_ORDER	18
// class BuddyPageAllocator : public PageAllocatorAlgorithm
// {
// private:
// 	/** Given a page descriptor, and an order, returns the buddy PGD.  The buddy could either be
// 	 * to the left or the right of PGD, in the given order.
// 	 * @param pgd The page descriptor to find the buddy for.
// 	 * @param order The order in which the page descriptor lives.
// 	 * @return Returns the buddy of the given page descriptor, in the given order.
// 	 */
// 	PageDescriptor *buddy_of(PageDescriptor *pgd, int order)
// 	{
//         // TODO: Implement me!
// 		int mid = (0.5<<order);
// 		if (order < MAX_ORDER){
// 			if((uintptr_t)pgd %2 == 0){//start is even --buddy right
// 				return pgd + mid;
// 			}else{//start is odd--buddy left
// 				return pdg-mid;
// 			}
// 		}
// 		else if(order == MAX_ORDER){
// 			mm_log.messagef(LogLevel::DEBUG, "This is the Largest Block, no buddy");
// 		}
// 		else{
// 			mm_log.messagef(LogLevel::DEBUG, "order exceeding MAX_ORDER, there is no buddy");
// 		}
// 	}

// 	/**
// 	 * Given a pointer to a block of free memory in the order "source_order", this function will
// 	 * split the block in half, and insert it into the order below.
// 	 * @param block_pointer A pointer to a pointer containing the beginning of a block of free memory.
// 	 * @param source_order The order in which the block of free memory exists.  Naturally,
// 	 * the split will insert the two new blocks into the order below.
// 	 * @return Returns the left-hand-side of the new block.
// 	 */
// 	PageDescriptor *split_block(PageDescriptor **block_pointer, int source_order)
// 	{
//         // TODO: Implement me!
//         //add below

// 		if(source_order >0) {
// 			int mid = (0.5 << order);
// 			PageDescriptor *pg = _free_areas[i];
// 			PageDescriptor *s_half = *block_pointer+mid;
// 			//remove
// 			if(*block_pointer == pg)
// 			{
// 			_free_areas[source_order] = *block_pointer->next_free;
// 			}
// 			//add
// 			_free_areas[source_order-1] = *block_pointer;
// 			*block_pointer->next_free = s_half;

			
// 		}else{
// 			mm_log.messagef(LogLevel::DEBUG, "Source order is 0, Cannot split it further");
// 		}
// 		return &_free_areas[source_order-1];
// 	}

// 	/**
// 	 * Takes a block in the given source order, and merges it (and its buddy) into the next order.
// 	 * @param block_pointer A pointer to a pointer containing a block in the pair to merge.
// 	 * @param source_order The order in which the pair of blocks live.
// 	 * @return Returns the new slot that points to the merged block.
// 	 */
// 	PageDescriptor **merge_block(PageDescriptor **block_pointer, int source_order){
//         // TODO: Implement me!
//          //add above
// 		int mid = (0.5 << order);
// 		PageDescriptor *pg = _free_areas[i];
// 		PageDescriptor *s_half = *block_pointer+mid;
// 		PageDescriptor **buddy = buddy_of(**block_pointer);
		
// 		if(block_pointer < buddy){//buddy starts
// 		_free_areas[source_order+1] = *block_pointer;//add block
// 		_free_areas[source_order] = *buddy->next_free;//remove blocks
// 		}else{
// 			_free_areas[source_order+1] = *buddy;//add block
// 			_free_areas[source_order] = *block_pointer->next_free;//remove blocks

// 		}
// 		return &_free_areas[source_order+1];
// 	}

// public:
// 	/**
// 	 * Allocates 2^order number of contiguous pages
// 	 * @param order The power of two, of the number of contiguous pages to allocate.
// 	 * @return Returns a pointer to the first page descriptor for the newly allocated page range, or NULL if
// 	 * allocation failed.
// 	 */
// 	PageDescriptor *allocate_pages(int order) override
// 	{
//         // TODO: Implement me!
//         bool found = false;
// 		for(int i = order;i < ARRAY_SIZE(_free_areas); i++){
// 			PageDescriptor *pg = _free_areas[i];
// 			while(pg != NULL){
// 				if(pg.type == PageDescriptorType::AVAILABLE){
// 					if(i==order){
// 						pg.type == PageDescriptorType::ALLOCATED;
// 						found = true;
// 						break;
// 					}else{
// 						int b_order = i;
// 						while(&_free_areas[order] == NULL){
// 							split_block(**pg,b_order); //split
// 							b_order -=1;
// 						}
// 						//should now allocate
// 						pg.type == PageDescriptorType::ALLOCATED;
// 						found = true;
// 						break;
// 					}
// 				}
// 				else{
//                     pg = pg->next_free
// 				}
//             }
// 		}
// 		if found = false{
//             catch{
//                 mm_log.messagef(LogLevel::DEBUG, "Memory Full:");
// 				return NULL;}     
//         }
// 		return &_free_areas[order];
// 	}

//     /**
// 	 * Frees 2^order contiguous pages.
// 	 * @param pgd A pointer to an array of page descriptors to be freed.
// 	 * @param order The power of two number of contiguous pages to free.
// 	 */
//     void free_pages(PageDescriptor *pgd, int order) override
//     {
//         // TODO: Implement me!
//         //traverse the linked list and look for pgd and then change to available 
//         PageDescriptor *head = &_free_area[order];
//         while (head =! NULL){
//             if(pgd = head){
//                 pgd.type == PageDescriptorType::AVAILABLE;
//                 //need to merge blocks
//                 int in_order = order;
//                 PageDescriptor *buddy = buddy_of(*pgd,order)
//                 while (buddy.type == PageDescriptorType::AVAILABLE){
//                     merge_block( **pgd, int source_order)
//                     *pgd = min(*pgd,*buddy);
//                     in_order +=1;
//                 }
//                 break;
//             }
//              head = head->next_free;
//         }
//     }

//     /**
//      * Marks a range of pages as available for allocation.
//      * @param start A pointer to the first page descriptors to be made available.
//      * @param count The number of page descriptors to make available.
//      */
//     virtual void insert_page_range(PageDescriptor *start, uint64_t count) override
//     {
//         // TODO: Implement me!
//         uint64_t req_order = ilog2_ceil(count);
//         uint64_t cur_order = MAX_ORDER;
//         while (cur_order > req_order){
//             split_block(**start, cur_order)
//             cur_order --;
//         }
//         if (cur_order==req_order){ //mark available
//             start->type == PageDescriptorType::AVAILABLE;
//         }
//     }
// >>>>>>> b0c129faaae2a919f8ef0cd7a2fef74c39069aee

// //     /**
// //      * Marks a range of pages as unavailable for allocation.
// //      * @param start A pointer to the first page descriptors to be made unavailable.
// //      * @param count The number of page descriptors to make unavailable.
// //      */
// //     virtual void remove_page_range(PageDescriptor *start, uint64_t count) override
// //     {
// //         // TODO: Implement me!
// //         int req_order = ilog2_ceil(count);
// //         int cur_order = MAX_ORDER;
// //         while (cur_order > req_order){
// //             split_block(**start, cur_order)
// //             cur_order --;
// //         }
// //         if (cur_order==req_order){ //reserve
// //             start.type == PageDescriptorType::RESERVED;
// //         }
// //     }

// <<<<<<< HEAD
// // 	/**
// // 	 * Initialises the allocation algorithm.
// // 	 * @return Returns TRUE if the algorithm was successfully initialised, FALSE otherwise.
// // 	 */
// // 	bool init(PageDescriptor *page_descriptors, uint64_t nr_page_descriptors) override
// // 	{
// //         // TODO: Implement me!   
// // 		for(int i = 0; i < ARRAY_SIZE(_free_areas); i++){
// //             Llist block;
// //             _free_area[i] = block;
// //         }
// // 	}
// =======
// 	/**
// 	 * Initialises the allocation algorithm.
// 	 * @return Returns TRUE if the algorithm was successfully initialised, FALSE otherwise.
// 	 */
// 	bool init(PageDescriptor *page_descriptors, uint64_t nr_page_descriptors) override
// 	{
//         // TODO: Implement me!   
// 		//initialize the free lists
// 		mm_log.messagef(LogLevel::DEBUG, "Buddy Page Allocator online");
// 		_pgd_base = page_descriptors;
// 		_nr_pgds = nr_page_descriptors;
// 		_free_area[max] = _pgd_base;
// 		return true;
// 	}
// >>>>>>> b0c129faaae2a919f8ef0cd7a2fef74c39069aee

// // 	/**
// // 	 * Returns the friendly name of the allocation algorithm, for debugging and selection purposes.
// // 	 */
// // 	const char* name() const override { return "buddy"; }

// // 	/**
// // 	 * Dumps out the current state of the buddy system
// // 	 */
// // 	void dump_state() const override
// // 	{
// // 		// Print out a header, so we can find the output in the logs.
// // 		mm_log.messagef(LogLevel::DEBUG, "BUDDY STATE:");

// // 		// Iterate over each free area.
// // 		for (unsigned int i = 0; i < ARRAY_SIZE(_free_areas); i++) {
// // 			char buffer[256];
// // 			snprintf(buffer, sizeof(buffer), "[%d] ", i);

// // 			// Iterate over each block in the free area.
// // 			PageDescriptor *pg = _free_areas[i];
// // 			while (pg) {
// // 				// Append the PFN of the free block to the output buffer.
// // 				snprintf(buffer, sizeof(buffer), "%s%lx ", buffer, sys.mm().pgalloc().pgd_to_pfn(pg));
// // 				pg = pg->next_free;
// // 			}

// // 			mm_log.messagef(LogLevel::DEBUG, "%s", buffer);
// // 		}
// // 	}

// <<<<<<< HEAD
// // }
// // // private:
// // // 	PageDescriptor *_free_areas[MAX_ORDER+1];
// // // 	//Llist *_free_areas[MAX_ORDER+1];
// // };
// =======
// }
// private:
// 	PageDescriptor *_free_areas[MAX_ORDER+1];

// };
// >>>>>>> b0c129faaae2a919f8ef0cd7a2fef74c39069aee

// // /* --- DO NOT CHANGE ANYTHING BELOW THIS LINE --- */

// // /*
// //  * Allocation algorithm registration framework
// //  */
// // RegisterPageAllocator(BuddyPageAllocator);???