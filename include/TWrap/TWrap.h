// SPDX-FileCopyrightText: 2021 Lisa Biermann
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <iostream>
#include <unsupported/Eigen/CXX11/Tensor>

using namespace Eigen;

/**
 * @file
 */
namespace TWrap
{

template <typename InnerType, std::size_t dim> class WTens
{
private:
public:
  Tensor<InnerType, dim> tens;

  // Constructor with initialization to zero
  template <typename... IndexTypes> WTens(IndexTypes... args) : tens(args...)
  {
    tens.setZero();
  }

  /*
   * Get tensor elements
   */
  template <typename... IndexTypes>
  InnerType operator()(IndexTypes... args) const
  {
    return tens(args...);
  }

  /*
   * Set tensor elements
   */
  template <typename... IndexTypes> InnerType &operator()(IndexTypes... args)
  {
    return tens(args...);
  }

  /*
   * Set tensor elements using nested initializer list
   */
  void setValues(std::initializer_list<InnerType> values)
  {
    this->tens.setValues(values);
  }
  void setValues(std::initializer_list<std::initializer_list<InnerType>> values)
  {
    this->tens.setValues(values);
  }
  void setValues(std::initializer_list<std::initializer_list<std::initializer_list<InnerType>>> values)
  {
    this->tens.setValues(values);
  }

  /*
   * Addition of tensors
   */
  WTens operator+(WTens t)
  {
    const auto &d1 = this->tens.dimensions();
    const auto &d2 = t.tens.dimensions();

    if (d1 == d2)
    {
      WTens<InnerType, dim> result;
      result.tens = this->tens + t.tens;
      return result;
    }
    else
      throw std::runtime_error("Trying to add tensors with wrong dimensions!");
  }

  /*
   * Multiplication of tensors
   */
  WTens operator*(InnerType scale)
  {
    WTens<InnerType, dim> result;
    result.tens = this->tens * scale;
    return result;
  }

  template <std::size_t dimin>
  WTens<InnerType, 1> operator*(WTens<InnerType, dimin> t)
  {
    Eigen::array<Eigen::IndexPair<InnerType>, 1> product_dims = {
        Eigen::IndexPair<InnerType>(1, 0)};
    WTens<InnerType, 1> result;
    result.tens = this->tens.contract(t.tens, product_dims);
    return result;
  }

  WTens concat(WTens<InnerType, dim> v, int index) { return v * double(index); }

  /*
   * write tensor
   */
  void print() { std::cout << this->tens << std::endl; }
};

} // namespace TWrap
