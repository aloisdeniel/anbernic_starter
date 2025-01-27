CC = gcc
CFLAGS := $(shell pkg-config --cflags --libs sdl2)
LDFLAGS  := $(shell sdl2-config --libs)
TARGET = cube

ANBERNIC_IP = root@192.168.1.28
ROM_DIR = /userdata/roms/tools/

all: $(TARGET)

$(TARGET): 
	mkdir -p build
	$(CC) cube.c -o build/$(TARGET) $(CFLAGS) $(LDFLAGS) -lm
	echo '#!/bin/bash\n\nDIR="$$(dirname "$$(readlink -f "$$0")")"\n\ncd $$DIR\n./$(TARGET)' > build/$(TARGET).sh

clean:
	rm -f build/$(TARGET)
	rm -f build/$(TARGET).sh

deploy: 
	scp ./build/$(TARGET) ./build/$(TARGET).sh $(ANBERNIC_IP):$(ROM_DIR)
