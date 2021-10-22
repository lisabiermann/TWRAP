// SPDX-FileCopyrightText: 2021 Lisa Biermann
//
// SPDX-License-Identifier: GPL-3.0-or-later

/**
 * @file
 */

#include <TWrap/TWrap.h>

namespace TWrap
{

/*
 * Print tensor values
 */
void TWrap::write()
{
  if (this->Dim1 != 0 && this->Dim2 == 0 && this->Dim3 == 0 && this->Dim4 == 0)
    std::cout << this->T1 << std::endl;
  else if (this->Dim1 != 0 && this->Dim2 != 0 && this->Dim3 == 0 &&
           this->Dim4 == 0)
    std::cout << this->T2 << std::endl;
  else if (this->Dim1 != 0 && this->Dim2 != 0 && this->Dim3 != 0 &&
           this->Dim4 == 0)
    std::cout << this->T3 << std::endl;
  else if (this->Dim1 != 0 && this->Dim2 != 0 && this->Dim3 != 0 &&
           this->Dim4 != 0)
    std::cout << this->T4 << std::endl;
  else if (this->Dim1 == 0 && this->Dim2 == 0 && this->Dim3 == 0 &&
           this->Dim4 == 0)
    std::cout << this->T0 << std::endl;
  else
    throw std::runtime_error("Wrong tensor dimensions!");
}

/*
 * Addition of tensors
 */
TWrap TWrap::operator+(TWrap t)
{
  if (this->Dim1 == t.Dim1 && this->Dim2 == t.Dim2 && this->Dim3 == t.Dim3 &&
      this->Dim4 == t.Dim4)
  {
    TWrap result(t.Dim1, t.Dim2, t.Dim3, t.Dim4);

    result.T0 = this->T0 + t.T0;
    result.T1 = this->T1 + t.T1;
    result.T2 = this->T2 + t.T2;
    result.T3 = this->T3 + t.T3;
    result.T4 = this->T4 + t.T4;

    return result;
  }
  else
    throw std::runtime_error("Trying to add tensors with wrong dimensions!");
}

/*
 * Multiplication of tensors
 */
TWrap TWrap::operator*(TWrap t)
{
  // 0-dim tensors
  if (this->Dim1 == t.Dim1 && this->Dim2 == t.Dim2 && this->Dim3 == t.Dim3 &&
      this->Dim4 == t.Dim4 && t.Dim1 == 0 && t.Dim2 == 0 && t.Dim3 == 0 &&
      t.Dim4 == 0)
  {
    TWrap result(t.Dim1);
    result.T0 = this->T0 * t.T0;
    return result;
  }
  // 1-dim tensors
  else if (this->Dim1 == t.Dim1 && this->Dim2 == t.Dim2 &&
           this->Dim3 == t.Dim3 && this->Dim4 == t.Dim4 && t.Dim1 != 0 &&
           t.Dim2 == 0 && t.Dim3 == 0 && t.Dim4 == 0)
  {
    TWrap result(0);
    result.T0 = (this->T1 * t.T1).sum();
    return result;
  }
  // 2-dim tensors
  else if (this->Dim2 == t.Dim1 && this->Dim3 == t.Dim3 &&
           this->Dim4 == t.Dim4 && t.Dim1 != 0 && this->Dim1 != 0 &&
           t.Dim2 != 0 && t.Dim3 == 0 && t.Dim4 == 0)
  {
    TWrap result(this->Dim1, t.Dim2);

    // for (int i = 0; i <= this->Dim1; i++)
    // {
    //   for (int j = 0; j <= t.Dim2; j++)
    //   {
    //     for (int n = 0; n <= this->Dim2; n++)
    //     {
    //       result(i, j) += double(this->T2(i, n) * t.T2(n, j));
    //     };
    //   };
    // };

    return result;
  }
  // 2-dim tensor and 1-dim tensor
  else if (this->Dim2 == t.Dim1 && this->Dim3 == t.Dim3 &&
           this->Dim4 == t.Dim4 && t.Dim1 != 0 && this->Dim1 != 0 &&
           t.Dim2 == 0 && t.Dim3 == 0 && t.Dim4 == 0)
  {
    TWrap result(this->Dim1);
    return result;
  }
  // 2-dim tensor and 0-dim tensor
  else if (this->Dim1 != 0 && this->Dim2 != 0 && t.Dim1 == 0 && t.Dim2 == 0 &&
           t.Dim3 == 0 && t.Dim4 == 0)
  {
    TWrap result(this->Dim1, this->Dim2);
    return result;
  }
  // 3-dim tensors
  // 4-dim tensors
  else
    throw std::runtime_error(
        "Trying to multiply tensors with wrong dimensions!");
}

} // namespace TWrap
