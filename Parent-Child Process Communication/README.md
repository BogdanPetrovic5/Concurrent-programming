# Parent-Child Process Communication with Message Queues
This C program demonstrates inter-process communication (IPC) between a parent and a child process using System V message queues. 
The program involves two processes that send and receive messages, with the ability to terminate the communication by sending a special "stop\n" message. 
Both processes can terminate each other using signals (SIGKILL).
