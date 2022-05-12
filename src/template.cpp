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
    std::cout << "multiplication of nxn tensor with n-dim-vector" << std::endl;
    auto start = std::chrono::steady_clock::now();
    WTens<double, 1> vec(4);
    WTens<double, 2> test(4, 4);

    vec.setValues({15,16,17,18});
    test.setValues({{1,2,3,4},{5,6,7,8}});
    
    auto res = test * vec;

    auto finish = std::chrono::steady_clock::now();
    double elapsed_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
            .count();
    std::cout << "elapsed time: " << elapsed_time << " ms \n";

    // WTens<double, 1> vector(4);
    // vector.setValues({1,2,3,4});
    // vector.print();
    
    // WTens<double, 2> tensor2(2,2);
    // tensor2.setValues({{1,2},{3,4}});
    // tensor2.print();

    // WTens<double, 3> tensor3(2,2,2);
    // tensor3.setValues({{{1,1},{2,2}},{{3,3},{4,4}},{{5,5},{6,6}}});
    // tensor3.print();
  }
  catch (std::exception &e)
  {
    std::cerr << "exception caught: " << e.what() << '\n';
  }
  return 0;
}