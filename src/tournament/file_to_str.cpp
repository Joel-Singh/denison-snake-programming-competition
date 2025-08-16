#include "file_to_str.h"

string file_to_str(ifstream &file) {
  string str;

  string line;
  while (getline(file, line)) {
    str += line + "\n";
  }

  // Remove trailing newline
  str = str.substr(0, str.size() - 1);

  return str;
}
