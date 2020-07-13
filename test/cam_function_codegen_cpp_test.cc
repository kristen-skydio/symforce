//  -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
//
// Instead modify:
//     symforce/codegen/cpp/templates/cam_package/example/cam_function_codegen_cpp_test.cc.cc.jinja
//
// And then run `symforce_function_codegen_test --update`.
// -----------------------------------------------------------------------------
/**
 * Tests for generated functions that accept C++ camera types as arguments. Mostly testing that everything
 * compiles.
 */

#include <iostream>
#include <Eigen/Dense>

// TODO(nathan): We just test linear camera for now, but could/should test other types in the future
#include <cam/linear_camera_cal.h>
#include "./symforce_function_codegen_test_data/pixel_to_ray_and_back.h"

// TODO(hayk): Use the catch unit testing framework (single header).
#define assertTrue(a)                                      \
  if (!(a)) {                                              \
    std::ostringstream o;                                  \
    o << __FILE__ << ":" << __LINE__ << ": Test failure."; \
    throw std::runtime_error(o.str());                     \
  }

template <typename T>
void TestGeneratedFunction() {
  using Scalar = typename T::Scalar;
  Scalar epsilon = 1e-6; // For preventing degenerate numerical cases (e.g. division by zero)
  Scalar tolerance = 10.0 * epsilon; // For assessing approximate equality

  Eigen::Matrix<Scalar, geo::StorageOps<T>::StorageDim(), 1> data;
  std::mt19937 gen(42);
  std::uniform_real_distribution<Scalar> cam_dist(100.0, 500.0);
  for (int i = 0; i < geo::StorageOps<T>::StorageDim(); i++) {
    data[i] = cam_dist(gen);
  }
  T cam(data);
  std::cout << "*** Testing generated function with " << cam << " ***" << std::endl;

  int is_valid;

  Eigen::Matrix<Scalar, 2, 1> pixel_coords;
  pixel_coords << 2.0 * cam_dist(gen), 2.0 * cam_dist(gen);
  Eigen::Matrix<Scalar, 2, 1> pixel_coords_reprojected = symforce::PixelToRayAndBack<Scalar>(pixel_coords, cam, epsilon);
  assertTrue(pixel_coords.isApprox(pixel_coords_reprojected, epsilon));
}

int main(int argc, char** argv) {
  TestGeneratedFunction<cam::LinearCameraCal<double>>();
  TestGeneratedFunction<cam::LinearCameraCal<float>>();
}
