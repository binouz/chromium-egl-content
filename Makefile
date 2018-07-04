# Copyright 2018 Aubin REBILLAT
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

ifeq (,$(findstring depot_tools,$(PATH)))
$(error "Can't find depot_tools in your path")
endif

TOPDIR = $(CURDIR)
VERSION = $(shell cat $(TOPDIR)/config/CHROMIUM_VERSION)
CHROMIUM_CHECKOUT ?= chromium
BUILD_OUTPUT_DIRECTORY ?= out

all: fetch prepare configure build

fetch:
	@./tools/fetch.sh $(TOPDIR) $(CHROMIUM_CHECKOUT) $(VERSION)

prepare:
	@./tools/prepare.sh $(TOPDIR) $(CHROMIUM_CHECKOUT) $(VERSION)

configure:
	@./tools/configure.sh $(TOPDIR) $(CHROMIUM_CHECKOUT) $(VERSION) \
		$(BUILD_OUTPUT_DIRECTORY)

build:
	@ninja -C out egl_content_lib

export:
	@./tools/export_headers.sh $(TOPDIR) $(CHROMIUM_CHECKOUT) $(VERSION) \
		$(BUILD_OUTPUT_DIRECTORY)

examples:
	make -C examples/desktop-demo TOPDIR=$(TOPDIR) \
		BUILD_OUTPUT_DIRECTORY=$(BUILD_OUTPUT_DIRECTORY)

#install: all
#	install -d out/eglcontent /usr/include
#	install -d out/chromium /usr/include
#	install out/lib/libegl_content_lib.so /usr/lib

clean:
	rm -rf out
	rm -rf $(TOPDIR)/$(CHROMIUM_CHECKOUT)

.PHONY: examples
