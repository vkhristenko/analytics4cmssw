// std headers
#include <iostream>
#include <vector>

// opencl c headers

// opencl c++ headers
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#include "cl2.hpp"

const int numElements = 32;

int main(int argc, char ** argv) {
    std::cout << "Hello World :)" << std::endl;

    // Discover number of platforms
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    std::cout << "\nNumber of OpenCL plaforms: " << platforms.size() << std::endl;

    for (std::vector<cl::Platform>::iterator plat = platforms.begin(); 
         plat != platforms.end(); plat++) {
        std::string s;
        plat->getInfo(CL_PLATFORM_NAME, &s);
        std::cout << "Platform: " << s << std::endl;

        plat->getInfo(CL_PLATFORM_VENDOR, &s);
        std::cout << "\tVendor:  " << s << std::endl;

        plat->getInfo(CL_PLATFORM_VERSION, &s);
        std::cout << "\tVersion: " << s << std::endl;

        // Discover number of devices
        std::vector<cl::Device> devices;
        plat->getDevices(CL_DEVICE_TYPE_ALL, &devices);
        std::cout << "\n\tNumber of devices: " << devices.size() << std::endl;

        for (std::vector<cl::Device>::const_iterator dev= devices.begin();
             dev!=devices.end(); dev++) {
            std::cout << "\t-------------------------" << std::endl;

            dev->getInfo(CL_DEVICE_NAME, &s);
            std::cout << "\t\tName: " << s << std::endl;

            dev->getInfo(CL_DEVICE_OPENCL_C_VERSION, &s);
            std::cout << "\t\tVersion: " << s << std::endl;

            int i;
            dev->getInfo(CL_DEVICE_MAX_COMPUTE_UNITS, &i);
            std::cout << "\t\tMax. Compute Units: " << i << std::endl;

            size_t size;
            dev->getInfo(CL_DEVICE_LOCAL_MEM_SIZE, &size);
            std::cout << "\t\tLocal Memory Size: " << size/1024 << " KB" << std::endl;

            dev->getInfo(CL_DEVICE_GLOBAL_MEM_SIZE, &size);
            std::cout << "\t\tGlobal Memory Size: " << size/(1024*1024) << " MB" << std::endl;

            dev->getInfo(CL_DEVICE_MAX_MEM_ALLOC_SIZE, &size);
            std::cout << "\t\tMax Alloc Size: " << size/(1024*1024) << " MB" << std::endl;

            dev->getInfo(CL_DEVICE_MAX_WORK_GROUP_SIZE, &size);
            std::cout << "\t\tMax Work-group Total Size: " << size << std::endl;

            std::vector<size_t> d;
            dev->getInfo(CL_DEVICE_MAX_WORK_ITEM_SIZES, &d);
            std::cout << "\t\tMax Work-group Dims: (";
            for (std::vector<size_t>::iterator st = d.begin(); st != d.end(); st++)
                std::cout << *st << " ";
            std::cout << "\x08)" << std::endl;

            std::cout << "\t-------------------------" << std::endl;
        }
    }
}
