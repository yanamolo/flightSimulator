//
// Created by orit on 17/12/2019.
//

#include <unistd.h>
#include "OpenServerCommand.h"
#include "Server.h"
#include "Defines.h"

using namespace std;

int OpenServerCommand::execute(list<string>::iterator it) {
    SymbolTable* s = s->getTable();
    it++;
    int portS;
    Interpreter *inter = new Interpreter();
    portS = (int) inter->interpret(*it);
    delete inter;
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(portS);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }

    // accepting a client
    int addrSize = sizeof(address);
    int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &addrSize);

    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
    } else {
        std::cout << "Someone connected to server" << std::endl;
    }
    close(socketfd);
    auto *t1 = new thread(&OpenServerCommand::callingForAccept, this, client_socket);
    s->update_threads(t1);
    t1->detach();
    return 2;
}

void OpenServerCommand::callingForAccept(int client_socket) {
    this->server->runServer(client_socket);
}

OpenServerCommand::~OpenServerCommand() {
    delete this->server;
}
