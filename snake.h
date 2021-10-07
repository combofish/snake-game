#ifndef __SNAKE_H_
#define __SNAKE_H_
#include <ctime>
#include <random>
#include <vector>

const int snake_box_width = 15;
const int snake_box_hight = 15;

std::time_t seed = time(nullptr);
std::minstd_rand0 eng(seed + clock());
std::uniform_int_distribution<int> dist_width(0,59);
std::uniform_int_distribution<int> dist_height(0,39);

enum class Direction { UP, DOWN, RIGHT, LEFT };

class Point {
private:
  int x, y;
  void get_random_point();
  
public:
  Point(){};
  Point(int nx, int ny) : x(nx), y(ny){};
  void set_x(int nx) { x = nx; };
  void set_y(int ny) { y = ny; };
  int get_x() { return x; };
  int get_y() { return y; };
  void move(Direction);
  void get_random_point_exclude(std::vector<Point>);
  bool is_equal(Point);
};

bool Point::is_equal(Point p){
  if (this -> x == p.get_x() && this -> y == p.get_y())
    return true;

  return false;
}

void Point::get_random_point(){
  int h1 = dist_height(eng) * 15;
  int w1 = dist_width(eng) * 15;
  x = h1;
  y = w1;
}

void Point::get_random_point_exclude(const std::vector<Point> ps){
  this -> get_random_point();
  bool can_use = true;
  for(auto it = ps.begin(); it!= ps.end(); it++)
    if(this->is_equal(*it))
      can_use = false;

  if (!can_use)
    this -> get_random_point_exclude(ps);
}


void Point::move(Direction d) {
  switch (d) {
  case Direction::UP:
    y += snake_box_width;
    break;
  case Direction::DOWN:
    y -= snake_box_width;
    break;
  case Direction::RIGHT:
    x -= snake_box_hight;
    break;
  case Direction::LEFT:
    x += snake_box_hight;
    break;
  default:
    break;
  }
}

class Snake {
public:
  Snake(int);
  std::vector<Point> get_locations();
  std::vector<Point> move(Direction);
  bool judge_eat(Direction, Point);
  
private:
  std::vector<Point> locates;
  std::vector<Point> eat(Point);
  int length;
};

Snake::Snake(int n) {
  Point loc;
  loc.set_x(120);
  loc.set_y(120);
  for (int i = 0; i < n; i++) {
    locates.push_back(loc);
    loc.set_x(loc.get_x() + 15);
  }
}

std::vector<Point> Snake::move(Direction d) {
  auto first_point = locates.front();
  first_point.move(d);
  locates.insert(locates.begin(), first_point);
  locates.pop_back();
  return locates;
}

bool Snake::judge_eat(Direction d,Point p){
  auto first_point = locates.front();
  first_point.move(d);
  if(first_point.is_equal(p)){
    this -> eat(first_point);
    return true;
  }
  return false;
}

std::vector<Point> Snake::eat(Point p) {
  locates.insert(locates.begin(), p);
  return locates;
}

std::vector<Point> Snake::get_locations() { return locates; }

#endif
