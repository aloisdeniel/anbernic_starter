CC = gcc
CFLAGS := $(shell pkg-config --cflags --libs sdl2)
LDFLAGS  := $(shell sdl2-config --libs)
TARGET = cube

ANBERNIC_IP = root@192.168.1.31 # Pass the real IP as an argument
ROM_DIR = userdata/roms/tools # The target dir (example based on Knulli here)

all: $(TARGET)

$(TARGET): 
	mkdir build
	$(CC) $(CFLAGS) cube.c -Wall -o build/$(TARGET) $(LDFLAGS)
	echo '#!/bin/bash\n\nDIR="\$(dirname "\$(readlink -f "\$0")")"\n\ncd \$DIR\n./$(TARGET)' > build/$(TARGET).sh

clean:
	rm -f build/$(TARGET)
	rm -f build/$(TARGET).sh

deploy: 
	scp ./build/$(TARGET) ./build/$(TARGET).sh $(ANBERNIC_IP):/$(ROM_DIR)
