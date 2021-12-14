The program demonstrates IPC through shared memory with the help of a password strength calculator application

Internal details
Process 1 gets access to a chunk of memory for shared usage which is allocated by generating a key and invoking shmget with the generated key as argument   
Process 1 gets a password as input from user and writes it to the shared memory
Process 1 then forks and uses execvp command to initiate the execution of process 2
After forking, process 1 executes waitpid with pid of process 2 thereby going into the wait state
Process 2 gets access to the shared memory via the key (the same key used by process 1) 
Process 2 accesses the password from shared memory and calculates the number of alphanumeric characters and special characters
Process 2 writes the calculated counts of alphanumeric characters and special characters into the shared memory
Process 2 then forks and uses execvp command to initiate the execution of process 3
After forking, process 2 executes waitpid with pid of process 3 thereby going into the wait state
Process 2 gets access to the shared memory via the key (the same key used by process 1 and process 2)
Process 3 accesses the counts of alphanumeric characters and special characters from shared memory and finds the strength of the password
Process 3 then writes the strength of the input password into the shared memory
Process 3 terminates thus waking up process 2
Process 2 terminates thus waking up process 1
Process 1 reads the strength of the password from the shared memory written by process 3 and outputs the same to the terminal

Functions related to shared memory used in the code are as follows:
ftok()   :generates a key
shmget() :allocates memory to be shared based on key and returns a memory identifier
shmat()  :returns a pointer to the shared memory based on the identifier of the shared memory given as argument

Method to run:
Compile the three programs, process1.c, process2.c and process3.c
Run process1.c
