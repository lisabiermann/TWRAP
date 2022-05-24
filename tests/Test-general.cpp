// SPDX-FileCopyrightText: 2021 Lisa Biermann
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "catch.hpp"
#include <TWrap/TWrap.h>

using namespace TWrap;

TEST_CASE("initialization", "[general]")
{
  WTens<double, 1> test(1);
  REQUIRE((test(0) == 0.0 && test(1) == 0.0));
}

TEST_CASE("value access", "[general]")
{
  WTens<double, 1> test(5);
  test.setValues({1, 2, 3, 4, 5});

  REQUIRE(((test(0) == 1.0) && (test(1) == 2.0) && (test(2) == 3.0) &&
           (test(3) == 4.0) && (test(4) == 5.0)));
}

TEST_CASE("addition of tensors", "[general]")
{
  WTens<double, 2> test1(2, 2);
  WTens<double, 2> test2(2, 2);

  test1(0, 0) = 1.0;
  test2(0, 0) = 3.3;

  auto test3 = test1 + test2;

  REQUIRE(test3(0, 0) == 4.3);
}

TEST_CASE("multiplication by scalar", "[general]")
{
  WTens<double, 1> test(4);
  test(0)      = 50.0;
  double scale = 2.0;

  auto res = test * scale;

  REQUIRE(res(0) == 100.0);
}

TEST_CASE("multiplication of 2D tensor by vector", "[general]")
{
  WTens<double, 1> vec(2);
  WTens<double, 2> test2D(2, 2);
  vec.setValues({10, 11});
  test2D.setValues({{1, 2}, {3, 4}});

  auto res = test2D.concat(vec, 1, 0);

  REQUIRE((res(0) == 32.0 && res(1) == 74.0));
}

TEST_CASE("multiplication of 3D tensor by vector", "[general]")
{
  WTens<double, 1> vec(3);
  WTens<double, 3> test3D(3, 2, 3);

  test3D.setValues({{{1, 2, 3}, {4, 5, 6}},
                  {{3, 4, 5}, {6, 7, 8}},
                  {{6, 7, 8}, {9, 10, 11}}});
  vec.setValues({10, 11, 12});

  auto res = test3D.concat(vec, 2, 0);

  REQUIRE((res(0, 0) == 68.0 && res(0, 1) == 167.0 && res(1, 0) == 134.0 &&
           res(1, 1) == 233.0 && res(2, 0) == 233.0 && res(2, 1) == 332.0));
}

TEST_CASE("multiplication of two tensors", "[general]")
{
  WTens<double, 2> tens1(2, 3);
  WTens<double, 2> tens2(3, 2);

  tens1.setValues({{1, 2, 3}, {6, 5, 4}});
  tens2.setValues({{1, 2}, {4, 5}, {5, 6}});

  auto res = tens1.concat(tens2, 1, 0);

  REQUIRE((res(0, 0) == 24.0 && res(1, 1) == 61.0));
}