// SPDX-FileCopyrightText: 2021 Lisa Biermann
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "catch.hpp"
#include <TWrap/TWrap.h>

using namespace TWrap;

TEST_CASE("initialization", "[general]")
{
    WTens<double, 3> test(1, 4, 3);
    test(0, 0, 0) = 1.0;
    test(0, 1, 0) = 2.0;
    
    REQUIRE(((test(0, 0, 0) == 1.0) && (test(0, 1, 0) == 2.0)));
}

TEST_CASE("addition of tensors", "[general]")
{
    WTens<double, 2> tens1(2, 2);
    WTens<double, 2> tens2(2, 2);

    tens1(0, 0) = 1.0;
    tens2(0, 0) = 3.3;

    WTens<double, 2> tens3 = tens1 + tens2;

    REQUIRE(tens3(0, 0) == 4.3);
}