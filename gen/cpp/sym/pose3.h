// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     geo_package/CLASS.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

#include <ostream>
#include <random>
#include <vector>

#include <Eigen/Dense>

#include "./ops/group_ops.h"
#include "./ops/lie_group_ops.h"
#include "./ops/storage_ops.h"
#include "./rot3.h"
#include "./util/epsilon.h"

namespace sym {

/**
 * Autogenerated C++ implementation of <class 'symforce.geo.pose3.Pose3'>.
 *
 * Group of three-dimensional rigid body transformations - SO(3) x R3.
 *
 * The storage is a quaternion (x, y, z, w) for rotation followed by position (x, y, z).
 *
 * The tangent space is 3 elements for rotation followed by 3 elements for translation in the
 * non-rotated frame.
 *
 * For Lie group enthusiasts: This class is on the PRODUCT manifold, if you really really want
 * SE(3) you should use Pose3_SE3.  On this class, the group operations (e.g. compose and between)
 * operate as you'd expect for a Pose or SE(3), but the manifold operations (e.g. retract and
 * local_coordinates) operate on the product manifold SO(3) x R3.  This means that:
 *
 *   - retract(a, vec) != compose(a, from_tangent(vec))
 *
 *   - local_coordinates(a, b) != to_tangent(between(a, b))
 *
 *   - There is no hat operator, because from_tangent/to_tangent is not the matrix exp/log
 */
template <typename ScalarType>
class Pose3 {
 public:
  // Typedefs
  using Scalar = ScalarType;
  using Self = Pose3<Scalar>;
  using DataVec = Eigen::Matrix<Scalar, 7, 1>;
  using TangentVec = Eigen::Matrix<Scalar, 6, 1>;
  using SelfJacobian = Eigen::Matrix<Scalar, 6, 6>;

  // Construct from data vec
  explicit Pose3(const DataVec& data) : data_(data) {}

  // Default construct to identity
  Pose3() : Pose3(GroupOps<Self>::Identity()) {}

  // Access underlying storage as const
  inline const DataVec& Data() const {
    return data_;
  }

  // Matrix type aliases
  using Vector3 = Eigen::Matrix<Scalar, 3, 1>;

  // --------------------------------------------------------------------------
  // Handwritten methods included from "custom_methods/pose3.h.jinja"
  // --------------------------------------------------------------------------

  template <typename Derived>
  Pose3(const Rot3<Scalar>& rotation, const Eigen::MatrixBase<Derived>& position) {
    static_assert(Derived::RowsAtCompileTime == 3, "Position must be a 3x1 vector");
    static_assert(Derived::ColsAtCompileTime == 1, "Position must be a 3x1 vector");
    data_.template head<4>() = rotation.Data();
    data_.template tail<3>() = position;
  }

  Rot3<Scalar> Rotation() const {
    return Rot3<Scalar>(data_.template head<4>());
  }

  Vector3 Position() const {
    return data_.template tail<3>();
  }

  // Generate a random element, with normally distributed position
  template <typename Generator>
  static Pose3 Random(Generator& gen) {
    // This cannot be combined into Pose3(Rot3::Random(gen), sym::StorageOps::Random(gen)),
    // because the standard does not guarantee evaluation order of arguments,
    // meaning that we would get different results on different compilers.
    const auto rot3 = Rot3<Scalar>::Random(gen);
    const auto vec3 = sym::StorageOps<Vector3>::Random(gen);
    return Pose3(rot3, vec3);
  }

  // --------------------------------------------------------------------------
  // Custom generated methods
  // --------------------------------------------------------------------------

  Vector3 Compose(const Vector3& right) const;

  Vector3 InverseCompose(const Vector3& point) const;

  // --------------------------------------------------------------------------
  // StorageOps concept
  // --------------------------------------------------------------------------

  static constexpr int32_t StorageDim() {
    return StorageOps<Self>::StorageDim();
  }

  void ToStorage(Scalar* const vec) const {
    return StorageOps<Self>::ToStorage(*this, vec);
  }

  static Pose3 FromStorage(const Scalar* const vec) {
    return StorageOps<Self>::FromStorage(vec);
  }

  // --------------------------------------------------------------------------
  // GroupOps concept
  // --------------------------------------------------------------------------

  static Self Identity() {
    return GroupOps<Self>::Identity();
  }

  Self Inverse() const {
    return GroupOps<Self>::Inverse(*this);
  }

  Self Compose(const Self& b) const {
    return GroupOps<Self>::Compose(*this, b);
  }

  Self Between(const Self& b) const {
    return GroupOps<Self>::Between(*this, b);
  }

  Self InverseWithJacobian(SelfJacobian* const res_D_a = nullptr) const {
    return GroupOps<Self>::InverseWithJacobian(*this, res_D_a);
  }

  Self ComposeWithJacobians(const Self& b, SelfJacobian* const res_D_a = nullptr,
                            SelfJacobian* const res_D_b = nullptr) const {
    return GroupOps<Self>::ComposeWithJacobians(*this, b, res_D_a, res_D_b);
  }

  Self BetweenWithJacobians(const Self& b, SelfJacobian* const res_D_a = nullptr,
                            SelfJacobian* const res_D_b = nullptr) const {
    return GroupOps<Self>::BetweenWithJacobians(*this, b, res_D_a, res_D_b);
  }

  // Compose shorthand
  template <typename Other>
  auto operator*(const Other& b) const -> decltype(Compose(b)) {
    return Compose(b);
  }

  // --------------------------------------------------------------------------
  // LieGroupOps concept
  // --------------------------------------------------------------------------

  static constexpr int32_t TangentDim() {
    return LieGroupOps<Self>::TangentDim();
  }

  static Self FromTangent(const TangentVec& vec, const Scalar epsilon = kDefaultEpsilon<Scalar>) {
    return LieGroupOps<Self>::FromTangent(vec, epsilon);
  }

  TangentVec ToTangent(const Scalar epsilon = kDefaultEpsilon<Scalar>) const {
    return LieGroupOps<Self>::ToTangent(*this, epsilon);
  }

  Self Retract(const TangentVec& vec, const Scalar epsilon = kDefaultEpsilon<Scalar>) const {
    return LieGroupOps<Self>::Retract(*this, vec, epsilon);
  }

  TangentVec LocalCoordinates(const Self& b, const Scalar epsilon = kDefaultEpsilon<Scalar>) const {
    return LieGroupOps<Self>::LocalCoordinates(*this, b, epsilon);
  }

  // --------------------------------------------------------------------------
  // General Helpers
  // --------------------------------------------------------------------------

  bool IsApprox(const Self& b, const Scalar tol) const {
    // isApprox is multiplicative so we check the norm for the exact zero case
    // https://eigen.tuxfamily.org/dox/classEigen_1_1DenseBase.html#ae8443357b808cd393be1b51974213f9c
    if (b.Data() == DataVec::Zero()) {
      return Data().norm() < tol;
    }

    return Data().isApprox(b.Data(), tol);
  }

  template <typename ToScalar>
  Pose3<ToScalar> Cast() const {
    return Pose3<ToScalar>(Data().template cast<ToScalar>());
  }

  bool operator==(const Pose3& rhs) const {
    return data_ == rhs.Data();
  }

 protected:
  DataVec data_;
};

// Shorthand for scalar types
using Pose3d = Pose3<double>;
using Pose3f = Pose3<float>;

// Print definitions
std::ostream& operator<<(std::ostream& os, const Pose3<double>& a);
std::ostream& operator<<(std::ostream& os, const Pose3<float>& a);

}  // namespace sym

// Externs to reduce duplicate instantiation
extern template class sym::Pose3<double>;
extern template class sym::Pose3<float>;

// Concept implementations for this class
#include "./ops/pose3/group_ops.h"
#include "./ops/pose3/lie_group_ops.h"
#include "./ops/pose3/storage_ops.h"
