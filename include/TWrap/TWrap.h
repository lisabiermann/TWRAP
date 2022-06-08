// SPDX-FileCopyrightText: 2021 Lisa Biermann
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <TWrap/utility.h>

/**
 * @file
 */
namespace TWrap
{

template <typename InnerType, std::size_t dim> class WTens
{
public:
  Eigen::Tensor<InnerType, dim> tens;

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
   * @brief Set whole tensor to value
   * @param value value to which all tensor elements should be set
   */
  void setToValue(const InnerType value) { this->tens.setConstant(value); }

  /**
   * @brief Set whole tensor to random values
   */
  void setRandom() { this->tens.setRandom(); }

  /**
   * @brief setValues Set tensor elements using nested initializer list
   * @param values initializer_list storing values to be set as tensor entries
   */
  void setValues(const std::initializer_list<InnerType> values)
  {
    this->tens.setValues(values);
  }
  void setValues(
      const std::initializer_list<std::initializer_list<InnerType>> values)
  {
    this->tens.setValues(values);
  }
  void
  setValues(const std::initializer_list<
            std::initializer_list<std::initializer_list<InnerType>>> values)
  {
    this->tens.setValues(values);
  }

  /**
   * @brief overload of << operator for WTens
   */
  friend std::ostream &operator<<(std::ostream &out, const WTens &t)
  {
    return out << t.tens;
  }

  /**
   * @brief Addition of tensors
   * @param t WTens to be added to class member
   * @return new WTens as sum of two WTens
   */
  template <std::size_t dimin> WTens operator+(WTens<InnerType, dimin> t)
  {
    bool wrong_dimensions =
        (dim != dimin) or (this->get_dimensions() != t.get_dimensions());

    if (wrong_dimensions)
    {
      std::string msg = "Wrong dimensions in addition";
      throw TWrapInvalidType(__FILE__, __LINE__, __func__, msg);
    }
    else
    {
      WTens<InnerType, dim> result;
      result.tens = this->tens + t.tens;
      return result;
    }
  }

  /**
   * @brief Multiplication of tensor by scale
   * @param scale scale
   * @return WTens with every entry multiplied by scale
   */
  WTens operator*(const InnerType scale)
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
  WTens<InnerType, 1> get_chip(const int offset, const int dim_chip)
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
                        const std::size_t index_first,
                        const std::size_t index_second = 0)
  {
    bool index_out_of_range =
        (dim < index_first + 1) || (dimin < index_second + 1);

    if (index_out_of_range)
    {
      std::string msg = "Index out of range";
      throw TWrapInvalidGet(__FILE__, __LINE__, __func__, msg);
    }
    else
    {
      Eigen::array<Eigen::IndexPair<InnerType>, 1> product_dims = {
          Eigen::IndexPair<InnerType>(index_first, index_second)};

      const std::size_t dimout_calc =
          dim + dimin - 2; // two indices are contracted

      WTens<InnerType, dimout_calc> result;
      result.tens = this->tens.contract(tensor_in.tens, product_dims);
      return result;
    }
  }

  /**
   * @brief get_NumDimensions
   * @return Number of dimensions of tensor
   */
  int get_NumDimensions() const { return this->tens.NumDimensions; }

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
  int get_dimensions(const int index) const
  {
    bool index_out_of_range = (this->get_NumDimensions() < index + 1);

    if (index_out_of_range)
    {
      std::string msg = "Index out of range";
      throw TWrapInvalidGet(__FILE__, __LINE__, __func__, msg);
    }
    else
    {
      std::vector<int> res = this->get_dimensions();
      return res[index];
    }
  }

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
