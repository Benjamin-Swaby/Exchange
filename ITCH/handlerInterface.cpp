#include "include/handlerInterface.hpp"

#include <iostream>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

void ITCH41::ITCH_Handler::start(const char* address, int port) {

    int server_fd, new_socket;
    struct sockaddr_in serv_addr;
    int opt = 1;
    int addrlen = sizeof(serv_addr);


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

    listenThread = new std::thread([this, server_fd, addrlen]() {
        while (true) {
            struct sockaddr_in client_addr;
            if ((this->socketID = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t*)&addrlen)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            // Handle the connection in the same thread to avoid the overhead of spawning a new thread
            while (true) {
                char buffer[1024] = {0};
                int valread = read(this->socketID, buffer, 1024);
                if (valread <= 0) {
                    // Client closed the connection or error occurred
                    close(this->socketID);
                    break;
                }
                action(reinterpret_cast<unsigned char*>(buffer), valread, this->socketID);
            }
        }
    });

}


void ITCH41::ITCH_Handler::action(unsigned char* buffer, size_t size, int socket) {
    switch (buffer[0]) {
        case 'S': 
            if (size < sizeof(System_Event_Message)) return; 
            handle(reinterpret_cast<System_Event_Message*>(buffer), socket); 
            break;
        case 'R': 
            if (size < sizeof(Stock_Directory)) return; 
            handle(reinterpret_cast<Stock_Directory*>(buffer), socket); 
            break;
        case 'H': 
            if (size < sizeof(Stock_Trading_Action)) return; 
            handle(reinterpret_cast<Stock_Trading_Action*>(buffer), socket); 
            break;
        case 'Y': 
            if (size < sizeof(Reg_SHO_Restriction)) return; 
            handle(reinterpret_cast<Reg_SHO_Restriction*>(buffer), socket); 
            break;
        case 'L': 
            if (size < sizeof(Market_Participant_Position)) return; 
            handle(reinterpret_cast<Market_Participant_Position*>(buffer), socket); 
            break;
        case 'A': 
            if (size < sizeof(Add_Order_Message)) return; 
            handle(reinterpret_cast<Add_Order_Message*>(buffer), socket); 
            break;
        case 'F': 
            if (size < sizeof(Add_Order_MPID_Attribution)) return; 
            handle(reinterpret_cast<Add_Order_MPID_Attribution*>(buffer), socket); 
            break;
        case 'E': 
            if (size < sizeof(Order_Executed_Message)) return; 
            handle(reinterpret_cast<Order_Executed_Message*>(buffer), socket); 
            break;
        case 'C': 
            if (size < sizeof(Order_Executed_With_Price_Message)) return; 
            handle(reinterpret_cast<Order_Executed_With_Price_Message*>(buffer), socket); 
            break;
        case 'X': 
            if (size < sizeof(Order_Cancel_Message)) return; 
            handle(reinterpret_cast<Order_Cancel_Message*>(buffer), socket); 
            break;
        case 'D': 
            if (size < sizeof(Order_Delete_Message)) return; 
            handle(reinterpret_cast<Order_Delete_Message*>(buffer), socket); 
            break;
        case 'U': 
            if (size < sizeof(Order_Replace_Message)) return; 
            handle(reinterpret_cast<Order_Replace_Message*>(buffer), socket); 
            break;
        case 'P': 
            if (size < sizeof(Trade_Message)) return; 
            handle(reinterpret_cast<Trade_Message*>(buffer), socket); 
            break;
        case 'Q': 
            if (size < sizeof(Cross_Trade_Message)) return; 
            handle(reinterpret_cast<Cross_Trade_Message*>(buffer), socket); 
            break;
        case 'B': 
            if (size < sizeof(Broken_Trade_Message)) return; 
            handle(reinterpret_cast<Broken_Trade_Message*>(buffer), socket); 
            break;
        case 'I': 
            if (size < sizeof(NOII_Message)) return; 
            handle(reinterpret_cast<NOII_Message*>(buffer), socket); 
            break;
        case 'N': 
            if (size < sizeof(RPII_Message)) return; 
            handle(reinterpret_cast<RPII_Message*>(buffer), socket); 
            break;
        default: 
            handle(buffer, socket);
    }
}

void ITCH41::ITCH_Handler::send_msg(unsigned char* msg, int socket) {

    send(socket, msg, strlen(reinterpret_cast<char*>(msg)), 0);

}


ITCH41::ITCH_Handler::~ITCH_Handler() {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // wait 1 second for requests.
    close(this->socketID);
    this->listenThread->join();
}