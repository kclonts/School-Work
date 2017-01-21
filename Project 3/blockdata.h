#ifndef _BLOCKDATA_
#define _BLOCKDATA_

#include <iostream>

using namespace std;

class blockdata {
  friend ostream& operator << (ostream&, const blockdata &);

 public:
  blockdata(int s, bool f, unsigned char *p);
  int blocksize;
  bool free;
  unsigned char *blockptr;	    
};


#endif
