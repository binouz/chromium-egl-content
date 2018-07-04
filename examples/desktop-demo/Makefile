TOPDIR                 ?= ../..
BUILD_OUTPUT_DIRECTORY ?= examples/desktop-demo
OUTPUT_DIRECTORY        = $(TOPDIR)/$(BUILD_OUTPUT_DIRECTORY)/eglcontent-desktop-demo

SOURCES   = application.cc display_delegate.cc main_delegate.cc
SOURCES  += browser_delegate.cc main.cc
OBJS      = $(SOURCES:.cc=.o)
C_FLAGS   = $(CFLAGS) -std=c++11 -I$(TOPDIR)/$(BUILD_OUTPUT_DIRECTORY) -g -ggdb
LD_FLAGS  = $(LDFLAGS) -L$(TOPDIR)/$(BUILD_OUTPUT_DIRECTORY)
LD_FLAGS += -legl_content_lib -lEGL -lGLESv2 -lX11
TARGET    = egl_content_demo

all: $(OUTPUT_DIRECTORY) $(OBJS) $(TARGET)

$(OUTPUT_DIRECTORY):
	mkdir $@

$(TARGET): $(OBJS)
	cd $(OUTPUT_DIRECTORY) && $(CXX) $(OBJS) $(LD_FLAGS) \
		-o $(TOPDIR)/$(BUILD_OUTPUT_DIRECTORY)/$(TARGET)

%.o : %.cc
	$(CXX) $(C_FLAGS) -c $< -o $(OUTPUT_DIRECTORY)/$@

clean:
	rm -rf *.o $(TARGET)
