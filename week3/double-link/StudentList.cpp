#include "StudentList.hpp"
#include <stdexcept>

void StudentList::insertHead(Student *stu) {
  // if the list is empty, initialize both head and tail

  if (head == nullptr)
    head = tail = new StudentLink(stu);

  // otherwise, just add a new link at the head
  else {
    // set first link and head to point to it
    StudentLink *temp = new StudentLink(stu, head);
    head = temp;
  }
}

void StudentList::insertTail(Student *stu) {
  if (head == nullptr)
    head = tail = new StudentLink(stu);
  else {
    StudentLink *temp = new StudentLink(stu);
    tail->setNext(temp);
    tail = temp;
  }
}

Student *StudentList::deleteHead() {
  if (head == nullptr) {
    throw std::underflow_error("The student list is empty.");
  }
  StudentLink *tempHead = head;
  Student *stuOut = tempHead->getStudent();
  head = tempHead->getNext();
  delete tempHead;
  return stuOut;
}

bool StudentList::findKey(std::string key) {
  for (StudentLink *ptr = head; ptr != nullptr; ptr = ptr->getNext()) {
    // check each link for the desired value
    if (ptr->getStudent()->getName() == key) {
      // save ptr and return true if it is found
      return true;
    }
  }
  return false;
}

bool StudentList::deleteKey(std::string key) {
  StudentLink *last, *ptr;
  last = ptr = head;
  while (ptr != nullptr) {
    // check each link for the desired value
    if (ptr->getStudent()->getName() == key) {
      // save ptr and return true if it is found
      last->setNext(ptr->getNext());
      delete ptr->getStudent();
      delete ptr;
      return true;
    }
    last = ptr;
    ptr = ptr->getNext();
  }
  return false;
}

StudentList::~StudentList() {
  // start at the head
  StudentLink *ptr = head;

  // continue until done
  while (ptr != nullptr) {
    // temporarily save the link
    StudentLink *temp = ptr;
    // move pointer to the next one
    ptr = ptr->getNext();
    // delete the no longer needed link
    delete temp->getStudent();
    delete temp;
  }
}
