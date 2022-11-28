/**
 * @file snake.cpp
 * @author combofish (combofish49@gmail.com)
 * @brief 实现蛇的类。
 * @version 0.6
 * @date 2021-10-16
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "snake.h"
#include "dot.h"

using namespace snake_game;

Snake::Snake(int n) {
    Dot loc(160, 160);
    for (int i = 0; i < n; i++) {
        _locations.push_back(loc);
        loc.set_x(loc.get_x() - grid_width);
    }
}

const std::vector<Dot> &Snake::locations() { return _locations; }

const int Snake::length() { return _locations.size(); }

Dot Snake::move(Direction d) {
    Dot first_p = _locations.front();
    Dot end_p = _locations.back();
    first_p.move(d);
    _locations.insert(_locations.begin(), first_p);
    _locations.pop_back();
    return end_p;
}

bool Snake::judge_eat(Direction d, Dot p) {
    Dot first_point = _locations.front();
    first_point.move(d);
    if (first_point == p) {
        this->eat(first_point);
        return true;
    }
    return false;
}

inline void Snake::eat(Dot p) { _locations.insert(_locations.cbegin(), p); }

bool Snake::judge_collision(Direction d) {
    Dot first_point = _locations.front();
    first_point.move(d);
    if (first_point.get_x() < 0 ||
        first_point.get_x() >= (grid_width_num * grid_width))
        return true;

    if (first_point.get_y() < 0 ||
        first_point.get_y() >= (grid_hight_num * grid_hight))
        return true;

    /* 排除最后一格。 */
    for (int i = 0; i < _locations.size() - 1; i++) {
        auto loc = _locations[i];
        if (loc == first_point)
            return true;
    }

    return false;
}
