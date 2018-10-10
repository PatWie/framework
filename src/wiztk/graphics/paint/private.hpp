/*
 * Copyright 2017 - 2018 The WizTK Authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef WIZTK_GRAPHICS_PAINT_PRIVATE_HPP_
#define WIZTK_GRAPHICS_PAINT_PRIVATE_HPP_

#include "wiztk/graphics/paint.hpp"

#include "SkPaint.h"
#include "SkTypeface.h"

namespace wiztk {
namespace graphics {

struct Paint::Private {

  static const Private &Get(const Paint &paint) {
    return *paint.p_;
  }

  Private() = default;

  Private(const Private &) = default;

  ~Private() = default;

  Private &operator=(const Private &) = default;

  SkPaint sk_paint;

};

} // namespace graphics
} // namespace wiztk

#endif // WIZTK_GRAPHICS_PAINT_PRIVATE_HPP_
