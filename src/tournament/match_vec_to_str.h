#pragma once

#include "tournament/match.h"
#include <string>
#include <vector>

/// \brief creates a string representation of every match in a vector<Match>
///
///
/// The outputted string looks like this:
/// first-last-name first-last-name MatchResult::PlayerOneWon
/// first-last-name first-last-name MatchResult::PlayerTwoWon
/// first-last-name first-last-name MatchResult::NotRun
/// first-last-name first-last-name MatchResult::NotRun
/// ...
///
string match_vec_to_str(vector<Match> match_vec);
