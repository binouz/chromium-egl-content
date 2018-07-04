// Copyright 2018 Aubin REBILLAT
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "display_delegate.h"

#include <iostream>

DemoDisplayDelegate::DemoDisplayDelegate(int width, int height)
  : width_(width), height_(height) {
  EGLint egl_major, egl_minor;
  /* FIXME : ASSERT display_ != NULL */
}

DemoDisplayDelegate::~DemoDisplayDelegate() {
}

EGLNativeDisplayType DemoDisplayDelegate::CreateNativeDisplay() {
  std::cout << "DemoDisplayDelegate::" << __FUNCTION__ << std::endl;
  x_display_ = XOpenDisplay(NULL);
  return x_display_;
}

void DemoDisplayDelegate::ReleaseNativeDisplay() {
}

EGLNativeWindowType DemoDisplayDelegate::CreateNativeWindow() {
  std::cout << "DemoDisplayDelegate::" << __FUNCTION__ << std::endl;
  int num_visuals, screen;
  unsigned long mask;
  Window root;
  XSetWindowAttributes attr;
  XVisualInfo *visInfo, visTemplate;
  XSizeHints sizehints;
  EGLint num_configs, visual_id;

  screen = DefaultScreen(x_display_);
  root = RootWindow(x_display_, screen);
  x_window_ = XCreateSimpleWindow(x_display_, root, 0, 0, width_, height_, 0, 2,
                                  BlackPixel(x_display_, screen));
  XMapWindow(x_display_, x_window_);

  return x_window_;
}

void DemoDisplayDelegate::ReleaseNativeWindow() {
  std::cout << "DemoDisplayDelegate::" << __FUNCTION__ << std::endl;
}

bool DemoDisplayDelegate::Resize(int size, int height, float scale_factor) {
  std::cout << "DemoDisplayDelegate::" << __FUNCTION__ << std::endl;
}

void DemoDisplayDelegate::GetSize(int* width, int* height) {
  std::cout << "DemoDisplayDelegate::" << __FUNCTION__ << std::endl;
  *width = width_;
  *height = height_;
}

char *DemoDisplayDelegate::EGLLibraryName() {
  std::cout << "DemoDisplayDelegate::" << __FUNCTION__ << std::endl;
#ifdef USE_NVIDIA
  return "libEGL_nvidia.so.0";
#else
  return "libEGL.so.1";
#endif
}

char *DemoDisplayDelegate::GLESLibraryName() {
  std::cout << "DemoDisplayDelegate::" << __FUNCTION__ << std::endl;
#ifdef USE_NVIDIA
  return "libGLESv2_nvidia.so.367.57";
#else
  return "libGLESv2.so.2";
#endif
}
