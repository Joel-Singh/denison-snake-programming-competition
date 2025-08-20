#include "tournament/match.h"
#include <string>
#include <vector>

/// \brief Converts a string to a match vector. The string must be in the format
/// outputted by \ref match_vec_to_str or else an exception is thrown.
vector<Match> str_to_match_vec(string str);
