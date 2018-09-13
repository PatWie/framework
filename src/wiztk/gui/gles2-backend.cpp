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

#include "gles2-backend/private.hpp"
#include "abstract-egl-backend/private.hpp"

#include "wiztk/gui/application.hpp"

#include "display/proxy.hpp"

namespace wiztk {
namespace gui {

GLES2Backend::GLES2Backend()
    : AbstractEGLBackend() {
  p_ = std::make_unique<Private>();

//  Display *display = Application::GetInstance()->GetDisplay();
//  p_->wl_egl_window = wl_egl_window_create(Proxy::GetWaylandSurface(surface), 400, 300);
//  p_->egl_surface = eglCreatePlatformWindowSurface(AbstractEGLBackend::p_->egl_display,
//                                                   AbstractEGLBackend::p_->egl_display,
//                                                   p_->wl_egl_window,
//                                                   nullptr);
}

GLES2Backend::~GLES2Backend() {
//  _ASSERT(nullptr != p_->egl_surface);
//  _ASSERT(nullptr != p_->wl_egl_window);
//  Display *display = Application::GetInstance()->GetDisplay();
//  eglDestroySurface(Display::Proxy::egl_display(display), p_->egl_surface);
//  wl_egl_window_destroy(p_->wl_egl_window);
}

} // namespace gui
} // namespace wiztk