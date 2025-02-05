#include "include/clientInterface.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

namespace ITCH41 {


    void ITCH_Client::start_session(char* address, int port) {
        struct sockaddr_in serv_addr;

        if ((this->sessionSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            std::cerr << "Socket creation error" << std::endl;
            return;
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);

        if (inet_pton(AF_INET, address, &serv_addr.sin_addr) <= 0) {
            std::cerr << "Invalid address/ Address not supported" << std::endl;
            return;
        }

        if (connect(this->sessionSocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            std::cerr << "Connection Failed" << std::endl;
            return;
        }

        this->address = address;
        this->port = port;   
    }

    void ITCH_Client::send_msg(const unsigned char* message, int len) {
        
        send(this->sessionSocket, message, len, 0);

        log(message);

    }


    void ITCH_Client::stop_session() {

        close(this->sessionSocket);

    }

    

}