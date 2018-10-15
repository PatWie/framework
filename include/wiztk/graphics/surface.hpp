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

#ifndef WIZTK_GRAPHIC_SURFACE_HPP_
#define WIZTK_GRAPHIC_SURFACE_HPP_

#include <memory>

namespace wiztk {
namespace graphics {

// Forward declarations
class Canvas;
class ImageInfo;

enum PixelGeometryType {
  kPixelGeometryUnknown,
  kPixelGeometry_RGB_H,
  kPixelGeometry_BGR_H,
  kPixelGeometry_RGB_V,
  kPixelGeometry_BGR_V
};

/**
 * @ingroup graphics
 * @brief A class responsible for managing the pixels that a canvas draws into
 *
 */
class Surface {

 public:

  class Properties;

  struct Private;

  Surface(const Surface &) = delete;
  Surface &operator=(const Surface &) = delete;

  /**
   * @brief Create a new surface object, using the specified pixels/rowbytes as its backend
   * @param pixels
   * @param row_bytes
   * @return
   */
  static Surface CreateRasterDirect(const ImageInfo &image_info,
                                    void *pixels,
                                    size_t row_bytes,
                                    const Properties *props = nullptr);

  static Surface CreateRaster(const ImageInfo &image_info,
                              size_t row_bytes,
                              const Properties *props = nullptr);

  Surface(Surface &&other) noexcept;

  Surface &operator=(Surface &&other) noexcept;

  virtual ~Surface();

 protected:

  Surface();

 private:

  std::unique_ptr<Private> p_;

};

class Surface::Properties {

 public:

  Properties(const Properties &other) = delete;
  Properties &operator=(const Properties &other) = delete;

  struct Private;

  Properties();

  Properties(uint32_t flags);

  Properties(Properties &&other) noexcept;

  ~Properties();

  Properties &operator=(Properties &&other) noexcept;

 private:

  std::unique_ptr<Private> p_;

};

} // namespace graphics
} // namespace wiztk

#endif //WIZTK_LAYER_HPP
