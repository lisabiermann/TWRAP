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
    std::cout << "performance comparison for tree-level potential" << std::endl;

    using vec2 = std::vector<std::vector<double>>;
    using vec3 = std::vector<std::vector<std::vector<double>>>;
    using vec4 = std::vector<std::vector<std::vector<std::vector<double>>>>;

    double value       = 1.2345;
    std::size_t NHiggs = 8;

    auto start_def = std::chrono::steady_clock::now();

    std::vector<double> v                  = std::vector<double>(NHiggs, value);
    std::vector<double> Curvature_Higgs_L1 = std::vector<double>(NHiggs, value);
    std::vector<std::vector<double>> Curvature_Higgs_L2 =
        vec2{NHiggs, std::vector<double>(NHiggs, value)};
    std::vector<std::vector<std::vector<double>>> Curvature_Higgs_L3 =
        vec3{NHiggs, vec2{NHiggs, std::vector<double>(NHiggs, value)}};
    std::vector<std::vector<std::vector<std::vector<double>>>>
        Curvature_Higgs_L4 = vec4{
            NHiggs,
            vec3{NHiggs, vec2{NHiggs, std::vector<double>(NHiggs, value)}}};

    double res_def = 0;

    for (std::size_t i = 0; i < NHiggs; i++)
    {
      if (v[i] != 0)
      {
        res_def += Curvature_Higgs_L1[i] * v[i];
        for (std::size_t j = 0; j < NHiggs; j++)
        {
          if (v[j] != 0)
          {
            res_def += 0.5 * Curvature_Higgs_L2[i][j] * v[i] * v[j];
            for (std::size_t k = 0; k < NHiggs; k++)
            {
              res_def +=
                  1.0 / 6.0 * Curvature_Higgs_L3[i][j][k] * v[i] * v[j] * v[k];
              for (std::size_t l = 0; l < NHiggs; l++)
              {
                res_def += 1.0 / 24.0 * Curvature_Higgs_L4[i][j][k][l] * v[i] *
                           v[j] * v[k] * v[l];
              }
            }
          }
        }
      }
    }

    auto finish_def = std::chrono::steady_clock::now();

    auto start_tens = std::chrono::steady_clock::now();

    WTens<double, 1> v_tens(NHiggs);
    WTens<double, 1> Curvature_Higgs_L1_tens(NHiggs);
    WTens<double, 2> Curvature_Higgs_L2_tens(NHiggs, NHiggs);
    WTens<double, 3> Curvature_Higgs_L3_tens(NHiggs, NHiggs, NHiggs);
    WTens<double, 4> Curvature_Higgs_L4_tens(NHiggs, NHiggs, NHiggs, NHiggs);

    v_tens.setToValue(value);
    Curvature_Higgs_L1_tens.setToValue(value);
    Curvature_Higgs_L2_tens.setToValue(value);
    Curvature_Higgs_L3_tens.setToValue(value);
    Curvature_Higgs_L4_tens.setToValue(value);

    auto res_tens =
        Curvature_Higgs_L1_tens.concat(v_tens, 0, 0) +
        (Curvature_Higgs_L2_tens.concat(v_tens, 1, 0)).concat(v_tens, 0, 0) *
            double(0.5) +
        ((Curvature_Higgs_L3_tens.concat(v_tens, 2, 0)).concat(v_tens, 1, 0))
                .concat(v_tens, 0, 0) *
            double(1.0 / 6.0) +
        (((Curvature_Higgs_L4_tens.concat(v_tens, 3, 0)).concat(v_tens, 2, 0))
             .concat(v_tens, 1, 0))
                .concat(v_tens, 0, 0) *
            double(1.0 / 24.0);

    auto finish_tens = std::chrono::steady_clock::now();

    std::cout << "res default = " << res_def << std::endl;
    std::cout << "res tensor  = " << res_tens << std::endl;

    double elapsed_time_def =
        std::chrono::duration_cast<std::chrono::milliseconds>(finish_def -
                                                              start_def)
            .count();
    double elapsed_time_tens =
        std::chrono::duration_cast<std::chrono::milliseconds>(finish_def -
                                                              start_def)
            .count();
    std::cout << "elapsed time default: " << elapsed_time_def << " ms \n";
    std::cout << "elapsed time tensor : " << elapsed_time_tens << " ms \n";
  }

  catch (TWrapExceptionBase &e)
  {
    e.what();
    exit(EXIT_FAILURE);
  }

  return 0;
}