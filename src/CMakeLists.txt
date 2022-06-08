# SPDX-FileCopyrightText: 2021 Lisa Biermann
#
# SPDX-License-Identifier: GPL-3.0-or-later

set(header_path "${TWrap_SOURCE_DIR}/include")

add_library(TWrap INTERFACE)
target_include_directories(TWrap INTERFACE ${header_path})
target_link_libraries(TWrap INTERFACE Eigen3::Eigen)

add_executable(template template.cpp)
target_link_libraries(template TWrap)
target_compile_features(template PUBLIC cxx_std_14)