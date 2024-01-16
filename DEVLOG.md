# Dev Log:

## Niki Chen

### 2024-01-02 - Brief description
Expanded description including how much time was spent on task.

### 2024-01-03 - Proposal
Outlined project in proposal; filled out all fields - 1 hour

### 2024-01-04 - Basic server and client network
Together, we pair programmed networking.c, included select statement so multiple clients can connect to a single server. Tried to make server continue receiving client messages after the first one. - 2 hours

### 2024-01-05 - Persistent server
Made server continue receiving client messages indefinitely.  - 1 hour

### 2024-01-07 - Invididual sockets for each client
Tried to have server to listen from five different sockets for different clients - 45 mins
Implemented client_sockets struct to store data about clients & messages - 20 mins

### 2024-01-08 - Invididual sockets for each client
Replaced client_sockets array with int sockets array - 15 mins
Server still only listens once - 1 hour

### 2024-01-09 - Client communication
Server can listen to one client at a time indefinitely - 1 hour
New version: server allows multiple clients to connect and echos messages (kind of, not really working). buff not clearing after every message stored. clients can't send multiple consecutive messages (needs to wait) - 1.5 hours

### 2024-01-10 - Client sending messages
Server listens to all client messages - 30 mins
Server echos message from client to others - 30 mins

### 2024-01-11 - Seg fault on lab machine
Server seg faults on lab machine because we forgot to initalize the sockets array, fixed - 1 hour

### 2024-01-12 - Testing connection between lab machines
Tried connecting a non-lab machine to lab machine, did not work
Connection between two lab machines works - 1 hour

### 2024-01-13 - Username implemented
Sends struct through sockets; structs contain username and message - 40 mins
Incoming messages on client end displays username - 30 mins

### 2024-01-14 - Client disconnect message
Server displays the name of client that disconnected; Stores all client structs in an array
Only displays name of the client that last sent a message - 1.5 hours

### 2024-01-15 - Client connect/disconnect message
Tried to fix disconnect bug, but it's still skewed
Increased max clients to 10



## Sophia Dasser

### 2024-01-02 - N/A
N/A (we didn't recieve the project yet)

### 2024-01-03 - Proposal
Completed the proposal, filled out all fields - 1hr

### 2024-01-04 - Basic server and client network
Together we pair programmed the networking.c, included select statement so that multiple clients can connect to server, and then we made sure that are client was persistent so that it would always be prompted user input. We left a bug that caused the socket to be made until the program crashed (so it was tooooo persistent) - 2 hr

### 2024-01-05 - Persistent Input
We pair programmed the persistant server, so that the client can always send a message until they choose to logout. - 1hr

### 2024-01-08 - Sockets for Clients
Pair programmed an array of sockets for each client. Originally was a struct and then we changed it later (read 01/11) to become only an arry of sockets - 1hr

### 2024-01-09 - Out sick

### 2024-01-10 - Client Sending Message
Worked on print statements of the chat, and only one socket opening at a time - 30 min

### 2024-01-11 - Fixed Segfault
Because we did most of our work on a mac, we realized that we needed to iniatlize the array of sockets before we used it. - 1hr

### 2024-01-12 - Tested Sockets
We tested sockets from multiple lab machines to the same server (IT WORKS!!!) and made everything look more like a chat, we also worked on bringing back the struct idea we had in 01/08 - 2hr

### 2024-01-14 - More Chat-like
Fixed the chat to look more chat like with interaction between clients to include the user of the client. (1hr)

### 2024-01-15 - Chat-log and Time stamps
A chat log is created with every new chat and time stamps are sent with every message (2.5 hr)



