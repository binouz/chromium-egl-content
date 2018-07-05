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

#include <string>
#include <iostream>

#include "browser_delegate.h"

DemoBrowserDelegate::DemoBrowserDelegate() {
}

DemoBrowserDelegate::~DemoBrowserDelegate() {
}

void DemoBrowserDelegate::BrowserCreated(
  EGLContent::BrowserDelegate::Controller* controller) {
  cmd_interface_.Initialise(controller);
}

void DemoBrowserDelegate::LoadingStateChanged(bool loading) {
  cmd_interface_.LoadingStateChanged(loading);
}

void DemoBrowserDelegate::LoadProgressed(double progress) {
  cmd_interface_.LoadProgressed(progress);
}

void DemoBrowserDelegate::TargetURLChanged(std::string& url) {
  cmd_interface_.TargetURLChanged(url);
}
