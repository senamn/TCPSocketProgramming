/*
Author: Sena Moon

CSCE 3530 Programming Assignment #1 - Client

This program lets server and client communicate with each other. 
Client side accepts user input message and send it to the server. 
Then, the server converts user input message to have the first letter capitalized and the rest of the letters into lower case. 
Server also counts the number of spaces, alphabets, and vowels of the accepted message. 
Finally, server sends processed information back to the client and client prints them out.
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int sockfd = 0, portno;
    char recvBuff[255]; // Array for user input message
    char msg[255]; // Array for message received from server
    int msg_sent, msg_len, msg_recv;
    struct sockaddr_in serv_addr;
    // memset(recvBuff, '0', sizeof(recvBuff));
    // memset(msg, '0', sizeof(msg));

    // Create client socket, if fails, prompt error message
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket error\n");
        exit(EXIT_FAILURE);
    }

    // Create address structure to connect to
    memset(&serv_addr, 0, sizeof(serv_addr)); // Clear out structure
    serv_addr.sin_family = AF_INET; // Address family
    // Accept user input port number
    portno = atoi(argv[1]);
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = inet_addr("129.120.151.95");

    // If connection to the server fails, prompt error message
    if (connect(sockfd, (const struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("connect error\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        // memset(recvBuff, '0', sizeof(recvBuff));
        // memset(msg, '0', sizeof(msg));

        // Clear out recvBuff and msg arrays
        bzero(recvBuff, sizeof(recvBuff));
        bzero(msg, sizeof(msg));
        // Prompt the user to input a message
        printf("\nInput: ");
        // Receive user input message
        fgets(recvBuff, 255, stdin);
        // If user inputs "quit", send the message to server and end the program
        if (strncmp(recvBuff,"quit", 4) == 0)
        {
            msg_sent = send(sockfd, recvBuff, msg_len, 0);
            if (msg_sent < 0)
            {
                printf("send error\n");
                exit(EXIT_FAILURE);
            }
            printf("\ncya!\n");
            exit(0);
        }

        // Send message to server
        msg_len = strlen(recvBuff);
        msg_sent = send(sockfd, recvBuff, msg_len, 0);
        // Prommpt error message if send fails
        if (msg_sent < 0)
        {
            printf("send error\n");
            exit(EXIT_FAILURE);
        }
        // Receive message from server
        // Prompt error message if receive fails
        msg_recv = recv(sockfd, msg, sizeof(msg), 0);
        if (msg_recv < 0)
        {
            printf("receive error\n");
            exit(EXIT_FAILURE);
        }
        // Print out processed message sent from server
        printf("%s", msg);
        // Clear out msg array
        bzero(msg, sizeof(msg));

    }

    return 0;
}
