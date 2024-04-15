# 定义编译器和编译选项
CC = gcc
CFLAGS = -Wall -Wextra -g

# 定义根目录和子目录
ROOT_DIR := .
SERVER_DIR := server
CLIENT_DIR := client

# 定义可执行文件
SERVER_EXEC := $(SERVER_DIR)/server
CLIENT_EXEC := $(CLIENT_DIR)/client

# 定义源文件
SERVER_SRC := $(wildcard $(SERVER_DIR)/*.c)
CLIENT_SRC := $(wildcard $(CLIENT_DIR)/*.c)

# 默认目标是全部编译
all: server client

# 编译服务器程序
server: $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $(SERVER_EXEC) $(SERVER_SRC) -lpthread

# 编译客户端程序
client: $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $(CLIENT_EXEC) $(CLIENT_SRC)

# 清理编译生成的文件
clean:
	rm -f $(SERVER_EXEC) $(CLIENT_EXEC)

# 打印编译信息
.PHONY: all server client clean