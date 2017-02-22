/* 
 * File:   main.cpp
 * Author: tommy
 *
 * Created on February 15, 2017, 6:11 PM
 */

#include <cstdlib>
#include "socket_headers.h"
#include "client_loop.h"
#include "server_configuration.h"

/*****************************************************************/

//declared in serrver_vonfiguration.h
const char *DAFAULT_SERVER_PASSWORD = "password";
int server_port = SERVER_PORT;
const char *server_password = DAFAULT_SERVER_PASSWORD;

int main(int argc, char* argv[]) {
    if (argc > 1)
        server_port = atoi(argv[1]);
    if (argc > 2)
        server_password = argv[2];



    void init_client_loop();

    int nSocket, nClientSocket;
    int nBind, nListen;
    int nFoo = 1;
    socklen_t nTmp;
    struct sockaddr_in stAddr, stClientAddr;

    /* address structure */
    memset(&stAddr, 0, sizeof (struct sockaddr));
    stAddr.sin_family = AF_INET;
    stAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    stAddr.sin_port = htons(server_port);

    /* create a socket */
    nSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (nSocket < 0) {
        fprintf(stderr, "%s: Can't create a socket.\n", argv[0]);
        exit(1);
    }
    setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR, (char*) &nFoo, sizeof (nFoo));

    /* bind a name to a socket */
    nBind = bind(nSocket, (struct sockaddr*) &stAddr, sizeof (struct sockaddr));
    if (nBind < 0) {
        fprintf(stderr, "%s: Can't bind a name to a socket.\n", argv[0]);
        exit(1);
    }
    /* specify queue size */
    nListen = listen(nSocket, QUEUE_SIZE);
    if (nListen < 0) {
        fprintf(stderr, "%s: Can't set queue size.\n", argv[0]);
    }

    while (1) {
        /* block for connection request */
        nTmp = sizeof (struct sockaddr);
        nClientSocket = accept(nSocket, (struct sockaddr*) &stClientAddr, &nTmp);
        if (nClientSocket < 0) {
            fprintf(stderr, "%s: Can't create a connection's socket.\n", argv[0]);
        } else {
            printf("[connection from %s]\n",
                    inet_ntoa((struct in_addr) stClientAddr.sin_addr));
            pthread_t id;
            pthread_create(&id, NULL, client_loop, &nClientSocket);
        }
    }

    close(nSocket);
    return (0);
}


