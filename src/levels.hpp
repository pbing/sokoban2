#pragma once

#include <string>

#include "board.hpp"

int levelsFromXSBFile(const std::string &filePath,
                      std::vector<board_t> &levels);
