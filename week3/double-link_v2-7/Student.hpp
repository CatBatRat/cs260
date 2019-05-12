#ifndef __STUDENT__
#define __STUDENT__

#include <string>

class Student {
private:
  std::string name;
  int age;

public:
  Student(std::string name, int age)
      : name(name), age(age) {}
  void setName(std::string name) { this->name = name; }
  std::string getName() { return this->name; }
  void setAge(int age) { this->age = age; }
  int getAge() { return this->age; }
};

#endif // __STUDENT__
