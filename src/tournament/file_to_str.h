#pragma once

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/// \brief Takes a filestream, and outputs it as a string
string file_to_str(ifstream &file);
