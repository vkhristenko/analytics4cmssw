#include <iostream>

#ifdef USE_CUDA
#include "cuda.h"
#include "cuda_runtime.h"
#include "execs/test_cuda_eigen/interface/test_eigen_kernels0.h"
#endif

int main() {
    std::cout << "hello world" << std::endl;

#ifdef USE_CUDA
    int nDevices;
    cudaGetDeviceCount(&nDevices);
    std::cout << "nDevices = " << nDevices << std::endl;

    int constexpr n = 100;
    Eigen::Vector3d a[n], b[n], c[n];
    Eigen::Vector3d *d_a, *d_b, *d_c;

    for (auto i=0; i<n; i++) {
        a[i] << i, i, i;
        b[i] << i, i, i;
    }

    // alloc on the device
    cudaMalloc((void**)&d_a, n * sizeof(Eigen::Vector3d) );
    cudaMalloc((void**)&d_b, n*sizeof(Eigen::Vector3d));
    cudaMalloc((void**)&d_c, n*sizeof(Eigen::Vector3d));

    // transfer to the device
    cudaMemcpy(d_a, a, n*sizeof(Eigen::Vector3d), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, n*sizeof(Eigen::Vector3d), cudaMemcpyHostToDevice);
    
    // run the kernel
    eigen_vector_add(d_a, d_b, d_c, n);

    cudaMemcpy(c, d_c, n*sizeof(Eigen::Vector3d), cudaMemcpyDeviceToHost);

    for (auto i=0; i<n; i++) 
        if (i%10 == 0)
            std::cout << "c[" << i << "]" << std::endl
                << c[i] << std::endl;

    cudaFree( d_a );
    cudaFree( d_a );
    cudaFree( d_a );

#endif // USE_CUDA
}
