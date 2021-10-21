// SPDX-FileCopyrightText: 2021 Lisa Biermann
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <iostream>
#include <TWrap.h>

int main()
{
  TWrap ten1(2);
  std::cout << "ten1 = " << std::endl;
  ten1.write();
  ten1(0) = 1;
  ten1(1) = 2;
  ten1.write();

  TWrap ten2(2);
  std::cout << "ten2 = " << std::endl;
  ten2.write();
  ten2(0) = 4;
  ten2(1) = 5;
  ten2.write();
}