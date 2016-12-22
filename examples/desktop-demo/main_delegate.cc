#include "main_delegate.h"

#include <eglcontent/browser_host.h>

#include <iostream>

DemoMainDelegate::DemoMainDelegate() {
}

DemoMainDelegate::~DemoMainDelegate() {
}

void DemoMainDelegate::OnStartupComplete() {
  std::cout << "DemoMainDelegate::OnStartupComplete" << std::endl;
}

void DemoMainDelegate::BeforeSandboxing() {
  std::cout << "DemoMainDelegate::BeforeSandboxing" << std::endl;
}

void DemoMainDelegate::AfterSandboxing() {
  std::cout << "DemoMainDelegate::AfterSandboxing" << std::endl;
}

