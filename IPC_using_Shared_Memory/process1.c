#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>


int main()
{
    int SharedMemID;
    key_t key;

	//generating key for creating and accessing shared memory
	key = ftok("process1",37);

    //getting the identifier to the shared memory
	SharedMemID = shmget(key,50,IPC_CREAT | 0666);
    char *SharedMemPtr;
	
	if(SharedMemID < 0)
        {
            perror("shmget");
            exit(1);
        }
	
    //getting the pointer to shared memory
	SharedMemPtr = shmat(SharedMemID, NULL, 0);
	
	printf("Process 1\n");
    char password [11];
    printf("Enter the Password:\n");
    scanf("%s",password);
	//Write the password into shared memory
    strcpy(SharedMemPtr, password);
	pid_t PID =fork();
	if(PID == 0)
	{
		char *args[]={"./process2",NULL};
		execvp(args[0],args);
	}
    (void)waitpid(PID,NULL,0);
    char Strength[7];
    strcpy(Strength, SharedMemPtr + 11 + 2 * sizeof(int));
    printf("Process 1\n");
    printf("The strength of the password as received from process 3 is: %s\n", Strength); 
    exit(0);
}
    
    
		
		
		
	
