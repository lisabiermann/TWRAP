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

using namespace std;
using namespace TWrap;

int main(int argc, char *argv[])
{
  try
  {
    // addition of tensors with wrong dimensions
    WTens<double, 2> test1(2, 2);
    WTens<double, 2> test2(3, 3);

    test1(0, 0) = 1.0;
    test2(0, 0) = 3.3;

    WTens<double, 2> test3 = test1 + test2;
  }
  catch (std::exception &e)
  {
    std::cerr << "exception caught: " << e.what() << '\n';
  }
  return 0;
}