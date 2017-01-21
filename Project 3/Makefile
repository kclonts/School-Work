main:  MemoryManager.o blockdata.o testMemMgr.o
	g++ -std=c++0x blockdata.o MemoryManager.o testMemMgr.o -o main

testMemMgr.o:  testMemMgr.cpp
	g++ -std=c++0x -c testMemMgr.cpp

blockdata.o: blockdata.h blockdata.cpp dlUtils.h
	g++ -std=c++0x -c blockdata.cpp

MemoryManager.o: MemoryManager.cpp MemoryManager.h
	g++ -std=c++0x -c MemoryManager.cpp

clean:
	rm *.o
