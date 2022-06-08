// SPDX-FileCopyrightText: 2021 Lisa Biermann
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <exception>
#include <iostream>

/**
 * @file
 */
namespace TWrap
{

class TWrapExceptionBase : public std::exception
{
private:
  char const *file;
  int line;
  char const *function;
  std::string output;

public:
  TWrapExceptionBase(char const *file_in,
                     int line_in,
                     char const *function_in,
                     std::string output_in = "Base error")
  {
    file     = file_in;
    line     = line_in;
    function = function_in;
    output   = output_in;
  }
  void what()
  {
    std::cout << this->output << " in file " << this->file << " at line "
              << this->line << " for function " << this->function << std::endl;
  }
};

class TWrapInvalidType : public TWrapExceptionBase
{
public:
  TWrapInvalidType(char const *file_in,
                   int line_in,
                   char const *function_in,
                   std::string output_in = "Invalid type")
      : TWrapExceptionBase(file_in, line_in, function_in, output_in)
  {
  }
};

class TWrapInvalidGet : public TWrapExceptionBase
{
public:
  TWrapInvalidGet(char const *file_in,
                  int line_in,
                  char const *function_in,
                  std::string output_in = "Invalid get")
      : TWrapExceptionBase(file_in, line_in, function_in, output_in)
  {
  }
};

class TWrapInvalidSet : public TWrapExceptionBase
{
public:
  TWrapInvalidSet(char const *file_in,
                  int line_in,
                  char const *function_in,
                  std::string output_in = "Invalid set")
      : TWrapExceptionBase(file_in, line_in, function_in, output_in)
  {
  }
};

} // namespace TWrap