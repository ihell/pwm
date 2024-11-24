CC = gcc
CFLAGS = -Wall -Wextra -lX11 -lXrandr -lXinerama -lXi -lXtst
SRC_DIR = ./src
BUILD_DIR = ./build
OUT = rafwm

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/config.c $(SRC_DIR)/window_manager.c $(SRC_DIR)/utils.c
OBJ = $(BUILD_DIR)/main.o $(BUILD_DIR)/config.o $(BUILD_DIR)/window_manager.o $(BUILD_DIR)/utils.o

$(OUT): $(OBJ)
	$(CC) -o $(OUT) $(OBJ) $(CFLAGS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c
	mkdir -p $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.o $(CFLAGS)

$(BUILD_DIR)/config.o: $(SRC_DIR)/config.c
	$(CC) -c $(SRC_DIR)/config.c -o $(BUILD_DIR)/config.o $(CFLAGS)

$(BUILD_DIR)/window_manager.o: $(SRC_DIR)/window_manager.c
	$(CC) -c $(SRC_DIR)/window_manager.c -o $(BUILD_DIR)/window_manager.o $(CFLAGS)

$(BUILD_DIR)/utils.o: $(SRC_DIR)/utils.c
	$(CC) -c $(SRC_DIR)/utils.c -o $(BUILD_DIR)/utils.o $(CFLAGS)

clean:
	rm -rf $(BUILD_DIR) $(OUT)
test:
	DISPLAY=:1 ./rafwm
screen:
	 Xephyr :1 -screen 1024x768 &
install:
	sudo cp ./rafwm /usr/local/bin
