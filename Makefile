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
	make -C examples/desktop-demo

#install: all
#	install -d out/eglcontent /usr/include
#	install -d out/chromium /usr/include
#	install out/lib/libegl_content_lib.so /usr/lib

clean:
	rm -rf out
	rm -rf $(TOPDIR)/$(CHROMIUM_CHECKOUT)
