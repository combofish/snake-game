
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef GUI_GUARD
#define GUI_GUARD

#include "Graph.h"
#include "Window.h"

namespace Graph_lib {

//------------------------------------------------------------------------------

    typedef void *Address; // Address is a synonym for void*
    typedef void (*Callback)(
            Address, Address); // FLTK's required function type for all callbacks

//------------------------------------------------------------------------------

    template<class W>
    W &reference_to(Address pw)
// treat an address as a reference to a W
    {
        return *static_cast<W *>(pw);
    }

//------------------------------------------------------------------------------

    class Widget {
        // Widget is a handle to an Fl_widget - it is *not* an Fl_widget
        // We try to keep our interface classes at arm's length from FLTK
    public:
        Widget(Point xy, int w, int h, const string &s, Callback cb)
                : loc(xy), width(w), height(h), label(s), do_it(cb) {}

        virtual ~Widget() {}

        virtual void move(int dx, int dy) {
            hide();
            pw->position(loc.x += dx, loc.y += dy);
            show();
        }

        virtual void hide() { pw->hide(); }

        virtual void show() { pw->show(); }

        virtual void attach(Window &) = 0;

        Point loc;
        int width;
        int height;
        string label;
        Callback do_it;

    protected:
        Window *own;   // every Widget belongs to a Window
        Fl_Widget *pw; // connection to the FLTK Widget
    };

//------------------------------------------------------------------------------

    class Button : public Widget {
        int s = 0;

    public:
        Button(Point xy, int w, int h, const string &label, Callback cb)
                : Widget(xy, w, h, label, cb) {}

        void set_shortcut(int ns) { s = ns; };

        void attach(Window &win);
    };

//------------------------------------------------------------------------------

    struct In_box : Widget {
        In_box(Point xy, int w, int h, const string &s) : Widget(xy, w, h, s, 0) {}

        int get_int();

        string get_string();

        void attach(Window &win);
    };

//------------------------------------------------------------------------------

    struct Out_box : Widget {
        Out_box(Point xy, int w, int h, const string &s) : Widget(xy, w, h, s, 0) {}

        void put(int);

        void put(const string &);

        void attach(Window &win);
    };
//------------------------------------------------------------------------------

    struct Menu : Widget {
        enum Kind {
            horizontal, vertical
        };

        Menu(Point xy, int w, int h, Kind kk, const string &label);

        Vector_ref<Button> selection;
        Kind k;
        int offset;

        int attach(Button &b); // Menu does not delete &b
        int attach(Button *p); // Menu deletes p

        void show() // show all buttons
        {
            for (unsigned int i = 0; i < selection.size(); ++i)
                selection[i].show();
        }

        void hide(); // hide all buttons

        void move(int dx, int dy); // move all buttons

        void attach(Window &win); // attach all buttons
    };

//------------------------------------------------------------------------------

} // namespace Graph_lib

#endif // GUI_GUARD
