#rob = robot_opponent.c robot_opponent.h header.h
#bas = basic.c basic.h robot_opponent.h header.h
#mai = main.c  basic.h

CC = gcc -Wall
CFLAGS =
BUILD_DIR = build

#源文件目录
C_PATH = source

#中间文件名 (不带目录)
O_FILE = $(notdir $(C_FILE:.c=.o))

#源文件名 (带目录)
C_FILE = $(wildcard $(addsuffix /*.c,$(C_PATH)))

final : $(O_FILE)
	$(CC) -o $@ $(addprefix $(BUILD_DIR)/,$(O_FILE))

vpath %.c $(C_PATH)
%.o : %.c | $(BUILD_DIR)
	$(CC) -c $< -o $(BUILD_DIR)/$@

$(BUILD_DIR) :
	mkdir $(BUILD_DIR)

.PHONY : clean

clean:
	-rm -rf $(BUILD_DIR)