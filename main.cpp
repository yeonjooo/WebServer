#include <iostream>
#ifdef WIN32
#include <WinSock2.h>
#else
#include <netinet/in.h>
#include <sys/socket.h>
#endif

#define BACKLOGSIZE 5
#define BUFSIZE 30
#define PORTNUM 8080

int main(int argc, char **argv)
{
    std::cout<<"Start Server Process!" << std::endl;

#ifdef WIN32
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2,2), &wsadata);
#endif

    SOCKET server_sock = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, 0, 0);

    SOCKADDR_IN server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORTNUM);
    if (bind(server_sock, (SOCKADDR*)&server_addr, sizeof(SOCKADDR_IN)) < 0) {
        std::cout << "Error while binding.." << std::endl;
        return -1;
    }
    listen(server_sock, BACKLOGSIZE);

    SOCKADDR_IN clientAddr;
    int len;
    SOCKET client_sock = accept(server_sock, (SOCKADDR*)&clientAddr, &len);

    char buf[BUFSIZE];
    memset(buf, 0, sizeof(buf));
    int n = recv(client_sock, buf, BUFSIZE - 1, 0);
    std::cout << "read buf : " << buf << "(" << n << ")" << std::endl;

    WSACleanup();
    return 0;
}
