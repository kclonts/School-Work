#ifndef __DLNODE__
#define __DLNODE__

#include <iostream>
#include <cassert>

template <class T>
struct dlNode {
  T info;
  dlNode<T> *prev;
  dlNode<T> *next;
  dlNode<T>(T val, dlNode<T> *p, dlNode<T> *n):info(val),prev(p),next(n){};
};

template <class T>
void printDlList(dlNode<T>* first,const char *sep)
{
  dlNode<T> *cursor = first;
  while(cursor != NULL && cursor->next!= NULL) {
    std::cout << cursor->info << sep;
    cursor = cursor->next;
  }
  if (cursor != NULL)
    std::cout << cursor->info << std::endl;
}

template <class T>
void insertAsFirst(dlNode<T>* &first, T newval)
{
  first = new dlNode<T>(newval,NULL,first);
  first->next->prev = first;
}

template <class T>
void insertAfter(dlNode<T> *first, dlNode<T> *current, T newval)
{
  assert(current != NULL);
  current->next = new dlNode<T>(newval,current,current->next);
  current = current->next;
  if (current->next != NULL)
    current->next->prev = current;
}

template <class T>
void insertBefore(dlNode<T>* &first, dlNode<T> *current, T newval)
{
  assert(current != NULL);
  if(current == first) 
    insertAsFirst(first,newval);
  else 
      insertAfter(first,current->prev,newval);
}

template <class T>
void deleteNext(dlNode<T> *current)
{
  assert(current != NULL && current->next != NULL);
  dlNode<T> *hold = current->next;
  current->next = hold->next;
  if (current->next != NULL)
    current->next->prev = current;
  delete hold;
}

template <class T>
void deletePrevious(dlNode<T> * &first,dlNode<T> *current)
{
  assert(first != NULL && current != NULL && current->prev != NULL);
  dlNode<T> *hold = current->prev;
  current->prev = hold->prev;
  if (current->prev != NULL)
     current->prev->next = current;
  else
     first = current;
  delete hold;
}

template <class T>
void deleteNode(dlNode<T>* &first, dlNode<T>* current)
{
  assert(first != NULL && current != NULL);
  dlNode<T> *hold = current;
  if (current == first) {
    first = first->next;
    first->prev = NULL;
    current = first;
  } else {
    current->prev->next = current->next;
    current->next->prev = current->prev;
    current = current->prev;
  }
  delete hold;
}


#endif
