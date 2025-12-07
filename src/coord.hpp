#pragma once

struct coord_t {
  int x;
  int y;

  coord_t &operator+=(const coord_t &rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  friend coord_t operator+(const coord_t &lhs, const coord_t &rhs) {
    return {.x = lhs.x + rhs.x, .y = lhs.y + rhs.y};
  }

  friend coord_t operator*(const int &lhs, const coord_t &rhs) {
    return {.x = lhs * rhs.x, .y = lhs * rhs.y};
  }

  friend coord_t operator*(const coord_t &lhs, const int &rhs) {
    return {.x = lhs.x * rhs, .y = lhs.y * rhs};
  }
};
