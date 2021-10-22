// SPDX-FileCopyrightText: 2021 Lisa Biermann
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "catch.hpp"
#include <TWrap/TWrap.h>

TEST_CASE("initialization", "[general]")
{
    using namespace TWrap;
    TWrap::TWrap t;
    REQUIRE(t.Dim1 == 1);
    REQUIRE(t.Dim2 == 0);
    REQUIRE(t.Dim3 == 0);
    REQUIRE(t.Dim4 == 0);
}