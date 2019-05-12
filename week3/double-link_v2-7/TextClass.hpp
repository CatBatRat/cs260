//
//  List.h
//  Double Ended Single Linked List
//
//  Created by Jim Bailey on 4/22/17.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#ifndef List_h
#define List_h

#include <sstream>
#include <stdexcept>

template <class T> class Ltr {
private:
  T value;
  Ltr *next;
  Ltr *prev;

public:
  Ltr(T v, Ltr *n = nullptr, Ltr *p = nullptr) : value(v), next(n), prev(p) {}

  // basic setters and getters
  void setNext(Ltr *n) { next = n; }
  Ltr *getNext() { return next; }
  void setPrev(Ltr *p) { prev = p; }
  Ltr *getPrev() { return prev; }
  T getValue() { return value; }
};

template <class T> class TextClass {
private:
  Ltr<T> *head;
  Ltr<T> *tail;
  Ltr<T> *iter;

public:
  TextClass();
  ~TextClass();

  void insertHead(T value);
  void insertTail(T value);
  T deleteHead();
  T deleteTail();

  bool findKey(T value);
  bool deleteKey(T value);

  std::string displayList();

  bool findIter(T value);
  bool insertKey(T value);
  bool appendList(TextClass<T> &aList);
  bool deleteIter();
  Ltr<T> *getHead() { return head; }
  Ltr<T> *getTail() { return head; }
};

// constructor initializes the head, tail, and iter
template <class T>
TextClass<T>::TextClass() : head(nullptr), tail(nullptr), iter(nullptr) {}

// destructor, deletes any remaining links
template <class T> TextClass<T>::~TextClass() {
  // start at the head
  Ltr<T> *ptr = head;

  // continue until done
  while (ptr != nullptr) {
    // temporarily save the link
    Ltr<T> *temp = ptr;
    // move pointer to the next one
    ptr = ptr->getNext();
    // delete the no longer needed link
    delete temp;
  }
}

// add a new link to the start of the list
template <class T> void TextClass<T>::insertHead(T value) {
  // if the list is empty, initialize both head and tail
  if (head == nullptr)
    head = tail = new Ltr<T>(value);

  // otherwise, just add a new link at the head
  else {
    // create new link will nullptr for prev
    Ltr<T> *temp = new Ltr<T>(value, head, nullptr);
    // set first link and head to point to it
    head->setPrev(temp);
    head = temp;
  }
}

// add a new link to the end of the list
template <class T> void TextClass<T>::insertTail(T value) {
  // if the list is empty, initialize both head and tail
  if (tail == nullptr)
    head = tail = new Ltr<T>(value);

  // otherwise, just add a new link at the end
  else {
    // create the new link
    Ltr<T> *temp = new Ltr<T>(value, nullptr, tail);
    // set last link and tail to point to it
    tail->setNext(temp);
    tail = temp;
  }
}

// take care of setting tail when list becomes empty
template <class T> T TextClass<T>::deleteHead() {
  // if list is empty, throw an exception
  if (head == nullptr)
    throw std::underflow_error("Empty List");

  // save the link and its value
  Ltr<T> *temp = head;
  T value = temp->getValue();

  // update head
  head = head->getNext();

  // if list is now empty, update tail
  if (head == nullptr)
    tail = nullptr;
  // otherwise, update prev on new first
  else
    head->setPrev(nullptr);

  // delete the old link and return
  if (head == iter)
    iter = nullptr;
  delete temp;
  return value;
}

// remove a link from the end of the list, returning
// its value. Throw an exception on an empty list
// take care of setting head when list becomes empty
template <class T> T TextClass<T>::deleteTail() {
  // if list is empty, throw an exception
  if (tail == nullptr)
    throw std::underflow_error("Empty List");

  // save the link and its value
  Ltr<T> *temp = tail;
  T value = temp->getValue();

  // update head
  tail = tail->getPrev();

  // if list is now empty, update tail
  if (tail == nullptr)
    head = nullptr;
  // otherwise, update prev on new first
  else
    tail->setNext(nullptr);

  // delete the old link and return
  if (tail == iter)
    iter = nullptr;
  delete temp;
  return value;
}

// see if a value is present in the list
template <class T> bool TextClass<T>::findKey(T value) {
  // Set `ptr` to head if `iter` not set, else set to `iter->next`
  Ltr<T> *base = (iter == nullptr) ? head : iter->getNext();
  // walk down the list from head until reach terminator
  for (Ltr<T> *ptr = base; ptr != nullptr; ptr = ptr->getNext()) {
    // check each link for the desired value
    if (ptr->getValue() == value) {
      // save ptr and return true if it is found
      iter = ptr;
      return true;
    }
  }
  // special case if reaching the end of the list when starting from `iter`
  if (iter != nullptr)
    // base case is `ptr != iter` to prevent searching the entire list
    //    again.
    for (Ltr<T> *ptr = head; ptr != iter; ptr = ptr->getNext()) {
      if (ptr->getValue() == value) {
        // save ptr and return true if it is found
        iter = ptr;
        return true;
      }
    }
  // if you reach the end without finding the value, not there
  iter = nullptr;
  return false;
}

// delete a value if present
template <class T> bool TextClass<T>::deleteKey(T value) {
  // special case empty list
  if (head == nullptr)
    return false;

  // walk down the list, looking for the value
  for (Ltr<T> *ptr = head; ptr; ptr = ptr->getNext()) {
    // see if link is it
    if (ptr->getValue() == value) {
      // special case head
      if (ptr == head) {
        deleteHead();
        return true;
      }
      // special case tail
      if (ptr == tail) {
        deleteTail();
        return true;
      }
      // typical link, set pointers around it
      ptr->getPrev()->setNext(ptr->getNext());
      ptr->getNext()->setPrev(ptr->getPrev());

      // delete it and return
      if (ptr == iter)
        iter = nullptr;
      delete ptr;
      return true;
    }
  }

  // done with list without finding it
  return false;
}

// display list starting at head
template <class T> std::string TextClass<T>::displayList() {
  // define a string stream to gather the information
  std::ostringstream ss;

  // walk down the list, until we reach terminating nullptr
  for (Ltr<T> *ptr = head; ptr; ptr = ptr->getNext())
    // add next value to the stream
    ss << ptr->getValue();

  // add terminating endline
  ss << "\n";

  // return the string out of the stringstream
  return ss.str();
}

// methods to support pointers to recently found items

// first find and set iter
template <class T> bool TextClass<T>::findIter(T value) {
  // walk down the list from head until reach terminator
  for (Ltr<T> *ptr = head; ptr != nullptr; ptr = ptr->getNext())
    // check each link for the desired value
    if (ptr->getValue() == value) {
      // save ptr and return true if it is found
      iter = ptr;
      return true;
    }

  // if you reach the end without finding the value, not there
  iter = nullptr;
  return false;
}

// now use iter for insert
template <class T> bool TextClass<T>::insertKey(T value) {
  // if iter not set, fail
  if (iter == nullptr)
    return false;

  // special case head
  if (iter == head) {
    head = new Ltr<T>(value, head, nullptr);
    iter->setPrev(head);
    return true;
  }

  // otherwise do it
  Ltr<T> *temp = new Ltr<T>(value, iter, iter->getPrev());
  iter->getPrev()->setNext(temp);
  iter->setPrev(temp);

  // and return
  return true;
}

// now use iter for append
template <class T> bool TextClass<T>::appendList(TextClass<T> &aList) {
  Ltr<T> *ptr = aList.getHead();
  if (ptr != nullptr)
    insertTail(ptr->getValue());

  while (ptr->getNext() != nullptr) {
    ptr = ptr->getNext();
    insertTail(ptr->getValue());
  }

  // and return
  return true;
}

// now remove that link
template <class T> bool TextClass<T>::deleteIter() {
  // if iter not set, fail
  if (iter == nullptr)
    return false;

  // special case head
  if (iter == head)
    deleteHead();
  else
      // special case tail
      if (iter == tail)
    deleteTail();

  // typical link, deal with it
  else {
    iter->getNext()->setPrev(iter->getPrev());
    iter->getPrev()->setNext(iter->getNext());
    delete iter;
  }

  // now clean up and return
  iter = nullptr;
  return true;
}

#endif /* List_h */
