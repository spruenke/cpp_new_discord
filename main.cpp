
#include "Math.hpp"
#include <iostream>

int main()
{
  Matrix<int> m1{{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
  std::cout << multiply(m1, m1);
  Matrix<int> m2{{3, 6}, {1, 2}};
  std::cout << transpose(m2);
  // Matrix<int> m2{{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
  // ++m1;
  // Matrix<int> m4 = m2;
  // std::cout << m1 + m2 << std::endl;
  // std::cout << m1 / m2 << std::endl;
  // Matrix<int> m3{m2};
  // Matrix<int> m55(3, 4);
  // std::cout << m55 << std::endl;
  std::vector<int> v{1, 3, 6, 1};
  std::cout << norm(v) << std::endl;
  std::cout << m1.norm(2) << std::endl;
  Matrix<int> row(1, 5);
  row = transpose(row);
  std::cout << row;
}