#include <string>
#include <iostream>

#include "browser_delegate.h"

DemoBrowserDelegate::DemoBrowserDelegate() {
  std::cout << "DemoBrowserDelegate::DemoBrowserDelegate" << std::endl;
}

DemoBrowserDelegate::~DemoBrowserDelegate() {
}

void DemoBrowserDelegate::BrowserCreated(
  EGLContent::BrowserDelegate::Controller* controller) {
  std::cout << "DemoBrowserDelegate::BrowserCreated" << std::endl;
  std::string url("http://www.google.com/");
  controller->LoadURL(url);
}
