#include <algorithm>
#include <curses.h>
#include <iostream>
#include <print>
#include <string>

#include "board.hpp"

int height(const board_t &brd) { return brd.size(); };

// https://youtu.be/eJCA2fynzME?t=812
int width(const board_t &brd) {
  const auto it =
      std::ranges::max_element(brd, {}, [](const auto &p) { return p.size(); });
  return it->size();
}

void print(const board_t &brd, const int level) {
  std::println("Level: {}", level);

  for (const auto &row : brd)
    std::cout << row << '\n';
}

// Print with ncurses.
void wprint(WINDOW *win, const board_t &brd, const int level) {
  mvwprintw(win, 0, 1, "Level: %d", level);

  for (auto i{1}; const auto &row : brd)
    mvwprintw(win, i++, 1, row.c_str());
}

// Find player coordinate.
coord_t findPlayer(const board_t &brd) {
  coord_t pos{};
  for (auto y{0}; const auto &row : brd) {
    for (auto x{0}; const auto &tile : row) {
      if (tile == '@' || tile == '+') {
        return (pos = {.x = x, .y = y});
      }
      ++x;
    }
    ++y;
  }
  return pos;
}

// Check if all crates are at their final positions.
bool isFinished(const board_t &brd) {
  for (const auto &row : brd)
    if (std::ranges::contains(row, '$'))
      return false;

  return true;
}

// Move player and crate.
void movePlayer(board_t &brd, const coord_t &dir) {
  const auto pos = findPlayer(brd);
  const auto pos1 = pos + dir;
  const auto pos2 = pos + 2 * dir;

  auto &curr = brd[pos.y][pos.x];
  auto &nxt1 = brd[pos1.y][pos1.x];
  auto &nxt2 = brd[pos2.y][pos2.x];

  if (curr == '@' && nxt1 == ' ') {
    curr = ' ';
    nxt1 = '@';
  } else if (curr == '@' && nxt1 == '.') {
    curr = ' ';
    nxt1 = '+';
  } else if (curr == '+' && nxt1 == ' ') {
    curr = '.';
    nxt1 = '@';
  } else if (curr == '+' && nxt1 == '.') {
    curr = '.';
    nxt1 = '+';
  } else if (curr == '@' && nxt1 == '$' && nxt2 == ' ') {
    curr = ' ';
    nxt1 = '@';
    nxt2 = '$';
  } else if (curr == '@' && nxt1 == '$' && nxt2 == '.') {
    curr = ' ';
    nxt1 = '@';
    nxt2 = '*';
  } else if (curr == '@' && nxt1 == '*' && nxt2 == ' ') {
    curr = ' ';
    nxt1 = '+';
    nxt2 = '$';
  } else if (curr == '@' && nxt1 == '*' && nxt2 == '.') {
    curr = ' ';
    nxt1 = '+';
    nxt2 = '*';
  } else if (curr == '+' && nxt1 == '$' && nxt2 == ' ') {
    curr = '.';
    nxt1 = '@';
    nxt2 = '$';
  } else if (curr == '+' && nxt1 == '$' && nxt2 == '.') {
    curr = '.';
    nxt1 = '@';
    nxt2 = '*';
  } else if (curr == '+' && nxt1 == '*' && nxt2 == ' ') {
    curr = '.';
    nxt1 = '+';
    nxt2 = '$';
  } else if (curr == '+' && nxt1 == '*' && nxt2 == '.') {
    curr = '.';
    nxt1 = '+';
    nxt2 = '*';
  }
}
