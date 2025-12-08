#include <curses.h>
#include <memory>
#include <print>

#include "board.hpp"
#include "levels.hpp"
#include "usage.hpp"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    usage(argv[0]);
    return 1;
  }

  // read all levels from XSB file
  const std::string fileName = "levels/sokoban_levels.xsb";
  std::vector<board_t> allLevels;
  const auto numLevels = levelsFromXSBFile(fileName, allLevels);
  if (numLevels == 0) {
    std::println(stderr, "Error: No levels found in {}", fileName);
    return 1;
  } else {
    std::println(stderr, "Info: {} levels loaded", numLevels);
  }

  // create board
  const auto level = std::clamp(std::stoi(argv[1]), 1, numLevels);
  auto board = allLevels[level - 1]; // vector index starts at zero

  // initialize ncurses
  initscr();
  noecho();
  cbreak();
  curs_set(0);

  // create window
  const auto h = height(board) + 2;
  const auto w = width(board) + 2;
  WINDOW *win = newwin(h, w, 0, 0);
  refresh();

  box(win, 0, 0);
  wprint(win, board, level);

  // game loop
  for (;;) {
    coord_t dir;
    auto ch = static_cast<char>(wgetch(win));

    switch (ch) {
    case 'w':
      dir = {.x = 0, .y = -1};
      break;
    case 'a':
      dir = {.x = -1, .y = 0};
      break;
    case 's':
      dir = {.x = 0, .y = 1};
      break;
    case 'd':
      dir = {.x = 1, .y = 0};
      break;
    case 'q':
      goto done;
      break;
    default:
      dir = {.x = 0, .y = 0};
    }

    movePlayer(board, dir);
    wprint(win, board, level);
  }

done:
  delwin(win);
  endwin();

  if (isFinished(board))
    std::puts("You won!");
  else
    std::puts("Better luck next time!");

  return 0;
}
