/**
 * @file snake_window.h
 * @author combofish (combofish49@gmail.com)
 * @brief 定义游戏的窗口类
 * @version 0.6
 * @date 2021-10-16
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef _SNAKE_WINDOW_H_
#define _SNAKE_WINDOW_H_
#include "GUI_Interface/GUI.h"
#include "GUI_Interface/Graph.h"
#include "GUI_Interface/Point.h"
#include "GUI_Interface/Window.h"
#include "dot.h"
#include "snake.h"
#include <vector>

using namespace Graph_lib;

namespace snake_game {

enum class GameStatus { PAUSE, RUN, COLLISION };

const Color back_ground_color = Color::white;
const Color snake_body_color = Color::green;
const Color snake_head_color = Color::dark_blue;
const Color food_color = Color::dark_red;
const int INIT_SNAKE_LENGTH = 3;

class Snake_window : public Graph_lib::Window {
public:
  Snake_window(Point p, int w, int h, const std::string &title);

  /**/
  Snake snake;
  Dot food_dot;

  GameStatus game_status;
  Direction game_direction;

  bool is_ready = false;

  void init_game();
  void game_over();

  void clean_dot(Dot, Color c = back_ground_color);

  /* 给一格填充颜色。*/
  void paint_dot(Dot, Color c = food_color);

  /* 给格填充颜色,可以设置主要填充颜色，和开头的填充颜色。*/
  void paint_dots(const std::vector<Dot> &dots,
                  Color last_color = snake_body_color,
                  Color first_dot_color = snake_head_color);

  Direction current_direction();
  void update_score();

private:
  /* 事件循环。 */
  // static void callback(Address);
  // void do_loop();

  /**/
  void clean_all_dots_color(Color c = back_ground_color);

  Direction can_direction_to(Direction);

  /* */
  Vector_ref<Rectangle> vr;

  /* */
  void draw_grid();

  /* 给一格填充颜色。*/
  void paint_color(Dot, Color);

  /* 获取位置点所对应的矩形。 */
  Rectangle &_get_rectangle(Dot);

  /* 给一个矩形填充颜色。 */
  void fill_rectangle_with_color(Rectangle &, Color);

  // Out_box score_out;

  Text game_name_text;
  Text instruction_start_text;
  Text game_over_text;

  Text instruction_quit_text;
  Text instruction_restart_text;
  Text instruction_pause_text;
  Text instruction_quit_text_;
  Text instruction_restart_text_;
  Text instruction_pause_text_;

  Text score_text;

  /* 画一个矩形框作为蛇的活动区域。 */
  Rectangle square;

  bool button_pushed;
  Button w_button;
  Button s_button;
  Button a_button;
  Button d_button;
  Button reset_button;
  Button quit_button;
  Button pause_button;

  void pause();
  void restart();
  void quit();

  void push_s();
  void push_w();
  void push_a();
  void push_d();

  static void cb_pause(Address, Address);
  static void cb_restart(Address, Address);
  static void cb_quit(Address, Address);

  static void cb_w(Address, Address);
  static void cb_s(Address, Address);
  static void cb_a(Address, Address);
  static void cb_d(Address, Address);
};
}; // namespace snake_game
#endif
