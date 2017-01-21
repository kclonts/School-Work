#include <cassert>
#include <iostream>
#include "dlUtils.h"
#include "MemoryManager.h"

MemoryManager::MemoryManager(unsigned int memtotal): memsize(memtotal)
{
   baseptr = new unsigned char[memsize];
   blockdata originalBlock(memsize,true,baseptr);
   firstBlock = new dlNode<blockdata>(originalBlock,NULL,NULL);
}

void MemoryManager::showBlockList() 
{
  printDlList(firstBlock,"->");
}

void MemoryManager::splitBlock(dlNode<blockdata> *p, unsigned int chunksize)
{ // Put your code below
	if (chunksize < p->info.blocksize) {

		unsigned int newBlockSize = p->info.blocksize - chunksize;
		unsigned char *newptr = new unsigned char[newBlockSize];
		blockdata newBlock(newBlockSize, true, newptr);

		insertAfter(firstBlock, p, newBlock);

		p->info.blocksize = chunksize;
	}
	else { cout << "Error. Block size too small" << endl; }
}

unsigned char * MemoryManager::malloc(unsigned int request)
{ // Put your code below

	dlNode<blockdata> *p = firstBlock;

	while (p != NULL) {
		if (p->info.blocksize > request && p->info.free == true) {
			splitBlock(p, request);
			p->info.free = false;
			p->info.blocksize = request;
			return p->info.blockptr;

		}
		else if (p->info.blocksize == request && p->info.free == true) {
			p->info.free = false;
			return p->info.blockptr;
		}
		else if (p->next == NULL) {
			return NULL;
			break;
		}
		p = p->next;
	}
}

void MemoryManager::mergeForward(dlNode<blockdata> *p)
{ // Put your code below
	assert(p->next != NULL);
	p->info.blocksize += p->next->info.blocksize;
	deleteNext(p);
}

void MemoryManager::mergeBackward(dlNode<blockdata> *p)
{ // Put your code below
	assert(p->prev != NULL);
	p->info.blocksize += p->prev->info.blocksize;
	deletePrevious(firstBlock, p);
}

void MemoryManager::free(unsigned char *ptr2block)
{ // Put your code below
	dlNode<blockdata> *p = firstBlock;
	assert(ptr2block != NULL);
	
	while (p != NULL) {
		if (p->info.blockptr == ptr2block) {
			p->info.free = true;
			
			if (p->next != NULL && p->next->info.free == true) { mergeForward(p); }
			if (p->prev != NULL && p->prev->info.free == true) { mergeBackward(p); }

			break;
		}
		else { p = p->next; }
	}
}


