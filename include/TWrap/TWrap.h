// SPDX-FileCopyrightText: 2021 Lisa Biermann
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <TWrap/utility.h>
#include <iostream>
#include <unsupported/Eigen/CXX11/Tensor>

using namespace Eigen;

/**
 * @file
 */
namespace TWrap
{

template <typename InnerType, std::size_t dim> class WTens
{
public:
  Tensor<InnerType, dim> tens;

  /**
   * @brief Constructor with initialization to zero
   */
  template <typename... IndexTypes> WTens(IndexTypes... args) : tens(args...)
  {
    tens.setZero();
  }

  /**
   * @brief Get individual tensor elements
   */
  template <typename... IndexTypes>
  InnerType operator()(IndexTypes... args) const
  {
    return tens(args...);
  }

  /**
   * @brief Set individual tensor elements
   */
  template <typename... IndexTypes> InnerType &operator()(IndexTypes... args)
  {
    return tens(args...);
  }

  /**
   * @brief Set whole tensor to constant
   * @param value value to which all tensor elements should be set
   */
  void setConstant(InnerType value) { this->tens.setConstant(value); }

  /**
   * @brief Set whole tensor to random values
   */
  void setRandom() { this->tens.setRandom(); }

  /**
   * @brief setValues Set tensor elements using nested initializer list
   * @param values initializer_list storing values to be set as tensor entries
   */
  void setValues(std::initializer_list<InnerType> values)
  {
    this->tens.setValues(values);
  }
  void setValues(std::initializer_list<std::initializer_list<InnerType>> values)
  {
    this->tens.setValues(values);
  }
  void
  setValues(std::initializer_list<
            std::initializer_list<std::initializer_list<InnerType>>> values)
  {
    this->tens.setValues(values);
  }

  /**
   * @brief Addition of tensors
   * @param t WTens to be added to class member
   * @return new WTens as sum of two WTens
   */
  WTens operator+(WTens t)
  {
    const auto &d1 = this->tens.dimensions();
    const auto &d2 = t.tens.dimensions();

    if (d1 == d2)
    {
      WTens<InnerType, dim> result;
      result.tens = this->tens + t.tens;
      return result;
    }
    else
      throw std::runtime_error("Trying to add tensors with wrong dimensions!");
  }

  /**
   * @brief Multiplication of tensor by scale
   * @param scale scale
   * @return WTens with every entry multiplied by scale
   */
  WTens operator*(InnerType scale)
  {
    WTens<InnerType, dim> result;
    result.tens = this->tens * scale;
    return result;
  }

  /**
   * @brief get_chip get subtensor at given dimension and offset
   * @param offset offset
   * @param dim_chip dimension
   * @return WTens subtensor
   */
  WTens<InnerType, 1> get_chip(int offset, int dim_chip)
  {
    WTens<InnerType, 1> result;
    result.tens = this->tens.chip(offset, dim_chip);
    return result;
  }

  /**
   * @brief concatND concatenate two tensors at specified indices
   * @param index_first index of first tensor to be concatenated
   * @param index_second index of second tensor to be concatenated
   * @return WTens
   */
  template <std::size_t dimin>
  decltype(auto) concat(WTens<InnerType, dimin> tensor_in,
                        int index_first,
                        int index_second = 0)
  {
    Eigen::array<Eigen::IndexPair<InnerType>, 1> product_dims = {
        Eigen::IndexPair<InnerType>(index_first, index_second)};

    const std::size_t dimout_calc =
        dim + dimin - 2; // two indices are contracted

    WTens<InnerType, dimout_calc> result;
    result.tens = this->tens.contract(tensor_in.tens, product_dims);
    return result;
  }

  /**
   * @brief get_NumDimensions
   * @return Number of dimensions of tensor
   */
  int get_NumDimensions() { return this->tens.NumDimensions; }

  /**
   * @brief get_dimensions
   * @return vector storing the sizes of the dimensions of the tensor
   */
  std::vector<int> get_dimensions()
  {
    std::vector<int> res;
    const auto &d = this->tens.dimensions();
    for (int i = 0; i < int(d.size()); i++)
    {
      res.push_back(d[i]);
    }
    return res;
  }

  /**
   * @brief get_dimensions
   * @return dimension of specified dimension index
   */
  int get_dimensions(int index)
  {
    std::vector<int> res = this->get_dimensions();
    return res[index];
  }

  /**
   * @brief print print tensor
   */
  void print() { std::cout << this->tens << std::endl; }

  /**
   * @brief print_DimOut print information on dimensions of tensor
   */
  void print_DimOut()
  {
    std::cout << "tensor dims = " << this->get_NumDimensions()
              << this->get_dimensions() << std::endl;
  }
};

} // namespace TWrap
