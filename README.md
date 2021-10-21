# TWrap
TWrap provides a C++ wrapper class around the Eigen3 Tensor class. Its API enables the creation of tensors of arbitrary size and implements addition and multiplication among them.

### dependencies
In case Eigen3 is not found automatically, it has to be linked via `-D Eigen3_DIR=/pathToEigen3/share/eigen3/cmake`.

### build
TWrap is build using cmake.

    mkdir build && cd build
    cmake (OPTIONS) ..
    make

A doxygen documentation is created running `make doc`.
