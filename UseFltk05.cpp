#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <X11/Xlib.h>
#include <iostream>

#include "./snake.h"

using std::cout;
using std::endl;

class MyWidget : public Fl_Widget {
protected:
  int handle(int);

public:
  MyWidget(int x, int y, int w, int h, const char *label)
      : Fl_Widget(x, y, w, h, label){};
  MyWidget(int x, int y, int w, int h) : MyWidget(x, y, w, h, 0L){};
  void draw();
  void draw_snake(int x, int y, int w, int h);
  void draw_snake(int x, int y);
};

int MyWidget::handle(int event) { return Fl_Widget::handle(event); }

void MyWidget::draw() { fl_frame("Main", 5, 5, 900, 600); }

void MyWidget::draw_snake(int x, int y, int w, int h) { fl_rect(x, y, w, h); }
void MyWidget::draw_snake(int x, int y) {
  MyWidget::draw_snake(x, y, snake_box_width, snake_box_hight);
}
void button02_cb(Fl_Widget *w, Fl_Window *fw) {
  std::cout << "Button2 Pressed" << std::endl;
  fw -> make_current();
  Fl::redraw();

  // fw->redraw();
  ((MyWidget *)w)->redraw();
  ((MyWidget *)w)->draw_snake(50, 50);
  ((MyWidget *)w)->draw_snake(80, 80);

  // fw->redraw();
  // fw->draw_snake(30, 30);
  // fw->draw_snake(60, 60);
  // fw->make_current();
}

void Btn01_cb(Fl_Widget *w, Fl_Window *fw) {
  std::cout << "Button Pressed" << std::endl;
  // mw->redraw();
  // mw->draw_snake(10, 10);
  //Fl::redraw();
  ((MyWidget *)w)->draw_snake(20, 20);
  //   fw->make_current();
  Snake sn(4);
  std::vector<Point> ls = sn.get_locations();
  for (auto it = ls.begin(); it != ls.end(); it++) {
    std::cout << it->get_x() << "\t" << it->get_y() << std::endl;
  }

  ls = sn.move(Direction::UP);
  std::cout << " " << std::endl;
  for (auto it = ls.begin(); it != ls.end(); it++) {
    std::cout << it->get_x() << "\t" << it->get_y() << std::endl;
  }

  Point np(100, 100);
  // ls = sn.eat(np);
  std::cout << " " << std::endl;
  for (auto it = ls.begin(); it != ls.end(); it++) {
    std::cout << it->get_x() << "\t" << it->get_y() << std::endl;
  }

  Point p(90, 90);
  std::cout << p.get_x() << "\t" << p.get_y() << std::endl;
  p.move(Direction::DOWN);
  std::cout << p.get_x() << "\t" << p.get_y() << std::endl;

  cout << dist_width(eng) << endl;
  cout << dist_height(eng) << endl;

  Point random_p;
  random_p.get_random_point_exclude(sn.get_locations());
  cout << random_p.get_x() << '\t' << random_p.get_y() << endl;
}

int main(int argc, char **argv) {
  auto window = new Fl_Window(1200, 600);
  // fl_frame("Main", 5, 5, 900, 600);
  auto mw = new MyWidget(0, 0, 910, 610);
  auto button = new Fl_Button(935, 100, 30, 30, "W");
  button->shortcut('w');
  button->type(FL_NORMAL_BUTTON);
  button->callback((Fl_Callback *)Btn01_cb, mw);

  auto button02 = new Fl_Button(935, 140, 30, 30, "S");
  button02->shortcut('s');
  button02->type(FL_NORMAL_BUTTON);
  button02->callback((Fl_Callback *)button02_cb, mw);

  //   window->end();
  window->show(argc, argv);
  // window->make_current();
  return Fl::run();
}
