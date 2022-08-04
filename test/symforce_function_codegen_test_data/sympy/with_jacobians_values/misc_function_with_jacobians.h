// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     function/FUNCTION.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

#include <Eigen/Dense>

#include <lcmtypes/sym/d_out_t.hpp>
#include <lcmtypes/sym/d_t.hpp>

#include <sym/rot3.h>

namespace sym {

/**
 * This function was autogenerated. Do not modify by hand.
 *
 * Args:
 *     a: Rot3
 *     b: Scalar
 *     c: Matrix51
 *     d: Values
 *
 * Outputs:
 *     a_out: Matrix31
 *     b_out: Scalar
 *     c_out: Matrix12
 *     d_out: Values
 *     a_out_D_a: (3x3) jacobian of a_out (3) wrt arg a (3)
 *     a_out_D_b: (3x1) jacobian of a_out (3) wrt arg b (1)
 *     a_out_D_c: (3x5) jacobian of a_out (3) wrt arg c (5)
 *     a_out_D_d: (3x3) jacobian of a_out (3) wrt arg d (3)
 *     b_out_D_a: (1x3) jacobian of b_out (1) wrt arg a (3)
 *     b_out_D_b: (1x1) jacobian of b_out (1) wrt arg b (1)
 *     b_out_D_c: (1x5) jacobian of b_out (1) wrt arg c (5)
 *     b_out_D_d: (1x3) jacobian of b_out (1) wrt arg d (3)
 *     c_out_D_a: (2x3) jacobian of c_out (2) wrt arg a (3)
 *     c_out_D_b: (2x1) jacobian of c_out (2) wrt arg b (1)
 *     c_out_D_c: (2x5) jacobian of c_out (2) wrt arg c (5)
 *     c_out_D_d: (2x3) jacobian of c_out (2) wrt arg d (3)
 *     d_out_D_a: (2x3) jacobian of d_out (2) wrt arg a (3)
 *     d_out_D_b: (2x1) jacobian of d_out (2) wrt arg b (1)
 *     d_out_D_c: (2x5) jacobian of d_out (2) wrt arg c (5)
 *     d_out_D_d: (2x3) jacobian of d_out (2) wrt arg d (3)
 */
template <typename Scalar>
void MiscFunctionWithJacobians(const sym::Rot3<Scalar>& a, const Scalar b,
                               const Eigen::Matrix<Scalar, 5, 1>& c, const sym::d_t& d,
                               Eigen::Matrix<Scalar, 3, 1>* const a_out = nullptr,
                               Scalar* const b_out = nullptr,
                               Eigen::Matrix<Scalar, 1, 2>* const c_out = nullptr,
                               sym::d_out_t* const d_out = nullptr,
                               Eigen::Matrix<Scalar, 3, 3>* const a_out_D_a = nullptr,
                               Eigen::Matrix<Scalar, 3, 1>* const a_out_D_b = nullptr,
                               Eigen::Matrix<Scalar, 3, 5>* const a_out_D_c = nullptr,
                               Eigen::Matrix<Scalar, 3, 3>* const a_out_D_d = nullptr,
                               Eigen::Matrix<Scalar, 1, 3>* const b_out_D_a = nullptr,
                               Eigen::Matrix<Scalar, 1, 1>* const b_out_D_b = nullptr,
                               Eigen::Matrix<Scalar, 1, 5>* const b_out_D_c = nullptr,
                               Eigen::Matrix<Scalar, 1, 3>* const b_out_D_d = nullptr,
                               Eigen::Matrix<Scalar, 2, 3>* const c_out_D_a = nullptr,
                               Eigen::Matrix<Scalar, 2, 1>* const c_out_D_b = nullptr,
                               Eigen::Matrix<Scalar, 2, 5>* const c_out_D_c = nullptr,
                               Eigen::Matrix<Scalar, 2, 3>* const c_out_D_d = nullptr,
                               Eigen::Matrix<Scalar, 2, 3>* const d_out_D_a = nullptr,
                               Eigen::Matrix<Scalar, 2, 1>* const d_out_D_b = nullptr,
                               Eigen::Matrix<Scalar, 2, 5>* const d_out_D_c = nullptr,
                               Eigen::Matrix<Scalar, 2, 3>* const d_out_D_d = nullptr) {
  // Total ops: 75

  // Input arrays
  const Eigen::Matrix<Scalar, 4, 1>& _a = a.Data();

  // Intermediate terms (15)
  const Scalar _tmp0 = 2 * _a[3];
  const Scalar _tmp1 = _a[1] * _tmp0;
  const Scalar _tmp2 = 2 * _a[2];
  const Scalar _tmp3 = _a[0] * _tmp2 + _tmp1;
  const Scalar _tmp4 = _a[0] * _tmp0;
  const Scalar _tmp5 = _a[1] * _tmp2;
  const Scalar _tmp6 = -_tmp4 + _tmp5;
  const Scalar _tmp7 = std::pow(_a[0], Scalar(2));
  const Scalar _tmp8 = std::pow(_a[1], Scalar(2));
  const Scalar _tmp9 = -2 * _tmp7 - 2 * _tmp8 + 1;
  const Scalar _tmp10 = std::sqrt(Scalar(
      std::pow(c(0, 0), Scalar(2)) + std::pow(c(1, 0), Scalar(2)) + std::pow(c(2, 0), Scalar(2)) +
      std::pow(c(3, 0), Scalar(2)) + std::pow(c(4, 0), Scalar(2))));
  const Scalar _tmp11 = _a[2] * _tmp0;
  const Scalar _tmp12 = 2 * _a[0] * _a[1];
  const Scalar _tmp13 = -std::pow(_a[2], Scalar(2)) + std::pow(_a[3], Scalar(2));
  const Scalar _tmp14 = Scalar(1.0) / (_tmp10);

  // Output terms (20)
  if (a_out != nullptr) {
    Eigen::Matrix<Scalar, 3, 1>& _a_out = (*a_out);

    _a_out(0, 0) = _tmp3 * b;
    _a_out(1, 0) = _tmp6 * b;
    _a_out(2, 0) = _tmp9 * b;
  }

  if (b_out != nullptr) {
    Scalar& _b_out = (*b_out);

    _b_out = _tmp10 + std::pow(b, Scalar(2));
  }

  if (c_out != nullptr) {
    Eigen::Matrix<Scalar, 1, 2>& _c_out = (*c_out);

    _c_out(0, 0) = 4 * d.x + d.y.data[0] + 3 * d.y.data[1];
    _c_out(0, 1) = 6 * d.x + 2 * d.y.data[0] + 4 * d.y.data[1];
  }

  if (d_out != nullptr) {
    sym::d_out_t& _d_out = (*d_out);

    _d_out.x = 3;
    _d_out.y = _a[3] + b;
  }

  if (a_out_D_a != nullptr) {
    Eigen::Matrix<Scalar, 3, 3>& _a_out_D_a = (*a_out_D_a);

    _a_out_D_a(0, 0) = b * (_tmp11 - _tmp12);
    _a_out_D_a(1, 0) = b * (-_tmp13 + _tmp7 - _tmp8);
    _a_out_D_a(2, 0) = b * (-_tmp4 - _tmp5);
    _a_out_D_a(0, 1) = b * (_tmp13 + _tmp7 - _tmp8);
    _a_out_D_a(1, 1) = b * (_tmp11 + _tmp12);
    _a_out_D_a(2, 1) = b * (2 * _a[0] * _a[2] - _tmp1);
    _a_out_D_a(0, 2) = 0;
    _a_out_D_a(1, 2) = 0;
    _a_out_D_a(2, 2) = 0;
  }

  if (a_out_D_b != nullptr) {
    Eigen::Matrix<Scalar, 3, 1>& _a_out_D_b = (*a_out_D_b);

    _a_out_D_b(0, 0) = _tmp3;
    _a_out_D_b(1, 0) = _tmp6;
    _a_out_D_b(2, 0) = _tmp9;
  }

  if (a_out_D_c != nullptr) {
    Eigen::Matrix<Scalar, 3, 5>& _a_out_D_c = (*a_out_D_c);

    _a_out_D_c.setZero();
  }

  if (a_out_D_d != nullptr) {
    Eigen::Matrix<Scalar, 3, 3>& _a_out_D_d = (*a_out_D_d);

    _a_out_D_d.setZero();
  }

  if (b_out_D_a != nullptr) {
    Eigen::Matrix<Scalar, 1, 3>& _b_out_D_a = (*b_out_D_a);

    _b_out_D_a.setZero();
  }

  if (b_out_D_b != nullptr) {
    Eigen::Matrix<Scalar, 1, 1>& _b_out_D_b = (*b_out_D_b);

    _b_out_D_b(0, 0) = 2 * b;
  }

  if (b_out_D_c != nullptr) {
    Eigen::Matrix<Scalar, 1, 5>& _b_out_D_c = (*b_out_D_c);

    _b_out_D_c(0, 0) = _tmp14 * c(0, 0);
    _b_out_D_c(0, 1) = _tmp14 * c(1, 0);
    _b_out_D_c(0, 2) = _tmp14 * c(2, 0);
    _b_out_D_c(0, 3) = _tmp14 * c(3, 0);
    _b_out_D_c(0, 4) = _tmp14 * c(4, 0);
  }

  if (b_out_D_d != nullptr) {
    Eigen::Matrix<Scalar, 1, 3>& _b_out_D_d = (*b_out_D_d);

    _b_out_D_d.setZero();
  }

  if (c_out_D_a != nullptr) {
    Eigen::Matrix<Scalar, 2, 3>& _c_out_D_a = (*c_out_D_a);

    _c_out_D_a.setZero();
  }

  if (c_out_D_b != nullptr) {
    Eigen::Matrix<Scalar, 2, 1>& _c_out_D_b = (*c_out_D_b);

    _c_out_D_b.setZero();
  }

  if (c_out_D_c != nullptr) {
    Eigen::Matrix<Scalar, 2, 5>& _c_out_D_c = (*c_out_D_c);

    _c_out_D_c.setZero();
  }

  if (c_out_D_d != nullptr) {
    Eigen::Matrix<Scalar, 2, 3>& _c_out_D_d = (*c_out_D_d);

    _c_out_D_d(0, 0) = 4;
    _c_out_D_d(1, 0) = 6;
    _c_out_D_d(0, 1) = 1;
    _c_out_D_d(1, 1) = 2;
    _c_out_D_d(0, 2) = 3;
    _c_out_D_d(1, 2) = 4;
  }

  if (d_out_D_a != nullptr) {
    Eigen::Matrix<Scalar, 2, 3>& _d_out_D_a = (*d_out_D_a);

    _d_out_D_a(0, 0) = 0;
    _d_out_D_a(1, 0) = -Scalar(1) / Scalar(2) * _a[0];
    _d_out_D_a(0, 1) = 0;
    _d_out_D_a(1, 1) = -Scalar(1) / Scalar(2) * _a[1];
    _d_out_D_a(0, 2) = 0;
    _d_out_D_a(1, 2) = -Scalar(1) / Scalar(2) * _a[2];
  }

  if (d_out_D_b != nullptr) {
    Eigen::Matrix<Scalar, 2, 1>& _d_out_D_b = (*d_out_D_b);

    _d_out_D_b(0, 0) = 0;
    _d_out_D_b(1, 0) = 1;
  }

  if (d_out_D_c != nullptr) {
    Eigen::Matrix<Scalar, 2, 5>& _d_out_D_c = (*d_out_D_c);

    _d_out_D_c.setZero();
  }

  if (d_out_D_d != nullptr) {
    Eigen::Matrix<Scalar, 2, 3>& _d_out_D_d = (*d_out_D_d);

    _d_out_D_d.setZero();
  }
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym
