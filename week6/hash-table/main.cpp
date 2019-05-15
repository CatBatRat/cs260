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
  sHash.addValue("the");
  sHash.addValue("tha");
  sHash.addValue("tho");
  sHash.addValue("thu");
  sHash.addValue("thi");
  sHash.addValue("thl");
  sHash.addValue("tht");
  sHash.addValue("noodle");
  sHash.addValue("Google");
  sHash.addValue("doggo");
  sHash.addValue("doggo");
  sHash.removeValue("doggo");
  sHash.removeValue("thl");
  cout << sHash.displayTable() << endl;
  string searcher[] = {"Google", "google", "internet",
                       "doggo",  "Dragon", "_END_"};
  int index = 0;
  do {
    string sch = "\"" + searcher[index] + "\"";
    cout << "searching for " << sch << " and it is ";
    cout << (sHash.findValue(searcher[index])? "here." : "not here.") << endl;
  } while (searcher[++index] != "_END_");

  return 0;
}
