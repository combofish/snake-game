
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef POINT_GUARD
#define POINT_GUARD

namespace Graph_lib {
//------------------------------------------------------------------------------

    class Point {
    public:
        int x, y;

        Point(int new_x, int new_y) : x(new_x), y(new_y) {}

        Point() : x(0), y(0) {}
    };

//------------------------------------------------------------------------------

    inline bool operator==(Point a, Point b) { return a.x == b.x && a.y == b.y; }

//------------------------------------------------------------------------------

    inline bool operator!=(Point a, Point b) { return !(a == b); }

//------------------------------------------------------------------------------

} // namespace Graph_lib
#endif // POINT_GUARD
