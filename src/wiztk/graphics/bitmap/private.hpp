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

#ifndef WIZTK_GRAPHICS_BITMAP_PRIVATE_HPP_
#define WIZTK_GRAPHICS_BITMAP_PRIVATE_HPP_

#include "wiztk/graphics/bitmap.hpp"

#include "wiztk/base/property.hpp"

#include "SkBitmap.h"

namespace wiztk {
namespace graphics {

/**
 * @brief The private structure used in Bitmap
 */
struct Bitmap::Private : public base::Property<Bitmap> {

  static const Private &Get(const Bitmap &bitmap) {
    return *bitmap.p_;
  }

  explicit Private(Bitmap *owner)
      : base::Property<Bitmap>(owner) {}

  ~Private() final = default;

  SkBitmap sk_bitmap;

};

} // namespace graphics
} // namespace wiztk

#endif // WIZTK_GRAPHICS_BITMAP_PRIVATE_HPP_
