CC = gcc
CFLAGS = -Wall -Wextra -g -lX11
SRC_DIR = ./src
BUILD_DIR = ./build
OUT = pwm

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/config.c $(SRC_DIR)/utils.c $(SRC_DIR)/window_manager.c
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

$(OUT): $(OBJ)
	$(CC) -o $(OUT) $(OBJ) $(CFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(BUILD_DIR) $(OUT)

test:
	DISPLAY=:1 ./${OUT}

screen:
	Xephyr :1 -screen 1024x768 &

install:
	sudo cp pwm /usr/local/bin
