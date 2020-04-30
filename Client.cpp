//
// Created by Yana Molodetsky on 19/12/2019.
#include "Client.h"
#include "SymbolTable.h"
#include <sys/socket.h>
#include "Defines.h"
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void Client::creatConnection(int port,const char* ip) {
    bool flag = true;
    SymbolTable *s = s->getTable();
    map<string, Var*>::iterator it;
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
    }
    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr(ip);  //the localhost address
    address.sin_port = htons(port);
    while (flag) {
        int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
        if (is_connect == -1) {
            std::cerr << "Could not connect to host server"<<std::endl;
        } else {
            std::cout<<"Client is now connected to server" <<std::endl;
            flag = false;
        }
    }

    while (s->getIfRun()) {
        if (!s->getMessages().empty()) {
            while (!s->getMessages().empty()) {
                string message = s->getMessages().front();
                s->pop_from_Messages();
                const char *c = message.c_str();
                send(client_socket, c, strlen(c), 0);
            }
        }
    }
    close(client_socket);
}
