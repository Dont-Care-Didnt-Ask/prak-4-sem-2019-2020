#include <iostream>

/*
 * You are given a rectangular field of n by m squares.
 * At each step you can move one square up, down, left or right – one of 4 directions.
 * Right edge is connected with left edge, and top edge is connected with bottom edge.
 * I.e. one can get from (0, y) to (n-1, y) OR from (x, 0) to (x, m-1) in one move.
 * 
 * What is the minimal amount of steps needed to get from (r1, c1) to (r2, c2)?
*/

int main(){
    int m, n;
    std::cin >> m >> n;
    int r1, c1, r2, c2;
    while(std::cin >> r1 >> c1 >> r2 >> c2) {
        if (r2 < r1) {
            std::swap(r1, r2);
        }
        if (c2 < c1) {
            std::swap(c1, c2);
        }
        // doesn't change anything because of the symmetry
    
        int x = std::min(r2 - r1, r1 + m - r2); 
        // either directly from r1 to r2, 
        // or using the fact that the edges are connected
        int y = std::min(c2 - c1, c1 + n - c2);

        std::cout << x + y << std::endl;
        // first going horizontally, from r1 to r2, then vertically, from c1 to c2
    }
    return 0;
}
