# Final Project Proposal

## Group Members: 

Niki Chen
Sophia Dasser
       
# Intentions:

A statement of the problem you are solving and/or a high level description of the project.

We'll be creating a chat that uses select statements to connect a server to multiple clients. The chat will be iniated by the server, and clients will connect to a specific server to chat. The messages will be sent by clients and will include a username (that the client will choose at the beginning of the connection) and the time stamp of when the server recieved the message. The server will store/write the message into the chatlog.txt file and echo back the message to all the clients. A chat will only close when all the clients leave the chat. When a client leaves the chat, chatlog.txt will be downloaded on the client's machine.
    
# Intended usage:

interface: on the terminal
multiple clients connected to the same server
shows chat log for every client immediately
clients can send to chat at the same time  
features: 
- timestamp
- client's name

# Technical Details:

A description of your technical design. This should include:
   
How you will be using the topics covered in class in the project.
     sockets, pipes, processes (fork), working with files

How you are breaking down the project and who is responsible for which parts.

select statements (mr. k demo)
server:
* receives all client messages and writes it into a txt file w/ timestamp (Sophia)
* stores time that the server receives the message from client (Niki)
* echos it back to all clients with timestamp (Niki)
* continues to wait for new messages (Sophia)
* keep chat open until all clients log off (Niki)
* chat log will be found in the directory of the client that initiated the chat (Sophia)

client:
* initiates a username (Sophia)
* initiate chat (Niki)
* initiate connection with server (Sophia)
* waits for user input (Niki)
* writes to server (Sophia)
* display chat log in real time (Niki)
* displays username with every message (Sophia)
* store time (Niki)
* clients send an interrupt signal to log off chat (Sophia)

What data structures you will be using and how.

A struct will be created for each client containing:
* a char array that holds the username
* a char array that holds the message
* an int that holds the time
* a boolean that will contain whether the client is active or not (maybe)

We will be using:
Pipes - to secure a connection between the clients and servers
Sockets - to connect multiple clients to the same server
Processes - we will use forking so that the client will always be prompted to say something in the chat
File Processes - we will create a chatlog.txt that will be appended with every new message and downloaded on the client of every computer
Select with many clients - we will maintain a list of clients that have joined the chat to connect it with the server
     
What algorithms and /or data structures you will be using, and how.
    
# Intended pacing:

A timeline with expected completion dates of parts of the project.

1. Before Monday the 8th we will have the connecting clients to a single server and each client sending a message to the server working (the client.c, server.c, and networking.c basics should be done)
2. 9th: We will have the server store the message from any client and put into a chatlog.c
3. 10th: We will have the server echo the message to all clients with the time stamp of when the message is recieved
4. 11th: We will fork the process, so the client can send the message as many times as it wants
5. 12th: The server will print the chat log everytime it echos back a message.
6. 13th and beyond: Making the username works and possible channels...

