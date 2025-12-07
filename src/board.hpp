#pragma once

#include <curses.h>
#include <string>
#include <vector>

#include "coord.hpp"

using board_t = std::vector<std::string>;

int height(const board_t &brd);

int width(const board_t &brd);

void print(const board_t &brd, const int level);

void wprint(WINDOW *win, const board_t &brd, const int level);

coord_t findPlayer(const board_t &brd);

bool isFinished(const board_t &brd);

void movePlayer(board_t &brd, const coord_t &dir);
