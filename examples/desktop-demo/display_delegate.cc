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

#ifdef USE_NVIDIA
static std::string kLibEGLName = "libEGL_nvidia.so.0";
static std::string kLibGLESName = "libGLESv2_nvidia.so.367.57";
#else
static std::string kLibEGLName =  "libEGL.so.1";
static std::string kLibGLESName = "libGLESv2.so.2";
#endif


DemoDisplayDelegate::DemoDisplayDelegate(int width, int height)
  : width_(width), height_(height) {
}

DemoDisplayDelegate::~DemoDisplayDelegate() {
}

EGLNativeDisplayType DemoDisplayDelegate::CreateNativeDisplay() {
  x_display_ = XOpenDisplay(NULL);
  return x_display_;
}

void DemoDisplayDelegate::ReleaseNativeDisplay() {
}

EGLNativeWindowType DemoDisplayDelegate::CreateNativeWindow() {
  int screen;
  Window root;

  screen = DefaultScreen(x_display_);
  root = RootWindow(x_display_, screen);
  x_window_ = XCreateSimpleWindow(x_display_, root, 0, 0, width_, height_, 0, 2,
                                  BlackPixel(x_display_, screen));
  XMapWindow(x_display_, x_window_);

  return x_window_;
}

void DemoDisplayDelegate::ReleaseNativeWindow() {
}

bool DemoDisplayDelegate::Resize(int size, int height, float scale_factor) {
  return true;
}

void DemoDisplayDelegate::GetSize(int* width, int* height) {
  *width = width_;
  *height = height_;
}

const char *DemoDisplayDelegate::EGLLibraryName() {
  return kLibEGLName.c_str();
}

const char *DemoDisplayDelegate::GLESLibraryName() {
  return kLibGLESName.c_str();
}
