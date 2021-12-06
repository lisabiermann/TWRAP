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
  Tensor<InnerType, dim> tens;

public:
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

  WTens operator*(WTens t)
  {
    const auto &d1 = this->tens.dimensions();
    const auto &d2 = t.tens.dimensions();

    if (d2[t.tens.NumDimensions - 1] == d1[this->tens.NumDimensions - 1])
    {
      WTens<InnerType, dim> result;
      result.tens = this->tens * t.tens;
      /* todo: implement proper Einstein sum convention */
      return result;
    }
    else
      throw std::runtime_error(
          "Trying to multiply tensors with wrong dimensions!");
  }
};

} // namespace TWrap
