#include "deps/ChainedHash.h"
#include "deps/StringHash.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main() {
  ChainedHash cHash;
  StringHash sHash;
  cHash.addValue("the");
  cHash.addValue("tha");
  cHash.addValue("tho");
  cHash.addValue("thu");
  cHash.addValue("thi");
  cHash.addValue("thl");
  cHash.addValue("tht");
  cHash.addValue("noodle");
  cHash.addValue("Google");
  cHash.addValue("doggo");
  cout << cHash.displayTable() << endl;
  string searcher[] = {"Google", "google", "internet",
                       "doggo",  "Dragon", "_END_"};
  int index = 0;
  do {
    string sch = "\"" + searcher[index] + "\"";
    cout << "searching for " << sch << " and it is ";
    cout << (cHash.findValue(searcher[index])? "here." : "not here.") << endl;
  } while (searcher[++index] != "_END_");

  return 0;
}
