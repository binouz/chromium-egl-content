#ifndef DISPLAY_DELEGATE_H_
# define DISPLAY_DELEGATE_H_

#include <eglcontent/display_delegate.h>

#define X_DISPLAY_NAME "EGLContent DemoApp"

class DemoDisplayDelegate: public EGLContent::DisplayDelegate {

  public:

    DemoDisplayDelegate(int width, int height);
    ~DemoDisplayDelegate();

    EGLNativeDisplayType CreateNativeDisplay() override;
    void ReleaseNativeDisplay() override;

    EGLNativeWindowType CreateNativeWindow() override;
    void ReleaseNativeWindow() override;

    bool Resize(int size, int height, float scale_factor) override;

    void GetSize(int* width, int* height) override;

    char* EGLLibraryName() override;
    char* GLESLibraryName() override;

  private:

    int width_;
    int height_;

    Display *x_display_;
    Window x_window_;

};

#endif /* !DISPLAY_DELEGATE.H */
