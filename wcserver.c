/*
Author: Sena Moon

CSCE 3530 Programming Assignment #1 - Server

This program lets server and client communicate with each other. 
Client side accepts user input message and send it to the server. 
Then, the server converts user input message to have the first letter capitalized and the rest of the letters into lower case. 
Server also counts the number of spaces, alphabets, and vowels of the accepted message. 
Finally, server sends processed information back to the client and client prints them out.
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0, cli_size, portno, msg_received;
    struct sockaddr_in serv_addr, cli_addr;
    char sendBuff[255]; // Array for message sent from client
    char temp[255]; // Array for processed message to send back to client
    
    // Create a socket for listening, if fails, prompt error message
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("socket error\n");
        exit(EXIT_FAILURE);
    }

    // Create local address structure
    memset(&serv_addr, '0', sizeof(serv_addr)); // Clear out structure
    serv_addr.sin_family = AF_INET; // Address family
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    //Accept user input port number
    portno = atoi(argv[1]);
    serv_addr.sin_port = htons(portno);   

    // int on = 1;
    // setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    
    // int i = bind(listenfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    // if (i < 0)
    // {
    //     printf("bind error\n");
    //     exit(EXIT_FAILURE);
    // }
    
    // Bind server socket to the local address
    if (bind(listenfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("bind error\n");
        exit(EXIT_FAILURE);
    }

    // Server starts to listen
    if (listen(listenfd, 5) == -1)
    {
        printf("listen error\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        // Create another socket to receive messages from client
        cli_size = sizeof(cli_addr);
        if ((connfd = accept(listenfd,(struct sockaddr *) &cli_addr,&cli_size)) == -1)
        {
            printf("accept error\n");
            exit(EXIT_FAILURE);
        }
        while (1)
        {
            //memset(sendBuff, '0', sizeof(sendBuff));

            // Clear out senbBuff array
            bzero(sendBuff, sizeof(sendBuff));
            // Receive messages from client
            msg_received = recv(connfd, sendBuff, 255, 0);

            if(msg_received > 0)
            {
                sendBuff[msg_received] = 0;

                // If client sends "quit", close sockets and exit program
                if (strncmp(sendBuff,"quit", 4) == 0)
                {
                    printf("cya!\n");
                    close(connfd);
                    close(listenfd);
                    exit(0);
                }

                // Print out message received from client
                printf("Message received: %s", sendBuff);
                //memset(sendBuff, '0', sizeof(sendBuff));
                //bzero(sendBuff, sizeof(sendBuff)); //GIVES INFINITE LOOP ON SERVER SIDE
                
                // Convert first letter to capital letter & rest of the letters into lower case
                int l;
                for(l = 0; sendBuff[l] != '\0'; l++)
                {
                    if(l == 0)
                    {
                        if(sendBuff[l]>='a' && sendBuff[l]<='z')
                        {
                            sendBuff[l] = sendBuff[l]-32;
                        }
                    }

                    else
                    {
                        if(sendBuff[l]>='A' && sendBuff[l]<='Z')
                        {
                            sendBuff[l] = sendBuff[l]+32;
                        }
                    }
                }
                //printf("Converted message: %s", sendBuff);

                // Count spaces
                int m, spc_count = 0;
                for(m = 0; sendBuff[m] != '\0'; m++)
                {
                    if(sendBuff[m] == ' ')
                    {
                        spc_count++;
                    }
                }
                //printf("Space count: %d\n", spc_count);

                // Count alphabets
                int n, alpha_count = 0;
                for(n = 0; sendBuff[n] != '\0'; n++)
                {
                    if(sendBuff[n]>='a' && sendBuff[n]<='z' || sendBuff[n]>='A' && sendBuff[n]<='Z')
                    {
                        alpha_count++;
                    }
                }
                //printf("Alpha count: %d\n", alpha_count);

                // Count vowels
                int a, vowel_count = 0;
                for(a = 0; sendBuff[a] != '\0'; a++)
                {
                    if(sendBuff[a] == 'a' || sendBuff[a] == 'e' || sendBuff[a] == 'i' 
                        || sendBuff[a] == 'o' || sendBuff[a] == 'u' || sendBuff[a] == 'A'
                        || sendBuff[a] == 'E' || sendBuff[a] == 'I' || sendBuff[a] == 'O' || sendBuff[a] == 'U')
                    {
                        vowel_count++;
                    }
                }
                //printf("Vowel count: %d\n", vowel_count);

                // Gather all processed information into temp array   
                sprintf(temp, "\nOutput: %s\nSpaces: %d\n\nAlphabets: %d\n\nVowels: %d\n\n", sendBuff, spc_count, alpha_count, vowel_count);
                
                // Send processed message back to client
                send(connfd, temp, strlen(temp), 0);
            }
        }

    }
        // Close sockets
        close(connfd); 
        close(listenfd);   
        sleep(1);


    return 0;
}