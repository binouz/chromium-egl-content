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

#ifndef UI_OZONE_PLATFORM_EGLCONTENT_GPU_MESSAGE_FILTER_H_
# define UI_OZONE_PLATFORM_EGLCONTENT_GPU_MESSAGE_FILTER_H_

#include "base/containers/id_map.h"

#include "ipc/message_filter.h"

#include "ui/gl/gl_gl_api_implementation.h"
#include "ui/gl/gl_egl_api_implementation.h"

namespace EGLContent {
  class DisplayDelegate;
}

namespace ui {

  class EGLContentDisplay;
  class EGLContentWindow;

  class EGLContentGPUMessageFilter : public IPC::MessageFilter {

    public:

      EGLContentGPUMessageFilter(EGLContent::DisplayDelegate* delegate);
      ~EGLContentGPUMessageFilter();

      // Called on the background thread to provide the filter with access to the
      // channel.  Called when the IPC channel is initialized or when AddFilter
      // is called if the channel is already initialized.
      void OnFilterAdded(IPC::Channel* channel) override;

      // Called on the background thread when the filter has been removed from
      // the ChannelProxy and when the Channel is closing.  After a filter is
      // removed, it will not be called again.
      void OnFilterRemoved() override;

      // Called to inform the filter that the IPC channel is connected and we
      // have received the internal Hello message from the peer.
      void OnChannelConnected(int32_t peer_pid) override;

      // Called when there is an error on the channel, typically that the channel
      // has been closed.
      void OnChannelError() override;

      // Called to inform the filter that the IPC channel will be destroyed.
      // OnFilterRemoved is called immediately after this.
      void OnChannelClosing() override;

      // Return true to indicate that the message was handled, or false to let
      // the message be handled in the default way.
      bool OnMessageReceived(const IPC::Message& message) override;

      EGLNativeDisplayType GetNativeDisplay();
      EGLContentWindow* GetWindow(int32_t id);
      EGLContent::DisplayDelegate* GetDisplayDelegate();

    private:

      void OnCreateDisplay();
      void OnReleaseDisplay();
      void OnCreateWindow(int32_t id);
      void OnReleaseWindow(int32_t id);

      EGLContent::DisplayDelegate* delegate_;

      IPC::Channel* channel_;

      std::unique_ptr<EGLContentDisplay> display_;
      std::map< int32_t, std::unique_ptr<EGLContentWindow> > windows_;

      base::Lock lock_;

  };

}

#endif /* !UI_OZONE_PLATFORM_EGLCONTENT_GPU_MESSAGE_FILTER.H */
