/**
 * @file snake.h
 * @author combofish (combofish49@gmail.com)
 * @brief 定义蛇类。
 * @version 0.6
 * @date 2021-10-16
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef __SNAKE_H_
#define __SNAKE_H_

#include "dot.h"
#include <vector>

namespace snake_game {

    class Snake {
    public:
        /* 初始化蛇的位置，可设置长度，默认长度为3； */
        Snake(int);

        Snake() : Snake(3) {};

        /* 获取蛇的位置。 */
        const std::vector<Dot> &locations();

        /* 获取蛇的长度。 */
        const int length();

        /* 移动蛇的位置，返回之前的一个点位置。*/
        Dot move(Direction);

        /* 在给定的方向上步进一格，查看是否与给定点重合，即是否可以吃掉。 */
        bool judge_eat(Direction, Dot);

        /* 在给定的方向上步进一格，查看是否与蛇自身或者方框边缘碰撞。 */
        bool judge_collision(Direction);

    private:
        /* 储存蛇的位置。 */
        std::vector<Dot> _locations;

        /* 吃掉食物。*/
        void eat(Dot);
    };
}; // namespace snake_game
#endif
