/**
 * @file dot.h
 * @author combofish (combofish49@gmail.com)
 * @brief 定义存储网格所用的坐标数据类。
 * @version 0.6
 * @date 2021-10-16
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef _SNAKE_DOT_H_
#define _SNAKE_DOT_H_
#include <ctime>
#include <random>

namespace snake_game {

const int grid_width_num = 20;
const int grid_hight_num = 20;
const int grid_width = 20;
const int grid_hight = 20;

static std::time_t seed = time(nullptr);
static std::minstd_rand0 eng(seed + clock());
static std::uniform_int_distribution<int> dist_width(0, 19);

enum class Direction { UP, DOWN, RIGHT, LEFT };

class Dot {
private:
  int x, y;
  static Dot get_random_dot();

public:
  Dot() : x(0), y(0){};
  Dot(int nx, int ny) : x(nx), y(ny){};
  void set_x(int nx) { x = nx; };
  void set_y(int ny) { y = ny; };
  int get_x() { return x; };
  int get_y() { return y; };

  void move(Direction);
  static Dot get_random_dot_exclude(const std::vector<Dot> &);

  bool operator==(Dot &a) {
    return ((this->get_x() == a.get_x()) && (this->get_y() == a.get_y()));
  };
  bool operator!=(Dot &b) { return !((*this) == b); };
};
}; // namespace snake_game
#endif
