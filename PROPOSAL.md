# Final Project Proposal

## Group Members: 

Niki Chen
Sophia Dasser
       
# Intentions:

A statement of the problem you are solving and/or a high level description of the project.
    
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
    - receives all client messages and writes it into a txt file w/ timestamp (Sophia)
    - stores time that the server receives the message from client (Niki)
    - echos it back to all clients with timestamp (Niki)
    - continues to wait for new messages (Sophia)
    - keep chat open until all clients log off (Niki)
    - chat log will be found in the directory of the client that initiated the chat (Sophia)

    client:
    - initiates a username (Sophia)
    - initiate chat (Niki)
    - initiate connection with server (Sophia)
    - waits for user input (Niki)
    - writes to server (Sophia)
    - display chat log in real time (Niki)
    - displays username with every message (Sophia)
    - store time (Niki)
    - clients send an interrupt signal to log off chat (Sophia)

What data structures you will be using and how.
     
What algorithms and /or data structures you will be using, and how.
    
# Intended pacing:

A timeline with expected completion dates of parts of the project.
