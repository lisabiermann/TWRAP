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

TEST_CASE("multiplication by vector", "[general]")
{
  WTens<double, 1> vec(2);
  WTens<double, 2> test(2, 2);

  test.setValues({{1, 2}, {3, 4}});
  vec.setValues({5, 6});

  auto res = test * vec;

  REQUIRE((res(0) == 17.0 && res(1) == 39.0));
}