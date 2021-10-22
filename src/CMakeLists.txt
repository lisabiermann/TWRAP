# SPDX-FileCopyrightText: 2021 Lisa Biermann
#
# SPDX-License-Identifier: GPL-3.0-or-later

set(header_path "${TWrap_SOURCE_DIR}/include/TWrap")
set(header
	${header_path}/TWrap.h
)

set(src
    TWrap.cpp
)

add_library(TWrap ${header} ${src})
target_link_libraries(TWrap PUBLIC Eigen3::Eigen)
target_include_directories(TWrap PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_features(TWrap PUBLIC cxx_std_14)