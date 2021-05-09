
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <ostream>
#include <vector>

template <typename T>
class Matrix
{
public:
  Matrix() = default;

  Matrix(std::initializer_list<std::vector<T>> list)
  {
    std::for_each(begin(list), end(list),
                  [this](auto const &row) { matrix.push_back(row); });
  }

  Matrix(std::size_t rows, std::size_t cols)
      : matrix(rows, std::vector<T>(cols))
  {
  }

  auto norm(double p = 2)
  {
    double result{};
    for (size_t row = 0; row < rows(); row++) {
      for (size_t col = 0; col < cols(); col++) {
        result += std::pow(std::abs(matrix[row][col]), p);
      }
    }
    return std::pow(result, 1 / p);
  }

  auto operator++()
  {
    std::for_each(matrix.begin(), matrix.end(), [](auto &row) {
      std::for_each(row.begin(), row.end(), [](auto &elem) { ++elem; });
    });
    return *this;
  }

  auto rows() const { return matrix.size(); }
  auto cols() const
  {
    assert(!matrix.empty());
    return matrix[0].size();
  }

  Matrix operator+(Matrix const &other)
  {
    assert(rows() == other.rows());
    assert(cols() == other.cols());

    for (size_t row = 0; row < rows(); row++) {
      for (size_t col = 0; col < cols(); col++) {

        matrix[row][col] += other.matrix[row][col];
      }
    }
    return *this;
  }
  Matrix operator-(Matrix const &other)
  {
    assert(rows() == other.rows());
    assert(cols() == other.cols());

    for (size_t row = 0; row < rows(); row++) {
      for (size_t col = 0; col < cols(); col++) {
        matrix[row][col] -= other.matrix[row][col];
      }
    }
    return *this;
  }
  Matrix operator*(Matrix const &other)
  {
    assert(rows() == other.rows());
    assert(cols() == other.cols());

    for (size_t row = 0; row < rows(); row++) {
      for (size_t col = 0; col < cols(); col++) {
        matrix[row][col] *= other.matrix[row][col];
      }
    }
    return *this;
  }
  Matrix operator/(Matrix const &other)
  {
    assert(rows() == other.rows());
    assert(cols() == other.cols());

    for (size_t row = 0; row < rows(); row++) {
      for (size_t col = 0; col < cols(); col++) {
        matrix[row][col] /= other.matrix[row][col];
      }
    }
    return *this;
  }

  std::vector<std::vector<T>> matrix;
};

template <typename T>
std::ostream &operator<<(std::ostream &out, Matrix<T> const &m)
{
  for (size_t row = 0; row < m.rows(); row++) {
    for (size_t col = 0; col < m.cols(); col++) {
      out << std::setw(6) << std::right << m.matrix[row][col];
    }
    std::cout << std::endl;
  }
  out << "\n\n";
  return out;
}

template <typename T, typename U>
Matrix<double> multiply(Matrix<T> const &lhs, Matrix<U> const &rhs)
{
  assert(lhs.cols() == rhs.rows());
  Matrix<double> result(lhs.rows(), rhs.cols());

  for (size_t i = 0; i < lhs.rows(); i++) {
    for (size_t j = 0; j < rhs.cols(); j++) {
      for (size_t z = 0; z < lhs.cols(); z++) {
        result.matrix[i][j] += lhs.matrix[i][z] * rhs.matrix[z][j];
      }
    }
  }

  return result;
}

template <typename T>
auto transpose(Matrix<T> const &m)
{
  Matrix<T> result(m.cols(), m.rows());

  for (size_t i = 0; i < m.rows(); i++) {
    for (size_t j = 0; j < m.cols(); j++) {
      result.matrix[j][i] = m.matrix[i][j];
    }
  }

  return result;
}

template <typename T>
auto norm(std::vector<T> const &v, double p = 2)
{
  return std::pow(std::accumulate(v.begin(), v.end(), 0.0,
                                  [p](auto lhs, auto el) {
                                    return lhs + std::pow(std::abs(el), p);
                                  }),
                  1 / p);
}