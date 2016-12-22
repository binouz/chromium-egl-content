#include <memory>
#include <iostream>

#include <eglcontent/eglcontent.h>

#include "application.h"

int main(int argc, const char **argv) {
  std::cout << "!! MAIN !!" << std::endl;
  std::unique_ptr<DemoApp> app;

  // Create our own application delegate
  app.reset(new DemoApp());

  std::cout << "EGLContent::Run" <<std::endl;
  // Now that the library is ready, let's start
  return EGLContent::Run(app.get(), argc, argv);
}
