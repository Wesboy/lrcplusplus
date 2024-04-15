#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <signal.h>


#include <time.h>
#include <pthread.h>

#define MAX_EVENTS  1024 //最多可以等待多少个事件
#define SERVER_PORT 8887
static char curTime[20];

// 定义客户端列表结构
typedef struct {
    int fd; // 客户端socket文件描述符
    struct sockaddr_in addr; // 客户端地址信息
} ClientInfo;

// 创建客户端列表
ClientInfo clients[MAX_EVENTS]; // 假设最大连接数与EPOLL_MAX_EVENTS相同


static int num_clients = 0;
static int server = 0;
static int epollInstance = 0;


// // 在 main 函数中调用 getcurrenttime 并打印当前时间
static char currentTime[20]; // 确保 buffer 大小足够存储时间字符串
// getcurrenttime(currentTime, sizeof(currentTime));
// printf("Current time: %s\n", currentTime);

// 获取当前时间并格式化为 "YYYY-MM-DD HH:MM:SS" 格式
void getcurrenttime(char *buffer, size_t size) {
    time_t now = time(NULL);
    sprintf(curTime, "%ld", now);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

long long printTime()
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    long long timestamp = (ts.tv_sec * 1000000000LL) + ts.tv_nsec;
    timestamp /= 1000000; // 转换为毫秒

    // printf("Current timestamp in milliseconds: %lld\n", timestamp);
    return timestamp;
}


void send_file_to_client(int client_fd, const char *filename) ;

// 声明信号处理函数
void signal_handler(int signum);


// 定义信号处理函数
void signal_handler(int signum)
{
        printf("Caught SIGINT, int:%d\n", signum);
    if (signum == SIGINT) {
        printf("Caught SIGINT, cleaning up...\n");
        

        for (int i = 0; i < num_clients; i++) {
            if(clients[i].fd != -1)
            {
                printf("client:%d close\n", i);
                close(clients[i].fd);
            }
        }

        // 关闭服务器socket
        close(epollInstance); // 注意：这里应该是关闭客户端的socket，而不是epoll实例
        close(server);
        
        // 取消绑定（如果有必要）
        // 注意：取消绑定通常是在关闭socket之后进行的，因为取消绑定会使得所有在该socket上的监听和连接都失效
        
        printf("Server is shutting down...\n");
        // 如果需要取消绑定，可以在这里添加代码
        
        // 退出程序
        exit(0);
    }
}


//创建一个线程任务
void *thread_task(void *arg) {
    if(arg == NULL)
        return NULL;
    int curId = *(int *)arg;
    long long curTime = printTime();
    long long endTime;

    // getcurrenttime(currentTime, sizeof(currentTime));
    // printf("thread_task time: %s.%d\n", currentTime, curTime);
    // send_file_to_client(curId, "test/00_small_1.jpg");
    send_file_to_client(curId, "test/big_bmp_1.bmp");
    endTime = printTime();
    // getcurrenttime(currentTime, sizeof(currentTime));
    printf("client:%d thread_task startTime:%ld end:%ld cast: %ldms\n", curId,curTime, endTime, endTime - curTime);

    return NULL;
}

// 向特定客户端发送消息的函数
int send_to_client(int client_fd, const char *message) {
    for (int i = 0; i < num_clients; i++) {
        if (clients[i].fd == client_fd) {
            // 找到客户端，发送消息
            int len = strlen(message);
            if (send(client_fd, message, len, 0) == -1) {
                perror("send");
                return -1; // 发送失败
            }
            return 0; // 发送成功
        }
    }
    return -1; // 未找到客户端
}


// 向特定客户端发送消息的函数
int send_to_all_client(const char *message) {
    for (int i = 0; i < num_clients; i++) {
        // 找到客户端，发送消息
        int len = strlen(message);
        if (send(clients[i].fd, message, len, 0) == -1) {
            perror("send");
            return -1; // 发送失败
        }
    }
    return 0; // 未找到客户端
}


// 向特定客户端发送消息的函数
int send_to_file() {
    for (int i = 0; i < num_clients; i++) {
        //创建thread_task线程
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, thread_task, &clients[i].fd);
    }
    return 0; // 未找到客户端
}

// 新连接处理函数，这里简单打印连接信息，实际应用中可能包含更多复杂的业务逻辑
void handle_new_connection(int client_sock, struct sockaddr_in* client_addr) {
    // 实际应用中在此处读取客户端数据并进行处理
    if(num_clients < MAX_EVENTS)
    {
        clients[num_clients].fd = client_sock;
        clients[num_clients].addr = *client_addr;
        num_clients++;
    }
    printf("[%d]+++New connection from %s:%d\n", num_clients,
           inet_ntoa(client_addr->sin_addr),
           ntohs(client_addr->sin_port));
}


// 创建控制台读取线程
static void consoleReadThread(void *arg)
{
    char *input = NULL;
    size_t inputSize = 0;
    ssize_t bytesRead;
    printf("Enter hexadecimal data (e.g., FF FE 33 FF 44 99). Enter 'Q' to quit.\n");

    while (1) {
        printf("[PID:%d]> ",getpid());

        // 从标准输入读取一行数据
        bytesRead = getline(&input, &inputSize, stdin);

        if (bytesRead == -1) {
            perror("Error reading input");
            break;
        }

        // 去除字符串末尾的换行符
        if (bytesRead > 0 && input[bytesRead - 1] == '\n') {
            input[bytesRead - 1] = '\0';
            bytesRead--;
        }

        // 将输入的十六进制数据转换并打印
        if (strcasecmp(input, "Q") == 0) {
            // 如果输入是 'Q'，退出循环
            break;
        } else {
            char *token = strtok(input, " ");
            while (token != NULL) {
                unsigned int hexValue;
                if (sscanf(token, "%x", &hexValue) == 1) {
                    printf("Hex Value: 0x%02X\n", hexValue);
                    if(hexValue == 0x5D)
                    {
                        //给所有给客户端都发送
                        // send_to_all_client("test+3");
                        send_to_file();
                    }
                } else {
                    printf("Invalid input: %s\n", token);
                }
                token = strtok(NULL, " ");
            }
        }
    }


    // 释放内存
    free(input);
    
}

void create_console()
{
    //创建控制台读取线程
    pthread_t console_thread;
    pthread_create(&console_thread, NULL, consoleReadThread, NULL);

}


int main()
{
    struct sockaddr_in saddr = {0};
    int client = 0;
    struct sockaddr_in caddr = {0};
    socklen_t asize = 0;
    int len = 0;
    char buf[32] = {0};
    int maxfd;
    int ret = 0;
    int i = 0;

    
    signal(SIGINT, signal_handler);

    server = socket(PF_INET, SOCK_STREAM, 0);

    if( server == -1 )
    {
        printf("server socket error\n");
        return -1;
    }

    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(SERVER_PORT);
    
    // 打印socket创建后的IP地址和端口
    printf("Server socket created successfully. IP: %s, Port: %d\n", inet_ntoa(saddr.sin_addr), ntohs(saddr.sin_port));

    if( bind(server, (struct sockaddr*)&saddr, sizeof(saddr)) == -1 )
    {
        printf("server bind error\n");
        return -1;
    }

    if( listen(server, 128) == -1 )
    {
        printf("server listen error\n");
        return -1;
    }

    printf("server start success\n");


    struct epoll_event event, events[MAX_EVENTS];
    /*创建epoll*/
    epollInstance = epoll_create1(0);
    if (epollInstance == -1) 
    {
        printf("Failed to create epoll instance\n");
    }
    /*将服务器添加进入event中*/
    event.events = EPOLLIN;
    event.data.fd = server;

    if (epoll_ctl(epollInstance, EPOLL_CTL_ADD, server, &event) == -1) 
    {
        printf("Failed to add server socket to epoll instance");
    }      


    create_console();


    while( 1 )
    {        
        int numEventsReady = epoll_wait(epollInstance, events, MAX_EVENTS, -1);
        if (numEventsReady == -1) 
        {
            printf("Failed to wait for events");
            return -1;
        }

        for(i = 0; i < numEventsReady; i++)
        {
            if(events[i].data.fd == server)
            {
                /*有客户端连接上来了*/
                asize = sizeof(caddr);  
                client = accept(server, (struct sockaddr*)&caddr, &asize);
                // printf("client is connect\n");
                        // 打印客户端的IP地址和端口
                // printf("Client connected. IP: %s, Port: %d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));

                event.events = EPOLLIN | EPOLLET;
                event.data.fd = client;

                if (epoll_ctl(epollInstance, EPOLL_CTL_ADD, client, &event) == -1) 
                {
                    printf("Failed to add client socket to epoll instance");
                    return -1;
                }
            
                // 调用回调函数处理新连接
                handle_new_connection(client, &caddr);                
            }
            else
            {
                memset(buf, 0, sizeof(buf));
                /*处理客户端的请求*/
                len = read(events[i].data.fd, buf, 1024);
                if(len == 0)
                {
                    printf("client is disconnect\n");
                    close(events[i].data.fd);
                     for (int j = 0; j < num_clients; j++) {
                        if (clients[j].fd == events[i].data.fd) {
                            clients[j].fd = -1; // 标记为断开
                            num_clients--;
                            
                            printf("client num_clients--:%d\n", num_clients);
                            break;
                        }
                    }
                }
                else
                {
                    printf("(%d)========recv : %s\n", len, buf);
                    
                    send(events[i].data.fd, buf, len, 0);

                }
            }
        }        


    }
    
    close(epollInstance); // 注意：这里应该是关闭客户端的socket，而不是epoll实例
    close(server);

    return 0;
}


//发送文件给客户端
void send_file_to_client(int client_fd, const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("fopen");
        return;
    }

    char buf[1024];
    int len;
    while ((len = fread(buf, 1, sizeof(buf), fp)) > 0) {
        if (send(client_fd, buf, len, 0) == -1) {
            perror("send");
            break;
        }
    }

    fclose(fp);
}

