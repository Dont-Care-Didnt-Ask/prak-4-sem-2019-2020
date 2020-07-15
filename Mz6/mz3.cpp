
/*
 * You are given a hexagonal field of n rows and m columns.
 * At each step you can move to any of 6 adjacent hexes.
 * 
 * What is the minimal amount of steps needed to get from (r1, c1) to (r2, c2)?
*/

/*
    /‾‾‾\   /‾‾‾\          /‾‾‾\
    |0,1|   |0,3|  ...   __|0,m|
/‾‾‾\___/‾‾‾\___/‾‾‾\      \___/
 0,0|   |0,2|   |0,4| ...  |   
\___/‾‾‾\___/‾‾‾\___/      /‾‾‾\
    |1,1|   |1,3|  ...     |1,m|
/‾‾‾\___/‾‾‾\___/‾‾‾\      \___/
|1,0|   |1,2|   |1,4| ...
\___/‾‾‾\___/‾‾‾\___/
    ...
    ...
\___/‾‾‾\___/‾‾‾\
    |n,1|   |n,3| ...
/‾‾‾\___/‾‾‾\___/
|n,0|   |n,2|     ...       
\___/   \___/

 I'm really sorry for my drawing skills.
*/

namespace Game{
    template <typename T>
    class Coord
    {
    public:
        typedef T value_type;
        T row, col;
        Coord(): row{}, col{}
        {}
        Coord(T r): row{r}, col{}
        {}
        Coord(T r, T c): row{r}, col{c}
        {}
    };

    template <typename T>
    T dist(const Coord<T>& field, const Coord<T>& first, const Coord<T>& second)
    {
        T x1 = first.col, y1 = first.row;
        T x2 = second.col, y2 = second.row;

        // There is no way you will understand what I did.
        // I don't understand it myself by this moment.
        // So just live, knowing, that this task can be solved in five ternary operators.

        T x_dist =  (x2 > x1) ? (x2 - x1) : (x1 - x2);
        T y_dist =  (y2 > y1) ? (y2 - y1) : (y1 - y2);
        T start_x = (x1 < x2) ? x1 : x2;

        T parity_addendum = ((x1 < x2) == (y1 < y2)) ? 1 - start_x % 2 : start_x % 2;

        T y_gain = (x_dist + parity_addendum) / 2;

        T y_residial = (y_dist - y_gain > 0) ? (y_dist - y_gain) : 0;

        return x_dist + y_residial;
    }
};