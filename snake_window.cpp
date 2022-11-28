/**
 * @file snake_window.cpp
 * @author combofish (combofish49@gmail.com)
 * @brief 实现游戏的窗口类
 * @version 0.6
 * @date 2021-10-16
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "snake_window.h"
#include "GUI_Interface/GUI.h"
#include "GUI_Interface/Graph.h"
#include "dot.h"
#include "snake.h"
#include <iostream>
#include <sstream>
#include <sys/stat.h>

using namespace snake_game;

Snake_window::Snake_window(Point p, int w, int h, const std::string &title)
        : Window(p, w, h, title), // score_out(Point(455, 10), 100, 20, "Score: "),
          button_pushed(false), game_status(GameStatus::PAUSE), is_ready(false),
          game_direction(Direction::LEFT),

          square(Point(0, 0), Point(400, 400)),
          game_name_text(Point(410, 40), "SNAKE GAME"),
          game_over_text(Point(20, 200), "GAME OVER!!!"),
          instruction_start_text(Point(425, 180), "Move to Start!"),
          instruction_quit_text(Point(435, 220), ":Q"),
          instruction_restart_text(Point(435, 240), ":R"),
          instruction_pause_text(Point(435, 260), ":P"),

          instruction_quit_text_(Point(485, 220), "Exit"),
          instruction_restart_text_(Point(485, 240), "Restart"),
          instruction_pause_text_(Point(485, 260), "Pause"),

          score_text(Point(430, 110), "000"),

          pause_button(Point(520, 300), 30, 30, "P", cb_pause),
          reset_button(Point(555, 300), 30, 30, "R", cb_restart),
          quit_button(Point(425, 300), 30, 30, "Q", cb_quit),
          w_button(Point(475, 300), 30, 30, "W", cb_w),
          a_button(Point(440, 335), 30, 30, "A", cb_a),
          s_button(Point(475, 335), 30, 30, "S", cb_s),
          d_button(Point(510, 335), 30, 30, "D", cb_d) {

    draw_grid();
    // score_out.put("0");
    if (!(is_ready)) {
        init_game();
        is_ready = true;
    }

    pause_button.set_shortcut('p');
    reset_button.set_shortcut('r');
    quit_button.set_shortcut('q');
    w_button.set_shortcut('w');
    a_button.set_shortcut('a');
    s_button.set_shortcut('s');
    d_button.set_shortcut('d');

    // attach(score_out);
    attach(square);

    game_name_text.set_font(Graph_lib::Font::times_bold_italic);
    game_name_text.set_font_size(25);
    game_name_text.set_color(Color::dark_green);

    game_over_text.set_font_size(60);
    game_over_text.set_font(Graph_lib::Font::courier_bold_italic);
    game_over_text.set_color(Color::dark_magenta);
    game_over_text.set_label("");
    // game_over_text.set_fill_color(Color::Transparency::invisible);
    // game_over_text.set_color(Color::Transparency::invisible);

    score_text.set_font_size(50);
    score_text.set_color(Color::red);

    attach(game_name_text);
    attach(game_over_text);
    attach(instruction_start_text);

    Color instruction_color = Color::dark_cyan;
    instruction_quit_text.set_color(instruction_color);
    instruction_restart_text.set_color(instruction_color);
    instruction_pause_text.set_color(instruction_color);

    instruction_quit_text_.set_color(instruction_color);
    instruction_restart_text_.set_color(instruction_color);
    instruction_pause_text_.set_color(instruction_color);

    attach(score_text);

    attach(instruction_quit_text);
    attach(instruction_restart_text);
    attach(instruction_pause_text);

    attach(instruction_quit_text_);
    attach(instruction_restart_text_);
    attach(instruction_pause_text_);

    attach(pause_button);
    attach(quit_button);
    attach(reset_button);
    attach(w_button);
    attach(s_button);
    attach(d_button);
    attach(a_button);
}

void Snake_window::restart() {
    /**/
    clean_all_dots_color();

    /**/
    init_game();

    /**/
    game_status = GameStatus::PAUSE;
}

void Snake_window::pause() { game_status = GameStatus::PAUSE; }

void Snake_window::quit() {
    button_pushed = true;
    //  std::cout << "q pressed" << std::endl;
    hide();
}

void Snake_window::push_s() {
    //  std::cout << "s pressed" << std::endl;
    if (game_status == GameStatus::PAUSE)
        game_status = GameStatus::RUN;

    game_direction = can_direction_to(Direction::DOWN);
};

void Snake_window::push_w() {
    //  std::cout << "w pressed" << std::endl;
    if (game_status == GameStatus::PAUSE)
        game_status = GameStatus::RUN;

    game_direction = can_direction_to(Direction::UP);
};

void Snake_window::push_a() {
    // std::cout << "a pressed" << std::endl;
    Direction d = current_direction();

    if (game_status == GameStatus::PAUSE)
        game_status = GameStatus::RUN;

    game_direction = can_direction_to(Direction::LEFT);
};

void Snake_window::push_d() {
    // std::cout << "d pressed" << std::endl;
    if (game_status == GameStatus::PAUSE)
        game_status = GameStatus::RUN;

    game_direction = can_direction_to(Direction::RIGHT);
};

inline void Snake_window::cb_pause(Address, Address pw) {
    reference_to<Snake_window>(pw).pause();
}

inline void Snake_window::cb_restart(Address, Address pw) {
    reference_to<Snake_window>(pw).restart();
}

inline void Snake_window::cb_quit(Address, Address pw) {
    reference_to<Snake_window>(pw).quit();
}

inline void Snake_window::cb_w(Address, Address pw) {
    reference_to<Snake_window>(pw).push_w();
}

inline void Snake_window::cb_d(Address, Address pw) {
    reference_to<Snake_window>(pw).push_d();
}

inline void Snake_window::cb_s(Address, Address pw) {
    reference_to<Snake_window>(pw).push_s();
}

inline void Snake_window::cb_a(Address, Address pw) {
    reference_to<Snake_window>(pw).push_a();
}

inline void Snake_window::draw_grid() {
    for (int i = 0; i < 20; ++i)
        for (int j = 0; j < 20; ++j) {
            vr.push_back(new Rectangle(Point(i * 20, j * 20), 20, 20));
            vr[vr.size() - 1].set_color(Color::Transparency::invisible);
            vr[vr.size() - 1].set_fill_color(Color::white);
            attach(vr[vr.size() - 1]);
        }
}

Rectangle &Snake_window::_get_rectangle(Dot p) {
    for (int i = 0; i < vr.size(); i++) {
        const Point loc = vr[i].get_location();
        if ((loc.x == p.get_x()) && (loc.y == p.get_y()))
            return vr[i];
    }

    return vr[0];
}

inline void Snake_window::fill_rectangle_with_color(Rectangle &rect,
                                                    Color c = Color::green) {
    rect.set_fill_color(c);
}

inline void Snake_window::paint_color(Dot p, Color c = Color::green) {
    fill_rectangle_with_color(_get_rectangle(p), c);
}

void Snake_window::clean_dot(Dot p, Color c) { paint_color(p, c); }

void Snake_window::paint_dot(Dot p, Color c) { paint_color(p, c); }

void Snake_window::paint_dots(const std::vector<Dot> &dots, Color last_color,
                              Color first_dot_color) {
    for (int i = 0; i < dots.size(); i++) {
        paint_color(dots[i], last_color);
        if (i == 0)
            paint_dot(dots[i], first_dot_color);
    }
}

void Snake_window::init_game() {
    snake = Snake(INIT_SNAKE_LENGTH);
    paint_dots(snake.locations());
    food_dot = Dot::get_random_dot_exclude(snake.locations());
    paint_dot(food_dot);

    // game_over_text.move(500, 500);
    game_over_text.set_label("");
    update_score();
}

inline Direction Snake_window::can_direction_to(Direction d) {
    Direction current_snake_direction = current_direction();

    switch (current_snake_direction) {
        case Direction::UP:
            if (d == Direction::RIGHT || d == Direction::UP || d == Direction::LEFT)
                return d;
            break;
        case Direction::DOWN:
            if (d == Direction::RIGHT || d == Direction::DOWN || d == Direction::LEFT)
                return d;
            break;
        case Direction::LEFT:
            if (d == Direction::UP || d == Direction::LEFT || d == Direction::DOWN)
                return d;
            break;
        case Direction::RIGHT:
            if (d == Direction::UP || d == Direction::RIGHT || d == Direction::DOWN)
                return d;
            break;
    }
    return current_snake_direction;
}

Direction Snake_window::current_direction() {
    Direction current_snake_direction;
    auto locs = snake.locations();
    auto p0 = locs[0];
    auto p1 = locs[1];

    if (p0.get_x() == p1.get_x()) {
        if (p0.get_y() > p1.get_y())
            current_snake_direction = Direction::DOWN;
        else
            current_snake_direction = Direction::UP;
    } else if (p0.get_y() == p1.get_y()) {
        if (p0.get_x() > p1.get_x())
            current_snake_direction = Direction::RIGHT;
        else
            current_snake_direction = Direction::LEFT;
    }

    return current_snake_direction;
}

inline void Snake_window::clean_all_dots_color(Color c) {
    for (int i = 0; i < vr.size(); i++) {
        vr[i].set_fill_color(c);
    }
}

void Snake_window::update_score() {
    int snake_length = snake.length() - INIT_SNAKE_LENGTH;
    stringstream ss;
    if (snake_length < 10)
        ss << "00" << snake_length;
    else if (snake_length < 100)
        ss << "0" << snake_length;
    else
        ss << snake_length;

    score_text.set_label(ss.str());
}

void Snake_window::game_over() { game_over_text.set_label("GAME OVER!!!"); };
