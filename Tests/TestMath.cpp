#include <iostream>
#include "Framework/Common/Math/MathLib.h"

using namespace ProjectEngine;

int main()
{
    Matrix3f m;
    m << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    std::cout << m << std::endl;

    Matrix3f t = m.transpose();
    std::cout << t << std::endl;

    Matrix4f r = Matrix4f::Random();
    std::cout << r << std::endl;

    return 0;
}