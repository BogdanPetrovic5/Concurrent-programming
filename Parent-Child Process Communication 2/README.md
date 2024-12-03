# Program overview
This is a program written in C where the main thread is the parent process that creates (forks) a child process. 
The parent process generates a random number in the range of 0 to 9 every 6 seconds and sends the corresponding signal to the child process.
If the generated number is even, the parent sends the SIGINT signal to the child; if the number is odd, it sends SIGCHLD; and if the number is 0, it sends SIGFPE. 
After sending the signal, the parent waits for 6 seconds and then starts a new round of signal sending until the child process is terminated.

The child process, in an infinite loop, prints a message every 3 seconds: `I am the child PID NUMBER`.
If the child receives the SIGINT signal, it increments the variable NUMBER by 1 and prints the message “I increased the variable.” 
If the child receives the SIGCHLD signal, it decrements the variable NUMBER by 1 and prints the message “I decreased the variable.” 
In the case of receiving the SIGFPE signal, the child prints the message “Finished with work” and terminates.
