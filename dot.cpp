/**
 * @file dot.cpp
 * @author combofish (combofish49@gmail.com)
 * @brief 存储网格所用的坐标数据类。
 * @version 0.6
 * @date 2021-10-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "dot.h"

using namespace snake_game;

Dot Dot::get_random_dot() {
    int w1 = dist_width(eng) * 20;
    int h1 = dist_width(eng) * 20;
    return Dot(h1, w1);
}


void Dot::move(Direction d) {
    switch (d) {
        case Direction::UP:
            y -= grid_width;
            break;
        case Direction::DOWN:
            y += grid_width;
            break;
        case Direction::RIGHT:
            x += grid_hight;
            break;
        case Direction::LEFT:
            x -= grid_hight;
            break;
        default:
            break;
    }
}

Dot Dot::get_random_dot_exclude(const std::vector<Dot> &ps) {
    Dot p = get_random_dot();
    bool can_use = true;
    for (Dot it: ps)
        if (p == it) {
            can_use = false;
            break;
        }

    if (!can_use)
        p = get_random_dot_exclude(ps);

    return p;
}
