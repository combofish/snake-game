
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "GUI.h"
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <string>

namespace Graph_lib {

//------------------------------------------------------------------------------

void Button::attach(Window &win) {
  pw = new Fl_Button(loc.x, loc.y, width, height, label.c_str());
  reference_to<Fl_Button>(pw).shortcut(s);
  pw->callback(reinterpret_cast<Fl_Callback *>(do_it), &win); // pass the window
  own = &win;
}

//------------------------------------------------------------------------------

int In_box::get_int() {
  Fl_Input &pi = reference_to<Fl_Input>(pw);
  // return atoi(pi.value());
  const char *p = pi.value();
  if (!isdigit(p[0]))
    return -999999;
  return atoi(p);
}

//------------------------------------------------------------------------------

string In_box::get_string() {
  Fl_Input *p = static_cast<Fl_Input *>(pw);

  return string{p->value()};
}

//------------------------------------------------------------------------------

void In_box::attach(Window &win) {
  pw = new Fl_Input(loc.x, loc.y, width, height, label.c_str());
  own = &win;
}

//------------------------------------------------------------------------------

void Out_box::put(const string &s) {
  reference_to<Fl_Output>(pw).value(s.c_str());
}

//------------------------------------------------------------------------------

void Out_box::attach(Window &win) {
  pw = new Fl_Output(loc.x, loc.y, width, height, label.c_str());
  own = &win;
}

//------------------------------------------------------------------------------

Menu::Menu(Point xy, int w, int h, Kind kk, const string &label)
    : Widget(xy, w, h, label, 0), k(kk), offset(0) {}

//------------------------------------------------------------------------------

void Menu::hide() // hide all buttons
{
  for (unsigned int i = 0; i < selection.size(); ++i)
    selection[i].hide();
}

//------------------------------------------------------------------------------

void Menu::move(int dx, int dy) // move all buttons
{
  for (unsigned int i = 0; i < selection.size(); ++i)
    selection[i].move(dx, dy);
}

//------------------------------------------------------------------------------

void Menu::attach(Window &win) // attach all buttons
{
  for (int i = 0; i < selection.size(); ++i)
    win.attach(selection[i]);
  own = &win;
}

//------------------------------------------------------------------------------

int Menu::attach(Button &b) {
  b.width = width;
  b.height = height;

  switch (k) {
  case horizontal:
    b.loc = Point{loc.x + offset, loc.y};
    offset += b.width;
    break;
  case vertical:
    b.loc = Point{loc.x, loc.y + offset};
    offset += b.height;
    break;
  }
  selection.push_back(b); // b is NOT OWNED: pass by reference
  return int(selection.size() - 1);
}

//------------------------------------------------------------------------------

int Menu::attach(Button *p) {
  Button &b = *p;
  b.width = width;
  b.height = height;

  switch (k) {
  case horizontal:
    b.loc = Point{loc.x + offset, loc.y};
    offset += b.width;
    break;
  case vertical:
    b.loc = Point{loc.x, loc.y + offset};
    offset += b.height;
    break;
  }
  selection.push_back(&b); // b is OWNED: pass by pointer
  return int(selection.size() - 1);
}

//------------------------------------------------------------------------------

}; // namespace Graph_lib
