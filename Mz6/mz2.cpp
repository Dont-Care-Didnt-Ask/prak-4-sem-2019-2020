#include <algorithm>

/*
 * You are given a rectangular field of n by m squares.
 * At each step you can move to any of 8 adjacent squares – horizontally, vertically or diagonally.
 * Right edge is connected with left edge, and top edge is connected with bottom edge.
 * I.e. one can get from (0, y) to (n-1, y) OR from (x, 0) to (x, m-1) in one move.
 * 
 * Define a template class 'Coord' for coordinates, parametrized by type of coordinates of the point.
 * Define a function 'dist' which calculates the distance between two points 
 * (i.e. minimal amount of steps to get from first to second).
*/

template <typename T>
class Coord{
public:
    typedef T value_type;
    T row{}, col{};

    Coord() = default; 
    Coord(T row): row{row} {}
    Coord(T row, T col): row{row}, col{col} {}
};


template <typename T>
T dist(const Coord<T>& field, const Coord<T>& first, const Coord<T>& second) {
    // first argument describes the field (amount of rows and columns, n and m)
    T rows = field.row, cols = field.col;
    // then we have points
    T x1 = first.col, y1 = first.row;
    T x2 = second.col, y2 = second.row;

    // Should have checked the correctness of the input (do the points lie in the field),
    // but it passed the tests anyway.

    if (x2 < x1) {
        std::swap(x2, x1);
    }
    if (y2 < y1) {
        std::swap(y2, y1);
    }
    // doesn't change the distance because of mirror symmetry
    
    T right = x2 - x1;          // from x1 to x2 directly. 'right' since x1 <= x2, and we move to the right
    T left  = cols + x1 - x2;   // or through connected edges
    T up    = y2 - y1;
    T down  = rows + y1 - y2;

    using std::max;
    using std::min;

    /* 
    Since we can move diagonally, the distance between two points is
    the maximum of x-distance and y-distance. There are two ways to get from x1 to x2 
    and two ways to get from y1 to y2 – directly or via conneted edges, so 4 variants at all.
     */
    T right_best = min(max(right, up), max(right, down));
    T left_best  = min(max(left, up),  max(left, down));
    return min(right_best, left_best);
}