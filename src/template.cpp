// SPDX-FileCopyrightText: 2021 Lisa Biermann
//
// SPDX-License-Identifier: GPL-3.0-or-later

/**
 * @file
 * template executable that shows the utilization of the TWrap Class
 *
 */

#include <TWrap/TWrap.h>
#include <chrono>
#include <exception>

using namespace std;
using namespace TWrap;

int main()
{
  try
  {
    std::cout << "multiplication of 10^10 tensor with 10-dim-vector"
              << std::endl;
    auto start_tens = std::chrono::steady_clock::now();

    WTens<double, 8> tens1(10, 10, 10, 10, 10, 10, 10, 10);
    tens1.setRandom();
    std::cout << "initialized tens1 with " << std::endl;
    tens1.print_DimOut();

    WTens<double, 1> tens2(10);
    tens2.setRandom();
    std::cout << "initialized tens2 with " << std::endl;
    tens2.print_DimOut();

    for (int i = 0; i < tens1.get_NumDimensions(); i++)
    {
      std::cout << "concat tensors at indices (" << i << " , " << 0 << ") ..."
                << std::endl;
      auto res = tens1.concat(tens2, i, 0);
      res.print_DimOut();
    }

    auto finish_tens = std::chrono::steady_clock::now();
    double elapsed_time_tens =
        std::chrono::duration_cast<std::chrono::milliseconds>(finish_tens -
                                                              start_tens)
            .count();
    std::cout << "elapsed time: " << elapsed_time_tens << " ms \n";
  }

  catch (TWrapExceptionBase &e)
  {
    e.what();
    exit(EXIT_FAILURE);
  }

  return 0;
}