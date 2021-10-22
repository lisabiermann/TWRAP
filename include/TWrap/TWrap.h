// SPDX-FileCopyrightText: 2021 Lisa Biermann
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <unsupported/Eigen/CXX11/Tensor>
#include <iostream>

using namespace Eigen;

/**
 * @file
 */
namespace TWrap
{

class TWrap
{
public:
  int Dim1            = 1;
  int Dim2            = 0;
  int Dim3            = 0;
  int Dim4            = 0;
  bool is_initialized = false;

  // basis constructor
  TWrap()
  {
    T0.setZero();
    T1.setZero();
    T2.setZero();
    T3.setZero();
    T4.setZero();
  };

  /*
   * Constructor
   */
  TWrap(int dim1, int dim2 = 0, int dim3 = 0, int dim4 = 0)
  {
    if (not is_initialized)
    {
      TWrap();
      is_initialized = true;
    };

    if (dim1 == 0 && dim2 == 0 && dim3 == 0 && dim4 == 0)
    {
      Dim1 = dim1;
      Tensor<double, 0> t0;
      T0 = t0;
    }
    else if (dim1 != 0 && dim2 == 0 && dim3 == 0 && dim4 == 0)
    {
      Dim1 = dim1;
      Tensor<double, 1> t1(dim1);
      T1 = t1;
    }
    else if (dim1 != 0 && dim2 != 0 && dim3 == 0 && dim4 == 0)
    {
      Dim1 = dim1;
      Dim2 = dim2;
      Tensor<double, 2> t2(dim1, dim2);
      T2 = t2;
    }
    else if (dim1 != 0 && dim2 != 0 && dim3 != 0 && dim4 == 0)
    {
      Dim1 = dim1;
      Dim2 = dim2;
      Dim3 = dim3;
      Tensor<double, 3> t3(dim1, dim2, dim3);
      T3 = t3;
    }
    else if (dim1 != 0 && dim2 != 0 && dim3 != 0 && dim4 != 0)
    {
      Dim1 = dim1;
      Dim2 = dim2;
      Dim3 = dim3;
      Dim4 = dim4;
      Tensor<double, 4> t4(dim1, dim2, dim3, dim4);
      T4 = t4;
    }
    else
      throw std::runtime_error("Wrong tensor dimensions!");
  }

  /*
   * Get tensor elements
   */
  double operator()(int i = -1, int j = -1, int k = -1, int l = -1) const
  {
    if (i == -1 && j == -1 && k == -1 && l == -1)
      return T0(0);
    else if (i >= 0 && j == -1 && k == -1 && l == -1)
      return T1(i);
    else if (i >= 0 && j >= 0 && k == -1 && l == -1)
      return T2(i, j);
    else if (i >= 0 && j >= 0 && k >= 0 && l == -1)
      return T3(i, j, k);
    else if (i >= 0 && j >= 0 && k >= 0 && l >= 0)
      return T4(i, j, k, l);
    else
      throw std::runtime_error("Wrong tensor dimensions!");
  }

  /*
   * Set tensor elements
   */
  double &operator()(int i = -1, int j = -1, int k = -1, int l = -1)
  {
    if (i == -1 && j == -1 && k == -1 && l == -1)
      return T0(0);
    else if (i >= 0 && j == -1 && k == -1 && l == -1)
      return T1(i);
    else if (i >= 0 && j >= 0 && k == -1 && l == -1)
      return T2(i, j);
    else if (i >= 0 && j >= 0 && k >= 0 && l == -1)
      return T3(i, j, k);
    else if (i >= 0 && j >= 0 && k >= 0 && l >= 0)
      return T4(i, j, k, l);
    else
      throw std::runtime_error("Wrong tensor dimensions!");
  }

  /*
   * Print tensor values
   */
  void write();

  /*
   * Addition of tensors
   */
  TWrap operator+(TWrap t);

  /*
   * Multiplication of tensors
   */
  TWrap operator*(TWrap t);

private:
  Tensor<double, 0> T0;
  Tensor<double, 1> T1;
  Tensor<double, 2> T2;
  Tensor<double, 3> T3;
  Tensor<double, 4> T4;
};

} // namespace TWrap
