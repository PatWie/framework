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

#include "wiztk/net/socket.hpp"

#include "wiztk/base/property.hpp"

#include "wiztk/net/ip-address.hpp"

#include <sys/socket.h>
#include <unistd.h>

namespace wiztk {
namespace net {

Socket::Socket()
    : socket_(0) {

}

Socket::Socket(const String &host, int port)
    : Socket() {

}

Socket::~Socket() {
  if (socket_) {
    close(socket_);
  }
}

} // namespace net
} // namespace wiztk
