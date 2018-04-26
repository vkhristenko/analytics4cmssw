#ifndef execs_test_cuda_eigen_interface_test_eigen_kernels0_h
#define execs_test_cuda_eigen_interface_test_eigen_kernels0_h

#include<Eigen/Core>

int constexpr nrows = 10;
int constexpr ncols = 10;
using Matrix10x10 = Eigen::Matrix<double, nrows, ncols>;

void eigen_vector_add(Eigen::Vector3d*, Eigen::Vector3d*, Eigen::Vector3d*, int const);

void eigen_vector_dot(Eigen::Vector3d*, Eigen::Vector3d*, Eigen::Vector3d::value_type*,
    int const);

void eigen_matrix_add(Matrix10x10*, Matrix10x10*, Matrix10x10*, int const);

void eigen_matrix_tests(Matrix10x10*, Matrix10x10*, int const);

#endif // execs_test_cuda_interface_test_kernels0_h
