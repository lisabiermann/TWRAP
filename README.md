# TWrap
TWrap is a C++ wrapper class around the [Eigen3-unsupported Tensor Module](https://eigen.tuxfamily.org/dox/unsupported/group__CXX11__Tensor__Module.html).

It is built via
```
mkdir build && cd build
cmake ..
make
```

A template executable - illustrating some core functionality - is provided and can be executed as
```
cd build
./bin/template
```

Unit tests can be run after compiling using `ctest`.

### How to use TWrap?
- create a tensor
  ```
  WTens<double, 1> myTensor(5);
  ```
  creates a new Tensor with dimension 1 and length 5. You need to give as many length arguments as dimensions, e.g.
  ```
  WTens<int, 4> myTensor4D(1,2,3,4);
  ```
  All its elements are initialized to zero.
   
- set tensor elements

  Individual tensor values are set via
  ```
  myTensor(0) = 1.2;
  ```
  or you can set the whole tensor content using a C++ `initializer_list`
  ```
  myTensor.setValues({1,2,3,4,5});
  ```
  There are also the options to set all values to zero 
  ```
  myTensor.setZero();
  ```
  or to a random value
  ```
  myTensor.setRandom();
  ```
  
- tensor operations
  - addition of tensor
  
  Two tensors are added via
  ```
  auto res = myTensor1 + myTensor2;
  ```
  
  - rescale a tensor with a factor

  By multiplying a tensor with a factor, all its content gets rescaled individually
  ```
  double scale = 2.0;
  auto res = myTensor * scale;
  ```
  
  - tensor multiplication
  Two tensors are multiplied using the `concat` function. You need to specify the indices which will be contracted. Below you see the example for a matix-vector multiplication.
  ```
  WTens<double, 1> vec(2);
  WTens<double, 2> matrix(2, 2);
  vec.setValues({10, 11});
  matrix.setValues({{1, 2}, {3, 4}});

  auto res = matrix.concat(vec, 1, 0);
  auto resT = matrix.concat(vec, 0, 0);
  ```
  `res` is the result for `A * b`, in indices: `A_ij * b_j = c_i`.
  `resT` the result for the product with the transposed vector, `b^T * A`, e.g. `A_ij * b_i = c_j`.
