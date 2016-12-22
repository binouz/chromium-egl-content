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
