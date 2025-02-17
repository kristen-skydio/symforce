// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     function/FUNCTION.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

#include <Eigen/Dense>

#include <sym/pose3.h>

namespace sym {

/**
 * Return the 2dof residual of reprojecting the landmark into the target camera and comparing
 * against the correspondence in the target camera.
 *
 * The landmark is specified as a pixel in the source camera and an inverse range; this means the
 * landmark is fixed in the source camera and always has residual 0 there (this 0 residual is not
 * returned, only the residual in the target camera is returned).
 *
 * The norm of the residual is whitened using the Barron noise model.  Whitening each component of
 * the reprojection error separately would result in rejecting individual components as outliers.
 * Instead, we minimize the whitened norm of the full reprojection error for each point.  See the
 * docstring for `NoiseModel.whiten_norm` for more information on this, and the docstring of
 * `BarronNoiseModel` for more information on the noise model.
 *
 * Args:
 *     source_pose: The pose of the source camera
 *     source_calibration_storage: The storage vector of the source camera calibration
 *     target_pose: The pose of the target camera
 *     target_calibration_storage: The storage vector of the target camera calibration
 *     source_inverse_range: The inverse range of the landmark in the source camera
 *     source_pixel: The location of the landmark in the source camera
 *     target_pixel: The location of the correspondence in the target camera
 *     weight: The weight of the factor
 *     gnc_mu: The mu convexity parameter for the Barron noise model
 *     gnc_scale: The scale parameter for the Barron noise model
 *     epsilon: Small positive value
 *     camera_model_class: The subclass of CameraCal to use as the camera model
 *
 * Outputs:
 *     res: 2dof residual of the reprojection
 *     jacobian: (2x13) jacobian of res wrt args source_pose (6), target_pose (6),
 *               source_inverse_range (1)
 *     hessian: (13x13) Gauss-Newton hessian for args source_pose (6), target_pose (6),
 *              source_inverse_range (1)
 *     rhs: (13x1) Gauss-Newton rhs for args source_pose (6), target_pose (6), source_inverse_range
 *          (1)
 */
template <typename Scalar>
void InverseRangeLandmarkAtanReprojectionErrorFactor(
    const sym::Pose3<Scalar>& source_pose,
    const Eigen::Matrix<Scalar, 5, 1>& source_calibration_storage,
    const sym::Pose3<Scalar>& target_pose,
    const Eigen::Matrix<Scalar, 5, 1>& target_calibration_storage,
    const Scalar source_inverse_range, const Eigen::Matrix<Scalar, 2, 1>& source_pixel,
    const Eigen::Matrix<Scalar, 2, 1>& target_pixel, const Scalar weight, const Scalar gnc_mu,
    const Scalar gnc_scale, const Scalar epsilon, Eigen::Matrix<Scalar, 2, 1>* const res = nullptr,
    Eigen::Matrix<Scalar, 2, 13>* const jacobian = nullptr,
    Eigen::Matrix<Scalar, 13, 13>* const hessian = nullptr,
    Eigen::Matrix<Scalar, 13, 1>* const rhs = nullptr) {
  // Total ops: 1234

  // Input arrays
  const Eigen::Matrix<Scalar, 7, 1>& _source_pose = source_pose.Data();
  const Eigen::Matrix<Scalar, 7, 1>& _target_pose = target_pose.Data();

  // Intermediate terms (352)
  const Scalar _tmp0 = std::pow(_target_pose[2], Scalar(2));
  const Scalar _tmp1 = -2 * _tmp0;
  const Scalar _tmp2 = std::pow(_target_pose[1], Scalar(2));
  const Scalar _tmp3 = 1 - 2 * _tmp2;
  const Scalar _tmp4 = _tmp1 + _tmp3;
  const Scalar _tmp5 = std::pow(_source_pose[2], Scalar(2));
  const Scalar _tmp6 = -2 * _tmp5;
  const Scalar _tmp7 = std::pow(_source_pose[1], Scalar(2));
  const Scalar _tmp8 = 1 - 2 * _tmp7;
  const Scalar _tmp9 = _tmp6 + _tmp8;
  const Scalar _tmp10 = -source_calibration_storage(2, 0) + source_pixel(0, 0);
  const Scalar _tmp11 = _tmp10 / source_calibration_storage(0, 0);
  const Scalar _tmp12 = -source_calibration_storage(3, 0) + source_pixel(1, 0);
  const Scalar _tmp13 =
      std::pow(_tmp12, Scalar(2)) / std::pow(source_calibration_storage(1, 0), Scalar(2));
  const Scalar _tmp14 = Scalar(0.5) * source_calibration_storage(4, 0);
  const Scalar _tmp15 = std::tan(_tmp14);
  const Scalar _tmp16 =
      std::pow(_tmp10, Scalar(2)) / std::pow(source_calibration_storage(0, 0), Scalar(2));
  const Scalar _tmp17 = _tmp13 + _tmp16 + epsilon;
  const Scalar _tmp18 = std::sqrt(_tmp17);
  const Scalar _tmp19 = _tmp18 * source_calibration_storage(4, 0);
  const Scalar _tmp20 = std::tan(_tmp19);
  const Scalar _tmp21 = (Scalar(1) / Scalar(4)) * std::pow(_tmp20, Scalar(2)) / _tmp17;
  const Scalar _tmp22 = _tmp21 / std::pow(_tmp15, Scalar(2));
  const Scalar _tmp23 =
      std::pow(Scalar(_tmp13 * _tmp22 + _tmp16 * _tmp22 + 1), Scalar(Scalar(-1) / Scalar(2)));
  const Scalar _tmp24 = (Scalar(1) / Scalar(2)) * _tmp20 / _tmp18;
  const Scalar _tmp25 = _tmp23 * _tmp24 / _tmp15;
  const Scalar _tmp26 = _tmp11 * _tmp25;
  const Scalar _tmp27 = 2 * _source_pose[0];
  const Scalar _tmp28 = _source_pose[2] * _tmp27;
  const Scalar _tmp29 = 2 * _source_pose[1];
  const Scalar _tmp30 = _source_pose[3] * _tmp29;
  const Scalar _tmp31 = _tmp28 + _tmp30;
  const Scalar _tmp32 = _source_pose[1] * _tmp27;
  const Scalar _tmp33 = 2 * _source_pose[2] * _source_pose[3];
  const Scalar _tmp34 = -_tmp33;
  const Scalar _tmp35 = _tmp32 + _tmp34;
  const Scalar _tmp36 = _tmp12 / source_calibration_storage(1, 0);
  const Scalar _tmp37 = _tmp25 * _tmp36;
  const Scalar _tmp38 = _source_pose[4] - _target_pose[4];
  const Scalar _tmp39 = _tmp38 * source_inverse_range;
  const Scalar _tmp40 = _tmp23 * _tmp31 + _tmp26 * _tmp9 + _tmp35 * _tmp37 + _tmp39;
  const Scalar _tmp41 = 2 * _target_pose[2];
  const Scalar _tmp42 = _target_pose[3] * _tmp41;
  const Scalar _tmp43 = 2 * _target_pose[1];
  const Scalar _tmp44 = _target_pose[0] * _tmp43;
  const Scalar _tmp45 = _tmp42 + _tmp44;
  const Scalar _tmp46 = std::pow(_source_pose[0], Scalar(2));
  const Scalar _tmp47 = -2 * _tmp46;
  const Scalar _tmp48 = _tmp47 + _tmp6 + 1;
  const Scalar _tmp49 = _source_pose[3] * _tmp27;
  const Scalar _tmp50 = -_tmp49;
  const Scalar _tmp51 = _source_pose[2] * _tmp29;
  const Scalar _tmp52 = _tmp50 + _tmp51;
  const Scalar _tmp53 = _tmp32 + _tmp33;
  const Scalar _tmp54 = _source_pose[5] - _target_pose[5];
  const Scalar _tmp55 = _tmp54 * source_inverse_range;
  const Scalar _tmp56 = _tmp23 * _tmp52 + _tmp26 * _tmp53 + _tmp37 * _tmp48 + _tmp55;
  const Scalar _tmp57 = _target_pose[0] * _tmp41;
  const Scalar _tmp58 = _target_pose[3] * _tmp43;
  const Scalar _tmp59 = -_tmp58;
  const Scalar _tmp60 = _tmp57 + _tmp59;
  const Scalar _tmp61 = _tmp47 + _tmp8;
  const Scalar _tmp62 = _tmp49 + _tmp51;
  const Scalar _tmp63 = -_tmp30;
  const Scalar _tmp64 = _tmp28 + _tmp63;
  const Scalar _tmp65 = _source_pose[6] - _target_pose[6];
  const Scalar _tmp66 = _tmp65 * source_inverse_range;
  const Scalar _tmp67 = _tmp23 * _tmp61 + _tmp26 * _tmp64 + _tmp37 * _tmp62 + _tmp66;
  const Scalar _tmp68 = _tmp4 * _tmp40 + _tmp45 * _tmp56 + _tmp60 * _tmp67;
  const Scalar _tmp69 = Scalar(1.0) / (target_calibration_storage(4, 0));
  const Scalar _tmp70 = _tmp69 * target_calibration_storage(0, 0);
  const Scalar _tmp71 = _tmp57 + _tmp58;
  const Scalar _tmp72 = _target_pose[1] * _tmp41;
  const Scalar _tmp73 = 2 * _target_pose[0] * _target_pose[3];
  const Scalar _tmp74 = -_tmp73;
  const Scalar _tmp75 = _tmp72 + _tmp74;
  const Scalar _tmp76 = std::pow(_target_pose[0], Scalar(2));
  const Scalar _tmp77 = -2 * _tmp76;
  const Scalar _tmp78 = _tmp3 + _tmp77;
  const Scalar _tmp79 = _tmp40 * _tmp71 + _tmp56 * _tmp75 + _tmp67 * _tmp78;
  const Scalar _tmp80 = std::max<Scalar>(_tmp79, epsilon);
  const Scalar _tmp81 = Scalar(0.5) * target_calibration_storage(4, 0);
  const Scalar _tmp82 = std::pow(_tmp80, Scalar(-2));
  const Scalar _tmp83 = -_tmp42;
  const Scalar _tmp84 = _tmp44 + _tmp83;
  const Scalar _tmp85 = _tmp1 + _tmp77 + 1;
  const Scalar _tmp86 = _tmp72 + _tmp73;
  const Scalar _tmp87 = _tmp40 * _tmp84 + _tmp56 * _tmp85 + _tmp67 * _tmp86;
  const Scalar _tmp88 = std::sqrt(Scalar(std::pow(_tmp68, Scalar(2)) * _tmp82 +
                                         _tmp82 * std::pow(_tmp87, Scalar(2)) + epsilon));
  const Scalar _tmp89 = std::atan(2 * _tmp88 * std::tan(_tmp81)) / (_tmp80 * _tmp88);
  const Scalar _tmp90 = target_calibration_storage(2, 0) - target_pixel(0, 0);
  const Scalar _tmp91 = _tmp68 * _tmp70 * _tmp89 + _tmp90;
  const Scalar _tmp92 = _tmp69 * target_calibration_storage(1, 0);
  const Scalar _tmp93 = target_calibration_storage(3, 0) - target_pixel(1, 0);
  const Scalar _tmp94 = _tmp87 * _tmp89 * _tmp92 + _tmp93;
  const Scalar _tmp95 = std::pow(_tmp91, Scalar(2)) + std::pow(_tmp94, Scalar(2)) + epsilon;
  const Scalar _tmp96 = Scalar(1.0) / (epsilon - gnc_mu + 1);
  const Scalar _tmp97 = epsilon + std::fabs(_tmp96);
  const Scalar _tmp98 = std::pow(gnc_scale, Scalar(-2));
  const Scalar _tmp99 = _tmp98 / _tmp97;
  const Scalar _tmp100 = 2 - _tmp96;
  const Scalar _tmp101 =
      _tmp100 + epsilon * (2 * std::min<Scalar>(0, (((_tmp100) > 0) - ((_tmp100) < 0))) + 1);
  const Scalar _tmp102 = (Scalar(1) / Scalar(2)) * _tmp101;
  const Scalar _tmp103 = 2 * _tmp97 / _tmp101;
  const Scalar _tmp104 =
      std::sqrt(weight) * std::max<Scalar>(0, (((-std::fabs(_tmp19) + Scalar(M_PI_2)) > 0) -
                                               ((-std::fabs(_tmp19) + Scalar(M_PI_2)) < 0)));
  const Scalar _tmp105 =
      _tmp104 * std::sqrt(Scalar(_tmp103 * (std::pow(Scalar(_tmp95 * _tmp99 + 1), _tmp102) - 1))) *
      std::max<Scalar>(0, (((_tmp79) > 0) - ((_tmp79) < 0))) / std::sqrt(_tmp95);
  const Scalar _tmp106 = _tmp105 * _tmp91;
  const Scalar _tmp107 = _tmp105 * _tmp94;
  const Scalar _tmp108 = std::pow(_source_pose[3], Scalar(2));
  const Scalar _tmp109 = -_tmp108;
  const Scalar _tmp110 = -_tmp7;
  const Scalar _tmp111 = std::tan(_tmp14);
  const Scalar _tmp112 = _tmp21 / std::pow(_tmp111, Scalar(2));
  const Scalar _tmp113 =
      std::pow(Scalar(_tmp112 * _tmp13 + _tmp112 * _tmp16 + 1), Scalar(Scalar(-1) / Scalar(2)));
  const Scalar _tmp114 = _tmp113 * _tmp52;
  const Scalar _tmp115 = _tmp24 / _tmp111;
  const Scalar _tmp116 = _tmp115 * _tmp36;
  const Scalar _tmp117 = _tmp113 * (_tmp109 + _tmp110 + _tmp46 + _tmp5) + _tmp114 * _tmp116;
  const Scalar _tmp118 = -_tmp51;
  const Scalar _tmp119 = -_tmp46;
  const Scalar _tmp120 = _tmp119 + _tmp5;
  const Scalar _tmp121 = _tmp108 + _tmp110;
  const Scalar _tmp122 = _tmp113 * _tmp115;
  const Scalar _tmp123 = _tmp122 * _tmp36;
  const Scalar _tmp124 = _tmp113 * (_tmp118 + _tmp50) + _tmp123 * (_tmp120 + _tmp121);
  const Scalar _tmp125 = -_tmp32;
  const Scalar _tmp126 = _tmp113 * _tmp31;
  const Scalar _tmp127 = _tmp113 * (_tmp125 + _tmp33) + _tmp116 * _tmp126;
  const Scalar _tmp128 = _tmp117 * _tmp75 + _tmp124 * _tmp78 + _tmp127 * _tmp71;
  const Scalar _tmp129 = _tmp113 * _tmp64;
  const Scalar _tmp130 = _tmp11 * _tmp115;
  const Scalar _tmp131 = _tmp113 * _tmp61 + _tmp123 * _tmp62 + _tmp129 * _tmp130 + _tmp66;
  const Scalar _tmp132 = _tmp113 * _tmp53;
  const Scalar _tmp133 = _tmp114 + _tmp123 * _tmp48 + _tmp130 * _tmp132 + _tmp55;
  const Scalar _tmp134 = _tmp11 * _tmp122;
  const Scalar _tmp135 = _tmp123 * _tmp35 + _tmp126 + _tmp134 * _tmp9 + _tmp39;
  const Scalar _tmp136 = _tmp133 * _tmp75 + _tmp135 * _tmp71;
  const Scalar _tmp137 = _tmp131 * _tmp78 + _tmp136;
  const Scalar _tmp138 = std::max<Scalar>(_tmp137, epsilon);
  const Scalar _tmp139 = std::pow(_tmp138, Scalar(-2));
  const Scalar _tmp140 = (((_tmp137 - epsilon) > 0) - ((_tmp137 - epsilon) < 0)) + 1;
  const Scalar _tmp141 = std::tan(_tmp81);
  const Scalar _tmp142 = _tmp131 * _tmp86 + _tmp135 * _tmp84;
  const Scalar _tmp143 = _tmp133 * _tmp85 + _tmp142;
  const Scalar _tmp144 = std::pow(_tmp143, Scalar(2));
  const Scalar _tmp145 = _tmp131 * _tmp60 + _tmp133 * _tmp45;
  const Scalar _tmp146 = _tmp135 * _tmp4 + _tmp145;
  const Scalar _tmp147 = std::pow(_tmp146, Scalar(2));
  const Scalar _tmp148 = _tmp139 * _tmp144 + _tmp139 * _tmp147 + epsilon;
  const Scalar _tmp149 = std::sqrt(_tmp148);
  const Scalar _tmp150 = std::atan(2 * _tmp141 * _tmp149);
  const Scalar _tmp151 = _tmp150 / _tmp149;
  const Scalar _tmp152 = (Scalar(1) / Scalar(2)) * _tmp139 * _tmp140 * _tmp151;
  const Scalar _tmp153 = _tmp146 * _tmp70;
  const Scalar _tmp154 = _tmp152 * _tmp153;
  const Scalar _tmp155 = _tmp117 * _tmp85 + _tmp124 * _tmp86 + _tmp127 * _tmp84;
  const Scalar _tmp156 = 2 * _tmp139;
  const Scalar _tmp157 = _tmp143 * _tmp156;
  const Scalar _tmp158 = _tmp140 / [&]() {
    const Scalar base = _tmp138;
    return base * base * base;
  }();
  const Scalar _tmp159 = _tmp144 * _tmp158;
  const Scalar _tmp160 = _tmp117 * _tmp45 + _tmp124 * _tmp60 + _tmp127 * _tmp4;
  const Scalar _tmp161 = _tmp146 * _tmp156;
  const Scalar _tmp162 = _tmp147 * _tmp158;
  const Scalar _tmp163 =
      -_tmp128 * _tmp159 - _tmp128 * _tmp162 + _tmp155 * _tmp157 + _tmp160 * _tmp161;
  const Scalar _tmp164 = Scalar(1.0) / (_tmp138);
  const Scalar _tmp165 = _tmp164 * _tmp70;
  const Scalar _tmp166 = _tmp146 * _tmp165;
  const Scalar _tmp167 = (Scalar(1) / Scalar(2)) * _tmp150 / (_tmp148 * std::sqrt(_tmp148));
  const Scalar _tmp168 = _tmp166 * _tmp167;
  const Scalar _tmp169 = _tmp141 / (_tmp148 * (4 * std::pow(_tmp141, Scalar(2)) * _tmp148 + 1));
  const Scalar _tmp170 = _tmp166 * _tmp169;
  const Scalar _tmp171 = _tmp151 * _tmp165;
  const Scalar _tmp172 =
      -_tmp128 * _tmp154 + _tmp160 * _tmp171 - _tmp163 * _tmp168 + _tmp163 * _tmp170;
  const Scalar _tmp173 = _tmp146 * _tmp171 + _tmp90;
  const Scalar _tmp174 = 2 * _tmp173;
  const Scalar _tmp175 = _tmp143 * _tmp92;
  const Scalar _tmp176 = _tmp152 * _tmp175;
  const Scalar _tmp177 = _tmp164 * _tmp92;
  const Scalar _tmp178 = _tmp143 * _tmp177;
  const Scalar _tmp179 = _tmp169 * _tmp178;
  const Scalar _tmp180 = _tmp151 * _tmp177;
  const Scalar _tmp181 = _tmp167 * _tmp178;
  const Scalar _tmp182 =
      -_tmp128 * _tmp176 + _tmp155 * _tmp180 + _tmp163 * _tmp179 - _tmp163 * _tmp181;
  const Scalar _tmp183 = _tmp143 * _tmp180 + _tmp93;
  const Scalar _tmp184 = 2 * _tmp183;
  const Scalar _tmp185 = _tmp172 * _tmp174 + _tmp182 * _tmp184;
  const Scalar _tmp186 = std::max<Scalar>(0, (((_tmp137) > 0) - ((_tmp137) < 0)));
  const Scalar _tmp187 = std::pow(_tmp173, Scalar(2)) + std::pow(_tmp183, Scalar(2)) + epsilon;
  const Scalar _tmp188 = std::pow(_tmp187, Scalar(Scalar(-1) / Scalar(2)));
  const Scalar _tmp189 = _tmp187 * _tmp99 + 1;
  const Scalar _tmp190 = std::sqrt(Scalar(_tmp103 * (std::pow(_tmp189, _tmp102) - 1)));
  const Scalar _tmp191 =
      _tmp104 * _tmp186 * _tmp188 * std::pow(_tmp189, Scalar(_tmp102 - 1)) * _tmp98 / _tmp190;
  const Scalar _tmp192 = (Scalar(1) / Scalar(2)) * _tmp191;
  const Scalar _tmp193 = _tmp173 * _tmp192;
  const Scalar _tmp194 = _tmp104 * _tmp186 * _tmp190;
  const Scalar _tmp195 = _tmp194 / (_tmp187 * std::sqrt(_tmp187));
  const Scalar _tmp196 = (Scalar(1) / Scalar(2)) * _tmp195;
  const Scalar _tmp197 = _tmp173 * _tmp196;
  const Scalar _tmp198 = _tmp188 * _tmp194;
  const Scalar _tmp199 = _tmp172 * _tmp198 + _tmp185 * _tmp193 - _tmp185 * _tmp197;
  const Scalar _tmp200 = _tmp183 * _tmp192;
  const Scalar _tmp201 = _tmp183 * _tmp196;
  const Scalar _tmp202 = _tmp182 * _tmp198 + _tmp185 * _tmp200 - _tmp185 * _tmp201;
  const Scalar _tmp203 = _tmp109 + _tmp7;
  const Scalar _tmp204 = -_tmp5;
  const Scalar _tmp205 = _tmp204 + _tmp46;
  const Scalar _tmp206 = _tmp129 + _tmp134 * (_tmp203 + _tmp205);
  const Scalar _tmp207 = -_tmp28;
  const Scalar _tmp208 = _tmp113 * (_tmp121 + _tmp205) + _tmp134 * (_tmp207 + _tmp63);
  const Scalar _tmp209 = _tmp132 + _tmp134 * (_tmp118 + _tmp49);
  const Scalar _tmp210 = _tmp206 * _tmp60 + _tmp208 * _tmp4 + _tmp209 * _tmp45;
  const Scalar _tmp211 = _tmp206 * _tmp78 + _tmp208 * _tmp71 + _tmp209 * _tmp75;
  const Scalar _tmp212 = _tmp158 * _tmp211;
  const Scalar _tmp213 = _tmp206 * _tmp86 + _tmp208 * _tmp84 + _tmp209 * _tmp85;
  const Scalar _tmp214 =
      -_tmp144 * _tmp212 - _tmp147 * _tmp212 + _tmp157 * _tmp213 + _tmp161 * _tmp210;
  const Scalar _tmp215 = _tmp152 * _tmp211;
  const Scalar _tmp216 =
      -_tmp153 * _tmp215 - _tmp168 * _tmp214 + _tmp170 * _tmp214 + _tmp171 * _tmp210;
  const Scalar _tmp217 =
      -_tmp175 * _tmp215 + _tmp179 * _tmp214 + _tmp180 * _tmp213 - _tmp181 * _tmp214;
  const Scalar _tmp218 = _tmp174 * _tmp216 + _tmp184 * _tmp217;
  const Scalar _tmp219 = _tmp193 * _tmp218 - _tmp197 * _tmp218 + _tmp198 * _tmp216;
  const Scalar _tmp220 = _tmp198 * _tmp217 + _tmp200 * _tmp218 - _tmp201 * _tmp218;
  const Scalar _tmp221 = _tmp123 * (_tmp207 + _tmp30) + _tmp134 * _tmp62;
  const Scalar _tmp222 = _tmp123 * (_tmp120 + _tmp203) + _tmp134 * _tmp35;
  const Scalar _tmp223 =
      _tmp123 * (_tmp125 + _tmp34) + _tmp134 * (_tmp108 + _tmp119 + _tmp204 + _tmp7);
  const Scalar _tmp224 = _tmp221 * _tmp78 + _tmp222 * _tmp71 + _tmp223 * _tmp75;
  const Scalar _tmp225 = _tmp221 * _tmp60 + _tmp222 * _tmp4 + _tmp223 * _tmp45;
  const Scalar _tmp226 = _tmp221 * _tmp86 + _tmp222 * _tmp84 + _tmp223 * _tmp85;
  const Scalar _tmp227 =
      _tmp157 * _tmp226 - _tmp159 * _tmp224 + _tmp161 * _tmp225 - _tmp162 * _tmp224;
  const Scalar _tmp228 =
      -_tmp154 * _tmp224 - _tmp168 * _tmp227 + _tmp170 * _tmp227 + _tmp171 * _tmp225;
  const Scalar _tmp229 =
      -_tmp176 * _tmp224 + _tmp179 * _tmp227 + _tmp180 * _tmp226 - _tmp181 * _tmp227;
  const Scalar _tmp230 = _tmp174 * _tmp228 + _tmp184 * _tmp229;
  const Scalar _tmp231 = _tmp193 * _tmp230 - _tmp197 * _tmp230 + _tmp198 * _tmp228;
  const Scalar _tmp232 = _tmp198 * _tmp229 + _tmp200 * _tmp230 - _tmp201 * _tmp230;
  const Scalar _tmp233 = _tmp161 * source_inverse_range;
  const Scalar _tmp234 = _tmp233 * _tmp4;
  const Scalar _tmp235 = _tmp159 * source_inverse_range;
  const Scalar _tmp236 = _tmp235 * _tmp71;
  const Scalar _tmp237 = _tmp162 * source_inverse_range;
  const Scalar _tmp238 = _tmp237 * _tmp71;
  const Scalar _tmp239 = _tmp157 * source_inverse_range;
  const Scalar _tmp240 = _tmp239 * _tmp84;
  const Scalar _tmp241 = _tmp234 - _tmp236 - _tmp238 + _tmp240;
  const Scalar _tmp242 = _tmp154 * source_inverse_range;
  const Scalar _tmp243 = _tmp242 * _tmp71;
  const Scalar _tmp244 = _tmp171 * source_inverse_range;
  const Scalar _tmp245 = _tmp244 * _tmp4;
  const Scalar _tmp246 = -_tmp168 * _tmp241 + _tmp170 * _tmp241 - _tmp243 + _tmp245;
  const Scalar _tmp247 = _tmp180 * source_inverse_range;
  const Scalar _tmp248 = _tmp247 * _tmp84;
  const Scalar _tmp249 = _tmp176 * source_inverse_range;
  const Scalar _tmp250 = _tmp249 * _tmp71;
  const Scalar _tmp251 = _tmp179 * _tmp241 - _tmp181 * _tmp241 + _tmp248 - _tmp250;
  const Scalar _tmp252 = _tmp174 * _tmp246 + _tmp184 * _tmp251;
  const Scalar _tmp253 = _tmp193 * _tmp252 - _tmp197 * _tmp252 + _tmp198 * _tmp246;
  const Scalar _tmp254 = _tmp198 * _tmp251 + _tmp200 * _tmp252 - _tmp201 * _tmp252;
  const Scalar _tmp255 = _tmp237 * _tmp75;
  const Scalar _tmp256 = _tmp239 * _tmp85;
  const Scalar _tmp257 = _tmp235 * _tmp75;
  const Scalar _tmp258 = _tmp233 * _tmp45;
  const Scalar _tmp259 = -_tmp255 + _tmp256 - _tmp257 + _tmp258;
  const Scalar _tmp260 = _tmp244 * _tmp45;
  const Scalar _tmp261 = _tmp242 * _tmp75;
  const Scalar _tmp262 = -_tmp168 * _tmp259 + _tmp170 * _tmp259 + _tmp260 - _tmp261;
  const Scalar _tmp263 = _tmp247 * _tmp85;
  const Scalar _tmp264 = _tmp249 * _tmp75;
  const Scalar _tmp265 = _tmp179 * _tmp259 - _tmp181 * _tmp259 + _tmp263 - _tmp264;
  const Scalar _tmp266 = _tmp174 * _tmp262 + _tmp184 * _tmp265;
  const Scalar _tmp267 = _tmp193 * _tmp266 - _tmp197 * _tmp266 + _tmp198 * _tmp262;
  const Scalar _tmp268 = _tmp198 * _tmp265 + _tmp200 * _tmp266 - _tmp201 * _tmp266;
  const Scalar _tmp269 = _tmp242 * _tmp78;
  const Scalar _tmp270 = _tmp235 * _tmp78;
  const Scalar _tmp271 = _tmp233 * _tmp60;
  const Scalar _tmp272 = _tmp237 * _tmp78;
  const Scalar _tmp273 = _tmp239 * _tmp86;
  const Scalar _tmp274 = -_tmp270 + _tmp271 - _tmp272 + _tmp273;
  const Scalar _tmp275 = _tmp167 * _tmp274;
  const Scalar _tmp276 = _tmp244 * _tmp60;
  const Scalar _tmp277 = -_tmp166 * _tmp275 + _tmp170 * _tmp274 - _tmp269 + _tmp276;
  const Scalar _tmp278 = _tmp247 * _tmp86;
  const Scalar _tmp279 = _tmp249 * _tmp78;
  const Scalar _tmp280 = -_tmp178 * _tmp275 + _tmp179 * _tmp274 + _tmp278 - _tmp279;
  const Scalar _tmp281 = _tmp174 * _tmp277 + _tmp184 * _tmp280;
  const Scalar _tmp282 = _tmp193 * _tmp281 - _tmp197 * _tmp281 + _tmp198 * _tmp277;
  const Scalar _tmp283 = _tmp198 * _tmp280 + _tmp200 * _tmp281 - _tmp201 * _tmp281;
  const Scalar _tmp284 = -_tmp2;
  const Scalar _tmp285 = _tmp0 + _tmp284;
  const Scalar _tmp286 = std::pow(_target_pose[3], Scalar(2));
  const Scalar _tmp287 = -_tmp286;
  const Scalar _tmp288 = _tmp287 + _tmp76;
  const Scalar _tmp289 = -_tmp44;
  const Scalar _tmp290 = -_tmp72;
  const Scalar _tmp291 =
      _tmp131 * (_tmp290 + _tmp74) + _tmp133 * (_tmp285 + _tmp288) + _tmp135 * (_tmp289 + _tmp42);
  const Scalar _tmp292 = -_tmp76;
  const Scalar _tmp293 = _tmp286 + _tmp292;
  const Scalar _tmp294 = _tmp131 * (_tmp285 + _tmp293) + _tmp136;
  const Scalar _tmp295 = _tmp157 * _tmp294 - _tmp159 * _tmp291 - _tmp162 * _tmp291;
  const Scalar _tmp296 = _tmp152 * _tmp291;
  const Scalar _tmp297 = -_tmp153 * _tmp296 - _tmp168 * _tmp295 + _tmp170 * _tmp295;
  const Scalar _tmp298 =
      -_tmp175 * _tmp296 + _tmp179 * _tmp295 + _tmp180 * _tmp294 - _tmp181 * _tmp295;
  const Scalar _tmp299 =
      (Scalar(1) / Scalar(2)) * _tmp174 * _tmp297 + (Scalar(1) / Scalar(2)) * _tmp184 * _tmp298;
  const Scalar _tmp300 = _tmp173 * _tmp299;
  const Scalar _tmp301 = _tmp191 * _tmp300 - _tmp195 * _tmp300 + _tmp198 * _tmp297;
  const Scalar _tmp302 = _tmp183 * _tmp299;
  const Scalar _tmp303 = _tmp191 * _tmp302 - _tmp195 * _tmp302 + _tmp198 * _tmp298;
  const Scalar _tmp304 = -_tmp0;
  const Scalar _tmp305 = _tmp135 * (_tmp284 + _tmp286 + _tmp304 + _tmp76) + _tmp145;
  const Scalar _tmp306 = -_tmp57;
  const Scalar _tmp307 = _tmp2 + _tmp304;
  const Scalar _tmp308 =
      _tmp131 * (_tmp288 + _tmp307) + _tmp133 * (_tmp290 + _tmp73) + _tmp135 * (_tmp306 + _tmp59);
  const Scalar _tmp309 = -_tmp159 * _tmp305 + _tmp161 * _tmp308 - _tmp162 * _tmp305;
  const Scalar _tmp310 = -_tmp176 * _tmp305 + _tmp179 * _tmp309 - _tmp181 * _tmp309;
  const Scalar _tmp311 =
      -_tmp154 * _tmp305 - _tmp168 * _tmp309 + _tmp170 * _tmp309 + _tmp171 * _tmp308;
  const Scalar _tmp312 = _tmp174 * _tmp311 + _tmp184 * _tmp310;
  const Scalar _tmp313 = _tmp193 * _tmp312 - _tmp197 * _tmp312 + _tmp198 * _tmp311;
  const Scalar _tmp314 = _tmp198 * _tmp310 + _tmp200 * _tmp312 - _tmp201 * _tmp312;
  const Scalar _tmp315 = _tmp133 * (_tmp293 + _tmp307) + _tmp142;
  const Scalar _tmp316 = _tmp131 * (_tmp306 + _tmp58) + _tmp133 * (_tmp289 + _tmp83) +
                         _tmp135 * (_tmp0 + _tmp2 + _tmp287 + _tmp292);
  const Scalar _tmp317 = _tmp157 * _tmp316 + _tmp161 * _tmp315;
  const Scalar _tmp318 = -_tmp168 * _tmp317 + _tmp170 * _tmp317 + _tmp171 * _tmp315;
  const Scalar _tmp319 = _tmp179 * _tmp317 + _tmp180 * _tmp316 - _tmp181 * _tmp317;
  const Scalar _tmp320 = _tmp174 * _tmp318 + _tmp184 * _tmp319;
  const Scalar _tmp321 = _tmp193 * _tmp320 - _tmp197 * _tmp320 + _tmp198 * _tmp318;
  const Scalar _tmp322 = _tmp198 * _tmp319 + _tmp200 * _tmp320 - _tmp201 * _tmp320;
  const Scalar _tmp323 = -_tmp234 + _tmp236 + _tmp238 - _tmp240;
  const Scalar _tmp324 = _tmp166 * _tmp323;
  const Scalar _tmp325 = -_tmp167 * _tmp324 + _tmp169 * _tmp324 + _tmp243 - _tmp245;
  const Scalar _tmp326 = _tmp179 * _tmp323 - _tmp181 * _tmp323 - _tmp248 + _tmp250;
  const Scalar _tmp327 = _tmp174 * _tmp325 + _tmp184 * _tmp326;
  const Scalar _tmp328 = _tmp193 * _tmp327 - _tmp197 * _tmp327 + _tmp198 * _tmp325;
  const Scalar _tmp329 = _tmp198 * _tmp326 + _tmp200 * _tmp327 - _tmp201 * _tmp327;
  const Scalar _tmp330 = _tmp255 - _tmp256 + _tmp257 - _tmp258;
  const Scalar _tmp331 = _tmp179 * _tmp330 - _tmp181 * _tmp330 - _tmp263 + _tmp264;
  const Scalar _tmp332 = -_tmp168 * _tmp330 + _tmp170 * _tmp330 - _tmp260 + _tmp261;
  const Scalar _tmp333 = _tmp174 * _tmp332 + _tmp184 * _tmp331;
  const Scalar _tmp334 = _tmp193 * _tmp333 - _tmp197 * _tmp333 + _tmp198 * _tmp332;
  const Scalar _tmp335 = _tmp198 * _tmp331 + _tmp200 * _tmp333 - _tmp201 * _tmp333;
  const Scalar _tmp336 = _tmp270 - _tmp271 + _tmp272 - _tmp273;
  const Scalar _tmp337 = _tmp166 * _tmp336;
  const Scalar _tmp338 = -_tmp167 * _tmp337 + _tmp169 * _tmp337 + _tmp269 - _tmp276;
  const Scalar _tmp339 = _tmp179 * _tmp336 - _tmp181 * _tmp336 - _tmp278 + _tmp279;
  const Scalar _tmp340 = _tmp174 * _tmp338 + _tmp184 * _tmp339;
  const Scalar _tmp341 = _tmp193 * _tmp340 - _tmp197 * _tmp340 + _tmp198 * _tmp338;
  const Scalar _tmp342 = _tmp198 * _tmp339 + _tmp200 * _tmp340 - _tmp201 * _tmp340;
  const Scalar _tmp343 = _tmp38 * _tmp71 + _tmp54 * _tmp75 + _tmp65 * _tmp78;
  const Scalar _tmp344 = _tmp38 * _tmp4 + _tmp45 * _tmp54 + _tmp60 * _tmp65;
  const Scalar _tmp345 = _tmp38 * _tmp84 + _tmp54 * _tmp85 + _tmp65 * _tmp86;
  const Scalar _tmp346 =
      _tmp157 * _tmp345 - _tmp159 * _tmp343 + _tmp161 * _tmp344 - _tmp162 * _tmp343;
  const Scalar _tmp347 =
      -_tmp176 * _tmp343 + _tmp179 * _tmp346 + _tmp180 * _tmp345 - _tmp181 * _tmp346;
  const Scalar _tmp348 =
      -_tmp154 * _tmp343 - _tmp168 * _tmp346 + _tmp170 * _tmp346 + _tmp171 * _tmp344;
  const Scalar _tmp349 = _tmp174 * _tmp348 + _tmp184 * _tmp347;
  const Scalar _tmp350 = _tmp193 * _tmp349 - _tmp197 * _tmp349 + _tmp198 * _tmp348;
  const Scalar _tmp351 = _tmp198 * _tmp347 + _tmp200 * _tmp349 - _tmp201 * _tmp349;

  // Output terms (4)
  if (res != nullptr) {
    Eigen::Matrix<Scalar, 2, 1>& _res = (*res);

    _res(0, 0) = _tmp106;
    _res(1, 0) = _tmp107;
  }

  if (jacobian != nullptr) {
    Eigen::Matrix<Scalar, 2, 13>& _jacobian = (*jacobian);

    _jacobian(0, 0) = _tmp199;
    _jacobian(1, 0) = _tmp202;
    _jacobian(0, 1) = _tmp219;
    _jacobian(1, 1) = _tmp220;
    _jacobian(0, 2) = _tmp231;
    _jacobian(1, 2) = _tmp232;
    _jacobian(0, 3) = _tmp253;
    _jacobian(1, 3) = _tmp254;
    _jacobian(0, 4) = _tmp267;
    _jacobian(1, 4) = _tmp268;
    _jacobian(0, 5) = _tmp282;
    _jacobian(1, 5) = _tmp283;
    _jacobian(0, 6) = _tmp301;
    _jacobian(1, 6) = _tmp303;
    _jacobian(0, 7) = _tmp313;
    _jacobian(1, 7) = _tmp314;
    _jacobian(0, 8) = _tmp321;
    _jacobian(1, 8) = _tmp322;
    _jacobian(0, 9) = _tmp328;
    _jacobian(1, 9) = _tmp329;
    _jacobian(0, 10) = _tmp334;
    _jacobian(1, 10) = _tmp335;
    _jacobian(0, 11) = _tmp341;
    _jacobian(1, 11) = _tmp342;
    _jacobian(0, 12) = _tmp350;
    _jacobian(1, 12) = _tmp351;
  }

  if (hessian != nullptr) {
    Eigen::Matrix<Scalar, 13, 13>& _hessian = (*hessian);

    _hessian(0, 0) = std::pow(_tmp199, Scalar(2)) + std::pow(_tmp202, Scalar(2));
    _hessian(1, 0) = _tmp199 * _tmp219 + _tmp202 * _tmp220;
    _hessian(2, 0) = _tmp199 * _tmp231 + _tmp202 * _tmp232;
    _hessian(3, 0) = _tmp199 * _tmp253 + _tmp202 * _tmp254;
    _hessian(4, 0) = _tmp199 * _tmp267 + _tmp202 * _tmp268;
    _hessian(5, 0) = _tmp199 * _tmp282 + _tmp202 * _tmp283;
    _hessian(6, 0) = _tmp199 * _tmp301 + _tmp202 * _tmp303;
    _hessian(7, 0) = _tmp199 * _tmp313 + _tmp202 * _tmp314;
    _hessian(8, 0) = _tmp199 * _tmp321 + _tmp202 * _tmp322;
    _hessian(9, 0) = _tmp199 * _tmp328 + _tmp202 * _tmp329;
    _hessian(10, 0) = _tmp199 * _tmp334 + _tmp202 * _tmp335;
    _hessian(11, 0) = _tmp199 * _tmp341 + _tmp202 * _tmp342;
    _hessian(12, 0) = _tmp199 * _tmp350 + _tmp202 * _tmp351;
    _hessian(0, 1) = 0;
    _hessian(1, 1) = std::pow(_tmp219, Scalar(2)) + std::pow(_tmp220, Scalar(2));
    _hessian(2, 1) = _tmp219 * _tmp231 + _tmp220 * _tmp232;
    _hessian(3, 1) = _tmp219 * _tmp253 + _tmp220 * _tmp254;
    _hessian(4, 1) = _tmp219 * _tmp267 + _tmp220 * _tmp268;
    _hessian(5, 1) = _tmp219 * _tmp282 + _tmp220 * _tmp283;
    _hessian(6, 1) = _tmp219 * _tmp301 + _tmp220 * _tmp303;
    _hessian(7, 1) = _tmp219 * _tmp313 + _tmp220 * _tmp314;
    _hessian(8, 1) = _tmp219 * _tmp321 + _tmp220 * _tmp322;
    _hessian(9, 1) = _tmp219 * _tmp328 + _tmp220 * _tmp329;
    _hessian(10, 1) = _tmp219 * _tmp334 + _tmp220 * _tmp335;
    _hessian(11, 1) = _tmp219 * _tmp341 + _tmp220 * _tmp342;
    _hessian(12, 1) = _tmp219 * _tmp350 + _tmp220 * _tmp351;
    _hessian(0, 2) = 0;
    _hessian(1, 2) = 0;
    _hessian(2, 2) = std::pow(_tmp231, Scalar(2)) + std::pow(_tmp232, Scalar(2));
    _hessian(3, 2) = _tmp231 * _tmp253 + _tmp232 * _tmp254;
    _hessian(4, 2) = _tmp231 * _tmp267 + _tmp232 * _tmp268;
    _hessian(5, 2) = _tmp231 * _tmp282 + _tmp232 * _tmp283;
    _hessian(6, 2) = _tmp231 * _tmp301 + _tmp232 * _tmp303;
    _hessian(7, 2) = _tmp231 * _tmp313 + _tmp232 * _tmp314;
    _hessian(8, 2) = _tmp231 * _tmp321 + _tmp232 * _tmp322;
    _hessian(9, 2) = _tmp231 * _tmp328 + _tmp232 * _tmp329;
    _hessian(10, 2) = _tmp231 * _tmp334 + _tmp232 * _tmp335;
    _hessian(11, 2) = _tmp231 * _tmp341 + _tmp232 * _tmp342;
    _hessian(12, 2) = _tmp231 * _tmp350 + _tmp232 * _tmp351;
    _hessian(0, 3) = 0;
    _hessian(1, 3) = 0;
    _hessian(2, 3) = 0;
    _hessian(3, 3) = std::pow(_tmp253, Scalar(2)) + std::pow(_tmp254, Scalar(2));
    _hessian(4, 3) = _tmp253 * _tmp267 + _tmp254 * _tmp268;
    _hessian(5, 3) = _tmp253 * _tmp282 + _tmp254 * _tmp283;
    _hessian(6, 3) = _tmp253 * _tmp301 + _tmp254 * _tmp303;
    _hessian(7, 3) = _tmp253 * _tmp313 + _tmp254 * _tmp314;
    _hessian(8, 3) = _tmp253 * _tmp321 + _tmp254 * _tmp322;
    _hessian(9, 3) = _tmp253 * _tmp328 + _tmp254 * _tmp329;
    _hessian(10, 3) = _tmp253 * _tmp334 + _tmp254 * _tmp335;
    _hessian(11, 3) = _tmp253 * _tmp341 + _tmp254 * _tmp342;
    _hessian(12, 3) = _tmp253 * _tmp350 + _tmp254 * _tmp351;
    _hessian(0, 4) = 0;
    _hessian(1, 4) = 0;
    _hessian(2, 4) = 0;
    _hessian(3, 4) = 0;
    _hessian(4, 4) = std::pow(_tmp267, Scalar(2)) + std::pow(_tmp268, Scalar(2));
    _hessian(5, 4) = _tmp267 * _tmp282 + _tmp268 * _tmp283;
    _hessian(6, 4) = _tmp267 * _tmp301 + _tmp268 * _tmp303;
    _hessian(7, 4) = _tmp267 * _tmp313 + _tmp268 * _tmp314;
    _hessian(8, 4) = _tmp267 * _tmp321 + _tmp268 * _tmp322;
    _hessian(9, 4) = _tmp267 * _tmp328 + _tmp268 * _tmp329;
    _hessian(10, 4) = _tmp267 * _tmp334 + _tmp268 * _tmp335;
    _hessian(11, 4) = _tmp267 * _tmp341 + _tmp268 * _tmp342;
    _hessian(12, 4) = _tmp267 * _tmp350 + _tmp268 * _tmp351;
    _hessian(0, 5) = 0;
    _hessian(1, 5) = 0;
    _hessian(2, 5) = 0;
    _hessian(3, 5) = 0;
    _hessian(4, 5) = 0;
    _hessian(5, 5) = std::pow(_tmp282, Scalar(2)) + std::pow(_tmp283, Scalar(2));
    _hessian(6, 5) = _tmp282 * _tmp301 + _tmp283 * _tmp303;
    _hessian(7, 5) = _tmp282 * _tmp313 + _tmp283 * _tmp314;
    _hessian(8, 5) = _tmp282 * _tmp321 + _tmp283 * _tmp322;
    _hessian(9, 5) = _tmp282 * _tmp328 + _tmp283 * _tmp329;
    _hessian(10, 5) = _tmp282 * _tmp334 + _tmp283 * _tmp335;
    _hessian(11, 5) = _tmp282 * _tmp341 + _tmp283 * _tmp342;
    _hessian(12, 5) = _tmp282 * _tmp350 + _tmp283 * _tmp351;
    _hessian(0, 6) = 0;
    _hessian(1, 6) = 0;
    _hessian(2, 6) = 0;
    _hessian(3, 6) = 0;
    _hessian(4, 6) = 0;
    _hessian(5, 6) = 0;
    _hessian(6, 6) = std::pow(_tmp301, Scalar(2)) + std::pow(_tmp303, Scalar(2));
    _hessian(7, 6) = _tmp301 * _tmp313 + _tmp303 * _tmp314;
    _hessian(8, 6) = _tmp301 * _tmp321 + _tmp303 * _tmp322;
    _hessian(9, 6) = _tmp301 * _tmp328 + _tmp303 * _tmp329;
    _hessian(10, 6) = _tmp301 * _tmp334 + _tmp303 * _tmp335;
    _hessian(11, 6) = _tmp301 * _tmp341 + _tmp303 * _tmp342;
    _hessian(12, 6) = _tmp301 * _tmp350 + _tmp303 * _tmp351;
    _hessian(0, 7) = 0;
    _hessian(1, 7) = 0;
    _hessian(2, 7) = 0;
    _hessian(3, 7) = 0;
    _hessian(4, 7) = 0;
    _hessian(5, 7) = 0;
    _hessian(6, 7) = 0;
    _hessian(7, 7) = std::pow(_tmp313, Scalar(2)) + std::pow(_tmp314, Scalar(2));
    _hessian(8, 7) = _tmp313 * _tmp321 + _tmp314 * _tmp322;
    _hessian(9, 7) = _tmp313 * _tmp328 + _tmp314 * _tmp329;
    _hessian(10, 7) = _tmp313 * _tmp334 + _tmp314 * _tmp335;
    _hessian(11, 7) = _tmp313 * _tmp341 + _tmp314 * _tmp342;
    _hessian(12, 7) = _tmp313 * _tmp350 + _tmp314 * _tmp351;
    _hessian(0, 8) = 0;
    _hessian(1, 8) = 0;
    _hessian(2, 8) = 0;
    _hessian(3, 8) = 0;
    _hessian(4, 8) = 0;
    _hessian(5, 8) = 0;
    _hessian(6, 8) = 0;
    _hessian(7, 8) = 0;
    _hessian(8, 8) = std::pow(_tmp321, Scalar(2)) + std::pow(_tmp322, Scalar(2));
    _hessian(9, 8) = _tmp321 * _tmp328 + _tmp322 * _tmp329;
    _hessian(10, 8) = _tmp321 * _tmp334 + _tmp322 * _tmp335;
    _hessian(11, 8) = _tmp321 * _tmp341 + _tmp322 * _tmp342;
    _hessian(12, 8) = _tmp321 * _tmp350 + _tmp322 * _tmp351;
    _hessian(0, 9) = 0;
    _hessian(1, 9) = 0;
    _hessian(2, 9) = 0;
    _hessian(3, 9) = 0;
    _hessian(4, 9) = 0;
    _hessian(5, 9) = 0;
    _hessian(6, 9) = 0;
    _hessian(7, 9) = 0;
    _hessian(8, 9) = 0;
    _hessian(9, 9) = std::pow(_tmp328, Scalar(2)) + std::pow(_tmp329, Scalar(2));
    _hessian(10, 9) = _tmp328 * _tmp334 + _tmp329 * _tmp335;
    _hessian(11, 9) = _tmp328 * _tmp341 + _tmp329 * _tmp342;
    _hessian(12, 9) = _tmp328 * _tmp350 + _tmp329 * _tmp351;
    _hessian(0, 10) = 0;
    _hessian(1, 10) = 0;
    _hessian(2, 10) = 0;
    _hessian(3, 10) = 0;
    _hessian(4, 10) = 0;
    _hessian(5, 10) = 0;
    _hessian(6, 10) = 0;
    _hessian(7, 10) = 0;
    _hessian(8, 10) = 0;
    _hessian(9, 10) = 0;
    _hessian(10, 10) = std::pow(_tmp334, Scalar(2)) + std::pow(_tmp335, Scalar(2));
    _hessian(11, 10) = _tmp334 * _tmp341 + _tmp335 * _tmp342;
    _hessian(12, 10) = _tmp334 * _tmp350 + _tmp335 * _tmp351;
    _hessian(0, 11) = 0;
    _hessian(1, 11) = 0;
    _hessian(2, 11) = 0;
    _hessian(3, 11) = 0;
    _hessian(4, 11) = 0;
    _hessian(5, 11) = 0;
    _hessian(6, 11) = 0;
    _hessian(7, 11) = 0;
    _hessian(8, 11) = 0;
    _hessian(9, 11) = 0;
    _hessian(10, 11) = 0;
    _hessian(11, 11) = std::pow(_tmp341, Scalar(2)) + std::pow(_tmp342, Scalar(2));
    _hessian(12, 11) = _tmp341 * _tmp350 + _tmp342 * _tmp351;
    _hessian(0, 12) = 0;
    _hessian(1, 12) = 0;
    _hessian(2, 12) = 0;
    _hessian(3, 12) = 0;
    _hessian(4, 12) = 0;
    _hessian(5, 12) = 0;
    _hessian(6, 12) = 0;
    _hessian(7, 12) = 0;
    _hessian(8, 12) = 0;
    _hessian(9, 12) = 0;
    _hessian(10, 12) = 0;
    _hessian(11, 12) = 0;
    _hessian(12, 12) = std::pow(_tmp350, Scalar(2)) + std::pow(_tmp351, Scalar(2));
  }

  if (rhs != nullptr) {
    Eigen::Matrix<Scalar, 13, 1>& _rhs = (*rhs);

    _rhs(0, 0) = _tmp106 * _tmp199 + _tmp107 * _tmp202;
    _rhs(1, 0) = _tmp106 * _tmp219 + _tmp107 * _tmp220;
    _rhs(2, 0) = _tmp106 * _tmp231 + _tmp107 * _tmp232;
    _rhs(3, 0) = _tmp106 * _tmp253 + _tmp107 * _tmp254;
    _rhs(4, 0) = _tmp106 * _tmp267 + _tmp107 * _tmp268;
    _rhs(5, 0) = _tmp106 * _tmp282 + _tmp107 * _tmp283;
    _rhs(6, 0) = _tmp106 * _tmp301 + _tmp107 * _tmp303;
    _rhs(7, 0) = _tmp106 * _tmp313 + _tmp107 * _tmp314;
    _rhs(8, 0) = _tmp106 * _tmp321 + _tmp107 * _tmp322;
    _rhs(9, 0) = _tmp106 * _tmp328 + _tmp107 * _tmp329;
    _rhs(10, 0) = _tmp106 * _tmp334 + _tmp107 * _tmp335;
    _rhs(11, 0) = _tmp106 * _tmp341 + _tmp107 * _tmp342;
    _rhs(12, 0) = _tmp106 * _tmp350 + _tmp107 * _tmp351;
  }
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym
