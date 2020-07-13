//  ----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------

#include <algorithm>
#include <cmath>

#include "./lie_group_ops.h"

namespace geo {
namespace pose3 {

template <typename Scalar>
geo::Pose3<Scalar> LieGroupOps<Scalar>::FromTangent(const Eigen::Matrix<Scalar, 6, 1>& vec, const Scalar epsilon) {
    // Input arrays

    // Intermediate terms (19)
    const Scalar _tmp0 = (vec[0] * vec[0]);
    const Scalar _tmp1 = (vec[1] * vec[1]);
    const Scalar _tmp2 = (vec[2] * vec[2]);
    const Scalar _tmp3 = _tmp0 + _tmp1 + _tmp2 + (epsilon * epsilon);
    const Scalar _tmp4 = std::sqrt(_tmp3);
    const Scalar _tmp5 = (1.0/2.0)*_tmp4;
    const Scalar _tmp6 = std::sin(_tmp5)/_tmp4;
    const Scalar _tmp7 = -_tmp2;
    const Scalar _tmp8 = -_tmp1;
    const Scalar _tmp9 = (_tmp4 - std::sin(_tmp4))/(_tmp3 * std::sqrt(_tmp3));
    const Scalar _tmp10 = (-std::cos(_tmp4) + 1)/_tmp3;
    const Scalar _tmp11 = _tmp10*vec[2];
    const Scalar _tmp12 = _tmp9*vec[0];
    const Scalar _tmp13 = _tmp12*vec[1];
    const Scalar _tmp14 = _tmp10*vec[1];
    const Scalar _tmp15 = _tmp12*vec[2];
    const Scalar _tmp16 = -_tmp0;
    const Scalar _tmp17 = _tmp10*vec[0];
    const Scalar _tmp18 = _tmp9*vec[1]*vec[2];

    // Output terms (1)
    Eigen::Matrix<Scalar, 7, 1> _res;
    _res[0] = _tmp6*vec[0];
    _res[1] = _tmp6*vec[1];
    _res[2] = _tmp6*vec[2];
    _res[3] = std::cos(_tmp5);
    _res[4] = vec[3]*(_tmp9*(_tmp7 + _tmp8) + 1) + vec[4]*(-_tmp11 + _tmp13) + vec[5]*(_tmp14 + _tmp15);
    _res[5] = vec[3]*(_tmp11 + _tmp13) + vec[4]*(_tmp9*(_tmp16 + _tmp7) + 1) + vec[5]*(-_tmp17 + _tmp18);
    _res[6] = vec[3]*(-_tmp14 + _tmp15) + vec[4]*(_tmp17 + _tmp18) + vec[5]*(_tmp9*(_tmp16 + _tmp8) + 1);

    return geo::Pose3<Scalar>(_res);
}

template <typename Scalar>
Eigen::Matrix<Scalar, 6, 1> LieGroupOps<Scalar>::ToTangent(const geo::Pose3<Scalar>& a, const Scalar epsilon) {
    // Input arrays
    const Eigen::Matrix<Scalar, 7, 1>& _a = a.Data();

    // Intermediate terms (23)
    const Scalar _tmp0 = std::acos(std::max<Scalar>(epsilon - 1, std::min<Scalar>(_a[3], -epsilon + 1)));
    const Scalar _tmp1 = std::max<Scalar>(epsilon, -(_a[3] * _a[3]) + 1);
    const Scalar _tmp2 = _tmp0/std::sqrt(_tmp1);
    const Scalar _tmp3 = 2*_tmp2;
    const Scalar _tmp4 = 4*(_tmp0 * _tmp0)/_tmp1;
    const Scalar _tmp5 = (_a[2] * _a[2])*_tmp4;
    const Scalar _tmp6 = -_tmp5;
    const Scalar _tmp7 = (_a[1] * _a[1])*_tmp4;
    const Scalar _tmp8 = -_tmp7;
    const Scalar _tmp9 = (_a[0] * _a[0])*_tmp4;
    const Scalar _tmp10 = _tmp5 + _tmp7 + _tmp9 + epsilon;
    const Scalar _tmp11 = std::sqrt(_tmp10);
    const Scalar _tmp12 = 0.5*_tmp11;
    const Scalar _tmp13 = (-1.0/2.0*_tmp11*std::cos(_tmp12)/std::sin(_tmp12) + 1)/_tmp10;
    const Scalar _tmp14 = 1.0*_tmp2;
    const Scalar _tmp15 = _a[2]*_tmp14;
    const Scalar _tmp16 = _a[1]*_tmp13*_tmp4;
    const Scalar _tmp17 = _a[0]*_tmp16;
    const Scalar _tmp18 = _a[1]*_tmp14;
    const Scalar _tmp19 = _a[0]*_a[2]*_tmp13*_tmp4;
    const Scalar _tmp20 = -_tmp9;
    const Scalar _tmp21 = _a[0]*_tmp14;
    const Scalar _tmp22 = _a[2]*_tmp16;

    // Output terms (1)
    Eigen::Matrix<Scalar, 6, 1> _res;
    _res(0, 0) = _a[0]*_tmp3;
    _res(1, 0) = _a[1]*_tmp3;
    _res(2, 0) = _a[2]*_tmp3;
    _res(3, 0) = _a[4]*(_tmp13*(_tmp6 + _tmp8) + 1.0) + _a[5]*(_tmp15 + _tmp17) + _a[6]*(-_tmp18 + _tmp19);
    _res(4, 0) = _a[4]*(-_tmp15 + _tmp17) + _a[5]*(_tmp13*(_tmp20 + _tmp6) + 1.0) + _a[6]*(_tmp21 + _tmp22);
    _res(5, 0) = _a[4]*(_tmp18 + _tmp19) + _a[5]*(-_tmp21 + _tmp22) + _a[6]*(_tmp13*(_tmp20 + _tmp8) + 1.0);

    return _res;
}

template <typename Scalar>
geo::Pose3<Scalar> LieGroupOps<Scalar>::Retract(const geo::Pose3<Scalar>& a, const Eigen::Matrix<Scalar, 6, 1>& vec, const Scalar epsilon) {
    // Input arrays
    const Eigen::Matrix<Scalar, 7, 1>& _a = a.Data();

    // Intermediate terms (39)
    const Scalar _tmp0 = (vec[0] * vec[0]);
    const Scalar _tmp1 = (vec[1] * vec[1]);
    const Scalar _tmp2 = (vec[2] * vec[2]);
    const Scalar _tmp3 = _tmp0 + _tmp1 + _tmp2 + (epsilon * epsilon);
    const Scalar _tmp4 = std::sqrt(_tmp3);
    const Scalar _tmp5 = (1.0/2.0)*_tmp4;
    const Scalar _tmp6 = std::sin(_tmp5)/_tmp4;
    const Scalar _tmp7 = _tmp6*vec[0];
    const Scalar _tmp8 = std::cos(_tmp5);
    const Scalar _tmp9 = _tmp6*vec[1];
    const Scalar _tmp10 = _tmp6*vec[2];
    const Scalar _tmp11 = _a[3]*_tmp6;
    const Scalar _tmp12 = _a[0]*_tmp6;
    const Scalar _tmp13 = 2*_a[0]*_a[1];
    const Scalar _tmp14 = 2*_a[2];
    const Scalar _tmp15 = _a[3]*_tmp14;
    const Scalar _tmp16 = (-std::cos(_tmp4) + 1)/_tmp3;
    const Scalar _tmp17 = _tmp16*vec[2];
    const Scalar _tmp18 = (_tmp4 - std::sin(_tmp4))/(_tmp3 * std::sqrt(_tmp3));
    const Scalar _tmp19 = _tmp18*vec[0];
    const Scalar _tmp20 = _tmp19*vec[1];
    const Scalar _tmp21 = -_tmp2;
    const Scalar _tmp22 = -_tmp0;
    const Scalar _tmp23 = _tmp16*vec[0];
    const Scalar _tmp24 = _tmp18*vec[1]*vec[2];
    const Scalar _tmp25 = vec[3]*(_tmp17 + _tmp20) + vec[4]*(_tmp18*(_tmp21 + _tmp22) + 1) + vec[5]*(-_tmp23 + _tmp24);
    const Scalar _tmp26 = -2*(_a[1] * _a[1]);
    const Scalar _tmp27 = -2*(_a[2] * _a[2]) + 1;
    const Scalar _tmp28 = -_tmp1;
    const Scalar _tmp29 = _tmp16*vec[1];
    const Scalar _tmp30 = _tmp19*vec[2];
    const Scalar _tmp31 = vec[3]*(_tmp18*(_tmp21 + _tmp28) + 1) + vec[4]*(-_tmp17 + _tmp20) + vec[5]*(_tmp29 + _tmp30);
    const Scalar _tmp32 = _a[0]*_tmp14;
    const Scalar _tmp33 = 2*_a[3];
    const Scalar _tmp34 = _a[1]*_tmp33;
    const Scalar _tmp35 = vec[3]*(-_tmp29 + _tmp30) + vec[4]*(_tmp23 + _tmp24) + vec[5]*(_tmp18*(_tmp22 + _tmp28) + 1);
    const Scalar _tmp36 = -2*(_a[0] * _a[0]);
    const Scalar _tmp37 = _a[1]*_tmp14;
    const Scalar _tmp38 = _a[0]*_tmp33;

    // Output terms (1)
    Eigen::Matrix<Scalar, 7, 1> _res;
    _res[0] = _a[0]*_tmp8 + _a[1]*_tmp10 - _a[2]*_tmp9 + _a[3]*_tmp7;
    _res[1] = _a[1]*_tmp8 + _a[2]*_tmp7 + _tmp11*vec[1] - _tmp12*vec[2];
    _res[2] = -_a[1]*_tmp7 + _a[2]*_tmp8 + _tmp11*vec[2] + _tmp12*vec[1];
    _res[3] = -_a[1]*_tmp9 - _a[2]*_tmp10 + _a[3]*_tmp8 - _tmp12*vec[0];
    _res[4] = _a[4] + _tmp25*(_tmp13 - _tmp15) + _tmp31*(_tmp26 + _tmp27) + _tmp35*(_tmp32 + _tmp34);
    _res[5] = _a[5] + _tmp25*(_tmp27 + _tmp36) + _tmp31*(_tmp13 + _tmp15) + _tmp35*(_tmp37 - _tmp38);
    _res[6] = _a[6] + _tmp25*(_tmp37 + _tmp38) + _tmp31*(_tmp32 - _tmp34) + _tmp35*(_tmp26 + _tmp36 + 1);

    return geo::Pose3<Scalar>(_res);
}

template <typename Scalar>
Eigen::Matrix<Scalar, 6, 1> LieGroupOps<Scalar>::LocalCoordinates(const geo::Pose3<Scalar>& a, const geo::Pose3<Scalar>& b, const Scalar epsilon) {
    // Input arrays
    const Eigen::Matrix<Scalar, 7, 1>& _a = a.Data();
    const Eigen::Matrix<Scalar, 7, 1>& _b = b.Data();

    // Intermediate terms (50)
    const Scalar _tmp0 = -_a[0]*_b[3] - _a[1]*_b[2] + _a[2]*_b[1] + _a[3]*_b[0];
    const Scalar _tmp1 = _a[0]*_b[0] + _a[1]*_b[1] + _a[2]*_b[2] + _a[3]*_b[3];
    const Scalar _tmp2 = std::acos(std::max<Scalar>(epsilon - 1, std::min<Scalar>(_tmp1, -epsilon + 1)));
    const Scalar _tmp3 = std::max<Scalar>(epsilon, -(_tmp1 * _tmp1) + 1);
    const Scalar _tmp4 = _tmp2/std::sqrt(_tmp3);
    const Scalar _tmp5 = 2*_tmp4;
    const Scalar _tmp6 = _a[0]*_b[2] - _a[1]*_b[3] - _a[2]*_b[0] + _a[3]*_b[1];
    const Scalar _tmp7 = -_a[0]*_b[1] + _a[1]*_b[0] - _a[2]*_b[3] + _a[3]*_b[2];
    const Scalar _tmp8 = 4*(_tmp2 * _tmp2)/_tmp3;
    const Scalar _tmp9 = (_tmp7 * _tmp7)*_tmp8;
    const Scalar _tmp10 = -_tmp9;
    const Scalar _tmp11 = (_tmp6 * _tmp6)*_tmp8;
    const Scalar _tmp12 = -_tmp11;
    const Scalar _tmp13 = (_tmp0 * _tmp0)*_tmp8;
    const Scalar _tmp14 = _tmp11 + _tmp13 + _tmp9 + epsilon;
    const Scalar _tmp15 = std::sqrt(_tmp14);
    const Scalar _tmp16 = 0.5*_tmp15;
    const Scalar _tmp17 = (-1.0/2.0*_tmp15*std::cos(_tmp16)/std::sin(_tmp16) + 1)/_tmp14;
    const Scalar _tmp18 = -2*(_a[2] * _a[2]);
    const Scalar _tmp19 = -2*(_a[1] * _a[1]) + 1;
    const Scalar _tmp20 = _tmp18 + _tmp19;
    const Scalar _tmp21 = 2*_a[0]*_a[1];
    const Scalar _tmp22 = 2*_a[2];
    const Scalar _tmp23 = _a[3]*_tmp22;
    const Scalar _tmp24 = _tmp21 + _tmp23;
    const Scalar _tmp25 = _a[0]*_tmp22;
    const Scalar _tmp26 = 2*_a[3];
    const Scalar _tmp27 = _a[1]*_tmp26;
    const Scalar _tmp28 = _tmp25 - _tmp27;
    const Scalar _tmp29 = -_a[4]*_tmp20 - _a[5]*_tmp24 - _a[6]*_tmp28 + _b[4]*_tmp20 + _b[5]*_tmp24 + _b[6]*_tmp28;
    const Scalar _tmp30 = 1.0*_tmp4;
    const Scalar _tmp31 = _tmp30*_tmp7;
    const Scalar _tmp32 = _tmp0*_tmp17*_tmp8;
    const Scalar _tmp33 = _tmp32*_tmp6;
    const Scalar _tmp34 = _tmp21 - _tmp23;
    const Scalar _tmp35 = -2*(_a[0] * _a[0]);
    const Scalar _tmp36 = _tmp18 + _tmp35 + 1;
    const Scalar _tmp37 = _a[1]*_tmp22;
    const Scalar _tmp38 = _a[0]*_tmp26;
    const Scalar _tmp39 = _tmp37 + _tmp38;
    const Scalar _tmp40 = -_a[4]*_tmp34 - _a[5]*_tmp36 - _a[6]*_tmp39 + _b[4]*_tmp34 + _b[5]*_tmp36 + _b[6]*_tmp39;
    const Scalar _tmp41 = _tmp30*_tmp6;
    const Scalar _tmp42 = _tmp32*_tmp7;
    const Scalar _tmp43 = _tmp19 + _tmp35;
    const Scalar _tmp44 = _tmp25 + _tmp27;
    const Scalar _tmp45 = _tmp37 - _tmp38;
    const Scalar _tmp46 = -_a[4]*_tmp44 - _a[5]*_tmp45 - _a[6]*_tmp43 + _b[4]*_tmp44 + _b[5]*_tmp45 + _b[6]*_tmp43;
    const Scalar _tmp47 = -_tmp13;
    const Scalar _tmp48 = _tmp0*_tmp30;
    const Scalar _tmp49 = _tmp17*_tmp6*_tmp7*_tmp8;

    // Output terms (1)
    Eigen::Matrix<Scalar, 6, 1> _res;
    _res(0, 0) = _tmp0*_tmp5;
    _res(1, 0) = _tmp5*_tmp6;
    _res(2, 0) = _tmp5*_tmp7;
    _res(3, 0) = _tmp29*(_tmp17*(_tmp10 + _tmp12) + 1.0) + _tmp40*(_tmp31 + _tmp33) + _tmp46*(-_tmp41 + _tmp42);
    _res(4, 0) = _tmp29*(-_tmp31 + _tmp33) + _tmp40*(_tmp17*(_tmp10 + _tmp47) + 1.0) + _tmp46*(_tmp48 + _tmp49);
    _res(5, 0) = _tmp29*(_tmp41 + _tmp42) + _tmp40*(-_tmp48 + _tmp49) + _tmp46*(_tmp17*(_tmp12 + _tmp47) + 1.0);

    return _res;
}


}  // namespace pose3
}  // namespace geo

// Explicit instantiation
template struct geo::pose3::LieGroupOps<double>;
template struct geo::pose3::LieGroupOps<float>;
