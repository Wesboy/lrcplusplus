/*
 * @Author: flywes bg_weapon@163.com
 * @Date: 2024-04-12 14:58:06
 * @LastEditors: flywes bg_weapon@163.com
 * @LastEditTime: 2024-04-15 18:21:21
 * @FilePath: \TinyWebServer\client.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "192.168.79.128"
// #define SERVER_IP "192.168.1.105"
#define SERVER_PORT 8887

int main() {
    // 创建socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    // 服务器地址信息
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 连接到服务器
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(client_socket);
        return EXIT_FAILURE;
    }

    // 构造HTTP请求
    char *request = "eSee";

    // 发送请求
    if (send(client_socket, request, strlen(request), 0) == -1) {
        perror("Send failed");
        close(client_socket);
        return EXIT_FAILURE;
    }
    printf("send ok:\n" );

    // 接收响应
    char buffer[1024];
    int bytes_received;
    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
                    /*对接收到的数据进行处理*/
        printf("(%d)========recv : %s\n", bytes_received, buffer );
    }
    if (bytes_received == -1) {
        perror("Receive failed");
    }

    // 关闭socket连接
    close(client_socket);

    return EXIT_SUCCESS;
}
