// Copyright 2017 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef GAMMA_CORRECT_H_
#define GAMMA_CORRECT_H_

#include <cmath>

#include "compiler_specific.h"

namespace pik {

// Values are in [0, 255].
static PIK_INLINE double Srgb8ToLinearDirect(double srgb8) {
  if (srgb8 <= 0.0) return 0.0;
  if (srgb8 <= 10.31475) return srgb8 / 12.92;
  if (srgb8 >= 255.0) return 255.0;
  const double srgb01 =srgb8 / 255.0;
  const double linear01 = std::pow((srgb01 + 0.055) / 1.055, 2.4);
  return linear01 * 255.0;
}

// Values are in [0, 255].
static PIK_INLINE double LinearToSrgb8Direct(double linear) {
  if (linear <= 0.0) return 0.0;
  if (linear >= 255.0) return 255.0;
  if (linear <= 10.31475 / 12.92) return linear * 12.92;
  const double linear01 = linear / 255.0;
  const double srgb01 = std::pow(linear01, 1.0 / 2.4) * 1.055 - 0.055;
  return srgb01 * 255.0;
}

}  // namespace pik

#endif  // GAMMA_CORRECT_H_
