// SPDX-FileCopyrightText: 2021 Lisa Biermann
//
// SPDX-License-Identifier: GPL-3.0-or-later

/**
 * @file
 * template executable that shows the utilization of the TWrap Class
 *
 */

#include <TWrap/TWrap.h>
#include <exception>
#include <unsupported/Eigen/CXX11/Tensor>

using namespace std;
using namespace TWrap;

int main()
{
  try
  {
    WTens<double, 1> vec(3);
    WTens<double, 2> test(3, 3);

    test(0, 0) = 1.0;
    test(0, 1) = 2.0;
    test(1, 0) = 3.0;
    test(1, 1) = 4.0;

    vec(0) = 5.0;
    vec(1) = 6.0;

    auto res = test * vec;

    test.print();
    vec.print();
    res.print();

    auto res2 = WTens::concat<double, 2>(vec, 2);

    res2.print();
  }
  catch (std::exception &e)
  {
    std::cerr << "exception caught: " << e.what() << '\n';
  }
  return 0;
}