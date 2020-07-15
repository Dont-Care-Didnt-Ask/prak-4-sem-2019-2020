#include <utility>
#include <vector>
#include <array>
#include <complex>
#include <limits>

/*
 Solve a quadratic equation with complex coefficients.
 Function should return a pair of bool and vector of solutions.
 bool is set to true, if an equation has two solutions, one solution or no solutions,
 and to false otherwise (in case 0x^2 + 0x + 0 = 0).
*/
namespace Equations
{
    template<typename _Tp>
    auto quadratic(std::array<std::complex<_Tp>, 3> equation) -> std::pair<bool, std::vector<std::complex<_Tp>>>
    {
        using std::vector;
        using std::complex;
        using std::norm;

        complex<_Tp> c = equation[0], b = equation[1], a = equation[2];
        _Tp EPS = 32 * std::numeric_limits<_Tp>::epsilon();

        // I don't want to mix integers with complex numbers in computations below
        // so I'll make a couple of constants
        constexpr complex<_Tp> four(4, 0), two(2, 0); 

        if (norm(a) < EPS) {
            if (norm(b) < EPS) { // identity (i.e. c = 0)
                if (norm(c) < EPS) {
                    return {false, vector<complex<_Tp>>{}};
                } else {
                    return {true, vector<complex<_Tp>>{}};
                }
            } else { // linear equation
                return {true, vector<complex<_Tp>>{ -c / b }};
            }
        } else { // quadratic equation
            complex<_Tp> discriminant = b * b - four * a * c;
            if (norm(discriminant) < EPS) {
                return {true, vector<complex<_Tp>>{ -b / (two * a), -b / (two * a)}};
            }
            discriminant = std::sqrt(discriminant);
            return {true, vector<complex<_Tp>>{ (discriminant - b) / (two * a), (-discriminant - b) / (two * a)}};
        }
    }
};