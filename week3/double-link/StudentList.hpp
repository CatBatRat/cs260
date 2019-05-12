#ifndef __STUDENT_LIST__
#define __STUDENT_LIST__

#include "Student.hpp"

class StudentLink {
private:
  Student *student;
  StudentLink *next;

public:
  StudentLink(Student *s = nullptr, StudentLink *n = nullptr)
      : student(s), next(n) {}
  Student *getStudent() { return student; }
  void setNext(StudentLink *n) { next = n; }
  StudentLink *getNext() { return next; }
};

class StudentList {
private:
  StudentLink *head;
  StudentLink *tail;

public:
  StudentList() { head = tail = nullptr; }
  ~StudentList();
  void insertHead(Student *stu);
  void insertTail(Student *stu);
  Student *deleteHead();
  bool findKey(std::string key);
  bool isEmpty() { return (head == nullptr) ? true : false; }
  bool deleteKey(std::string key);
};

#endif // __STUDENT_LIST__
