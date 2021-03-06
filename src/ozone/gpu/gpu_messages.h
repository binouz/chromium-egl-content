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

#include "ipc/ipc_message_macros.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT

#define IPC_MESSAGE_START OzoneGpuMsgStart

// Browser => GPU
IPC_MESSAGE_CONTROL0(EGLContentMsg_CreateDisplay)
IPC_MESSAGE_CONTROL0(EGLContentMsg_ReleaseDisplay)
IPC_MESSAGE_CONTROL1(EGLContentMsg_CreateWindow, int32_t /* ID */)
IPC_MESSAGE_CONTROL1(EGLContentMsg_ReleaseWindow, int32_t /* ID */)

// GPU => Browser
