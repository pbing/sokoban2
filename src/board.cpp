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

  for (auto i = 0; i != static_cast<int>(brd.size()); ++i)
    mvwprintw(win, i + 1, 1, brd[i].c_str());
}

// Find player coordinate.
coord_t findPlayer(const board_t &brd) {
  coord_t dir{};
  for (auto y = 0; y != static_cast<int>(brd.size()); ++y)
    for (auto x = 0; x != static_cast<int>(brd[y].size()); ++x) {
      const auto c = brd[y][x];
      if (c == '@' || c == '+') {
        return (dir = {.x = x, .y = y});
      }
    }
  return dir;
}

// Check if all crates are at their final positions.
bool isFinished(const board_t &brd) {
  for (auto y = 0U; y != brd.size(); ++y)
    for (auto x = 0U; x != brd[y].size(); ++x)
      if (brd[y][x] == '$')
        return false;
  return true;
}

// Move player and crate.
void movePlayer(board_t &brd, const coord_t &dir) {
  const auto pos = findPlayer(brd);
  const auto pos1 = pos + dir;
  const auto pos2 = pos + 2 * dir;

  const auto curr = brd[pos.y][pos.x];
  const auto nxt1 = brd[pos1.y][pos1.x];
  const auto nxt2 = brd[pos2.y][pos2.x];

  if (curr == '@' && nxt1 == ' ') {
    brd[pos.y][pos.x] = ' ';
    brd[pos1.y][pos1.x] = '@';
  } else if (curr == '@' && nxt1 == '.') {
    brd[pos.y][pos.x] = ' ';
    brd[pos1.y][pos1.x] = '+';
  } else if (curr == '+' && nxt1 == ' ') {
    brd[pos.y][pos.x] = '.';
    brd[pos1.y][pos1.x] = '@';
  } else if (curr == '+' && nxt1 == '.') {
    brd[pos.y][pos.x] = '.';
    brd[pos1.y][pos1.x] = '+';
  } else if (curr == '@' && nxt1 == '$' && nxt2 == ' ') {
    brd[pos.y][pos.x] = ' ';
    brd[pos1.y][pos1.x] = '@';
    brd[pos2.y][pos2.x] = '$';
  } else if (curr == '@' && nxt1 == '$' && nxt2 == '.') {
    brd[pos.y][pos.x] = ' ';
    brd[pos1.y][pos1.x] = '@';
    brd[pos2.y][pos2.x] = '*';
  } else if (curr == '@' && nxt1 == '*' && nxt2 == ' ') {
    brd[pos.y][pos.x] = ' ';
    brd[pos1.y][pos1.x] = '+';
    brd[pos2.y][pos2.x] = '$';
  } else if (curr == '@' && nxt1 == '*' && nxt2 == '.') {
    brd[pos.y][pos.x] = ' ';
    brd[pos1.y][pos1.x] = '+';
    brd[pos2.y][pos2.x] = '*';
  } else if (curr == '+' && nxt1 == '$' && nxt2 == ' ') {
    brd[pos.y][pos.x] = '.';
    brd[pos1.y][pos1.x] = '@';
    brd[pos2.y][pos2.x] = '$';
  } else if (curr == '+' && nxt1 == '$' && nxt2 == '.') {
    brd[pos.y][pos.x] = '.';
    brd[pos1.y][pos1.x] = '@';
    brd[pos2.y][pos2.x] = '*';
  } else if (curr == '+' && nxt1 == '*' && nxt2 == ' ') {
    brd[pos.y][pos.x] = '.';
    brd[pos1.y][pos1.x] = '+';
    brd[pos2.y][pos2.x] = '$';
  } else if (curr == '+' && nxt1 == '*' && nxt2 == '.') {
    brd[pos.y][pos.x] = '.';
    brd[pos1.y][pos1.x] = '+';
    brd[pos2.y][pos2.x] = '*';
  }
}
