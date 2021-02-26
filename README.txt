Author: Sena Moon

CSCE 3530 Programming Assignment #1

This program lets server and client communicate with each other. Client side accepts user input message and send it to the server. Then, the server converts user input message to have the first letter capitalized and the rest of the letters into lower case. Server also counts the number of spaces, alphabets, and vowels of the accepted message. Finally, server sends processed information back to the client and client prints them out.


To run this program:

* PORT_NUMBER could be any 4 or 5 digit integer from 1024 to 65535.

1. Log into cse02 and cse03 servers separately.

2. Upload wcserver.c, wcclient.c, and makefile to the CSE machine.

3. Enter "make" into either server.

4. Type ./wcs PORT_NUMBER into cse02 server to run the server socket.

5. Type ./wcc PORT_NUMBER (where the PORT_NUMBER is the same 1-5 digit integer used to connect server socket) into cse03 server to run the client socket.

6. Enter message into "Input: " prompt on the client side.

7. Enter "quit" into client side to end the program.

8. If you wish to remove .o and executable files created for this program, simply type in "make clean".