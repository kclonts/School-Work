#include <iostream>
#include "MemoryManager.h"
using namespace std;

int main()
{
   MemoryManager heaper(50);
   cout << "\nheap initialized\n";
   cout << "\n-------------BlockList start------------------\n";
   heaper.showBlockList();
   cout << "-------------BlockList end------------------\n\n";
   cout << "Doing first malloc:\n";
   unsigned char * p1 = heaper.malloc(10);

   cout << "malloc done\n";
   cout << "\n-------------BlockList start------------------\n";
   heaper.showBlockList();
   cout << "-------------BlockList end------------------\n\n";

   cout << "On to the second malloc\n";
   unsigned char *p2 = heaper.malloc(20);
   cout << "malloc done\n";
   cout << "\n-------------BlockList start------------------\n";
   heaper.showBlockList();
   cout << "-------------BlockList end------------------\n\n";

   cout << "Now let's ask for an un-allocatable block\n";
   unsigned char *p8 = heaper.malloc(30);
   if (p8 == 0)
      cout << "Good. The call to malloc returned NULL\n";
   else
      cout << "Uh-oh.  Call to malloc did not return NULL as it should have\n";

   cout << "Next free the first pointer\n";
   heaper.free(p1);
   cout << "\n-------------BlockList start------------------\n";
   heaper.showBlockList();
   cout << "-------------BlockList end------------------\n\n";

   cout << "Now do a malloc for a block too big for the initial open block\n";
   p1 = heaper.malloc(15);
   cout << "malloc done\n";
   cout << "\n-------------BlockList start------------------\n";
   heaper.showBlockList();
   cout << "-------------BlockList end------------------\n\n";

   cout << "Next free the most recently allocated pointer\n";
   heaper.free(p1);
   cout << "Here is the block list\n";
   cout << "\n-------------BlockList start------------------\n";
   heaper.showBlockList();
   cout << "-------------BlockList end------------------\n\n";

   cout << "Next free the middle pointer\n";
   heaper.free(p2);
   cout << "Here is the block list\n";
   cout << "-------------BlockList start------------------\n";
   heaper.showBlockList();
   cout << "\n-------------BlockList end------------------\n\n";

   cin.get();

   return 0;
}
