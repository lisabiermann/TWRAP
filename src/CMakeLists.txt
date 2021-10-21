# SPDX-FileCopyrightText: 2021 Lisa Biermann
#
# SPDX-License-Identifier: GPL-3.0-or-later

set(header_path "${TWRAP_SOURCE_DIR}/include")
set(header
	${header_path}/TWrap.h
)
set(src
    TWrap.cpp
)
add_library(TWRAP ${header} ${src})
target_link_libraries(TWRAP PUBLIC Eigen3::Eigen)
target_compile_features(TWRAP PUBLIC cxx_std_14)

add_executable(example example/example.cpp)
target_link_libraries(example TWRAP)
target_compile_features(example PUBLIC cxx_std_14)