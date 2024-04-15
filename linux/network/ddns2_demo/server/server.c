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

#define MAX_EVENTS  1024 //最多可以等待多少个事件
#define SERVER_PORT 8887

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




// 声明信号处理函数
void signal_handler(int signum);


// 定义信号处理函数
void signal_handler(int signum)
{
        printf("Caught SIGINT, int:%d\n", signum);
    if (signum == SIGINT) {
        printf("Caught SIGINT, cleaning up...\n");
        
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
                printf("client is connect\n");
                        // 打印客户端的IP地址和端口
                printf("Client connected. IP: %s, Port: %d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));

                event.events = EPOLLIN | EPOLLET;
                event.data.fd = client;

                if (epoll_ctl(epollInstance, EPOLL_CTL_ADD, client, &event) == -1) 
                {
                    printf("Failed to add client socket to epoll instance");
                    return -1;
                }                
            }
            else
            {
                /*处理客户端的请求*/
                len = read(events[i].data.fd, buf, 1024);
                if(len == 0)
                {
                    printf("client is disconnect\n");
                    close(events[i].data.fd);
                     for (int j = 0; j < num_clients; j++) {
                        if (clients[j].fd == events[i].data.fd) {
                            clients[j].fd = -1; // 标记为断开
                            break;
                        }
                    }
                }
                else
                {
                    /*对接收到的数据进行处理*/
                    printf("(%d)========recv : %s\n", len, buf);
                    write(events[i].data.fd, buf, len);
                }
            }
        }        


    }
    
    close(epollInstance); // 注意：这里应该是关闭客户端的socket，而不是epoll实例
    close(server);

    return 0;
}


