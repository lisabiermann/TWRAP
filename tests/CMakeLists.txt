# SPDX-FileCopyrightText: 2021 Lisa Biermann
#
# SPDX-License-Identifier: GPL-3.0-or-later

add_library(Catch catch.cpp)
target_link_libraries(Catch TWrap)
target_include_directories(Catch INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(Catch PUBLIC cxx_std_14)

set(TESTDIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCE_FILES "Test-*.cpp" CONFIURE_DEPENDS)
add_executable(GenericTests ${SOURCE_FILES})
target_link_libraries(GenericTests Catch)
target_compile_features(GenericTests PUBLIC cxx_std_14)

include(Catch)
catch_discover_tests(GenericTests)
