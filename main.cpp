#include <iostream>
#ifdef WIN32
#include <WinSock2.h>
#else
#include <sys/socket.h>
#endif
int main()
{
    std::cout<<"Start Server Process!"<<std::endl;
#ifdef WIN32
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2,2), &wsadata);
#endif
    SOCKET server_sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8081);
    if (bind(server_sock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN)) < 0) {
        std::cout << "Error while binding.." << std::endl;
        return -1;
    }
    listen(server_sock, 5);

    SOCKADDR_IN clientAddr;
    int len;
    SOCKET cli_sock = accept(server_sock, (SOCKADDR*)&clientAddr, &len);

    char buf[30];
    memset(buf, 0, sizeof(buf));
    int n = recv(cli_sock, buf, 29, 0);

    std::cout << "read buf : " << buf << "(" << n << ")" <<std::endl;
    WSACleanup();
    return 0;
}
