#include "write_segments.h"

namespace writer {

string write_segments(vector<Pos> const &segments) {
  string segments_str = "";
  for (auto pos : segments) {
    string pos_str = to_string(pos.x) + " " + to_string(pos.y);
    if (segments_str == "") {
      segments_str += pos_str;
    } else {
      segments_str += " " + pos_str;
    }
  }

  return segments_str;
}

} // namespace writer
