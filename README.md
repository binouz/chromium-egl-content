CHROMIUM EGL FRAMEWORK
----------------------

Objectives
==========

The goal of this project is to provide an HTML5 based user interface library using chromium content module and aura.
Its main feature is to provide the ability to create native applications with (at least) all the UI handled using web technologies.
There is mainy other project today to do so but mainly for desktop, therefore this project will be focusing on embedded multimedia devices with a GPU supporting OpenGLES and EGL.
As there is a lot of different chipsets and devices in the world today, this library will have to be portable easily, that's why we propose such an architecture for the resulting app :

```
+-----------+
| HTML5 APP |
+-----------+
|  LIBRARY  |
+-----------+
| LAUNCHER  |
+-----------+
```

The goal of this architecture is to leave the SoC specific code out of the library : A set of delegates will be exposed to the launcher to be implemented by the end developer, such as EGL specifics but also media acceleration if available.
The launcher is not part of the library but we will try to provide as mainy examples as possible.

COMPILE
=======

```
> make
```


GN_EXTRA_ARGS
-------------

This environment variable enable to pass extra GN arguments to configure the build, such as :

```
enable_ac3_eac3_audio_demuxing
enable_hevc_demuxing
enable_mdns
enable_mse_mpeg2ts_stream_parser
enable_webrtc
enable_widevine
ffmpeg_branding
media_use_ffmpeg
media_use_libvpx
proprietary_codecs
use_alsa
is_debug
target_cpu
arm_version
arm_tune
arm_use_neon
target_sysroot
```

Please refer to chromium GN files for each argument usage.


Cross compiliation
------------------

By default, build is configured for x64.
For other targets, set environment variables accordingly.

* CC, CXX, AR, LD for the toolchain
* GN_EXTRA_ARGS for chromium build configuration

This is an example for an arm target :

```
> export CC=arm-linux-gnu-gcc
> export CXX=arm-linux-gnu-g++
> export AR=arm-linux-gnu-ar
> export LD=arm-linux-gnu-ld
> export GN_EXTRA_ARGS="              \
    target_cpu="arm"                  \
    arm_version="7"                   \
    arm_tune="cortex-a7"              \
    arm_use_neon=true                 \
    target_sysroot="/opt/arm-sysroot" \
  "
> make
```

TODO
====

* Configure script to compile content module and aura
* Implement required code :
  * Generic ozone platform
* Make patches if necessary
* Define delegate to export
  * Ozone interface
* Implement launcher with mesa and gstreamer
* Develop small TV UI in JS
