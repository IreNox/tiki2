#pragma once

// This file contains settings used by all the applications, for connecting
// to the Visual Remote Debugger (VRD). Edit this file to make the apps connect to the computer running the VRD application.
#include "NxRemoteDebugger.h"

//Set this to 0 to stop the app from trying to connect to the VRD
#define USE_VRD 0

//Change this setting to the IP number or DNS name of the computer that is running the VRD
#define VRD_HOST "localhost"

//Change this setting to the port on which the VRD is listening, or keep the default: NX_DBG_DEFAULT_PORT = 5425
#define VRD_PORT NX_DBG_DEFAULT_PORT

//Change this setting to decide what type of information is sent to the VRD. Default: NX_DBG_EVENTMASK_EVERYTHING
#define VRD_EVENTMASK NX_DBG_EVENTMASK_EVERYTHING