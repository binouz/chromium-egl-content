SOURCES=application.cc display_delegate.cc main_delegate.cc browser_delegate.cc main.cc
OBJS=$(SOURCES:.cc=.o)
TARGET=egl_content_demo
C_FLAGS=$(CFLAGS) -std=c++11 -I../../out -I../../out/chromium -g -ggdb
LD_FLAGS=$(LDFLAGS) -L../../out -legl_content_lib -lEGL -lGLESv2 -lX11

all: $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LD_FLAGS) -o $(TARGET)

%.o : %.cc
	$(CXX) $(C_FLAGS) -c $< -o $@

clean:
	rm -rf *.o $(TARGET)
