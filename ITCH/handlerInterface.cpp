#include "include/handlerInterface.hpp"

#include <iostream>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

void ITCH41::ITCH_Handler::start(const char* address, int port, std::thread *lthread) {

    int server_fd, new_socket;
    struct sockaddr_in serv_addr;
    int opt = 1;
    int addrlen = sizeof(serv_addr);

    this->listenThread = lthread;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(address);
    serv_addr.sin_port = htons(port);

    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    lthread = new std::thread([this, server_fd, addrlen]() {
        while (true) {
            int new_socket;
            struct sockaddr_in client_addr;
            if ((new_socket = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t*)&addrlen)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            // Handle the connection in the same thread to avoid the overhead of spawning a new thread
            char buffer[1024] = {0};
            int valread = read(new_socket, buffer, 1024);
            action(reinterpret_cast<unsigned char*>(buffer), valread, new_socket);

            close(new_socket);
        }
    });

    lthread->join();


}


void ITCH41::ITCH_Handler::send_msg(unsigned char* msg, int socket) {

    send(socket, msg, strlen(reinterpret_cast<char*>(msg)), 0);

}