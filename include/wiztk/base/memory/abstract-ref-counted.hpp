/*
 * Copyright 2017 The WizTK Authors.
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

#ifndef WIZTK_BASE_MEMORY_ABSTRACT_REF_COUNT_HPP_
#define WIZTK_BASE_MEMORY_ABSTRACT_REF_COUNT_HPP_

namespace wiztk {
namespace base {
namespace memory {

/**
 * @ingroup base_memory
 * @brief Abstract class with reference count.
 */
class AbstractRefCounted {

 public:

  struct DefaultDeleter {

    template<typename T>
    void operator()(T *p) {
      delete p;
    }

  };

  AbstractRefCounted() = default;

  virtual ~AbstractRefCounted() = default;

 protected:

  virtual void Reference() = 0;

  virtual void Unreference() = 0;

  virtual void Destroy() = 0;

};

} // namespace memory
} // namespace base
} // namespace wiztk

#endif // WIZTK_BASE_MEMORY_ABSTRACT_REF_COUNT_HPP_
