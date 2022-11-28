/**
 * @file main.cpp
 * @author combofish (combofish49@gmail.com)
 * @brief 主要逻辑实现。
 * @version 0.6
 * @date 2021-10-16
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "main.h"
#include "GUI_Interface/GUI.h"
#include "dot.h"
#include "snake.h"
#include "snake_window.h"

using namespace snake_game;

/**
 * @brief
 *
 * @param d
 */
void event_loop(Address d);

/**
 * @brief
 *
 * @param d
 */
void snake_game_run(Address d);

int main() {
    Graph_lib::Point p1(100, 100);

    try {
        Snake_window win(p1, 600, 400, "Snake");
        win.set_label("Snake Game");

        Fl::add_timeout(GAME_SPEED, event_loop, &win);
        return Graph_lib::gui_main();
    } catch (exception &e) {
        std::cerr << "exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Some ecception" << std::endl;
        return 2;
    }
}

/**
 * @brief
 *
 * @param d
 */
void event_loop(Address d) {

    // Snake_window *instance = static_cast<Snake_window *>(d);
    Snake_window &snake_win = reference_to<Snake_window>(d);
    // cout << "Delay 1s" << endl;
    // cout << "Is Ready: " << instance->is_ready << endl;
    // cout << "Game Status: " << (int)instance->game_status << endl;
    // cout << "Current Direction: " << (int)instance->current_direction() <<
    // endl;

    switch (snake_win.game_status) {
        case GameStatus::PAUSE: {
            // cout << "Game Pause" << endl;
            break;
        };
        case GameStatus::RUN: {

            snake_game_run(d);
            break;
        }
        case GameStatus::COLLISION: {
            // std::cout << "Collision" << endl;
            // std::cout << "Game Over!" << std::endl;
            snake_win.game_over();
            break;
        }
    }

    Fl::redraw();
    Fl::repeat_timeout(GAME_SPEED, event_loop, d);
}

/**
 * @brief
 *
 * @param d
 */
void snake_game_run(Address d) {
    Snake_window &snake_win = reference_to<Snake_window>(d);
    /* Judge Eat. */
    bool is_eat =
            snake_win.snake.judge_eat(snake_win.game_direction, snake_win.food_dot);
    if (is_eat) {
        // cout << "Eat" << endl;

        /* Update Food Dot. */
        snake_win.food_dot =
                Dot::get_random_dot_exclude(snake_win.snake.locations());
        snake_win.paint_dot(snake_win.food_dot);
    } else {

        /* */
        bool is_collision =
                snake_win.snake.judge_collision(snake_win.game_direction);
        if (is_collision) {
            snake_win.game_status = snake_game::GameStatus::COLLISION;
        } else {

            /* Snake length don't increase. */
            Dot p = snake_win.snake.move(snake_win.game_direction);
            snake_win.clean_dot(p);
        }
    }

    /* Redraw Snake Locations. */
    snake_win.paint_dots(snake_win.snake.locations());

    /* Update Score. */
    snake_win.update_score();
    /**/
}
