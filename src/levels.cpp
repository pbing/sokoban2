#include <fstream>
#include <print>
#include <string>

#include "board.hpp"
#include "levels.hpp"

int levelsFromXSBFile(const std::string &filePath,
                      std::vector<board_t> &levels) {

  std::ifstream ifs(filePath);
  if (!ifs.is_open()) {
    std::println(stderr, "Error: Cannot open file {}", filePath);
    std::exit(1);
  }

  std::vector<std::string> lvl;
  for (std::string str; std::getline(ifs, str);) {
    if (str != "") {
      lvl.push_back(str);
    } else {
      levels.push_back(lvl);
      lvl.clear();
    }
  }
  levels.push_back(lvl);

  return levels.size();
}
